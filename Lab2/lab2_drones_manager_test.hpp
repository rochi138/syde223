#ifndef DRONES_MANAGER_TEST
#define DRONES_MANAGER_TEST

#include "lab2_drones_manager.hpp"

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

class DronesManagerTest {
public:
    // PURPOSE: New empty list is valid
    bool test1() {
        DronesManager manager;
        ASSERT_TRUE(manager.get_size() == 0)
        ASSERT_TRUE(manager.empty() == true)
        ASSERT_TRUE(manager.first == NULL)
        ASSERT_TRUE(manager.last == NULL)
        
        return true;
    }
    
    // PURPOSE: insert_front() and insert_back() on zero-element list
    bool test2() {
        DronesManager manager1, manager2;
        ASSERT_TRUE(manager1.insert_front(DronesManager::DroneRecord(100)));
        ASSERT_TRUE(manager2.insert_back(DronesManager::DroneRecord(100)));
        
        ASSERT_TRUE(manager1.get_size() == manager2.get_size() && manager1.get_size() == 1)
        ASSERT_TRUE(manager1.first != NULL && manager1.first == manager1.last)
        ASSERT_TRUE(manager2.first != NULL && manager2.first == manager2.last)
        ASSERT_TRUE(manager1.first->prev == NULL && manager1.last->next == NULL)
        ASSERT_TRUE(manager2.first->prev == NULL && manager2.last->next == NULL)
        ASSERT_TRUE(manager1.select(0) == manager2.select(0) && manager1.select(0) == DronesManager::DroneRecord(100))
        return true;
    }
    
    // TODO: Implement all of the test cases below
    
    // PURPOSE: select() and search() work properly
    bool test3() {
        DronesManager manager1, manager2;
        const int num_elems = 5;
        
        for (int i = 0; i < num_elems; i++) {
            ASSERT_TRUE(manager1.insert_back(DronesManager::DroneRecord(i*100)))
        }
        
        for (int i = 0; i < num_elems; i++){
            ASSERT_TRUE(manager1.select(i) == DronesManager::DroneRecord(i*100));
            ASSERT_TRUE(manager1.search(DronesManager::DroneRecord(i*100)) == i);
            ASSERT_TRUE(manager1.search(manager1.select(i)) == i)
        }
        
        ASSERT_TRUE(manager1.select(5) == DronesManager::DroneRecord(400));
        ASSERT_TRUE(manager1.select(6) == DronesManager::DroneRecord(400));
        ASSERT_TRUE(manager2.select(0) == DronesManager::DroneRecord(0));
        ASSERT_TRUE(manager2.select(1) == DronesManager::DroneRecord(0));
        
        ASSERT_TRUE(manager1.search(DronesManager::DroneRecord(123)) == manager1.get_size());
        ASSERT_TRUE(manager2.search(DronesManager::DroneRecord(123)) == 0);
        ASSERT_TRUE(manager1.first->prev == NULL && manager1.last->next == NULL);
        
        return true;
    }
    
    // PURPOSE: remove_front() and remove_back() on one-element list
    bool test4() {
        DronesManager manager1, manager2, manager3;
        ASSERT_TRUE(manager1.insert_front(DronesManager::DroneRecord(123)))
        ASSERT_TRUE(manager2.insert_front(DronesManager::DroneRecord(123)))
        ASSERT_TRUE(manager3.insert(DronesManager::DroneRecord(123), 0))
        ASSERT_TRUE(manager1.remove_front())
        ASSERT_TRUE(manager2.remove_back())
        ASSERT_TRUE(manager3.remove_front())
        ASSERT_FALSE(manager3.remove_front())
        ASSERT_FALSE(manager3.remove_back())
        
        ASSERT_TRUE(manager1.first == NULL && manager1.last == NULL)
        ASSERT_TRUE(manager2.first == NULL && manager2.last == NULL)
        ASSERT_TRUE(manager3.first == NULL && manager3.last == NULL)
        ASSERT_TRUE(manager1.get_size() == 0)
        ASSERT_TRUE(manager2.get_size() == 0)
        ASSERT_TRUE(manager3.get_size() == 0)
        ASSERT_TRUE(manager1.empty())
        ASSERT_TRUE(manager2.empty())
        ASSERT_TRUE(manager3.empty())
        
        return true;
    }
    
    // PURPOSE: replace() and reverse_list() work properly
    bool test5() {
        DronesManager manager;
        const int num_elems = 8;
        for (int i = 0; i < num_elems; i++) {
            ASSERT_TRUE(manager.insert_back(DronesManager::DroneRecord(i)))
        }
        
        ASSERT_TRUE(manager.replace(0, DronesManager::DroneRecord(8)));
        ASSERT_TRUE(manager.replace(3, DronesManager::DroneRecord(9)));
        ASSERT_TRUE(manager.replace(7, DronesManager::DroneRecord(10)));
        ASSERT_TRUE(manager.replace(1, DronesManager::DroneRecord(1)));
        ASSERT_FALSE(manager.replace(8, DronesManager::DroneRecord(123)));
        
        ASSERT_TRUE(*manager.first == DronesManager::DroneRecord(8));
        ASSERT_TRUE(*manager.last == DronesManager::DroneRecord(10));
        ASSERT_TRUE(*(manager.first->next) == DronesManager::DroneRecord(1));
        ASSERT_TRUE(*(manager.last->prev) == DronesManager::DroneRecord(6));
        ASSERT_TRUE(*(manager.first->next->next->next) == DronesManager::DroneRecord(9));
        
        int test_values[8] = {10, 6, 5, 4, 9, 2, 1, 8};
        ASSERT_TRUE(manager.reverse_list());
        for (int i = 0; i < num_elems; i++) {
            ASSERT_TRUE(manager.select(i) == DronesManager::DroneRecord(test_values[i]));
        }
        
        ASSERT_TRUE(manager.first->prev == NULL && manager.last->next == NULL);
        
        return true;
    }
    
    // PURPOSE: insert_front() keeps moving elements forward
    bool test6() {
        DronesManager manager;
        const int num_elems = 10;
        for (int i = 0; i < num_elems; i++) {
            ASSERT_TRUE(manager.insert_front(DronesManager::DroneRecord(i)));
            ASSERT_TRUE(manager.get_size() == (i + 1));
            ASSERT_TRUE(*manager.first == DronesManager::DroneRecord(i));
            ASSERT_TRUE(manager.first->prev == NULL && manager.last->next == NULL);
            
            DronesManager::DroneRecord* n = manager.first;
            for (int j = 0; j <= i; j++) {
                DronesManager::DroneRecord expected_value = DronesManager::DroneRecord(i - j);
                ASSERT_TRUE(n != NULL && *n == expected_value);
                n = n->next;
            }
        }
        ASSERT_TRUE(manager.first->prev == NULL && manager.last->next == NULL);
        return true;
    }
    
    // PURPOSE: inserting at different positions in the list
    bool test7() {
        DronesManager manager;
        
        ASSERT_FALSE(manager.insert(DronesManager::DroneRecord(123), 1));
        ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(200), 0));
        ASSERT_FALSE(manager.insert(DronesManager::DroneRecord(321), 2));
        ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(500), 1));
        ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(300), 1));
        ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(000), 0));
        ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(100), 1));
        ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(400), 4));
        
        for (int i = 0; i < 6; i++){
            ASSERT_TRUE(manager.select(i) == DronesManager::DroneRecord(i*100));
            ASSERT_TRUE(manager.search(DronesManager::DroneRecord(i*100)) == i);
            ASSERT_TRUE(manager.search(manager.select(i)) == i);
        }
        
        ASSERT_TRUE(manager.first->prev == NULL && manager.last->next == NULL);
        
        return true;
    }
    
    // PURPOSE: try to remove too many elements, then add a few elements
    bool test8() {
        
        DronesManager manager1, manager2, manager3;
        
        ASSERT_TRUE(manager1.insert_back(DronesManager::DroneRecord(0)));
        ASSERT_TRUE(manager1.insert_back(DronesManager::DroneRecord(1)));
        ASSERT_TRUE(manager2.insert_back(DronesManager::DroneRecord(0)));
        ASSERT_TRUE(manager2.insert_back(DronesManager::DroneRecord(1)));
        ASSERT_TRUE(manager3.insert_back(DronesManager::DroneRecord(0)));
        ASSERT_TRUE(manager3.insert_back(DronesManager::DroneRecord(1)));
        
        ASSERT_FALSE(manager1.remove(2));
        ASSERT_TRUE(manager1.remove_back());
        ASSERT_FALSE(manager1.remove(1));
        ASSERT_TRUE(manager1.remove(0));
        ASSERT_FALSE(manager1.remove_back());
        ASSERT_FALSE(manager1.remove_front());
        ASSERT_FALSE(manager1.remove(0));
        
        ASSERT_TRUE(manager2.remove_front());
        ASSERT_TRUE(manager2.remove_back());
        ASSERT_FALSE(manager2.remove_back());
        ASSERT_FALSE(manager2.remove_front());
        ASSERT_FALSE(manager2.remove(0));
        
        ASSERT_TRUE(manager3.remove(1));
        ASSERT_TRUE(manager3.remove_front());
        ASSERT_FALSE(manager3.remove_back());
        ASSERT_FALSE(manager3.remove_front());
        ASSERT_FALSE(manager3.remove(0));
        
        
        ASSERT_TRUE(manager1.insert(DronesManager::DroneRecord(1), 0));
        ASSERT_TRUE(manager1.insert_back(DronesManager::DroneRecord(2)));
        ASSERT_TRUE(manager1.insert_front(DronesManager::DroneRecord(0)));
        
        for (int i = 0; i < 3; i++){
            ASSERT_TRUE(manager1.select(i) == DronesManager::DroneRecord(i));
        }
        
        return true;
    }
    
    // PURPOSE: lots of inserts and deletes, some of them invalid
    bool test9() {
        return false;
    }
    
    // PURPOSE: insert into an unsorted list, then sort the list
    bool test10() {
        return false;
    }
    
    // PURPOSE: insert and remove into sorted manager in ascending order
    bool test11() {
        return false;
    }
    
    // PURPOSE: insert and remove into sorted manager in descending order
    bool test12() {
        return false;
    }
};


#endif
