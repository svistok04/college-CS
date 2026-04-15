use std::f64::consts::PI;
use num_complex::Complex;

fn main() {
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
}