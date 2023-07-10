from Sat import Sat
from simulated_anneling import Anneling
from greedy_search import Greedy
from random_search import Randon_Search

import os 
import datetime


def generate_pack(name):
   caminho = os.path.join(os.getcwd(),name)
   os.mkdir(caminho)


# if __name__=='__main__':
   # for i in range(0,10):
   #    a = Anneling('./Instancias/uf20-01.cnf', 3)
   #    a.generate_initial_solution()
   #    a.generate_neighbor(4)
   #    print(a.interation(250000,4))
   #    pack_name = f'solutions/SA/20/interaction{i+1}'
   #    a.plot_queda_temp(pack_name,100)
   #    a.save_info('solutions/SA/20.txt')
   
# if __name__=='__main__':
#    for i in range(0,10):
#       a = Randon_Search('./Instancias/uf20-01.cnf', 3)
#       a.generate_initial_solution()
#       print(a.interation(250000))
#       pack_name = f'solutions/RS/20/interaction{i+1}'
#       a.plot_queda_temp(pack_name,20)
#       a.save_info('solutions/RS/20.txt')

if __name__=='__main__':
   for i in range(0,10):
      a = Greedy('./Instancias/uf20-01.cnf', 3)
      a.generate_initial_solution()
      a.generate_neighbor(10)
      print(a.interation(250000,10))
      pack_name = f'solutions/GS/20/interaction{i+1}'
      a.plot_queda_temp(pack_name,20)
      a.save_info('solutions/GS/20.txt')
   
   

