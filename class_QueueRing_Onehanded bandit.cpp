// class_QueueRing_Onehanded bandit.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
#include <conio.h>
/*
	Создать имитацию игры «однорукий бандит». Например, 
	при нажатии кнопки «Enter» происходит «вращение» 
	трех барабанов (естественно, количество шагов вращений 
	каждого из них выбирается случайно), на которых
	изображены разные значки; и если выпадает определенная 
	комбинация, то игрок получает какой-то выигрыш
	(использовать кольцевую очередь).
*/

class QueueRing		 // класс кольцевая очередь
{
	int* queue;		 // указатель на динамический массив - очерель
	int max_len;	 // максимальный размер очереди
	int current_len; // текущий размер очереди
public:
	QueueRing(int size);
	~QueueRing();
	void add_element(int el);  // метод добавления эл-та
	bool extract_element();	   // метод извлечения эл-та
	void clear_queue();        // метод очистки очереди
	bool is_empty();           // метод - проверка на пустоту очереди
	bool is_full();            // метод - проверка на заполнение очереди
	int get_count();           // метод - кол-во элементов в очереди
	void show();               // метод - демонстрация очереди
	void show_element();       // метод - демонстрация определенного эл-та
	int get_element();         // метод - возврат определенного эл-та
	void fill();               // метод - заполнение очереди
	void num_of_ring();        // метод - кол-во "шагов вращений"
};

void QueueRing::add_element(int elem)  // метод добавления эл-та
{
	if (!is_full())  // если очередь не полна
	{
		queue[current_len++] = elem;  // увеличиваем текущую очередь и 
	}								  // втсавляем новый элемент
}

void QueueRing::fill()  // метод - заполнение очереди
{
	for (int i = 0; i < 5; i++)   // цикл - 5 эл-тов в очереди
	{		
		add_element(rand() % 6);  // заполнить значениями от 0 до 5
	}
}

void QueueRing::show()  // метод - демонстрация очереди
{
	for (int i = 0; i < current_len; i++)  // цикл до текущей длины
	{
		std::cout << queue[i] << ' ';  // вывод эл-тов очереди на экран
	}
	std::cout << std::endl;
}

void QueueRing::show_element()  // метод - показ определенного эл-та
{	
	std::cout << queue[4] << std::endl;	// выбрала последний эл-т (5-ый)
}

int QueueRing::get_element()  // метод - возврат определенного эл-та
{
	return queue[4];  // возврат эл-та, показанного в ф-ии show_element()
}

QueueRing::~QueueRing()
{
	delete[] queue;
}

QueueRing::QueueRing(int size)  // конструктор
{
	max_len = size;            // получаем максимальный размер
	queue = new int[max_len];  // создаем массив - очередь
	current_len = 0;           // изначально очередь пуста
}

void QueueRing::clear_queue()  // метод очистки очереди
{
	current_len = 0;
}

bool QueueRing::is_empty()  // метод - проверка на пустоту очереди
{
	return current_len == 0;
}

bool QueueRing::is_full()  // метод - проверка на заполненность очереди
{
	return current_len == max_len;
}

int QueueRing::get_count()  // метод - кол-во элементов в очереди
{
	return current_len;     // кол-во элементов в очереди в данный момент
}

bool QueueRing::extract_element()  // метод - извлечение эл-та
{
	if (!is_empty())  // если очерель не пуста
	{
		int temp = queue[0];  // запоминаем 1ый элемент
		for (int i = 1; i < current_len; i++)  // цикл от 2го эл-та
		{
			queue[i - 1] = queue[i];  // сдвигаем все эл-ты 
		}
		queue[current_len - 1] = temp;  // эл-т, который запомнили ранее
		return 1;						//  вставить в конец очерели
	}								    
	else
	{
		return 0;
	}
}

void QueueRing::num_of_ring()  // метод - кол-во "шагов вращений"
{
	for (int i= 0; i < rand() % 5; i++)  // повторить от 0 до 5 раз
	{									 // извлечение элемента - это и 
		extract_element();				 // будет шагом нашего вращения
	}									 // барабана
}

int main()
{
	srand(time(0));

	QueueRing roll1(20);  // объект - барабан-очередь 1
	QueueRing roll2(20);  // объект - барабан-очередь 2
	QueueRing roll3(20);  // объект - барабан-очередь 3

	roll1.fill();  // заполнение очереди 1
	roll2.fill();  // заполнение очереди 2
	roll3.fill();  // заполнение очереди 3

	char c;  // символ для считывания с клавиатуры
	std::cout << "One-handed bandit\n"
		<< "Let's Play\n"
		<< "\nTo start - press 'enter'..."
		<< "\nTo exit - press '0'\n";
	
	c = _getch();  // считываем нажатую пользователем клавишу
	if (c == 13) {  // если enter
		do
		{
			system("cls");
			
			//roll1.show();  // для наглядности правильности работы
			roll1.num_of_ring();  // вращаем барабан1 rand-раз (0...5)
			//roll1.show();  // для наглядности правильности работы
			roll1.show_element();
			std::cout << std::endl;

			//roll2.show();  // для наглядности правильности работы
			roll2.num_of_ring();  // вращаем барабан2 rand-раз (0...5)
			//roll2.show();  // для наглядности правильности работы
			roll2.show_element();
			std::cout << std::endl;

			//roll3.show();  // для наглядности правильности работы
			roll3.num_of_ring();  // вращаем барабан3 rand-раз (0...5)
			//roll3.show();  // для наглядности правильности работы
			roll3.show_element();

			if (roll1.get_element() == roll2.get_element() &&  // если 
				roll2.get_element() == roll3.get_element())	   // эл-ты равны
			{
				std::cout << "\nYou are winner!!!";
				Sleep(1000);
			}
			else
			{
				std::cout << "\nOps... You are loser";
				Sleep(1000);
			}
			std::cout << "\n\nTo try again - press 'enter'..."
				<< "\nTo exit - press '0'";
			
			c = _getch();  // считываем нажатую пользователем клавишу
		} while (c != 27);  // если нажали esc - выход
	}
	return 0;
}
