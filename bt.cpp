#include "bt.h"
using namespace std;

// Sets the only child node for the root node of the bt
void BehaviourTree::RootNode::setChild(btNode* newChild) {
	child = newChild;
}

// Tick() returns the previous nodes tick() which can be either false or true
// which shows if it was traversed succesfully or not
bool BehaviourTree::RootNode::tick() {
	return child->tick();
}

bool BehaviourTree::tick() {
	return root->tick();
}

// Function that sets the only child node of the root node
void BehaviourTree::setRootChild(btNode* rootChild) {
	root->setChild(rootChild);
}

// Adds a new child node in the children vector - that represents the tree
void BehaviourTree::ControlNode::addChild(btNode* child) {
	children.push_back(child);
}

// Adds multiple child nodes to the children vector
void BehaviourTree::ControlNode::addChildren(vector<btNode*>& newChildren) {
	for (btNode* child : newChildren) {
		addChild(child);
	}
}

// Basic implementation of a Fallback node
bool BehaviourTree::Fallback::tick() {
	// traverses the child nodes of the current fallback node, and if one of them
	// succeeds the node will succeed and return true, otherwise it returns false
	for (btNode* child : getChildren()) {  
		if (child->tick() == true)  
			return true;
	}
	return false;  
}

// Basic implementation of a Sequence node
bool BehaviourTree::Sequence::tick() {
	// traverses the child nodes of the current sequence node, and if one of them
	// fails the node will fail and return false, otherwise it returns true
	for (btNode* child : getChildren()) {  
		if (child->tick() == false)  
			return false;
	}
	return true;  
}

// Constructor for an Execution node, that takes the task name and whether its successful or not
// Initially success will be set as false, and this will change if the task is completed
Execution::Execution(string newTask, bool success) {
	task = newTask;
	isSuccessful = success = false;
}

// Based on whether the task is completed successfully, the node will return true or false
// and print the task name and if it succeeded or failed
bool Execution::tick() {
	if (isSuccessful == true) {
		cout << task << " succeeded." << endl;
		return true;
	}
	cout << task << " failed." << endl;
	return false;
}




