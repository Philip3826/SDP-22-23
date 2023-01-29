#include "catch2/catch_all.hpp"
#include "solution.h"

TEST_CASE("removeConsecutiveDuplicates(nullptr) does not throw")
{
	REQUIRE_NOTHROW(removeConsecutiveDuplicates(nullptr));
}

TEST_CASE("removeConsecutiveDuplicates() correctly removes duplicate values")
{
	// Arrange
	// Create the list 1 -> 1 -> 1 -> 2 -> 2 -> 3 -> 1 -> 2 -> 2

	Node *head = nullptr;
	head = new Node(2);
	head = new Node(2, head);
	head = new Node(1, head);
	head = new Node(3, head);
	head = new Node(2, head);
	head = new Node(2, head);
	head = new Node(1, head);
	head = new Node(1, head);
	head = new Node(1, head);

	int expected[] = {1, 2, 3, 1, 2};

	// Act
	REQUIRE_NOTHROW(removeConsecutiveDuplicates(head));

	// Assert
	SECTION("Duplicate elements are correctly removed and the list has the proper structure")
	{
		Node* p = head;
		for(int i = 0; i < 5; ++i) {
			REQUIRE(p != nullptr);
			REQUIRE(p->value == expected[i]);
			p = p->next;
		}
		REQUIRE(p == nullptr);
	}
}

TEST_CASE("cloneReversed(nullptr) returns nullptr")
{
	REQUIRE(cloneReversed(nullptr) == nullptr);
}

TEST_CASE("cloneReversed() creates a reversed copy")
{
	// Arrange
	// Create the list 1 -> 2 -> 3 -> 4 -> 5
	Node e(4);
	Node d(3, &e);
	Node c(2, &d);
	Node b(1, &c);
	Node a(0, &b);

	// Store the addresses of the original boxes
	Node* originalBoxes[] = {&a, &b, &c, &d, &e};

	// Act
	Node* result = cloneReversed(&a);

	// Assert
	SECTION("The list contains the necessary number of elements and the proper values ")
	{
		Node* p = result;
		for(int i = 4; i >= 0; --i) {
			REQUIRE(p != nullptr);  // Make sure the element exists
			REQUIRE(p->value == i); // Make sure the value is correct
			p = p->next;
		}
		REQUIRE(p == nullptr); // Make sure there are no more elements in the list
	}
	SECTION("The addresses of the boxes in the new list differ from those of the original list")
	{
		Node* p = result;
		for(int i = 4; i >= 0; --i) {
			REQUIRE(p != originalBoxes[i]); // Make sure the element exists
		}

		// Note: If a box is "reused" in another place, there will either
		// be a value mismatch, or the original list will be modified,
		// which is caught by the other two tests. Hence here we only
		// need to check the corresponding boxes.
	}
	SECTION("The original list is NOT modified")
	{
		Node* p = &a;
		for(int i = 0; i <= 4; ++i) {
			REQUIRE(p == originalBoxes[i]); // The address of the i-th box is unchanged
			REQUIRE(p->value == i);         // The value in the i-th box is unchanged
			p = p->next;
		}
		REQUIRE(p == nullptr);
	}
}