import statistics
import matplotlib.pyplot as plt

file = './solutions/20randon.txt'
arquivo = open(file, 'r')
arquivo = arquivo.readlines()

lista1 =[]
for line in arquivo:
    line = line.split(' ')
    lista1.append(float(line[0]))


file2 = './solutions/100randon.txt'
arquivo = open(file2, 'r')
arquivo = arquivo.readlines()

lista2 =[]
for line in arquivo:
    line = line.split(' ')
    lista2.append(float(line[0]))


file3 = './solutions/250randon.txt'
arquivo = open(file3, 'r')
arquivo = arquivo.readlines()

lista3 =[]
for line in arquivo:
    line = line.split(' ')
    lista3.append(float(line[0]))


print('--------------------------')
media = media = statistics.mean(lista1)
dp = statistics.stdev(lista1)
print(media)
print(dp)
print('--------------------------')
media = media = statistics.mean(lista2)
dp = statistics.stdev(lista2)
print(media)
print(dp)
print('--------------------------')
media = media = statistics.mean(lista3)
dp = statistics.stdev(lista3)
print(media)
print(dp)


plt.boxplot([lista1, lista2, lista3])
plt.legend(['20 Variaveis', '100 Variaveis','250 Variaveis'])
plt.title("3 SAT - resolvido ")
plt.xlabel("Casos")
plt.ylabel("(%) solucionado")

plt.show()
