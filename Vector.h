#pragma once
#include <iostream>

using namespace std;

template <typename T>
class Vector
{
private:
	T* data;
	size_t size, capacity;

	void copy(const Vector& other)
	{
		this->capacity = other.capacity;

		this->data = new T[capacity];

		for (size_t i = 0; i < other.size; i++)
		{
			this->data[i] = other.data[i];
		}

		this->size = other.size;
	}

	void erase()
	{
		delete[] this->data;
	}

	void resize()
	{
		if (this->size >= this->capacity)
			this->capacity *= 2;

		T* bigger = new T[this->capacity];

		for (size_t i = 0; i < this->size; i++)
		{
			bigger[i] = this->data[i];
		}

		this->erase();
		this->data = bigger;
	}
public:
	Vector();
	Vector(const Vector& other);
	Vector& operator=(const Vector& other);
	~Vector();

	void push_back(const T& el);
	void pop_back();
	void push_front(const T& el);
	void pop_front();
	void push_at(const T& el, int position);
	void pop_at(size_t position);
	void pop_by_data(const T& el);
	bool contains(const T& el);

	size_t getSize() const;
	size_t getCapacity() const;
	bool isEmpty() const;
	void print() const;
	void clear();

	Vector<T> operator +(const Vector& other);
	Vector<T>& operator +=(const Vector& other);
	T& operator [](size_t i);
	const T& operator [] (size_t i) const;
	bool operator==(const Vector& other);
	bool operator!=(const Vector& other);
};

template <typename T>
Vector<T>::Vector()
{
	this->data = nullptr;
	this->size = 0;
	this->capacity = 8;
}

template <typename T>
Vector<T>::Vector(const Vector<T>& other)
{
	this->copy(other);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if (this != &other)
	{
		this->erase();
		this->copy(other);
	}

	return *this;
}

template <typename T>
Vector<T>::~Vector()
{
	this->erase();
}

template <typename T>
void Vector<T>::push_back(const T& el)
{
	if (size == capacity || this->data == nullptr) {
		resize();
	}

	this->data[size] = el;
	this->size++;
}

template <typename T>
void Vector<T>::pop_back()
{
	T* smaller = new T[this->capacity];

	for (size_t i = 0; i < this->size - 1; i++)
	{
		smaller[i] = this->data[i];
	}

	--this->size;
	this->erase();
	this->data = smaller;
}

template <typename T>
void Vector<T>::push_front(const T& el)
{
	this->resize();
	T* bigger = new T[this->size + 1];

	for (size_t i = 0; i < this->size; i++)
	{
		bigger[i + 1] = this->data[i];
	}

	++size;
	bigger[0] = el;
	this->erase();
	this->data = bigger;
}

template <typename T>
void Vector<T>::pop_front()
{
	T* smaller = new T[this->size + 1];

	for (size_t i = 0; i < this->size; i++)
	{
		smaller[i] = this->data[i + 1];
	}

	--this->size;
	this->erase();
	this->data = smaller;
}

template <typename T>
void Vector<T>::push_at(const T& el, int position)
{
	this->resize();

	if (this->size >= position)
	{
		for (size_t i = this->size; i >= position; i--)
		{
			this->data[i] = this->data[i - 1];
		}

		++this->size;
		this->data[position - 1] = el;
	}
	else
		cout << "Position greater than the SIZE!" << endl;
}

template <typename T>
void Vector<T>::pop_at(size_t position)
{
	for (size_t i = position - 1; i < this->size; i++)
	{
		this->data[i] = this->data[i + 1];
	}

	--this->size;
}

template <typename T>
void Vector<T>::pop_by_data(const T& el)
{
	for (int i = 0; i < this->size; i++)
	{
		if (this->data[i] == el)
			this->pop_at(i + 1);
	}
}

template<typename T>
bool Vector<T>::contains(const T& el)
{
	for (size_t i = 0; i < this->size; i++) {
		if (this->data[i] == el)
			return true;
	}

	return false;
}

template <typename T>
size_t Vector<T>::getSize() const
{
	return this->size;
}

template <typename T>
size_t Vector<T>::getCapacity() const
{
	return this->capacity;
}

template <typename T>
bool Vector<T>::isEmpty() const
{
	return this->size == 0;
}

template <typename T>
void Vector<T>::print() const
{
	for (size_t i = 0; i < this->size; i++)
	{
		std::cout << this->data[i] << " ";
	}

	cout << std::endl;
}

template<typename T>
void Vector<T>::clear()
{
	data = nullptr;
	size = 0;
	capacity = 0;
}

template <typename T>
Vector<T> Vector<T>::operator +(const Vector<T>& other)
{
	Vector<T> result;

	this->resize();
	result.data = new T[this->capacity + other.capacity];

	for (size_t i = 0; i < this->size; i++)
	{
		result[i] = this->data[i];
	}

	for (size_t i = 0; i < other.size; i++)
	{
		result[this->size + i] = other.data[i];
	}


	result.size = this->size + other.size;
	return result;
}

template <typename T>
Vector<T>& Vector<T>::operator +=(const Vector& other)
{
	this->resize();
	T* bigger = new T[this->capacity];

	for (size_t i = 0; i < this->size; i++)
	{
		bigger[i] = this->data[i];
	}

	for (size_t i = 0; i < other.size; i++)
	{
		bigger[this->size + i] = other.data[i];
	}

	this->erase();
	this->data = bigger;
	this->size = this->size + other.size;

	return *this;
}

template <typename T>
T& Vector<T>::operator [](size_t i)
{
	return data[i];
}

template <typename T>
const T& Vector<T>::operator[] (size_t i) const
{
	return data[i];
}

template <typename T>
bool Vector<T>::operator==(const Vector& other)
{
	if (this->size != other.size)
		return false;

	for (size_t i = 0; i < this->size; i++)
	{
		if (this->data[i] != other.data[i])
			return false;
	}

	return true;
}

template <typename T>
bool Vector<T>::operator!=(const Vector& other)
{
	return !(this == &other);
}

template <typename T>
ostream& operator<<(ostream& stream, Vector<T> v)
{
	for (size_t i = 0; i < v.getSize(); i++)
	{
		cout << v[i] << " ";
	}

	return stream;
}