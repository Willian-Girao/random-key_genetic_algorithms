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
    array<int,2> pair_ids; /* Ids of the refered two nodes */
    double distance; /* Distance between them */
    int n_edges_between; /* Number of edges 'w' caused by presence of artifial nodes */
    EdgeData *edges_between_info; /* 'w' edges associated information */
};

class Instance {
  public:
    Instance();

    /* Getters */
    int getNodesLabel(int index); /* Gets the label of a node indexed by 'index' */
    double getNodesX(int index); /* Gets the x coordinate of a node indexed by 'index' */
    double getNodesY(int index); /* Gets the y coordinate of a node indexed by 'index' */
    double getNodesCRange(int index); /* Gets the communication rang of a node indexed by 'index' */
    double getNodesTRate(int index); /* Gets the transmition rate of a node indexed by 'index' */
    double getNodesDemmand(int index); /* Gets the demmand of a node indexed by 'index' */
    int getNumberOfOriginalNodes(void); /* Gets the number of original nodes in the graph */
    Node getNode(int index); /* Gets the representation of a node indexed by 'index' */
    Node getBaseStation(); /* Gets the representation of the base station */

    /* Setters */
    void setSpeedNumber(int speeds_count);
    void setOriginalNodesNumber(int orig_nodes_n);
    void setTotalNodesNumber(int total_nodes);
    void setNode(int index, double x, double y, double c_range, double t_rate, double demmand); /* Sets the properties of the node indexed by 'index' */
    void setSpeed(int i, double x); /* Sets the value of the i-th possible speed */
    void setNodeX(int index, double x);
    void setNodeY(int index, double y);
    void setNodeCRange(int index, double c_range);
    void setNodeTRate(int index, double t_rate);
    void setNodeDemmand(int index, double demmand);

    /* Helpers */
    void printNode(int index); /* Prints the informations of a node indexed by 'index' */
    void printSpeeds(void); /* Prints the allowed speed's values */
    void printInstanceMetadata(void); /* Prints all the metadata associated with the graph */

  private:
    int original_nodes_n; /* Number of nodes in the original graph */
    int total_nodes_n; /* Number of nodes in the original alterated graph (original nodes + fictious ones) */
    int speeds_n; /* Number of nodes in the original graph */
    double *speeds; /* 'List' of 'doubles' Values of the possible speeds */
    Node *original_nodes; /* 'List' of 'Nodes' with the descriptions of the nodes */
};

#endif
