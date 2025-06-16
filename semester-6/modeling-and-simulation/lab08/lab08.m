clear all
close all
clc 

out = sim("magnetic_pendulum.slx");
x = out.x;
y = out.y;

x_i = str2num(get_param("magnetic_pendulum/Subsystem", "x_i"));
y_i = str2num(get_param("magnetic_pendulum/Subsystem", "y_i"));
d_i = str2num(get_param("magnetic_pendulum/Subsystem", "d_i"));
a_i = str2num(get_param("magnetic_pendulum/Subsystem", "a_i"));
m = str2num(get_param("magnetic_pendulum/Subsystem", "m"));
l = str2num(get_param("magnetic_pendulum/Subsystem", "l"));


for i = 1 : length(x)
    plot3(x_i(a_i > 0), y_i(a_i > 0), d_i(a_i > 0), 'r.', MarkerSize=20); % magnesy przyciagajace
    hold on
    plot3(x_i(a_i < 0), y_i(a_i < 0), d_i(a_i < 0), 'b.', MarkerSize=20); % magnesy odpychajace

    b = sqrt(x(i)^2+y(i)^2);
    c = sqrt(l^2 - b^2);
    z = l - c;

    plot3(x(i), y(i), z, 'k.', MarkerSize = 20 * m); % masa
    plot3([x(i), 0], [y(i), 0], [z, l], 'b', LineWidth = 2); % lina
    hold off
    axis([-l, l, -l, l, -0.1, l]);
    pause(0.01);
end