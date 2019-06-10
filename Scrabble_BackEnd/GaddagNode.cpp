#include"GaddagNode.h"

int GaddagNode::idCounter = 0;

GaddagNode::~GaddagNode() {
	for (int i = 0; i < 27; i++)
	{
		delete(children[i]);
	}
}


GaddagNode::GaddagNode(char x) {
	ID = idCounter;
	idCounter++;
}

GaddagNode* GaddagNode::putTransitionChar(char transitionChar, GaddagNode * son) {
	GaddagNode* child = this->getChildren(transitionChar);
	if (child == NULL) {
		transitions |= bitPosistion[transitionChar - 'A'];
		if (son == NULL) {
			GaddagNode * node = new GaddagNode(transitionChar);
			children[transitionChar - 'A'] = node;
		}
		else
			children[transitionChar - 'A'] = son;
		return children[transitionChar - 'A'];
	}
	else {
		return child;
	}
}



GaddagNode* GaddagNode::getChildren(char  transitionChar) {
	if ((bitPosistion[transitionChar - 'A'] & transitions) != 0) {
		return children[transitionChar - 'A'];
	}
	return NULL;
}

bool GaddagNode::contains(std::string query) {
	if (query.find('[') != std::string::npos) {
		return containsRecur(query);
	}
	else {
		return containsRecur(query.insert(1, "["));
	}
}
//
bool GaddagNode::containsRecur(std::string query) {
	if (query.length() == 0) {
		return false;
	}
	char c = query[0];
	if (query.length() == 1 && this->hasCharAsEnd(c)) {
		return true;
	}
	GaddagNode* child = this->getChildren(c);
	if (child != NULL) {
		return child->containsRecur(query.substr(1));
	}
	return false;
}

void GaddagNode::putEnd(char endChar) {
	end |= bitPosistion[endChar - 'A'];
}

bool GaddagNode::hasCharAsEnd(char endChar) {
	return contains(end, endChar);
}

bool GaddagNode::contains(unsigned int x, char y) {
	if ((bitPosistion[y - 'A'] & x) != 0)
		return true;
	return false;
}

GaddagNode** GaddagNode::getChildren() {
	return children;
}

int GaddagNode::getTransitions() {
	return transitions;
}

int GaddagNode::getEnd() {
	return this->end;
}

unsigned int GaddagNode::calculateChildrenIndex(char transachionChar)
{
	unsigned x = (comulativeBitPosistion[transachionChar - 'A']) & (transitions);
	return (__popcnt(x));
}


void GaddagNode::getOnesPositions(unsigned int  transitions, std::vector<unsigned int>&res)
{
	res.reserve(27);
	for (; transitions != 0; transitions &= (transitions - 1))
	{
		res.push_back((unsigned int)log2(transitions & ~(transitions - 1)));
	}
}

