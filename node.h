//CPE 400 Project 2020
//Dynamic Routing Mechanism Design in Faulty Network

//Mari Trombley, Skylar Glock, Henry Strum

#include <iostream>
#include <vector>
#include <string>

#include <map>
#include <time.h>

using namespace std;

class Node{
    public:
            Node(char nodeChar, map < char, Node *> neighbors);
            Node& operator = (const Node& other);
            Node * location();

            char name;
            bool pathCheck;
            bool replyCheck;

            string requestString;
            string replyString;

            vector<checkRequest> prerequest;
            map<char, Node*> nodeNeighbor;

            void setNeighbor(map < char, Node *> neighbors);
            void addNeighbor(char name, Node * location);
            void removeNeighbor(char name);
            void getReply(char src, char dst, string requestReply, int size, char replySource);

            bool neighborCheck(char name);
            
};

struct checkRequest{
    char requestSource;
    int idRequest;
};

Node::Node(char nodeChar, map < char, Node *> neighbors){
    name = nodeChar;
    setNeighbor(neighbors);
    pathCheck = false;
    replyCheck = false;
}


Node::Node& operator = (const Node& other){
    if(this == &rhs) return * this;
    return * this;
}

Node::Node * location(){
    return this;
}


void Node::setNeighbor(map < char, Node *> neighbors){
    nodeNeighbor = neighbor;
}

void Node::addNeighbor(char name, Node * location){
    nodeNeighbor.insert(pair<char, Node *> (name, location));
}

void Node::removeNeighbor(char name){
    nodeNeighbor.erase(name);
}

bool neighborCheck(char name){
    if(nodeNeighbor.count(name) > 0) return true;
    else return false;
}

Node *nodePtr(char node, map<char, Node*> nodeMap){
    map<char, Node*>::iterator find = nodemap.find(node);
    return (find->second);
}


void getReply(char src, char dst, string requestReply, int size, char replySource){
    if(size == 0){
        cout << "Node" << name << "recieved path to" << replySource "." << endl;
        cout << "Route taken: " << requestReply << replySource << endl;
    } else if(size == (requestReply.size()-1)){
        cout << "Node" << name << "recieved reply from" << replySource "." << endl;
        cout << "Route taken: " << requestReply << replySource << endl;
    } else if(size != requestReply.size()){
        cout << "Node" << name << "recieved reply from" << replySource "." << endl;
        cout << "Route taken: " << requestReply << replySource << endl;
    } else

    replyCheck = true;
    map<char, Node*>::iterator find_iterator;
    Node * postNode = NULL;
    
    if((size - 1) >= 0){
        if (size != 0){
            getIterator = nodeNeighbor.find(requestReply[size - 1]);
        }
        postNode = getIterator -> second;
    }

    if(postNode != NULL){
        postNode -> replyString = requestReply;
        postNode -> getReply(postNode -> name, dst, requestReply, size -1, replySource);
    }
}