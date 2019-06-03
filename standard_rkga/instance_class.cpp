#include <iostream>
#include <array>
#include <stdlib.h>
#include <fstream>

#include "instance_class.h"

using namespace std;

/* Public methods */

/*
  orig_nodes_n: number of original nodes
  total_nodes: number of total nodes after graphs pre-processing
  speeds_count: number of allowed speeds
*/
Instance::Instance() {
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
    node_i.c_range = (i + 0.1);
    node_i.t_rate = 0.0; 
    node_i.demmand = 0.0;

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

  (*(original_nodes + index)).x_axis = x;

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

/* Private methods */
