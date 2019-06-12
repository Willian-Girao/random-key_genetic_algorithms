#include <iostream>
#include <array>
#include <stdlib.h>
#include <fstream>
#include <string>

#include "instance_class.h"

using namespace std;

/* Public methods */
Instance::Instance() {}

void Instance::setTotalNodesNumber(int total_nodes) {
  total_nodes_n = total_nodes;
  return;
}

void Instance::setOriginalNodesNumber(int orig_nodes_n) {
  original_nodes_n = orig_nodes_n;
  original_nodes = new Node[original_nodes_n];

  for (int i = 0; i < original_nodes_n; ++i)
  {
    Node node_i;

    node_i.label = i;
    node_i.x_axis = 0.0;
    node_i.y_axis = 0.0;
    node_i.c_range = 0.0;
    node_i.t_rate = 0.0; 
    node_i.demmand = 0.0;
    node_i.paired_with_nodes_info = new NodePairInfo;
    node_i.paired_with_nodes_info->edges_between_info = new EdgeData;
    node_i.paired_with_nodes_info->edges_between_info->ids_nodes_can_serve = new int;

    original_nodes[i] = node_i;
  }

  return;
}

void Instance::setSpeedNumber(int speeds_count) {
  speeds_n = speeds_count;
  speeds = new double[speeds_n];

  for (int i = 0; i < speeds_n; ++i)
  {
    speeds[i] = 1.0;
  }

  return;
}

void Instance::setSpeed(int i, double s) { /* Sets the value of the i-th possible speed to 's' */
  if (i < 0 || i == speeds_n)
  {
    return;
  }

  (*(speeds + i)) = s;

  return;
}

int Instance::getNodesLabel(int index) { /* Gets the label of a node indexed by 'index' */
  if (index < 0 || index == original_nodes_n)
  {
    return (*(original_nodes)).label;
  }
  return (*(original_nodes + index)).label;
}

double Instance::getNodesX(int index) { /* Gets the x coordinate of a node indexed by 'index' */
  if (index < 0 || index == original_nodes_n)
  {
    return (*(original_nodes)).x_axis;
  }
  return (*(original_nodes + index)).x_axis;
}

double Instance::getNodesY(int index) { /* Gets the y coordinate of a node indexed by 'index' */
  if (index < 0 || index == original_nodes_n)
  {
    return (*(original_nodes)).y_axis;
  }
  return (*(original_nodes + index)).y_axis;
}

double Instance::getNodesCRange(int index) { /* Gets the communication rang of a node indexed by 'index' */
  if (index < 0 || index == original_nodes_n)
  {
    return (*(original_nodes)).c_range;
  }
  return (*(original_nodes + index)).c_range;
}

double Instance::getNodesTRate(int index) { /* Gets the transmition rate of a node indexed by 'index' */
  if (index < 0 || index == original_nodes_n)
  {
    return (*(original_nodes)).t_rate;
  }
  return (*(original_nodes + index)).t_rate;
}

double Instance::getNodesDemmand(int index) { /* Gets the demmand of a node indexed by 'index' */
  if (index < 0 || index == original_nodes_n)
  {
    return (*(original_nodes)).demmand;
  }
  return (*(original_nodes + index)).demmand;
}

Node Instance::getNode(int index) { /* Gets the representation of a node indexed by 'index' */
  if (index < 0 || index == original_nodes_n)
  {
    return (*(original_nodes));
  }
  return (*(original_nodes + index));
}

Node Instance::getBaseStation() { /* Gets the representation of the base station */
  return (*(original_nodes));
}

void Instance::printNode(int index) { /* Prints the informations of a node indexed by 'index' */
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

void Instance::printSpeeds(void) { /* Prints the allowed speed's values */
  cout << endl;
  for (int i = 0; i < speeds_n; ++i)
  {
    cout << "Speed " << i << ": " << (*(speeds + i)) << endl;
  }
  cout << endl;

  return;
}

void Instance::setNode(int index, double x, double y, double c_range, double t_rate, double demmand) { /* Sets the properties of the node indexed by 'index' */
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

void Instance::setNodeX(int index, double x) {
  if (index < 0 || index == original_nodes_n)
  {
    return;
  }

  (*(original_nodes + index)).x_axis = x;;

  return;
}

void Instance::setNodeY(int index, double y) {
  if (index < 0 || index == original_nodes_n)
  {
    return;
  }

  (*(original_nodes + index)).y_axis = y;

  return;
}

void Instance::setNodeCRange(int index, double c_range) {
  if (index < 0 || index == original_nodes_n)
  {
    return;
  }

  (*(original_nodes + index)).c_range = c_range;

  return;
}

void Instance::setNodeTRate(int index, double t_rate) {
  if (index < 0 || index == original_nodes_n)
  {
    return;
  }

  (*(original_nodes + index)).t_rate = t_rate;

  return;
}

void Instance::setNodeDemmand(int index, double demmand) {
  if (index < 0 || index == original_nodes_n)
  {
    return;
  }

  (*(original_nodes + index)).demmand = demmand;

  return;
}

void Instance::printInstanceMetadata(void) { /* Prints all the metadata associated with the graph */
  cout << endl;

  cout << "Original nodes: " << original_nodes_n << endl;
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

int Instance::getNumberOfOriginalNodes(void) { /* Gets the number of original nodes in the graph */
  return original_nodes_n;
}

void Instance::setNodePair(int value_index, double value, int &main_node_index, int &pair_node_index, bool &is_parsing_artificial_info, int &artifial_edge_info_counter) {
  switch(value_index) {
    case 0 :
      break;
    case 1 :
      ((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_node_index)->pair_id = int(value);
      break;
    case 2 :
      ((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_node_index)->distance = value;
      break;
    case 3 :
      // Initializing data struct to hold information regarding to artificial edges (segmented due to the presence of an artidial vertex).
      ((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_node_index)->edges_between_info = new EdgeData;
      // Setting number of artificial edges (segmentation of an original edge).
      ((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_node_index)->n_edges_between = int(value);
      if (int(value) > 0)
      {
        is_parsing_artificial_info = true;
        // There are now artificial edges information regarding this pair.
        ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_node_index)).edges_between_info)->edge_label = -1;
      }
      artifial_edge_info_counter = int(value);
      pair_node_index++;
      break;
    default :
      break;
  }
}

void Instance::setNodePairEdgeData(int value_index, double value, int &main_node_index, int &pair_node_index, bool &is_parsing_artificial_info, int &artifial_edge_info_counter, int &nodes_can_be_served_counter) {
  int pair_aux = pair_node_index -1;
  int edge_label_aux = ((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_aux)->n_edges_between;
  switch(value_index) {
    case 0 :
      ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_aux)).edges_between_info + (edge_label_aux - artifial_edge_info_counter))->edge_label = int(value);
      break;
    case 1 :
      ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_aux)).edges_between_info + (edge_label_aux - artifial_edge_info_counter))->start_x_axis = value;
      break;
    case 2 :
      ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_aux)).edges_between_info + (edge_label_aux - artifial_edge_info_counter))->start_y_axis = value;
      break;
    case 3 :
      ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_aux)).edges_between_info + (edge_label_aux - artifial_edge_info_counter))->end_x_axis = value;
      break;
    case 4 :
      ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_aux)).edges_between_info + (edge_label_aux - artifial_edge_info_counter))->end_y_axis = value;
      break;
    case 5 :
      ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_aux)).edges_between_info + (edge_label_aux - artifial_edge_info_counter))->length = value;
      break;
    case 6 :
      // Number of artificial edges information data Ex.: if = 2 -> .
      ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_aux)).edges_between_info + (edge_label_aux - artifial_edge_info_counter))->n_nodes_can_serve = int(value);
      if (int(value) > 0)
      {
        //Probably error here too.
        ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_aux)).edges_between_info + (edge_label_aux - artifial_edge_info_counter))->ids_nodes_can_serve = new int[int(value) - 1];        
      }
      nodes_can_be_served_counter = int(value);
      break;
    default :
      // Number of artificial edges information data.
      int total_edges_edges_to_parse = ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_aux)).edges_between_info + (edge_label_aux - artifial_edge_info_counter))->n_nodes_can_serve;
      // id index within pointer: total - (total_aux - i) - i:0,1,2...
      int index_id_node_can_be_served = total_edges_edges_to_parse - nodes_can_be_served_counter;
      if (index_id_node_can_be_served < total_edges_edges_to_parse)
      {
        *((((original_nodes + main_node_index)->paired_with_nodes_info + pair_aux)->edges_between_info + (edge_label_aux - artifial_edge_info_counter))->ids_nodes_can_serve + index_id_node_can_be_served) = int(value);
        nodes_can_be_served_counter--; // Decreasing account for the accounting of an id I can serve. Ex.: 4 -> 3 == "Out of 4 id's there are 3 left to set"
      } else {
        artifial_edge_info_counter--;
        // Counter 'index_id_node_can_be_served' has the same value as the amount of artificial edegs -> 'nodes_can_be_served_counter' == 0
      }
      // Out of 'n' ids, how many have i set?
      // if (index_id_node_can_be_served > ((original_nodes + main_node_index)->paired_with_nodes_info + pair_aux)->n_edges_between)
      int label_aux = ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_aux)).edges_between_info + (edge_label_aux - artifial_edge_info_counter))->edge_label;
      int n_edges_between_aux = ((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_aux)->n_edges_between;

      if (nodes_can_be_served_counter == 0 && (label_aux == n_edges_between_aux))
      {
        // Not parsing segmented edge information anymore.
        // Set 'is_parsing_artificial_info' to false.
        is_parsing_artificial_info = false;        
      }
      // If next pair counter equals the number of total original nodes
      // then the main pair must be increased and the next pair must be set to zero again
      int actual_last_pair_node_index_processed = (pair_node_index-1)
      if (actual_last_pair_node_index_processed == getNumberOfOriginalNodes())
      {
        main_node_index++;
        pair_node_index = 0;
      }
      // If the main index counter equals the total number of original vertices
      // then resume processing graph in the txt.
      if (main_node_index == getNumberOfOriginalNodes())
      {
        // finish the program here.
        return;
      }
      break;
  }
}

void Instance::pauseExecution(int line, string str) { /* Pauses the execution of the program for debbuging purposes */
  cout << "\n[ EXECUTION PAUSED ON LINE '" << line << "' of file '" << str << "' ] _";
  int pause = 0;
  cin >> pause;
  cout << endl;
  return;
}

void Instance::printPairsFromMainNode(int main_node_index) {  
  for (int i = 0; i < original_nodes_n; ++i)
  {
    cout << main_node_index << " ";
    cout << ((*(original_nodes + main_node_index)).paired_with_nodes_info + i)->pair_id << " ";
    cout << ((*(original_nodes + main_node_index)).paired_with_nodes_info + i)->distance << " ";
    cout << ((*(original_nodes + main_node_index)).paired_with_nodes_info + i)->n_edges_between << endl;
    // for (int j = 0; j < ((*(original_nodes + main_node_index)).paired_with_nodes_info + i)->n_edges_between; ++j)
    // {
    //   cout << ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + i)).edges_between_info + j)->edge_label << " ";
    //   cout << ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + i)).edges_between_info + j)->start_x_axis << " ";
    //   cout << ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + i)).edges_between_info + j)->start_y_axis << " ";
    //   cout << ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + i)).edges_between_info + j)->end_x_axis << " ";
    //   cout << ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + i)).edges_between_info + j)->end_y_axis << " ";
    //   cout << ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + i)).edges_between_info + j)->length << " ";
    //   cout << ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + i)).edges_between_info + j)->n_nodes_can_serve << " ";
    //   for (int k = 0; k < ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + i)).edges_between_info + j)->n_nodes_can_serve; ++k)
    //   {
    //     cout << *((((original_nodes + main_node_index)->paired_with_nodes_info + i)->edges_between_info + j)->ids_nodes_can_serve + k) << " ";
    //   }
    //   cout << endl;
    // }
    // cout << endl;
  }
}

// cout << ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_aux)).edges_between_info + 1)->edge_label << endl;
// cout << ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_aux)).edges_between_info + 1)->start_x_axis << endl;
// cout << ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_aux)).edges_between_info + 1)->start_y_axis << endl;
// cout << ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_aux)).edges_between_info + 1)->end_x_axis << endl;
// cout << ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_aux)).edges_between_info + 1)->end_y_axis << endl;
// cout << ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_aux)).edges_between_info + 1)->length << endl;
// cout << ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_aux)).edges_between_info + 1)->n_nodes_can_serve << endl;

// cout << "Main: " << main_node_index << endl;
// cout << "Pair: " << pair_aux << endl;
// cout << "Edge: " << (edge_label_aux - artifial_edge_info_counter) << endl;
// cout << "----------------------------------------------" << endl;
// cout << ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_aux)).edges_between_info + (edge_label_aux - artifial_edge_info_counter))->edge_label << endl;
// cout << "----------------------------------------------" << endl;

/* Private methods */
 