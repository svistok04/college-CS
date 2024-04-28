A = input("Wprowadz wektor wspolrzednych wielomianu: ");

x = -10:0.1:10;

W = zeros(size(x));

disp(size(x));

A_length = length(A);

for i = 1:A_length
    W = W + A(i) * x.^(i-1);
end

plot(x, W)

podpis = "W(x) = ";

for i = 1:A_length
   if A(i) ~= 0 
        if i > 1
            podpis = podpis + "+";
        end
        podpis = podpis + A(i);
        if i > 1
            podpis = podpis + "x^" + (i-1);
        end
   end
end

title(podpis);
grid on;
