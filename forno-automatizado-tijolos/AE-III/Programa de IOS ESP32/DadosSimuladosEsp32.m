
figure;

subplot(2,1,1);
plot(Tempo, Temperatura, 'r-o', 'LineWidth', 1.5);
title('Temperatura');
xlabel('Tempo (s)');
ylabel('Graus C');
grid on;

subplot(2,1,2);
plot(Tempo, Corrente, 'b-o', 'LineWidth', 1.5);
title('Corrente');
xlabel('Tempo (s)');
ylabel('mA');
grid on;