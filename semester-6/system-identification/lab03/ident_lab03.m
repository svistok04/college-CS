clear all;
close all;
clc ;

out = sim("reservoirs.slx");

h1_sim = out.h1_sim.signals.values;
h2_sim = out.h2_sim.signals.values;
disp(max(h1_sim));
disp(max(h2_sim));
time = out.tout;
k = 15.0;
for i = 1:length(h1_sim)
    if (h1_sim(i) >= 0.632*k)
        disp(time(i));
        break;
    end
end

k2 = max(h2_sim); 
for i = 1:length(h2_sim)
    if h2_sim(i) >= 0.5*k2
        T50 = time(i);
        disp(T50);
        break;
    end
end

for i = 1:length(h2_sim)
    if h2_sim(i) >= 0.9*k2
        T90 = time(i);
        disp(T90);
        break;
    end
end

ratio = T90 / T50;
alpha = 20;
T = T90/47.08;
disp(T);
disp(T*T*alpha);
disp(T*alpha);

h1_id = out.h1_id.signals.values;
h2_id = out.h2_id.signals.values;
subplot(2, 1, 1);
plot(time, h1_sim, 'b');
hold on;
plot(time, h1_id, '.r', 'MarkerSize', 1);
title('$G_1(s) = \frac{15}{1 + 4.72s}$ (first order)', ...
    'Interpreter', 'latex', 'FontSize', 14);
legend('simulation', 'identification', Location='southeast');

subplot(2, 1, 2);
plot(time, h2_sim, 'b');
hold on;
plot(time, h2_id, '.r', 'MarkerSize', 1);
title({...
    '$G_2(s) = \frac{5.85}{(1 + 0.26s)(1 + 5.20s)} = \frac{5.85}{1 + 5.362s + 1.4375s^2}$ (second order)', ...
    }, 'Interpreter', 'latex', 'FontSize', 14);
legend('simulation', 'identification', Location='southeast');
