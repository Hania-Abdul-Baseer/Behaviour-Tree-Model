#ifndef BT_H
#define BT_H

#include <vector>
#include <iostream>

class BehaviourTree {
		public:
			// Class for each node of the behaviour tree
			class btNode {  
				public:
					// Tick() is a pure virtual function and is only defined by subclasses of btNode.
					// As tick() behaves differently depending on the type of behaviour tree node
					virtual bool tick() = 0;
			};

			// The root node can have only one child node
			class RootNode : public btNode {
				public:
					btNode* child;
					void setChild (btNode* newChild);
					virtual bool tick();
			};

			RootNode* root;
			// BehaviourTree constructor that uses root as the RootNode
			BehaviourTree() : root(new RootNode) {};
			virtual bool tick();
			// The root node can only have one child node and this function sets that child node
			void setRootChild (btNode* rootChild);

			// Control Node are the non-leaf nodes of the behaviour tree 
			// and there are two types of them used in this model: Fallback and Sequence
			class ControlNode : public btNode {  
				public:
					std::vector<btNode*> children;

					const std::vector<btNode*>& getChildren() { 
						return children;
					};
					void addChild (btNode* child);
					void addChildren (std::vector<btNode*>& newChildren);
			};

			/* 
			Class for Fallback Nodes: The node spreads its ticks to its child
			nodes from left to right, and returns “failure” only when
			all of its child nodes return “failure”.
			*/
			class Fallback : public ControlNode {
				public:
					virtual bool tick();
			};

			/* 
			Class for Sequence Nodes: The node spreads its ticks to its child
			nodes from left to right, and returns “success" only when all the 
			child nodes return success.
			*/
			class Sequence : public ControlNode {
				public:
					virtual bool tick();
			};
};

/* 
Class for Execution Nodes: These nodes define the behaviour and actions.
And can only return success or failure based on whether the given task is 
completed successfully. The nodes are leaf-nodes and once they are constructed using
a custom task, they can be added to the behaviour tree using addChild() method
of control nodes.
*/
class Execution : public BehaviourTree::btNode {
	private:
		std::string task;
		bool isSuccessful;
        virtual bool tick();

	public:
		// Constructor that takes newTask: a task name, and success: whether its successful or not
		Execution (std::string newTask, bool success);	
};

#endif 