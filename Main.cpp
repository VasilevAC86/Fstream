# include <iostream>
#include<fstream>
#include<string>

// Функция вывода файла в консоль
void print_file(std::string path) {
	static std::ifstream in;
	in.open(path);
	std::cout << "------------------------\n";
	if (in.is_open()) {
		char sym;
		while (in.get(sym))
			std::cout << sym;
		in.close();
	}
	std::cout << "\n------------------------\n";
}

bool into_file(std::string path, std::string str, int pos) {
	static std::fstream out;
	out.open(path, std::ios::in);	
	if (!out.is_open())
		return false;	
	std::string file;
	std::string tmp;
	while (std::getline(out, tmp))
		file += tmp + '\n';
	out.close();	
	out.open(path, std::ios::out);
	if (!out.is_open())
		return false;
	for (size_t i = 0; i < file .length(); ++i) { // size_t - это unsugned long long
		if (i == pos)
			out << str;
		out << file[i];
	}	
	out.close();
	return true;		
}

int main() {
	setlocale(LC_ALL, "Russian");
	int n;
	std::string path = "file.txt";

	// Класс fstream
	std::fstream fs;
	fs.open(path, std::ios::app | std::ios::in);	
	if (fs.is_open()) {
		std::cout << "Файл открыт.\n";
		// Запись данных в файл
		std::cout << "Введите строку -> ";
		std::string msg;
		std::getline(std::cin, msg);
		fs << msg << '\n';
		fs.seekg(0, std::ios::beg); // Смещение в начало файла
		// Чтение данных из файла
		std::cout << "Содержимое файла:\n----------------------------------------\n";
		char sym;
		while (fs.get(sym))
			std::cout << sym;
		std::cout << "\n----------------------------------------\n";
		fs.close();
	}
	else
		std::cout << "Ошибка открытия файла.\n";

	// Задание "Запись в середину файла"
	std::cout << "Задача \n\n";
	std::cout << "Изначальный файл:\n";
	print_file(path);
	std::cout << "Введите строку -> ";
	std::string str;
	std::getline(std::cin, str);
	std::cout << "Введите позицию -> ";
	std::cin >> n;	
	if (into_file(path, str, n)) {
		std::cout << "Запись вставлена в итоговый файл:\n";
		print_file(path);
		std::cout << std::endl;
	}
	else
		std::cout << "Ошибка!\n\n";

	// Задача 1. Считывание даты из файла
	std::cout << "Задача 1.\nСодержимое файла:\n";
	const char date_path[] = "date.txt";
	print_file(date_path);
	std::ifstream in;
	in.open(date_path);
	if (in.is_open()) {
		std::string date;
		in >> date;
		in.close();
		
		int m_index = date.find('.') + 1;
		int y_index = date.rfind('.') + 1;

		int day = std::stoi(date); // stoy доходит до первой точки и выводит число до точки
		int mouth = std::stoi(date.substr(m_index));
		int year = std::stoi(date.substr(y_index));
		std::cout << "День: " << day << std::endl;
		std::cout << "Месяц: " << mouth << std::endl;
		std::cout << "Год: " << year << std::endl;
	}

	return 0;
}