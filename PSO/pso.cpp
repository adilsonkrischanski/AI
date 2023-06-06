#include "particle.cpp"

#include <vector>

#define NUMBER_PARTICLES 10
#define MAX_INTERACTIONS 10

class PSO{
    private:
        Particle particles[NUMBER_PARTICLES] ;
        double global_best_fitnees;

    public:

    void run(){

        for(int i=0; i<NUMBER_PARTICLES;i++){
            particles[i].genetate_initial_solution();
            printf("%f\n", particles[i].fitness_1());
        
        }

    }
                
    





    



};