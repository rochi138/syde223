// Lab 3
// Chris Staykov 20717876
// Robyn Ching 20719829

#include "lab3_fridge_organizer.hpp"

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

// PURPOSE: Returns the number of meal portions in the fridge
int FridgeOrganizer::number_of_portions() {
    
    // Return 0 if insufficient number of stacks
    if (stacks.size() < 2){
        return 0;
    }
    
    // Assign counter to value of total number of full stacks
    int portionCount = (stacks.size() - 2) * stack_capacity;
    
    // Add to count the number of portions stored in second last stack
    portionCount += (*(--(--stacks.end())))->size();

    return portionCount;
}

// PURPOSE: Adds a new meal portion to existing portions if there is space
// insert the portion into the first empty stack from the back
bool FridgeOrganizer::add_meal_portion(string n_name, string n_expiry) {
    
    // If insufficient number of stacks, add them
    while(stacks.size() < 2 ) {
        stacks.push_back(new stack<MealPortion*>);
    }
    
    stack<MealPortion*>* lastUsableStack = *(--(--stacks.end()));
    
    // If last usable stack is at capacity, add a new stack if possible
    if (lastUsableStack->size() == stack_capacity){
        if (stacks.size() < stack_number)
            stacks.push_back(new stack<MealPortion*>);
        else
            return false;
        lastUsableStack = *(--(--stacks.end()));
    }
    
    // Add new meal portion to the last usable stack
    lastUsableStack->push(new MealPortion(n_name, n_expiry));
    
    return true;
}

// PURPOSE: Removes the meal from the fridge based on LIFO principle
// if the fridge is empty, returns ("EMPTY", "N/A")
FridgeOrganizer::MealPortion FridgeOrganizer::remove_meal_portion() {
    
    // Create a temporary MealPortion("EMPTY", "N/A") object called m
    MealPortion m = MealPortion("EMPTY", "N/A");
    
    // If the stacks list is empty return m
    if (stacks.size() < 2){
        return m;
    }
    
    // Get pointer to last usable stack and store top value of meal portion
    stack<MealPortion*>* lastStack = *(--(--stacks.end()));
    m = *(lastStack->top());
    
    // Deallocate memory and remove pointer from top of stack
    delete lastStack->top();
    lastStack->pop();
    
    // Remove stack if empty
    if (lastStack->size() == 0){
        delete stacks.back();
        stacks.pop_back();
    }
    
    return m;
}

// PURPOSE: Finds the meal in the fridge with earliest expiry date value
// assumes that valid expiry will be expressed as YY-MM-DD
// if the fridge is empty, returns ("EMPTY", "N/A")
// this method may not disrupt other functionality
FridgeOrganizer::MealPortion FridgeOrganizer::find_meal_portion_by_expiry() {
    
    // Create a temporary MealPortion("EMPTY", "N/A") object called min
    MealPortion min = MealPortion("EMPTY", "N/A");
    
    // If the stacks list is empty return min
    if (stacks.size() < 2){
        return min;
    }
    
    // step3 use list iterator to go through list elements; see print function
    // step3.1 create a local copy of the current stack; also, store its size as a variable
    // step3.2 iterate through the copy of the current stack using index value
    // step3.2.1 grab a pointer to the top of the stack
    // step3.2.2 if the stack top's expiry date is less than min.expiry
    // step3.2.2.1 copy the stack top's value into min
    // step3.2.3 pop the top element from the stack; do not free its memory
    
    int cur_stack_index = 0;
    for (list<stack<MealPortion*>*>::iterator i = stacks.begin(); i != stacks.end(); ++i, ++cur_stack_index) {
        stack<MealPortion*> cur_stack = **i;
        unsigned long cur_stack_size = cur_stack.size();
        for (int cur_element_index = 0; cur_element_index < cur_stack_size; ++cur_element_index) {
            if (cur_stack.top()->expiry < min.expiry) {
                min = *cur_stack.top();
            }
            cur_stack.pop();
        }
    }
    
    // Return corresponding min value
    return min;
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
