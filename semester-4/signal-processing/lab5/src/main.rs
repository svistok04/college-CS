use std::error::Error;
use std::f64::consts::PI;
use std::cmp::{Ordering, min};
use std::fs::File;
use std::io::{Write, BufWriter};

use plotters::prelude::*;
use plotters::style::full_palette::ORANGE;

const message_bitstream: &str = "1001000110010111011001101100110111101011000100000101011111011111110010110110011001000100001";
const T_c: f64 = 1.0; // signal duration
const W: f64 = 6.0; // scaling factor for the maximum frequency
const f_s: f64 = 3.0 * f_n2; // sampling frequency
const f_n: f64 = W / T_b; // maximum signal frequency
const f_n1: f64 = (W + 1.0) / T_b; // maximum signal frequency for FSK
const f_n2: f64 = (W + 2.0) / T_b; // maximum signal frequency for FSK
const N: usize = (f_s * T_c) as usize; // number of samples
// const B: usize = message_bitstream.len(); // number of bits
const B: usize = 2;
const T_b: f64 = T_c / B as f64; // bit duration
const A_1: f64 = 1.0; // amplitude for 0
const A_2: f64 = 2.0; // amplitude for 1
const A_r: f64 = 1.0;

fn main() {
    // modulations
    let timings: Vec<f64> = (0..N)
        .map(|n| {
            n as f64 / f_s
        })
        .collect();
    let step = (N / B) as f64;
    let ASK: Vec<f64> =  {
        (0..N)
            .map(|i| {
                let n = (i as f64 / step) as usize;
                if message_bitstream.chars().nth(n).unwrap() == '0' {
                    A_1 * (2.0 * PI * f_n * timings[i]).sin()
                } else {
                    A_2 * (2.0 * PI * f_n * timings[i]).sin()
                }
            })
            .collect()
    };
    let PSK: Vec<f64> = {
        (0..N)
            .map(|i| {
                let n = (i as f64 / step) as usize;
                if message_bitstream.chars().nth(n).unwrap()  == '0' {
                    (2.0 * PI * f_n * timings[i]).sin()
                } else {
                    (2.0 * PI * f_n * timings[i] + PI).sin()
                }
            })
            .collect()
    };
    let FSK: Vec<f64> = {
        (0..N)
            .map(|i| {
                let n = (i as f64 / step) as usize;
                if message_bitstream.chars().nth(n).unwrap()  == '0' {
                    (2.0 * PI * f_n1 * timings[i]).sin()
                } else {

                    (2.0 * PI * f_n2 * timings[i]).sin()
                }
            })
            .collect()
    };
    // demodulations
    // ask
    let dt = 1.0 / f_s;
    let x: Vec<f64> = (0..N)
        .map(|n| {
            ASK[n] * (2.0 * PI * f_n * timings[n]).sin()
        })
        .collect();
    let p: Vec<f64> = x.chunks(N / B ).flat_map(|chunk| {
        trapezoidal_rule(chunk, dt)
    }).collect();
    let mut max_mean = 0.0;
    let h = p.chunks(N / B)
        .map(|chunk| {
            let mean: f64 = chunk.iter().sum::<f64>() / chunk.len() as f64;
            if mean > max_mean {
                max_mean = mean;
            }
            max_mean
        })
        .last()
        .unwrap_or(0.0);
    println!("h {:?}", h);
    let c: Vec<char> = p.chunks(N / B)
        .map(|chunk| {
            let last = chunk[chunk.len() - 1];
            if last > h {
                '1'
            } else {
                '0'
            }
        })
        .collect();
    draw_graph(&timings, &ASK, "ask_z.png", "Time", "Values").unwrap();
    draw_graph(&timings, &x, "ask_x.png", "Time", "Values").unwrap();
    draw_graph(&timings, &p, "ask_p.png", "Time", "Values").unwrap();
    draw_graph2(&timings, &ASK, &c, "porownanie_ask.png").unwrap();
    println!("ask c {:?}", c);
    // psk
    let x: Vec<f64> = (0..N)
        .map(|n| {
            PSK[n] * (2.0 * PI * f_n * timings[n]).sin()
        })
        .collect();
    let p: Vec<f64> = x.chunks(N / B ).flat_map(|chunk| {
        trapezoidal_rule(chunk, dt)
    }).collect();
    let c: Vec<char> = p.chunks(N / B)
        .map(|chunk| {
            let sum: f64 = chunk.iter().sum();
            let mean = sum / chunk.len() as f64;
            if mean < 0.0 {
                '1'
            } else {
                '0'
            }
        })
        .collect();
    draw_graph(&timings, &PSK, "psk_z.png", "Time", "Values").unwrap();
    draw_graph(&timings, &x, "psk_x.png", "Time", "Values").unwrap();
    draw_graph(&timings, &p, "psk_p.png", "Time", "Values").unwrap();
    draw_graph2(&timings, &PSK, &c, "porownanie_psk.png").unwrap();
    println!("psk c {:?}", c);
    // fsk
    let x_1: Vec<f64> = (0..N)
        .map(|n| {
            FSK[n] * (2.0 * PI * f_n1 * timings[n]).sin()
        })
        .collect();
    let x_2: Vec<f64> = (0..N)
        .map(|n| {
            FSK[n] * (2.0 * PI * f_n2 * timings[n]).sin()
        })
        .collect();
    let p_1: Vec<f64> = x_1.chunks(N / B ).flat_map(|chunk| {
        trapezoidal_rule(chunk, dt)
    }).collect();
    let p_2: Vec<f64> = x_2.chunks(N / B ).flat_map(|chunk| {
        trapezoidal_rule(chunk, dt)
    }).collect();
    let p: Vec<f64> = p_1.iter().zip(p_2.iter()).map(|(x, y)| {
        -x + y
    }).collect();
    let c = p.chunks(N / B)
        .map(|chunk| {
        let sum: f64 = chunk.iter().sum();
        let mean = sum / chunk.len() as f64;
        if mean > 0.0 {
            '1'
        } else {
            '0'
        }
    }).collect::<Vec<char>>();
    draw_graph(&timings, &FSK, "fsk_z.png", "Time", "Values").unwrap();
    draw_graph(&timings, &x_1, "fsk_x1.png", "Time", "Values").unwrap();
    draw_graph(&timings, &x_2, "fsk_x2.png", "Time", "Values").unwrap();
    draw_graph(&timings, &p_1, "fsk_p1.png", "Time", "Values").unwrap();
    draw_graph(&timings, &p_2, "fsk_p2.png", "Time", "Values").unwrap();
    draw_graph(&timings, &p, "fsk_p.png", "Time", "Values").unwrap();
    draw_graph2(&timings, &FSK, &c, "porownanie_fsk.png").unwrap();
    println!("fsk c {:?}", c);
    println!("orig {:?}", message_bitstream.chars().take(B).collect::<Vec<char>>());
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

fn draw_graph2(x_data: &[f64], y_data: &[f64], bits_message: &[char], file_name: &str) -> Result<(), Box<dyn Error>> {
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

        let y_level = if value == '1' { y_max } else { y_min };
        chart.draw_series(LineSeries::new(
            vec![(start_x, y_level), (end_x, y_level)],
            *&ShapeStyle::from(&ORANGE.mix(1.0)).stroke_width(2),
        ))?;

        start_x = end_x;
    }

    if bits_message.last().unwrap() == &'1' {
        chart.draw_series(LineSeries::new(
            vec![(start_x, y_min), (start_x, y_max)],
            *&ShapeStyle::from(&ORANGE.mix(1.0)).stroke_width(2),
        ))?;
    }

    root_area.present()?;

    Ok(())
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