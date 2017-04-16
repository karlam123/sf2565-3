clear
fileID =  fopen('outfile.bin', 'r');
data = fread(fileID, 'double');
fclose(fileID);

m = data(1)
n = data(2)
x = data(3:m*n+2)
y = data(m*n+3:end)
plot(x, y, '.')
hold on
N=100;
x1 = linspace(-10, 5, N);
y1 = linspace(0, 3, N);

plot(x1, f(x1),'r')
plot(-10*ones(N, 1), y1,'r')
plot(x1, 3*ones(N, 1),'r')
plot(5*ones(N, 1), y1,'r')
xlabel('x')
ylabel('y')