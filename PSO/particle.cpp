#include <vector>
#include <random>

#define DIM 10

#define LOWER_BOUND -600
#define UPPER_BOUND 600

class Particle {
    private :
    int lower_bound = LOWER_BOUND;
    int upper_bound = UPPER_BOUND;
    int contentaion_factor = 1;
    int max_speed = 10;
    int min_speed = 10;

    double atual_fitness;
    
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

            (*speed_particle)[i] += (*vel_best)[i] *contentaion_factor +(*vel_global_best)[i]*contentaion_factor;
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

    void updateBest(std::vector<int>* best_global_position) {
        for (int i = 0; i < DIM; ++i){
            (*best_position)[i] = (*best_global_position)[i];
        }
    }
  

    double fitness() {
      
    }


};
