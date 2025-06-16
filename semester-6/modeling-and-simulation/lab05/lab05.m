clear all
close all
clc

out = sim('spring_pendulum.slx');
r = out.r;
theta = out.theta;
L = str2num(get_param("spring_pendulum/Subsystem", "l"));
m = str2num(get_param("spring_pendulum/Subsystem", "m"));

L_max = (max(r) + L) + 0.5;

for i = 1:length(r)
    x = -(L + r(i)) * sin(theta(i));
    y = -(L + r(i)) * cos(theta(i));

    plot(x, y, 'b.', 'MarkerSize', 5*m);
    hold on
    [xs, ys] = generate_spring(L, r(i), theta(i), 0, 0);
    plot(xs, ys, 'LineWidth', 2);
    hold off
    axis([-L_max, L_max, -L_max, L_max]);
    pause(2^-6)
end