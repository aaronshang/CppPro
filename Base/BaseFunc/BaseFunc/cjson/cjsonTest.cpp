#include "cjsonTest.h"
#include "cJSON.h"
#include <iostream>
using namespace std;


void testJson()
{
	cout << "king" << endl;

	cJSON *root = cJSON_CreateObject();
	//cJSON_AddItemToObject(root, "UTCTime", cJSON_CreateLongLong(12345));
	//cJSON_AddItemToObject(root, "UTCTime", cJSON_CreateLongLong(123456789012345678));
	cJSON_AddItemToObject(root, "UTCTime", cJSON_CreateNumber(12345));

	char *out = cJSON_Print(root);

	cJSON *parseRoot = cJSON_Parse(out);
	cJSON *time = cJSON_GetObjectItem(parseRoot, "UTCTime");
	long long num = time->valueLongLong;
	cJSON_Delete(root);
}