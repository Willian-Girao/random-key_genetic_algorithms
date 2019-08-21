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
    int getLength(void);
    int getIndex(int index); /* Returns the index (node id) of a hallele within the chromosome. */
    double getFitness(void); /* Returns the fiteness value of a chromosome. */
    double getGene(int index); /* Returns the gene (random key) in the position 'index'. */    
    void printGenes(void); /* Prints the vector to the screen. */
    void calculateFitness(void); /* Evaluate the vector on the objective function. */
    void generateGenes(int chromosomeSize); /* Initializes the random keys of the chromosome. */
    void setResetGenes(Hallele * newGenes); /* Change the current hallele sequency for 'newGenes'. */
    void setFitness(double fit); /* Updates a chromosome fitness value. */ 
    void resetChromosome(void); /* Whipe cleans a chromosome - reset */
    Hallele * getChromosomeAsArray(void); /* Returns the raw structure of the solution array. */

  private:
    double fitness; /* Quality of the solution. */
    int length; /* Dimension of solution vector. */
    Hallele *genes; /* Raw array representing the solution. */
    void updateGene(int i, double key); /* Updates the key 'i' of the vector with the value 'key'. */
};

#endif
