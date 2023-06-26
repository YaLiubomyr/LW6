#pragma once
#include <iostream>
#include <string>

using namespace std;

template<typename KeyType, typename DataType>
struct Node
{
	KeyType key;
	DataType data;
	Node<KeyType, DataType>* next;

	Node(KeyType key = KeyType(), DataType data = DataType(), Node* next = nullptr) : key(key), data(data), next(next) {}
};


template<typename KeyType, typename DataType>
class AssociativeArray
{
	int Size;
	Node<KeyType, DataType>* head;

public:
	class Iterator
	{
		Node<KeyType, DataType>* current;

	public:
		Iterator(Node<KeyType, DataType>* current) : current(current) {}
		Node<KeyType, DataType>* get() { return current; };
		void next() { current = current->next; };
		bool operator==(const Iterator& it) { return current == it.current; }
		bool operator!=(const Iterator& it) { return current != it.current; }
	};

	AssociativeArray() : Size(0), head(nullptr) {};
	~AssociativeArray();

	bool isEmpty();
	void clear();
	void insert(KeyType key, DataType data);
	Node<KeyType, DataType>* findMinKey();
	void removeAt(KeyType);
	Iterator begin() { return Iterator(head); };
	Iterator end() { return Iterator(nullptr); };
	void popFront();
	void printall();
	int getSize() { return Size; }
};


template<typename KeyType, typename DataType>
bool AssociativeArray<KeyType, DataType>::isEmpty()
{
	return (head == nullptr);
}

template<typename KeyType, typename DataType>
inline void AssociativeArray<KeyType, DataType>::clear()
{
	while (head != nullptr)
	{
		Node<KeyType, DataType>* temp = head;
		head = head->next;
		delete temp;
	}
	Size = 0;
}

template<typename KeyType, typename DataType>
void AssociativeArray<KeyType, DataType>::insert(KeyType key, DataType data)
{
	if (head == nullptr)
	{
		head = new Node<KeyType, DataType>(key, data);
	}
	else
	{
		Iterator it = begin();
		while (it != end())
		{
			if (it.get()->key == key)
			{
				it.get()->data = data;
				return;
			}
			else if (it.get()->next == nullptr)
			{
				it.get()->next = new Node<KeyType, DataType>(key, data);
				break;
			}
			it.next();
		}
	}

	Size++;
}

template<typename KeyType, typename DataType>
inline Node<KeyType, DataType>* AssociativeArray<KeyType, DataType>::findMinKey()
{
	if (head == nullptr) {
		return nullptr;
	}

	Node<KeyType, DataType>* min = head;
	Node<KeyType, DataType>* current = head->next;

	while (current != nullptr) {
		if (current->key < min->key) {
			min = current;
		}
		current = current->next;
	}

	return min;
}

template<typename KeyType, typename DataType>
inline void AssociativeArray<KeyType, DataType>::removeAt(KeyType key)
{
	if (head->key == key)
	{
		popFront();
	}
	else
	{
		//Node<KeyType, DataType>* previous = head;
		Iterator previous = begin();
		while (previous.get()->next != nullptr) {
			if (previous.get()->next->key == key) {
				break;
			}
			previous.next();
		}


		if (previous.get()->next != nullptr)
		{
			Node<KeyType, DataType>* to_delete = previous.get()->next;
			previous.get()->next = to_delete->next;
			delete to_delete;
			Size--;
		}
		else
		{
			cout << "Error. Can't find this key!" << endl;
		}
	}
}


template<typename KeyType, typename DataType>
inline void AssociativeArray<KeyType, DataType>::popFront()
{
	Node<KeyType, DataType>* temp = head;
	head = head->next;
	delete temp;
	Size--;
}

template<typename KeyType, typename DataType>
void AssociativeArray<KeyType, DataType>::printall()
{
	//Node<KeyType, DataType>* current = head;
	Iterator it = begin();
	while (it != end())
	{
		cout << "Key: " << it.get()->key << " - data: " << it.get()->data << endl;
		it.next();
	}
}


template<typename KeyType, typename DataType>
AssociativeArray<KeyType, DataType>::~AssociativeArray()
{
	Node<KeyType, DataType>* current = head;
	while (current != nullptr)
	{
		Node<KeyType, DataType>* next = current->next;
		delete current;
		current = next;
	}
}