#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cstring>
#include <cctype>
#include <array>	
#include <time.h>

#include "instance_class.h"

using namespace std;

void print(Instance *inst) { /* Sets the value of the i-th possible speed to 's' */
  inst->printSpeeds();
  return;
}

void test(ifstream& instance_file) {
	
}

void initialInstanceData(int value_index, double value, Instance *inst) {
	int speed_counter = 0;
	switch(value_index) {
		case 0 :
			cout << " setting original graph's node count: " << int(value) << endl;
			inst->setOriginalNodesNumber(int(value));
			break;
		case 1 :
			cout << " setting final graph's node count: " << int(value) << endl;
			inst->setTotalNodesNumber(int(value));
			break;
		case 2 :
			cout << " setting allowed speeds count: " << int(value) << endl;
			inst->setSpeedNumber(int(value));
			break;
		default :
			cout << " setting speed " << (value_index - 3) << " value: " << value << endl;
			inst->setSpeed((value_index - 3), value);
	}

	return;
}

void setOriginalNodeData(int line_index, int value_index, double value, Instance *inst) {
	switch(value_index) {
		case 0 :
			inst->setNodeX((line_index - 1), value);
			break;
		case 1 :
			inst->setNodeY((line_index - 1), value);
			break;
		case 2 :
			inst->setNodeCRange((line_index - 1), value);
			break;
		case 3 :
			inst->setNodeTRate((line_index - 1), value);
			break;
		case 4 :
			inst->setNodeDemmand((line_index - 1), value);
			break;
		default :
			break;
	}
	
	return;
}

void setNodesPairData(int value_index, double value, Instance *inst, int &main_node_index, int &pair_node_index, bool &is_parsing_artificial_info, int &artifial_edge_info_counter) {
	inst->setNodePair(value_index, value, main_node_index, pair_node_index, is_parsing_artificial_info, artifial_edge_info_counter);
	return;
}

void setNodesPairSegmentedEdgeData(int value_index, double value, Instance *inst, int &main_node_index, int &pair_node_index, bool &is_parsing_artificial_info, int &artifial_edge_info_counter, int &nodes_can_be_served_counter) {
	inst->setNodePairEdgeData(value_index, value, main_node_index, pair_node_index, is_parsing_artificial_info, artifial_edge_info_counter, nodes_can_be_served_counter);
	return;
}

void fileLineHandler(int line_index, int value_index, double value, Instance *inst, int &main_node_index, int &pair_node_index, bool &is_parsing_artificial_info, int &artifial_edge_info_counter, int &nodes_can_be_served_counter) {
	if (line_index == 0)
	{
		// cout << "	Accessing general metadata header... ";
        initialInstanceData(value_index, value, inst);
	} else if (line_index > 0 && line_index < (inst->getNumberOfOriginalNodes() + 1))
	{
        setOriginalNodeData(line_index, value_index, value, inst); 
	} else if ((line_index > inst->getNumberOfOriginalNodes()) && !is_parsing_artificial_info)
	{
		artifial_edge_info_counter = 0; /* Reseting */
		nodes_can_be_served_counter = 0; /* Reseting */
		// cout << "	Processing artifially created graphs data..." << endl;
		setNodesPairData(value_index, value, inst, main_node_index, pair_node_index, is_parsing_artificial_info, artifial_edge_info_counter);
	} else if ((line_index > inst->getNumberOfOriginalNodes()) && is_parsing_artificial_info)
	{
		// cout << "	Processing artifially created edge metadata...";
		// cout << value << endl;
		setNodesPairSegmentedEdgeData(value_index, value, inst, main_node_index, pair_node_index, is_parsing_artificial_info, artifial_edge_info_counter, nodes_can_be_served_counter);
	} else {
		cout << " SHOULD NOT HAVE ENTERED HERE " << endl;
	}
}

void consumeInstance(ifstream& instance_file, Instance *inst) {
	string str;
	int line_index = 0;

	cout << "Reading through instace file lines: " << endl;

	int main_node_index = 0;
    int pair_node_index = 0;
    int artifial_edge_info_counter = 0;
    int nodes_can_be_served_counter = 0;
    bool is_parsing_artificial_info = false;

	while(getline(instance_file, str)) {
	    string parsed_line = "";
	    int n_of_values = 0;
	    double *values = new double[100];

	    for(char& c : str) {
	      parsed_line += isspace(c) ? ',' : c;
	    }

	    while(parsed_line != "") {
	      string number = parsed_line.substr(0, parsed_line.find(","));
	      parsed_line.erase(0, (number.length() + 1));

	      (*(values + n_of_values)) = stod(number);
	      n_of_values++;
	    }

	    /* Numerical content of the n-th line i the file */
	    for (int i = 0; i < n_of_values; ++i)
	    {
	    	cout << (*(values + i)) << "*" << endl;
	    	fileLineHandler(line_index, i, (*(values + i)), inst, main_node_index, pair_node_index, is_parsing_artificial_info, artifial_edge_info_counter, nodes_can_be_served_counter);
	    }

	    line_index++;
  }

  return;
}