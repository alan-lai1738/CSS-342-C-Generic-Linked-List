/*
 * List342.h
 *
 * List342.h Declaration and Definition
 *
 * CSS 342: Assignment 3
 *
 * Functions and definitions for the List342 object.
 * Everything is generic and templatized for any object.
 * 
 * List342 implements a default constructor, copy constructor, destructor
 * <<, +, +=, ==, !=, = overload operators
 * Private Templatized Node: Data and Next Pointer
 * Private Node Head
 * List342 Actions:
 * BuildList: Builds a list reading from a file
 * Insert: Inserts an item into a list, returns false if it doesn't happen
 * Remove: Removes an item and puts into result 
 * Peek: If item exists, returns the item.
 * DeleteList: Deletes a list from memory
 * Merge: Combines both lists and deletes the other
 * isEmpty: Returns a bool if a list is empty
 *
 * 11/6-15/2020
 * Alan Lai
 * alan.lai1738@gmail.com
 *
 */

#ifndef LIST342_H
#define LIST342_H
#include <iostream>
#include <string>
using namespace std;

template<class ItemType>
class List342
{	
	friend ostream& operator<<(ostream& out_stream, const List342<ItemType>& right_hand_side)
	{
		if (right_hand_side.head_ == nullptr)
		{
			cout << "List is empty" << endl;
			return out_stream;
		}
		Node* current = right_hand_side.head_;
		while (current != nullptr)
		{
			ItemType temp = *(current->data_);
			out_stream << temp;
			current = current->next;
		}
		return out_stream;
	}

public:
	// Constructors and Destructors
	List342();
	List342(const List342 &list);
	~List342();

	// Actions
	bool BuildList(string fileName);
	bool Insert(ItemType *obj);
	bool Remove(ItemType target, ItemType& result);
	bool Peek(ItemType target, ItemType& result) const;
	void DeleteList();
	bool Merge(List342& list1);
	bool isEmpty() const;

	// Operator Overloads
	List342<ItemType>& operator+=(const List342<ItemType> &right_hand_side);
	List342<ItemType>& operator+(const List342<ItemType> &right_hand_side) const;
	bool operator==(const List342& to_compare) const;
	bool operator!=(const List342& to_compare) const;
	List342<ItemType>& operator=(const List342<ItemType> &list);
	
	

private:
	// Private Data Variables
	struct Node
	{
		ItemType* data_ = nullptr;
		Node* next = nullptr;
	};
	Node *head_;
	
};
#endif

#include <iostream>
#include <string>
#include <fstream>

// ------------------------------------------------------- Definitions ------------------------------------------------------- 

//Constructors

template<class ItemType>
List342<ItemType>::List342()	// Default Constructor
{
	head_ = nullptr;
}

template<class ItemType>
List342<ItemType>::List342(const List342& list)	// Copy constructor
{
	*this = list;
}

template<class ItemType>
bool List342<ItemType>::Insert(ItemType* obj)
{
	Node* ins_node = new Node;	// Create node with new data
	ins_node->data_ = obj;
	if (obj == NULL)	// Bad object check
	{
		delete ins_node;
		return false;
	}
	if (isEmpty()) // If head is empty, this node is head.
	{
		head_ = new Node;
		head_->data_ = obj;
		head_->next = nullptr;
		return true;
	}
	if (*obj == *(head_->data_)) // Duplicate check
	{
		delete ins_node;
		return false;
	}
	if (*obj < *(head_->data_))	// If data is less than the head data, make it the new head
	{
		ins_node->next = head_;
		head_ = ins_node;
		return true;
	}
	if (head_->next == nullptr)	// If data is greater, and head's next is null, put the object there
	{
		if (*obj == *(head_->data_))	// Duplicate check
		{
			delete ins_node;
			return false;
		}
		head_->next = ins_node;
		return true;
	}
	Node* p_node = head_;	// Otherwise, it belongs somewhere after the head.
	while ((p_node->next != nullptr) && (*(p_node->next->data_) < *obj))	// If this obj>next object, keep moving our p_node until we find the right spot.
	{
		p_node = p_node->next;
	}
	if ((p_node->next) == nullptr)	// If the next spot is null
	{
		ins_node->next = p_node->next;
		p_node->next = ins_node;
		return true;
	}
	if ((p_node->next) != nullptr && *(p_node->next->data_) == *obj)
	{
		delete ins_node;
		return false;
	}
	ins_node->next = p_node->next;
	p_node->next = ins_node;
	return true;
}

template<class ItemType>
bool List342<ItemType>::Remove(ItemType target, ItemType& result) {
	Node* c_node;					// Current node, helper pointer
	if (isEmpty())
	{
		return false;
	}
	if (*head_->data_ == target)	// Target Found: Delete Node
	{
		c_node = head_;
		head_ = head_->next;
		result = *c_node->data_;
		delete c_node;
		c_node = nullptr;
		return true;
	}
	Node* p_node = head_;
	while ((p_node->next != nullptr) && *(p_node->next->data_) < target)
	{
		p_node = p_node->next;	// Iterate through the list.
	}
	if (p_node->next == nullptr)
	{
		return false;
	}
	if (*p_node->next->data_ == target)	// Target Found!
	{
		c_node = p_node->next;
		result = *c_node->data_;
		p_node->next = p_node->next->next;
		delete c_node;
		c_node = nullptr;
		return true;
	}
	return false;
}


template<class ItemType>
bool List342<ItemType>::Peek(ItemType target, ItemType& result) const
{
	Node* c_node;
	if (isEmpty())
	{
		return false;
	}
	if (*head_->data_ == target)
	{
		c_node = head_;
		result = *c_node->data_;
		return true;
	}
	Node* p_node = head_;
	while ((p_node->next != nullptr) && *(p_node->next->data_) < target)
	{
		p_node = p_node->next;
	}
	if (p_node->next == nullptr)
	{
		return false;
	}
	if (*p_node->next->data_ == target)
	{
		c_node = p_node->next;
		result = *c_node->data_;
		return true;
	}
	return false;
}

template<class ItemType>
void List342<ItemType>::DeleteList() {
	while (head_ != nullptr)
	{
		Node* temp = new Node;
		temp = head_;
		head_ = head_->next;
		delete temp;
	}
}

template<class ItemType>
bool List342<ItemType>::Merge(List342<ItemType>& list1)
{
	if (*this == list1)
	{
		return false;
	}
	Node* c_node = head_;								// This Current Node (c_node) will move through our main list, starting from head.
	while (list1.head_ != nullptr && c_node != nullptr)
	{
		if (c_node->next == nullptr)
		{
			c_node->next = list1.head_;
			list1.head_ = nullptr;
			return true;
		}
		else if (*head_->data_ == *list1.head_->data_)	// If heads are equal, delete the duplicate head
		{
			Node* toDelete = list1.head_;				// This List1 duplicate will be deleted.
			list1.head_ = list1.head_->next;			// Move to the next data of list1
			delete toDelete;							// Delete list1's head. 
		}
		else if (*head_->data_ > *list1.head_->data_)	// Head Check: If our head > their head
		{
			head_ = list1.head_;						// They are the new head
			list1.head_ = list1.head_->next;			// Go to next data
			head_->next = c_node;						// We are the next to the new head
			c_node = head_;								// Our current is to the new head
		}
		else if (*c_node->next->data_ == *list1.head_->data_)	// If our next data is a duplicate
		{
			Node* toDelete = c_node->next;				// Delete list1's version of it and move on
			toDelete = list1.head_;
			list1.head_ = list1.head_->next;
			delete toDelete;
		}
		else if (*c_node->next->data_ > *list1.head_->data_)// If our next data is greater than list1's data
		{
			
			Node* temp = c_node->next;						// We will swap them: Our temp holds ptr to high value
			c_node->next = list1.head_;						// Our current is now the lower value coming from list1's data
			list1.head_ = list1.head_->next;				// Move on to next list1 data
			c_node = c_node->next;							// List1.head, our smaller value, is now the new current Node
			c_node->next = temp;							// Finish the swap by moving our higher value to after our current
		}
		else
		{
			c_node = c_node->next;							// No moves/swaps need to be made, lets move onto our next node
		}
	}
	return true;
}



template<class ItemType>
bool List342<ItemType>::isEmpty() const
{
	if (head_ == nullptr)
	{
		return true;
	}
	return false;
}

template<class ItemType>
List342<ItemType>& List342<ItemType>::operator+=(const List342<ItemType>& right_hand_side)
{
	List342<ItemType> to_merge = right_hand_side;
	this->Merge(to_merge);
	return *this;

}

template<class ItemType>
List342<ItemType>& List342<ItemType>::operator+(const List342<ItemType> &right_hand_side) const
{
	List342<ItemType> result = *this;
	List342<ItemType> other_list = right_hand_side;
	result.Merge(other_list);
	return result;
}

template<class ItemType>
inline bool List342<ItemType>::operator==(const List342& to_compare) const
{
	Node* this_node, * that_node;
	this_node = head_;
	that_node = to_compare.head_;
	if (this->isEmpty() && to_compare.isEmpty())
	{
		return true;
	}
	while (this_node != nullptr && that_node != nullptr)
	{
		if (this_node->data_ != that_node->data_)
		{
			return false;
		}
		this_node = this_node->next;
		that_node = that_node->next;
	}
	return true;
}


template<class ItemType>
inline bool List342<ItemType>::operator!=(const List342& to_compare) const
{
	return!(*this == to_compare);
}

template <class ItemType>
List342<ItemType>& List342<ItemType>::operator=(const List342<ItemType>& right_hand_side)
{
	Node* s_node, *p_node, *ins_node;
	if (this == &right_hand_side)	// If they're the same list, return this list
	{
		return *this;
	}
	if (right_hand_side.head_ == nullptr)	// If the list is empty, return an empty list
	{
		return *this;
	}
	this->DeleteList();	// Delete the old list
	p_node = new Node;
	p_node->data_ = (right_hand_side.head_)->data_;
	this->head_ = p_node;
	s_node = (right_hand_side.head_)->next;
	while (s_node != nullptr)
	{
		ins_node = new Node;
		ins_node->data_ = s_node->data_;
		p_node->next = ins_node;
		p_node = p_node->next;
		s_node = s_node->next;
	}
	return *this;
}

template <class ItemType>
bool List342<ItemType>::BuildList(string file_name)
{
	ifstream in_file;
	in_file.open(file_name);
	if (in_file.is_open())
	{
		while (!in_file.eof()) // while were not end of file
		{
			ItemType *item = new ItemType;
			in_file >> *item;
			Insert(item);
		}
	}
	else
	{
		cout << "File: " << file_name << " not found." << endl;
		return false;
	}
}

template<class ItemType>
List342<ItemType>::~List342()
{
	this->DeleteList();
}