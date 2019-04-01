// Robyn Ching 20719829
// Chris Staykov 20717876
// Jozef Brudnicki 20723332
#include "lab4_priority_queue.hpp"

// PURPOSE: Parametric constructor 
// initializes heap to an array of (n_capacity + 1) elements
PriorityQueue::PriorityQueue(unsigned int n_capacity) {
	capacity = n_capacity;
    size = 0;
	heap = new TaskItem*[n_capacity + 1];
}

// PURPOSE: Explicit destructor of the class PriorityQueue
PriorityQueue::~PriorityQueue() {
	for (int i = 1; i <= size; i++){
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
	return !size;
}

// PURPOSE: Returns true if the priority queue is full; false, otherwise
bool PriorityQueue::full() const {
    return size == capacity;
}

// PURPOSE: Prints the contents of the priority queue; format not specified
void PriorityQueue::print() const {
	if (!size){
		cout<<"No items in queue"<<endl;
		return;
	}
	cout<<"Task #\t"<<"Priority\t"<<"Description"<<endl;
	for (int i = 1; i <= size; ++i){
		cout<<i<<"\t"<<heap[i]->priority<<"\t\t"<<heap[i]->description<<endl;
	}
}

// PURPOSE: Returns the max element of the priority queue without removing it
// if the priority queue is empty, it returns (-1, "N/A")
PriorityQueue::TaskItem PriorityQueue::max() const {
    
    if (size)
        return *heap[1];
    else
        return TaskItem(-1, "N/A");
    
}

// PURPOSE: Inserts the given value into the priority queue
// re-arranges the elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::enqueue( TaskItem val ) {
	if (size == capacity)
		return false;
    
    if (size == 0)
        heap[1] = new TaskItem(val);
    else {
        int i = size + 1;
        heap[i] = new TaskItem(val);
        while (i > 1 && heap[i/2]->priority < heap[i]->priority) {
            TaskItem* swap = heap[i];
            heap[i] = heap[i/2];
            heap[i/2] = swap;
            i = i/2;
        }
    }
	size++;
	return true;
}

// PURPOSE: Removes the top element with the maximum priority
// re-arranges the remaining elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::dequeue() {
    
    // Empty heap case
    if (size == 0)
        return false;
    
    else {
        
        // Delete pointer for max value and replace with bottom value of heap
        delete heap[1];
        heap[1] = heap[size];
        heap[size] = NULL;
        size--;
        
        unsigned int i = 1;
        unsigned int largest, left, right;
        
        // Sort heap down starting with root
        while (1){
            largest = i;
            left = 2*i;
            right = 2*i + 1;
            
            if (left <= size && heap[left] > heap[i])
                largest = left;
            
            if (right <= size && heap[right] > heap[largest])
                largest = right;
            
            // If node is larger than children, exit, else swap with largest child
            if (largest == i)
                return true;
            else {
                TaskItem* swap = heap[i];
                heap[i] = heap[largest];
                heap[largest] = swap;
                i = largest;
            }
                
        }
        
    }
    return false;
}
