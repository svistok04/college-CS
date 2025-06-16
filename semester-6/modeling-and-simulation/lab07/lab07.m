clear all
close all
clc 

out = sim("double_pendulum.slx");
phi1 = out.phi1;
phi2 = out.phi2;
m1 = str2num(get_param("double_pendulum/Subsystem", "m1"));
m2 = str2num(get_param("double_pendulum/Subsystem", "m2"));
l1 = str2num(get_param("double_pendulum/Subsystem", "l1"));
l2 = str2num(get_param("double_pendulum/Subsystem", "l2"));

L = l1 + l2;

for i = 1:length(phi1)
    x1 = -l1 * sin(phi1(i));
    y1 = -l1 * cos(phi1(i));
    x2 = -l2 * sin(phi2(i)) + x1;
    y2 = -l2 * cos(phi2(i)) + y1;
    plot(x1, y1, 'b.', MarkerSize=20*m1);
    hold on 
    plot([0 x1], [0 y1], LineWidth=2);
    plot(x2, y2, 'b.', MarkerSize=20*m2);
    plot([x1 x2], [y1 y2], LineWidth=2);
    hold off
    axis([-1.1 * L, 1.1 * L, -1.1 * L, 1.1 * L]);
    pause(2^-5);
end