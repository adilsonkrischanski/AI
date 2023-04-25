from Sat import Sat

if __name__=='__main__':
   sat = Sat('./Instancias/uf20-01.cnf',3)
   sat.upload()
   sat.generate_initial_solution()
   sat.generate_neighbor()
   print(sat.fitness(0))
   print(sat.fitness(1))