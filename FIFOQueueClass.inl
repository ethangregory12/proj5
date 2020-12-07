#include "FIFOQueueClass.h"
#include <iostream>
using namespace std;

//Ethan Gregory
//November 24 2020
//This class allows the user to utilize the LinkedNodeClass< T > to
//generate a queue of values. This stack follows the FIFO format
//when being referenced, and allows the user to "enqueue" and
//"dequeue" data points in the queue, as well as utilizing
//a series of other functionalities.

template <class T>
FIFOQueueClass< T >::FIFOQueueClass(
)
{
   T listContains;
   head = new LinkedNodeClass< T >(NULL, listContains, NULL);
   tail = new LinkedNodeClass< T >(NULL, listContains, NULL);
};

template <class T>
FIFOQueueClass< T >::~FIFOQueueClass(
)
{
   clear();
   delete head;
   delete tail;
};

template <class T>
void FIFOQueueClass< T >::enqueue(
const T &newItem
)
{
//Verifying if the queue has any items in it:
   if (head->getNext() == NULL && tail->getPrev() == NULL)
   {
      LinkedNodeClass< T > *newNode;
      newNode = new LinkedNodeClass< T >(head, newItem, tail);
      newNode->setBeforeAndAfterPointers();
      newNode->setNextPointerToNull();
      newNode->setPreviousPointerToNull();
   }
//If there are nodes in queue, place the new node in at the head of the queue:
   else
   {
      LinkedNodeClass< T > *newNode;
      newNode = new LinkedNodeClass< T >(head,newItem, head->getNext());
      newNode->setBeforeAndAfterPointers();
      newNode->setPreviousPointerToNull();
   }
};

template <class T>
bool FIFOQueueClass< T >::dequeue(
T &outItem
)
{
//If the queue is empty:
   if (tail->getPrev() == NULL)
   {
      return false;
   }
   else
   {
      outItem = tail->getPrev()->getValue();
      LinkedNodeClass< T > *newFirstObject;

//If the queue only contains one value:
      if (tail->getPrev()->getPrev() == NULL
         && head->getNext()->getNext() == NULL)
      {
         outItem = tail->getPrev()->getValue();
         clear();
      }

//If the queue contains two values (The new first value will also be the last):
      else if (tail->getPrev()->getPrev()->getPrev() == NULL)
      {

         newFirstObject = new LinkedNodeClass< T >(head,
            tail->getPrev()->getPrev()->getValue(),
            tail);
//Resetting the list with the now single value:
         delete tail->getPrev();
         newFirstObject->setBeforeAndAfterPointers();
         newFirstObject->setNextPointerToNull();
         newFirstObject->setPreviousPointerToNull();
      }

//If the queue contains more than two values:
      else
      {
         newFirstObject = new LinkedNodeClass< T >(
            tail->getPrev()->getPrev()->getPrev(),
            tail->getPrev()->getPrev()->getValue(),
            tail);
         delete tail->getPrev();
         newFirstObject->setBeforeAndAfterPointers();
         newFirstObject->setNextPointerToNull();
      }
      return true;
   }
};

template <class T>
void FIFOQueueClass< T >::print(
) const
{
   bool printFinished = false;
   LinkedNodeClass< T > *printPointer = head;
   if (printPointer->getNext() != NULL) //If queue contains values, print queue:
   {
      printPointer = printPointer->getNext();
      while (printFinished == false)
      {
         cout << printPointer->getValue() << " ";
         if (printPointer->getNext() == NULL)
         {
            printFinished = true;
         }
         else
         {
            printPointer = printPointer->getNext();
         }
      }
   }
   cout << "\n";
};

template <class T>
int FIFOQueueClass< T >::getNumElems(
 ) const
{
   int listLength = 0;
   bool endOfList = false;
   LinkedNodeClass< T > *tempCountingPtr = head;

   while (endOfList == false)
   {
      if (tempCountingPtr->getNext() == NULL)
      {
         endOfList = true;
      }
      else
      {
      tempCountingPtr = tempCountingPtr->getNext();
      listLength++;
      }
   }
   return listLength;
};

template <class T>
void FIFOQueueClass< T >::clear(
)
{
   T tempNullVal;
   int numElems = getNumElems();
//Detecting if there is one node or multiple (Zero element arrays are caught by
//the else statement, which doesn't do anything since the for loop won't
//iterate over anything:
   if (numElems == 1)
   {
      delete head->getNext();
      head->setNextPointerToNull();
      tail->setPreviousPointerToNull();
   }
   else if (numElems > 1)
   {
      LinkedNodeClass< T > *tempCountingPtr;
      tempCountingPtr = head->getNext()->getNext();
//Iterates the tempCountingPtr to delete all but the last node:
      for (int n = 1; n <= (numElems-2); n++)
      {
         delete tempCountingPtr->getPrev();
         tempCountingPtr = tempCountingPtr->getNext();
         
      }
//Deletes the second to last node in the linked queue:
      delete tempCountingPtr->getPrev();
//Deletes the final node in the linked queue (Prev of tail):
      delete tail->getPrev();
//      delete tempCountingPtr;
      head->setNextPointerToNull();
      tail->setPreviousPointerToNull();
   }

};
