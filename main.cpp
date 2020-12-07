//CPE 400 Project 2020
//Dynamic Routing Mechanism Design in Faulty Network

//Mari Trombley, Skylar Glock, Henry Strum

#include "Node.h"
//#include <time.h>

#define NUM_NODES 10

using namespace std;

//creates inital edges between two nodes
void createEdges(char nodeOne, char nodeTwo, map<char, Node*> nodeMap);

//simulate edge failure
void edgeFailure(char nodeOne, char nodeTwo, map<char, Node*> nodeMap);

//simulate node failure
//void nodeFailure(char node, map<char, Node*> nodeMap);

//restore failed node
//void nodeRestore(char node, map<char, Node*> nodeMap);

//checks if two nodes are connected
bool connected(char nodeOne, char nodeTwo, map<char, Node*> nodeMap);

//sends request out to find path
void sendRequest(map<char, Node*> nodeMap, char source, int requestNum, char destination, char Nodes[]);


int main(int argc, char const *argv[])
{
	char Nodes[NUM_NODES] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

	//create all nodes
	map<char, Node*>	nothing;
	map<char, Node*>	nodeMap;
	Node				A('A', nothing);
	Node				B('B', nothing);
	Node				C('C', nothing);
	Node				D('D', nothing);
	Node				E('E', nothing);
	Node				F('F', nothing);
	Node				G('G', nothing);
	Node				H('H', nothing);
	Node				I('I', nothing);
	Node				J('J', nothing);

	//define map
	nodeMap.insert(pair<char, Node*>('A', A.memory_location()));
	nodeMap.insert(pair<char, Node*>('B', B.memory_location()));
	nodeMap.insert(pair<char, Node*>('C', C.memory_location()));
	nodeMap.insert(pair<char, Node*>('D', D.memory_location()));
	nodeMap.insert(pair<char, Node*>('E', E.memory_location()));
	nodeMap.insert(pair<char, Node*>('F', F.memory_location()));
	nodeMap.insert(pair<char, Node*>('G', G.memory_location()));
	nodeMap.insert(pair<char, Node*>('H', H.memory_location()));
	nodeMap.insert(pair<char, Node*>('I', I.memory_location()));
	nodeMap.insert(pair<char, Node*>('J', J.memory_location()));

	//create edges between nodes
	createEdges('A', 'B', nodeMap);
	createEdges('A', 'D', nodeMap);
	createEdges('A', 'E', nodeMap);
	createEdges('A', 'G', nodeMap);
	createEdges('B', 'C', nodeMap);
	createEdges('C', 'D', nodeMap);
	createEdges('D', 'E', nodeMap);
	createEdges('D', 'F', nodeMap);
	createEdges('E', 'F', nodeMap);
	createEdges('E', 'H', nodeMap);
	createEdges('E', 'J', nodeMap);
	createEdges('F', 'G', nodeMap);
	createEdges('G', 'H', nodeMap);
	createEdges('G', 'I', nodeMap);
	createEdges('H', 'I', nodeMap);
	createEdges('H', 'J', nodeMap);
	createEdges('I', 'J', nodeMap);

	//begin simulation
	int i = 0;
	char nodeChoice;
	cout << "****Simple edge and node failure test****" << endl << endl;
	cout << "Finding path from node A to J" << endl;
	sendRequest(nodeMap, 'A', i, 'J', Nodes[]);
	i++;

	cout << "Simulating Edge failure from E to J..." << endl;
	edgeFailure('E', 'J', nodeMap);

	cout << "Finding new path from node A to J..." << endl;
	sendRequest(nodeMap, 'A', i, 'J', Nodes[]);
	i++;

	cout << "Restoring failed Edge..." << endl;
	createEdges('E', 'J', nodeMap);

	cout << "Choose a node to fail: ";
	cin >> nodeChoice;
	//nodeFailure(nodeChoice, nodeMap);

	cout << "Finding new path from node A to J..." <<endl;
	sendRequest(nodeMap, 'A', i, 'J', Nodes[]);
	i++;

	cout << "Restoring failed node..." << endl;
	//nodeRestore(nodeChoice, nodeMap);


	cout << "****Finished simple tests****" << endl << endl;
	cout << "****Begin random node failure test while routing****" << endl << endl;

	for (int j = 0; j < 10; ++j)
	{
		failedNode1 = Node[rand() % NUM_NODES];
		failedNode2 = Node[rand() % NUM_NODES];
		//nodeFailure(failedNode1, nodeMap);
		//nodeFailure(failedNode2, nodeMap);

		cout << "Random failure test " << j << "..." << endl;
		sendRequest(nodeMap, 'A', i, 'J', Nodes[]);
		i++;
		//nodeRestore(failedNode1, nodeMap);
		//nodeRestore(failedNode2, nodeMap);
	}

	cout << "****Finished random node failure test****" << endl << endl;

	return 0;
}


//creates inital edges between two nodes
void createEdges(char nodeOne, char nodeTwo, map<char, Node*> nodeMap)
{
	Node *nodeOnePtr = node_ptr(nodeOne, nodeMap);
	Node *nodeTwoPtr = node_ptr(nodeTwo, nodeMap);

	nodeOnePtr->addNeighbor(nodeTwo, nodeTwoPtr);
	nodeTwoPtr->addNeighbor(nodeOne, nodeOnePtr);
}


//simulate edge failure
void edgeFailure(char nodeOne, char nodeTwo, map<char, Node*> nodeMap)
{
	Node *nodeOnePtr = node_ptr(nodeOne, nodeMap);
	Node *nodeTwoPtr = node_ptr(nodeTwo, nodeMap);

	nodeOnePtr->deleteNeighbor(nodeTwo, nodeTwoPtr);
	nodeTwoPtr->deleteNeighbor(nodeOne, nodeOnePtr);
}


//simulate node failure
//TODO


//restore failed nodes
//TODO


//checks if two nodes are connected
bool connected(char nodeOne, char nodeTwo, map<char, Node*> nodeMap)
{
	return pointer_for_node(first_node, nodeMap)->am_I_connected(second_node);
}


//chooses which edges/nodes to simulate failure on (Needed?)
//TODO