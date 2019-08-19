#ifndef CHROMOSOME_H
#define CHROMOSOME_H

using namespace std;

struct Hallele {
  double key;
  int index;
  // double demand;
};

class Chromosome {

  friend class Population;

  public:
    Chromosome();
    double getFitness(void); /* Returns the fiteness value of a chromosome. */
    double getGene(int index); /* Returns the gene (random key) in the position 'index'. */
    void printGenes(void); /* Prints the vector to the screen. */
    void calculateFitness(void); /* Evaluate the vector on the objective function. */
    void generateGenes(int chromosomeSize); /* Initializes the random keys of the chromosome. */
    // bool updateDemand(int ind, double demand);
    
    Hallele * getChromosomeAsArray(void);
    void resetChromosome(void); /* Whipe cleans a chromosome - reset */

  private:
    void setFitness(double fit); /* Updates a chromosome fitness value. */    
    void updateGene(int i, double key); /* Updates the key 'i' of the vector with the value 'key'. */
    double fitness;
    int length;
    Hallele *genes;
};

#endif
