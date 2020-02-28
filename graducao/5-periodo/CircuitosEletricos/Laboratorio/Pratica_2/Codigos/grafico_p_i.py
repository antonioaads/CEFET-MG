### Código para plotar o gráfico P x I e P x V.
import matplotlib.pyplot as plt
import numpy as np

# Armazenando os valores em variáveis.
# Em nosso caso esses valores representam a tensão em Volts.
v = np.array([0, 0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 5.5, 6, 6.5, 7, 7.5, 8, 8.5, 9, 9.5, 10, 10.5, 11, 11.5, 12, 12.5, 13, 13.5, 14, 14.5, 15, 15.5, 16, 16.5, 17, 17.5, 18, 18.5, 19, 19.5, 20, 20.5, 21, 21.5, 22, 22.5, 23, 23.5, 24, 24.5, 25, 25.5, 26, 26.5, 27, 27.5, 28, 28.5, 29, 29.5, 30])
# Corrente medida em miliAmperes
i = np.array([0, 0.061, 0.104, 0.159, 0.209, 0.258, 0.308, 0.360, 0.408, 0.463, 0.516, 0.565, 0.616, 0.664, 0.710, 0.768, 0.818, 0.868, 0.914, 0.965, 1.014, 1.068, 1.114, 1.174, 1.216, 1.265, 1.323, 1.368, 1.420, 1.468, 1.527, 1.570, 1.621, 1.670, 1.722, 1.771, 1.822, 1.878, 1.932, 1.977, 2.029, 2.078, 2.133, 2.184, 2.232, 2.286, 2.333, 2.391, 2.441, 2.491, 2.545, 2.587, 2.643, 2.689, 2.747, 2.799, 2.845, 2.901, 2.946, 3.002, 3.051])
p = [] # Lista criada para armazenar os valores de p, sendo P = VI.

# Criando a relações de correspondência.
for z in range(61):
	p.append(v[z]*i[z])

# Passando os parâmetros para combinação.
plt.plot(v,p)

# Título do gráfico.
plt.title("Relação P X V")
# Alterando o label dos eixos.
plt.ylabel("P(W)")
plt.xlabel("V(V)")
# Inserindo a legenda no melhor lugar.
#plt.legend(loc='upper left')
# Exibindo o gráfico.
plt.show()