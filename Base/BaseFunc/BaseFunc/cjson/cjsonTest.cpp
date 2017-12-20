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

string GetJsonTransGPS(string gpsJson)
{
	string rvt = "";
	cJSON * pJsonRoot = NULL;
	pJsonRoot = cJSON_CreateObject();
	if (NULL == pJsonRoot)
	{
		return rvt;
	}
	cJSON_AddStringToObject(pJsonRoot, "UB_CMD", "Transmit");
	cJSON_AddStringToObject(pJsonRoot, "CMD", "TransGPS");

	cJSON * pSubJson = NULL;
	pSubJson = cJSON_CreateObject();
	if (NULL == pSubJson)
	{
		cJSON_Delete(pJsonRoot);
		return rvt;
	}
	cJSON_AddNumberToObject(pSubJson, "From", 0);
	cJSON_AddNumberToObject(pSubJson, "To", 100);
	cJSON_AddStringToObject(pSubJson, "Msg", gpsJson.c_str());
	cJSON_AddItemToObject(pJsonRoot, "Param", pSubJson);

	char *str = cJSON_Print(pJsonRoot);
	rvt = str;
	cJSON_Delete(pJsonRoot);

	return rvt;
}