use std::f64::consts::PI;
use std::time::Instant;
use std::error::Error;
use std::fs::File;
use std::io::{BufWriter, Write};

use num_complex::Complex;
use plotters::prelude::*;
use rustfft::FftPlanner;


const i: Complex<f64> = Complex::new(0.0, 1.0);

const Tc: f64 = 1.0;
const f: f64 = 60.0;
const fs: f64 = 150.0;
const N: usize = (Tc * fs) as usize;
const phi: f64 = PI / 2.0;

fn draw_graph(x_data: &[f64], y_data: &[f64], path: &str) -> Result<(), Box<dyn Error>> {
    let root_area = BitMapBackend::new(path, (1920, 1080)).into_drawing_area();
    root_area.fill(&WHITE)?;

    let x_min = *x_data.iter().min_by(|a, b| a.partial_cmp(b).unwrap()).unwrap();
    let x_max = *x_data.iter().max_by(|a, b| a.partial_cmp(b).unwrap()).unwrap();
    let y_min = *y_data.iter().min_by(|a, b| a.partial_cmp(b).unwrap()).unwrap();
    let y_max = *y_data.iter().max_by(|a, b| a.partial_cmp(b).unwrap()).unwrap();

    let mut chart = ChartBuilder::on(&root_area)
        .margin(10) // You can increase margin size here
        .x_label_area_size(50)
        .y_label_area_size(70)
        .build_cartesian_2d(x_min..x_max, y_min..y_max)?;

    chart.configure_mesh()
        .x_desc("Frequency (Hz)")
        .y_desc("Amplitude (dB)")
        .axis_desc_style(("sans-serif", 15).into_font())
        .draw()?;

    chart.draw_series(LineSeries::new(
        x_data.iter().cloned().zip(y_data.iter().cloned()),
        *&ShapeStyle::from(&BLUE.mix(0.5)).stroke_width(2) // Lighter color and same stroke width
    )).unwrap()
        .label("Amplitude");

    root_area.present()?;
    Ok(())
}

fn main() -> Result<(), Box<dyn Error>> {
    let plots_names = ["x", "y", "z", "v", "u", "b1", "b2", "b3"];
    let mut samplings_vec: Vec<Vec<f64>> = Vec::with_capacity(8);
    let timings: Vec<f64> = (0..N)
        .map(|n| n as f64 / fs)
        .collect();

    let x: Vec<f64> = timings.iter()
        .map(|&t| (2.0 * PI * f * t + phi).sin())
        .collect();
    samplings_vec.push(x.clone());
    let y: Vec<f64> = (0..N)
        .map(|n| {
            2.0 * x[n].powi(2) + 12.0 * timings[n].cos()
        })
        .collect();
    samplings_vec.push(y.clone());
    let z: Vec<f64> = (0..N)
        .map(|n| {
            (2.0 * PI * 7.0 * timings[n]).sin() * x[n] - 0.2 * (y[n].abs() + PI).log10()
        })
        .collect();
    samplings_vec.push(z.clone());
    let v: Vec<f64> = (0..N).
        map(|n| {
            (y[n] * y[n] * z[n]).abs().sqrt() - 1.8 * (0.4 * timings[n] * z[n] * x[n]).sin()
        })
        .collect();
    samplings_vec.push(v);
    let u = |t: f64| -> f64 {
        match t {
            t if t >= 0.0 && t < 0.5 => t * (t.sqrt() + 0.7 * (22.0 * PI * t * t.powi(2).cos()).sin()),
            t if t >= 0.5 && t < 1.3 => (t + 1.0).log10() * (20.0 * t.powi(3).sin()).abs() - 0.4,
            t if t >= 1.3 && t < 2.2 => (t.powi(2) + 1.0) * (2.0 * PI * t * (4.0 * t).cos()).sin(),
            t if t >= 2.2 && t < 2.7 => 0.5 * (20.0 * PI * t * (t / 3.0 + 2.3)).sin(),
            _ => 0.0,
        }
    };
    let u: Vec<f64> = timings.iter()
        .map(|&t| {
            u(t)
        })
        .collect();
    samplings_vec.push(u);
    let mut bks: [Vec<f64>; 3] = [Vec::with_capacity(N), Vec::with_capacity(N), Vec::with_capacity(N)];
    let hs = [1, 2, 22];
    for (j, &h) in hs.iter().enumerate() {
        let bk = |t: f64| -> f64 {
            (1..=h).fold(0.0, |acc, h_current| {
                acc + (h_current as f64 * PI * t).sin() /
                    (2.0 + (2.0 * h_current as f64 * PI * t).cos())
            })
        };
        for n in 0..N {
            let t = n as f64 / fs;
            bks[j].push(bk(t));
        }
    }
    samplings_vec.push(bks[0].clone());
    samplings_vec.push(bks[1].clone());
    samplings_vec.push(bks[2].clone());
    // cw. 1
    let dft_fun = |samplings: &Vec<f64>| -> Vec<Complex<f64>> {
        let size = samplings.len();
        (0..size)
            .map(|k| {
                (0..size).fold(Complex::new(0.0, 0.0), |acc, n| {
                    acc + samplings[n] * (-2.0 * PI * n as f64 * k as f64 / size as f64 * i).exp()
                })
            })
            .collect()
    };
    // cw. 2
    let amplitude_spectrum_fun = |dft_result: &Vec<Complex<f64>>| -> Vec<f64> {
        dft_result
            .iter()
            .map(|&x| (x.re.powi(2) + x.im.powi(2)).sqrt())
            .collect()
    };
    let amplitude_decibel_fun = |amplitude_spectrum: &Vec<f64>| {
        amplitude_spectrum
            .iter().take(amplitude_spectrum.len() / 2 - 1)
            .map(|&x| 20.0 * x.log10())
            .collect()
    };
    let frequency_scale: Vec<f64> = (0..N/2-1)
        .map(|k| k as f64 * fs / N as f64)
        .collect();
    let mut file = File::create("timings_table.txt")?;
    writeln!(file, "Group    | DFT           | FFT        ")?;
    writeln!(file, "---------|---------------|---------------")?;
    let mut total_dft = 0.0;
    let mut total_fft = 0.0;
    let mut planner = FftPlanner::new();
    let fft = planner.plan_fft_forward(N);
    for j in (0..samplings_vec.len()) {
        let start = Instant::now();
        let dft_result = dft_fun(&samplings_vec[j].clone());
        let elapsed_dft = start.elapsed().as_nanos() as f64 / 1_000_000.0;
        let mut samples: Vec<Complex<f64>> = samplings_vec[j].iter()
            .map(|&x| Complex::new(x, 0.0))
            .collect();
        let start = Instant::now();
        fft.process(&mut samples);
        let elapsed_fft = start.elapsed().as_nanos() as f64 / 1_000_000.0;
        let amplitude_spectrum: Vec<f64> = amplitude_spectrum_fun(&dft_result);
        let amplitude_decibel: Vec<f64> = amplitude_decibel_fun(&amplitude_spectrum);
        // draw_graph(&timings, &samplings_vec[j], &format!("{}.png", plots_names[j]))?;
        draw_graph(&frequency_scale, &amplitude_decibel, &format!("{}.png", plots_names[j]))?;
        writeln!(file, "{:<8} | {:>10.6} ms | {:>8.6} ms", plots_names[j], elapsed_dft, elapsed_fft)?;
        total_dft += elapsed_dft;
        total_fft += elapsed_fft;
    }
    writeln!(file, "---------|---------------|---------------")?;
    writeln!(file, "{:<8} | {:>10.6} ms | {:>8.6} ms", "All", total_dft, total_fft)?;
    Ok(())
}
