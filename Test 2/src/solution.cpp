#include "solution.h"

#include <stdexcept>

void removeConsecutiveDuplicates(Node* first)
{
	if (!first || !first->next) return; // if the list has zero or one element

	Node* current = first->next;
	Node* previous = first;
	while (current)
	{
		if (current->value == previous->value)
		{
			Node* temp = current;
			previous->next = current->next;
			current = current->next;
			delete temp;
		}
		else
		{
			previous = current;
			current = current->next;
		}
	}
}
void clean(Node* first)
{
	while (first)
	{
		Node* tmp = first;
		first = first->next;
		delete tmp;
	}
}
Node* cloneReversed(Node* first)
{
	if (!first) return nullptr; // if list is empty

	Node* current = first;
	Node* reversed = nullptr;
	while (current)
	{
		Node* newNode = new Node(current->value, reversed);
		if (!newNode)
		{
			clean(reversed);
			throw std::bad_alloc();
		}
		reversed = newNode;
		current = current->next;
	}

	return reversed;
}