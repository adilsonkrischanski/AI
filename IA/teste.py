import random

n = random.randint(0, 10) # número de valores a serem gerados entre 0 e 10

# Gera uma lista de n valores aleatórios entre 0 e 100
aleatorios = [random.randint(0, 100) for _ in range(n)]

print(aleatorios) # Imprime a lista gerada
