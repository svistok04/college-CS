clear all
close all
clc

out = sim('lab03');
fi = out.phi;

L = str2num(get_param("lab03/Subsystem", 'l'))
m = str2num(get_param("lab03/Subsystem", 'm'))

for i = 1:length(fi)
    plot(-L*sin(fi(i)), -L*cos(fi(i)), 'b.','MarkerSize',5*m);% kulka
    hold on
    plot([0 -L*sin(fi(i))], [0 -L*cos(fi(i))],'Color','r','LineWidth',2); % wahadlo
    hold off
    axis([-1.1*L 1.1*L -1.1*L 1.1*L])
    pause(0.001)
end