// C++ program for the above approach
#include <bits/stdc++.h>
using namespace std;

typedef struct {
	int key;
	int value;
} HashNode;

const int capacity = 20;
int size = 0;
HashNode** arr;
HashNode* dummy;

void insert(int key, int V) { // Function to add key value pair

	HashNode* temp = (HashNode*) malloc(sizeof(HashNode));
	temp->key = key;
	temp->value = V;

	// Apply hash function to find
	// index for given key
	int hashIndex = key % capacity;

	// Find next free space
	while (arr[hashIndex] != NULL && arr[hashIndex]->key != key && arr[hashIndex]->key != -1) {
		hashIndex++;
		hashIndex %= capacity;
	}

	// If new node to be inserted
	// increase the current size
	if (arr[hashIndex] == NULL || arr[hashIndex]->key == -1) size++;

	arr[hashIndex] = temp;
}

int deleteKey(int key) { // Function to delete a key value pair
	// Apply hash function to find
	// index for given key
	int hashIndex = key % capacity;

	// Finding the node with given
	// key
	while (arr[hashIndex] != NULL) {
		// if node found
		if (arr[hashIndex]->key == key) {
			// Insert dummy node here
			// for further use
			arr[hashIndex] = dummy;

			// Reduce size
			size--;

			// Return the value of the key
			return 1;
		}
		hashIndex++;
		hashIndex %= capacity;
	}

	// If not found return null
	return 0;
}

int find(int key) {// Function to search the value for a given key
	// Apply hash function to find
	// index for given key
	int hashIndex = (key % capacity);

	// Find the node with given key
	while (arr[hashIndex] != NULL) {

		int counter = 0;
		// If counter is greater than
		// capacity
		if (counter++ > capacity)
			break;

		// If node found return its
		// value
		if (arr[hashIndex]->key == key)
			return arr[hashIndex]->value;

		hashIndex++;
		hashIndex %= capacity;
	}

	// If not found return
	// -1
	return -1;
}

int main() {
	arr = (HashNode**) malloc(sizeof(HashNode*) * capacity);
	// Assign NULL initially
	for (int i = 0; i < capacity; i++) {
		arr[i] = NULL;
    }

	dummy = (HashNode*)malloc(sizeof(HashNode));
	dummy->key = -1;
	dummy->value = -1;

	insert(1, 5);
	insert(2, 15);
	insert(3, 20);
	insert(4, 7);

	if (find(4) != -1) cout << "Value of Key 4 = " << find(4) << endl;
	else cout << "Key 4 does not exists" << endl;

	if (deleteKey(4)) cout << "Node value of key 4 is deleted successfully" << endl;
	else cout << "Key does not exists" << endl;

	if (find(4) != -1) cout << "Value of Key 4 = " << find(4) << endl;
	else cout << "Key 4 does not exists" << endl;
}