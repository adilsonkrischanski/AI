import statistics
import matplotlib.pyplot as plt

file = './solutions/10.txt'
arquivo = open(file, 'r')
arquivo = arquivo.readlines()

lista1 =[]
for line in arquivo:
    line = line.split(' ')
    lista1.append(float(line[0]))


file2 = './solutions/100.txt'
arquivo = open(file2, 'r')
arquivo = arquivo.readlines()

lista2 =[]
for line in arquivo:
    line = line.split(' ')
    lista2.append(float(line[0]))


file3 = './solutions/250.txt'
arquivo = open(file3, 'r')
arquivo = arquivo.readlines()

lista3 =[]
for line in arquivo:
    line = line.split(' ')
    lista3.append(float(line[0]))


media = media = statistics.mean(lista1)
dp = statistics.stdev(lista1)


plt.boxplot([lista1, lista2, lista3])
plt.legend(['10 Variaveis', '100 Variaveis','250 Variaveis'])
plt.title("3 SAT - resolvido ")
plt.xlabel("Casos")
plt.ylabel("(%) solucionado")

plt.show()
