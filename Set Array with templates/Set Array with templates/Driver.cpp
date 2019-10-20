#include<iostream>
using namespace std;
#include"Set.h"
#include<initializer_list>

int main()
{
	
	//Set<int>a = { 1,2,3 };
	Set<Set<int>> s1 =  { {},{ 1 }, { 2 }, { 1,2 }};
	Set<Set<int>>s2 = { { 4 }, { 5 }, { 6,7 } };
	cout << s1.calcUnion(s2);
	cout << "\n\n\n\n\n\n\n";
	/*Set<Set<Set<int>>> b;
	b.reSize(3);
	b.insert({});
	b.insert({ 2 });
	b.insert({ 3 });
	for (int i = 0; i < 3; i = i + 1)
	{
		for (int j = 0; j < 2; j = j + 1)
		{
			b[i].insert(i + j);
		}
	}
	for (int i = 0; i < 3; i = i + 1)
	{
	     b[i].print();
	}*/
	
	return 0;
}