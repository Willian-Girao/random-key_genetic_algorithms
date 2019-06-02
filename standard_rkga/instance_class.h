#ifndef INSTANCE_H
#define INSTANCE_H

using namespace std;

struct Node { /* Data associated to a node */
    int label; /* Id that differentiates the nodes */
    double x_axis; /* X coordiante in the plane */
    double y_axis; /* Y coordiante in the plane */
    double c_range; /* Communication range */
    double t_rate; /* Transmition rate */
    double demmand; /* Information menaging demand */
};

class Instance {
  public:
    /*
     orig_nodes_n: number of original nodes
     total_nodes: number of total nodes after graphs pre-processing
     speeds_count: number of allowed speeds
    */
    Instance(int orig_nodes_n, int total_nodes, int speeds_count);

    /* Getters */
    int getNodesLabel(int index); /* Gets the label of a node indexed by 'index' */
    double getNodesX(int index); /* Gets the x coordinate of a node indexed by 'index' */
    double getNodesY(int index); /* Gets the y coordinate of a node indexed by 'index' */
    double getNodesCRange(int index); /* Gets the communication rang of a node indexed by 'index' */
    double getNodesTRate(int index); /* Gets the transmition rate of a node indexed by 'index' */
    double getNodesDemmand(int index); /* Gets the demmand of a node indexed by 'index' */
    void printNode(int index); /* Prints the informations of a node indexed by 'index' */
    void printSpeeds(void); /* Prints the allowed speed's values */
    Node getNode(int index); /* Gets the representation of a node indexed by 'index' */
    Node getBaseStation(); /* Gets the representation of the base station */

    /* Setters */
    void setNode(int index, double x, double y, double c_range, double t_rate, double demmand); /* Sets the properties of the node indexed by 'index' */
    void setSpeed(int i, double x); /* Sets the value of the i-th possible speed */

  private:
    int original_nodes_n; /* Number of nodes in the original graph */
    int total_nodes_n; /* Number of nodes in the original alterated graph (original nodes + fictious ones) */
    int speeds_n; /* Number of nodes in the original graph */
    double *speeds; /* 'List' of 'doubles' Values of the possible speeds */
    Node *original_nodes; /* 'List' of 'Nodes' with the descriptions of the nodes */
};

#endif
