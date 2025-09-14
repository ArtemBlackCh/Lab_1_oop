#include <iostream>
#include <string>
using namespace std;

class DynamicArray
{
private:
	
	string name;
	int size;
	int* array;

	static int count;

public:

	DynamicArray();

	explicit DynamicArray(int size);

	DynamicArray(string name, int size);

	DynamicArray(DynamicArray& other);

	DynamicArray(const DynamicArray& other);

	~DynamicArray();

	string getName() { return name; };
	int getSize() { return size; };

	void setSize(int size);
	void setName(string name);

	static int get_count() { return count; };

	int& operator[] (int index);

	const int& operator[] (int index) const;

	DynamicArray& operator= (const DynamicArray& copyArray);

	friend DynamicArray operator* (const DynamicArray& firstArray, const DynamicArray& secondArray);

	friend bool operator>(const DynamicArray& firstArray, const DynamicArray& secondArray);
	friend bool operator>(const int& num, const DynamicArray& secondArray);
	friend bool operator>(const DynamicArray& firstArray, const int& num);

	friend ostream& operator<< (ostream& out, const DynamicArray outArray);
	friend istream& operator>> (istream& out, DynamicArray& inputArray);

	DynamicArray& operator--();
	DynamicArray operator--(int i);
	
	DynamicArray next();
};

int DynamicArray::count = 0;

ostream& operator<< (ostream& out, DynamicArray outArray)
{
	out << "name: " << outArray.name << " size: " << outArray.size << " array: ";

	for (int i = 0; i < outArray.size; i++)
	{
		cout << outArray[i] << ' ';
	}

	return out;
}

istream& operator>> (istream& in, DynamicArray& inArray)
{
	in >> inArray.name;
	in >> inArray.size;

	if (inArray.array)
	{
		delete[] inArray.array;
	}

	if (inArray.size < 0)
	{
		inArray.size = 0;
	}

	inArray.array = new int[inArray.size];

	if (inArray.size > 0)
	{
		for (int i = 0; i < inArray.size; i++)
		{
			in >> inArray.array[i];
		}
	}

	return in;
}

void DynamicArray::setSize(int size)
{
	if (this->size != size)
	{ 
		if (array)
		{
			int* newArray = new int[size];

			if (size == 0)
			{
				newArray = nullptr;
			}
			else if (this->size > size)
			{
				for (int i = 0; i < size; i++)
				{
					newArray[i] = array[i];
				}
			}
			else
			{
				for (int i = 0; i < this->size; i++)
				{
					newArray[i] = array[i];
				}

				for (int i = this->size; i < size; i++)
				{
					newArray[i] = 0;
				}
			}

			this->size = size;
			delete[] array;
			this->array = newArray;
		}
		else
		{
			this->size = size;
			array = new int[size];
		
			for (int i = 0; i < size; i++)
			{
				array[i] = 0;
			}
		}
	}
}

void DynamicArray::setName(string name)
{ 
	this->name = name;
}

int& DynamicArray::operator[](int index)
{
	if (index < size && index >= 0)
	{
		return array[index];
	}
	else
	{
		return array[0];
	}
}

const int& DynamicArray::operator[](int index) const
{
	if (index < size && index >= 0)
	{
		return array[index];
	}
	else
	{
		return array[0];
	}
}

DynamicArray& DynamicArray::operator=(const DynamicArray& copyArray)
{
	//name = "copyArray " + other.name;
	name = copyArray.name;

	size = copyArray.size;

	if (array)
	{
		delete[] array;
	}

	if (size == 0)
	{
		array = nullptr;
	}
	else
	{
		array = new int[size];

		for (int i = 0; i < size; i++)
		{
			array[i] = copyArray[i];
		}
	}

	return *this;
}

DynamicArray operator*(const DynamicArray& firstArray, const DynamicArray& secondArray)
{
	if (firstArray.size != 0 && secondArray.size != 0)
	{ 
		DynamicArray result("nameless", firstArray.size);

		int element;
		int index = 0;
		bool flag;
	
		for (int i = 0; i < firstArray.size; i++)
		{
			element = firstArray.array[i];
			flag = true;

			for (int j = 0; j < secondArray.size && flag; j++)
			{
				if (element == secondArray[j])
				{
					result[index] = element;
					index++;
					flag = false;
				}
			}
		}

		int resultSize = index;

		result.setSize(resultSize);

		return result;
	}
	else
	{
		DynamicArray result;  

		return result;
	}
}

bool operator>(const DynamicArray& firstArray, const DynamicArray& secondArray)
{
	bool result;

	if (firstArray.size == secondArray.size && firstArray.size != 0)
	{
		result = true;
		
		for (int i = 0; i < firstArray.size && result; i++)
		{
			if (firstArray[i] < secondArray[i])
			{
				result = false;
			}
		}
	}
	else
	{
		result = false;
	}

	return result;
}

bool operator>(const int& num, const DynamicArray& secondArray)
{
	bool result = true;

	for (int i = 0; i < secondArray.size && result; i++)
	{
		if (num < secondArray[i])
		{
			result = false;
		}
	}

	return result;
}

bool operator>(const DynamicArray& firstArray, const int& num)
{
	bool result = true;

	for (int i = 0; i < firstArray.size && result; i++)
	{
		if (firstArray[i] < num)
		{
			result = false;
		}
	}

	return result;
}

DynamicArray& DynamicArray::operator--()
{
	if (this->array)
	{
		for (int i = 0; i < this->size; i++)
		{
			this->array[i]--;
		}
	}

	return *this;
}

DynamicArray DynamicArray::operator--(int i)
{
	DynamicArray temp = *this;

	--*this;

	return temp;
}

DynamicArray::DynamicArray()
{
	this->size = 0;
	this->name = "nameless";
	count++;

	cout << "a constructor with no parameters was used" << endl;
}

DynamicArray::DynamicArray(int size)
{
	this->name = "nameless";
	count++;
	
	if (size > 0)
	{
		this->array = new int[size];
		this->size = size;

		for (int i = 0; i < size; i++)
		{
			array[i] = 0;
		}
	}
	else
	{
		this->array = nullptr;
		this->size = 0;
	}

	cout << "a explicit constructor with one parameter was used" << endl;
}

DynamicArray::DynamicArray(string name, int size)
{
	this->name = name;
	count++;

	if (size > 0)
	{
		this->array = new int[size];
		this->size = size;

		for (int i = 0; i < size; i++)
		{
			array[i] = 0;
		}
	}
	else
	{
		this->array = nullptr;
		this->size = 0;
	}

	cout << "a constructor with parameters was used" << endl;
}

DynamicArray::DynamicArray(DynamicArray& other)
{
	//name = "copy " + other.name;
	name = other.name;

	size = other.size;
	count++;

	if (size == 0)
	{
		array = nullptr;
	}
	else
	{
		array = new int[size];

		for (int i = 0; i < size; i++)
		{
			array[i] = other[i];
		}
	}

	cout << "a copy constructor was used" << endl;
}

DynamicArray::DynamicArray(const DynamicArray& other)
{
	//name = "copy " + other.name;
	name = other.name;

	size = other.size;
	count++;

	if (size == 0)
	{
		array = nullptr;
	}
	else
	{
		array = new int[size];

		for (int i = 0; i < size; i++)
		{
			array[i] = other[i];
		}
	}

	cout << "a copy constructor was used" << endl;
}

DynamicArray::~DynamicArray()
{
	cout << "a destructor was used on " << this->name << endl;
	count--;

	if (array)
	{
		delete[] array;
	}
}

DynamicArray DynamicArray::next()
{
	if (this->size != 0)
	{
		for (int i = 0; i < this->size; i++)
		{
			this->array[i]++;
		}
	}
	
	return *this;
}

void F(void)
{
	cout << "count: " << DynamicArray::get_count() << endl;

	DynamicArray A("A", 4), B("B", 5);

	cout << " Enter array A size: " << A.getSize() << endl;
	for (int i = 0; i < A.getSize(); i++)
	{
		cin >> A[i];
	}

	cout << " Enter array B size: " << B.getSize() << endl;
	for (int i = 0; i < B.getSize(); i++)
	{
		cin >> B[i];
	}

	cout << "count: " << DynamicArray::get_count() << endl;

	DynamicArray C = A;
	C.setName("C");

	cout << "count: " << DynamicArray::get_count() << endl;

	DynamicArray D;

	cout << "count: " << DynamicArray::get_count() << endl;

	D = A * B;
	D.setName("D");

	cout << A << endl << B << endl << C << endl << D;
}

int main()
{
	F();
	cout << "count: " << DynamicArray::get_count() << endl;

	DynamicArray A("A", 5);
	A.next();
	cout << A;
}

