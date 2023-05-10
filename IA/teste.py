import matplotlib.pyplot as plt
import numpy as np

# Criando dados para o gráfico
x = np.arange(0, 10, 0.1)
y = np.sin(x)

# Criando o gráfico
plt.plot(x, y)

# Personalizando o gráfico
plt.title('Função seno')
plt.xlabel('Ângulo em radianos')
plt.ylabel('Valor de seno')
plt.grid(True)

# Exibindo o gráfico
plt.show()
