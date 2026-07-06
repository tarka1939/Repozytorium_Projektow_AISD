#define TABLE_SIZE 10000
#define NULL nullptr
// Hash node class template
template <typename K, typename V>
class HashNode {
public:
    HashNode(const K& first, const V& second) :
        first(first), second(second), next(NULL) {
    }

    K getKey() const {
        return first;
    }

    V& getValue() {
        return second;
    }

    template <Ts ...args>
    void setValue(V second) {
        HashNode::second = second;
    }

    HashNode* getNext() const {
        return next;
    }

    void setNext(HashNode* next) {
        HashNode::next = next;
    }
    K first;
    V second;
private:
    HashNode* next;
};
// Default hash function class
template <typename K>
struct KeyHash {
    unsigned long operator()(const K& key) const
    {
        return key % TABLE_SIZE;
    }
};

// Hash map class template
template <typename K, typename V, typename F = KeyHash<K>>
class unordered_map {
    struct myiterator;
public:
    unordered_map() {
        // construct zero initialized hash table of size
        table = new HashNode<K, V>*[TABLE_SIZE];
    }

    ~unordered_map() {
        if (borrowed) return;
        // destroy all buckets one by one
        for (int i = 0; i < TABLE_SIZE; ++i) {
            HashNode<K, V>* entry = table[i];
            while (entry != NULL) {
                HashNode<K, V>* prev = entry;
                entry = entry->getNext();
                delete prev;
            }
            table[i] = NULL;
        }
        // destroy the hash table
        delete[] table;
    }
    unordered_map(const unordered_map& other) = delete;
    unordered_map& operator=(const unordered_map& other) = delete;

    V& operator[](const K& key) {
		unsigned long hashValue = hashFunc(key);
		HashNode<K, V>* entry = table[hashValue];
        while (entry != NULL) {
            if (entry->getKey() == key) {
				return entry->getValue();
			}
			entry = entry->getNext();
		}
		entry = new HashNode<K, V>(key, V());
		return entry->getValue();
	}

    bool get(const K& key, V& value) {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V>* entry = table[hashValue];

        while (entry != NULL) {
            if (entry->getKey() == key) {
                value = entry->getValue();
                return true;
            }
            entry = entry->getNext();
        }
        return false;
    }

    template <typename ...Ts>
    void put(const K& key, Ts ...args) {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V>* prev = NULL;
        HashNode<K, V>* entry = table[hashValue];

        while (entry != NULL && entry->getKey() != key) {
            prev = entry;
            entry = entry->getNext();
        }

        if (entry == NULL) {
            entry = new HashNode<K, V>(key, new V(...args));
            if (prev == NULL) {
                // insert as first bucket
                table[hashValue] = entry;
            }
            else {
                prev->setNext(entry);
            }
        }
        else {
            // just update the value
            entry->setValue(...args);
        }
    }

    bool containsKey(const K& key) {
		unsigned long hashValue = hashFunc(key);
		HashNode<K, V>* entry = table[hashValue];
        while (entry != NULL) {
            if (entry->getKey() == key) {
				return true;
			}
			entry = entry->getNext();
		}
		return false;
	}

    void remove(const K& key) {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V>* prev = NULL;
        HashNode<K, V>* entry = table[hashValue];

        while (entry != NULL && entry->getKey() != key) {
            prev = entry;
            entry = entry->getNext();
        }

        if (entry == NULL) {
            // key not found
            return;
        }
        else {
            if (prev == NULL) {
                // remove first bucket of the list
                table[hashValue] = entry->getNext();
            }
            else {
                prev->setNext(entry->getNext());
            }
            delete entry;
        }
    }
    myiterator begin() {
		return myiterator(0, table[0],this);
	}
    myiterator end() {
		return myiterator(TABLE_SIZE, NULL,this);
	}
private:
    bool borrowed = false;
    HashNode<K, V>** table;
    struct myiterator {
        int index;
        unordered_map<K, V, F>* map;
        HashNode<K, V>* node;
        myiterator(int index, HashNode<K, V>* node, unordered_map<K,V,F>* map) : index(index), node(node), map(map) {}
        myiterator& operator++() {
            if (node->getNext() != NULL) {
                node = node->getNext();
            }
            else {
                while (node->getNext() == NULL) {
                    index++;
                    node = map->table[index];
                }
            }
            return *this;
        }
        bool operator!=(const myiterator& other) {
            return node != other.node;
        }
        HashNode<K, V>& operator*() {
            return *node;
        }
    };
    // hash table
   
    F hashFunc;
};