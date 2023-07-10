#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>

#define MAX_ITERATIONS 100000
#define NUM_PARTICLES 50
#define NUM_DIMENSIONS 10
#define RANGE_MIN -32
#define RANGE_MAX 32
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
    return min + ((double)rand() / RAND_MAX) * (max - min);
}

double ackley_function(double x[], int num_dimensions) {
    // Função Ackley
    double sum_sq = 0.0;
    double sum_cos = 0.0;

    for (int j = 0; j < num_dimensions; j++) {
        sum_sq += x[j] * x[j];
        sum_cos += cos(2.0 * M_PI * x[j]);
    }

    double term1 = -20.0 * exp(-0.2 * sqrt(sum_sq / num_dimensions));
    double term2 = -exp(sum_cos / num_dimensions);
    double value = term1 + term2 + 20.0 + exp(1.0);

    return value;
}

void initialize_particle(Particle* particle) {
    for (int i = 0; i < NUM_DIMENSIONS; i++) {
        particle->position[i] = rand_range(RANGE_MIN, RANGE_MAX);
        particle->velocity[i] = 0.0;
    }
    particle->fitness = ackley_function(particle->position, NUM_DIMENSIONS);
    for (int i = 0; i < NUM_DIMENSIONS; i++) {
        particle->best_position[i] = particle->position[i];
    }
    particle->best_fitness = particle->fitness;
}

void update_particle(Particle* particle, double global_best_position[]) {
    for (int i = 0; i < NUM_DIMENSIONS; i++) {
        double r1 = rand_range(0, 1);
        double r2 = rand_range(0, 1);
        particle->velocity[i] = particle->velocity[i]
            + r1 * (particle->best_position[i] - particle->position[i])
            + r2 * (global_best_position[i] - particle->position[i]);
        particle->position[i] += particle->velocity[i];
    }

    particle->fitness = ackley_function(particle->position, NUM_DIMENSIONS);
    if (particle->fitness < particle->best_fitness) {
        for (int i = 0; i < NUM_DIMENSIONS; i++) {
            particle->best_position[i] = particle->position[i];
        }
        particle->best_fitness = particle->fitness;
    }
}

void update_particle2(Particle* particle, double global_best_position[]) {
    for (int i = 0; i < NUM_DIMENSIONS; i++) {
        double r1 = rand_range(0, 1);
        double r2 = rand_range(0, 1);
        particle->velocity[i] = INERTIA_WEIGHT * particle->velocity[i]
            + r1 * (particle->best_position[i] - particle->position[i])
            + r2 * (global_best_position[i] - particle->position[i]);
        particle->position[i] += particle->velocity[i];
    }

    particle->fitness = ackley_function(particle->position, NUM_DIMENSIONS);
    if (particle->fitness < particle->best_fitness) {
        for (int i = 0; i < NUM_DIMENSIONS; i++) {
            particle->best_position[i] = particle->position[i];
        }
        particle->best_fitness = particle->fitness;
    }
}

void update_particle3(Particle* particle, double global_best_position[]) {
    for (int i = 0; i < NUM_DIMENSIONS; i++) {
        double r1 = rand_range(0, 1);
        double r2 = rand_range(0, 1);
       particle->velocity[i] = INERTIA_WEIGHT * particle->velocity[i]
                            + COGNITIVE_WEIGHT * r1 * (particle->best_position[i] - particle->position[i])
                            + SOCIAL_WEIGHT * r2 * (global_best_position[i] - particle->position[i]);
     particle->position[i] += particle->velocity[i];
    }

    particle->fitness = ackley_function(particle->position, NUM_DIMENSIONS);
    if (particle->fitness < particle->best_fitness) {
        for (int i = 0; i < NUM_DIMENSIONS; i++) {
            particle->best_position[i] = particle->position[i];
        }
        particle->best_fitness = particle->fitness;
    }
}

std::string getOutputFileName(int experiment) {
    return "results_" + std::to_string(experiment) + ".txt";
}

int main() {
    Particle particles[NUM_PARTICLES];
    double global_best_position[NUM_DIMENSIONS];
    double global_best_fitness = INFINITY;

    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int experiment = 1; experiment <= 10; experiment++) {
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

        // Open the file for writing
        std::string fileName = getOutputFileName(experiment);
        std::ofstream file(fileName);

        // Run the PSO algorithm
        for (int i = 0; i < MAX_ITERATIONS; i++) {
            double sum_fitness = 0.0;

            for (int j = 0; j < NUM_PARTICLES; j++) {
                update_particle3(&particles[j], global_best_position);
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
            file << "Experiment " << experiment << ", Iteration " << i + 1 << ": Best Fitness = " << global_best_fitness << ", Average Fitness = " << average_fitness << std::endl;
        }

        // Close the file
        file.close();

        // Reset global best fitness for the next experiment
        global_best_fitness = INFINITY;
    }

    std::cout << "Optimization finished." << std::endl;

    return 0;
}
