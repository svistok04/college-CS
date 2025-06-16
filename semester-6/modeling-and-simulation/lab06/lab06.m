clear all
close all
clc 

out = sim("atwood.slx");
x = out.x;
y = out.y;
r = out.r;

m1 = str2num(get_param("atwood/Subsystem", "m1"));
m2 = str2num(get_param("atwood/Subsystem", "m2"));
M = str2num(get_param("atwood/Subsystem", "M"));
R = str2num(get_param("atwood/Subsystem", "R"));

ltotal = 2 * max(r);

for i = 1:length(x)

    yc = -(ltotal - r(i));

    plot(x(i), y(i), 'b.', 'MarkerSize', 50 * m1); % kula
    hold on

    plot([M, x(i)], [0, y(i)], 'k-', 'LineWidth', 2); % lina od kuli

    plot(M, 0, 'b.', 'MarkerSize', 50 * M); % bloczek 1

    plot(-M, 0, 'b.', 'MarkerSize', 50 * M); % bloczek 2

    plot([-M, M], [0, 0], 'k-', 'LineWidth', 2); % lina miedzy blokami

    plot(-M, yc, 'b.', 'MarkerSize', 50 * m2); % ciezarek

    plot([-M, -M], [0, yc], 'k-', 'LineWidth', 2); % lina miedzy ciezarem a blokiem
    hold off

    axis([-ltotal, ltotal, -ltotal, ltotal])
    pause(2^(-5));
end


