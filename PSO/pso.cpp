#include "particle.cpp"

#include <vector>

#define NUMBER_PARTICLES 10
#define MAX_INTERACTIONS 10

class PSO{
    private:
        Particle particles[NUMBER_PARTICLES] ;
        double global_best_fitnees;
        std::vector<double>* global_best_position;

    public:

    void run(){

        for(int i=0; i<NUMBER_PARTICLES;i++){
            
            particles[i].genetate_initial_solution();
            if(i==0){
                global_best_fitnees = particles[i].fitness_1();
            }
            // printf("%f\n", particles[i].fitness_1());
        }
        

        //  for(int i=0; i<MAX_INTERACTIONS;i++){
            
        //     double atual_fitness = particles[i].fitness_1();

        //     if (global_best_fitnees < atual_fitness){
        //         global_best_fitnees = atual_fitness;
        //         global_best_position = particles[i].getAtualPosition();

        //         for(int j =0; j<10;j++){
        //             printf("%d",global_best_position[i]);
        //         }
        //     } 

        //     // for(int j = 0; j < NUMBER_PARTICLES; j++){
        //     //     printf("ENTREI NO FOR");
        //     //     particles[i].updateVelocity(global_best_position);
        //     //     printf("update velocidade check");


        //     //     particles[i].update_position();
        //     // }

           
        //     // update beste global position

        //     //passar o melhor pra todas as particulas

        //     //particulas integem

        //     // TODO AGAIN

        //      printf("BEST: %f  \n", global_best_fitnees);
        // }



    }
                    



};