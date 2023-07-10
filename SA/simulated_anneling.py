from Sat import Sat
import random
import math
import matplotlib.pyplot as plt

class Anneling:
    def __init__(self, file, len) -> None:
        self.sat = Sat(file, len) # sat class
        self.sat.upload()

        self.current_solution = []
        self.neighbor_solution = []

        self.current_value = 0
        self.neighbor_value = 0

        self.interation_number = 0
        self.fatorResfriamento = 4 # 4.5 # min 1 max 5, 4 funciona ok

        # to graphics generator
        self.temperaturas = []
        self.graphic_solution =[]

    def generate_initial_solution(self):
        for i in range(0,self.sat.get_quant_var()):
            bit = random.randint(0, 1)
            self.current_solution.append(bit)
            self.neighbor_solution.append(bit)
        
        self.current_value = self.sat.fitness(self.current_solution)
        self.neighbor_value  = self.current_value


    def generate_neighbor(self,bitflipquant):
        quant_bitflip = random.randint(0,bitflipquant)
        self.neighbor_solution = []
        for i in self.current_solution:
            self.neighbor_solution.append(i)
        
        for i in range(0,quant_bitflip):
            cases_to_flip = random.sample(range(0, self.sat.get_quant_var()), quant_bitflip)
            for case in cases_to_flip:
                if self.neighbor_solution[case] == 0:
                    self.neighbor_solution[case] = 1
                else:
                    self.neighbor_solution[case] = 0

        self.neighbor_value = self.sat.fitness(self.neighbor_solution)

    
    def temperatura_upgrade(self, interaction_number,maxquantInteraction):
        self.temp = (1- interaction_number/maxquantInteraction)**self.fatorResfriamento
        self.temperaturas.append(self.temp)
    

    def interation(self, max, bitflip):
        for i in range(0, max): 
            self.graphic_solution.append(100-self.current_value)
            self.interation_number = i
            if self.current_value == 100:
                self.graphic_solution.append(100-self.current_value)
                return self.current_value
            
            self.temperatura_upgrade(i,max)
            self.generate_neighbor(bitflip)

            if self.current_value <= self.neighbor_value:
                self.current_solution = []
                for j in self.neighbor_solution:  
                    self.current_solution.append(j)

                self.current_value = self.neighbor_value         
            else:
                probability = math.exp(-(self.current_value - self.neighbor_value) / self.temp)

                if random.uniform(0, 1) < probability:
                    self.current_solution = []
                    for j in self.neighbor_solution:  
                        self.current_solution.append(j)

                    self.current_value = self.neighbor_value

        return self.current_value
    

    def plot_queda_temp(self,name_save, var):
        plt.clf()
        plt.cla()
        fig, axs = plt.subplots(nrows=1, ncols=2, figsize=(8, 4))
        axs[0].plot(self.graphic_solution)
        axs[0].set_title(f'Simulated Anneling {var} Variaveis ')
        axs[0].set_xlabel('Iterações')
        axs[0].set_ylabel('% Sat NOT Solved')
        axs[1].plot(self.temperaturas)
        axs[1].set_title('Queda Temperatura')
        axs[1].set_xlabel('Iterações')
        axs[1].set_ylabel('Temperatura')
        plt.savefig(f'{name_save}_SA.png')


    def save_info(self, file):
        file = open(file,'a')
        file.write(f'{self.current_value} - {self.interation_number} - {self.current_solution}\n')
        file.close()




    