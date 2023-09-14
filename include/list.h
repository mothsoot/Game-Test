#pragma once

#include "math.h"
#include "object.h"
#include "items.h"

template <typename t>
class List {
    public:
        t* item;
        t* next;

        loadPosMap();
        loadIDMap();
        loadColMap();
};

/*
class List {
    private:
        struct Node {
            //Item item;
            Node* prev;
            Node* next;
        };

        Node* front;
        Node* back;
    
    public:
        List();
        ~List();

        bool insertBack();
        bool removeFront(Node* ring);
        Ring search(int type, Position pos);


};

// FOR IN .CPP
bool List::insertBack()
{
    // ringList
    Node* cur;

		if(cur == nullptr) {
			return false; // no item to insert
		} else if(front == nullptr) {
			// new item is only item in list, both front and back
			front = cur;
			back = cur;
		} else {
			// putting i behind an existing item
			cur->prev = back; // old back item is in front
			back->next = cur; // i is behind old back
			back = cur; // i is new back of list
		}
		return true;
}

bool List::removeFront(Node* ring)
{
	// i is item we want to remove
	if(ring == nullptr) {
		return false; // nothing to remove
	} 
	// special case 1: i is only item in list (remove front accounts for this)
    // special case 2: i is front of list but not only
    else if(ring == front) {
        Node* temp = removeFront(front, back);
        return true;
    }
    // special case 3: i is back of list but not only
    else if(ring == back) {
        back = back->prev;
        back->next = nullptr;
        ring->prev = nullptr;
        return true;
    }
    // general case: i is somewhere in the middle
    else {
        Node* afterRing = ring->next;
        Node* beforeRing = ring->prev;
        // bypassing i
        afterRing->prev = beforeRing;
        beforeRing->next = afterRing;

        ring->next = nullptr;
        ring->prev = nullptr;

        return true;
    }

}

Ring List::search(int type, Position pos)
{
	Node* cur = front;
	while (cur != nullptr) {
		if(cur->ring.getPos() == pos) {
            if(cur->ring.type == type) {
                return cur->ring;
            }
		}
		
        cur = cur->next;
		}
}
*/