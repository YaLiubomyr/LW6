#include <iostream>
#include <string>
#include <sstream>
#include "Map.h"

using namespace std;

string enterValue(string str)
{
	string value_string;

	cout << "Enter " + str + ": ";
	cin >> value_string;
	if (value_string == "exit")
	{
		return "exit";
	}
	return value_string;
}

void checkMainValue(string str, string* value)
{
	do {
		*value = enterValue(str);
		if (*value != "exit")
			break;
		else
			cout << "Enter " + str + "!" << endl;
	} while (true);
}

bool isInteger(const string& str)
{
	try {
		stoi(str);
		return true;
	}
	catch (const exception& e)
	{
		return false;
	}
}

bool isFloat(const string& str)
{
	try {
		stof(str);
		return true;
	}
	catch (const exception& e)
	{
		return false;
	}
}

string getVariableType(const string& str)
{
	if (isFloat(str)) {
		return "float";
	}
	else if (isInteger(str)) {
		return "int";
	}
	else {
		return "string";
	}
}

template<typename ValueType>
string enterFewValues(string str, string type)
{
	do {
		string temp = enterValue(str);
		if (temp == "exit")
			return "exit";
		else if (getVariableType(temp) != type)
		{
			cout << "Print values the same type!" << endl;
			continue;
		}
		else
			return temp;
	} while (true);
}

template<typename ValueType>
void checkType(ValueType* value, string type, string str)
{
	istringstream iss(str);
	iss >> *value;
}

template<typename ValueType>
void getInsertValue(string str, ValueType* value, string valueType)
{
	string string_value;
	do
	{
		cout << "Enter " + str + ": ";
		cin >> string_value;
		if (getVariableType(string_value) == valueType)
		{
			checkType(&(*value), valueType, string_value);
			break;
		}
		else
			cout << "Print values the same type!" << endl;
	} while (true);
}

template<typename KeyType, typename DataType>
void commandFunc(KeyType key, DataType data, string keyType, string dataType)
{
	AssociativeArray<KeyType, DataType> obj;
	obj.insert(key, data);

	do {
		string string_key = enterFewValues<KeyType>("key", keyType);
		if (string_key == "exit")
			break;
		checkType(&key, keyType, string_key);
		string string_data = enterFewValues<DataType>("data", dataType);
		if (string_data == "exit")
			break;
		checkType(&data, dataType, string_data);
		obj.insert(key, data);
	} while (true);

	string command;

	cout << endl << "Command list: " << endl;
	cout << "empty - checks if the associated array is empty" << endl;
	cout << "clear - clears the associated array" << endl;
	cout << "min - print pair with min value of key in associated array" << endl;
	cout << "remove [key] - remove pair with key value \"key\"" << endl;
	cout << "add - adds pair to associated array" << endl;
	cout << "print - prints all pairs of associated array" << endl;
	cout << "end - end the program" << endl;

	do {
		cout << endl << "Command: ";
		cin >> command;
		if (command == "empty") {
			if (obj.isEmpty())
				cout << "Array is empty." << endl;
			else
			{
				cout << "Array is not empty:" << endl;
				obj.printall();
			}
		}
		else if (command == "clear") {
			obj.clear();
		}
		else if (command == "min") {
			cout << "Min key: \"" << obj.findMinKey()->key << "\" and its data: \"" << obj.findMinKey()->data << "\"" << endl;
		}
		else if (command == "remove") {
			string string_key;
			do
			{
				cin >> string_key;
				if (getVariableType(string_key) == keyType)
				{
					checkType(&key, keyType, string_key);
					break;
				}
				else
				{
					cout << "Print key the same type!" << endl;
					cout << "Enter key: ";
				}
			} while (true);
			obj.removeAt(key);
		}
		else if (command == "add") {
			getInsertValue("key", &key, keyType);
			getInsertValue("data", &data, dataType);
			obj.insert(key, data);
		}
		else if (command == "print") {
			if (obj.isEmpty())
				cout << "Array is empty!" << endl;
			else
				obj.printall();
		}
		else if (command != "end")
			cout << "Incorrect input!" << endl;
	} while (command != "end");
}

void defineArrayType(string key, string keyType, string data, string dataType)
{
	if (keyType == "int" && dataType == "int")
	{
		commandFunc(stoi(key), stoi(data), keyType, dataType);
	}
	else if (keyType == "int" && dataType == "float")
	{
		commandFunc(stoi(key), stof(data), keyType, dataType);
	}
	else if (keyType == "int" && dataType == "string")
	{
		commandFunc(stoi(key), data, keyType, dataType);
	}
	else if (keyType == "float" && dataType == "int")
	{
		commandFunc(stof(key), stoi(data), keyType, dataType);
	}
	else if (keyType == "float" && dataType == "float")
	{
		commandFunc(stof(key), stof(data), keyType, dataType);
	}
	else if (keyType == "float" && dataType == "string")
	{
		commandFunc(stof(key), data, keyType, dataType);
	}
	else if (keyType == "string" && dataType == "int")
	{
		commandFunc(key, stoi(data), keyType, dataType);
	}
	else if (keyType == "string" && dataType == "float")
	{
		commandFunc(key, stof(data), keyType, dataType);
	}
	else if (keyType == "string" && dataType == "string")
	{
		commandFunc(key, data, keyType, dataType);
	}
}