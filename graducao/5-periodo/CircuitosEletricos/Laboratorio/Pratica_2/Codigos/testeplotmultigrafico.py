### Código para plotar 3 funções em um único gráfico.
import matplotlib.pyplot as plt

# Armazenando os valores em variáveis.
# Em nosso caso esses valores representam a tensão em Volts.
x = [0, 0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 5.5, 6, 6.5, 7, 7.5, 8, 8.5, 9, 9.5, 10, 10.5, 11, 11.5, 12, 12.5, 13, 13.5, 14, 14.5, 15, 15.5, 16, 16.5, 17, 17.5, 18, 18.5, 19, 19.5, 20, 20.5, 21, 21.5, 22, 22.5, 23, 23.5, 24, 24.5, 25, 25.5, 26, 26.5, 27, 27.5, 28, 28.5, 29, 29.5, 30]

# Valores de Corrente variando em função da resistência usada.
yResNominal = [] # Corrente com a resistencia nominal.
yResMedido = [] # Corrente com a resistencia medida.
yResEstimado = [] # Corrente com a resistencia estimada.

# Criando as relações de correspondência.
for z in x:
	yResNominal.append(z/10)
	yResMedido.append(z/9.943)
	yResEstimado.append(z/9.856)

# Passando os parâmetros para combinação.
plt.plot(x,yResNominal, label="Nominal")
plt.plot(x,yResMedido, label="Medida")
plt.plot(x,yResEstimado, label="Estimada")

# Título do gráfico.
plt.title("Relação I X V")
# Alterando o label dos eixos.
plt.ylabel("I(mA)")
plt.xlabel("V(V)")
# Inserindo a legenda no melhor lugar.
plt.legend(loc='upper left')
# Exibindo o gráfico.
plt.show()