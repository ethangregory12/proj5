#include "SortedListClass.h"
#include <iostream>
using namespace::std;

//Ethan Gregory
//November 24 2020
//This class allows the automated generation of an automatically
//sorted list by a user. It utilizes the LinkedNodeClass< T > objects to
//generate the list using a series of linked nodes.
template <class T>
SortedListClass<T>::SortedListClass(
)
{
//Assigning a blank set of head and tails:
   T listContains;
   head = new LinkedNodeClass< T >(NULL, listContains, NULL);
   tail = new LinkedNodeClass< T >(NULL, listContains, NULL);
};

template <class T>
SortedListClass< T >::SortedListClass(
const SortedListClass &rhs
)
{
//Generating new head and tail:
   T listContains;
   head = new LinkedNodeClass< T >(NULL, listContains, NULL);
   tail = new LinkedNodeClass< T >(NULL, listContains, NULL);

//Preparing to copy the contents of the rhs:
   int numElems = rhs.getNumElems();
   LinkedNodeClass< T > *tempCopyPtr = rhs.head->getNext();
   for (int n = 0; n < numElems; n++)
   {
      T copyNodeValue = tempCopyPtr->getValue();
      this->insertValue(copyNodeValue);
      tempCopyPtr = tempCopyPtr->getNext();
   }
};

template <class T>
SortedListClass< T >::~SortedListClass(
)
{
   clear();
   delete head;
   delete tail;
};

template <class T>
void SortedListClass< T >::clear(
)
{
   int numElems = getNumElems();
//Detecting if there is one node or multiple (Zero element arrays are caught by
//the else statement, which doesn't do anything since the for loop won't
//iterate over anything:
   if (numElems == 1)
   {
      delete [] head->getNext();
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
//Deletes the final node in the linked list (Prev of tail):
      delete tail->getPrev();
//      delete tempCountingPtr;
      head->setNextPointerToNull();
      tail->setPreviousPointerToNull();
   }
};

template <class T>
void SortedListClass< T >::insertValue(
const T &valToInsert
)
{
//Implementing list insertion:
   bool insertChoice = false;
   int countingIndex = 0;
   LinkedNodeClass< T > *tempPlacerPtr = head;
   T valueNull();

   while (tempPlacerPtr != 0 && !insertChoice)
   {
//Checking to see if this is the first value in the list:
      if (head->getNext() == NULL
         && tail->getPrev() == NULL)
      {
         LinkedNodeClass< T > *newNode;
         newNode = new LinkedNodeClass< T >(head, valToInsert, tail);
         newNode->setBeforeAndAfterPointers();
         newNode->setNextPointerToNull();
         newNode->setPreviousPointerToNull();
         insertChoice = true;
      }
      else
      {
         tempPlacerPtr = tempPlacerPtr->getNext();
         countingIndex++;
//Inserting a new value before the current tempPlacerPtr pointer
//(if tempPlacerPtr doesn't point null/isn't currently the header):
         if (tempPlacerPtr->getValue() > valToInsert)
         {
            LinkedNodeClass< T > *newNode;
//If this is the first value:
            if (countingIndex == 1)
            {
               newNode = new LinkedNodeClass< T >(head, valToInsert, tempPlacerPtr);
               newNode->setBeforeAndAfterPointers();
               newNode->setPreviousPointerToNull();
            }
//If this is any other value lower than an existing one:
            else
            {
               newNode = new LinkedNodeClass< T >(tempPlacerPtr->getPrev(),
                  valToInsert, tempPlacerPtr);
               newNode->setBeforeAndAfterPointers();
            }
            insertChoice = true;
         }
//Inserting the value at the end, in the case that the loop has reached the
//end of the array, indicating that valToAdd is the largest number so far:
         else if (tempPlacerPtr->getNext() == NULL)
         {
            LinkedNodeClass< T > *newNode;
            newNode = new LinkedNodeClass< T >(tempPlacerPtr, valToInsert, tail);
            newNode->setBeforeAndAfterPointers();
            newNode->setNextPointerToNull();
            insertChoice = true;
         }

      }
   }
};

template <class T>
void SortedListClass< T >::printForward(
) const
{
   cout << "Forward List Contents Follow:" << endl;
   bool printFinished = false;
   LinkedNodeClass< T > *printPointer = head;
//If head points null, and the list is empty:
   if (printPointer->getNext() == NULL)
      {
         cout << "End Of List Contents" << endl;
      }
//If there are values in the list:
   else
   {
      printPointer = printPointer->getNext();
      while (printFinished == false)
      {
         cout << "  " << printPointer->getValue() << endl;
         if (printPointer->getNext() == NULL)
         {
            cout << "End Of List Contents" << endl;
            printFinished = true;
         }
         else
         {
            printPointer = printPointer->getNext();
         }
      }
   }
};

template <class T>
void SortedListClass< T >::printBackward(
) const
{
   cout << "Backward List Contents Follow:" << endl;
   bool printFinished = false;
   LinkedNodeClass< T > *printPointer = tail;
//If head points null, and the list is empty:
   if (printPointer->getPrev() == NULL)
      {
         cout << "End Of List Contents" << endl;
      }

//If there are values in the list:
   else
   {
      printPointer = printPointer->getPrev();
      while (printFinished == false)
      {
         cout << "  " << printPointer->getValue() << endl;
         if (printPointer->getPrev() == NULL)
         {
            cout << "End Of List Contents" << endl;
            printFinished = true;
         }
         else
         {
            printPointer = printPointer->getPrev();
         }
      }
   }
};

template <class T>
bool SortedListClass< T >::removeFront(
T &theVal
)
{
//If the list is empty:
   if (head->getNext() == NULL)
   {
      return false;
   }
   else
   {
      theVal = head->getNext()->getValue();
      LinkedNodeClass< T > *newFirstObject;
//If the list only contains one value:
      if (head->getNext()->getPrev() == NULL
         && head->getNext()->getNext() == NULL)
      {
         theVal = head->getNext()->getValue();
         clear();
      }
//If the list contains two values (The new first value will also be the last):
      else if (head->getNext()->getNext()->getNext() == NULL)
      {

         newFirstObject = new LinkedNodeClass< T >(head,
            head->getNext()->getNext()->getValue(),
            tail);
         newFirstObject->setBeforeAndAfterPointers();
         newFirstObject->setNextPointerToNull();
         newFirstObject->setPreviousPointerToNull();
      }
//If the list contains more than two values:
      else
      {
         newFirstObject = new LinkedNodeClass< T >(head,
            head->getNext()->getNext()->getValue(),
            head->getNext()->getNext()->getNext());
         newFirstObject->setBeforeAndAfterPointers();
         newFirstObject->setPreviousPointerToNull();
      }
      return true;
   }
};

template <class T>
bool SortedListClass< T >::removeLast(
T &theVal
)
{
//If the list is empty:
   if (tail->getPrev() == NULL)
   {
      return false;
   }
   else
   {
      theVal = tail->getPrev()->getValue();
      LinkedNodeClass< T > *newFirstObject;

//If the list only contains one value:
      if (tail->getPrev()->getNext() == NULL
         && tail->getPrev()->getPrev() == NULL)
      {
         theVal = tail->getPrev()->getValue();
         clear();
      }

//If the list contains two values (The new first value will also be the last):
      else if (tail->getPrev()->getPrev()->getPrev() == NULL)
      {

         newFirstObject = new LinkedNodeClass< T >(head,
            tail->getPrev()->getPrev()->getValue(),
            tail);
         newFirstObject->setBeforeAndAfterPointers();
         newFirstObject->setNextPointerToNull();
         newFirstObject->setPreviousPointerToNull();
      }

//If the list contains more than two values:
      else
      {
         newFirstObject = new LinkedNodeClass< T >(
            tail->getPrev()->getPrev()->getPrev(),
            tail->getPrev()->getPrev()->getValue(),
            tail);
         newFirstObject->setBeforeAndAfterPointers();
         newFirstObject->setNextPointerToNull();
      }
      return true;
   }
};

template <class T>
int SortedListClass< T >::getNumElems(
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
bool SortedListClass< T >::getElemAtIndex(
const int index,
T &outVal
) const
{
   int listLength = getNumElems();

//If list is empty or index provided is out of range, return fail state:
   if ((head->getNext() == NULL && tail->getPrev() == NULL)
      || (index > (listLength-1)))
   {
      return false;
   }
//If list contains values and the index is in range, find the value at
//the given index:
   else
   {
      LinkedNodeClass< T > *tempCounter = head;

      for (int n = 0; n <= index; n++)
      {
         tempCounter = tempCounter->getNext();
      }

      outVal = tempCounter->getValue();

      return true;
   }
};

