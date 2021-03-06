#include <iostream>
#include <array>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <limits>

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

/* Returns the cost of the edge AB (total demand attended/distance travelled) */
double Instance::getGainAB(int A_index, int B_index, double muleSpeed) {
  if (B_index == -1) {
    return 0.0;
  }
  int aeBetween = getNumberOfAEBP(A_index, B_index);
  double totalDistance = getDistanceBP(A_index, B_index);
  double totalDemandAttended = 0.0;
  int pause = 0;

  // cout << "[ A: " << A_index << ", B: " << B_index << " ]" << endl;
  // cout << "AB distance: " << totalDistance << endl;

  SolutionStruct *idsToServe = new SolutionStruct[original_nodes_n];

  for (int i = 0; i < original_nodes_n; ++i)
  {
    SolutionStruct sl;

    sl.node = i;
    sl.demand = getNodesDemmand(i);

    sl.key = 0; // not important here

    idsToServe[i] = sl;
  }

  // Going through the artificial edges metadata ('j' is an artificial edge "id").
  for (int j = (aeBetween-1); j >= 0; --j)
  {
    double aeLength = getAELength(A_index, B_index, j);
    double timeInJ = aeLength / 0.001;                                                // set mule speed here!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    double timeLeftInJ = timeInJ; //"Workble time" left while in 'j'.

    // cout << "AE: " << j+1 << endl;
    // cout << "length: " << aeLength << endl;

    int n_nodes_can_be_served = original_nodes[A_index].paired_with_nodes_info[B_index].edges_between_info[j].n_nodes_can_serve;

    // cout << "# nodes reacheble: " << n_nodes_can_be_served << endl;
    // cout << "time available in AE: " << timeInJ << endl;

    for (int i = 0; i < n_nodes_can_be_served; ++i)
    {
      int target = original_nodes[A_index].paired_with_nodes_info[B_index].edges_between_info[j].ids_nodes_can_serve[i];

      // cout << "serving: " << idsToServe[target].node << endl;
      // cout << "demand: " << idsToServe[target].demand << endl;

      double trate = getNodesTRate(idsToServe[target].node);
      double timeRequired = idsToServe[target].demand / trate;

      // cout << "time required: " << timeRequired << endl;
      // cout << "time left in AE: " << timeLeftInJ << endl;

      if (timeRequired <= timeLeftInJ && idsToServe[target].demand > 0)
      {
        timeLeftInJ -= timeRequired;
        totalDemandAttended += idsToServe[target].demand;
        idsToServe[target].demand -= idsToServe[target].demand;
        // cout << "# served #" << endl;
      } else {
        // cout << "# not served #" << endl;
      }

      // cout << "\n==============================\n";

      // cin >> pause;
    }
  }

  // for (int i = 0; i < original_nodes_n; ++i)
  // {
  //   cout << "Node: " << idsToServe[i].node << endl;
  //   cout << "Demand: " << idsToServe[i].demand << "\n\n";
  // }
  //
  // cin >> pause;

  // double totalCost = totalDemandAttended / (totalDistance / muleSpeed);
  double totalCost = totalDemandAttended / totalDistance;

  // cout << "total cost: " << totalCost << endl;
  //
  // cin >> pause;

  return totalCost; // The bigger, the better.
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

  for (int i = 0; i < (original_nodes_n + 1); ++i)
  {
    SolutionStruct sl;

    sl.node = chromosome[i].index;
    sl.key = chromosome[i].key;
    sl.demand = getNodesDemmand(chromosome[i].index); // Get demand here.

    solution[i] = sl;
  }

  //Decoder.
  sortHalleleDecoder(solution, (original_nodes_n + 1));

  return solution;
}

int Instance::findFinalBSIndex(SolutionStruct *solution) {
  int index = 0;
  // cout << "\n";
  for (int i = 1; i < (original_nodes_n + 1); ++i)
  {
    // cout << solution[i].node << " [" << solution[i].key << "] ";
    if (solution[i].node == 0)
    {
      index = i;
      break;
    }
  }
  // cout << "\n";

  return index;
}

int Instance::findAXFromA(SolutionStruct *solution, int a) {
  int next = -1;

  for (int i = 1; i < (original_nodes_n + 1); ++i)
  {
    if (solution[i].node == a && i <= (original_nodes_n - 1))
    {
      next = solution[i+1].node;
      break;
    }
  }

  return next;
}

bool Instance::isInvalidSolution(double fitness) {
  if (fitness == numeric_limits<double>::max()) {
    return true;
  }
  return false;
}

bool Instance::isntInSolution(SolutionStruct *solution, int a, int size) {
  if (a == -1) {
    return false;
  }
  bool comparison = true;
  for (int i = 1; i < size; i++) {
    if (solution[i].node == a) {
      comparison = false;
      break;
    }
  }
  return comparison;
}

// 'ae' stands for Artificial Edge.
double Instance::evaluateSolution(Hallele *chromosome, double muleVelocity, double skipeBSCheck) {
  double totalDistance = 0.0;
  double timeElapsedServing = 0.0;
  double demandMet = 0.0;
  int sizeC = original_nodes_n + 1;

  // cout << "A: ";
  // for (int i = 0; i < sizeC; ++i)
  // {
  //   cout << chromosome[i].index << "[" << chromosome[i].key << "] ";
  // }
  // cout << "\n\n";

  //Building solution structure array.
  SolutionStruct *solution = buildSolutionStructure(chromosome);

  int index = findAXFromA(solution, 1);

  // if (solution[1].node == 0 && !skipeBSCheck)
  // {
  //   int w = 0;
  //   cout << "\nBS followed by BS\n";
  //   cin >> w;
  // }

  // cout << "sol [ ";
  // for (int i = 0; i < (original_nodes_n + 1); ++i)
  // {
  //   cout << solution[i].node << " (" << solution[i].key << ") ";
  //   // cout << solution[i].node << " ";
  // }
  // cout << " ]\n\n";

  // cout << "As: ";
  // for (int i = 0; i < sizeC; ++i)
  // {
  //   cout << chromosome[i].index << "[" << chromosome[i].key << "] ";
  // }
  // cout << "\n\n";

  // int l = 0;
  // cin >> l;

  for (int i = 0; i < sizeC; ++i)
  {
    if (i < (sizeC-1))
    {
      int nodeA = solution[i].node;
      int nodeB = solution[i+1].node;
      int aeBetween = getNumberOfAEBP(nodeA, nodeB);

      // Acounting time to cross edge between main nodes under consideration.
      totalDistance += getDistanceBP(nodeA, nodeB);

      // Going through the artificial edges metadata ('j' is an artificial edge "id").
      for (int j = (aeBetween-1); j >= 0; --j)
      {
        int countAux = 0;
        int numNodesCanServe = getAENumberNodeCanBeServed(nodeA, nodeB, j);
        double aeLength = getAELength(nodeA, nodeB, j);
        double timeInJ = aeLength / muleVelocity;
        double timeLeftInJ = timeInJ; //"Workble time" left while in 'j'.

        // cout << "Pair: " << nodeA << ", " << nodeB << endl;
        // cout << "A.E. ID: " << j+1 << endl;
        // cout << "A.E. length: " << aeLength << endl;
        // cout << "Time in A.E.: " << timeInJ << endl;
        // cout << "Time left in A.E.: " << timeLeftInJ << endl;
        // cout << "Mule velocity: " << muleVelocity << endl << endl;

        // Getting G's nodes that can be served in 'j'.
        for (int k = 0; k < sizeC; ++k)
        {
          // Processing information regarding each node that can be served by 'j'.
          if (canXbeServedInAE(nodeA, nodeB, j, solution[k].node) && (timeLeftInJ > 0) && (solution[k].demand > 0))
          {
            double timeRequired = solution[k].demand / getNodesTRate(solution[k].node);
            // cout << "Node being served: " << solution[k].node << endl;
            // cout << "Time required to serve it: " << timeRequired << endl;

            if (timeRequired <= timeLeftInJ)
            {
              timeLeftInJ -= timeRequired;
              timeElapsedServing += timeRequired;

              solution[k].demand -= solution[k].demand;

              if (solution[k].demand < 0)
              {
                cout << " - WARNING 2 -\n";
              }

              // cout << "Time left in A.E.: " << timeLeftInJ << endl;
              // cout << "Sensor " << solution[k].node << " updated demand: " << solution[k].demand << endl << endl;

              int pause = 0;
              // cin >> pause;
            }
          }
        }
        // Finished parsing artificial edge metadata.
      }
    }

    if (solution[i+1].node == 0)
    {
      break;
    }
  }

  double demandLeft = 0.0;
  for (int i = 0; i < sizeC; ++i)
  {
    demandLeft += solution[i].demand;

    if (solution[i].demand < 0)
    {
      cout << " - WARNING 2 -\n";
    }
  }

  double fit = (totalDistance / muleVelocity);

  if ((total_demand - demandLeft) < total_demand) {
    // cout << numeric_limits<double>::max() << "\n\n";
    return numeric_limits<double>::max();
  }

  // cout << fit << "\n\n";

  return fit;
};

double Instance::evalSolFromSolStructure(SolutionStruct *solutionInput, double muleVelocity, bool skipDemandBreak) {
  double totalDistance = 0.0;
  double timeElapsedServing = 0.0;
  double demandMet = 0.0;
  int sizeC = original_nodes_n + 1;

  SolutionStruct *solution = new SolutionStruct[sizeC];

  for (int i = 0; i < sizeC; ++i)
  {
    SolutionStruct s;
    s.node = solutionInput[i].node;
    s.demand = solutionInput[i].demand;
    s.key = solutionInput[i].key;

    solution[i] = s;
  }

  for (int i = 0; i < sizeC; ++i)
  {
    if (i < (sizeC-1))
    {
      int nodeA = solution[i].node;
      int nodeB = solution[i+1].node;
      int aeBetween = getNumberOfAEBP(nodeA, nodeB);

      // Acounting time to cross edge between main nodes under consideration.
      totalDistance += getDistanceBP(nodeA, nodeB);

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
          if (canXbeServedInAE(nodeA, nodeB, j, solution[k].node) && (timeLeftInJ > 0) && (solution[k].demand > 0))
          {
            double timeRequired = solution[k].demand / getNodesTRate(solution[k].node);

            if (timeRequired <= timeLeftInJ)
            {
              timeLeftInJ -= timeRequired;
              timeElapsedServing += timeRequired;

              solution[k].demand -= solution[k].demand;

              if (solution[k].demand < 0)
              {
                cout << " - WARNING 2 -\n";
              }
            }
          }
        }
        // Finished parsing artificial edge metadata.
      }
    }

    if (solution[i+1].node == 0)
    {
      break;
    }
  }

  double demandLeft = 0.0;
  for (int i = 1; i < sizeC; ++i)
  {
    demandLeft += solution[i].demand;

    if (solution[i].demand < 0)
    {
      cout << " - WARNING 2 -\n";
    }

    if (solution[i].node == 0 && skipDemandBreak)
    {
      break;
    }
  }

  double fit = (totalDistance / muleVelocity);

  if ((total_demand - demandLeft) < total_demand) {
    fit = numeric_limits<double>::max();
  }

  delete[] solution;

  return fit;
};

double Instance::evalSolFromSolStructure2(SolutionStruct *solutionInput, double muleVelocity, bool skipDemandBreak) {
  double totalDistance = 0.0;
  double timeElapsedServing = 0.0;
  double demandMet = 0.0;
  int sizeC = original_nodes_n + 1;

  SolutionStruct *solution = new SolutionStruct[sizeC];

  for (int i = 0; i < sizeC; ++i)
  {
    SolutionStruct s;
    s.node = solutionInput[i].node;
    s.demand = solutionInput[i].demand;
    s.key = solutionInput[i].key;

    solution[i] = s;
  }

  cout << "\n\n==================================== EVALUATION ====================================";

  for (int i = 0; i < sizeC; ++i)
  {
    if (i < (sizeC-1))
    {
      int nodeA = solution[i].node;
      int nodeB = solution[i+1].node;
      int aeBetween = getNumberOfAEBP(nodeA, nodeB);

      // Acounting time to cross edge between main nodes under consideration.
      totalDistance += getDistanceBP(nodeA, nodeB);

      // cout << "\n\n>>> Pair : " << nodeA << " " << nodeB << " | # A.E.s : " << aeBetween << " | path length : " << getDistanceBP(nodeA, nodeB) << endl;
      // cout << "\n\n>>> path length : " << getDistanceBP(nodeA, nodeB) << endl;

      // Going through the artificial edges metadata ('j' is an artificial edge "id").
      for (int j = (aeBetween-1); j >= 0; --j)
      {
        int countAux = 0;
        int numNodesCanServe = getAENumberNodeCanBeServed(nodeA, nodeB, j);
        double aeLength = getAELength(nodeA, nodeB, j);
        double timeInJ = aeLength / muleVelocity;
        double timeLeftInJ = timeInJ; //"Workble time" left while in 'j'.

        // cout << "\n>> A.E. : " << j+1 << " | # reacheble sensors : " << numNodesCanServe << " | workable time : " << timeInJ << endl;

        // Getting G's nodes that can be served in 'j'.
        for (int k = 0; k < sizeC; ++k)
        {
          // Processing information regarding each node that can be served by 'j'.
          if (canXbeServedInAE(nodeA, nodeB, j, solution[k].node) && (timeLeftInJ > 0) && (solution[k].demand > 0))
          {
            double timeRequired = solution[k].demand / getNodesTRate(solution[k].node);

            // cout << "\n> Serving : " << solution[k].node << " | Demand : " << solution[k].demand << " | Required time : " << timeRequired << " | Time available : " << timeLeftInJ << endl;

            if (timeRequired <= timeLeftInJ)
            {
              timeLeftInJ -= timeRequired;
              timeElapsedServing += timeRequired;

              solution[k].demand -= solution[k].demand;

              if (solution[k].demand < 0)
              {
                cout << " - WARNING 2 -\n";
              }
            }
          }
        }
        // Finished parsing artificial edge metadata.
      }

      // cout << "\n ***** ***** ***** ***** *****";
    }

    if (solution[i+1].node == 0)
    {
      break;
    }
  }

  double demandLeft = 0.0;
  for (int i = 1; i < sizeC; ++i)
  {
    demandLeft += solution[i].demand;

    if (solution[i].demand < 0)
    {
      cout << " - WARNING 2 -\n";
    }

    if (solution[i].node == 0 && skipDemandBreak)
    {
      break;
    }
  }

  double fit = (totalDistance / muleVelocity);

  cout << "\n\ntotal distance : " << totalDistance;
  cout << "\nmule velocity : " << muleVelocity << endl;

  if ((total_demand - demandLeft) < total_demand) {
    fit = numeric_limits<double>::max();
  }

  delete[] solution;

  return fit;
};

double Instance::evaluateBRKGA02Solution(SolutionStruct *solutionInput, double muleVelocity, int sensorsOnRounte, bool skipDemandBreak) {
  double totalDistance = 0.0;
  double timeElapsedServing = 0.0;
  double demandMet = 0.0;
  int sizeC = original_nodes_n + 1;

  SolutionStruct *solution = new SolutionStruct[sensorsOnRounte];

  // return 1.0;

  for (int i = 0; i < sensorsOnRounte; ++i)
  {
    solution[i].node = solutionInput[i].node;
    solution[i].demand = solutionInput[i].demand;
    solution[i].key = solutionInput[i].key;
  }

  for (int i = 0; i < sensorsOnRounte; ++i)
  {
    if (i < (sensorsOnRounte-1))
    {
      int nodeA = solution[i].node;
      int nodeB = solution[i+1].node;
      int aeBetween = getNumberOfAEBP(nodeA, nodeB);

      // Acounting time to cross edge between main nodes under consideration.
      totalDistance += getDistanceBP(nodeA, nodeB);

      // Going through the artificial edges metadata ('j' is an artificial edge "id").
      for (int j = (aeBetween-1); j >= 0; --j)
      {
        int countAux = 0;
        int numNodesCanServe = getAENumberNodeCanBeServed(nodeA, nodeB, j);
        double aeLength = getAELength(nodeA, nodeB, j);
        double timeInJ = aeLength / muleVelocity;
        double timeLeftInJ = timeInJ; //"Workble time" left while in 'j'.

        // Getting G's nodes that can be served in 'j'.
        for (int k = 0; k < sensorsOnRounte; ++k)
        {
          // Processing information regarding each node that can be served by 'j'.
          if (canXbeServedInAE(nodeA, nodeB, j, solution[k].node) && (timeLeftInJ > 0) && (solution[k].demand > 0))
          {
            double timeRequired = solution[k].demand / getNodesTRate(solution[k].node);

            if (timeRequired <= timeLeftInJ)
            {
              timeLeftInJ -= timeRequired;
              timeElapsedServing += timeRequired;

              // cout << solution[k].demand << endl;
              solution[k].demand -= solution[k].demand;

              if (solution[k].demand < 0)
              {
                cout << " - WARNING 2 -\n";
              }
            }
          }
        }
        // Finished parsing artificial edge metadata.
      }
    }

    if (solution[i+1].node == 0)
    {
      break;
    }
  }

  double demandLeft = 0.0;
  for (int i = 0; i < sensorsOnRounte; ++i)
  {
    demandLeft += solution[i].demand;
    if (solution[i].demand < 0)
    {
      cout << " - WARNING 2 -\n";
    }
  }

  double fit = (totalDistance / muleVelocity);

  if ((total_demand - demandLeft) < total_demand) {
    if (!skipDemandBreak)
    {
      fit = numeric_limits<double>::max();
    }
  }

  delete[] solution;

  return fit;
};

int Instance::checkCanInserSensor(SolutionStruct *sol, int sensor, int sensorsOnRoute) {
  bool canInsert = true;
  int *aux = new int[original_nodes_n];

  for (int i = 0; i < original_nodes_n; ++i)
  {
    aux[i] = i;
  }
  aux[0] = -1;

  for (int i = 1; i < sensorsOnRoute; ++i)
  {
    /* marking used sensor */
    for (int j = 1; j < sensorsOnRoute; ++j)
    {
      for (int k = 1; k < original_nodes_n; ++k)
      {
        if (sol[j].node == aux[k])
        {
          aux[k] = -1;
          break;
        }
      }
    }

    // check if it was used already
    if (sol[i].node == sensor)
    {
      canInsert = false;
      break;
    }
  }

  if (!canInsert)
  {
    /* searching for legitimate */
    for (int j = 0; j < original_nodes_n; ++j)
    {
      if (aux[j] != -1)
      {
        return aux[j];
      }
    }
  }

  delete[] aux;

  return sensor;
}

int Instance::findNextSensorOnRoute(SolutionStruct *sol, int sensor) {
  int nextSensorIndex = -1;
  // cout << "Entering: " << sensor << "\n";

  for (int i = 1; i < original_nodes_n+1; ++i)
  {
    if (sol[i].node == sensor && i < original_nodes_n+2)
    {
      nextSensorIndex = i+1;
      break;
    }
  }

  // cout << "Returnin: " << nextSensorIndex << "\n";

  return nextSensorIndex;
}

void Instance::printFinalSolution(Hallele *chromosome, double muleVelocity) {
  double totalDistance = 0.0;
  double timeElapsedServing = 0.0;
  double demandMet = 0.0;
  int sizeC = original_nodes_n + 1;

  //Building solution structure array.
  SolutionStruct *solution = buildSolutionStructure(chromosome);

  cout << "Path: ";
  for (int i = 0; i < (original_nodes_n + 1); ++i)
  {
    if (i < original_nodes_n)
    {
      cout << solution[i].node << " [" << solution[i].demand << "], ";
    } else {
      cout << solution[i].node << " [" << solution[i].demand << "]";
    }
  }
  cout << "\n\n";

  for (int i = 0; i < sizeC; ++i)
  {
    if (i < (sizeC-1))
    {
      int nodeA = solution[i].node;
      int nodeB = solution[i+1].node;
      int aeBetween = getNumberOfAEBP(nodeA, nodeB);

      // Acounting time to cross edge between main nodes under consideration.
      totalDistance += getDistanceBP(nodeA, nodeB);

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
          if (canXbeServedInAE(nodeA, nodeB, j, solution[k].node) && (timeLeftInJ > 0) && (solution[k].demand > 0))
          {
            double timeRequired = solution[k].demand / getNodesTRate(solution[k].node);

            if (timeRequired <= timeLeftInJ)
            {
              timeLeftInJ -= timeRequired;
              timeElapsedServing += timeRequired;

              solution[k].demand -= solution[k].demand;

              if (solution[k].demand < 0)
              {
                cout << " - WARNING 2 -\n";
              }
            }
          }
        }
        // Finished parsing artificial edge metadata.
      }
    }

    if (solution[i+1].node == 0)
    {
      break;
    }
  }

  double demandLeft = 0.0;
  for (int i = 0; i < sizeC; ++i)
  {
    demandLeft += solution[i].demand;
    if (solution[i].demand < 0)
    {
      cout << " - WARNING 2 -\n";
    }
  }

  if ((total_demand - demandLeft) < total_demand) {
    totalDistance = -1.0;
  }

  // cout << "\n> Solution found\n\n";
  // cout << "Demand missed: " << demandLeft << endl;
  // cout << "Route length: " << totalDistance << endl;
  // cout << "Time Serving: " << timeElapsedServing << endl;
  // cout << "\n\nFitness: " << (totalDistance / muleVelocity) << endl;
  cout << "Path: ";
  for (int i = 0; i < (original_nodes_n + 1); ++i)
  {
    cout << solution[i].node << " [" << solution[i].demand << "] ";
  }
};

void Instance::setTotalDemand() {
  int sizeC = original_nodes_n + 1;
  int totalDemand = 0.0;

  for (int i = 0; i < sizeC; ++i)
  {
    totalDemand += getNodesDemmand(i);
  }

  total_demand = totalDemand;
}
