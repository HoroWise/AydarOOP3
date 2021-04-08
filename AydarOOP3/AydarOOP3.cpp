#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Human {
protected:
	string name;
	int age;
	int weight;

public:
	Human() {
		name = "RandomName";
		age = 0;
		weight = 0;
	}

	Human(string name, int age, int weight) {
		this->name = name;
		this->age = age;
		this->weight = weight;
	}

	Human(const Human& h) {
		name = h.name;
		age = h.age;
		weight = h.weight;
	}

	virtual void about_me() {
		printf("Меня зовут %s,мне %d лет и я вешу %d кг.\n", name.c_str(), age, weight);
	}

	~Human() { }
};

int main()
{
    
}
