#include "particle.cpp"

#include <vector>

#define NUMBER_PARTICLES 50
#define MAX_INTERACTIONS 100000

class PSO{
    private:
        Particle particles[NUMBER_PARTICLES] ;
        double global_best_fitnees;
        double atual_fitness;
        double medium_fitness;
        double* global_best_position;

    public:

    void run(){
        global_best_position = (double *) malloc(sizeof(double)*DIM);


        for(int i=0; i<NUMBER_PARTICLES;i++){
            
            particles[i].genetate_initial_solution();
            if(i==0){
                global_best_fitnees = particles[i].fitness_1();
            }
        }

        for(int i=0; i<MAX_INTERACTIONS;i++){
            medium_fitness = 0;
            
            for(int j = 0; j < NUMBER_PARTICLES; j++){

                atual_fitness = particles[j].fitness_1();
                medium_fitness += atual_fitness;

                if (atual_fitness < global_best_fitnees){
                    global_best_fitnees = atual_fitness;
                    for (int k = 0; k < DIM; k++){
                        global_best_position[k] = particles[j].getAtualPosition()[k];
                    }
                    // global_best_position = particles[j].getAtualPosition();
                }
            }

            for(int j = 0; j < NUMBER_PARTICLES; j++){

                particles[j].updateVelocity(global_best_position);
                // particles[j].update_position();
            }

            printf("\nBEST: %f  ", global_best_fitnees);
            printf("\nMEDIUM: %f  ", (medium_fitness/(double)NUMBER_PARTICLES));

            // printf("\nPOSITION: ");

            // for(int i = 0; i< DIM;i++){
            //     printf("%f ",global_best_position[i]);
            // }

           

        }

        
        





    }
                    



};