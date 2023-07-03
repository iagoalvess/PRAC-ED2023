#ifndef CONJUNTO_DISJUNTO_HPP
#define CONJUNTO_DISJUNTO_HPP

class ConjuntoDisjunto {
private:
	int *pai;			// Array para armazenar o pai de cada elemento
	int *tamanho; // Array para armazenar o tamanho do conjunto raiz
	int contador; // Contagem total de conjuntos

public:
	ConjuntoDisjunto();
	~ConjuntoDisjunto();
	void makeSet(long elemento);
	void unionSet(long elementoA, long elementoB);
	long findSet(long elemento);
};

#endif