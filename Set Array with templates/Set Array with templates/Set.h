#ifndef SET_H
#define SET_H
#include "Array.h"
#include<initializer_list>

template<typename T>
class Set
{
private:
	Array<T> data;
	int noOfElements;
public:
	bool operator!=(const Set & s2)const
	{
		int i = 0;
		if (s2.noOfElements != noOfElements)
		{
			return true;
		}
		while (i < noOfElements)
		{
			if ((searchElementPosition(s2.data[i]))==-1)
			{
				return true;
			}
			i++;
		}
		return false;
	}

	int searchElementPosition(T element)const
	{
		int i = 0;
		while (i < noOfElements && data[i] != element)
		{
			i = i + 1;
		}
		if (i == noOfElements)
		{
			return -1;
		}
		else
		{
			return i;
		}
	}
	int getCommonElements(const Set & b)const
	{
		int count = 0;
		for (int i = 0; i < noOfElements; i = i + 1)
		{
			if (b.isMember(data[i]))
			{
				count = count + 1;
			}
		}
		return count;
	}
	void assignToArray(int*b, int size, unsigned int binary)const
	{
		for (int i = size - 1; i >= 0; i = i - 1)
		{
			int digit = binary % 10;
			binary = binary / 10;
			b[i] = digit;
		}
	}
	long long convertToBinary(long long num)const
	{
		long long decimal = num;
		long long convert = 0;
		long long i = 1;
		while (decimal > 0)
		{
			convert = convert + (decimal % 2) * i;
			decimal = decimal / 2;
			i = i * 10;
		}
		return convert;
	}
public:
	Set(int capacity=10)
	{
		data.reSize(capacity);
		noOfElements = 0;
	}

	Set(initializer_list<T> list):Set(0)
	{
		//cout<<typeid(this).name()<<"\n";
		for (auto i : list)
		{
			insert(i);
		}
	}

	void insert(T element)
	{
		if (!isMember(element))
		{
			if (noOfElements == data.getCapacity())
			{
				reSize(noOfElements + 2);
			}
			data[noOfElements] = element;
			noOfElements = noOfElements + 1;
		}
	}
	void remove(T element)
	{
		int i = searchElementPosition(element);
		if (i != -1)
		{
			data[i] = data[noOfElements - 1];
			noOfElements = noOfElements - 1;
		}
	}
	void print()const
	{
		cout << ' ';
		for (int i = 0; i < noOfElements; i = i + 1)
		{
			cout << data[i] << " ";
		}
		cout << '\n';
	}
	int getCardinality()const
	{
		return noOfElements;
	}
	bool isMember(T val)const
	{
		int i = 0;
		while (i < noOfElements && data[i] != val)
		{
			i = i + 1;
		}
		if (i == noOfElements)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	int isSubset(Set s2)const
	{
		int count = 0;
		for (int i = 0; i < noOfElements; i = i + 1)
		{
			if (s2.isMember(data[i]))
			{
				count = count + 1;
			}
		}
		if (count == noOfElements)
		{
			if (count == s2.noOfElements)
			{
				if (count == noOfElements)
				{
					return 2;
				}
				return -1;
			}
			else
			{
				return 1;
			}
		}
		else
		{
			return 0;
		}
	}
	void reSize(int newCapacity)
	{
		data.reSize(newCapacity);
		if (newCapacity < noOfElements)
		{
			noOfElements = newCapacity;
		}
	}
	Set calcUnion(const Set & s2)const
	{
		Set res(noOfElements + s2.noOfElements - getCommonElements(s2));
		for (int i = 0; i < noOfElements; i = i + 1)
		{
			res.data[i] = data[i];
		}
		res.noOfElements = noOfElements;
		for (int i = 0; i < s2.noOfElements; i = i + 1)
		{
			res.insert(s2.data[i]);
		}
		return res;
	}
	Set calcIntersection(const Set & s2)const
	{
		Set res(getCommonElements(s2));
		for (int i = 0; i < noOfElements; i = i + 1)
		{
			if (s2.isMember(data[i]))
			{
				res.data[res.noOfElements] = data[i];
				res.noOfElements = res.noOfElements + 1;
			}
		}
		return res;
	}
	Set calcDifference(const Set & s2)const
	{
		Set diff(noOfElements - getCommonElements(s2));
		for (int i = 0; i < noOfElements; i = i + 1)
		{
			if (!s2.isMember(data[i]))
			{
				diff.data.getSet(diff.noOfElements) = data[i];
				diff.noOfElements = diff.noOfElements + 1;
			}
		}
		return diff;
	}
	Set calcSymmetricDifference(const Set & s2)const
	{
		Set a(calcDifference(s2));
		Set b(s2.calcDifference(*this));
		Set SDifference(a.calcUnion(b));
		return SDifference;
	}
	void displayPowerSet()const
	{
		int*b = new int[noOfElements];
		for (int i = 0; i < noOfElements; i = i + 1)
		{
			b[i] = 0;
		}

		int powerSetSize = pow(2, noOfElements);
		cout << '{';
		for (int i = 0; i < powerSetSize; i = i + 1)
		{
			unsigned int binary = convertToBinary(i);
			assignToArray(b, noOfElements, binary);
			cout << '{';
			for (int j = 0; j < noOfElements; j = j + 1)
			{
				if (b[j] == 1)
				{
					cout << data[j];
					if (j + 1 != noOfElements)
					{
						cout << ',';
					}
				}
			}
			cout << '}';
			if (i + 1 != powerSetSize)
			{
				cout << ',';
			}
		}
		cout << '}';
	}
	T& operator[](int index)
	{
		if (index >= 0 && index < noOfElements)
		{
			return data[index];
		}
		exit(0);
	}
	template<typename T>
	friend ostream& operator<<(ostream&o, const Set<T>& s);
};

template<typename T>
ostream& operator<<(ostream&o, const Set<T>& s)
{
	s.print();
	return o;
}

#endif 
