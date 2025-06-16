#![allow(unused)]
use egui::{Color32, CentralPanel, Stroke, Rect, vec2, NumExt};
use egui_plot::{Line, Plot, PlotPoints, Legend};
use eframe::{self, egui};
use plotters::prelude::*;
use plotters::drawing::IntoDrawingArea;
use std::error::Error;

const ANIM_DURATION: f64 = 10.0;

#[derive(PartialEq)]
enum PlotType { IvsTime, DiDtvsTime, Phase }
impl PlotType {
    fn as_str(&self) -> &'static str {
        match self {
            PlotType::IvsTime => "I(t)",
            PlotType::DiDtvsTime => "dI/dt(t)",
            PlotType::Phase => "Phase plot (dI/dt vs I)",
        }
    }
}

#[derive(PartialEq)]
enum Tab { Plots, Animation }

struct RLCApp {
    anim_start_time: Option<std::time::Instant>,
    anim_speed: f64,
    prev_tab: Tab,
    tab: Tab,
    r: f64, l: f64, c: f64,
    i0: f64, di_dt0: f64,
    dt: f64, t_max: f64, plot_type: PlotType,
    save_requested: bool, save_message: Option<String>,
    sim_time: f64, sim_speed: f64, anim_reset: bool,
    last_update: Option<std::time::Instant>,
}
impl Default for RLCApp {
    fn default() -> Self {
        Self {
            anim_start_time: None,
            anim_speed: 1.0,
            prev_tab: Tab::Plots,
            tab: Tab::Plots,
            r: 0.1, l: 1.5, c: 0.001, i0: 1.0, di_dt0: 1.0,
            dt: 0.0001, t_max: 1.0, plot_type: PlotType::IvsTime,
            save_requested: false, save_message: None,
            sim_time: 0.0, sim_speed: 200.0, anim_reset: false, last_update: None,
        }
    }
}

fn rlc_derivs(r: f64, l: f64, c: f64, _t: f64, state: &[f64; 2]) -> [f64; 2] {
    // state[0] = x1 = I
    // state[1] = x2 = dI/dt
    let x1 = state[0]; // current I
    let x2 = state[1]; // dI/dt

    // dI/dt = x2 (by definition)
    // d^2I/dt^2 = -R/L*x2 - 1/(L*C)*x1
    let dx1_dt = x2;
    let dx2_dt = -r / l * x2 - 1.0 / (l * c) * x1;
    [dx1_dt, dx2_dt]
}

fn rk4_step(
    r: f64,
    l: f64,
    c: f64,
    t: f64,
    state: &[f64; 2],
    dt: f64,
) -> [f64; 2] {
    // K1
    let k1 = rlc_derivs(r, l, c, t, state);

    // K2 state = state + dt/2 * k1
    let state_k2 = [
        state[0] + dt / 2.0 * k1[0],
        state[1] + dt / 2.0 * k1[1],
    ];
    let k2 = rlc_derivs(r, l, c, t + dt / 2.0, &state_k2);

    // K3 state = state + dt/2 * k2
    let state_k3 = [
        state[0] + dt / 2.0 * k2[0],
        state[1] + dt / 2.0 * k2[1],
    ];
    let k3 = rlc_derivs(r, l, c, t + dt / 2.0, &state_k3);

    // K4 state = state + dt * k3
    let state_k4 = [
        state[0] + dt * k3[0],
        state[1] + dt * k3[1],
    ];
    let k4 = rlc_derivs(r, l, c, t + dt, &state_k4);

    // weighted sum x+1 = dt / 6 * (K1 + 2K2 + 2K3 + K4)
    [
        state[0] + dt / 6.0 * (k1[0] + 2.0 * k2[0] + 2.0 * k3[0] + k4[0]),
        state[1] + dt / 6.0 * (k1[1] + 2.0 * k2[1] + 2.0 * k3[1] + k4[1]),
    ]
}

fn simulate_rlc(
    r: f64,
    l: f64,
    c: f64,
    i0: f64,
    di_dt0: f64,
    dt: f64,
    t_max: f64,
) -> (Vec<f64>, Vec<f64>, Vec<f64>) {
    let n = (t_max / dt) as usize;
    let mut state = [i0, di_dt0];
    let mut time = Vec::with_capacity(n);
    let mut i = Vec::with_capacity(n);
    let mut di_dt = Vec::with_capacity(n);

    let mut t = 0.0;
    for _ in 0..n {
        time.push(t);
        i.push(state[0]);
        di_dt.push(state[1]);
        state = rk4_step(r, l, c, t, &state, dt);
        t += dt;
    }
    (time, i, di_dt)
}


fn plot_series(
    x: &[f64],
    y: &[f64],
    base_filename: &str,
    y_label: &str,
    r: f64, l: f64, c: f64,
    i0: f64, di_dt0: f64,
    dt: f64, t_max: f64,
) -> Result<(), Box<dyn Error>> {
    let filename = format!(
        "{}_R{:.3}_L{:.3}_C{:.3}_I{:.2}_DI{:.2}_dt{:.4}_tmax{:.2}.png",
        base_filename, r, l, c, i0, di_dt0, dt, t_max
    );

    let root = BitMapBackend::new(&filename, (800, 600)).into_drawing_area();
    root.fill(&WHITE)?;

    let x_min = *x.first().unwrap();
    let x_max = *x.last().unwrap();
    let y_min = y.iter().cloned().fold(f64::INFINITY, f64::min);
    let y_max = y.iter().cloned().fold(f64::NEG_INFINITY, f64::max);

    let mut chart = ChartBuilder::on(&root)
        .margin(20)
        .caption(y_label, ("sans-serif", 30))
        .x_label_area_size(40)
        .y_label_area_size(60)
        .build_cartesian_2d(x_min..x_max, y_min..y_max)?;

    chart
        .configure_mesh()
        .x_desc(if y_label == "Current (A)" || y_label == "dI/dt (A/s)" {"Time [s]"} else {"Current I (A)"})
        .y_desc(y_label)
        .draw()?;

    chart.draw_series(LineSeries::new(
        x.iter().cloned().zip(y.iter().cloned()),
        &BLUE,
    ))?;

    root.present()?;
    println!("Result saved to {}", filename);

    Ok(())
}



fn draw_animated_rlc(
    painter: &egui::Painter,
    size: egui::Vec2,
    current_value: f64,
    t: f64,
) {
    let offset = egui::Pos2::new(0.0, 0.0);


    let mx = size.x * 0.12;
    let my = size.y * 0.23;


    let w = size.x - 2.0 * mx;
    let h = size.y - 2.0 * my;

    let a = offset + vec2(mx, my);
    let b = offset + vec2(mx + w * 0.4, my);
    let c = offset + vec2(mx + w, my);
    let d = offset + vec2(mx + w, my + h);
    let e = offset + vec2(mx, my + h);

    let path = [a, b, c, d, e, a];


    for win in path.windows(2) {
        painter.line_segment([win[0], win[1]], Stroke::new(3.0, Color32::GRAY));
    }


    let elem_w = w * 0.09;
    let elem_h = h * 0.25;

    painter.rect_filled(Rect::from_center_size(b, vec2(elem_w, elem_h)), 3.0, Color32::RED);
    painter.text(b, egui::Align2::CENTER_CENTER, "R", egui::FontId::proportional((elem_h * 0.7) as f32), Color32::WHITE);

    painter.rect_filled(Rect::from_center_size(c, vec2(elem_w, elem_h)), 3.0, Color32::BLUE);
    painter.text(c, egui::Align2::CENTER_CENTER, "L", egui::FontId::proportional((elem_h * 0.7) as f32), Color32::WHITE);

    painter.rect_filled(Rect::from_center_size(d, vec2(elem_w, elem_h)), 3.0, Color32::GREEN);
    painter.text(d, egui::Align2::CENTER_CENTER, "C", egui::FontId::proportional((elem_h * 0.7) as f32), Color32::BLACK);


    let n_dots = 16;
    let loop_len = {
        let mut len = 0.0;
        for win in path.windows(2) {
            len += win[0].distance(win[1]);
        }
        len
    };


    let speed = (w + h) * 0.18 * (current_value.tanh() as f32);

    for i in 0..n_dots {
        let base_phase = i as f32 / n_dots as f32;
        let mut phase = base_phase + (t as f32 * speed / loop_len as f32);
        phase %= 1.0;
        if phase < 0.0 { phase += 1.0; }

        let mut remaining = phase * loop_len;
        let mut pos = path[0];
        for win in path.windows(2) {
            let seg_len = win[0].distance(win[1]);
            if remaining <= seg_len {
                let frac = remaining / seg_len;
                pos = win[0].lerp(win[1], frac);
                break;
            }
            remaining -= seg_len;
        }
        painter.circle_filled(pos, elem_h * 0.18, Color32::YELLOW);
    }
}

impl eframe::App for RLCApp {
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        CentralPanel::default().show(ctx, |ui| {

            ui.horizontal(|ui| {
                if ui.selectable_label(self.tab == Tab::Plots, "Plots").clicked() { self.tab = Tab::Plots; }
                if ui.selectable_label(self.tab == Tab::Animation, "Animation").clicked() { self.tab = Tab::Animation; }
            });
            ui.separator();


            ui.horizontal(|ui| {
                ui.label("R (Ohms):");
                ui.add(egui::Slider::new(&mut self.r, 0.1..=10_000.0).logarithmic(true));
                ui.label("L (Henries):");
                ui.add(egui::Slider::new(&mut self.l, 0.000_001..=10.0).logarithmic(true));
                ui.label("C (Farads):");
                ui.add(egui::Slider::new(&mut self.c, 0.000_000_001..=0.01).logarithmic(true));
                ui.label("I(0):");
                ui.add(egui::Slider::new(&mut self.i0, -1.0..=1.0));
                ui.label("dI/dt(0):");
                ui.add(egui::Slider::new(&mut self.di_dt0, -10.0..=10.0));
            });

            match self.tab {
                Tab::Plots => {
                    ui.horizontal(|ui| {
                        ui.label("dt:");
                        ui.add(egui::Slider::new(&mut self.dt, 0.0001..=1.0));
                        ui.label("t_max:");
                        ui.add(egui::Slider::new(&mut self.t_max, 0.1..=10.0));
                        if ui.button("💾 Save plot").clicked() {
                            self.save_requested = true;
                        }
                    });
                    ui.horizontal(|ui| {
                        ui.label("Plot:");
                        egui::ComboBox::from_label("")
                            .selected_text(self.plot_type.as_str())
                            .show_ui(ui, |cb| {
                                cb.selectable_value(&mut self.plot_type, PlotType::IvsTime, "I(t)");
                                cb.selectable_value(&mut self.plot_type, PlotType::DiDtvsTime, "dI/dt(t)");
                                cb.selectable_value(&mut self.plot_type, PlotType::Phase, "Phase plot (dI/dt vs I)");
                            });
                    });

                    let (time, i, di_dt) = simulate_rlc(self.r, self.l, self.c, self.i0, self.di_dt0, self.dt, self.t_max);
                    let points: PlotPoints = match self.plot_type {
                        PlotType::IvsTime => time.iter().zip(i.iter()).map(|(&t, &v)| [t, v]).collect(),
                        PlotType::DiDtvsTime => time.iter().zip(di_dt.iter()).map(|(&t, &v)| [t, v]).collect(),
                        PlotType::Phase => i.iter().zip(di_dt.iter()).map(|(&i, &d)| [i, d]).collect(),
                    };
                    let (label, x_label, y_label) = match self.plot_type {
                        PlotType::IvsTime => ("I(t)", "Time (s)", "Current (A)"),
                        PlotType::DiDtvsTime => ("dI/dt(t)", "Time (s)", "dI/dt (A/s)"),
                        PlotType::Phase => ("Phase plot", "Current I (A)", "dI/dt (A/s)"),
                    };
                    Plot::new("plot")
                        .legend(Legend::default())
                        .x_axis_label(x_label)
                        .y_axis_label(y_label)
                        .show(ui, |plot_ui| {
                            plot_ui.line(Line::new(label, points));
                        });

                    if self.save_requested {
                        let fname = match self.plot_type {
                            PlotType::IvsTime => "current_vs_time.png",
                            PlotType::DiDtvsTime => "di_dt_vs_time.png",
                            PlotType::Phase => "phase_plot.png",
                        };
                        let result = match self.plot_type {
                            PlotType::IvsTime => plot_series(
                                &time, &i, "current_vs_time", y_label,
                                self.r, self.l, self.c, self.i0, self.di_dt0, self.dt, self.t_max
                            ),
                            PlotType::DiDtvsTime => plot_series(
                                &time, &di_dt, "di_dt_vs_time", y_label,
                                self.r, self.l, self.c, self.i0, self.di_dt0, self.dt, self.t_max
                            ),
                            PlotType::Phase => plot_series(
                                &i, &di_dt, "phase_plot", y_label,
                                self.r, self.l, self.c, self.i0, self.di_dt0, self.dt, self.t_max
                            ),
                        };
                        self.save_message = if result.is_ok() {
                            Some(format!("Plot saved as {fname}"))
                        } else {
                            Some(format!("Failed to save {fname}"))
                        };
                        self.save_requested = false;
                    }

                    if let Some(msg) = &self.save_message {
                        ui.label(msg);
                    }
                }
                Tab::Animation => {
                    ui.horizontal(|ui| {
                        ui.label("Speed:");
                        ui.add(egui::Slider::new(&mut self.anim_speed, 0.1..=5.0).logarithmic(true));
                        if ui.button("Reset").clicked() {
                            self.sim_time = 0.0;
                            self.anim_start_time = Some(std::time::Instant::now());
                        }
                    });

                    let now = std::time::Instant::now();
                    let dt_real = if let Some(last) = self.last_update {
                        (now - last).as_secs_f64()
                    } else { 0.0 };
                    self.last_update = Some(now);

                    let time_per_real_second = self.t_max / ANIM_DURATION * self.anim_speed;
                    if !self.anim_reset {
                        self.sim_time += dt_real * time_per_real_second;
                    } else {
                        self.anim_reset = false;
                    }

                    let mut state = [self.i0, self.di_dt0];
                    let mut t = 0.0;
                    let dt_anim = 0.001;
                    while t + dt_anim < self.sim_time {
                        state = rk4_step(self.r, self.l, self.c, t, &state, dt_anim);
                        t += dt_anim;
                    }

                    ui.add_space(10.0);

                    let available = ui.available_size();
                    let desired_size = egui::vec2(available.x, available.y).at_least(egui::vec2(800.0, 480.0));
                    let (response, painter) = ui.allocate_painter(desired_size, egui::Sense::hover());

                    draw_animated_rlc(&painter, desired_size, state[0], t);
                }
            }
        });
    }
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let native_options = eframe::NativeOptions::default();
    eframe::run_native(
        "RLC Circuit Simulator",
        native_options,
        Box::new(|_cc| Ok(Box::new(RLCApp::default()))),
    );
    Ok(())
}
