from Sat import Sat
import os 
import datetime


def generate_pack(name):
   caminho = os.path.join(os.getcwd(),name)
   os.mkdir(caminho)

# if __name__=='__main__':
   # for i in range(0,51):
   #    sat = Sat('./Instancias/uf20-01.cnf',3)
   #    sat.upload()
   #    sat.generate_initial_solution()
   #    sat.generate_neighbor(5)
   #    print(sat.interation(10000,5))
   #    pack_name = f'solutions/10/{datetime.datetime.now().time()}'
   #    generate_pack(pack_name)
   #    sat.plot_queda_temp(f'{pack_name}/10-1000-5-4')
   #    sat.plot_fitness_vizinho(f'{pack_name}/10-1000-5-4')
   #    sat.save_info('./solutions/10.txt')

# if __name__=='__main__':
#    for i in range(0,51):
#       sat = Sat('./Instancias/uf100-01.cnf',3)
#       sat.upload()
#       sat.generate_initial_solution()
#       sat.generate_neighbor(15)
#       print(sat.interation(250000,10)) #15
#       pack_name = f'solutions/100/{datetime.datetime.now().time()}'
#       generate_pack(pack_name)
#       sat.plot_queda_temp(f'{pack_name}/100-250000-10-4')
#       sat.plot_fitness_vizinho(f'{pack_name}/100-250000-10-4')
#       sat.save_info('./solutions/100.txt')

if __name__=='__main__':
   # for i in range(0,51):
      sat = Sat('./Instancias/uf250-01.cnf',3)
      sat.upload()
      sat.generate_initial_solution()
      sat.generate_neighbor(15)
      print(sat.interation(250000,15))
      # pack_name = f'solutions/250/{datetime.datetime.now().time()}'
      # generate_pack(pack_name)
      # sat.plot_queda_temp(f'{pack_name}/250-250000-30-4')
      # sat.plot_fitness_vizinho(f'{pack_name}/250-250000-30-4')
      # sat.save_info('./solutions/250.txt')



# if __name__=='__main__':
#    for i in range(0,10):
#       sat = Sat('./Instancias/uf20-01.cnf',3)
#       sat.upload()
#       sat.generate_initial_solution()
#       sat.randon_solution()
#       print(sat.interactions2(2000))
      


      
   

