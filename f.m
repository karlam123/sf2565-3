function [y] = f(x)
N = length(x);
y = zeros(N, 1);

for n=1:N
    if (-10 <= x(n) && x(n) < -3)
       y(n) = 0.5/(1+exp(-3*(x(n)+6)));
    elseif (-3 <= x(n) && x(n) <= 5)
       y(n) = 0.5/(1+exp(3*x(n)));
    else
       y(n)=0;
    end
end
end

