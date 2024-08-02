#include <unordered_map>
#include <list>

class LRUCache {
private:
    int capacity;
    std::list<std::pair<int, int>> cache;  
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> map;  

    void moveToFront(int key, int value) {
        cache.erase(map[key]);
        cache.push_front({key, value});
        map[key] = cache.begin();
    }

public:
    LRUCache(int capacity) : capacity(capacity) {}
    
    int get(int key) {
        if (map.find(key) == map.end()) {
            return -1; 
        }
        
        int value = map[key]->second;
        moveToFront(key, value);
        return value;
    }
    
    void put(int key, int value) {
        if (map.find(key) != map.end()) {
            moveToFront(key, value);
        } else {
            if (cache.size() == capacity) {
                int leastUsedKey = cache.back().first;
                map.erase(leastUsedKey);
                cache.pop_back();
            }
            
            cache.push_front({key, value});
            map[key] = cache.begin();
        }
    }
};