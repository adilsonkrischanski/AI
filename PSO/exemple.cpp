#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <thread>
#include <mutex>

const int NUM_PARTICLES = 20;
const int NUM_DIMENSIONS = 2;
const double LOWER_BOUND = -10.0;
const double UPPER_BOUND = 10.0;
const int MAX_ITERATIONS = 100;
const double INERTIA_WEIGHT = 0.7;
const double COGNITIVE_WEIGHT = 1.5;
const double SOCIAL_WEIGHT = 1.5;

std::mutex g_mutex;

double fitness(const std::vector<double>& position) {
    // Função de avaliação (fitness) - exemplo: função esfera (sphere function)
    double sum = 0.0;
    for (double coord : position) {
        sum += std::pow(coord, 2);
    }
    return sum;
}

class Particle {
public:
    Particle() {
        position_.resize(NUM_DIMENSIONS);
        velocity_.resize(NUM_DIMENSIONS);
        bestPosition_.resize(NUM_DIMENSIONS);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dist(LOWER_BOUND, UPPER_BOUND);

        for (int j = 0; j < NUM_DIMENSIONS; ++j) {
            position_[j] = dist(gen);
            velocity_[j] = dist(gen);
            bestPosition_[j] = position_[j];
        }

        bestFitness_ = fitness(position_);
    }

    void update(const std::vector<double>& globalBestPosition) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dist(0.0, 1.0);

        for (int i = 0; i < NUM_DIMENSIONS; ++i) {
            double r1 = dist(gen);
            double r2 = dist(gen);
            velocity_[i] = INERTIA_WEIGHT * velocity_[i]
                + COGNITIVE_WEIGHT * r1 * (bestPosition_[i] - position_[i])
                + SOCIAL_WEIGHT * r2 * (globalBestPosition[i] - position_[i]);

            position_[i] += velocity_[i];

            if (position_[i] < LOWER_BOUND) {
                position_[i] = LOWER_BOUND;
            }
            else if (position_[i] > UPPER_BOUND) {
                position_[i] = UPPER_BOUND;
            }
        }

        double currentFitness = fitness(position_);
        if (currentFitness < bestFitness_) {
            bestFitness_ = currentFitness;
            bestPosition_ = position_;
        }
    }

    double getBestFitness() const {
        return bestFitness_;
    }

    std::vector<double> getBestPosition() const {
        return bestPosition_;
    }

private:
    std::vector<double> position_;
    std::vector<double> velocity_;
    std::vector<double> bestPosition_;
    double bestFitness_;
};

class PSO {
public:
    PSO() {
        particles_.reserve(NUM_PARTICLES);
        for (int i = 0; i < NUM_PARTICLES; ++i) {
            particles_.push_back(Particle());
        }
    }

    void runPSO() {
        for (int iteration = 0; iteration < MAX_ITERATIONS; ++iteration) {
            std::vector<std::thread> threads;
            for (Particle& particle : particles_) {
                threads.emplace_back(&Particle::update, &particle, globalBestPosition_);
            }

            for (std::thread& thread : threads) {
                thread.join();
            }

            updateGlobalBest();
        }
    }

    std::vector<double> getGlobalBestPosition() const {
        return globalBestPosition_;
    }

private:
    std::vector<Particle> particles_;
    std::vector<double> globalBestPosition_;

    void updateGlobalBest() {
        double globalBestFitness = std::numeric_limits<double>::infinity();
        for (const Particle& particle : particles_) {
            double particleBestFitness = particle.getBestFitness();
            if (particleBestFitness < globalBestFitness) {
                globalBestFitness = particleBestFitness;
                globalBestPosition_ = particle.getBestPosition();
            }
        }
    }
};

class PSOManager {
public:
    std::vector<double> runPSO() {
        PSO pso;
        std::vector<std::thread> threads;

        for (int i = 0; i < NUM_PARTICLES; ++i) {
            threads.emplace_back(&PSO::runPSO, &pso);
        }

        for (std::thread& thread : threads) {
            thread.join();
        }

        return pso.getGlobalBestPosition();
    }
};

int main() {
    PSOManager psoManager;
    std::vector<double> bestPosition = psoManager.runPSO();

    std::cout << "Best position found:";
    for (double coord : bestPosition) {
        std::cout << " " << coord;
    }
    std::cout << std::endl;

    std::cout << "Best fitness value: " << fitness(bestPosition) << std::endl;

    return 0;
}
