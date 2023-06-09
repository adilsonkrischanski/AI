#include <iostream>
#include <vector>
#include <random>
#include <cmath>

// Função de aptidão (objetivo) a ser minimizada (Griewank)
double objectiveFunction(const std::vector<double>& x) {
    double sum = 0.0;
    double product = 1.0;
    for (int i = 0; i < x.size(); i++) {
        sum += x[i] * x[i];
        product *= std::cos(x[i] / std::sqrt(i + 1));
    }
    return 1 + sum / 4000 - product;
}

// Estrutura de uma partícula
struct Particle {
    std::vector<double> position;
    std::vector<double> velocity;
    std::vector<double> bestPosition;
    double bestFitness;
};

// Parâmetros do algoritmo PSO
const int numParticles = 20;
const int numDimensions = 10;
const int maxIterations = 10000;
const double c1 = 2.0;   // Fator de aceleração cognitiva
const double c2 = 2.0;   // Fator de aceleração social
const double w = 0.7;    // Inércia
const double searchSpaceMin = -600.0;
const double searchSpaceMax = 600.0;

int main() {
    // Inicialização do gerador de números aleatórios
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distribution(searchSpaceMin, searchSpaceMax);

    // Inicialização das partículas
    std::vector<Particle> particles(numParticles);
    for (int i = 0; i < numParticles; i++) {
        particles[i].position.resize(numDimensions);
        particles[i].velocity.resize(numDimensions);
        particles[i].bestPosition.resize(numDimensions);
        particles[i].bestFitness = std::numeric_limits<double>::max();
        
        for (int j = 0; j < numDimensions; j++) {
            particles[i].position[j] = distribution(gen);
            particles[i].velocity[j] = 0.0;
            particles[i].bestPosition[j] = particles[i].position[j];
        }
        
        double fitness = objectiveFunction(particles[i].position);
        if (fitness < particles[i].bestFitness) {
            particles[i].bestFitness = fitness;
            particles[i].bestPosition = particles[i].position;
        }
    }
    
    std::vector<double> globalBestPosition = particles[0].bestPosition;
    double globalBestFitness = particles[0].bestFitness;

    // Execução do algoritmo PSO
    for (int iteration = 0; iteration < maxIterations; iteration++) {
        for (int i = 0; i < numParticles; i++) {
            for (int j = 0; j < numDimensions; j++) {
                double r1 = distribution(gen);
                double r2 = distribution(gen);
                
                particles[i].velocity[j] = w * particles[i].velocity[j] +
                                           c1 * r1 * (particles[i].bestPosition[j] - particles[i].position[j]) +
                                           c2 * r2 * (globalBestPosition[j] - particles[i].position[j]);
                                           
                particles[i].position[j] += particles[i].velocity[j];
                particles[i].position[j] = std::max(std::min(particles[i].position[j], searchSpaceMax), searchSpaceMin);
            }
            
            double fitness = objectiveFunction(particles[i].position);
            if (fitness < particles[i].bestFitness) {
                particles[i].bestFitness = fitness;
                particles[i].bestPosition = particles[i].position;
            }
            
            if (fitness < globalBestFitness) {
                globalBestFitness = fitness;
                globalBestPosition = particles[i].position;
            }
        }
    }

    // Resultados
    std::cout << "Melhor solução encontrada:" << std::endl;
    std::cout << "Posição: ";
    for (int i = 0; i < numDimensions; i++) {
        std::cout << globalBestPosition[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Aptidão: " << globalBestFitness << std::endl;

    return 0;
}
