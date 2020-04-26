#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int produtos[10];
int tamanho = 10;
int quantidadeProdutos = 0;
mutex mtx;

void print(string acao) {
	
	cout << acao << ": [";

	for (int i = 0; i < tamanho; i++) {
		if (produtos[i] == 0) {
			cout << "_";

		} else {
			cout << produtos[i];
		}


		if (i != tamanho - 1) {
			cout << ", ";
		}
	}

	cout << "]" << endl;
}

void Produtor() {
	mtx.lock();
	bool aux = false;

	while (true) {
		if (aux) {
			mtx.lock();
			aux = false;
		}

		if (quantidadeProdutos != 10) {
			produtos[quantidadeProdutos] = rand() % 100 + 1;
			quantidadeProdutos++;

			print("Produzindo");
		} else {
			mtx.unlock();
			aux = true;
		}

		this_thread::sleep_for(chrono::seconds(1));
	}
}

void Consumidor() {
	mtx.lock();
	bool aux = false;

	while (true) {
		if (aux) {
			mtx.lock();
			aux = false;
		}

		if (quantidadeProdutos > 0) {
			quantidadeProdutos--;
			produtos[quantidadeProdutos] = 0;

			print("Consumindo");
		} else {
			mtx.unlock();
			aux = true;
		}

		this_thread::sleep_for(chrono::seconds(1));
	}
}

int main() {
	srand(time(NULL));

	thread threadProdutor(Produtor);
	thread threadConsumidro(Consumidor);

	threadProdutor.join();
	threadConsumidro.join();

	return 0;
}