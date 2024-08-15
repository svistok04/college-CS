use std::error::Error;
use std::f64::consts::PI;
use std::cmp::{Ordering, min};
use std::fs::File;
use std::io::{Write, BufWriter};

use num_complex::Complex;
use rustfft::FftPlanner;
use lerp::Lerp;
use plotters::prelude::*;

// zad 1
const message_bitstream: &str = "1001000110010111011001101100110111101011000100000101011111011111110010110110011001000100001";
const T_c: f64 = 1.0; // signal duration
const W: f64 = 10.0; // scaling factor for the maximum frequency
const f_s: f64 = 4.0 * f_n2; // sampling frequency
const f_n: f64 = W / T_b; // maximum signal frequency
const f_n1: f64 = (W + 1.0) / T_b; // maximum signal frequency for FSK
const f_n2: f64 = (W + 2.0) / T_b; // maximum signal frequency for FSK
const N: usize = (f_s * T_c) as usize; // number of samples
// const B: usize = message_bitstream.len(); // number of bits
const B: usize = 10;
const T_b: f64 = T_c / B as f64; // bit duration
const A_1: f64 = 1.0; // amplitude for 0
const A_2: f64 = 2.0; // amplitude for 1

fn draw_graph(x_data: &[f64], y_data: &[f64], file_name: &str, x_label: &str, y_label: &str) -> Result<(), Box<dyn Error>> {
    let root_area = BitMapBackend::new(file_name, (2500, 1000)).into_drawing_area();
    root_area.fill(&WHITE)?;

    let x_min = *x_data.iter().min_by(|a, b| a.partial_cmp(b).unwrap()).unwrap();
    let x_max = *x_data.iter().max_by(|a, b| a.partial_cmp(b).unwrap()).unwrap();
    let y_min = *y_data.iter().min_by(|a, b| a.partial_cmp(b).unwrap()).unwrap();
    let y_max = *y_data.iter().max_by(|a, b| a.partial_cmp(b).unwrap()).unwrap();

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

fn draw_graph2(x_data: &[f64], y_data: &[f64], y_colors: &[char], file_name: &str) -> Result<(), Box<dyn Error>> {
    let root_area = BitMapBackend::new(file_name, (2500, 1000)).into_drawing_area();
    root_area.fill(&WHITE)?;

    let x_min = *x_data.iter().min_by(|a, b| a.partial_cmp(b).unwrap()).unwrap();
    let x_max = *x_data.iter().max_by(|a, b| a.partial_cmp(b).unwrap()).unwrap();
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

    let green = GREEN.mix(0.1).filled();
    let red = RED.mix(0.1).filled();
    let default = WHITE.filled();

    for (index, &color) in y_colors.iter().enumerate() {
        let start_x = x_min + index as f64 * T_b;
        let end_x = start_x + T_b;
        let color_style = match color {
            '0' => &green,
            '1' => &red,
            _ => &default,
        };
        chart.draw_series(std::iter::once(Rectangle::new(
            [(start_x, y_min), (end_x, y_max)],
            *color_style,
        )))?;
    }

    chart.draw_series(LineSeries::new(
        x_data.iter().cloned().zip(y_data.iter().cloned()),
        *&ShapeStyle::from(&BLUE.mix(0.5)).stroke_width(2),
    ))?;

    chart.draw_series(vec![
        Circle::new((x_max + 1.0, y_max), 5, RED.filled()),
    ]).unwrap().label("1")
        .legend(|(x, y)| Circle::new((x + 10, y), 5, RED.filled()));

    chart.draw_series(vec![
        Circle::new((x_max + 1.0, y_max), 5, GREEN.filled()),
    ]).unwrap().label("0")
        .legend(|(x, y)| Circle::new((x + 10, y), 5, GREEN.filled()));


    chart.configure_series_labels()
        .background_style(&WHITE.mix(0.8))
        .border_style(&BLACK)
        .position(SeriesLabelPosition::LowerRight)
        .draw()?;

    root_area.present()?;
    Ok(())
}

fn main() -> Result<(), Box<dyn Error>> {
    // println!("{}", message_bitstream.len());
    let binary_representation = ascii_to_bitstream("transmisja");
    println!("{:?}", binary_representation);
    // zad 2
    let timings: Vec<f64> = (0..N)
        .map(|n| {
            n as f64 / f_s
        })
        .collect();
    let mut key_shiftings: Vec<Vec<f64>> = Vec::with_capacity(3);
    let names: Vec<&str> = vec!["za", "zp", "zf"];
    let step = (N / B) as f64;
    let file = File::create("ASK.txt")?;
    let mut writer = BufWriter::new(file);
    let ASK: Vec<f64> =  {
        (0..N)
            .map(|i| {
                let n = (i as f64 / step) as usize;
                if message_bitstream.chars().nth(n).unwrap() == '0' {
                    let res = A_1 * (2.0 * PI * f_n * timings[i]).sin();
                    writeln!(writer, "{}", res).unwrap();
                    res
                } else {
                    let res = A_2 * (2.0 * PI * f_n * timings[i]).sin();
                    writeln!(writer, "{}", res).unwrap();
                    res
                }
            })
            .collect()
    };

    let file = File::create("PSK.txt")?;
    let mut writer = BufWriter::new(file);
    let PSK: Vec<f64> = {
        (0..N)
            .map(|i| {
                let n = (i as f64 / step) as usize;
                if message_bitstream.chars().nth(n).unwrap()  == '0' {
                    let res = (2.0 * PI * f_n * timings[i]).sin();
                    writeln!(writer, "{}", res).unwrap();
                    res
                } else {
                    let res = (2.0 * PI * f_n * timings[i] + PI).sin();
                    writeln!(writer, "{}", res).unwrap();
                    res
                }
            })
            .collect()
    };

    let file = File::create("FSK.txt")?;
    let mut writer = BufWriter::new(file);
    let FSK: Vec<f64> = {
        (0..N)
            .map(|i| {
                let n = (i as f64 / step) as usize;
                if message_bitstream.chars().nth(n).unwrap()  == '0' {
                    let res = (2.0 * PI * f_n1 * timings[i]).sin();
                    writeln!(writer, "{}", res).unwrap();
                    res
                } else {
                    let res = (2.0 * PI * f_n2 * timings[i]).sin();
                    writeln!(writer, "{}", res).unwrap();
                    res
                }
            })
            .collect()
    };
    key_shiftings.push(ASK);
    key_shiftings.push(PSK);
    key_shiftings.push(FSK);
    let timings_message: Vec<f64> = (0..B)
        .map(|n| n as f64 * T_b)
        .collect();
    let chars: Vec<char> = message_bitstream.chars().take(B).collect();
    let numbers: Vec<f64> = chars.iter()
        .map(|&c| c.to_string().parse::<f64>().unwrap())
        .collect();
    draw_graph(&timings_message, &numbers, "message.png", "Time [s]", "Value")?;
    for i in 0..3 {
        draw_graph2(&timings, &key_shiftings[i], &chars, &format!("{}.png", &names[i]))?;
    }

    // zad 3
    let frequency_scale: Vec<f64> = (0..(N as f64/ 2.0 - 1.0) as usize)
        .map(|k| k as f64 * f_s / N as f64)
        .collect();

    let amplitude_spectrum_fun = |fft_result: Vec<Complex<f64>>| -> Vec<f64> {
        fft_result.
            iter()
            .take((N as f64 / 2.0 - 1.0) as usize)
            .map(|x| (x.re.powi(2) + x.im.powi(2)).sqrt()).collect()
    };
    let amplitude_decibel_fun = |amplitude_spectrum: &Vec<f64>| -> Vec<f64>{
        amplitude_spectrum
            .iter()
            .map(|&x| 20.0 * x.log10())
            .collect()
    };
    let mut decibel_spectrums: Vec<Vec<f64>> = Vec::with_capacity(3);
    let mut planner = FftPlanner::new();
    let fft = planner.plan_fft_forward(N);
    for i in 0..3 {
        let mut signal: Vec<Complex<f64>> = key_shiftings[i]
            .iter()
            .map(|&x| Complex::new(x, 0.0))
            .collect();
        fft.process(&mut signal);
        let amplitude_spectrum = amplitude_spectrum_fun(signal);
        let amplitude_decibel = amplitude_decibel_fun(&amplitude_spectrum);
        decibel_spectrums.push(amplitude_decibel);
        draw_graph(&frequency_scale, &decibel_spectrums[i], &format!("{}_widmo.png", &names[i]), "Frequency [Hz]", "Amplitude [dB]")?;
    }
    // zad 4
    let file = File::create("bandwidths.txt")?;
    let mut writer = BufWriter::new(file);
    for i in 0..3 {
        let decibel_spectrum = &decibel_spectrums[i];
        let max_index = decibel_spectrum.iter()
            .enumerate()
            .max_by(|(_, a), (_, b)| a.partial_cmp(b).unwrap_or(Ordering::Equal))
            .map(|(index, _)| index)
            .unwrap();
        let max_db = decibel_spectrum[max_index];
        let find_frequency_for_db_drop = |db_drop: f64| -> (f64, f64) {
            let target_level = max_db - db_drop;
            let mut i = max_index;
            while i > 0 && decibel_spectrum[i] > target_level {
                i -= 1;
            }
            let min_freq = if (i == 0 && decibel_spectrum[i] > target_level) || decibel_spectrum[i] == target_level {
                frequency_scale[i]
            } else {
                frequency_scale[i].lerp(frequency_scale[i + 1], (target_level - decibel_spectrum[i]) / (decibel_spectrum[i + 1] - decibel_spectrum[i]))
            };

            let mut j = max_index;
            while j < decibel_spectrum.len() - 1 && decibel_spectrum[j] > target_level {
                j += 1;
            }
            let max_freq = if (j == decibel_spectrum.len() - 1 && decibel_spectrum[j] > target_level) || decibel_spectrum[j] == target_level {
                frequency_scale[j]
            } else {
                frequency_scale[j - 1].lerp(frequency_scale[j], (target_level - decibel_spectrum[j - 1]) / (decibel_spectrum[j] - decibel_spectrum[j - 1]))
            };
            (min_freq, max_freq)
        };
        let (freq_min_3db, freq_max_3db) = find_frequency_for_db_drop(3.0);
        let (freq_min_6db, freq_max_6db) = find_frequency_for_db_drop(6.0);
        let (freq_min_12db, freq_max_12db) = find_frequency_for_db_drop(12.0);

        writeln!(writer, "Signal: {}", names[i])?;
        writeln!(writer, "3dB: {:.4} Hz to {:.4} Hz and equals {:.4} Hz", freq_min_3db, freq_max_3db, freq_max_3db - freq_min_3db)?;
        writeln!(writer, "6dB: {:.4} Hz to {:.4} Hz and equals {:.4} Hz", freq_min_6db, freq_max_6db, freq_max_6db - freq_min_6db)?;
        writeln!(writer, "12dB: {:.4} Hz to {:.4} Hz and equals {:.4} Hz", freq_min_12db, freq_max_12db, freq_max_12db - freq_min_12db)?;
    }

    let file = File::create("signal.txt")?;
    let mut writer = BufWriter::new(file);
    let signal = timings
        .iter()
        .map(|t| (2.0 * PI * f_n * t).sin())
        .collect::<Vec<f64>>();
    for val in &signal {
        writeln!(writer, "{}", val)?;
    }

    let file = File::create("signal1.txt")?;
    let mut writer = BufWriter::new(file);
    let signal1 = timings
        .iter()
        .map(|t| (2.0 * PI * f_n1 * t).sin())
        .collect::<Vec<f64>>();
    for val in &signal1 {
        writeln!(writer, "{}", val)?;
    }

    let file = File::create("signal2.txt")?;
    let mut writer = BufWriter::new(file);
    let signal2 = timings
        .iter()
        .map(|t| (2.0 * PI * f_n2 * t).sin())
        .collect::<Vec<f64>>();
    for val in &signal2 {
        writeln!(writer, "{}", val)?;
    }
    draw_graph(&timings, &signal, "signal.png", "Time [s]", "Values")?;
    draw_graph(&timings, &signal1, "signal1.png", "Time [s]", "Values")?;
    draw_graph(&timings, &signal2, "signal2.png", "Time [s]", "Values")?;

    Ok(())
}

fn ascii_to_bitstream(text: &str) -> String {
    text.chars()
        .filter(|&c| c as u32 >= 32 && c as u32 <= 127)
        .map(|c| format!("{:07b}", c as u8))
        .collect()
}

fn format(num: f64) -> String {
    let num_int_len = if num == 0.0 {
        1
    } else {
        num.log10().abs().floor() as usize + 1
    };

    let decimal_places = 5 - num_int_len;
    if decimal_places > 0 {
        format!("{:.*}", decimal_places, num)
    } else {
        format!("{:.0}", num)
    }
}