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

class Fishman :public Human {
protected:
	int fish_amount;

public:
	Fishman() {
		fish_amount = 10;
	}

	Fishman(int fish_amount) {
		this->fish_amount = fish_amount;
	}

	Fishman(const Fishman& f) {
		fish_amount = f.fish_amount;
	}

	virtual void about_me() {
		printf("Меня зовут %s, мой сегодняшний улов составил %d рыб\n", name.c_str(), fish_amount);
	}

	~Fishman() { }
};

class Farmer :public Human {
protected:
	int hens_amount;

public:
	Farmer() {
		hens_amount = 20;
	}

	Farmer(int hens_amount) {
		this->hens_amount = hens_amount;
	}

	Farmer(const Farmer& f) {
		hens_amount = f.hens_amount;
	}

	virtual void about_me() {
		printf("Меня зовут %s, в моем хозяйстве находится %d кур\n", name.c_str(), hens_amount);
	}

	~Farmer() { }
};

int main()
{
	setlocale(0, "");
	//Storage storage;
	srand(time(0));
	string text = " ";
	int n = 100; // Кол-во операций
	int count = 10; // Кол-во элементов

again:
	cout << "Напишите сколько случайных операций выполнить : ";
	cin >> n;
	unsigned int start_time = clock();
	for (int i = 0; i < n; ++i) {
		int act = rand() % count; // Выбираем с каким объектом взаимодействуем
		int vibor = 1 + rand() % 3; // Выбираем какое действие произойдёт с выбранным объектом
		int k = 1 + rand() % 2; // Выбираем подкласс
		printf("%d)", i + 1);
		//switch (vibor) {}
	}
}
