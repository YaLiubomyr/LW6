#include <iostream>
#include "Map.h"
#include "funcs.h"
#include <string>

using namespace std;

int main()
{
	cout << "Enter keys and data for associated array [for exit print \"exit\"]:\n\n";

	string key;
	checkMainValue("key", &key);
	string keyType = getVariableType(key);

	string data;
	checkMainValue("data", &data);
	string dataType = getVariableType(data);

	defineArrayType(key, keyType, data, dataType);

	return 0;
}