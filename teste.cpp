#include <thread>
#include <mutex>
#include <iostream>
#include <vector>

using namespace std;

mutex mtx;

vector<int>* arrayTeste = new vector<int>;
auto tamanhoArray = 5;
int tamanhoAtual;

void printArrayTeste() {
	for (auto value : *arrayTeste) {
		cout << value << " ";
	}

	for (tamanhoAtual = arrayTeste->size(); tamanhoAtual < tamanhoArray; tamanhoAtual++)
	{
		cout << "0 ";
	}
	cout << " " << endl;
}

void produtor()
{
	int i = 0;
	int item;
	bool aguardar;
	aguardar = false;

	while (true)
	{
		if (aguardar != true) {
			mtx.lock();
			aguardar = true;
		}

		if (arrayTeste->size() == tamanhoArray)
		{
			mtx.unlock();
			aguardar = false;
		}
		else
		{
			auto numeroBuffer = 1;
			arrayTeste->push_back(numeroBuffer);
			this_thread::sleep_for(chrono::seconds(2));
		}
		printArrayTeste();
	}
}

void consumidor()
{
	int item;
	bool aguardar;
	aguardar = false;

	while (true)
	{
		if (aguardar != true)
		{
			mtx.lock();
			aguardar = true;
		}
		if (arrayTeste->size() == 0)
		{
			mtx.unlock();
			aguardar = false;
		}
		else {
			arrayTeste->pop_back();
			this_thread::sleep_for(chrono::seconds(2));
		}
		printArrayTeste();
	}
}

int main()
{
	std::thread prod1(produtor);
	std::thread cons1(consumidor);

	prod1.join();
	cons1.join();

	return 0;
}

