F = @(x, y) 2*x.^2+y.^2+x*y-6*x-5*y+8;
a = -5; b = 5;
precision = 0.05;
alpha = 0.05; % constant leaning rate instead of exact line search
h = 0.5;
iterations = 1;

x_curr = y_curr = -5;
x_prev = y_prev = Inf;
derx = (F(x_curr+h, y_curr) - F(x_curr-h, y_curr))/(2*h);
dery = (F(x_curr, y_curr+h) - F(x_curr, y_curr-h))/(2*h);

while(norm([derx, dery]) > precision)
    iterations = iterations + 1;
    x_prev = x_curr;
    y_prev = y_curr;
    x_curr = x_prev - alpha*derx/norm([derx, dery]);
    y_curr = y_prev - alpha*dery/norm([derx, dery]);
    derx = (F(x_curr+h, y_curr) - F(x_curr-h, y_curr))/(2*h);
    dery = (F(x_curr, y_curr+h) - F(x_curr, y_curr-h))/(2*h);
end

fprintf('Minimum found at x = %f, y = %f\n', x_curr, y_curr);
fprintf('Iterations = %d\n', iterations);
fprintf('Minimum value = %f\n', F(x_curr, y_curr));

%F = @(v) 2*v(1).^2+v(2).^2+v(1)*v(2)-6*v(1)-5*v(2)+8;
%a = -5; b = 5;
%precision = 0.01;
%alpha = 0.3; % constant leaning rate instead of exact line search
%h = 0.01;
%iterations = 1;
%v_curr = [-5; -5];
%v_prev = Inf*ones(2, 1);
%grad_norm = norm(v_curr - v_prev);
%
%while(grad_norm > precision)
%    iterations = iterations + 1;
%    v_prev = v_curr;
%    der = [(F([v_curr(1)+h; v_curr(2)]) - F([v_curr(1)-h; v_curr(2)]))/(2*h);
%           (F([v_curr(1); v_curr(2)+h]) - F([v_curr(1); v_curr(2)-h]))/(2*h)];
%    grad_norm = norm(der);
%    v_curr = v_prev - alpha*der/grad_norm;
%    disp(grad_norm);
%end
%
%fprintf('Minimum found at x = %f, y = %f\n', v_curr(1), v_curr(2));
%fprintf('Iterations = %d\n', iterations);
%fprintf('Minimum value = %f\n', F(v_curr));
