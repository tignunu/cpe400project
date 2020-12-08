//CPE 400 Project 2020
//Dynamic Routing Mechanism Design in Faulty Network

//Mari Trombley, Skylar Glock, Henry Strum

#include "Node.h"
#include <stdlib.h>
#include <time.h>

#define NUM_NODES 10

using namespace std;

//creates inital edges between two nodes
void createEdges(char nodeOne, char nodeTwo, map<char, Node*> nodeMap);

//simulate edge failure
void edgeFailure(char nodeOne, char nodeTwo, map<char, Node*> nodeMap);

//checks if two nodes are connected
bool connected(char nodeOne, char nodeTwo, map<char, Node*> nodeMap);

//sends request out to find path
void sendRequest(map<char, Node*> nodeMap, char src, int requestNum, char dst, char Nodes[]);


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
	nodeMap.insert(pair<char, Node*>('A', A.location()));
	nodeMap.insert(pair<char, Node*>('B', B.location()));
	nodeMap.insert(pair<char, Node*>('C', C.location()));
	nodeMap.insert(pair<char, Node*>('D', D.location()));
	nodeMap.insert(pair<char, Node*>('E', E.location()));
	nodeMap.insert(pair<char, Node*>('F', F.location()));
	nodeMap.insert(pair<char, Node*>('G', G.location()));
	nodeMap.insert(pair<char, Node*>('H', H.location()));
	nodeMap.insert(pair<char, Node*>('I', I.location()));
	nodeMap.insert(pair<char, Node*>('J', J.location()));

	//create edges between nodes
	createEdges('A', 'B', nodeMap);
	createEdges('A', 'D', nodeMap);
	createEdges('A', 'C', nodeMap);
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
	cout << "**************Begin random node failure test while routing**************" << endl;

	for (int j = 1; j < 6; ++j)
	{
		int seed = time(NULL);
		srand(seed);
		char failedNode1 = Nodes[rand() % NUM_NODES];
		char failedNode2 = Nodes[rand() % NUM_NODES];
		char failedNode3 = Nodes[rand() % NUM_NODES];
		char failedNode4 = Nodes[rand() % NUM_NODES];
		edgeFailure(failedNode1, failedNode2, nodeMap);
		edgeFailure(failedNode3, failedNode4, nodeMap);
		edgeFailure(failedNode1, failedNode3, nodeMap);
		edgeFailure(failedNode2, failedNode4, nodeMap);


		cout << endl << "Random failure test " << j << "..." << endl;
		cout << "Edge failure between " << failedNode1 << " and " << failedNode2 << endl;
		cout << "Edge failure between " << failedNode3 << " and " << failedNode4 << endl;
		cout << "Edge failure between " << failedNode1 << " and " << failedNode3 << endl;
		cout << "Edge failure between " << failedNode2 << " and " << failedNode4 << endl;

		sendRequest(nodeMap, 'A', i, 'J', Nodes);
		i++;
		createEdges(failedNode1, failedNode2, nodeMap);
		createEdges(failedNode3, failedNode4, nodeMap);
		createEdges(failedNode1, failedNode3, nodeMap);
		createEdges(failedNode2, failedNode4, nodeMap);
	}

	cout << endl << "**************Finished random node failure test**************" << endl << endl;

	return 0;
}


//creates inital edges between two nodes
void createEdges(char nodeOne, char nodeTwo, map<char, Node*> nodeMap)
{
	Node *nodeOnePtr = nodePtr(nodeOne, nodeMap);
	Node *nodeTwoPtr = nodePtr(nodeTwo, nodeMap);

	nodeOnePtr->addNeighbor(nodeTwo, nodeTwoPtr);
	nodeTwoPtr->addNeighbor(nodeOne, nodeOnePtr);
}


//simulate edge failure
void edgeFailure(char nodeOne, char nodeTwo, map<char, Node*> nodeMap)
{
	Node *nodeOnePtr = nodePtr(nodeOne, nodeMap);
	Node *nodeTwoPtr = nodePtr(nodeTwo, nodeMap);

	nodeOnePtr->removeNeighbor(nodeTwo);
	nodeTwoPtr->removeNeighbor(nodeOne);
}


//checks if two nodes are connected
bool connected(char nodeOne, char nodeTwo, map<char, Node*> nodeMap)
{
	return nodePtr(nodeOne, nodeMap)->neighborCheck(nodeTwo);
}


void sendRequest(map<char, Node*> nodeMap, char src, int requestNum, char dst, char Nodes[])
{
//this simulates an RREQ message
	time_t start = time(0);
	Node * currentNode = nodePtr(src, nodeMap);
	currentNode->pathCheck = true;
	bool success = false;
	
	//currentNode refers to current node being traversed
	//originator refers to where RREQ was started
	
	vector<char> neighborVector;
	while(1)
	{
		bool alreadyChecked = true;
		//did currentNode already ask its neighbors to check for (originator_of_RREQ, request_ID)? if so, ignore this RREQ
		for(int i = 0; i < currentNode->prerequest.size(); i++)
		{
			if(	currentNode->prerequest[i].requestSource == src &&
				currentNode->prerequest[i].idRequest == requestNum)
			{
				alreadyChecked = false; //ignore
			}
		}
		//no previous ask? so now currentNode will check its neighbors then and ask each of its neighbors
		if(alreadyChecked)
		{
			//save this RREQ to previous requests
			checkRequest insert_record = {src, requestNum};
			currentNode-> prerequest.push_back(insert_record);
			//if currentNode is desired node, no need to ask neighbors
			if(currentNode->name != dst)
			{
				//for each of currentNode’s neighbors, ask RREQ
				for(map<char, Node*>::const_iterator i = currentNode->nodeNeighbor.begin(); i != currentNode->nodeNeighbor.end(); i++)
				{
					Node * neighbor_node = i->second;
					if(neighbor_node->pathCheck == false)
					{
						//send neighbor_node current path taken from originator
						neighbor_node->requestString = (currentNode->requestString + (currentNode->name));
						neighbor_node->pathCheck = true;
						if(neighbor_node->name == dst)
						{ 
						//found dst!
							cout 	<< "Node " << neighbor_node->name << " received a request from Node " << currentNode->name
									<< " to get to this node! So, begin reply ["
									<< (neighbor_node->requestString + neighbor_node->name) << "]" << endl;
							//now, begin journey back to RREQ originator by starting RREP
							neighbor_node->getReply(dst, src, neighbor_node->requestString, (neighbor_node->requestString).size(), dst);
							success = true;
						}
						else
						{
						//did not find, so neighbor_node will now ask its neighbors
							cout	<< "Node " << neighbor_node->name << " received a request from Node " << currentNode->name
									<< " to get to Node " << dst << ", list of identifiers: " << neighbor_node->requestString << endl;
									success = false;
						}
					}
					//add neighbor_node to queue, to forward RREQ
					neighborVector.push_back(i->first);
				}
			}
			else
			{
				//do nothing
			}
		}
		//update currentNode to next in queue
		if(neighborVector.size() > 0)
		{
			currentNode = nodePtr(neighborVector[0], nodeMap);
			neighborVector.erase(neighborVector.begin());
		}
		//no response after 1.0 seconds means dst isn't in network
		if(difftime(time(0), start) > 1.0)
		{
			//Node * verify = nodePtr(src, nodeMap);
			if(!success)//currentNode->name != dst)
			{
				cout << "No route could be found from Node " << src << " to Node " << dst << endl;
				cout << "(Too many edges down)" << endl;
			}
			break;
		}
	}
	//reset received
	Node * reset_node = NULL;
	for(int i=0; i<NUM_NODES; i++)
	{	reset_node = nodePtr(Nodes[i], nodeMap);
		reset_node->pathCheck = false;
		reset_node->replyString = "";
		reset_node->requestString = "";
	}
	Node * reset_source_node = nodePtr(src, nodeMap);
	reset_source_node->replyCheck = false;
	reset_source_node->replyString = "";
	reset_source_node->requestString = "";
}