import matplotlib.pyplot as plt
import numpy as np

# Definindo os dados
dados = np.random.normal(0, 1, size=100)

# Definindo o intervalo
intervalo = [-2, 2]

# Criando o box plot com intervalo definido
plt.boxplot(dados, whis=[intervalo[0], intervalo[1]])
plt.ylim([intervalo[0]-1, intervalo[1]+1])
plt.show()