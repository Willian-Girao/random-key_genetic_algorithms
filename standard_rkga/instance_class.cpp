#include <iostream>
#include <array>
#include <stdlib.h>
#include <fstream>
#include <string>

#include "instance_class.h"

using namespace std;

/* Public methods */
Instance::Instance() {}

Instance::~Instance() {
  cout << "asdsds\n";
  delete []speeds;  
  cout << "end\n";
  delete []original_nodes;
  cout << "end2\n";
  // delete []original_nodes->paired_with_nodes_info->edges_between_info;
  // delete []original_nodes->paired_with_nodes_info;
  // delete []original_nodes;  
  cout << "end\n";
}

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

/* Sets up information associated to a pair of nodes in the file - [int main_node_id, int pair_node_id, double distance, int artificial_edges_between] */
void Instance::setNodePair(int value_index, double value, int &main_node_index, int &pair_node_index, bool &is_parsing_artificial_info, int &artifial_edge_info_counter, bool &done) {  
  switch(value_index) {
    case 0 :
      /* ID of the current main node of the pair - should be equal to 'main_node_index' */      
      main_node_index = int(value);      
      break;
    case 1 :
      /* ID of the node being paired with the main node - should be equal to 'pair_node_index' */
      pair_node_index = int(value);
      (*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_node_index)).pair_id = int(value);
      break;
    case 2 :
      /* Distance between the two nodes */
      (*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_node_index)).distance = value;
      break;
    case 3 :
      /* Number of artificial edges (segments of the original edge) between the two nodes */            
      (*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_node_index)).n_edges_between = int(value); // Setting number of artificial edges (segmentation of an original edge)
      (*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_node_index)).edges_between_info = new EdgeData[int(value)]; // Initializing data struct to hold information regarding to artificial edges (segmented due to the presence of an artidial vertex)      

      if (int(value) > 0) // There is information regarding the artificial edges to be processed
      {
        is_parsing_artificial_info = true;
        artifial_edge_info_counter = int(value); // Value will be decreased while parsing artificial info in order to know the list positioning of the i-th artificial edge data
      } else 
      {
        // There is no artificial edge information -> no change in the line controlling parameters required
      }
      // cout << "main: " << main_node_index << " pair: " << pair_node_index << endl;
      cout << "node pair info just set: " << main_node_index << " ";
      cout << ((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_node_index)->pair_id << " ";
      cout << ((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_node_index)->distance << " ";
      cout << ((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_node_index)->n_edges_between << endl;
      // cout << "\n----------------------------------------------------------------------------" << endl;
      // cout << ((*(original_nodes + 0)).paired_with_nodes_info + 5)->pair_id << " ";
      // cout << ((*(original_nodes + 0)).paired_with_nodes_info + 5)->distance << " ";
      // cout << ((*(original_nodes + 0)).paired_with_nodes_info + 5)->n_edges_between << endl;
      // cout << "----------------------------------------------------------------------------" << endl;
      // pauseExecution(5,"PAIR LINE HAS JUST BEEN PARSED");
      if (main_node_index == (getNumberOfOriginalNodes()-1) && pair_node_index == (getNumberOfOriginalNodes()-1))
      {
        done = true;        
      }
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
  int total_artificial_edges = ((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_node_index)->n_edges_between;
  int artificial_edge_pointer_index_counter = (total_artificial_edges - artifial_edge_info_counter); // Value starts as '0' and increases until it reaches...  
  switch(value_index) {
    case 0 :
      /* Artificial edge "label" */
      ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_node_index)).edges_between_info + artificial_edge_pointer_index_counter)->edge_label = int(value);
      break;
    case 1 :
      /* Artificial edge starting node x axis */
      ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_node_index)).edges_between_info + artificial_edge_pointer_index_counter)->start_x_axis = value;
      break;
    case 2 :
      /* Artificial edge starting node y axis */
      ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_node_index)).edges_between_info + artificial_edge_pointer_index_counter)->start_y_axis = value;
      break;
    case 3 :
      /* Artificial edge ending node x axis */
      ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_node_index)).edges_between_info + artificial_edge_pointer_index_counter)->end_x_axis = value;
      break;
    case 4 :
      /* Artificial edge ending node y axis */
      ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_node_index)).edges_between_info + artificial_edge_pointer_index_counter)->end_y_axis = value;
      break;
    case 5 :
      /* Artificial edge length */
      ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_node_index)).edges_between_info + artificial_edge_pointer_index_counter)->length = value;
      break;
    case 6 :
      /* Number of original nodes that can be served while crossing this artificial edge */
      ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_node_index)).edges_between_info + artificial_edge_pointer_index_counter)->n_nodes_can_serve = int(value);

      if (int(value) > 0)
      {
        /* There are nodes that can be served */
        ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_node_index)).edges_between_info + artificial_edge_pointer_index_counter)->ids_nodes_can_serve = new int[int(value) - 1];        
      } else
      {
        /* There are no nodes that can be served */        
        ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_node_index)).edges_between_info + artificial_edge_pointer_index_counter)->ids_nodes_can_serve = new int[1];

        // "Label" of the current artificial edge being processed
        int current_artificial_edge_label = ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_node_index)).edges_between_info + artificial_edge_pointer_index_counter)->edge_label;
        // Total of artificial edges that must be processed
        int number_of_artificial_edges_to_process = ((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_node_index)->n_edges_between;
        // Tells me if the current line being processd is the last artificial edge to be processed for now
        bool is_last_artificial_edge = (current_artificial_edge_label == number_of_artificial_edges_to_process);

        if (is_last_artificial_edge)
        {
          /* This is the last artificial edge to be processed and the next line regards to node->pair information */
          is_parsing_artificial_info = false;
        }
      }

      nodes_can_be_served_counter = int(value); // Counter will be decreased in order to calculate the index of the processed "served node id" within the list of ids that can be served while passing through this edge
      // if (((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_node_index)->distance == 989)
      // {
      //   cout << "\n----------------------------------------------------------------------------" << endl;
      //   cout << ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_node_index)).edges_between_info + artificial_edge_pointer_index_counter)->length << endl;
      //   cout << "----------------------------------------------------------------------------" << endl;
      //   pauseExecution(int(value),"HERE");
      // }
      break;
    default :
      if (value_index > 6)
      {
        int number_nodes_can_be_served = ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_node_index)).edges_between_info + artificial_edge_pointer_index_counter)->n_nodes_can_serve;
        // if (((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_node_index)->distance == 989)
        // {
        //   cout << "\n----------------------------------------------------------------------------" << endl;
        //   cout << ((*(original_nodes + 1)).paired_with_nodes_info + 0)->pair_id << " ";
        //   cout << ((*(original_nodes + 1)).paired_with_nodes_info + 0)->distance << " ";
        //   cout << ((*(original_nodes + 1)).paired_with_nodes_info + 0)->n_edges_between << endl;
        //   cout << "----------------------------------------------------------------------------" << endl;
        //   pauseExecution(int(value),"HERE");
        // }

        // 'index_id_node_can_be_served' is the value that will be added to the pointer that points to the ids that can be served while in this edge
        int index_id_node_can_be_served = number_nodes_can_be_served - nodes_can_be_served_counter; // Value starts as '0' and increases until it is equal to the number of ids i can serve

        // Ex.: number of nodes i can serve equals to 1 AND 'index_id_node_can_be_served' starts as 0 (always) -> when 'index_id_node_can_be_served' reaches '1' it means I've already parsed all the ids
        if (index_id_node_can_be_served < number_nodes_can_be_served)
        {
          *((((original_nodes + main_node_index)->paired_with_nodes_info + pair_node_index)->edges_between_info + artificial_edge_pointer_index_counter)->ids_nodes_can_serve + index_id_node_can_be_served) = int(value);
          nodes_can_be_served_counter--; // Decreasing account for the accounting of an id I can serve. Ex.: 4 -> 3 == "Out of 4 id's there are 3 left to set"
        } else
        {
          /* There are no nodes that can be served while in this edge */
        }
        
        // "Label" of the current artificial edge being processed
        int current_artificial_edge_label = ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_node_index)).edges_between_info + artificial_edge_pointer_index_counter)->edge_label;
        // Total of artificial edges that must be processed
        int number_of_artificial_edges_to_process = ((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_node_index)->n_edges_between;
        // Tells me if the current line being processd is the last artificial edge to be processed for now
        bool is_last_artificial_edge = (current_artificial_edge_label == number_of_artificial_edges_to_process);

        // 'nodes_can_be_served_counter' will equal to '0' in two cases:
        //    1 - current artificial edge being processed can't serve no original node
        //    2 - i have already processed all the ids of the nodes that can be served in this edge
        if ((nodes_can_be_served_counter == 0) && is_last_artificial_edge)
        {          
          /* Not parsing segmented edge information anymore */
          is_parsing_artificial_info = false;
        } else if (nodes_can_be_served_counter == 0)
        {
          /* There are no nodes that can be served while in this edge - just go to the next line in the file */
        } else
        {
          /* There are still ids of nodes that can be served to be parsed - do nothing here */
          //TODO make sure next line must really stay commented out
          // pauseExecution(372,"WARNING - Uncaught case in file line 'instance_class.cpp'.");
        }        
      }
      break;
  }
}

void Instance::pauseExecution(int line, string str) { /* Pauses the execution of the program for debbuging purposes */
  cout << "\n[ EXECUTION PAUSED ON LINE '" << line << "' -> '" << str << "' ] _: ";
  int pause = 0;
  cin >> pause;
  cout << endl;
  return;
}

void Instance::printPairsFromMainNode(int main_node_index, int pair_index) {
  cout << main_node_index << " ";
  cout << ((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_index)->pair_id << " ";
  cout << ((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_index)->distance << " ";
  cout << ((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_index)->n_edges_between << endl;
  for (int i = 0; i < original_nodes_n; ++i)
  {
    // cout << main_node_index << " ";
    // cout << ((*(original_nodes + main_node_index)).paired_with_nodes_info + i)->pair_id << " ";
    // cout << ((*(original_nodes + main_node_index)).paired_with_nodes_info + i)->distance << " ";
    // cout << ((*(original_nodes + main_node_index)).paired_with_nodes_info + i)->n_edges_between << endl;
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
// cout << "Edge: " << artificial_edge_pointer_index_counter << endl;
// cout << "----------------------------------------------" << endl;
// cout << ((*((*(original_nodes + main_node_index)).paired_with_nodes_info + pair_aux)).edges_between_info + (edge_label_aux - artifial_edge_info_counter))->edge_label << endl;
// cout << "----------------------------------------------" << endl;

/* Private methods */
 