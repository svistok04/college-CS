clear all
close all
clc

out = sim("satelita");
x = out.x;
y = out.y;

R = str2num(get_param("satelita/Subsystem", "R"));
Rs = str2num(get_param("satelita/Subsystem", "Rs"));

figure
for i = 1:length(x)
    
    plot(x(1:i), y(1:i), 'b.','MarkerSize',5);
    hold on
    daspect([1, 1, 1])
    rectangle(Position=[0-R, 0-R, 2 * R, 2 * R], Curvature=[1, 1])
    rectangle(Position=[x(i)-Rs y(i)-Rs, 2*Rs 2*Rs], Curvature=[1, 1])
    axis([-10, 10, -10, 10])
    hold off
    pause(2^-7)
end
