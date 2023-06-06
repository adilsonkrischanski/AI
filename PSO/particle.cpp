#include <vector>
#include <random>
#include <cmath>

#define DIM 10

#define LOWER_BOUND -600
#define UPPER_BOUND 600

class Particle {
    private :
    int lower_bound = LOWER_BOUND;
    int upper_bound = UPPER_BOUND;
    int contentation_factor = 1;
    int max_speed = 10;
    int min_speed = -10;

    double atual_fitness;
    double best_fitness;


    std::vector<double> atual_position[DIM];
    std::vector<double> best_position[DIM];
    std::vector<double> speed_particle[DIM];

public:

    void genetate_initial_solution(){
        for(int i=0; i< DIM; i++){
            atual_position->push_back(std::rand() % 1201 - 600);
            speed_particle->push_back(0);
            best_position->push_back((*atual_position)[i]);
        }

    }
    

    void updateVelocity(std::vector<int>* best_global_position) {
        std::vector<double> vel_best[DIM];
        std::vector<double> vel_global_best[DIM];
        for(int i=0; i< DIM; i++){
            vel_best->push_back(sqrt((*best_position)[i]*(*best_position)[i] +  (*atual_position)[i]*(*atual_position)[i]));
            vel_global_best->push_back(sqrt((*best_global_position)[i]*(*best_global_position)[i] +  (*atual_position)[i]*(*atual_position)[i]));

            (*speed_particle)[i] += (*vel_best)[i] *contentation_factor +(*vel_global_best)[i]*contentation_factor;
            if ((*speed_particle)[i]> max_speed){
                (*speed_particle)[i] = max_speed;
            }
            if ((*speed_particle)[i]< min_speed){
                (*speed_particle)[i] = min_speed;
            }
        }

    }

    void update_position(){
        for(int i=0; i< DIM; i++){
            (*atual_position)[i] += (*speed_particle)[i];

            if((*atual_position)[i] > upper_bound){
                (*atual_position)[i] = upper_bound;
            }

            if((*atual_position)[i] < lower_bound){
                (*atual_position)[i] = lower_bound;
            }
        
        }

    }
  

    double fitness_1() {

        int top=0;
        int top1=0;
        int top2=1;
        for(int j=0;j<DIM;j++) {
            top1=top1+pow(((*atual_position)[j]),(double)2);
            top2=top2*cos(((((*atual_position)[j])/sqrt((double)(j+1)))*M_PI)/180);
            }

        top=(1/(double)4000)*top1-top2+1;

        atual_fitness = top;
        if (best_fitness < atual_fitness){
            best_fitness = atual_fitness;
            for(int i=0; i< DIM; i++){
                (*best_position)[i] = (*atual_position)[i];
            }

            
        }
        return top;
    }
    
    double fitness_2() {
        int aux = 0;
        int aux1 = 0;
        for (int i = 0; i < DIM; i++) {
            aux += (*atual_position)[i]*(*atual_position)[i];
        }
        for (int i = 0; i < DIM; i++){
            aux1 += cos(2.0*M_PI*(*atual_position)[i]);
        }
        atual_fitness = (-20.0*(exp(-0.2*sqrt(1.0/(float)DIM*aux)))-exp(1.0/(float)DIM*aux1)+20.0+exp(1));

        return (-20.0*(exp(-0.2*sqrt(1.0/(float)DIM*aux)))-exp(1.0/(float)DIM*aux1)+20.0+exp(1));
    }


    std::vector<double> getAtualPosition() {
        return *atual_position;
    }

    std::vector<double> getBestPosition() {
        return *best_position;
    }

    std::vector<double> getSpeedParticle() {
        return *speed_particle;
    }


};
