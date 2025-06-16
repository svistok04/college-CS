clear all;
close all;
clc ;

out = sim("reservoirs.slx");
h1 = out.h1;
h2 = out.h2;

S1 = str2num(get_param("reservoirs/Subsystem", "S1"));
S2 = str2num(get_param("reservoirs/Subsystem", "S2"));
Swy1 = str2num(get_param("reservoirs/Subsystem", "Swy1"));
Swy2 = str2num(get_param("reservoirs/Subsystem", "Swy2"));

for i = 1 : length(h1)
    fill([0 S1 S1 0], [0 0 h1(i) h1(i)], "b", EdgeColor="none");
    hold on
    fill([S1 S1+1 S1+1 S1], [0 0 min(h1(i), Swy1) min(h1(i), Swy1)], 'b', EdgeColor="none");
    fill([S1+1 S1+1+S2 S1+1+S2 S2], [0 0 h2(i) h2(i)],'b', EdgeColor="none");
    fill([S1+1+S2 S1+2+S2 S1+2+S2 S1+1+S2], [0 0 min(h2(i), Swy2) min(h2(i), Swy2)],'b', EdgeColor="none");

    plot([0 S1+S2+2], [0 0], 'k') 

    plot([0 0], [0 max(h1) + 1], 'k'); % line 1_1
    plot([S1 S1], [Swy1 max(h1) + 1], 'k'); % line 1_2
    
    plot([S1+1 S1+1], [Swy2 max(h2) + 1], 'k'); % line 2_1
    plot([S1+1+S2 S1+1+S2], [Swy2 max(h2) + 1], 'k'); % line 2_2

    plot([S1 S1+1], [Swy1 Swy1], 'k');
    plot([S1+1+S2 S1+2+S2], [Swy2 Swy2], 'k');

    axis([-0.5, S1+S2+2.5, -0.5, max(max(h1), max(h2)) + 1.5]);
    hold off
    pause(0.01);
end