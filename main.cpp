#include <iostream>
#include "SortedListClass.h"
#include "FIFOQueueClass.h"
#include "random.h"
using namespace std;

int main()
{
   cout << "Testing SortedListClass With Chars: " << endl;
   string testFront;
   string testNum;
   string testLast;
   int testInd = 3;
   SortedListClass <string> testList;
   testList.insertValue("ab");
   testList.insertValue("bc");
   testList.insertValue("cd");
   testList.insertValue("de");
   testList.printForward();
   cout << testList.getElemAtIndex(testInd,testNum) << testNum << endl;
   SortedListClass <string> testListClone(testList);

   testListClone.printForward();
   testListClone.removeFront(testFront);
   testList.removeLast(testLast);
   testList.printForward();
   testListClone.printForward();

   cout << "Testing SortedListClass With ints: " << endl;
   int testFront2;
   int testNum2;
   int testLast2;
   int testInd2 = 3;
   SortedListClass <int> testList2;
   testList2.insertValue(1);
   testList2.insertValue(2);
   testList2.insertValue(3);
   testList2.insertValue(4);
   testList2.printForward();
   cout << testList2.getElemAtIndex(testInd2,testNum2) << testNum2 << endl;
   SortedListClass <int> testListClone2(testList2);

   testListClone2.printForward();
   testListClone2.removeFront(testFront2);
   testList2.removeLast(testLast2);
   testList2.printForward();
   testListClone2.printForward();

//testing FIFOQueueClass:
   cout << "\nTesting FIFOQueueClass with Chars: " << endl;
   string outQueue;
   FIFOQueueClass <string> testQueue;
   testQueue.enqueue("de");
   testQueue.enqueue("cd");
   testQueue.enqueue("bc");
   testQueue.enqueue("za");
   testQueue.print();
   cout << testQueue.dequeue(outQueue) << " " << outQueue << endl;
   testQueue.print();
   testQueue.enqueue("de");
   testQueue.print();
   testQueue.clear();
   testQueue.print();

//testing FIFOQueueClass:
   cout << "\nTesting FIFOQueueClass With Ints: " << endl;
   int outQueue2;
   FIFOQueueClass <int> testQueue2;
   testQueue2.enqueue(4);
   testQueue2.enqueue(3);
   testQueue2.enqueue(2);
   testQueue2.enqueue(1);
   testQueue2.print();
   cout << testQueue2.dequeue(outQueue2) << " " << outQueue2 << endl;
   testQueue2.print();
   testQueue2.enqueue(4);
   testQueue2.print();
   testQueue2.clear();
   testQueue2.print();
}
