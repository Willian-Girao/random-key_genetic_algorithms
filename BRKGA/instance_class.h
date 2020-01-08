#ifndef INSTANCE_H
#define INSTANCE_H

#include "chromosome_class.h"

using namespace std;

struct SolutionStruct { /* Structure used to evaluate the solution for the DMSP - Mr. Pablo's graph instance's structure based. */
    int node; //Node id.
    double key;
    double demand; //Node demand to be served.
};

struct EdgeData { /* Holds the information assiciated to 'w' edges - created due to presence of artificial node */
    int edge_label; /* Edge identifier */
    double start_x_axis; /* X-start coordiante in the plane */
    double start_y_axis; /* Y-start coordiante in the plane */
    double end_x_axis; /* X-end coordiante in the plane */
    double end_y_axis; /* Y-end coordiante in the plane */
    double length; /* length of the edge */
    int n_nodes_can_serve; /* Number of nodes that can be served while in this edge */
    int *ids_nodes_can_serve; /* Ids of the nodes that can be served while in this edge */
};

struct NodePairInfo { /* Holds the information (with artificial nodes) regarding two connected nodes */
    int pair_id = -1; /* Id of the refered two node's pair */
    double distance = -1.0; /* Distance between them */
    int n_edges_between = -1; /* Number of edges 'w' caused by presence of artifial nodes */
    EdgeData *edges_between_info; /* 'w' edges associated information */
};

struct Node { /* Data associated to a node */
    int label; /* Id that differentiates the nodes */
    double x_axis; /* X coordiante in the plane */
    double y_axis; /* Y coordiante in the plane */
    double c_range; /* Communication range */
    double t_rate; /* Transmition rate - amount of data it transfers per unit of time */
    double demmand; /* Information menaging demand */
    NodePairInfo *paired_with_nodes_info; /* Information regarding this node being connected to another node 'x' */
};

class Instance {
  public:
    /* Constructor and Destructor */
    Instance();
    ~Instance();

    /* Getters */
    int getNumberOfOriginalNodes(void); /* Gets the number of original nodes in the graph */
    int getNodesLabel(int index); /* Gets the label of a node indexed by 'index' */
    double getNodesX(int index); /* Gets the x coordinate of a node indexed by 'index' */
    double getNodesY(int index); /* Gets the y coordinate of a node indexed by 'index' */
    double getNodesCRange(int index); /* Gets the communication rang of a node indexed by 'index' */
    double getNodesTRate(int index); /* Gets the transmition rate of a node indexed by 'index' */
    double getNodesDemmand(int index); /* Gets the demmand of a node indexed by 'index' */
    double evaluateSolution(Hallele *solution, double muleVelocity, double skipeBSCheck); /* Set and returns the fitness value of a solution - evaluate on the problem. */
    double evalSolFromSolStructure(SolutionStruct *solution, double muleVelocity, bool skipDemandBreak);
    double evaluateBRKGA02Solution(SolutionStruct *solution, double muleVelocity, int sensorsOnRounte, bool skipDemandBreak);
    void printFinalSolution(Hallele *chromosome, double muleVelocity); /*  */
    Node getNode(int index); /* Gets the representation of a node indexed by 'index' */
    Node getBaseStation(); /* Gets the representation of the base station */
    SolutionStruct * buildSolutionStructure(Hallele *chromosome); /* Interface between RKGA solution vector and DMSP structure - Mr. Pablo's modeling based. */
    int checkCanInserSensor(SolutionStruct *sol, int sensor, int sensorsOnRoute);
    int findNextSensorOnRoute(SolutionStruct *sol, int sensor);

    /* Getters - Objective function evaluation helpers | AE - Artificial Edge | BP - Between Pairs' | Values regarding metadata between two consecutive nodes */
    int getNumberOfAEBP(int main_node_index, int pair_node_index); /* Returns the number of artificial edges */
    int getAENumberNodeCanBeServed(int main_node_index, int pair_node_index, int ae_index); /* Returns the number of nodes that can be served in 'ed_index' */
    double getDistanceBP(int main_node_index, int pair_node_index); /* Returns the distance */
    double getAExStartAxis(int main_node_index, int pair_node_index, int ae_index); /* Returns the x starting coordinate of 'ed_index' */
    double getAEyStartAxis(int main_node_index, int pair_node_index, int ae_index); /* Returns the y starting coordinate of 'ed_index' */
    double getAExEndAxis(int main_node_index, int pair_node_index, int ae_index); /* Returns the x ending coordinate of 'ed_index' */
    double getAEyEndAxis(int main_node_index, int pair_node_index, int ae_index); /* Returns the y ending coordinate of 'ed_index' */
    double getAELength(int main_node_index, int pair_node_index, int ae_index); /* Returns the length of 'ed_index' */
    bool canXbeServedInAE(int main_node_index, int pair_node_index, int ae_index, int x); /* Returns true if 'x' can be served in 'ed_index' - false otherwise */

    /* Mating New */
    double getGainAB(int A_index, int B_index); /* Returns the cost of the edge AB (total demand attended/distance travelled) - the bigger, the better.*/
    int findFinalBSIndex(SolutionStruct *solution);
    int findAXFromA(SolutionStruct *solution, int a);
    bool isInvalidSolution(double fitness);
    bool isntInSolution(SolutionStruct *solution, int a, int size);

    /* Setters */
    /* Sets number of possible speeds to be used */
    void setSpeedNumber(int speeds_count);
    /* Sets number of total original nodes - including the BS */
    void setOriginalNodesNumber(int orig_nodes_n);
    /* Sets number of total nodes - after pre-processing */
    void setTotalNodesNumber(int total_nodes);
    /* Sets the properties of the node indexed by 'index' */
    void setNode(int index, double x, double y, double c_range, double t_rate, double demmand);
    /* Sets the value of the i-th possible speed */
    void setSpeed(int i, double x);
    /* Sets the x axis of the node indexd by 'index' */
    void setNodeX(int index, double x);
    /* Sets the y axis of the node indexd by 'index' */
    void setNodeY(int index, double y);
    /* Sets the communication range of the node indexd by 'index' */
    void setNodeCRange(int index, double c_range);
    /* Sets the transmission rate of the node indexd by 'index' */
    void setNodeTRate(int index, double t_rate);
    /* Sets the demmand of the node indexd by 'index' */
    void setNodeDemmand(int index, double demmand);
    /* Sets up information associated to a pair of nodes in the file - [int main_node_id, int pair_node_id, double distance, int artificial_edges_between] */
    void setNodePair(int value_index, double value, int &main_node_index, int &pair_node_index, bool &is_parsing_artificial_info, int &artifial_edge_info_counter, bool &done);
    /* Sets up the meta-information associated to a pair of nodes */
    void setNodePairEdgeData(int value_index, double value, int &main_node_index, int &pair_node_index, bool &is_parsing_artificial_info, int &artifial_edge_info_counter, int &nodes_can_be_served_counter);
    /* Used in pre-processing to reset structures of edges between pairs of nodes */
    void resetEdgesBetweenInfo(int main_node_index, int pair_node_index, int value);
    /* Used in pre-processing to reset structures of ids served in artificial edges between pairs of nodes */
    void resetIdsCanbeServed(int main_node_index, int pair_node_index, int value, int artificial_edge_pointer_index_counter);
    void setTotalDemand();

    /* Helpers */
    void printNode(int index); /* Prints the informations of a node indexed by 'index' */
    void printSpeeds(void); /* Prints the allowed speed's values */
    void printInstanceMetadata(void); /* Prints all the metadata associated with the graph */
    void pauseExecution(int line, string str); /* Pauses the execution of the program for debbuging purposes */
    void printPairsRelatedInfo(void); /* Prints all the metadata associated all pairs of original nodes */

  private:
    int original_nodes_n; /* Number of nodes in the original graph */
    int total_nodes_n; /* Number of nodes in the original alterated graph (original nodes + fictious ones) */
    int speeds_n; /* Number of nodes in the original graph */
    int total_demand; /* Total demand to be met. */
    double *speeds; /* 'List' of 'doubles' Values of the possible speeds */
    Node *original_nodes; /* 'List' of 'Nodes' with the descriptions of the nodes */
};

#endif
