use std::cmp::Ordering;
use std::f64::consts::PI;
use std::error::Error;
use std::fs::File;
use std::io::Write;

use plotters::prelude::*;
use num_complex::Complex;
use rustfft::FftPlanner;
const f_s: f64 = 500.0; // sampling frequency
const T_c: f64 = 1.0; // duration of the signal
const f_m: f64 = 29.0; // maximum message frequency
const f_n: f64 = 160.0; // maximum carrier wave frequency
const N: f64 = T_c * f_s; // number of samples


fn draw_graph(x_data: &[f64], y_data: &[f64], file_name: &str, x_label: &str, y_label: &str) -> Result<(), Box<dyn Error>> {
    let root_area = BitMapBackend::new(file_name, (3000, 1000)).into_drawing_area();
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
    )).unwrap()
        .label("smth");

    root_area.present()?;
    Ok(())
}

fn draw_graph2( x_data: &[f64], y_data: &[f64], y_data2: &[f64], file_name: &str) -> Result<(), Box<dyn Error>> {
    let root_area = BitMapBackend::new(file_name, (3000, 1000)).into_drawing_area();
    root_area.fill(&WHITE)?;

    let x_min = *x_data.iter().min_by(|a, b| a.partial_cmp(b).unwrap()).unwrap();
    let x_max = *x_data.iter().max_by(|a, b| a.partial_cmp(b).unwrap()).unwrap();
    let y_overall_min = y_data.iter().chain(y_data2.iter()).min_by(|a, b| a.partial_cmp(b).unwrap()).unwrap();
    let y_overall_max = y_data.iter().chain(y_data2.iter()).max_by(|a, b| a.partial_cmp(b).unwrap()).unwrap();

    let mut chart = ChartBuilder::on(&root_area)
        .margin(10)
        .x_label_area_size(50)
        .y_label_area_size(70)
        .build_cartesian_2d(x_min..x_max, *y_overall_min..*y_overall_max)?;

    chart.configure_mesh()
        .x_desc("Time")
        .y_desc("Values")
        .axis_desc_style(("sans-serif", 15).into_font())
        .draw()?;

    chart.draw_series(LineSeries::new(
        x_data.iter().cloned().zip(y_data.iter().cloned()),
        *&ShapeStyle::from(&BLUE.mix(0.5)).stroke_width(2)
    ))?.label("Modulated Signal")
        .legend(|(x, y)| PathElement::new(vec![(x, y), (x + 20, y)], &BLUE));

    chart.draw_series(LineSeries::new(
        x_data.iter().cloned().zip(y_data2.iter().cloned()),
        *&ShapeStyle::from(&RED.mix(0.5)).stroke_width(7)
    ))?.label("Message")
        .legend(|(x, y)| PathElement::new(vec![(x, y), (x + 20, y)], &RED));

    chart.configure_series_labels()
        .background_style(&WHITE.mix(0.8))
        .border_style(&BLACK)
        .position(SeriesLabelPosition::LowerRight)
        .draw()?;

    root_area.present()?;
    Ok(())
}

fn main() -> Result<(), Box<dyn Error>> {
    let tone = |t: &f64| -> f64 {(2.0 * PI * f_m * t).sin()};
    let timings: Vec<f64> = (0..N as usize).
        map(|n| n as f64 / f_s)
        .collect();
    let samples: Vec<f64> = timings
        .iter()
        .map(|t| tone(t))
        .collect();
    // draw_graph(&timings, &samples, "tone.png", "Time", "Amplitude")?;
    // zad 1
    let modulated_by_amplitude_fun = |timings: &Vec<f64>, samples: &Vec<f64>, k_A: f64| -> Vec<f64> {
        (0..N as usize)
            .map(|n| {
            (k_A * samples[n] + 1.0) * (2.0 * PI * f_n * timings[n]).cos()
        }).collect()
    };
    let modulated_by_phase_fun = |timings: &Vec<f64>, samples: &Vec<f64>, k_P: f64| -> Vec<f64> {
        (0..N as usize)
            .map(|n|{
            (2.0 * PI * f_n * timings[n] + k_P * samples[n]).cos()
        }).collect()
    };
    let modulated_by_freq_fun = |timings: &Vec<f64>, samples: &Vec<f64>, k_F: f64| -> Vec<f64> {
        (0..N as usize)
            .map(|n| {
            (2.0 * PI * f_n * timings[n] + k_F / f_m * samples[n]).cos()
        }).collect()
    };
    let frequency_scale: Vec<f64> = (0..(N / 2.0 - 1.0) as usize)
        .map(|k| k as f64 * f_s / N)
        .collect();

    let mut modulated_signals: Vec<Vec<f64>> = Vec::with_capacity(9);
    // a)
    let k_A: f64 = 0.5;
    let k_P: f64 = 0.1;
    let k_F: f64 = -0.1;
    modulated_signals.push(modulated_by_amplitude_fun(&timings, &samples, k_A));
    modulated_signals.push(modulated_by_phase_fun(&timings, &samples, k_P));
    modulated_signals.push(modulated_by_freq_fun(&timings, &samples, k_F));
    // b)
    let k_A = 5.0;
    let k_P = PI/2.0;
    let k_F = PI/3.0;
    modulated_signals.push(modulated_by_amplitude_fun(&timings, &samples, k_A));
    modulated_signals.push(modulated_by_phase_fun(&timings, &samples, k_P));
    modulated_signals.push(modulated_by_freq_fun(&timings, &samples, k_F));
    // c)
    let k_A = 22.2;
    let k_P = 2.5*PI;
    let k_F = 4.0*PI;
    modulated_signals.push(modulated_by_amplitude_fun(&timings, &samples, k_A));
    modulated_signals.push(modulated_by_phase_fun(&timings, &samples, k_P));
    modulated_signals.push(modulated_by_freq_fun(&timings, &samples, k_F));
    // let modulated_signals_names = vec!["signal_AM_a", "signal_PM_a", "signal_FM_a",
    //                                    "signal_AM_b", "signal_PM_b", "signal_FM_b",
    //                                    "signal_AM_c", "signal_PM_c", "signal_FM_c"];
    // let amplitude_spectrums_names = vec!["amplitude_spectrum_AM_a", "amplitude_spectrum_PM_a", "amplitude_spectrum_FM_a",
    //                                     "amplitude_spectrum_AM_b", "amplitude_spectrum_PM_b", "amplitude_spectrum_FM_b",
    //                                     "amplitude_spectrum_AM_c", "amplitude_spectrum_PM_c", "amplitude_spectrum_FM_c"];
    let names = vec!["za_a", "zp_a", "zf_a",
                     "za_b", "zp_b", "zf_b",
                     "za_c", "zp_c", "zf_c"];
    // zad 3
    let amplitude_spectrum_fun = |fft_result: Vec<Complex<f64>>| -> Vec<f64> {
        fft_result.
            iter()
            .take((N / 2.0 - 1.0) as usize)
            .map(|x| (x.re.powi(2) + x.im.powi(2)).sqrt()).collect()
    };
    let amplitude_decibel_fun = |amplitude_spectrum: &Vec<f64>| -> Vec<f64>{
        amplitude_spectrum
            .iter()
            .map(|&x| 20.0 * x.log10())
            .collect()
    };
    let mut planner = FftPlanner::new();
    let fft = planner.plan_fft_forward(N as usize);
    // zad 2 i 3
    for i in 0..=8 {
        // draw_graph(&timings, &modulated_signals[i], &format!("{}.png", names[i]), "Time", "Values")?;
        draw_graph2(&timings, &modulated_signals[i], &samples, &format!("{}.png", names[i]))?;
        let mut modulated_signal: Vec<Complex<f64>> = modulated_signals[i].iter()
            .map(|&x| Complex::new(x, 0.0))
            .collect();
        fft.process(&mut modulated_signal);
        let amplitude_spectrum = amplitude_spectrum_fun(modulated_signal);
        let amplitude_decibel: Vec<f64> = amplitude_decibel_fun(&amplitude_spectrum);
        // draw_graph(&frequency_scale, &amplitude_spectrum, &format!("{}_widmo.png", names[i]), "Frequency", "Amplitude")?;
        draw_graph(&frequency_scale, &amplitude_decibel, &format!("{}_widmo.png", names[i]), "Frequency", "dB")?;
    }
    // zad 4
    let interpolate = |x0: f64, y0: f64, x1: f64, y1: f64, target_y: f64| -> f64 {
        x0 + (x1 - x0) / (y1 - y0) * (target_y - y0)
    };
    let mut file = File::create("bandwidths.txt")?;
    writeln!(file, "{:<50} | {:<50}", "Using Amplitude spectrum", "Using dB spectrum")?;
    writeln!(file, "{} | {}", "-".repeat(50), "-".repeat(43))?;

    for i in 0..=8 {
        let mut modulated_signal: Vec<Complex<f64>> = modulated_signals[i].iter()
            .map(|&x| Complex::new(x, 0.0))
            .collect();
        fft.process(&mut modulated_signal);
        let amplitude_spectrum = amplitude_spectrum_fun(modulated_signal);
        let amplitude_decibel = amplitude_decibel_fun(&amplitude_spectrum);

        let max_index = amplitude_spectrum.iter()
            .enumerate()
            .max_by(|(_, a), (_, b)| a.partial_cmp(b).unwrap_or(Ordering::Equal))
            .map(|(index, _)| index)
            .unwrap();
        let max_amplitude = amplitude_spectrum[max_index];
        let max_db = amplitude_decibel[max_index];

        let find_frequency_for_db_drop = |spectrum: &[f64], db_drop: f64, is_db: bool| -> (f64, f64) {
            let target_level = if is_db {
                max_db - db_drop
            } else {
                max_amplitude / db_drop
            };

            let mut i = max_index;
            while i > 0 && spectrum[i] > target_level {
                i -= 1;
            }
            let mut min_freq = 0.0;
            if (i == 0 && spectrum[i] > target_level) || spectrum[i] == target_level {
                min_freq = frequency_scale[i];
            } else {
                min_freq = interpolate(frequency_scale[i], spectrum[i], frequency_scale[i + 1], spectrum[i + 1], target_level);
            }

            let mut j = max_index;
            while j < spectrum.len() - 1 && spectrum[j] > target_level {
                j += 1;
            }
            let mut max_freq = 0.0;
            if (j == spectrum.len() - 1 && spectrum[j] > target_level) || spectrum[j] == target_level{
                max_freq = frequency_scale[j];
            } else {
                max_freq = interpolate(frequency_scale[j - 1], spectrum[j - 1], frequency_scale[j], spectrum[j], target_level);
            }

            (min_freq, max_freq)
        };

        let (freq_min_3db_amp, freq_max_3db_amp) = find_frequency_for_db_drop(&amplitude_spectrum, 2.0_f64.sqrt(), false);
        let (freq_min_6db_amp, freq_max_6db_amp) = find_frequency_for_db_drop(&amplitude_spectrum, 2.0, false);
        let (freq_min_12db_amp, freq_max_12db_amp) = find_frequency_for_db_drop(&amplitude_spectrum, 4.0, false);

        let (freq_min_3db_db, freq_max_3db_db) = find_frequency_for_db_drop(&amplitude_decibel, 3.0, true);
        let (freq_min_6db_db, freq_max_6db_db) = find_frequency_for_db_drop(&amplitude_decibel, 6.0, true);
        let (freq_min_12db_db, freq_max_12db_db) = find_frequency_for_db_drop(&amplitude_decibel, 12.0, true);

        writeln!(file, "Signal: {}{}|", names[i], " ".repeat(39))?;
        writeln!(file, "3 dB:  {} Hz to {} Hz and equals {} Hz | {} Hz to {} Hz and equals {} Hz",
                 format(freq_min_3db_amp), format(freq_max_3db_amp), format(freq_max_3db_amp - freq_min_3db_amp),
                 format(freq_min_3db_db), format(freq_max_3db_db), format(freq_max_3db_db - freq_min_3db_db))?;
        writeln!(file, "6 dB:  {} Hz to {} Hz and equals {} Hz | {} Hz to {} Hz and equals {} Hz",
                 format(freq_min_6db_amp), format(freq_max_6db_amp), format(freq_max_6db_amp - freq_min_6db_amp),
                 format(freq_min_6db_db), format(freq_max_6db_db), format(freq_max_6db_db - freq_min_6db_db))?;
        writeln!(file, "12 dB: {} Hz to {} Hz and equals {} Hz | {} Hz to {} Hz and equals {} Hz",
                 format(freq_min_12db_amp), format(freq_max_12db_amp), format(freq_max_12db_amp - freq_min_12db_amp),
                 format(freq_min_12db_db), format(freq_max_12db_db), format(freq_max_12db_db - freq_min_12db_db))?;
        writeln!(file, "{}", "-".repeat(95))?;
    }
    // 0 3 6 // 1 4 7 // 2 5 8
    // printing all signals to compare them
    let carrier: Vec<f64> = (0..N as usize)
        .map(|n| (2.0 * PI * f_n * timings[n]).cos())
        .collect();
    println!("original message, {:?}", samples);
    println!("carrier signal, {:?}", carrier);
    // draw_graph(&timings, &carrier, "carrier.png", "Time", "Values")?;
    for i in 0..3 {
        println!("{}:, {:?}", names[i], modulated_signals[i]);
        println!("{}:, {:?}", names[i+3], modulated_signals[i+3]);
        println!("{}:, {:?}", names[i+6], modulated_signals[i+6]);
    }
    Ok(())
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