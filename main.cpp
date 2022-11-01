// Driver code for the hide and seek simulation using behaviour tree

#include "bt.h"
#include <iostream>

using namespace std;

int main() {
	/* 
	The behaviour tree model constructed here is the same as the behaviour tree model diagram.
	The behaviour tree model for the hide and seek simulation has 4 fallback nodes, 8 sequence nodes, and 10 unique execution nodes 
	some of these are repeated in the behaviour tree model, giving 16 execution nodes in total.
	*/
	BehaviourTree behaviourTree;
	BehaviourTree::Fallback fallback[4];
	BehaviourTree::Sequence sequence[8];
	Execution 	walkToDoor ("Walk to door", false), openDoor ("Open door", false), unlockDoor ("Unlock door", false), breakDoor ("Break door", false), 
			walkToTree ("Walk to Tree", false), crouchDown ("Crouch Down", false), climbTree ("Climb Tree", false),
			walkToBed ("Walk to Bed", false), RemoveBlanket ("Climb Tree", false), lookForPerson("Look for person", false);	
	
	// Setting a fallback node as the root node of the behaviour tree
	behaviourTree.setRootChild (&fallback[0]); 
	// The rootnode will have three subtrees that are all sequence nodes
	fallback[0].addChild(&sequence[0]);
	fallback[0].addChild(&sequence[1]);
	fallback[0].addChild(&sequence[2]);

	// First subtree - the person searches behind the door
	sequence[0].addChild(&walkToDoor);
	sequence[0].addChild(&fallback[1]);
	sequence[0].addChild(&lookForPerson);

	fallback[1].addChild(&openDoor);
	fallback[1].addChild(&sequence[3]);
	fallback[1].addChild(&breakDoor);

	sequence[3].addChild(&unlockDoor);
	sequence[3].addChild(&openDoor);

	// Second subtree - the person searches under the tree
	sequence[1].addChild(&walkToTree);
	sequence[1].addChild(&fallback[2]);

	fallback[2].addChild(&sequence[4]);
	fallback[2].addChild(&sequence[5]);

	sequence[4].addChild(&crouchDown);
	sequence[4].addChild(&lookForPerson);

	sequence[5].addChild(&climbTree);
	sequence[5].addChild(&lookForPerson);

	// Third subtree - the person searches under the blanket
	sequence[2].addChild(&walkToBed);
	sequence[2].addChild(&fallback[3]);

	fallback[3].addChild(&sequence[6]);
	fallback[3].addChild(&sequence[7]);

	sequence[6].addChild(&crouchDown);
	sequence[6].addChild(&lookForPerson);

	sequence[7].addChild(&RemoveBlanket);
	sequence[7].addChild(&lookForPerson);

	// If the final tick is true, it shows the execution tasks were completed successfully 
	if (behaviourTree.tick() == true) cout << "You have found the hiding robot :)" << endl;
	else cout << "You were unable to find the hiding robot :(" << endl;

	cout<<"End of hide and seek simulation."<<endl;

	return 0;
}


