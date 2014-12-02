/*
* Author: Nick Cooperrider
* Date: 11/11/2014
* All code was written by myself with examples taken from the reading and in class.
*
*/

#include "Queue.h"
#include <utility>

//This should be the initial arrSize
#define START_SIZE 10

/*
 * This is a priority queue, which means that as items are removed in order
 * of decreasing priority.
 *
 * 
 */
template<class Pri, class T>
class Heap : public Queue<std::pair<Pri, T> > {
public:
  Heap();
  ~Heap();

  //Add a new item
  virtual void add(std::pair<Pri,T> toAdd);

  //Remove the item with lowest priority, and return it
  //If the queue is empty, throw a string exception
  virtual std::pair<Pri,T> remove();

  //Return the number of items currently in the queue
  virtual unsigned long getNumItems();

private:
  int arrSize;
  int numItems;
  std::pair<Pri, T>* backingArray;

  //Grow the backingArray by making a new array of twice the size,
  // and copying over the data
  void grow();

  //Check the item at index, and make sure it is in the right place.
  // If not, swap it up the "tree" of the heap until you find the right
  // place
  void bubbleUp(unsigned long index);

  //Check the item at index, and make sure it is in the right place.
  // If not, swap it down the "tree" of the heap until you find the right
  // place
  void trickleDown(unsigned long index);  
};

//heap.ipp starts here

#include <string>

template<class Pri, class T>
Heap<Pri,T>::Heap(){
  arrSize = START_SIZE;
  numItems = 0;
  backingArray = new std::pair<Pri, T>[START_SIZE];
}

template<class Pri, class T>
Heap<Pri,T>::~Heap(){
	delete[] backingArray;
	numItems = 0;
	arrSize = 0;
}

template<class Pri, class T>
void Heap<Pri,T>::grow(){
	
	arrSize = arrSize * 2;
	std::pair<Pri, T>* tempArray = new std::pair<Pri, T>[arrSize];

	for(int i = 0; i < numItems; i++) {
		tempArray[i] = backingArray[i];
	}

	delete[] backingArray;
	backingArray = tempArray;
}

template<class Pri, class T>
void Heap<Pri,T>::add(std::pair<Pri,T> toAdd){
	
	if(numItems == arrSize) {
		grow();
	}

	backingArray[numItems] = toAdd;
	bubbleUp(numItems);
	numItems++;
}

template<class Pri, class T>
void Heap<Pri,T>::bubbleUp(unsigned long index){

	int parent = (index - 1)/2;

	if (backingArray[parent] > backingArray[index] && index > 0) {
		backingArray[parent].swap(backingArray[index]);
		index = parent;
		bubbleUp(parent);
	}
}

template<class Pri, class T>
void Heap<Pri,T>::trickleDown(unsigned long index){

	do {
 		int count = -1;
 		int left = (2 * index) + 1;
 		int right = (2 * index) + 2;
 
 		if (backingArray[index] > backingArray[left] || backingArray[index] > backingArray[right]) {
 			if (backingArray[left] < backingArray[right])
 				count = left;
 			else
				count = right;
 		}
 
 		if (count >= 0)
 			backingArray[index].swap(backingArray[count]);
 
 
 		index = count;
 	} while (index <= 0);
 }

template<class Pri, class T>
std::pair<Pri,T> Heap<Pri,T>::remove(){

	if(numItems == 0) {
		throw std::string("Error, no items to remove");
	}

	std::pair<Pri,T> tmp = backingArray[0];
	backingArray[0] = backingArray[(numItems - 1)];
	numItems--;
	trickleDown(0);

  return tmp;
}

template<class Pri, class T>
unsigned long Heap<Pri,T>::getNumItems(){
  return numItems;
}
