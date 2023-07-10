#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>

#define MAX_ITERATIONS 100000
#define NUM_PARTICLES 50
#define NUM_DIMENSIONS 20
#define RANGE_MIN -600
#define RANGE_MAX 600
#define INERTIA_WEIGHT 0.7
#define COGNITIVE_WEIGHT 1.4
#define SOCIAL_WEIGHT 1.4

struct Particle {
    double position[NUM_DIMENSIONS];
    double velocity[NUM_DIMENSIONS];
    double fitness;
    double best_position[NUM_DIMENSIONS];
    double best_fitness;
};

double rand_range(double min, double max) {
    return min + ((double) rand() / RAND_MAX) * (max - min);
}

double objective_function(double x[], int num_dimensions) {
    // Objective function (example: Rastrigin function)
    double top = 0;
    double top1 = 0;
    double top2 = 1;
    for (int j = 0; j < num_dimensions; j++) {
        top1 = top1 + pow(x[j], 2.0);
        top2 = top2 * cos(((x[j] / sqrt(static_cast<double>(j + 1))) * M_PI) / 180.0);
    }
    top = (1.0 / 4000.0) * top1 - top2 + 1.0;

    return top;
}

void initialize_particle(Particle *particle) {
    for (int i = 0; i < NUM_DIMENSIONS; i++) {
        particle->position[i] = rand_range(RANGE_MIN, RANGE_MAX);
        particle->velocity[i] = 0.0;
    }
    particle->fitness = objective_function(particle->position, NUM_DIMENSIONS);
    for (int i = 0; i < NUM_DIMENSIONS; i++) {
        particle->best_position[i] = particle->position[i];
    }
    particle->best_fitness = particle->fitness;
}

// void update_particle(Particle *particle, double global_best_position[]) {
//     for (int i = 0; i < NUM_DIMENSIONS; i++) {
//         double r1 = rand_range(0, 1);
//         double r2 = rand_range(0, 1);
//         particle->velocity[i] = particle->velocity[i]
//                                 + r1 * (particle->best_position[i] - particle->position[i])
//                                 + r2 * (global_best_position[i] - particle->position[i]);
//         particle->position[i] += particle->velocity[i];
//     }
    
//     particle->fitness = objective_function(particle->position, NUM_DIMENSIONS);
//     if (particle->fitness < particle->best_fitness) {
//         for (int i = 0; i < NUM_DIMENSIONS; i++) {
//             particle->best_position[i] = particle->position[i];
//         }
//         particle->best_fitness = particle->fitness;
//     }
// }

// void update_particle(Particle *particle, double global_best_position[]) {
//     for (int i = 0; i < NUM_DIMENSIONS; i++) {
//         double r1 = rand_range(0, 1);
//         double r2 = rand_range(0, 1);
//         particle->velocity[i] = INERTIA_WEIGHT * particle->velocity[i]
//                                 + COGNITIVE_WEIGHT * r1 * (particle->best_position[i] - particle->position[i])
//                                 + SOCIAL_WEIGHT * r2 * (global_best_position[i] - particle->position[i]);
//         particle->position[i] += particle->velocity[i];
//     }
    
//     particle->fitness = objective_function(particle->position, NUM_DIMENSIONS);
//     if (particle->fitness < particle->best_fitness) {
//         for (int i = 0; i < NUM_DIMENSIONS; i++) {
//             particle->best_position[i] = particle->position[i];
//         }
//         particle->best_fitness = particle->fitness;
//     }
// }

void update_particle(Particle *particle, double global_best_position[]) {
    for (int i = 0; i < NUM_DIMENSIONS; i++) {
        double r1 = rand_range(0, 1);
        double r2 = rand_range(0, 1);
        particle->velocity[i] = INERTIA_WEIGHT * particle->velocity[i]
                                + r1 * (particle->best_position[i] - particle->position[i])
                                + r2 * (global_best_position[i] - particle->position[i]);
        particle->position[i] += particle->velocity[i];
    }
    
    particle->fitness = objective_function(particle->position, NUM_DIMENSIONS);
    if (particle->fitness < particle->best_fitness) {
        for (int i = 0; i < NUM_DIMENSIONS; i++) {
            particle->best_position[i] = particle->position[i];
        }
        particle->best_fitness = particle->fitness;
    }
}

int main() {
    for (int k = 0; k < 10; k++) {
        Particle particles[NUM_PARTICLES];
        double global_best_position[NUM_DIMENSIONS];
        double global_best_fitness = INFINITY;

        // Seed the random number generator
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        // Initialize particles
        for (int i = 0; i < NUM_PARTICLES; i++) {
            initialize_particle(&particles[i]);
            if (particles[i].best_fitness < global_best_fitness) {
                for (int j = 0; j < NUM_DIMENSIONS; j++) {
                    global_best_position[j] = particles[i].best_position[j];
                }
                global_best_fitness = particles[i].best_fitness;
            }
        }

        // Create the filename
        std::string filename = "results_" + std::to_string(k) + ".txt";

        // Open the file for writing
        std::ofstream file(filename);
        if (file.is_open()) {
            // Run the PSO algorithm
            for (int i = 0; i < MAX_ITERATIONS; i++) {
                double sum_fitness = 0.0;

                for (int j = 0; j < NUM_PARTICLES; j++) {
                    update_particle(&particles[j], global_best_position);
                    if (particles[j].best_fitness < global_best_fitness) {
                        for (int k = 0; k < NUM_DIMENSIONS; k++) {
                            global_best_position[k] = particles[j].best_position[k];
                        }
                        global_best_fitness = particles[j].best_fitness;
                    }

                    sum_fitness += particles[j].best_fitness;
                }

                // Calculate the average fitness
                double average_fitness = sum_fitness / NUM_PARTICLES;

                // Write the results to the file
                file << "Iteration " << i + 1 << ": Best Fitness = " << global_best_fitness << ", Average Fitness = " << average_fitness << std::endl;
            }

            // Close the file
            file.close();

            std::cout << "Optimization finished for " << filename << std::endl;
            std::cout << "Global Best Fitness = " << global_best_fitness << std::endl;
            std::cout << "Global Best Position:" << std::endl;
            for (int i = 0; i < NUM_DIMENSIONS; i++) {
                std::cout << global_best_position[i] << " ";
            }
            std::cout << std::endl;
        } else {
            std::cout << "Error opening file: " << filename << std::endl;
        }
    }

    return 0;
}
