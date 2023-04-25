import random
class Sat:
    def __init__(self,file, len):
        self.quant_var = None
        self.clause_length = len
        self.file = file
        self.instances =[]
        self.solution = []
        self.neighbor = []

    def upload(self,):
        file = open(self.file,'r')
        file = file.read()
        file = file.split('\n')
        for line in file:
            line = line.split(' ')
            print(line)
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

    def generate_neighbor(self):
        quant_bitflip = random.randint(0,10)
        self.neighbor = self.solution
        for i in range(0,quant_bitflip):
            cases_to_flip = random.sample(range(0, self.quant_var), quant_bitflip)
            for case in cases_to_flip:
                self.neighbor[case] = random.randint(0, 1)
    

    def fitness(self, param): # if param = 0 fitness of solution if param = 1 solution of neighbor
        count = 0
        if param == 0:
            for instance in self.instances:
                instace_conditional = False
                for var in instance:
                    if var > 0:
                        if self.solution[var] == 1:
                            instace_conditional  = True
                            break
                    else:
                        if self.solution[(var*(-1))] == 0:
                            instace_conditional  = True
                            break
                if instace_conditional ==1:
                    count +=1
        if param == 1:
            for instance in self.instances:
                instace_conditional = False
                for var in instance:
                    print(var)
                    if var > 0:
                        if self.neighbor[var] == 1:
                            instace_conditional  = True
                            break
                    else:
                        if self.neighbor[(var*(-1))] == 0:
                            instace_conditional  = True
                            break
                if instace_conditional ==1:
                    count +=1
        return count

