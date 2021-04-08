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

class Storage {
protected:
	Human** objects;
public:
	Storage() { }

	Human* get(int index) {
		return objects[index];
	}

	void initialize(int count) {
		objects = new Human * [count];
		for (int i = 0; i < count; ++i)
			objects[i] = NULL;
	}

	void add_object(int index, Human* object) {
		objects[index] = object;
	}

	void delete_object(int index) {
		delete objects[index];
		objects[index] = NULL;
	}

	void method(int index) {
		objects[index]->about_me();
	}

	bool check_empty(int index) {
		if (objects[index] == NULL)
			return true;
		else return false;
	}

	void expose_all(int n) {
		for (int i = 0; i < n; ++i) {
			if (check_empty(i))
				printf("%d) Пустое место\n ", i);
			else
			{
				printf("%d) ", i);
				method(i);
			}
		}
	}

	int occupied(int size) {
		int count_occupied = 0;
		for (int i = 0; i < size; ++i)
			if (!check_empty(i))
				++count_occupied;
		return count_occupied;
	}

	void doubleSize(int& size) {
		Storage storage1;
		storage1.initialize(size * 2);
		for (int i = 0; i < size; ++i)
			storage1.objects[i] = objects[i];
		for (int i = size; i < (size * 2) - 1; ++i) {
			storage1.objects[i] = NULL;
		}
		size = size * 2;
		initialize(size);
		for (int i = 0; i < size; ++i)
			objects[i] = storage1.objects[i];
	}

	~Storage() {

	}
};

Human* random_object(int variant) {
	switch (variant) {
	case 1:
		return new Fishman;
	case 2:
		return new Farmer;
	}
}

int main()
{
	setlocale(0, "");
	Storage storage;
	srand(time(0));
	string text = " ";
	int n = 100; // Кол-во операций
	int count = 10; // Кол-во элементов
	storage.initialize(count);

start:
	cout << "Напишите сколько случайных операций выполнить : ";
	cin >> n;
	unsigned int start_time = clock();
	for (int i = 0; i < n; ++i) {
		int act = rand() % count; // Выбираем с каким объектом взаимодействуем
		int vibor = 1 + rand() % 3; // Выбираем какое действие произойдёт с выбранным объектом
		int k = 1 + rand() % 2; // Выбираем подкласс
		printf("%d)", i + 1);
		switch (vibor) {
		case 1:
		add:
			if (storage.check_empty(act)) { // Если место свободно, то добавляем объект
				if (k == 1) {
					text = "Fishman";
				}
				else text = "Farmer";
				printf("  Добавили в %i место хранилища объект класса %s\n", act, text.c_str());
				storage.add_object(act, random_object(k));
			}
			else
			{
				if (storage.occupied(count) == count)
				{
					printf("Хранилище полностью заполнено, увеличиваем кол-во элементов в хранилище в 2 раза\n");
					storage.doubleSize(count);
				}
				printf("  %i место хранилища занято, ищем свободное место в хранилище\n", act);
				while (storage.get(act) != NULL)
					act = (act + 1) % count;
				goto add;
			}
			break;
		case 2:
			if (!storage.check_empty(act)) { // Если место занято, то удаляем объект
				printf("  Освободили %i место хранилища\n", act);
				storage.delete_object(act);
			}
			else printf("  %i место хранилища пустое, освободить место в хранилище невозможно\n", act);
			break;
		case 3:
			if (!storage.check_empty(act)) { // Если место занято, то вызываем метод у объекта
				printf("  Запуск метода about_me() у %i объекта из хранилища\n", act);
				storage.method(act);
			}
			else printf("  %i место хранилища пустое, вызвать метод невозможно\n", act);
			break;
		}
	}

	unsigned int end_time = clock();
	unsigned int search_time = end_time - start_time;
	cout << "\n" << "Время работы = " << search_time / 1000.0 << "сек" << endl;
	cout << "Общее кол-во занятых ячеек хранилища = " << storage.occupied(count) << endl;
	cout << "\n" << "Вы хотите посмотреть всё хранилище? 1 - Да, 2 - Нет : ";
	int a;
	cin >> a;
	if (a == 1) {
		storage.expose_all(count);
	}	cout << "Вы хотите продолжить тестировать хранилище? 1 - Да, 2 - Нет : ";
	int b;
	cin >> b;
	if (b == 1) {
		goto start;
	}
}
