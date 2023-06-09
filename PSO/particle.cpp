#include <vector>
#include <random>
#include <cmath>

#define DIM 1

#define LOWER_BOUND -600
#define UPPER_BOUND 600

using namespace std;

class Particle {
    private :
    int lower_bound = LOWER_BOUND;
    int upper_bound = UPPER_BOUND;
    double contention_factor_best = 2;
    double contention_factor_social = 2;
    int max_speed = 10;
    int min_speed = -10;

    double atual_fitness;
    double best_fitness;


    double atual_position[DIM];
    double best_position[DIM];
    double speed_particle[DIM];

public:

    
    void genetate_initial_solution(){
        for(int i=0; i< DIM; i++){
            atual_position[i] = (rand() % (UPPER_BOUND - LOWER_BOUND + 1)) + LOWER_BOUND;
            speed_particle[i] = 0;
            best_position[i] = atual_position[i];
            
        }
    }
    
    void updateVelocity(double* best_global_position) {
        double vel_best[DIM];
        double vel_global_best[DIM];

        // printf("\nVELOCIDADE:\n");

        for (int i = 0; i < DIM; i++) {

            vel_best[i] = best_position[i] - atual_position[i];
            vel_global_best[i] = best_global_position[i] - atual_position[i];

            speed_particle[i] += (vel_best[i] * contention_factor_social) + (vel_global_best[i] * contention_factor_social);

            if (speed_particle[i] > max_speed) {
                double value = std::fmod(std::floor(speed_particle[i]), 10.0);
                speed_particle[i] = value ;
            }
            if (speed_particle[i] < min_speed) {
                double value = std::fmod(std::floor(speed_particle[i]), 10.0);
                speed_particle[i] = value;
            }

            // printf("%f ",speed_particle[i]);
        }

    }


    void update_position(){
        for(int i=0; i< DIM; i++){

            atual_position[i] += speed_particle[i];

            if( atual_position[i] > upper_bound){
                atual_position[i] = upper_bound;
                speed_particle[i] *= -1 ;
            }

            if(atual_position[i] < lower_bound){
                atual_position[i] = lower_bound;
                speed_particle[i] *= -1 ;
            }
        }

    }
  
    double fitness_1() {

        int top = 0;
        int top1 = 0;
        int top2 = 1;
        for(int j = 0; j < DIM; j++) {
            top1 = top1 + pow((atual_position[j]), (double)2);
            top2 = top2 * cos((((atual_position[j]) / sqrt((double)(j+1))) * M_PI)/180);
            }

        top = (1/(double)4000) * top1 - top2 + 1;

        atual_fitness = top;

        if (atual_fitness < best_fitness){
            best_fitness = atual_fitness;
            for(int i=0; i< DIM; i++){
                best_position[i] = atual_position[i];
            }

        }
        return top;
    }
    
    double fitness_2() {
        int aux = 0;
        int aux1 = 0;
        for (int i = 0; i < DIM; i++) {
            aux += atual_position[i] * atual_position[i];
        }
        for (int i = 0; i < DIM; i++){
            aux1 += cos(2.0*M_PI* atual_position[i]);
        }
        atual_fitness = (-20.0*(exp(-0.2*sqrt(1.0/(float)DIM*aux)))-exp(1.0/(float)DIM*aux1)+20.0+exp(1));

        return (-20.0*(exp(-0.2*sqrt(1.0/(float)DIM*aux)))-exp(1.0/(float)DIM*aux1)+20.0+exp(1));
    }


    double* getAtualPosition() {
        return atual_position;
    }

    double*  getBestPosition() {
        return best_position;
    }

    double* getSpeedParticle() {
        return speed_particle;
    }


};
