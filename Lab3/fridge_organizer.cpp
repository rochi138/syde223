#include <iostream>
#include <list> // see http://www.cplusplus.com/reference/list/list/ for additional reference
#include <stack> // see http://www.cplusplus.com/reference/stack/stack/ for additional reference
#include "fridge_organizer.hpp"
using namespace std;

// PURPOSE: Parametric constructor for FridgeOrganizer
FridgeOrganizer::FridgeOrganizer(unsigned int n_stack_number, unsigned int n_stack_capacity) {
	if (n_stack_number >= 2) 		
		stack_number = n_stack_number;		
	else 
		stack_number = 2;
	usable_stacks = stack_number - 1;
	stack_capacity = n_stack_capacity;
}

// PURPOSE: Destructor for FridgeOrganizer
FridgeOrganizer::~FridgeOrganizer() {
	for (list<stack<MealPortion*>*>::iterator i = stacks.begin(); i != stacks.end(); ++i) {
		stack<MealPortion*>* cur_stack = *i; int cur_stack_size = cur_stack->size();
		for (int index = 0; index < cur_stack_size; ++index) {
			delete cur_stack->top();
			cur_stack->pop();
		}
		delete *i;
	}		
}

// PURPOSE: Prints all meal stacks in the fridge
void FridgeOrganizer::print_stacks() {
	cout << endl << "-= START OF CURRENT FRIDGE ORGANIZER STATE =-" << endl;
	// use iterator to iterate through list elements
	int cur_stack_index = 0;
	for (list<stack<MealPortion*>*>::iterator i = stacks.begin(); i != stacks.end(); ++i, ++cur_stack_index) {
		cout << "STACK " << cur_stack_index << endl;
		// iterate through stack elements
		stack<MealPortion*> cur_stack = **i; int cur_stack_size = cur_stack.size();
		for (int cur_element_index = 0; cur_element_index < cur_stack_size; ++cur_element_index) {
			cout << "| ELEMENT " << cur_element_index << ": " << cur_stack.top()->name << ", " << cur_stack.top()->expiry << " |" << endl;
			cur_stack.pop();
		}
	}
	cout << "-= END OF CURRENT FRIDGE ORGANIZER STATE =-" << endl << endl;
}	

// TO-DO: implement the number_of_portions() method
// PURPOSE: Returns the number of meal portions in the fridge
int FridgeOrganizer::number_of_portions() {
	// step1 initialize portion count to 0
	// step2 use list iterator to iterate through list elements; see print function
	// step2.1 add current stack size to portion count
	// step3 return final portion count
	return 0;
}	

// TO-DO: implement the add_meal_portion() method
// PURPOSE: Adds a new meal portion to existing portions if there is space
// insert the portion into the first empty stack from the back
bool FridgeOrganizer::add_meal_portion(string n_name, string n_expiry) {
	// step1 create a new meal portion object on the heap
	
	// step2 grab a pointer to the last stack from the back
	
	// step3 if the stacks list is not empty and there is space in the current stack
	// step3.1 insert the new meal into the current stack
	
	// step4 else if there is space for a new stack
	// step4.1 create a new stack with new stack<MealPortion*>
	// step4.2 add the meal portion to that stack
	// step4.3 add the new stack to the stacks list
	
	// step5 else there is no more space for new stacks
	// step5.1 return false
	
	// step6 return true if addition was successful
	return true;
}	

// TO-DO: implement the remove_meal_portion() method
// PURPOSE: Removes the meal from the fridge based on LIFO principle
// if the fridge is empty, returns ("EMPTY", "N/A")
FridgeOrganizer::MealPortion FridgeOrganizer::remove_meal_portion() {
	// step1 create a temporary MealPortion("EMPTY", "N/A") object called m
	
	// step2 if the stacks list is empty
	// step2.1 return corresponding m value

	// step3 grab a pointer to the stack at the back of the list
	// step4 set m's value to match the value of top element of that stack
	// step5 free memory for the top element and pop it from the stack

	// step6 if the current stack is empty
	// step6.1 free its memory and remove it from the list

	// step7 return corresponding m value
	return MealPortion("","");
}

// TO-DO: implement the find_meal_portion_by_expiry() method
// PURPOSE: Finds the meal in the fridge with earliest expiry date value
// assumes that valid expiry will be expressed as YY-MM-DD
// if the fridge is empty, returns ("EMPTY", "N/A")
// this method may not disrupt other functionality
FridgeOrganizer::MealPortion FridgeOrganizer::find_meal_portion_by_expiry() {
	// step1 create a temporary MealPortion("EMPTY", "N/A") object called min

	// step2 if the stacks list is empty
	// step2.1 return min value

	// step3 use list iterator to go through list elements; see print function
	// step3.1 create a local copy of the current stack; also, store its size as a variable
	// step3.2 iterate through the copy of the current stack using index value
	// step3.2.1 grab a pointer to the top of the stack
	// step3.2.2 if the stack top's expiry date is less than min->expiry
	// step3.2.2.1 copy the stack top's value into min
	// step3.2.3 pop the top element from the stack; do not free its memory		

	// step4 return corresponding min value
	return MealPortion("","");
}

// PURPOSE: Tests FridgeOrganizer constructor and basic item insertion
bool FridgeOrganizerTest::test1() {
	FridgeOrganizer fridge1(1,2);
	fridge1.add_meal_portion("Portion1", "18-07-01");
	fridge1.add_meal_portion("Portion2", "18-07-03");
	ASSERT_TRUE(fridge1.number_of_portions() == 2);	
	fridge1.add_meal_portion("Portion3", "18-08-03");
	fridge1.add_meal_portion("Portion4", "18-08-05");
	ASSERT_TRUE(fridge1.number_of_portions() == 2);			
	return true;	
}

// PURPOSE: Tests stack growth and shrinking with LIFO removal
bool FridgeOrganizerTest::test2() {
	FridgeOrganizer fridge(6,4);
	fridge.add_meal_portion("Portion1", "18-07-01");
	fridge.add_meal_portion("Portion2", "18-07-03");
	fridge.add_meal_portion("Portion3", "18-08-03");
	fridge.add_meal_portion("Portion4", "18-08-05");
	fridge.add_meal_portion("Portion5", "18-08-15");
	fridge.add_meal_portion("Portion6", "18-08-25");
	ASSERT_TRUE(fridge.number_of_portions() == 6);		
	//fridge.print_stacks();
	ASSERT_TRUE(fridge.remove_meal_portion().expiry == "18-08-25");
	ASSERT_TRUE(fridge.remove_meal_portion().expiry == "18-08-15");
	ASSERT_TRUE(fridge.remove_meal_portion().name == "Portion4");
	ASSERT_TRUE(fridge.remove_meal_portion().name == "Portion3");
	ASSERT_TRUE(fridge.number_of_portions() == 2);	
	//fridge.remove_meal_portion().print();
	//fridge.print_stacks();
	fridge.remove_meal_portion();
	fridge.remove_meal_portion();
	fridge.remove_meal_portion();
	fridge.remove_meal_portion();
	//fridge.print_stacks();
	//fridge.remove_meal_portion().print();
	ASSERT_TRUE(fridge.number_of_portions() == 0);		
	return true;	
}

// PURPOSE: Tests finding meal portion by earliest expiry date
bool FridgeOrganizerTest::test3() {
	FridgeOrganizer fridge(7,4);
	fridge.add_meal_portion("Portion1", "19-07-01");
	fridge.add_meal_portion("Portion2", "19-07-03");
	fridge.add_meal_portion("Portion3", "19-06-03");
	fridge.add_meal_portion("Portion4", "19-08-05");
	fridge.add_meal_portion("Portion5", "19-08-15");
	fridge.add_meal_portion("Portion6", "19-05-25");
	//fridge.print_stacks();
	ASSERT_TRUE(fridge.find_meal_portion_by_expiry().expiry == "19-05-25")
	fridge.remove_meal_portion();
	ASSERT_TRUE(fridge.find_meal_portion_by_expiry().expiry == "19-06-03")
	fridge.remove_meal_portion();
	fridge.remove_meal_portion();
	fridge.remove_meal_portion();
	//fridge.find_meal_portion_by_expiry().print();
	ASSERT_TRUE(fridge.find_meal_portion_by_expiry().expiry == "19-07-01")
	return true;	
}

// PURPOSE: Runs all of the specified tests and produces corresponding output
void FridgeOrganizerTest::runTests() {
	cout << endl << "-= TEST 1: Test FridgeOrganizer constructor and basic item insertion";
	cout << (test1() ? " PASSED =-" : " FAILED =-") << endl;
	cout << endl << "-= TEST 2: Test stack growth and shrinking with LIFO removal";
	cout << (test2() ? " PASSED =-" : " FAILED =-") << endl;
	cout << endl << "-= TEST 3: Test find meal portion by earliest expiry date";
	cout << (test3() ? " PASSED =-" : " FAILED =-") << endl;
}

int main() {
	FridgeOrganizerTest fridge_test;
	fridge_test.runTests();	
	return 0;
}

