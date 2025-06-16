function [x, y] = generate_spring(L, r, theta, x_start, y_start)
    spring_length = L + r;    
    theta = -(theta) - pi/2; 
    amp = 0.1; % szerokosc sprezyny
    coil_number = 30; % gestosc
    
    
    x_spring = 0: 0.01 : (spring_length - 0.2); % 0.2 na zaczepienie
    x_coils = linspace(0, pi * coil_number, length(x_spring)); 
    % zmapowanie y dla sinusoidy na wsp. na linie wahadla
    coords = [x_spring, spring_length; sin(x_coils) * amp, 0];
    
    R = [cos(theta) -sin(theta); sin(theta) cos(theta)]; 
    rotcoord = R*coords;

    x = x_start + rotcoord(1, :);
    y = y_start + rotcoord(2, :);
end