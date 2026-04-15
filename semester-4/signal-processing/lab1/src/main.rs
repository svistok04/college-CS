use std::f64::consts::PI;
use plotters::prelude::*;
use std::error::Error;
fn draw_graph(results: &Vec<(f64, f64)>, path: &str) -> Result<(), Box<dyn Error>> {
    let root_area = BitMapBackend::new(path, (640, 480)).into_drawing_area();
    root_area.fill(&WHITE)?;

    let x_min = results.iter().map(|x| x.0).fold(f64::INFINITY, f64::min);
    let x_max = results.iter().map(|x| x.0).fold(f64::NEG_INFINITY, f64::max);
    let y_min = results.iter().map(|x| x.1).fold(f64::INFINITY, f64::min);
    let y_max = results.iter().map(|x| x.1).fold(f64::NEG_INFINITY, f64::max);

    let mut chart = ChartBuilder::on(&root_area)
        .margin(5)
        .x_label_area_size(30)
        .y_label_area_size(30)
        .build_cartesian_2d(x_min..x_max, y_min..y_max)?;

    chart.configure_mesh().draw()?;

    chart.draw_series(LineSeries::new(
        results.iter().map(|&(x, y)| (x, y)),
        &BLUE,
    ))?;
    root_area.present()?;
    Ok(())
}

fn main() -> Result<(), Box<dyn Error>> {
    const Tc: f64 = 1.0;
    const f: f64 = 4000.0;
    const phi: f64 = PI / 2.0;
    let mut fs: f64 = 8000.0;
    const N: usize = (Tc * fs) as usize;
    // cw 1 funckaj nr. 1
    let x = |t: f64| -> f64 { (2.0 * PI * f * t + phi).cos() * (2.5 * t.powf(0.2) * PI).cos() };
    let mut results1: Vec<(f64, f64)> = Vec::with_capacity(N);
    for n in 0..N {
        let t = n as f64 / fs;
        results1.push((t, x(t)));
    }
    draw_graph(&results1, "cw1.png")?;
    // for &e in results1.iter() {
    //     println!("{:?}", e);
    // }
    // cw 2 funkcje nr. 11
    let mut results21: Vec<(f64, f64)> = Vec::with_capacity(N);
    let mut results22: Vec<(f64, f64)> = Vec::with_capacity(N);
    let mut results23: Vec<(f64, f64)> = Vec::with_capacity(N);
    let y = |t: f64| {2.0 * x(t).powi(2) + 12.0 * t.cos()};
    let z = |t: f64| -> f64 {y(t) * ((0.2 * PI * t).sin()*(x(t) / 5.0).abs())};
    let v= |t: f64| -> f64 {x(t).abs().sqrt() * (0.5 * y(t)).cos() + z(t)};
    for n in 0..N {
        let t = n as f64 / fs;
        results21.push((t, y(t)));
        results22.push((t, z(t)));
        results23.push((t, v(t)));
    }
    draw_graph(&results21, "cw21.png")?;
    draw_graph(&results22, "cw22.png")?;
    draw_graph(&results23, "cw23.png")?;

    // cw 3, funkcja nr. 5
    let u = |t: f64| -> f64 {
        match t {
            t if t >= 0.0 && t < 0.5 => t * (t.sqrt() + 0.7 * (22.0 * PI * t * t.powi(2).cos()).sin()),
            t if t >= 0.5 && t < 1.3 => (t + 1.0).log10() * (20.0 * t.powi(3).sin()).abs() - 0.4,
            t if t >= 1.3 && t < 2.2 => (t.powi(2) + 1.0) * (2.0 * PI * t * (4.0 * t).cos()).sin(),
            t if t >= 2.2 && t < 2.7 => 0.5 * (20.0 * PI * t * (t / 3.0 + 2.3)).sin(),
            _ => 0.0,
        }
    };
    let mut results3: Vec<(f64, f64)> = Vec::with_capacity(N);
    for n in 0..N {
        let t = n as f64 / fs;
        results3.push((t, u(t)));
    }
    draw_graph(&results3, "cw3.png")?;

    // cw. 4, funkcja nr. 6
    fs = 22050.0;
    let hs = [1, 2, 22];
    // let mut results4: Vec<Vec<(f64, f64)>> = vec![Vec::with_capacity(N); 3];
    let mut results4: [Vec<(f64, f64)>; 3] = [Vec::with_capacity(N), Vec::with_capacity(N), Vec::with_capacity(N)];
    for (i, &h) in hs.iter().enumerate() {
        let bk = |t: f64| -> f64 {
            (1..=h).fold(0.0, |acc, h_current| {
                acc + (h_current as f64 * PI * t).sin() /
                    (2.0 + (2.0 * h_current as f64 * PI * t).cos())
            })
        };
        for n in 0..N {
            let t = n as f64 / fs;
            let result = bk(t);
            results4[i].push((t, result));
        }
    }
    draw_graph(&results4[0], "cw41.png")?;
    draw_graph(&results4[1], "cw42.png")?;
    draw_graph(&results4[2], "cw43.png")?;
    Ok(())
}
