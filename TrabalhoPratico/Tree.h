#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <bitset>

using namespace std;

string binario, binChOcorrencia;
int nZeros = 0;

class Nodo
{
public:
	char ch;
	int ocorrencia;
	string codigo;
	Nodo *left;
	Nodo *right;
};

class Tree
{
public:
	Nodo *root;
	Tree()
	{
		root = NULL;
	}

	~Tree()
	{
		_Tree(root);
		root = NULL;
	}

	bool isEmpty()
	{
		return root == NULL;
	}

	/**
	* Fun��o respons�vel por adicionar
	* caracteres e ocorr�ncias na �rvore
	*
	* @param ch - caracter a ser adicionado
	* @param ocorrencia - ocorr�ncia a ser adicionada
	*/
	void add(char ch, int ocorrencia)
	{
		Nodo * novo = new Nodo();
		novo->ch = ch;
		novo->ocorrencia = ocorrencia;
		novo->codigo = "";
		novo->left = NULL;
		novo->right = NULL;
		root = novo;
	}

	/**
	* Fun��o respons�vel por verificar se n� � folha
	*
	* @param actual - N� actual
	* @return bool  - retorna true se for folha
	*/
	bool isLeaf(Nodo* actual) {
		if (actual->right == NULL && actual->left == NULL) {
			return true;
		}
		else {
			return false;
		}
	}

	void codifica()
	{
		codifica(root, "");
	}

	void mostrar()
	{
		mostrar(root, 0);
	}

	void colocaBinario(char value) {
		colocaBinario(root, value);
	}

	void encodeLetrasOc() {
		encodeLetrasOc(root);
	}

	/**
	* Fun��o respons�vel por separar a string 
	* em caracteres e enviar para a fun��o colocaBinario
	*
	* @param  value - string a ser processada
	*/
	void at(string value) {
		for (unsigned i = 0; i < value.length(); ++i) {
			char x = value.at(i);
			colocaBinario(x);
		}
	}

	/**
	* Fun��o respons�vel por 
	*
	* @param  bin - valor binario
	* @return string - 
	*/
	string converteTexto(string bin) //teste
	{
		string caracteres = "", valor = "";
		for (int i = 0; i < bin.length() - nZeros; i++) {
			valor += bin[i];

			char aux = encontraBin(valor);
			if (aux != '\0') {
				valor = "";
				caracteres += aux;
			}
		}
		return caracteres;
	}

private:
	void _Tree(Nodo *actual)
	{
		if (actual != NULL)
		{
			_Tree(actual->left);
			_Tree(actual->right);
			delete actual;
		}
	}

	/**
	* Fun��o respons�vel por percorrer e mostrar a �rvore
	*
	* @param actual - No actual
	* @param nivel  - Nivel na arvore
	*/
	void mostrar(Nodo *actual, int nivel) {
		if (actual != NULL) {
			mostrar(actual->right, nivel + 1);
			for (int i = 0; i < nivel; i++)
				cout << "  ";
			if (!isLeaf(actual)) {
				cout << "*";
			}
			if (actual->ch == '\n') {
				cout << "<" << char(217) << ":" << actual->ocorrencia << " " << actual->codigo << endl;
			}
			else if (actual->ch == ' ') {
				cout << char(95) << ":" << actual->ocorrencia << " " << actual->codigo << endl;
			}
			else {
				cout << actual->ch << ":" << actual->ocorrencia << " " << actual->codigo << endl;
			}
			mostrar(actual->left, nivel + 1);
		}
	}

	/**
	* Fun��o respons�vel por percorrer e codificar a �rvore
	* adicionando '1' aos n�s da direita e '0' aos da esquerda
	*
	* @param actual - No actual
	* @param bin    - valor binario
	*/
	void codifica(Nodo *actual, string bin) {
		if (actual != NULL) {
			codifica(actual->right, bin + "1");
			if (isLeaf(actual)) {
				actual->codigo = bin;
			}
			codifica(actual->left, bin + "0");
		}
	}

	/**
	* Fun��o respons�vel por receber um caracter e
	* colocar o seu valor bin�rio na vari�vel global
	*
	* @param actual - N� actual
	* @param value  - Caracter
	*/
	void colocaBinario(Nodo *actual, char value) {
		if (actual != NULL) {
			colocaBinario(actual->right, value);

			if (isLeaf(actual)) {
				if (actual->ch == value) {
					binario += actual->codigo;
				}
			}
			colocaBinario(actual->left, value);
		}
	}

	string chToBin(char x) {
		string binary = bitset<8>(x).to_string();
		return binary;
	}
	unsigned long binToCh(string x) {
		unsigned long decimal = bitset<8>(x).to_ulong();
		return decimal;
	}

	/**
	* Fun��o respons�vel por guardar o binario das
	* letras e numero de correncias na var global
	*
	* @param  actual - n� actual
	*/
	void encodeLetrasOc(Nodo* actual) { //encodeBin
		if (actual != NULL) {
			encodeLetrasOc(actual->left);
			if (isLeaf(actual)) {
				binChOcorrencia += chToBin(actual->ch) + chToBin(actual->ocorrencia);
			}
			encodeLetrasOc(actual->right);
		}
	}

	/**
	* Fun��o respons�vel por retornar o caracter 
	* presente na �rvore correspondente ao binario
	* introduzido
	*
	* @param  valor - binario a procurar
	* @return char - valor encontrado
	*/
	char encontraBin(string valor) { //find
		Nodo *actual = root;
		for (int i = 0; i < valor.size(); i++) {
			if (actual == NULL)
				return '\0';
			char ch = valor.at(i);
			if (ch == '0')
				actual = actual->left;
			if (ch == '1')
				actual = actual->right;
		}

		if (actual == NULL)
			return '\0';

		return actual->ch;
	}

};