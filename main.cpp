//CPE 400 Project 2020
//Dynamic Routing Mechanism Design in Faulty Network

//Mari Trombley, Skylar Glock, Henry Strum

#include "Node.h"
//#include <time.h>

#define NUM_NODES 10

using namespace std;

//sends request out to find path
void sendRequest(map<char, Node*> nodeMap, char source, int requestNum, char destination, char Nodes[]);

//creates inital edges between two nodes
void createEdges(char nodeOne, char nodeTwo, map<char, Node*> nodeMap);

//checks if two nodes are connected
bool connected(char nodeOne, char nodeTwo, map<char, Node*> nodeMap);

//node pointer function (move this to node.h)////////////////////////////////
Node *nodePtr(char node, map<char, Node*> nodeMap)
{
	map<char, Node*>::iterator find = nodemap.find(node);
	return (find->second);
}
/////////////////////////////////////////////////////////////////////////////


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
	createEdges('A', 'G', nodeMap);
	createEdges('A', 'I', nodeMap);
	createEdges('B', 'C', nodeMap);
	createEdges('C', 'D', nodeMap);
	createEdges('D', 'E', nodeMap);
	createEdges('D', 'F', nodeMap);
	createEdges('E', 'F', nodeMap);
	createEdges('E', 'H', nodeMap);
	createEdges('E', 'K', nodeMap);
	createEdges('F', 'G', nodeMap);
	createEdges('G', 'H', nodeMap);
	createEdges('G', 'I', nodeMap);
	createEdges('H', 'I', nodeMap);
	createEdges('H', 'J', nodeMap);
	createEdges('H', 'K', nodeMap);
	createEdges('I', 'J', nodeMap);

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


//checks if two nodes are connected
bool connected(char nodeOne, char nodeTwo, map<char, Node*> nodeMap)
{
	return pointer_for_node(first_node, nodeMap)->am_I_connected(second_node);
}


//chooses which edges/nodes to simulate failure on (Needed?)
//TODO