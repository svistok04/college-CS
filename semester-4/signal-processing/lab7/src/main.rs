use std::error::Error;
use std::f64::consts::PI;
use std::fs::File;
use std::io::{Write, BufWriter};

use plotters::prelude::*;
use plotters::style::full_palette::{GREEN, YELLOW, ORANGE};
use rand::prelude::*;
use rand_distr::Normal;

// const message_bitstream: &str = "1001000110010111011001101100110111101011000100000101011111011111110010110110011001000100001";
const message_bitstream: &str = "111010011100101100001110111011100111101101110100111100111101010110000100"; // 48

const T_c: f64 = 1.0; // signal duration
const W: f64 = 36.0; // scaling factor for the maximum frequency
const f_s: f64 = 3.0 * f_n2; // sampling frequency
const f_n: f64 = W / T_b; // maximum signal frequency
const f_n1: f64 = (W + 1.0) / T_b; // maximum signal frequency for FSK
const f_n2: f64 = (W + 2.0) / T_b; // maximum signal frequency for FSK
const N: usize = (f_s * T_c) as usize; // number of samples
const fn hamming_encoded_length(bits: usize) -> usize {
    let rounded_bits = if bits % 4 == 0 { bits } else { ((bits + 4 - bits % 4) / 4) * 4 };
    (rounded_bits / 4) * 7
}
const B: usize = hamming_encoded_length(message_bitstream.len()); // number of bits
// const B: usize = 10;
const T_b: f64 = T_c / B as f64; // bit duration
// const T_b: f64 = 0.5;
const A_1: f64 = 1.0; // amplitude for 0
const A_2: f64 = 0.5; // amplitude for 1
const A_r: f64 = 1.0;


fn main() {
    println!("Hello, world!");
    let mut file = BufWriter::new(File::create("data.txt").unwrap());
    println!("{}", N);
    println!("{}", T_b);
    let alpha = 0.7;
    let beta = 8.4;
    let method = "FSK";
    let mode = 1;
    let output = system(message_bitstream, method, mode, alpha, beta);
    println!("{:?}", output);
    visualize_signals(&message_bitstream, &output, "5porownianie.png").unwrap();
    writeln!(file, "{}_{}", method, mode).unwrap();
    writeln!(file, "alpha{}, beta{}", alpha, beta).unwrap();
    writeln!(file, "input: {}", message_bitstream).unwrap();
    writeln!(file, "output: {}", output).unwrap();
    writeln!(file, "BER: {}", calculate_ber(message_bitstream, &output)).unwrap();
    println!("{}", calculate_ber(message_bitstream, &output));
    // let method = "PSK";
    // let mode = 1;
    // let mut file = BufWriter::new(File::create("ber_tests_mode_1.txt").unwrap());
    // writeln!(file, "simulating BER over alpha with constant beta = 5 and mode {}", mode).unwrap();
    // simulate_ber_over_alpha(&mut file, 0.0..1.0, 0.1, method, mode);
    // writeln!(file, "simulating BER over beta with constant alpha = 0.5 and mode {}", mode).unwrap();
    // simulate_ber_over_beta(&mut file,0.0..10.0, 1.0, method, mode);
    // let mode = 2;
    // let mut file = BufWriter::new(File::create("ber_tests_mode_2.txt").unwrap());
    // writeln!(file, "simulating BER over alpha with constant beta = 5 and mode {}", mode).unwrap();
    // simulate_ber_over_alpha(&mut file, 0.0..1.0, 0.1, method, mode);
    // writeln!(file, "simulating BER over beta with constant alpha = 0.5 and mode {}", mode).unwrap();
    // simulate_ber_over_beta(&mut file,0.0..10.0, 1.0, method, mode);

}

fn hamming_encoder(input: &[u8]) -> Vec<u8> {
    if input.len() != 4 {
        panic!("Input length must be 4");
    }
    let mut output = vec![0; 7];

    output[2] = input[0];
    output[4] = input[1];
    output[5] = input[2];
    output[6] = input[3];

    let p1 = output[2] ^ output[4] ^ output[6];
    let p2 = output[2] ^ output[5] ^ output[6];
    let p4 = output[4] ^ output[5] ^ output[6];

    output[0] = p1;
    output[1] = p2;
    output[3] = p4;

    output
}

fn hamming_decoder(input: &[u8]) -> Vec<u8> {
    if input.len() != 7 {
        panic!("Input length must be 7");
    }

    let p1 = input[0] - b'0';
    let p2 = input[1] - b'0';
    let p3 = input[2] - b'0';
    let p4 = input[3] - b'0';
    let p5 = input[4] - b'0';
    let p6 = input[5] - b'0';
    let p7 = input[6] - b'0';

    let s1 = (p1 ^ p3 ^ p5 ^ p7) as usize;
    let s2 = (p2 ^ p3 ^ p6 ^ p7) as usize;
    let s4 = (p4 ^ p5 ^ p6 ^ p7) as usize;

    let syndrome = (s4 << 2) | (s2 << 1) | s1;

    let mut corrected = input.to_vec();
    if syndrome != 0 {
        corrected[syndrome - 1] ^= 1;
    }

    vec![corrected[2], corrected[4], corrected[5], corrected[6]]
}

fn modulation(input: &[u8], method: &str) -> Vec<f64> {
    let timings: Vec<f64> = (0..N)
        .map(|n| {
            n as f64 / f_s
        })
        .collect();
    let step = N / B;
    let output: Vec<f64> = match method {
        "ASK" => {
                (0..N)
                .map(|i| {
                    let n = i / step;
                    if input[n]  == b'1' {
                        A_1 * (2.0 * PI * f_n * timings[i]).sin()
                    } else {
                        A_2 * (2.0 * PI * f_n * timings[i]).sin()
                    }
                })
                .collect()
        },
        "FSK" => {
            (0..N)
                .map(|i| {
                    let n = i / step;
                    if input[n] == b'0' {
                        (2.0 * PI * f_n1 * timings[i]).sin()
                    } else {
                        (2.0 * PI * f_n2 * timings[i]).sin()
                    }
                })
                .collect()
        },
        "PSK" => {
            (0..N)
                .map(|i| {
                    let n = (i / step);
                    if input[n] == b'0' {
                        (2.0 * PI * f_n * timings[i]).sin()
                    } else {
                        (2.0 * PI * f_n * timings[i] + PI).sin()
                    }
                })
                .collect()
        },
        _ => {
            panic!("Invalid modulation method");
        }
    };
    draw_graph(&timings, &output, "1modulated_signal.png", "Time", "Values").unwrap();
    output
}

fn demodulation(input: Vec<f64>, method: &str) -> Vec<u8> {
    let timings: Vec<f64> = (0..N)
        .map(|n| {
            n as f64 / f_s
        })
        .collect();
    let dt = 1.0 / f_s;
    let chunk_size = N / B;
    let output = match method {
        "ASK" => {
            let x: Vec<f64> = (0..N)
                .map(|i| {
                    input[i] * (2.0 * PI * f_n * timings[i]).sin()
                })
                .collect();
            // draw_graph(&timings, &x, "2x.png", "Time", "Values").unwrap();
            let p: Vec<f64> = x.chunks(chunk_size).flat_map(|chunk| {
                trapezoidal_rule(chunk, dt)
            }).collect();
            // draw_graph(&timings, &p, "3p.png", "Time", "Values").unwrap();
            let mut max_mean = 0.0;
            let h = p.chunks(chunk_size).map(|chunk| {
                let mean = chunk.iter().sum::<f64>() / chunk.len() as f64;
                if mean > max_mean {
                    max_mean = mean;
                }
                max_mean
            })
                .last()
                .unwrap_or(0.0);
            let c: Vec<u8> = p.chunks(chunk_size).map(|chunk| {
                let last = chunk[chunk.len() - 1];
                if last > h {
                    b'1'
                } else {
                    b'0'
                }
            }).collect();
            c
        },
        "FSK" => {
            let x_1: Vec<f64> = (0..N)
                .map(|i| {
                    input[i] * (2.0 * PI * f_n1 * timings[i]).sin()
                }).collect();
            draw_graph(&timings, &x_1, "2x_1.png", "Time", "Values").unwrap();
            let x_2: Vec<f64> = (0..N)
                .map(|i| {
                    input[i] * (2.0 * PI * f_n2 * timings[i]).sin()
                }).collect();
            draw_graph(&timings, &x_2, "2x_2.png", "Time", "Values").unwrap();
            let p_1: Vec<f64> = x_1.chunks(N / B)
                .flat_map(|chunk| {
                    trapezoidal_rule(chunk, dt)
                }).collect();
            draw_graph(&timings, &p_1, "3p_1.png", "Time", "Values").unwrap();
            let p_2: Vec<f64> = x_2.chunks(N / B)
                .flat_map(|chunk| {
                    trapezoidal_rule(chunk, dt)
                }).collect();
            draw_graph(&timings, &p_2, "3p_2.png", "Time", "Values").unwrap();
            let p: Vec<f64> = p_1.iter().zip(p_2.iter())
                .map(|(x, y)| {
                    -x + y
                }).collect();
            draw_graph(&timings, &p, "3p.png", "Time", "Values").unwrap();
            let c: Vec<u8> = p.chunks(N / B)
                .map(|chunk| {
                    let mean = chunk.iter().sum::<f64>() / chunk.len() as f64;
                    if mean > 0.0 {
                        b'1'
                    } else {
                        b'0'
                    }
                }).collect();
            c
        },
        "PSK" => {
            let x: Vec<f64> = (0..N)
                .map(|i| {
                    input[i] * (2.0 * PI * f_n * timings[i]).sin()
                }).collect();
            // draw_graph(&timings, &x, "2x.png", "Time", "Values").unwrap();
            let p: Vec<f64> = x.chunks(N / B).flat_map(|chunk| {
                trapezoidal_rule(chunk, dt)
            }).collect();
            // draw_graph(&timings, &p, "3p.png", "Time", "Values").unwrap();
            let c: Vec<u8> = p.chunks(N / B).map(|chunk| {
                let mean = chunk.iter().sum::<f64>() / chunk.len() as f64;
                if mean < 0.0 {
                    b'1'
                } else {
                    b'0'
                }
            }).collect();
            c
        },
        _ => {
            panic!("Invalid demodulation method");
        }
    };
    // draw_graph2(&timings, &input, &output, "4porownianie.png").unwrap();
    output
}

fn channel(input: Vec<f64>, mode: u8, alpha: f64, beta: f64) -> Vec<f64> {
    match mode {
        1 => {
            let input = AWGN(input, alpha);
            attenuation(input, beta)
        },
        2 => {
            let input = attenuation(input, beta);
            AWGN(input, alpha)
        },
        _ => {
            panic!("Invalid channel mode");
        }
    }
}

fn AWGN(input: Vec<f64>, alpha: f64) -> Vec<f64> {
    let noise_level = 1.0;
    let normal = Normal::new(0.0, noise_level).unwrap();
    input.iter()
        .map(|&x| {
            x + alpha * normal.sample(&mut thread_rng())
        }).collect::<Vec<f64>>()
}

fn attenuation(input: Vec<f64>, beta: f64) -> Vec<f64> {
    input.iter().enumerate()
        .map(|(i, &x)| {
            let t = i as f64 / f_s;
            x * (-beta * t).exp()
        })
        .collect::<Vec<f64>>()
}

fn system(input: &str,
          modulation_method: &str,
          channel_mode: u8,
          alpha: f64,
          beta: f64) -> String {
    let mut input = input.as_bytes().to_vec();
    if input.len() % 4 != 0 {
        input.resize(input.len() + 4 - input.len() % 4, b'0');
    }
    let encoded: Vec<u8> = input
        .chunks(4)
        .flat_map(|chunk| {
            hamming_encoder(chunk)
        })
        .collect();
    let modulated = modulation(&encoded, modulation_method);
    let transmitted = channel(modulated, channel_mode, alpha, beta);
    let demodulated = demodulation(transmitted, modulation_method);
    let output = demodulated
        .chunks(7)
        .flat_map(|chunk| {
            hamming_decoder(chunk)
        })
        .collect();
    String::from_utf8(output).unwrap()
}

fn trapezoidal_rule(y: &[f64], dt: f64) -> Vec<f64> {
    let mut result = Vec::with_capacity(y.len());
    result.push(0.0);
    y.windows(2)
        .fold(0.0, |acc, pair| {
            let new_acc = acc + (pair[0] + pair[1]) * 0.5 * dt;
            result.push(new_acc);
            new_acc
        });
    result
}

fn draw_graph(x_data: &[f64], y_data: &[f64], file_name: &str, x_label: &str, y_label: &str) -> Result<(), Box<dyn Error>> {
    let root_area = BitMapBackend::new(file_name, (2500, 1000)).into_drawing_area();
    root_area.fill(&WHITE)?;

    let mut x_min = *x_data.iter().min_by(|a, b| a.partial_cmp(b).unwrap()).unwrap();
    let mut x_max = *x_data.iter().max_by(|a, b| a.partial_cmp(b).unwrap()).unwrap();
    let mut y_min = *y_data.iter().min_by(|a, b| a.partial_cmp(b).unwrap()).unwrap();
    let mut y_max = *y_data.iter().max_by(|a, b| a.partial_cmp(b).unwrap()).unwrap();
    x_min -= x_max * 0.01;
    x_max *= 1.03;
    if y_min < 0.0 {
        y_min *= 1.03;
    } else {
        y_min *= 0.97;
    }
    y_max *= 1.01;

    let mut chart = ChartBuilder::on(&root_area)
        .margin(10)
        .x_label_area_size(50)
        .y_label_area_size(70)
        .build_cartesian_2d(x_min..x_max, y_min..y_max)?;

    chart.configure_mesh()
        .x_desc(x_label)
        .y_desc(y_label)
        .axis_desc_style(("sans-serif", 15).into_font())
        .draw()?;

    chart.draw_series(LineSeries::new(
        x_data.iter().cloned().zip(y_data.iter().cloned()),
        *&ShapeStyle::from(&BLUE.mix(0.5)).stroke_width(2)
    )).unwrap();

    root_area.present()?;
    Ok(())
}

fn draw_graph2(x_data: &[f64], y_data: &[f64], bits_message: &[u8], file_name: &str) -> Result<(), Box<dyn Error>> {
    let root_area = BitMapBackend::new(file_name, (2500, 1000)).into_drawing_area();
    root_area.fill(&WHITE)?;

    let x_min = *x_data.first().unwrap();
    let x_max = *x_data.last().unwrap();
    let y_min = *y_data.iter().min_by(|a, b| a.partial_cmp(b).unwrap()).unwrap();
    let y_max = *y_data.iter().max_by(|a, b| a.partial_cmp(b).unwrap()).unwrap();

    let mut chart = ChartBuilder::on(&root_area)
        .margin(10)
        .x_label_area_size(50)
        .y_label_area_size(70)
        .build_cartesian_2d(x_min..x_max, y_min..y_max)?;

    chart.configure_mesh()
        .x_desc("Time")
        .y_desc("Values")
        .axis_desc_style(("sans-serif", 15).into_font())
        .draw()?;

    chart.draw_series(LineSeries::new(
        x_data.iter().cloned().zip(y_data.iter().cloned()),
        *&ShapeStyle::from(&BLUE.mix(0.5)).stroke_width(2),
    ))?;

    let mut start_x = x_min;
    let mut current_value = bits_message[0];

    for (idx, &value) in bits_message.iter().enumerate() {
        let end_x = start_x + T_b;

        if idx == 0 || value != current_value {
            if idx > 0 {
                chart.draw_series(LineSeries::new(
                    vec![(start_x, y_min), (start_x, y_max)],
                    *&ShapeStyle::from(&ORANGE.mix(1.0)).stroke_width(2),
                ))?;
            }
            current_value = value;
        }

        let y_level = if value == b'1' { y_max } else { y_min };
        chart.draw_series(LineSeries::new(
            vec![(start_x, y_level), (end_x, y_level)],
            *&ShapeStyle::from(&ORANGE.mix(1.0)).stroke_width(2),
        ))?;

        start_x = end_x;
    }

    if bits_message.last().unwrap() == &b'1' {
        chart.draw_series(LineSeries::new(
            vec![(start_x, y_min), (start_x, y_max)],
            *&ShapeStyle::from(&ORANGE.mix(1.0)).stroke_width(2),
        ))?;
    }

    root_area.present()?;

    Ok(())
}

fn visualize_signals(input: &str, output: &str, file_name: &str) -> Result<(), Box<dyn Error>> {
    let root_area = BitMapBackend::new(file_name, (2500, 1000)).into_drawing_area();
    root_area.fill(&WHITE)?;

    let mut chart = ChartBuilder::on(&root_area)
        .margin(10)
        .x_label_area_size(50)
        .y_label_area_size(50)
        .build_cartesian_2d(0..input.len(), -1.0..1.0)?;

    chart.configure_mesh().draw()?;

    for (i, (in_char, out_char)) in input.chars().zip(output.chars()).enumerate() {
        if in_char == '1' {
            chart.draw_series(vec![Rectangle::new(
                [(i, 0.0), (i + 1, 1.0)],
                GREEN.filled(),
            )])?;
        }
        if out_char == '1' {
            chart.draw_series(vec![Rectangle::new(
                [(i, -1.0), (i + 1, 0.0)],
                YELLOW.filled(),
            )])?;
        }
    }

    chart.draw_series(std::iter::once(PathElement::new(
        vec![(0, 0.0), (0, 0.0)],
        GREEN.filled(),
    )))?.label("Input").legend(|(x, y)| Rectangle::new([(x, y - 20), (x + 40, y + 20)], GREEN.filled()));

    chart.draw_series(std::iter::once(PathElement::new(
        vec![(0, 0.0), (0, 0.0)],
        YELLOW.filled(),
    )))?.label("Output").legend(|(x, y)| Rectangle::new([(x, y - 20), (x + 40, y + 20)], YELLOW.filled()));

    chart.configure_series_labels()
        .border_style(&BLACK)
        .position(SeriesLabelPosition::UpperRight)
        .label_font(("sans-serif", 30))  // Increase the font size
        .legend_area_size(50) // Increase the legend area size to provide spacing
        .draw()?;

    Ok(())
}


fn calculate_ber(original: &str, received: &str) -> f64 {
    assert_eq!(original.len(), received.len());
    let errors = original.chars().zip(received.chars()).filter(|&(a, b)| a != b).count();
    errors as f64 / original.len() as f64
}

fn simulate_ber_over_alpha(file: &mut BufWriter<File>, alpha_range: std::ops::Range<f64>, step: f64, modulation_method: &str, channel_mode: u8) {
    let beta = 5.0;
    let mut alpha = alpha_range.start;
    while alpha < alpha_range.end {
        let output = system(message_bitstream, modulation_method, channel_mode, alpha, beta);
        let ber = calculate_ber(message_bitstream, &output);
        writeln!(file, "Alpha: {}, BER: {:.5}", alpha, ber).unwrap();
        alpha += step;
    }
}

fn simulate_ber_over_beta(file: &mut BufWriter<File>, beta_range: std::ops::Range<f64>, step: f64, modulation_method: &str, channel_mode: u8) {
    let alpha = 0.5;
    let mut beta = beta_range.start;
    while beta < beta_range.end {
        let output = system(message_bitstream, modulation_method, channel_mode, alpha, beta);
        let ber = calculate_ber(message_bitstream, &output);
        writeln!(file, "Beta: {}, BER: {:.5}", beta, ber).unwrap();
        beta += step;
    }
}

