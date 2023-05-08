import random
import matplotlib.pyplot as plt
import math
class Sat:
    def __init__(self,file, len):
        self.quant_var = None
        self.clause_length = len
        self.file = file
        self.instances =[]
        self.solution = []
        self.neighbor = []
        self.interation_number = 0
        self.fit_solution = 0
        self.fit_neighbor = 0


        self.temp = 1
        self.fatorResfriamento = 5 # 4.5 # min 1 max 5, 4 funciona ok
        self.temperaturas = []

        self.fitzinho =[]

    def upload(self,):
        file = open(self.file,'r')
        file = file.read()
        file = file.split('\n')
        for line in file:
            line = line.split(' ')
            if line[0]== 'p':
                self.quant_var = int(line[2])
                self.quant_clausulas = int(line[3])
            else:
                instance =[]
                for i in range(0, self.clause_length):
                    instance.append(int(line[i]))
                self.instances.append(instance)
    

    def generate_initial_solution(self):
        for i in range(0,self.quant_var):
            bit = random.randint(0, 1)
            self.solution.append(bit)
            self.neighbor.append(bit)
        self.fit_solution = self.fitness(0)

    def generate_neighbor(self,bitflipquant):
        quant_bitflip = random.randint(0,bitflipquant)
        self.neighbor = []
        for i in self.solution:
            self.neighbor.append(i)
        
        
        for i in range(0,quant_bitflip):
            cases_to_flip = random.sample(range(0, self.quant_var), quant_bitflip)
            for case in cases_to_flip:
                #need alternate 
                if self.neighbor[case] == 0:
                    self.neighbor[case] = 1
                else:
                    self.neighbor[case] = 0

        self.fit_neighbor = self.fitness(1)



    def fitness(self, param): # if param = 0 fitness of solution if param = 1 solution of neighbor
        count = 0
        if param == 0:
            for instance in self.instances:
                instace_conditional = False
                for var in instance:
                    if var > 0:
                        if self.solution[var-1] == 1:
                            instace_conditional  = True
                            break
                    else:
                        if self.solution[(var*(-1))-1] == 0:
                            instace_conditional  = True
                            break
                if instace_conditional ==1:
                    count +=1
        if param == 1:
            for instance in self.instances:
                instace_conditional = False
                for var in instance:
                    if var > 0:
                        if self.neighbor[var-1] == 1:
                            instace_conditional  = True
                            break
                    else:
                        if self.neighbor[(var*(-1))-1] == 0:
                            instace_conditional  = True
                            break
                if instace_conditional ==1:
                    count +=1
        return (count/self.quant_clausulas)*100


    def interation(self, max, bitflip):
        for i in range(0, max): 
            self.interation_number = i
            if self.fit_solution == 100:
                return self.fit_solution
            self.temperatura_upgrade(i,max)
            self.generate_neighbor(bitflip)
            if self.fit_solution <= self.fit_neighbor:
                self.solution=[]
                for j in self.neighbor:  
                    self.solution.append(j)
                self.fitzinho.append(100-self.fit_neighbor)
                self.fit_solution = self.fit_neighbor
            else:
                probability = math.exp(-(self.fit_solution - self.fit_neighbor) / self.temp)
                if random.uniform(0, 1) < probability:
                    self.solution=[]
                    for j in self.neighbor:  
                        self.solution.append(j)
                    self.fitzinho.append(100-self.fit_neighbor)
                    self.fit_solution = self.fit_neighbor
                    

        return self.fit_solution

    def temperatura_upgrade(self, interaction_number,maxquantInteraction):
        self.temp = (1- interaction_number/maxquantInteraction)**self.fatorResfriamento
        self.temperaturas.append(self.temp)


    def plot_queda_temp(self,name_save):
        plt.clf()
        plt.cla()
        # print(self.temperaturas)
        x=list(range(1,len(self.temperaturas)+1))
        print(len(x))
        plt.plot(x, self.temperaturas )
        
        plt.savefig(f'{name_save}_temperature.png')
    
    def plot_fitness_vizinho(self,name_save):
        plt.clf()
        plt.cla()
        # print(self.temperaturas)
        x =list(range(1,len(self.fitzinho)+1))
        plt.plot(x, self.fitzinho)
        plt.ylim(0, 30)
        print(len(x))
        plt.savefig(f'{name_save}_fitnes.png')

    def save_info(self, file):
        file = open(file,'a')
        file.write(f'{self.fitness(0)} {self.interation_number}\n')
        file.close()

    def randon_solution(self):
        self.neighbor = []
        for i in self.solution:
            self.neighbor.append(random.randint(0, 1))

    def interactions2(self,quant):
        grafico = []
        aux =0
        for i in range(0,quant):
            self.randon_solution()
            if self.fitness(0)>self.fitness(1):
                aux =i
                self.solution = []
                for i in self.neighbor:
                    self.solution.append(i)

            grafico.append(self.fitness(1))
        
        plt.plot(grafico)
        plt.show()

        return (aux, self.fitness(0))

        

                

