#include "LinkedNodeClass.h"
#include <iostream>

//Ethan Gregory
//November 24 2020
//This class allows the user to generate a node, which contains
//a value, as well as two pointers that allow the user to link the
//node to two other nodes, particularly useful for list generation.
template < class T >
LinkedNodeClass< T >::LinkedNodeClass(
LinkedNodeClass< T >  *inPrev,
const T &inVal,
LinkedNodeClass< T > *inNext
)
{
   prevNode = inPrev;
   nextNode = inNext;
   nodeVal = inVal;
};

template < class T >
 T LinkedNodeClass< T >::getValue(
) const
{
   return nodeVal;
};

template < class T >
LinkedNodeClass< T >* LinkedNodeClass< T >::getNext(
) const
{
   return nextNode;
};

template < class T >
LinkedNodeClass< T >* LinkedNodeClass< T >::getPrev(
) const
{
   return prevNode;
};

template < class T >
void LinkedNodeClass< T >::setNextPointerToNull(
)
{
   nextNode = NULL;
};

template < class T >
void LinkedNodeClass< T >::setPreviousPointerToNull(
)
{
   prevNode = NULL;
};

template < class T >
void LinkedNodeClass< T >::setBeforeAndAfterPointers(
)
{
   nextNode->prevNode = this;
   prevNode->nextNode = this;
};
