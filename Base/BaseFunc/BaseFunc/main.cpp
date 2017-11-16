#include <iostream>
#include "Base01/Number.h"
#include <vector>

using namespace std;

//For example, given array S = [-1, 0, 1, 2, -1, -4],
class Solution {
public:

	bool IsHaveThirdNum(int num1, int num2, vector<int> vec){
	
		bool ret = false;

		int num = -(num2 + num1);
		bool filter = true;
		for (int i = 0; i < vec.size();i++)
		{
			if (num == vec[i])
			{
				if ((num == num1 || num == num2) && filter)
				{
					continue;
					filter = false;
				}
				ret = true;
				break;
			}
		}

		return ret;
	}

	int maxValue(vector<int> vec){
		
		int maxV = vec[0];
		for (int i = 0; i < vec.size();i++)
		{
			if (vec[i]>=maxV)
			{
				maxV = vec[i];
			}
		}
		return maxV;
	}

	int minValue(vector<int> vec){

		int minV = vec[0];
		for (int i = 0; i < vec.size(); i++)
		{
			if (vec[i]<= minV)
			{
				minV = vec[i];
			}
		}
		return minV;
	}



	bool IsSame(vector<int> v1, vector<int> v2){
		
		if (maxValue(v1)== maxValue(v2) && minValue(v1)==minValue(v2))
		{
			return true;
		}
		return false;
	}

	bool IsRepeat(vector<vector<int>> ary, vector<int> vec){
		
		bool ret = false;
		for (int i = 0; i < ary.size();i++)
		{
			if (IsSame(ary[i], vec))
			{
				ret = true;
				break;
			}
		}
		return ret;
	}

	vector<vector<int>> threeSum(vector<int>& nums) {

		vector<vector<int>> retVec;

		vector<int> vec;
		for (int i = 0; i < nums.size(); i++)
		{
			vec.clear();
			vec.push_back(nums[i]);
			for (int j = i + 1; j < nums.size(); j++)
			{
				if (IsHaveThirdNum(nums[i], nums[j], nums))
				{
					int third = -(nums[i] + nums[j]);
					vec.push_back(nums[j]);
					vec.push_back(third);
					if (IsRepeat(retVec, vec) == false)
					{
						retVec.push_back(vec);

						//����Ѱ��
						vec.clear();
						vec.push_back(nums[i]);
					}
					break;
				}
			}
		}
		return retVec;
	}


	vector<vector<int>> threeSum2(vector<int>& nums) {

		vector<int> t(3);
		vector< vector<int> > triplets;
		int n = nums.size();
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				for (int k = j + 1; k < n; k++) {
					if (nums[i] + nums[j] + nums[k] == 0) {
						t[0] = nums[i];
						t[1] = nums[j];
						t[2] = nums[k];
						triplets.push_back(t);
					}
				}
			}
		}
		return triplets;

	}
};

int ReplaceString(string &str, const string &oldSubStr, const string newSubStr, int AllReplace)
{
	int ReplaceItems = 0;
	const size_t nsize = newSubStr.size();
	const size_t psize = oldSubStr.size();

	for (std::string::size_type pos = str.find(oldSubStr, 0);
		pos != std::string::npos;
		pos = str.find(oldSubStr, pos + nsize))
	{
		str.replace(pos, psize, newSubStr);
		ReplaceItems++;

		if (!AllReplace)
			break;
	}

	return ReplaceItems;
}


int main(){

	cout << "hello" << endl;

	string oldstr = "^CELLSIG:\r\nRSRP: -116.000000\r\nRSRQ : -7.000000\r\nRSSI : -106.000000\r\nSINR : -1.000000\r\nOK";
	cout << oldstr.c_str() << endl;

	ReplaceString(oldstr, "^CELLSIG:", "", 1);
	ReplaceString(oldstr, " ", "", 1);
	ReplaceString(oldstr, "\r\n", " ", 1);
	ReplaceString(oldstr, "00000", "", 1);
	ReplaceString(oldstr, "OK", "", 1);
	cout << oldstr.c_str() << endl;

	//CNumber *number = new CNumber();
	//number->test();
	//delete number;

	//vector<int> numVec;
	//numVec.push_back(-1);
	//numVec.push_back(0);
	//numVec.push_back(1);
	//numVec.push_back(2);
	//numVec.push_back(-1);
	//numVec.push_back(-4);

	//Solution *ss = new Solution();
	//ss->threeSum2(numVec);

	//string dstr = "a";
	//dstr += '\r';
	//dstr += '\n';
	//cout << "length" << dstr.length() << endl;

	return 0;

}