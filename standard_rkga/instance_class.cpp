#include <iostream>
#include <array>
#include <stdlib.h>
#include <fstream>
#include <string>

#include "instance_class.h"
#include "quicksort.cpp"

using namespace std;

/* Public methods */
Instance::Instance() {}

Instance::~Instance() {
  delete []speeds;  
  // delete []original_nodes->paired_with_nodes_info->edges_between_info->ids_nodes_can_serve;
  // delete []original_nodes->paired_with_nodes_info->edges_between_info;
  // delete []original_nodes->paired_with_nodes_info;
  delete []original_nodes;
  cout << "\n> Instance object terminated" << endl;
}

/* Sets number of total nodes - after pre-processing */
void Instance::setTotalNodesNumber(int total_nodes) {
  total_nodes_n = total_nodes;
  return;
}

/* Used in pre-processing to reset structures of edges between pairs of nodes */
void Instance::resetEdgesBetweenInfo(int main_node_index, int pair_node_index, int value) {
  // Initializing data struct to hold information regarding to artificial edges (segmented due to the presence of an artidial vertex)
  original_nodes[main_node_index].paired_with_nodes_info[pair_node_index].edges_between_info = new EdgeData[value];

  // Setting artificial edge structures
  for (int k = 0; k < value; ++k)
  {
    EdgeData artificial_edge_k;

    artificial_edge_k.edge_label = k+1;
    artificial_edge_k.start_x_axis = -1.0;
    artificial_edge_k.start_y_axis = -1.0;
    artificial_edge_k.end_x_axis = -1.0;
    artificial_edge_k.end_y_axis = -1.0;
    artificial_edge_k.length = -1.0;
    artificial_edge_k.n_nodes_can_serve = original_nodes_n;

    // Setting temporary ids that can be served
    artificial_edge_k.ids_nodes_can_serve = new int[original_nodes_n];        
    for (int l = 0; l < original_nodes_n; ++l)
    {
      artificial_edge_k.ids_nodes_can_serve[l] = -1;
    }

    original_nodes[main_node_index].paired_with_nodes_info[pair_node_index].edges_between_info[k] = artificial_edge_k;
  }

  return;
}

/* Used in pre-processing to reset structures of ids served in artificial edges between pairs of nodes */
void Instance::resetIdsCanbeServed(int main_node_index, int pair_node_index, int value, int artificial_edge_pointer_index_counter) {
  original_nodes[main_node_index].paired_with_nodes_info[pair_node_index].edges_between_info[artificial_edge_pointer_index_counter].ids_nodes_can_serve = new int[value];
  for (int i = 0; i < value; ++i)
  {
    original_nodes[main_node_index].paired_with_nodes_info[pair_node_index].edges_between_info[artificial_edge_pointer_index_counter].ids_nodes_can_serve[i] = -1;
  }
}

/* Sets number of total original nodes - including the BS */
void Instance::setOriginalNodesNumber(int orig_nodes_n) {
  original_nodes_n = orig_nodes_n;
  original_nodes = new Node[original_nodes_n];

  for (int i = 0; i < original_nodes_n; ++i)
  {
    // Setting node structure
    Node node_i;

    node_i.label = i;
    node_i.x_axis = -1.0;
    node_i.y_axis = -1.0;
    node_i.c_range = -1.0;
    node_i.t_rate = -1.0; 
    node_i.demmand = -1.0;

    // Setting node->pair structures
    node_i.paired_with_nodes_info = new NodePairInfo[orig_nodes_n];
    for (int j = 0; j < original_nodes_n; ++j)
    {
      NodePairInfo pair_j;

      pair_j.pair_id = j;
      pair_j.distance = -1.0;
      pair_j.n_edges_between = 1; // Has to be reset when parsing line
      pair_j.edges_between_info = new EdgeData[1]; // Has to be reset when parsing line

      // Setting artificial edge structures
      for (int k = 0; k < 1; ++k)
      {
        EdgeData artificial_edge_k;

        artificial_edge_k.edge_label = k+1;
        artificial_edge_k.start_x_axis = -1.0;
        artificial_edge_k.start_y_axis = -1.0;
        artificial_edge_k.end_x_axis = -1.0;
        artificial_edge_k.end_y_axis = -1.0;
        artificial_edge_k.length = -1.0;
        artificial_edge_k.n_nodes_can_serve = original_nodes_n;

        // Setting temporary ids that can be served
        artificial_edge_k.ids_nodes_can_serve = new int[original_nodes_n];        
        for (int l = 0; l < original_nodes_n; ++l)
        {
          artificial_edge_k.ids_nodes_can_serve[l] = -1;
        }

        pair_j.edges_between_info[k] = artificial_edge_k;
      }

      node_i.paired_with_nodes_info[j] = pair_j;
    }

    original_nodes[i] = node_i;
  }

  return;
}

/* Sets number of possible speeds to be used */
void Instance::setSpeedNumber(int speeds_count) {
  speeds_n = speeds_count;
  speeds = new double[speeds_n];

  for (int i = 0; i < speeds_n; ++i)
  {
    speeds[i] = 1.0;
  }

  return;
}

/* Sets the value of the i-th possible speed to 's' */
void Instance::setSpeed(int i, double s) {
  if (i < 0 || i == speeds_n)
  {
    return;
  }

  (*(speeds + i)) = s;

  return;
}

/* Gets the label of a node indexed by 'index' */
int Instance::getNodesLabel(int index) {
  if (index < 0 || index == original_nodes_n)
  {
    return (*(original_nodes)).label;
  }
  return (*(original_nodes + index)).label;
}

/* Gets the x coordinate of a node indexed by 'index' */
double Instance::getNodesX(int index) {
  if (index < 0 || index == original_nodes_n)
  {
    return (*(original_nodes)).x_axis;
  }
  return (*(original_nodes + index)).x_axis;
}

/* Gets the y coordinate of a node indexed by 'index' */
double Instance::getNodesY(int index) {
  if (index < 0 || index == original_nodes_n)
  {
    return (*(original_nodes)).y_axis;
  }
  return (*(original_nodes + index)).y_axis;
}

/* Gets the communication rang of a node indexed by 'index' */
double Instance::getNodesCRange(int index) {
  if (index < 0 || index == original_nodes_n)
  {
    return (*(original_nodes)).c_range;
  }
  return (*(original_nodes + index)).c_range;
}

/* Gets the transmition rate of a node indexed by 'index' */
double Instance::getNodesTRate(int index) {
  if (index < 0 || index == original_nodes_n)
  {
    return (*(original_nodes)).t_rate;
  }
  return (*(original_nodes + index)).t_rate;
}

/* Gets the demmand of a node indexed by 'index' */
double Instance::getNodesDemmand(int index) {
  if (index < 0 || index == original_nodes_n)
  {
    return (*(original_nodes)).demmand;
  }
  return (*(original_nodes + index)).demmand;
}

/* Gets the representation of a node indexed by 'index' */
Node Instance::getNode(int index) {
  if (index < 0 || index == original_nodes_n)
  {
    return (*(original_nodes));
  }
  return (*(original_nodes + index));
}

/* Gets the representation of the base station */
Node Instance::getBaseStation() {
  return (*(original_nodes));
}

/* Prints the informations of a node indexed by 'index' */
void Instance::printNode(int index) {
  if (index < 0 || index == original_nodes_n)
  {
    return;
  }

  cout << "Label: " << (*(original_nodes + index)).label << endl << endl;
  cout << "X component: " << (*(original_nodes + index)).x_axis << endl;
  cout << "Y component: " << (*(original_nodes + index)).y_axis << endl;
  cout << "Communication range: " << (*(original_nodes + index)).c_range << endl;
  cout << "Transmition rate: " << (*(original_nodes + index)).t_rate << endl;
  cout << "Demmand: " << (*(original_nodes + index)).demmand << endl << endl;

  return;
}

/* Prints the allowed speed's values */
void Instance::printSpeeds(void) {
  cout << endl;
  for (int i = 0; i < speeds_n; ++i)
  {
    cout << "Speed " << i << ": " << (*(speeds + i)) << endl;
  }
  cout << endl;

  return;
}

/* Sets the properties of the node indexed by 'index' */
void Instance::setNode(int index, double x, double y, double c_range, double t_rate, double demmand) {
  if (index < 0 || index == original_nodes_n)
  {
    return;
  }

  (*(original_nodes + index)).x_axis = x;
  (*(original_nodes + index)).y_axis = y;
  (*(original_nodes + index)).c_range = c_range;
  (*(original_nodes + index)).t_rate = t_rate; 
  (*(original_nodes + index)).demmand = demmand;

  return;
}

/* Sets the x axis of the node indexd by 'index' */
void Instance::setNodeX(int index, double x) {
  if (index < 0 || index == original_nodes_n)
  {
    return;
  }

  original_nodes[index].x_axis = x;

  return;
}

/* Sets the y axis of the node indexd by 'index' */
void Instance::setNodeY(int index, double y) {
  if (index < 0 || index == original_nodes_n)
  {
    return;
  }

  original_nodes[index].y_axis = y;

  return;
}

/* Sets the communication range of the node indexd by 'index' */
void Instance::setNodeCRange(int index, double c_range) {
  if (index < 0 || index == original_nodes_n)
  {
    return;
  }

  original_nodes[index].c_range = c_range;

  return;
}

/* Sets the transmission rate of the node indexd by 'index' */
void Instance::setNodeTRate(int index, double t_rate) {
  if (index < 0 || index == original_nodes_n)
  {
    return;
  }

  original_nodes[index].t_rate = t_rate;

  return;
}

/* Sets the demmand of the node indexd by 'index' */
void Instance::setNodeDemmand(int index, double demmand) {
  if (index < 0 || index == original_nodes_n)
  {
    return;
  }

  original_nodes[index].demmand = demmand;

  return;
}

/* Prints all the metadata associated with the graph */
void Instance::printInstanceMetadata(void) {
  cout << "\nOriginal nodes: " << original_nodes_n << endl;
  cout << "Total nodes: " << total_nodes_n << endl;
  cout << "Number of speeds: " << speeds_n << endl;
  
  cout << "Speeds values: ";
  for (int i = 0; i < speeds_n; ++i)
  {
    if (i == (speeds_n - 1))
    {
      cout << (*(speeds + i));
    } else
    {
      cout << (*(speeds + i)) << ", ";
    }
  }
  cout << endl;

  cout << "Original nodes information: " << endl << endl;
  cout << "   label - [x component, y component, communication range, transmition rate, demmand]" << endl;
  for (int index = 0; index < original_nodes_n; ++index)
  {
    cout << "   " << (*(original_nodes + index)).label << " - " << "[" << (*(original_nodes + index)).x_axis << ", " << (*(original_nodes + index)).y_axis << ", " << (*(original_nodes + index)).c_range << ", " << (*(original_nodes + index)).t_rate << ", " << (*(original_nodes + index)).demmand << " ]" << endl;
  }

  return;
}

/* Gets the number of original nodes in the graph */
int Instance::getNumberOfOriginalNodes(void) {
  return original_nodes_n;
}

/* Sets up information associated to a pair of nodes in the file - [int main_node_id, int pair_node_id, double distance, int artificial_edges_between] */
void Instance::setNodePair(int value_index, double value, int &main_node_index, int &pair_node_index, bool &is_parsing_artificial_info, int &artifial_edge_info_counter, bool &done) {  
  switch(value_index) {
    case 0 :
      // ID of the current main node of the pair - should be equal to 'main_node_index'
      main_node_index = int(value);      
      break;
    case 1 :
      // ID of the node being paired with the main node - should be equal to 'pair_node_index'
      pair_node_index = int(value);
      original_nodes[main_node_index].paired_with_nodes_info[pair_node_index].pair_id = int(value);
      break;
    case 2 :
      // Distance between the two nodes
      original_nodes[main_node_index].paired_with_nodes_info[pair_node_index].distance = value;
      break;
    case 3 :
      // Number of artificial edges (segments of the original edge) between the two nodes
      original_nodes[main_node_index].paired_with_nodes_info[pair_node_index].n_edges_between = int(value); // Setting number of artificial edges (segmentation of an original edge)
      
      resetEdgesBetweenInfo(main_node_index, pair_node_index, int(value)); // Initializing data struct to hold information regarding to artificial edges (segmented due to the presence of an artidial vertex)

      if (int(value) > 0) // There is information regarding the artificial edges to be processed
      {
        is_parsing_artificial_info = true;        
      } else 
      {
        // There is no artificial edge information -> no change in the line controlling parameters required
      }
      if (main_node_index == (getNumberOfOriginalNodes()-1) && pair_node_index == (getNumberOfOriginalNodes()-1))
      {
        done = true;        
      }
      artifial_edge_info_counter = int(value); // Value will be decreased while parsing artificial info in order to know the list positioning of the i-th artificial edge data
      break;
    default :
      pauseExecution(288,"WARNING - Uncaught case in 'instance_class.cpp'.");
      break;
  }
}

void Instance::setNodePairEdgeData(int value_index, double value, int &main_node_index, int &pair_node_index, bool &is_parsing_artificial_info, int &artifial_edge_info_counter, int &nodes_can_be_served_counter) {
  if (main_node_index == (getNumberOfOriginalNodes()-1) && pair_node_index == (getNumberOfOriginalNodes()-1))
  {
    return;
  }
  int total_artificial_edges = original_nodes[main_node_index].paired_with_nodes_info[pair_node_index].n_edges_between;
  int artificial_edge_pointer_index_counter = (total_artificial_edges - artifial_edge_info_counter); // Value starts as '0' and increases until it reaches...
  switch(value_index) {
    case 0 :
      // Artificial edge "label"
      original_nodes[main_node_index].paired_with_nodes_info[pair_node_index].edges_between_info[artificial_edge_pointer_index_counter].edge_label = int(value);
      break;
    case 1 :
      // Artificial edge starting node x axis
      original_nodes[main_node_index].paired_with_nodes_info[pair_node_index].edges_between_info[artificial_edge_pointer_index_counter].start_x_axis = value;
      break;
    case 2 :
      // Artificial edge starting node y axis
      original_nodes[main_node_index].paired_with_nodes_info[pair_node_index].edges_between_info[artificial_edge_pointer_index_counter].start_y_axis = value;
      break;
    case 3 :
      // Artificial edge ending node x axis
      original_nodes[main_node_index].paired_with_nodes_info[pair_node_index].edges_between_info[artificial_edge_pointer_index_counter].end_x_axis = value;
      break;
    case 4 :
      // Artificial edge ending node y axis
      original_nodes[main_node_index].paired_with_nodes_info[pair_node_index].edges_between_info[artificial_edge_pointer_index_counter].end_y_axis = value;
      break;
    case 5 :
      // Artificial edge length
      original_nodes[main_node_index].paired_with_nodes_info[pair_node_index].edges_between_info[artificial_edge_pointer_index_counter].length = value;
      break;
    case 6 :
      // Number of original nodes that can be served while crossing this artificial edge
      original_nodes[main_node_index].paired_with_nodes_info[pair_node_index].edges_between_info[artificial_edge_pointer_index_counter].n_nodes_can_serve = int(value);

      if (int(value) > 0)
      {
        // There are nodes that can be served
        // original_nodes[main_node_index].paired_with_nodes_info[pair_node_index].edges_between_info[artificial_edge_pointer_index_counter].ids_nodes_can_serve = new int[int(value) - 1];
        resetIdsCanbeServed(main_node_index, pair_node_index, int(value), artificial_edge_pointer_index_counter);
      } else
      {
        // There are no nodes that can be served
        // original_nodes[main_node_index].paired_with_nodes_info[pair_node_index].edges_between_info[artificial_edge_pointer_index_counter].ids_nodes_can_serve = new int[1];
        resetIdsCanbeServed(main_node_index, pair_node_index, 1, artificial_edge_pointer_index_counter);

        // "Label" of the current artificial edge being processed
        int current_artificial_edge_label = original_nodes[main_node_index].paired_with_nodes_info[pair_node_index].edges_between_info[artificial_edge_pointer_index_counter].edge_label;
        // Total of artificial edges that must be processed
        int number_of_artificial_edges_to_process = original_nodes[main_node_index].paired_with_nodes_info[pair_node_index].n_edges_between;
        // Tells me if the current line being processd is the last artificial edge to be processed for now
        bool is_last_artificial_edge = (current_artificial_edge_label == number_of_artificial_edges_to_process);

        if (is_last_artificial_edge)
        {
          // This is the last artificial edge to be processed and the next line regards to node->pair information
          is_parsing_artificial_info = false;
        }

        artifial_edge_info_counter--; // Go to net artificial edge
      }

      nodes_can_be_served_counter = int(value); // Counter will be decreased in order to calculate the index of the processed "served node id" within the list of ids that can be served while passing through this edge
      break;
    default :
      if (value_index > 6)
      {
        int number_nodes_can_be_served = original_nodes[main_node_index].paired_with_nodes_info[pair_node_index].edges_between_info[artificial_edge_pointer_index_counter].n_nodes_can_serve;

        // 'index_id_node_can_be_served' is the value that will be added to the pointer that points to the ids that can be served while in this edge
        int index_id_node_can_be_served = number_nodes_can_be_served - nodes_can_be_served_counter; // Value starts as '0' and increases until it is equal to the number of ids i can serve

        // Ex.: number of nodes i can serve equals to 1 AND 'index_id_node_can_be_served' starts as 0 (always) -> when 'index_id_node_can_be_served' reaches '1' it means I've already parsed all the ids
        if (index_id_node_can_be_served < number_nodes_can_be_served)
        {
          original_nodes[main_node_index].paired_with_nodes_info[pair_node_index].edges_between_info[artificial_edge_pointer_index_counter].ids_nodes_can_serve[index_id_node_can_be_served] = int(value);
          nodes_can_be_served_counter--; // Decreasing account for the accounting of an id I can serve. Ex.: 4 -> 3 == "Out of 4 id's there are 3 left to set"
        } else
        {
          // There are no nodes that can be served while in this edge
        }
        
        // "Label" of the current artificial edge being processed
        int current_artificial_edge_label = original_nodes[main_node_index].paired_with_nodes_info[pair_node_index].edges_between_info[artificial_edge_pointer_index_counter].edge_label;
        // Total of artificial edges that must be processed
        int number_of_artificial_edges_to_process = original_nodes[main_node_index].paired_with_nodes_info[pair_node_index].n_edges_between;
        // Tells me if the current line being processd is the last artificial edge to be processed for now
        bool is_last_artificial_edge = (current_artificial_edge_label == number_of_artificial_edges_to_process);

        // 'nodes_can_be_served_counter' will equal to '0' in two cases:
        //    1 - current artificial edge being processed can't serve no original node
        //    2 - i have already processed all the ids of the nodes that can be served in this edge
        if ((nodes_can_be_served_counter == 0) && is_last_artificial_edge)
        {       
          // Not parsing segmented edge information anymore
          is_parsing_artificial_info = false;
        } else if (nodes_can_be_served_counter == 0)
        {
          // There are no nodes that can be served while in this edge - just go to the next line in the file
          artifial_edge_info_counter--; // Go to net artificial edge
        } else
        {
          // There are still ids of nodes that can be served to be parsed - do nothing here
        }        
      }
      break;
  }
}

/* Pauses the execution of the program for debbuging purposes */
void Instance::pauseExecution(int line, string str) {
  cout << "\n[ EXECUTION PAUSED ON LINE '" << line << "' -> '" << str << "' ] _: ";
  int pause = 0;
  cin >> pause;
  cout << endl;
  return;
}

/* Prints all the metadata associated all pairs of original nodes */
void Instance::printPairsRelatedInfo(void) {
  for (int i = 0; i < original_nodes_n; ++i)
  {
    for (int j = 0; j < original_nodes_n; ++j)
    {
      cout << i << "  ";
      cout << original_nodes[i].paired_with_nodes_info[j].pair_id << "  ";
      cout << original_nodes[i].paired_with_nodes_info[j].distance << "  ";
      cout << original_nodes[i].paired_with_nodes_info[j].n_edges_between << endl;

      for (int k = 0; k < original_nodes[i].paired_with_nodes_info[j].n_edges_between; ++k)
      {
        cout << original_nodes[i].paired_with_nodes_info[j].edges_between_info[k].edge_label << "  ";
        cout << original_nodes[i].paired_with_nodes_info[j].edges_between_info[k].start_x_axis << "  ";
        cout << original_nodes[i].paired_with_nodes_info[j].edges_between_info[k].start_y_axis << "  ";
        cout << original_nodes[i].paired_with_nodes_info[j].edges_between_info[k].end_x_axis << "  ";
        cout << original_nodes[i].paired_with_nodes_info[j].edges_between_info[k].end_y_axis << "  ";
        cout << original_nodes[i].paired_with_nodes_info[j].edges_between_info[k].length << "  ";
        cout << original_nodes[i].paired_with_nodes_info[j].edges_between_info[k].n_nodes_can_serve << "  ";

        for (int l = 0; l < original_nodes[i].paired_with_nodes_info[j].edges_between_info[k].n_nodes_can_serve; ++l)
        {
          cout << original_nodes[i].paired_with_nodes_info[j].edges_between_info[k].ids_nodes_can_serve[l] << "  ";
        }
        cout << endl;
      }
      cout << endl;
    }
    cout << endl;
  }
}


/* Getters - Objective function evaluation helpers | AE - Artificial Edge | BP - Between Pairs' | Values regarding metadata between two consecutive nodes */

/* Returns the number of artificial edges */
int Instance::getNumberOfAEBP(int main_node_index, int pair_node_index) {
  return original_nodes[main_node_index].paired_with_nodes_info[pair_node_index].n_edges_between;
};

/* Returns the number of nodes that can be served in 'ed_index' */
int Instance::getAENumberNodeCanBeServed(int main_node_index, int pair_node_index, int ae_index) {
  return original_nodes[main_node_index].paired_with_nodes_info[pair_node_index].edges_between_info[ae_index].n_nodes_can_serve;
};

/* Returns the distance */    
double Instance::getDistanceBP(int main_node_index, int pair_node_index) {
  return original_nodes[main_node_index].paired_with_nodes_info[pair_node_index].distance;
};

/* Returns the x starting coordinate of 'ed_index' */
double Instance::getAExStartAxis(int main_node_index, int pair_node_index, int ae_index) {
  return original_nodes[main_node_index].paired_with_nodes_info[pair_node_index].edges_between_info[ae_index].start_x_axis;
}; 

/* Returns the y starting coordinate of 'ed_index' */
double Instance::getAEyStartAxis(int main_node_index, int pair_node_index, int ae_index) {
  return original_nodes[main_node_index].paired_with_nodes_info[pair_node_index].edges_between_info[ae_index].start_y_axis;
}; 

/* Returns the x ending coordinate of 'ed_index' */
double Instance::getAExEndAxis(int main_node_index, int pair_node_index, int ae_index) {
  return original_nodes[main_node_index].paired_with_nodes_info[pair_node_index].edges_between_info[ae_index].end_x_axis;
}; 

/* Returns the y ending coordinate of 'ed_index' */
double Instance::getAEyEndAxis(int main_node_index, int pair_node_index, int ae_index) {
  return original_nodes[main_node_index].paired_with_nodes_info[pair_node_index].edges_between_info[ae_index].end_y_axis;
}; 

/* Returns the length of 'ed_index' */
double Instance::getAELength(int main_node_index, int pair_node_index, int ae_index) {
  return original_nodes[main_node_index].paired_with_nodes_info[pair_node_index].edges_between_info[ae_index].length;
}; 

/* Returns true if 'x' can be served in 'ed_index' - false otherwise */
bool Instance::canXbeServedInAE(int main_node_index, int pair_node_index, int ae_index, int x) {
  bool canBeServed = false;
  int n_nodes_can_be_served = original_nodes[main_node_index].paired_with_nodes_info[pair_node_index].edges_between_info[ae_index].n_nodes_can_serve;
  for (int i = 0; i < n_nodes_can_be_served; ++i)
  {
    if (original_nodes[main_node_index].paired_with_nodes_info[pair_node_index].edges_between_info[ae_index].ids_nodes_can_serve[i] == x)
    {
      canBeServed = true;
    }
  }
  return canBeServed;
};

SolutionStruct * Instance::buildSolutionStructure(Hallele *chromosome) {
  SolutionStruct *solution = new SolutionStruct[original_nodes_n + 1];
  // cout << "Sol struct [n]: n = " << (original_nodes_n + 1) << endl;

  for (int i = 0; i < (original_nodes_n + 1); ++i)
  {
    SolutionStruct sl;

    sl.node = chromosome[i].index;
    sl.demand = getNodesDemmand(chromosome[i].index); // Get demand here.

    solution[i] = sl;
  }

  return solution;
}

// 'ae' stands for Artificial Edge.
double Instance::evaluateSolution(Hallele *chromosome, double muleVelocity) {
  //TODO where there is a '6' put the actual number of nodes in G + 1 (solution vector size).
  double totalTimeElapsed = 0.0;
  double timeElapsedServing = 0.0;
  double demandMet = 0.0;
  double totalDemand = 0.0;
  int sizeC = original_nodes_n + 1;

  //Decoder.
  sortHalleleDecoder(chromosome, sizeC);

  //Building solution structure array.
  SolutionStruct *solution = buildSolutionStructure(chromosome);


  // for (int i = 0; i < sizeC; ++i)
  // {
  //   cout << chromosome[i].key << " (" << chromosome[i].index << ")" << endl;
  // }

  // cout << "\n\n*****\n\n";

  // for (int i = 0; i < sizeC; ++i)
  // {
  //   cout << solution[i].node << " (" << solution[i].demand << ")" << endl;
  // }

  //TODO - THIS MUST BE A CLASS PROPERTY.
  // Calculating total demand.
  for (int i = 0; i < sizeC; ++i)
  {
    //TODO - TOTAL DEMAND SHOULD BE A PROPERTY OF INSTANCE CLASS.
    totalDemand += getNodesDemmand(i);
  }

  for (int i = 0; i < sizeC; ++i)
  {
    if (i < (sizeC-1))
    {
      int nodeA = solution[i].node;
      int nodeB = solution[i+1].node;
      int aeBetween = getNumberOfAEBP(nodeA, nodeB);

      // cout << "(" << nodeA << ", " << nodeB << ")" << endl;

      // Acounting time to cross edge between main nodes under consideration.
      totalTimeElapsed += getDistanceBP(nodeA, nodeB) / muleVelocity;

      // Going through the artificial edges metadata ('j' is an artificial edge "id").
      for (int j = (aeBetween-1); j >= 0; --j)
      {
        int countAux = 0;        
        int numNodesCanServe = getAENumberNodeCanBeServed(nodeA, nodeB, j);
        double aeLength = getAELength(nodeA, nodeB, j);
        double timeInJ = aeLength / muleVelocity;
        double timeLeftInJ = timeInJ; //"Workble time" left while in 'j'.

        // Getting G's nodes that can be served in 'j'.
        for (int k = 0; k < sizeC; ++k)
        {
          // Processing information regarding each node that can be served by 'j'.
          if (canXbeServedInAE(nodeA, nodeB, j, k) && (timeLeftInJ > 0) && (solution[k].demand > 0))
          {
            double timeRequired = floor(solution[k].demand / getNodesTRate(k)); //.
            double timeUnitsLeft = timeLeftInJ - timeRequired;

            if (timeRequired <= timeLeftInJ)
            {
              if (timeUnitsLeft > 0)
              {
                // There is still time left in 'j' to serve another node.
                // demandMet += solution[k].demand; // Accounting demand attended.
                // cout << "Added1: " << solution[k].demand << endl;
                timeLeftInJ -= timeRequired;
                timeElapsedServing += timeRequired;

                // cout << solution[k].demand << " (" << k << ")" << endl;
                solution[k].demand -= solution[k].demand;
                // cout << ": " << solution[k].demand << endl;
              } else {
                // Time in 'j' not enought to serve the whole demand of 'k'.
                double timeUsedUpPositive = timeRequired - (timeRequired - timeLeftInJ);

                // timeElapsedServing += floor(timeUsedUpPositive * getNodesTRate(solution[k].node)) / getNodesTRate(solution[k].node);
                timeElapsedServing += timeUsedUpPositive;

                //TODO - The bellow code should be the transmition rate, not the demand.
                // demandMet += timeUsedUpPositive * solution[k].demand; // Accounting demand attended.
                // demandMet += floor(timeUsedUpPositive * getNodesTRate(solution[k].node));
                // cout << "Added2: " << floor(timeUsedUpPositive * getNodesTRate(solution[k].node)) << endl;

                // timeLeftInJ -= floor(timeUsedUpPositive * getNodesTRate(solution[k].node)) / getNodesTRate(solution[k].node);
                timeLeftInJ -= timeUsedUpPositive;

                // cout << (timeUsedUpPositive * solution[k].demand) << " (" << k << ")" << endl;
                solution[k].demand -= floor(timeUsedUpPositive * getNodesTRate(solution[k].node));
                // cout << ". " << floor(timeUsedUpPositive * getNodesTRate(solution[k].node)) << endl;
              }
            }
          }
        }

        // Finished parsing artificial edge metadata.
      }
    }
  }

  // cout << "Total demand required: " << totalDemand << endl;
  // cout << "Total demand met: " << demandMet << endl;
  // cout << "Time used: " << totalTimeElapsed << endl;

  if (demandMet > 46)
  {
    cout << " - WARNING -\n";
  }

  double demandLeft = 0.0;
  for (int i = 0; i < sizeC; ++i)
  {
    demandLeft += solution[i].demand;
  }
  
  //TODO - DEMAND NOT MET MUST HAVE MORE SEVERE PUNISHMENT.
  return (totalDemand - demandLeft);
};

double Instance::evaluateSolutionFinal(Hallele *chromosome, double muleVelocity) {
  //TODO where there is a '6' put the actual number of nodes in G + 1 (solution vector size).
  double totalTimeElapsed = 0.0;
  double timeElapsedServing = 0.0;
  double demandMet = 0.0;
  double totalDemand = 0.0;
  int sizeC = original_nodes_n + 1;

  //Decoder.
  sortHalleleDecoder(chromosome, sizeC);

  //Building solution structure array.
  SolutionStruct *solution = buildSolutionStructure(chromosome);


  // for (int i = 0; i < sizeC; ++i)
  // {
  //   cout << chromosome[i].key << " (" << chromosome[i].index << ")" << endl;
  // }

  // cout << "\n\n*****\n\n";

  // for (int i = 0; i < sizeC; ++i)
  // {
  //   cout << solution[i].node << " (" << solution[i].demand << ")" << endl;
  // }

  //TODO - THIS MUST BE A CLASS PROPERTY.
  // Calculating total demand.
  for (int i = 0; i < sizeC; ++i)
  {
    //TODO - TOTAL DEMAND SHOULD BE A PROPERTY OF INSTANCE CLASS.
    totalDemand += getNodesDemmand(i);
  }

  for (int i = 0; i < sizeC; ++i)
  {
    if (i < (sizeC-1))
    {
      int nodeA = solution[i].node;
      int nodeB = solution[i+1].node;
      int aeBetween = getNumberOfAEBP(nodeA, nodeB);

      // cout << "(" << nodeA << ", " << nodeB << ")" << endl;

      // Acounting time to cross edge between main nodes under consideration.
      totalTimeElapsed += getDistanceBP(nodeA, nodeB) / muleVelocity;

      // Going through the artificial edges metadata ('j' is an artificial edge "id").
      for (int j = (aeBetween-1); j >= 0; --j)
      {
        int countAux = 0;        
        int numNodesCanServe = getAENumberNodeCanBeServed(nodeA, nodeB, j);
        double aeLength = getAELength(nodeA, nodeB, j);
        double timeInJ = aeLength / muleVelocity;
        double timeLeftInJ = timeInJ; //"Workble time" left while in 'j'.

        // Getting G's nodes that can be served in 'j'.
        for (int k = 0; k < sizeC; ++k)
        {
          // Processing information regarding each node that can be served by 'j'.
          if (canXbeServedInAE(nodeA, nodeB, j, k) && (timeLeftInJ > 0) && (solution[k].demand > 0))
          {
            double timeRequired = floor(solution[k].demand / getNodesTRate(k)); //.
            double timeUnitsLeft = timeLeftInJ - timeRequired;

            if (timeRequired <= timeLeftInJ)
            {
              if (timeUnitsLeft > 0)
              {
                // There is still time left in 'j' to serve another node.
                // demandMet += solution[k].demand; // Accounting demand attended.
                // cout << "Added1: " << solution[k].demand << endl;
                timeLeftInJ -= timeRequired;
                timeElapsedServing += timeRequired;

                // cout << solution[k].demand << " (" << k << ")" << endl;
                solution[k].demand -= solution[k].demand;
                // cout << ": " << solution[k].demand << endl;
              } else {
                // Time in 'j' not enought to serve the whole demand of 'k'.
                double timeUsedUpPositive = timeRequired - (timeRequired - timeLeftInJ);

                // timeElapsedServing += floor(timeUsedUpPositive * getNodesTRate(solution[k].node)) / getNodesTRate(solution[k].node);
                timeElapsedServing += timeUsedUpPositive;

                //TODO - The bellow code should be the transmition rate, not the demand.
                // demandMet += timeUsedUpPositive * solution[k].demand; // Accounting demand attended.
                // demandMet += floor(timeUsedUpPositive * getNodesTRate(solution[k].node));
                // cout << "Added2: " << floor(timeUsedUpPositive * getNodesTRate(solution[k].node)) << endl;

                // timeLeftInJ -= floor(timeUsedUpPositive * getNodesTRate(solution[k].node)) / getNodesTRate(solution[k].node);
                timeLeftInJ -= timeUsedUpPositive;

                // cout << (timeUsedUpPositive * solution[k].demand) << " (" << k << ")" << endl;
                solution[k].demand -= floor(timeUsedUpPositive * getNodesTRate(solution[k].node));
                // cout << ". " << floor(timeUsedUpPositive * getNodesTRate(solution[k].node)) << endl;
              }
            }
          }
        }

        // Finished parsing artificial edge metadata.
      }
    }
  }

  double demandLeft = 0.0;
  for (int i = 0; i < sizeC; ++i)
  {
    demandLeft += solution[i].demand;
  }

  cout << "Total demand required: " << totalDemand << endl;
  cout << "Total demand met: " << (totalDemand - demandLeft) << endl;
  cout << "Time to serve all: " << timeElapsedServing << endl;

  if (demandMet > 46)
  {
    cout << " - WARNING -\n";
  }
  
  //TODO - DEMAND NOT MET MUST HAVE MORE SEVERE PUNISHMENT.
  return (totalDemand - demandLeft);
};
