use plotters::prelude::*;
use std::error::Error;

const Tc: i32 = 8; // częstotliwość sygnału
const Fs: i32 = 16; // częstotliwość próbkowania
const N: usize = (Tc * Fs) as usize;

fn draw_graph(data: &[(f64, f64)], path: &str) -> Result<(), Box<dyn Error>> {
    let root = BitMapBackend::new(path, (640, 480)).into_drawing_area();
    root.fill(&WHITE)?;

    let min_x = data.iter().min_by(|a, b| a.0.partial_cmp(&b.0).unwrap()).unwrap().0;
    let max_x = data.iter().max_by(|a, b| a.0.partial_cmp(&b.0).unwrap()).unwrap().0;
    let min_y = 0.0;
    let max_y = data.iter().max_by(|a, b| a.1.partial_cmp(&b.1).unwrap()).unwrap().1;

    let mut chart = ChartBuilder::on(&root)
        .margin(5)
        .x_label_area_size(30)
        .y_label_area_size(30)
        .build_cartesian_2d(min_x..max_x, min_y..(max_y + max_y * 0.1))?;

    chart.configure_mesh().draw()?;

    chart.draw_series(LineSeries::new(
        data.iter().map(|(x, y)| (*x, *y)), &RED,
    ))?;

    root.present()?;
    Ok(())
}

fn main() -> Result<(), Box<dyn Error>> {
    let mut arr: Vec<(f64, f64)> = Vec::with_capacity(N);
    // let mut arr: [f64; N] = [0.0; N];
    let f = |x: f64| -> f64 {(x).powf(1.58)};
    for n in 0..N {
        let t: f64 = n as f64 / Fs as f64;
        let w = f(t);
        arr.push((t, w))
    }
    for &e in arr.iter() {
        println!("{:?}", e);
    }
    draw_graph(&arr, "f.png")?;
    Ok(())
}
