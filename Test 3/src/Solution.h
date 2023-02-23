#pragma once

#include "Allocator.h"
#include "Node.h"

#include <stdexcept>
#include <algorithm>
// this test was taken at room 120

int getTreeHeight(Node<int>* rootptr) // helper function 
{
    if (!rootptr) return 0;

    return std::max(1 + getTreeHeight(rootptr->left), 1 + getTreeHeight(rootptr->right));
}

bool isHeightBalanced(Node<int>* rootptr)
{
    if (!rootptr) return true;
    
    int leftHeight = getTreeHeight(rootptr->left);
    int rightHeight = getTreeHeight(rootptr->right);
    if (leftHeight - rightHeight > 1 || rightHeight - leftHeight > 1)
        return false;

    return isHeightBalanced(rootptr->left) && isHeightBalanced(rootptr->right);
}

template <typename AllocatorType>
void free(Node<int>* rootptr, AllocatorType& allocator)
{
    if (!rootptr) return;

    Node<int>* toDelete = rootptr;
    Node<int>* left = rootptr->left;
    Node<int>* right = rootptr->right;
    
    allocator.release(toDelete);

    free(left, allocator);
    free(right, allocator);
}

template <typename AllocatorType>
Node<int>* cloneMirror(Node<int>* rootptr, AllocatorType& allocator)
{
    if (!rootptr) return nullptr;


    Node<int>* clonedNode = allocator.buy();
    clonedNode->data = rootptr->data;

    if (!clonedNode) throw std::bad_alloc();
    
    if (!rootptr->hasLeftSuccessor() && !rootptr->hasRightSuccessor())
        return clonedNode;
    try
    {
    clonedNode->left = cloneMirror(rootptr->right, allocator);
    clonedNode->right = cloneMirror(rootptr->left, allocator);

    }
    catch (std::bad_alloc & b)
    {
        free(clonedNode, allocator);
        throw& b;
    }
    

    return clonedNode;
}
