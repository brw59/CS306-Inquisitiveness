/***********************************************************************
 * Module:
 *    Lesson 10, Sort Binary
 *    Brother Helfrich, CS 235
 * Author:
 *    Justin Stucki 1Hr
 * Summary:
 *    This program will implement the Binary Tree Sort
 ************************************************************************/

#ifndef SORT_BINARY_H
#define SORT_BINARY_H

#include "bst.h"
#include <cassert>

/*****************************************************
 * SORT BINARY
 * Perform the binary tree sort
 ****************************************************/
template <class T>
void sortBinary(T array[], int num)
{
   BST<T> tree;                         //Create a tree to sort with
   for (int i = 0; i < num; i++)
      tree.insert(array[i]);            //Build the tree

   int i = 0;                           //Index through array
   BSTIterator<T> it = tree.begin();    //Iterate through tree
   for (it; it != NULL; ++it)
   {
      array[i] = *it;                   //Replace array with sorted items
      i++;
   }
}

#endif // SORT_BINARY_H
