#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

struct Student {
	char prizv[100];
	unsigned int mark_1;
	unsigned int mark_2;
	unsigned int mark_3;
};

void tryInput(const char message[], unsigned int& mark) {
	bool fail;
	do {
		fail = false;
		cout << message; cin >> mark;
		if (cin.fail()) {
			fail = true;
			cout << "Неправильний ввід\n";
			cin.clear();
			cin.ignore(65536, '\n');
		}
	} while (fail);
}

void addStudent(string filename) {
	ofstream file(filename, ios::binary | ios::app);

	Student student;
	cout << "Введіть прізвище: "; cin >> student.prizv; 
	tryInput("Введіть оцінку 1: ", student.mark_1);
	tryInput("Введіть оцінку 2: ", student.mark_2);
	tryInput("Введіть оцінку 3: ", student.mark_3);

	file.write((char*) &student, sizeof(Student));
	file.close();
}

int calc_n(int n) {
	int res = 0;
	while (n != 0) {
		n /= 10;
		res++;
	}
	return res;
}

int max_len(string t) {
	ifstream file(t, ios::binary);
	size_t res = 0;
	Student student;

	while (file.read((char*)&student, sizeof(Student))) {
		if (res < strlen(student.prizv)) {
			res = strlen(student.prizv);
		}
	}

	file.close();

	return res;
}

int amount_of_students(string t) {
	ifstream file(t, ios::binary);
	int counter = 0;
	Student student;

	while (file.read((char*)&student, sizeof(Student))) {
		counter++;
	}
	
	file.close();

	return counter;
}

void printStudents(string t) {
	ifstream file(t, ios::binary);

	if (!file) {
		cout << "Файл пустий" << endl;
		file.close();
		return;
	}

	size_t width = max_len(t);
	int maxDigits = calc_n(amount_of_students(t));
	width < 8 ? (width = 8) : (NULL);

	for (int i = 0; i < (maxDigits - 1) + (width - 8) + 45; i++) {
		cout << "=";
	}
	cout << endl;

	cout << "|" << setw(maxDigits) << right << "№";
	cout << "|" << setw(width) << left << "Прізвище" << "| Оцінка 1 | Оцінка 2 | Оцінка 3 |" << endl;

	for (int i = 0; i < (maxDigits - 1) + (width - 8) + 45; i++) {
		cout << "-";
	}
	cout << endl;

	int i = 0;
	Student student;
	while (file.read((char*)&student, sizeof(Student))) {
		cout << "|" << setw(maxDigits) << right << i + 1;
		cout << "|" << setw(width) << left << student.prizv;
		cout << "|" << setw(10) << left << student.mark_1;
		cout << "|" << setw(10) << left << student.mark_2;
		cout << "|" << setw(10) << left << student.mark_3 << "|" << endl;
		i++;
	}

	for (int i = 0; i < (maxDigits - 1) + (width - 8) + 45; i++) {
		cout << "-";
	}
	cout << endl;
	file.close();
}

void menu(string t) {
	int option;
	while (true) {
	
		cout << "Меню:\n[1] Додати студента\n[2] Вивести список студентів\n[3] Вихід\n : ";
		cin >> option;

		switch (option){
			case 1:
				addStudent(t);
				break;

			case 2:
				printStudents(t);
				break;

			case 3:
				return;

			default:
				cout << "Неправильний ввід!" << endl;
				break;
		}
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string t;
	cout << "Введіть ім'я файлу: "; cin >> t;

	menu(t);
}
