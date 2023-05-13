import statistics
import matplotlib.pyplot as plt

file = './solutions/250.txt'
arquivo = open(file, 'r')
arquivo = arquivo.readlines()

lista1 =[]
for line in arquivo:
    line = line.split(' ')
    lista1.append(float(line[0]))


file2 = './solutions/250randon.txt'
arquivo = open(file2, 'r')
arquivo = arquivo.readlines()

lista2 =[]
for line in arquivo:
    line = line.split(' ')
    lista2.append(float(line[0]))


fig, ax = plt.subplots()
ax.boxplot([lista1, lista2])

# personalizando o boxplot
ax.set_title('20 Variaveis')
ax.set_xticklabels(['SA', 'RS'])
ax.set_ylabel('% solved')

# mudando a cor das linhas do boxplot
for line in ax.lines:
    line.set_color('purple')

# mudando a cor das caixas do boxplot
for box in ax.artists:
    box.set_facecolor('lightblue')
    box.set_edgecolor('blue')



# ajustando o tamanho das fontes
ax.tick_params(axis='both', which='major', labelsize=10)

plt.show()
