import statistics
import matplotlib.pyplot as plt
import math

def function(lista):
    # Calculando a média
    media = sum(lista) / len(lista)
    print("Média:", media)

    # Calculando o desvio padrão
    variancia = sum((x-media)**2 for x in lista) / (len(lista) - 1)
    desvio_padrao = math.sqrt(variancia)
    print("Desvio padrão:", desvio_padrao)

    return media, desvio_padrao


def mostra(l1,l2,l3,var):
    m1,dp1 = function(l1)
    m2,dp2 = function(l2)
    m3,dp3 = function(l3)
    print(f'uf{var}-91-01 & {m1:.2f}\% & {dp1:.3f} & {m2:.2f}\% & {dp2:.3f} & {m3:.2f}\% & {dp3:.3f} \\')

def plot(lista, labels):


    fig, ax = plt.subplots()
    ax.boxplot(lista)


    ax.set_title(f'{var} Variaveis')
    ax.set_xticklabels(labels)
    ax.set_ylabel('% solved')

    for line in ax.lines:
        line.set_color('purple')

    # mudando a cor das caixas do boxplot
    for box in ax.artists:
        box.set_facecolor('lightblue')
        box.set_edgecolor('blue')

    plt.title(f"{var} Variaveis")
    plt.savefig(f'BOX_{var}.png')

if __name__=="__main__":
    var = 250

    file = f'./solutions/GS/{var}.txt'
    arquivo = open(file, 'r')
    arquivo = arquivo.readlines()


    lista1 =[] 
    for line in arquivo:
        line = line.split(' ')
        lista1.append(float(line[0]))

    file2  = f'./solutions/RS/{var}.txt'
    arquivo = open(file2, 'r')
    arquivo = arquivo.readlines()

    lista2 =[]
    for line in arquivo:
        line = line.split(' ')
        lista2.append(float(line[0]))

    file3  = f'./solutions/SA/{var}.txt'
    arquivo = open(file3, 'r')
    arquivo = arquivo.readlines()
    lista3 =[]
    for line in arquivo:
        line = line.split(' ')
        lista3.append(float(line[0]))


    mostra(lista1,lista2,lista3,var)

    plot([lista1,lista2,lista3],['SA','GS', 'RS'])
