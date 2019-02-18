#include "lab2_drones_manager.hpp"

// TODO: Implement all of the listed functions below

DronesManager::DronesManager() : first(NULL), last(NULL), size(0) {
}

DronesManager::~DronesManager() {
    DroneRecord* current = first;
    while (current != NULL){
        DroneRecord* next = current->next;
        delete current;
        current = next;
    }
}

bool operator==(const DronesManager::DroneRecord& lhs, const DronesManager::DroneRecord& rhs) {
    return (lhs.droneID == rhs.droneID &&
            lhs.range == rhs.range &&
            lhs.yearBought == rhs.yearBought &&
            lhs.droneType == rhs.droneType &&
            lhs.manufacturer == rhs.manufacturer &&
            lhs.description == rhs.description &&
            lhs.batteryType == rhs.batteryType);
}

unsigned int DronesManager::get_size() const {
    return size;
}

bool DronesManager::empty() const {
    return size == 0;
}

DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
    
    if ( this->empty() )
        return DroneRecord(0);
    
    if ( index >= size )
        return *last;
    
    DroneRecord* current = first;

    while (index != 0){
        current = current->next;
        index--;
    }
    
    return *current;
}

unsigned int DronesManager::search(DroneRecord value) const {
    
    if ( this->empty() )
        return 0;
    
    DroneRecord* current = first;
    int index = 0;
    
    while ( current != NULL ) {
        if ( *current == value )
            return index;
        index++;
        current = current->next;
    }
    
    return size;
}

void DronesManager::print() const {
    
    if ( this->empty() ) {
        cout<<"Printing error: Drone Manager List is empty"<<endl;
        return;
    }
    
    cout<<"=============================="<<endl;
    cout<<" Printing contents of list:"<<endl;
    
    DroneRecord* current = first;
    int index = 0;
    
    while (current != NULL) {
        cout<<"|----------------------------"<<endl;
        cout<< "|Drone Record "<<index<<": "<<endl;
        cout<<"|----------------------------"<<endl;
        cout<< "|Drone ID \t \t |"<<current->droneID<< endl;
        cout<< "|Range \t \t \t |"<<current->range<< endl;
        cout<< "|Year bought \t |"<<current->yearBought<< endl;
        cout<< "|Drone type  \t |"<<current->droneType<< endl;
        cout<< "|Description \t |"<<current->description<< endl;
        cout<< "|Manufacturer \t |"<<current->manufacturer<< endl;
        cout<< "|Battery type \t |"<<current->batteryType<< endl;
    
        current = current->next;
        index++;
    }
    
    cout<<"=============================="<<endl;
}

bool DronesManager::insert(DroneRecord value, unsigned int index) {
    if (index > size)
        return false;
    if (index == 0) {
        insert_front(value);
        return true;
    }
    if (index == size){
        insert_back(value);
        return true;
    }
    
    DroneRecord* before = first;
    
    for (int i = 0; i < index - 1 && before != NULL; i++){
        before = before->next;
    }
    
    DroneRecord* after = before->next;
    
    before->next = new DroneRecord(value);
    before->next->prev = before;
    before->next->next = after;
    after->prev = before->next;
    
    size++;
    return true;
}

bool DronesManager::insert_front(DroneRecord value) {
    
    if (first == NULL) {
        first = new DroneRecord(value);
        last = first;
        first->next = NULL;
        first->prev = NULL;
    } else {
        first->prev = new DroneRecord(value);
        first->prev->next = first;
        first = first->prev;
        first->prev = NULL;
    }
    
    size++;
    return true;
}

bool DronesManager::insert_back(DroneRecord value) {
    
    if (first == NULL) {
        first = new DroneRecord(value);
        last = first;
        first->next = NULL;
        first->prev = NULL;
    } else {
        last->next = new DroneRecord(value);
        last->next->prev = last;
        last = last->next;
        last->next = NULL;
    }
    
    size++;
    return true;
}

bool DronesManager::remove(unsigned int index) {
    if (index >= size)
        return false;
    if (first == NULL)
        return false;
    if (size == 1){
        first = NULL;
        last = NULL;
        size--;
        return true;
    }
    return false;
}

bool DronesManager::remove_front() {
    return false;
}

bool DronesManager::remove_back() {
    return false;
}

bool DronesManager::replace(unsigned int index, DroneRecord value) {
    return false;
}

bool DronesManager::reverse_list() {
    return false;
}

bool DronesManagerSorted::is_sorted_asc() const {
    return false;
}

bool DronesManagerSorted::is_sorted_desc() const {
    return false;
}

bool DronesManagerSorted::insert_sorted_asc(DroneRecord val) {
    return false;
}

bool DronesManagerSorted::insert_sorted_desc(DroneRecord val) {
    return false;
}

void DronesManagerSorted::sort_asc() {
}

void DronesManagerSorted::sort_desc() {
}

