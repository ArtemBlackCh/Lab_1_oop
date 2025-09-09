#include <iostream>
#include <string>
using namespace std;

class DynamicArray
{
private:
	
	string name;
	int size;
	int* arrey;

public:

	string getName() { return name; };
	int getSize() { return size; };

	void setSize(int size);
	void setName(string name);

	int& operator[] (int index);

	const int& operator[] (int index) const;

	DynamicArray& operator= (const DynamicArray& copyArrey);

	friend DynamicArray operator* (const DynamicArray& firstArrey, const DynamicArray& secondArrey);

	friend bool operator>(const DynamicArray& firstArrey, const DynamicArray& secondArrey);

	friend bool operator>(const int& num, const DynamicArray& secondArrey);

	friend bool operator>(const DynamicArray& firstArrey, const int& num);

	friend ostream& operator<< (ostream& out, const DynamicArray outArrey);

	friend istream& operator>> (istream& out, DynamicArray& inputArrey);

	DynamicArray& operator++();

	const DynamicArray& operator++(int i);
	
	DynamicArray();

	explicit DynamicArray(int size);

	DynamicArray(string name, int size);

	DynamicArray(DynamicArray& other);

	~DynamicArray();

	DynamicArray next();
};

ostream& operator<< (ostream& out, const DynamicArray outArrey)
{
	out << "name: " << outArrey.name << " size: " << outArrey.size << " arrey: ";

	for (int i = 0; i < outArrey.size; i++)
	{
		cout << outArrey[i] << ' ';
	}

	return out;
}

istream& operator>> (istream& in, DynamicArray& inArrey)
{
	in >> inArrey.name;
	in >> inArrey.size;

	if (inArrey.arrey)
	{
		delete[] inArrey.arrey;
	}

	if (inArrey.size < 0)
	{
		inArrey.size = 0;
	}

	inArrey.arrey = new int[inArrey.size];

	if (inArrey.size > 0)
	{
		for (int i = 0; i < inArrey.size; i++)
		{
			in >> inArrey.arrey[i];
		}
	}

	return in;
}

void DynamicArray::setSize(int size)
{
	if (this->size != size)
	{ 
		if (arrey)
		{
			int* newArrey = new int[size];

			if (size == 0)
			{
				newArrey = nullptr;
			}
			else if (this->size > size)
			{
				for (int i = 0; i < size; i++)
				{
					newArrey[i] = arrey[i];
				}
			}
			else
			{
				for (int i = 0; i < this->size; i++)
				{
					newArrey[i] = arrey[i];
				}

				for (int i = this->size; i < size; i++)
				{
					newArrey[i] = 0;
				}
			}

			this->size = size;
			delete[] arrey;
			this->arrey = newArrey;
		}
		else
		{
			this->size = size;
			arrey = new int[size];
		
			for (int i = 0; i < size; i++)
			{
				arrey[i] = 0;
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
		return arrey[index];
	}
	else
	{
		return arrey[0];
	}
}

const int& DynamicArray::operator[](int index) const
{
	if (index < size && index >= 0)
	{
		return arrey[index];
	}
	else
	{
		return arrey[0];
	}
}

DynamicArray& DynamicArray::operator=(const DynamicArray& copyArrey)
{
	name = copyArrey.name;
	size = copyArrey.size;

	if (arrey)
	{
		delete[] arrey;
	}

	if (size == 0)
	{
		arrey = nullptr;
	}
	else
	{
		arrey = new int[size];

		for (int i = 0; i < size; i++)
		{
			arrey[i] = copyArrey[i];
		}
	}

	return *this;
}

DynamicArray operator*(const DynamicArray& firstArrey, const DynamicArray& secondArrey)
{
	if (firstArrey.size != 0 && secondArrey.size != 0)
	{ 
		DynamicArray result("nameless", firstArrey.size);

		int element;
		int index = 0;
		bool flag;
	
		for (int i = 0; i < firstArrey.size; i++)
		{
			element = firstArrey.arrey[i];
			flag = true;

			for (int j = 0; j < secondArrey.size && flag; j++)
			{
				if (element == secondArrey[j])
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

bool operator>(const DynamicArray& firstArrey, const DynamicArray& secondArrey)
{
	bool result;

	if (firstArrey.size == secondArrey.size && firstArrey.size != 0)
	{
		result = true;
		
		for (int i = 0; i < firstArrey.size && result; i++)
		{
			if (firstArrey[i] < secondArrey[i])
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

bool operator>(const int& num, const DynamicArray& secondArrey)
{
	bool result = true;

	for (int i = 0; i < secondArrey.size && result; i++)
	{
		if (num < secondArrey[i])
		{
			result = false;
		}
	}

	return result;
}

bool operator>(const DynamicArray& firstArrey, const int& num)
{
	bool result = true;

	for (int i = 0; i < firstArrey.size && result; i++)
	{
		if (firstArrey[i] < num)
		{
			result = false;
		}
	}

	return result;
}

DynamicArray::DynamicArray()
{
	this->size = 0;
	this->name = "nameless";

	cout << "a constructor with no parameters was used" << endl;
}

DynamicArray::DynamicArray(int size)
{
	this->name = "nameless";
	
	if (size > 0)
	{
		this->arrey = new int[size];
		this->size = size;

		for (int i = 0; i < size; i++)
		{
			arrey[i] = 0;
		}
	}
	else
	{
		this->arrey = nullptr;
		this->size = 0;
	}

	cout << "a explicit constructor with one parameter was used" << endl;
}

DynamicArray::DynamicArray(string name, int size)
{
	this->name = name;

	if (size > 0)
	{
		this->arrey = new int[size];
		this->size = size;

		for (int i = 0; i < size; i++)
		{
			arrey[i] = 0;
		}
	}
	else
	{
		this->arrey = nullptr;
		this->size = 0;
	}

	cout << "a constructor with parameters was used" << endl;
}

DynamicArray::DynamicArray(DynamicArray& other)
{
	name = other.name;
	size = other.size;

	if (size == 0)
	{
		arrey = nullptr;
	}
	else
	{
		arrey = new int[size];

		for (int i = 0; i < size; i++)
		{
			arrey[i] = other[i];
		}
	}

	cout << "a copy constructor was used" << endl;
}

DynamicArray::~DynamicArray()
{
	if (arrey)
	{
		delete[] arrey;
	}

	cout << "a destructor was used on " << endl;
}

DynamicArray DynamicArray::next()
{
	if (this->size != 0)
	{
		for (int i = 0; i < this->size; i++)
		{
			this->arrey[i]++;
		}
	}
	
	return *this;
}

void F(void)
{
	DynamicArray A, B;

	cout << " enter array A (name size and elements)\n";
	cin >> A;

	cout << " enter array B (name size and elements)\n";
	cin >> A;

	DynamicArray C = A;
	DynamicArray D;

	D = A * B;

	cout << A << endl << B << endl << C << endl << D;
}

int main()
{
	DynamicArray A("A", 5);

	cout << A << endl;
	
	A.next().next();

	cout << A << endl;
}

