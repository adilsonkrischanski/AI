import matplotlib.pyplot as plt

# dados das listas
lista1 = [10, 15, 20, 25, 30, 35]
lista2 = [5, 10, 15, 20, 25, 30]

# criando o boxplot
fig, ax = plt.subplots()
box = ax.boxplot([lista1, lista2])

for i, patch in enumerate(box['boxes']):
    x = patch.get_xdata()
    y = patch.get_ydata()
    ax.fill_betweenx(y, x[0], x[3], alpha=0.3, color=f'C{i}')

# personalizando o boxplot
ax.set_title('Exemplo de Boxplot com Corpo Preenchido')
ax.set_xticklabels(['Lista 1', 'Lista 2'])
ax.set_ylabel('Valores')

# mudando a cor das linhas do boxplot
for line in ax.lines:
    line.set_color('purple')

# mudando a cor das caixas do boxplot
for box in ax.artists:
    box.set_edgecolor('blue')

# ajustando o tamanho das fontes
ax.tick_params(axis='both', which='major', labelsize=10)

plt.show()
