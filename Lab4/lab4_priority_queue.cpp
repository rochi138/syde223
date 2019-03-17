#include<iostream>
#include "lab4_priority_queue.hpp"

using namespace std;

// PURPOSE: Parametric constructor 
// initializes heap to an array of (n_capacity + 1) elements
PriorityQueue::PriorityQueue(unsigned int n_capacity) {
	capacity = n_capacity;
	heap = new TaskItem*[n_capacity + 1];
}

// PURPOSE: Explicit destructor of the class PriorityQueue
PriorityQueue::~PriorityQueue() {
	for (int i = 0; i < size; ++i){
		delete heap[i];
	}
	delete heap;
}

// PURPOSE: Returns the number of elements in the priority queue
unsigned int PriorityQueue::get_size() const {
	return size;
}

// PURPOSE: Returns true if the priority queue is empty; false, otherwise
bool PriorityQueue::empty() const {
	if (size)
		return false;
	return true;
}

// PURPOSE: Returns true if the priority queue is full; false, otherwise
bool PriorityQueue::full() const {
	if (size == capacity)
		return true;
	return false;
}

// PURPOSE: Prints the contents of the priority queue; format not specified
void PriorityQueue::print() const {
}

// PURPOSE: Returns the max element of the priority queue without removing it
// if the priority queue is empty, it returns (-1, "N/A")
PriorityQueue::TaskItem PriorityQueue::max() const {
	if (!size)
		return TaskItem(-1, "N/A");
	TaskItem* max = heap[0];
	for (int i = 1; i < size; ++i){
		if ( max->priority < heap[i]->priority )
			max = heap[i];
	}
	return *max;
}

// PURPOSE: Inserts the given value into the priority queue
// re-arranges the elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::enqueue( TaskItem val ) {
	if (size == capacity)
		return false;
	heap[size] = new TaskItem(val);
	++size;
	return true;
}

// PURPOSE: Removes the top element with the maximum priority
// re-arranges the remaining elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::dequeue() {
	if (!size)
		return false;
	int max = 0;
	for (int i = 1; i < size; ++i){
		if ( heap[max]->priority < heap[i]->priority )
			max = i;
	}
	delete heap[max];
	for (int i = max; i < size-1; ++i){
		heap[i] = heap[i+1];
	}
	--size;
	return true;
}
