#include <iostream>
#include <array>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Chromosome {
  public:
    double getFitness(void);
    void printGenes(void);
    void calculateFitness(void);
    Chromosome();

  private:
    void setFitness(double fit);
    void generateGenes();
    double fitness;
    array<double,5> genes;
};

Chromosome::Chromosome() {
  fitness = 0.0;
  generateGenes();
}

/* Private methods */

void Chromosome::setFitness(double fit) {
  fitness = fit;
}

void Chromosome::generateGenes() {
  for (size_t i = 0; i < genes.size(); i++) {
    double key = ((double) rand() / RAND_MAX);
    while (key == 1.0) {
      key = ((double) rand() / RAND_MAX);
    }
    genes[i] = key;
  }
}

/* Mutation actually has to be a method of the class representing the
  evolution of the solution process: mutation on RKGA is achived by
  introducing a set o randomly generated (new) random key vectors. */

/* Public methods */

double Chromosome::getFitness(void) {
  return fitness;
}

void Chromosome::calculateFitness(void) {
  double updatedFitness = 0.0;
  // get chromosome genes here and evaluate the objective funtion (that should be passed as argument)
  setFitness(updatedFitness);
}

void Chromosome::printGenes(void) {
  for (size_t i = 0; i < genes.size(); i++) {
    cout << genes[i] << endl;
  }
}



int main() {
  srand (time(NULL));
  Chromosome chromosome;

  cout << "Current fitness: " << chromosome.getFitness() << endl;
  cout << "\n" << endl;
  chromosome.printGenes();
  return 0;
}
