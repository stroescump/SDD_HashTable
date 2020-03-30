#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Floare
{

	char* nume;
	float pret;
};

struct Nod
{
	Floare info;
	Nod* next;
};

struct HashTable {
	Nod** vector;
	int dim;
};

Floare initFloare(const char* nume, float pret) {
	Floare f;
	f.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(f.nume, nume);
	f.pret = pret;
	return f;
}

void afisareFloare(Floare f) {
	printf("Floarea %s costa %5.2f\n", f.nume, f.pret);
}

void inserareSfarsitInListaSimpla(Nod*& cap, Floare f) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = f;
	nou->next = NULL;
	if (cap) {
		Nod* temp = cap;
		while (cap->next) {
			temp = temp->next;
		}
		temp->next = nou;
	}
	else {
		cap = nou;
	}
}

HashTable initHashTable(int dim) {
	HashTable h;
	h.dim = dim;
	h.vector = (Nod**)malloc(sizeof(Nod*) * h.dim);
	for (int i = 0; i < h.dim; i++) {
		h.vector[i] = NULL;
	}
	return h;
}

int calculeazaHash(const char* nume, int dim) {
	int lungimeNume = strlen(nume);
	lungimeNume *= 11;
	return lungimeNume % dim;
}

void inserareInHashTable(HashTable& tabela, Floare f) {
	if (tabela.dim > 0) {
		int codHash = calculeazaHash(f.nume, tabela.dim);
		//if (tabela.vector[codHash]) { // Verificam daca avem coliziune, exista deja un ob. pe ac. poz.
		//	inserareSfarsitInListaSimpla(tabela.vector[codHash], f);
		//}
		//else {
		//	inserareSfarsitInListaSimpla(tabela.vector[codHash], f);
		//}
		inserareSfarsitInListaSimpla(tabela.vector[codHash], f);
	}
	else {
		throw "Tabela neinitalizata";
	}
}

void afisareListaSimpla(Nod* capLista) {
	while (capLista) {
		afisareFloare(capLista->info);
		capLista = capLista->next;
	}
}

void afisareFloriDinHashTable(HashTable h) {
	for (int i = 0; i < h.dim; i++) {
		afisareListaSimpla(h.vector[i]);
		printf("\n");
	}
}

float cautarePretDupaNumeFloare(HashTable h, const char* nume) {
	int codHash = calculeazaHash(nume, h.dim);
	if (codHash >= 0 && codHash < h.dim) {
		if (h.vector[codHash]) {
			Nod* aux = h.vector[codHash];
			while (aux) {
				if (strcmp(aux->info.nume, nume) == 0) {
					return aux->info.pret;
				}
				aux = aux->next;
			}
			throw "Floarea nu exista";
		}
		else throw "Nu exista elemente la pozitia aceasta";
	}
	else throw "Codul nu exista in tabela";
}


void main() {
	HashTable h = initHashTable(5);
	Floare f1 = initFloare("Lalea", 12);
	Floare f2 = initFloare("Margareta", 7);
	Floare f3 = initFloare("Zambila", 8);
	Floare f4 = initFloare("Trandafir", 10);

	inserareInHashTable(h, f1);
	inserareInHashTable(h, f2);
	inserareInHashTable(h, f3);
	inserareInHashTable(h, f4);

	afisareFloriDinHashTable(h);
	printf("Pretul unei flori este de %5.2f", cautarePretDupaNumeFloare(h, "Trandafir"));
}