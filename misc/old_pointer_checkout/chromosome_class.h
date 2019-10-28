#ifndef CHROMOSOME_H
#define CHROMOSOME_H

using namespace std;

struct Hallele {
  double key;
  int index;
};

class Chromosome {

  friend class Population;

  public:
    Chromosome();
    double getFitness(void); /* Returns the fiteness value of a chromosome. */
    double getGene(int index); /* Returns the gene (random key) in the position 'index'. */
    void printGenes(void); /* Prints the vector to the screen. */
    void calculateFitness(void); /* Evaluate the vector on the objective function. */

  private:
    void setFitness(double fit); /* Updates a chromosome fitness value. */
    void generateGenes(void); /* Initializes the random keys of the chromosome. */
    void updateGene(int i, double key); /* Updates the key 'i' of the vector with the value 'key'. */
    double fitness;
    array<double,5> genes;
};

#endif
