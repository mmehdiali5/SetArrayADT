#include<iostream>
using namespace std;
#ifndef ARRAY_H
#define ARRAY_H
#include<initializer_list>

template<typename T>
class Array
{
private:
	T * data;
	int capacity = 0;
	int isValidIndex(int index)const
	{
		return index >= 0 && index < capacity;
	}
public:
	Array&operator =(const Array& ref);
	T& operator[](int index);
	Array();

	Array(initializer_list<T>list)
	{
		capacity = list.size();
		if (capacity == 0)
		{
			data = 0;
			return;
		}
		data = new T[capacity];
		int j = 0;
		for (auto i : list)
		{
			data[j] = i;
			j++;
		}
	}

	~Array()
	{
		//cout << "\n~Array()";
		if (data != nullptr)
		{
			delete[]data;
		}
		data = nullptr;
		capacity = 0;
	}
	Array(const Array & ref)
	{
		if (ref.data == nullptr)
		{
			data = nullptr;
			capacity = 0;
			return;
		}
		capacity = ref.capacity;
		data = new T[capacity];
		//memcpy(data, ref.data, capacity * sizeof(T));
		for (int i = 0; i < capacity; i++)
		{
			data[i] = ref.data[i];
	    }
	}
	const T&  operator[](int index)const
	{
		if (isValidIndex(index))
		{
			return data[index];
		}
		exit(0);
	}

	int getCapacity()const
	{
		return capacity;
	}
	void reSize(int newCap)
	{
		if (newCap < 0)
		{
			this->~Array();
			return;
		}
		if (capacity == 0)
		{
			T * ptr = new T[newCap];
			this->~Array();
			capacity = newCap;
			data = ptr;
			return;
		}
		T * ptr = new T[newCap];
		//memcpy(ptr, data, (newCap < capacity ? newCap : capacity) * sizeof(T));
		for (int i = 0; i < (newCap < capacity ? newCap : capacity); i++)
		{
			ptr[i] = data[i];
		}
		this->~Array();
		capacity = newCap;
		data = ptr;
	}
};

template<typename T>
Array<T>::Array()
{
	data = 0;
	capacity = 0;
}

template<typename G>
Array<G>& Array<G>:: operator =(const Array & ref)
{
	if (this == &ref)
	{
		return *this;
	}
	this->~Array();
	if (ref.data == nullptr)
	{
		data = nullptr;
		capacity = 0;
		return *this;
	}
	capacity = ref.capacity;
	data = new G[capacity];
	//memcpy(data, ref.data, capacity * sizeof(G));
	for (int i = 0; i < capacity; i = i + 1)
	{
		data[i] = ref.data[i];
    }
}

template<typename T>
T& Array<T>::operator[](int index)
{
	if (isValidIndex(index))
	{
		return data[index];
	}
	exit(0);
}

//specialization examples
//template<>
//int Array<int>::getCapacity()const
//{
//	return capacity;
//}
//
//template<>
//class Array<float>
//{
//public:
//	void f()
//	{
//		cout << "hello";
//	}
//};

#endif 


