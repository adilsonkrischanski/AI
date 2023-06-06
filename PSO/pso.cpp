#include "particle.cpp"

#include <vector>

#define NUMBER_PARTICLES 10
#define MAX_INTERACTIONS 10

class PSO{
    private:
        Particle particles[NUMBER_PARTICLES] ;
        double global_best_fitnees;
        std::vector<double> global_best_position[DIM];

    public:

    void run(){

        for(int i=0; i<NUMBER_PARTICLES;i++){
            particles[i].genetate_initial_solution();
            printf("%f\n", particles[i].fitness_1());
        }

        for(int i=0; i<MAX_INTERACTIONS;i++){


            // ver todos os fitness e salvar o melhor (value and postion)
                  
            // update beste global position

            //passar o melhor pra todas as particulas

            //particulas integem

            // TODO AGAIN


        }



    }
                
    





    



};