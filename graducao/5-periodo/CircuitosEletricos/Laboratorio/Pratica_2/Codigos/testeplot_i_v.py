### Código para plotar gráfico I x V do circuito com LED.
import matplotlib.pyplot as plt

# Armazenando os valores em variáveis.
# Em nosso caso esses valores representam a corrente em miliAmperes.
x = [0, 0.002, 0.001, 0.002, 0.037, 0.085, 0.139, 0.186, 0.230, 0.282, 0.333, 0.385, 0.428, 0.478, 0.531, 0.584, 0.630, 0.681, 0.731, 0.785, 0.832, 0.879, 0.936, 0.988, 1.035, 1.084, 1.137, 1.188, 1.231, 1.281, 1.333, 1.386, 1.436, 1.482, 1.541, 1.583, 1.641, 1.687, 1.738, 1.783, 1.839, 1.888, 1.938, 1.988, 2.039, 2.092, 2.141, 2.199, 2.245, 2.297, 2.353, 2.402, 2.450, 2.509, 2.550, 2.609, 2.658, 2.710, 2.752, 2.806, 2.860]
# Valores do potêncial.
y = [0, 0.535, 1.14, 1.67, 1.75, 1.79, 1.82, 1.82, 1.83, 1.84, 1.85, 1.86, 1.87, 1.88, 1.89, 1.89, 1.9, 1.9, 1.9, 1.9, 1.9, 1.9, 1.91, 1.91, 1.91, 1.92, 1.92, 1.93, 1.93, 1.93, 1.94, 1.94, 1.95, 1.95, 1.95, 1.95, 1.96, 1.96, 1.96, 1.96, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98]

# Passando os parâmetros para combinação.
plt.plot(x,y)

# Título do gráfico.
plt.title("Relação I X V circuito com LED")
# Alterando o label dos eixos.
plt.ylabel("I(mA)")
plt.xlabel("V(V)")
# Inserindo a legenda no melhor lugar.
#plt.legend(loc='upper left')
# Exibindo o gráfico.
plt.show()