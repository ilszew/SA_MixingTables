#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream>

template <typename T>
class ArrayList {
protected:
	T* dane;
	int maxroz;
	int roz;

	void zmroz() {
		int newMaxroz = (maxroz == 0) ? 1 : maxroz * 2;
		T* nDane = new T[newMaxroz];

		for (int i = 0; i < roz; i++) {
			nDane[i] = dane[i];
		}


			delete[] dane;


		dane = nDane;
		maxroz = newMaxroz;
	}

public:
	ArrayList() : dane(nullptr), maxroz(0), roz(0) {}

	ArrayList(const ArrayList& other) : dane(nullptr), maxroz(0), roz(0) {
		if (other.roz > 0) {
			maxroz = other.maxroz;
			roz = other.roz;
			dane = new T[maxroz];
			for (int i = 0; i < roz; i++) {
				dane[i] = other.dane[i];
			}
		}
	}

	ArrayList& operator=(const ArrayList& other) {
		if (this != &other) {
			if (dane != nullptr) {
				delete[] dane;
				dane = nullptr;
			}

			maxroz = other.maxroz;
			roz = other.roz;

			if (other.roz > 0) {
				dane = new T[maxroz];
				for (int i = 0; i < roz; i++) {
					dane[i] = other.dane[i];
				}
			}
		}
		return *this;
	}

	~ArrayList() {

			delete[] dane;

	}

	void DodajP(T element) {
		if (roz == maxroz) {
			zmroz();
		}
		for (int i = roz; i > 0; i--) {
			dane[i] = dane[i - 1];
		}
		dane[0] = element;
		roz++;
	}

	void UsunP() {
		if (roz > 0) {
			for (int i = 0; i < roz - 1; i++) {
				dane[i] = dane[i + 1];
			}
			roz--;
		}
		else {
			throw std::out_of_range("Tablica jest pusta");
		}
	}

	void DodajK(T element) {
		if (roz == maxroz) {
			zmroz();
		}
		dane[roz++] = element;
	}

	void UsunK() {
		if (roz > 0) {
			roz--;
		}
		else {
			throw std::out_of_range("Tablica jest pusta");
		}
	}

	void DodajLos(int miejsce, T element) {
		if (roz == maxroz) {
			zmroz();
		}
		if (miejsce < 0 || miejsce > roz) {
			throw std::out_of_range("Indeks poza zakresem");
		}
		for (int i = roz; i > miejsce; i--) {
			dane[i] = dane[i - 1];
		}
		dane[miejsce] = element;
		roz++;
	}

	void UsunLos(int miejsce) {
		if (miejsce < 0 || miejsce >= roz) {
			throw std::out_of_range("Indeks poza zakresem");
		}
		for (int i = miejsce; i < roz - 1; i++) {
			dane[i] = dane[i + 1];
		}
		roz--;
	}

	bool Szukaj(T element) {
		for (int i = 0; i < roz; i++) {
			if (dane[i] == element) {
				return true;
			}
		}
		return false;
	}

	int wielkosc() const {
		return roz;
	}

	int wielkosc() {
		return roz;
	}

	void wyswietl() {
		for (int i = 0; i < roz; i++) {
			std::cout << dane[i] << " ";
		}
		std::cout << std::endl;
	}

	T& operator[](int index) {
		if (index < 0 || index >= roz) {
			throw std::out_of_range("Indeks poza zakresem");
		}
		return dane[index];
	}

	const T& operator[](int index) const {
		if (index < 0 || index >= roz) {
			throw std::out_of_range("Indeks poza zakresem");
		}
		return dane[index];
	}
};

#endif //ARRAYLIST_H