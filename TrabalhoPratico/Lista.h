#pragma once
#include <iostream>
#include <string>
#include "Tree.h"

using namespace std;

class ItemDL {
public:
	Tree *data;
	ItemDL *next;
	ItemDL *previous;
};


class LinkedDupleList {
public:
	ItemDL *head;
	ItemDL *tail;
	LinkedDupleList() {
		head = NULL;
		tail = NULL;
	}
	~LinkedDupleList() {
		ItemDL *aux = head;
		while (aux != NULL) {
			head = head->next;
			delete aux->data;
			delete aux;
			aux = head;
		}
		tail = NULL;
	};

	bool isEmpty() {
		return head == NULL || tail == NULL;
	}

	ItemDL* addOrdered(char ch, int ocorrencia) {
		ItemDL *novo = new ItemDL();
		novo->data = new Tree();
		novo->data->add(ch, ocorrencia);
		novo->next = NULL;
		novo->previous = NULL;
		if (head == NULL) {
			head = novo;
			tail = novo;
		}
		else {
			if (ocorrencia < head->data->root->ocorrencia ||
				(ocorrencia == head->data->root->ocorrencia && ch <= head->data->root->ch)) {
				head->previous = novo;
				novo->next = head;
				head = novo;
			}
			else if (ocorrencia > tail->data->root->ocorrencia || (ocorrencia == tail->data->root->ocorrencia && ch > tail->data->root->ch)) {
				novo->previous = tail;
				tail->next = novo;
				tail = novo;
			}
			else {
				ItemDL*aux = head;
				while (aux->data->root->ocorrencia < ocorrencia ||
					(aux->data->root->ocorrencia == ocorrencia &&aux->data->root->ch< ch))
					aux = aux->next;
				novo->next = aux;
				novo->previous = aux->previous;
				aux->previous->next = novo;
				aux->previous = novo;
			}

		}
		return novo;
	}
	Tree* RemoveFirst() {
		if (head == NULL)
			return NULL;
		else if (head == tail) {
			Tree *aux = head->data;
			delete head;
			head = tail = NULL;
			return aux;
		}
		else {
			Tree *aux = head->data;
			head = head->next;
			delete head->previous;
			head->previous = NULL;
			return aux;
		}

	}
	void mostra() {
		ItemDL *aux = head;
		while (aux != NULL)
		{
			aux->data->mostrar();
			aux = aux->next;
		}
	}

	void codifica() {
		ItemDL *aux = head;
		while (aux != NULL)
		{
			aux->data->codifica();
			aux = aux->next;
		}
	}
	void colocaBinario(string codigo) {
		ItemDL *aux = head;
		while (aux != NULL)
		{
			aux->data->at(codigo);
			aux = aux->next;
		}
	}

	void encodeLetrasOc() {
		ItemDL *aux = head;
		return aux->data->encodeLetrasOc();
		aux = aux->next;
	}

	string converteTexto(string letras) {
		ItemDL *aux = head;
		return aux->data->converteTexto(letras);
		cout << endl;
	}
};