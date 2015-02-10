/***********************************************************************
* Program:
*    Assignment 17, Heap Sort
*    Brother Ercanbrack, CS235
* Author:
*    Benjamin Ray Walker
* Summary:
*    Read in a file and use a Heap Sort to sort it
************************************************************************/

#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;

#define MAX 120

/***********************************************************************
 * Btree traverses the tree inserting and deleting parts of it
 ***********************************************************************/
class BTree
{
private:
   int data;          // --- data stored in node of tree
   BTree* left;       // --- pointer to left subtree
   BTree* right;      // --- pointer to right subtree
   BTree* parent;     // --- pointer to the parent node;

public:
   BTree(int item = 0);
   ~BTree(void);
   void insertLeft(int item);     // creates a new node and inserts node to left
   void insertRight(int item);    // creates a new node and inserts node to right
   BTree* getLeftChild(void);     // return the ptr to the left child
   BTree* getRightChild(void);    // return the ptr to the right child
   BTree* getParent(void);        // return parent
   int getData(void);
   void setData(int item);
   void setLeft(BTree* tree);
   void setRight(BTree* tree);
   void infix(void);              // do infix traversal
   void prefix(void);             // do prefix traversal
   void postfix(void);            // do postfix traversal
   void level(void);              // do level order traversal
   void heapify(int heapIndex, int treeSize); // set it up properly for heaping
   void swapHeapTree(int wall); // swap data for the tree
   void heapSort(int treeSize);               // sort the "hopefully" heaped tree
};

/***********************************************************************
 * traverses the tree inserting and removing items
 ***********************************************************************/
class BST
{
private:
   BTree* root;

public:
   BST();
   int empty(void);
   BTree* search(int item);
   void insert(int item);
   void remove(int item);
   void BSTInfix(void);
};

/***********************************************************************
 * set the root node to the correct place
 ***********************************************************************/
BST::BST()
{
   root = NULL;
}

/***********************************************************************
 * check to see if there is even a tree
 ***********************************************************************/
int BST::empty()
{
   if (root == NULL)
      return 1;
   return false;
}

/***********************************************************************
 * search the tree to find a position where an item is located
 ***********************************************************************/
BTree* BST::search(int item)
{
   if (root == NULL)
   {
      cout << "You cannot search through a tree that doesn't exist\n";
      return NULL;
   }

   BTree * temp;
   temp = root;
   
   while (temp->getData() != item)
   {
      if (temp->getData() < item)
         if (temp->getRightChild())
              temp = temp->getRightChild();
         else
         {
            cout << "Item " << item << " is not found, cannot delete it!\n";
            return NULL;
         }
      else
      {
         if (temp->getLeftChild())
            temp = temp->getLeftChild();
         else
         {
            cout << "Item " << item << " is not found, cannot delete it!\n";
            return NULL;
         }
      }
   }

   return temp;
}

/***********************************************************************
 * find the position a new number should go and insert
 ***********************************************************************/
void BST::insert(int item)
{
   if (root == NULL)
   {
      root = new BTree(item);   
      return;
   }
   
   BTree * temp;
   temp = root;

   for (;;)
   {
      if (temp->getData() < item)
      {
         if (temp->getRightChild())
         {
            temp = temp->getRightChild();
         }
         else
         {
            temp->insertRight(item);
            break;
         }
      }
      else
      {     
         if (temp->getLeftChild())
            temp = temp->getLeftChild();
         else
         {
            temp->insertLeft(item);
            break;
         }
      }
   }
}

/***********************************************************************
 * find a particular node and remove it using methods of having
 * two, one or two children
 ***********************************************************************/
void BST::remove(int item)
{
   BTree * temp = search(item);

   if (temp)
   {
      int data = temp->getData();
      BTree * right = temp->getRightChild();
      BTree * left = temp->getLeftChild();
      BTree * parent = temp->getParent();
      if (!right && !left) // no kids
      {
         if (data <= parent->getData())
            parent->setLeft(NULL);
         else
            parent->setRight(NULL);
         delete temp;
         temp = NULL;
      }
      else if (!right && left) // one left kid
      {
         if (data <= parent->getData())
            parent->setLeft(left);
         else
            parent->setRight(left);
         delete temp;
         temp = NULL;
      }
      else if (right && !left) // one right kid
      {
         if (data <= parent->getData())
            parent->setLeft(right);
         else
            parent->setRight(right);
         delete temp;
         temp = NULL;
      }
      else // both kids
      {
         BTree * succession = temp;
         // find next in succession

         succession = right;

         while (succession->getLeftChild())
            succession = succession->getLeftChild();

         temp->setData(succession->getData());

         // delete succession node
         data = succession->getData();
         right = succession->getRightChild();
         left = succession->getLeftChild();
         parent = succession->getParent();

         if (right) // one right kid
         {
            parent->setRight(right);
            delete succession;
            succession = NULL;
         }
         else // no kids
         {
            parent->setRight(NULL);
            delete succession;
            succession = NULL;
         }
      }
   }
}

/***********************************************************************
 * just do an infix print
 ***********************************************************************/
void BST::BSTInfix(void)
{
   root->infix();
}

/***********************************************************************
 * display data
 * check left node
 * check right node
 ***********************************************************************/
void BTree::prefix()
{
   cout << data << " ";
   if (left != NULL) left->prefix();
   if (right != NULL) right->prefix();
}

/***********************************************************************
 * check left node
 * check right node
 * display data
 ***********************************************************************/
void BTree::postfix()
{
   if (left != NULL) left->postfix();
   if (right != NULL) right->postfix();
   cout << data << " ";
}

/***********************************************************************
 * point current right pointer to child and visa versa
 ***********************************************************************/
void BTree::setRight(BTree* tree)
{
//   BTree * right = new BTree(num);
   
   right = tree;
   if (tree != NULL)
      tree->parent = this;
}

/***********************************************************************
 * point current left pointer to child and visa versa
 ***********************************************************************/
void BTree::setLeft(BTree* tree)
{
//   BTree * left = new BTree(num);
      
   left = tree;
   if (tree != NULL)
      tree->parent = this;
}

/***********************************************************************
 * set node data
 ***********************************************************************/
void BTree::setData(int item)
{
   data = item;
}

/***********************************************************************
 * return node data
 ***********************************************************************/
int BTree::getData()
{
   return data;
}

/***********************************************************************
 * return parent pointer
 ***********************************************************************/
BTree * BTree::getParent()
{
   return parent;
}

/***********************************************************************
 * return right pointer
 ***********************************************************************/
BTree * BTree::getRightChild()
{
   return right;
}

/***********************************************************************
 * return left pointer
 ***********************************************************************/
BTree * BTree::getLeftChild()
{
   return left;
}

/***********************************************************************
 * create new node and set right pointer to child and child to current
 * with parameter data
 ***********************************************************************/
void BTree::insertRight(int item)
{
   right = new BTree;
   right->data = item;
   right->parent = this;
}

/***********************************************************************
 * set new node to left pointer and insert data
 ***********************************************************************/
void BTree::insertLeft(int item)
{
   left = new BTree;
   left->data = item;
   left->parent = this;
}

/***********************************************************************
 * create new node and put in item
 ***********************************************************************/
BTree::BTree(int item)
{
   data = item;
   parent = NULL;
   left = NULL;
   right = NULL;
}

/***********************************************************************
 * delete node, and only this node
 ***********************************************************************/
BTree::~BTree()
{
}

/***********************************************************************
 * check left child, display current data, check right child
 ***********************************************************************/
void BTree::infix()
{
   if (left != NULL) left->infix();
   cout << data << " ";
   if (right != NULL) right->infix();
}

/***********************************************************************
 * display level by level data
 ***********************************************************************/
void BTree::level()
{
   BTree *queue[MAX];
   BTree *temp;
   int front = 0;
   int back = 0;

   queue[back++] = this;

   while (front != back)
   {
      temp = queue[front];
      front = (front + 1) % MAX;
      if (temp != NULL)
      {
         cout << temp->data << " ";

         queue[back] = temp->left;
         back = (back + 1) % MAX;
         queue[back] = temp->right;
         back = (back + 1) % MAX;

      }
   }
}

/***********************************************************************
 * Get the whole tree ready to be heaped, then call the sorting function
 ***********************************************************************/
void BTree::heapSort(int treeSize)
{

   int wall;
   int index = 0;
   const int boolSize = log(MAX) / log(2.0) + 2;
   bool position[boolSize]; // must be one more than x big for 2^x = MAX
   
   while (treeSize > 1)
   {
      // last leaf swap with root, then call sortHeapTree(wall)
      int tempHeapIndex = treeSize;
      
      while (tempHeapIndex > 1)
      {
         if (tempHeapIndex % 2 == 1)
            position[index++] = true; // go right
         else
            position[index++] = false; // go left
         tempHeapIndex /= 2;
      }

      index -= 1; // it's current index is NULL
      BTree * temp = this;

      while (true)
      {
         if (index == -1)
         {
            // because they're being sorted, the root is the
            // next biggest number
            wall = getData();
            // swap data
            int t = getData();
            setData(temp->getData());
            temp->setData(t); 
            index = 0;
            break;
         }

         // traverse "position" backwards
         if (position[index])
            temp = temp->getRightChild(); // go right
         else
            temp = temp->getLeftChild(); // go left
         index--;
      }

      swapHeapTree(wall);      
      treeSize--;
   }

}

/***********************************************************************
 * Get the whole tree ready to be heaped, then call the sorting function
 ***********************************************************************/
void BTree::heapify(int heapIndex, int treeSize)
{
   if (heapIndex == 0)
   {
      heapSort(treeSize);
      return;
   }
   
   int tempHeapIndex = heapIndex;
   const int boolSize = log(MAX) / log(2.0) + 2;
   
   bool position[boolSize]; // must be one more than x big for 2^x = MAX
   int index = 0;
   while (tempHeapIndex > 1)
   {
      if (tempHeapIndex % 2 == 1)
         position[index++] = true; // go right
      else
         position[index++] = false; // go left
      tempHeapIndex /= 2;
   }
   
   index -= 1; // it's current index is NULL
   
   BTree * temp = this;
   
   while (true)
   {
      if (index == -1)
      {
         temp->swapHeapTree(100);
         break;
      }
      // traverse "position" backwards
      if (position[index])
         temp = temp->getRightChild(); // go right
      else
         temp = temp->getLeftChild(); // go left
      index--;
   }

   heapify(--heapIndex, treeSize);   

}

/***********************************************************************
 * swap elements in the tree and traverse downward
 ***********************************************************************/
void BTree::swapHeapTree(int wall)
{
   if (getRightChild() == NULL ||
       getLeftChild() == NULL)
      return;

   if (getLeftChild()->getData() <= wall)
      if (getLeftChild()->getData() > getData() &&
          getLeftChild()->getData() >= getRightChild()->getData())
      {
         int t = getData();
         setData(getLeftChild()->getData());
         getLeftChild()->setData(t);
         // recursively traverse tree
         getLeftChild()->swapHeapTree(wall);
      }
   if (getRightChild()->getData() <= wall)
      if (getRightChild()->getData() > getData() &&
          getLeftChild()->getData() < getRightChild()->getData())
      {
         int t = getData();
         setData(getRightChild()->getData());
         getRightChild()->setData(t);
         // recursively traverse tree
         getRightChild()->swapHeapTree(wall);
      }
}

/***********************************************************************
 * read through a file and organize it using a Heap Sort
 ***********************************************************************/
int main(int argc, char * argv[])
{
   char * fileName;
   if (argc > 1)
   {
      fileName = argv[1];
   }
   else
   {
      cout << "Enter input filename: ";
      fileName = new char[80];
      cin >> fileName;
   }

   ifstream input;
   input.open(fileName);
   if (input.fail())
   {
      cout << "ERROR: Filename Invalid" << endl;
      return 0;
   }

      
   int num;

   input >> num;
   BTree * heapTree = new BTree(num);
   BTree * temp = heapTree;

   // plus 1 because "int"s are floored, plus 2 because
   // of last NULL in an array
   const int boolSize = log(MAX) / log(2.0) + 2; 

   int i = 2; // start at position 2 because root was already set
   while (input >> num)
   {
      int j = i;
      bool position[boolSize]; // must be one more than x big for 2^x = MAX
      int index = 0;
      while (j > 1)
      {
         if (j % 2 == 1)
            position[index++] = true; // go right
         else
            position[index++] = false; // go left
         j /= 2;
      }

      index -= 1; // it's current index is NULL
      temp = heapTree;
      while (true)
      {
         if (index == 0) 
         {
            BTree * newTree = new BTree(num);
            if (i % 2 == 0)
            {
               temp->setLeft(newTree);
            }
            else if (i % 2 == 1)
            {
               temp->setRight(newTree);
            }
            break;
         }
         // traverse "position" backwards
         if (position[index])
            temp = temp->getRightChild(); //go right
         else
            temp = temp->getLeftChild(); // go left
         index--;
      }
      i++;
   }

   heapTree->heapify((i - 1) / 2, i - 1);
   heapTree->level();
   cout << endl;
   return 0;
}
