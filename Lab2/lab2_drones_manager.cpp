#include "lab2_drones_manager.hpp"

// TODO: Implement all of the listed functions below

DronesManager::DronesManager() : first(NULL), last(NULL), size(0) {
}

DronesManager::~DronesManager() {
    DroneRecord* current = first;
    while (current != NULL){
        current = first->next;
        delete first;
        first = current;
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
    if (index == 0)
        return (remove_front());
    if (index == size-1)
        return (remove_back());
    
    DroneRecord* before = first;
    
    for (int i = 0; i < index - 1 && before != NULL; i++){
        before = before->next;
    }
    
    DroneRecord* toRemove = before->next;
    
    before->next = before->next->next;
    before->next->prev = before;
    delete toRemove;
    size--;
    return true;
}

bool DronesManager::remove_front() {
    if (first == NULL)
        return false;
    if (size == 1){
        delete first;
        first = NULL;
        last = NULL;
        size--;
        return true;
    }
    
    DroneRecord* toRemove = first;
    
    first->next->prev = NULL;
    first = first->next;
    delete toRemove;
    size--;
    return true;
}

bool DronesManager::remove_back() {
    if (first == NULL)
        return false;
    if (size == 1){
        delete first;
        first = NULL;
        last = NULL;
        size--;
        return true;
    }
    
    DroneRecord* toRemove = last;
    
    last->prev->next = NULL;
    last = last->prev;
    delete toRemove;
    size--;
    return true;
}

bool DronesManager::replace(unsigned int index, DroneRecord value) {
    
    return (remove(index) && insert(value, index));
}

bool DronesManager::reverse_list() {
    if (first == NULL)
        return false;
    if (size == 1)
        return true;
    DroneRecord* temp = first;
    first = last;
    last = temp;
    DroneRecord* current = first;
    while (current != NULL){
        temp = current->next;
        current->next = current->prev;
        current->prev = temp;
        current = current->next;
    }
    return true;
}

bool DronesManagerSorted::is_sorted_asc() const {
    if (first == NULL || size == 1)
        return true;
    DroneRecord* current = first->next;
    while (current != NULL){
        if (current->prev->droneID > current->droneID)
            return false;
        current = current->next;
    }
    return true;
}

bool DronesManagerSorted::is_sorted_desc() const {
    if (first == NULL || size == 1)
        return true;
    DroneRecord* current = last->prev;
    while (current != NULL){
        if (current->next->droneID > current->droneID)
            return false;
        current = current->next;
    }
    return true;
}

bool DronesManagerSorted::insert_sorted_asc(DroneRecord val) {
    if (!is_sorted_asc())
        return false;
    if (first == NULL || first->droneID >= val.droneID)
        return (insert_front(val));
    if (last->droneID <= val.droneID)
        return (insert_back(val));
    DroneRecord* before = first;
    unsigned int index = 0;
    while(before != NULL && before->droneID < val.droneID){
        before = before->next;
        index++;
    }
    return insert(val, index);
}

bool DronesManagerSorted::insert_sorted_desc(DroneRecord val) {
    if (!is_sorted_desc())
        return false;
    if (first == NULL || first->droneID <= val.droneID)
        return (insert_front(val));
    if (last->droneID >= val.droneID)
        return (insert_back(val));
    DroneRecord* after = first;
    unsigned int index = 0;
    while(after != NULL && after->droneID > val.droneID){
        after = after->next;
        index++;
    }
    return insert(val, index);
}

void DronesManagerSorted::sort_asc() {
    if (first == NULL)
        return;
    if (size == 1)
        return;
    DroneRecord* subfirst = first;
    DroneRecord* current;
    DroneRecord* min;
    while (subfirst->next != NULL){
        current = first->next;
        min = subfirst;
        while (current != NULL){
            if (min->droneID < current->droneID)
                min = current;
            current = current->next;
        }
        if (subfirst == first){
            if (min != first)
                min->prev->next = min->next;
            else
                first = min->next;
        } else
            subfirst->prev->next = min;
        if (min != last)
            min->next->prev = min->prev;
        else
            last = min->prev;
        min->prev = subfirst->prev;
        min->next = subfirst;
        subfirst->prev = min;
        subfirst = subfirst->next;
    }
}

void DronesManagerSorted::sort_desc() {
    if (first == NULL)
        return;
    if (size == 1)
        return;
    DroneRecord* subfirst = first;
    DroneRecord* current;
    DroneRecord* max;
    while (subfirst->next != NULL){
        current = first->next;
        max = subfirst;
        while (current != NULL){
            if (max->droneID < current->droneID)
                max = current;
            current = current->next;
        }
        if (subfirst == first){
            if (max != first)
                max->prev->next = max->next;
            else
                first = max->next;
        } else
            subfirst->prev->next = max;
        if (max != last)
            max->next->prev = max->prev;
        else
            last = max->prev;
        max->prev = subfirst->prev;
        max->next = subfirst;
        subfirst->prev = max;
        subfirst = subfirst->next;
    }
}

