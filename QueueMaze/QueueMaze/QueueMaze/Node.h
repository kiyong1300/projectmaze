#pragma once
#include "Location.h"

class Node : public Location {
	Location* location;
	Node* link;
public:
	Node(int row, int col) : location(new Location(row, col)), link(NULL) {}
	~Node() { if (location != NULL) delete location; }
	Node* getLink() { return link; }
	void setLink(Node* p) { link = p; }
	Location* getLocation() { return location; }
};