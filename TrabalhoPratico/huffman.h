#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Lista.h"
#include "Tree.h"

LinkedDupleList lista;

using namespace std;

// vem do ficheiro Tree.h
extern string binario, binChOcorrencia;
extern int nZeros;

class huffman {
public:
	/**
	* Função responsável por abrir o ficheiro dado como
	* parametro e retornar o seu conteudo
	*
	* @param nome     - nome do ficheiro a abrir
	* @return string  - conteudo do ficheiro
	*/
	string abreFicheiro(string nome) {
		ifstream ficheiro;
		string item, conteudo;
		ficheiro.open(nome);

		if (ficheiro.is_open())
		{
			if (ficheiro.fail()) {
				cerr << "Erro a abrir!!!!!!" << endl;
				system("pause");
				exit(1);
			}

			while (!ficheiro.eof()) {
				getline(ficheiro, item);
				conteudo += item;
				if (ficheiro.eof() - 1) {
					conteudo += "\n";
				}
			}
		}
		else {
			cout << "Nao foi possivel encontrar o ficheiro" << endl;
			exit(1);
		}

		ficheiro.close();
		return conteudo;
	}

	/**
	* Função responsável por contar o numero de
	* ocorrencias de um char numa string criando
	* a lista
	*
	* @param conteudo - string a ser adicionada à lista
	*/
	void criaLista(string conteudo)
	{
		int cont;
		char c;

		for (int i = 0; i <= 255; i++) {
			c = (char)i;
			cont = (int)count(conteudo.begin(), conteudo.end(), c);
			if (cont) {
				lista.addOrdered(c, cont);
				cont = 0;
			}
		}
	}

	string chToBin(char x) {
		string binary = bitset<8>(x).to_string();
		return binary;
	}
	int binToCh(string x) {
		int decimal = bitset<8>(x).to_ulong();
		return decimal;
	}

	/**
	* Função responsável por converter o valor
	* binário para caracteres
	*
	* @param binario  - valor binario a ser convertido
	* @return string - string convertida
	*/
	string binarioParaCh(string binario)
	{
		string texto, colocaZero;
		int i, x = binario.length() % 8;
		if (x != 0) {
			nZeros = 8 - binario.length() % 8;
			while (x < 8) {
				colocaZero += "0";
				x++;
			}
		}

		binario += colocaZero;
		for (int i = 0; i < binario.length();i += 8)
		{
			string octeto = binario.substr(i + 0, 8);
			texto += char(binToCh(octeto));
		}
		return texto;
	}

	/**
	* Função responsável por criar o ficheiro
	* com o conteudo compactado
	*
	* @param nome - nome do ficheiro a ser criado
	*/
	void guardaFicheiroCompactado(string nome)
	{
		string aux = binarioParaCh(binChOcorrencia) + "\n" + binarioParaCh(binario), novo;
		novo = binToCh(chToBin(nZeros));
		novo += aux;
		ofstream ficheiro(nome + ".huff");
		if (ficheiro.is_open())
		{
			ficheiro << novo;
			ficheiro.close();
			cout << "O ficheiro foi criado com o nome " << nome + ".huff" << endl;
		}
		else {
			cout << "Ocorreu um erro ao escrever o ficheiro!" << endl;
		}
	}

	/**
	* Função responsável por criar o ficheiro
	* com o conteudo descompactado
	*
	* @param nome - nome do ficheiro a ser criado
	* @param conteudo - conteudo do ficheiro a ser criado
	*/
	void guardaFicheiroDescompactado(string nome, string conteudo)
	{
		size_t found = nome.find(".huff");
		nome.replace(found, std::string(".huff").length(), "");

		ofstream ficheiro(nome);
		if (ficheiro.is_open())
		{
			ficheiro << conteudo;
			ficheiro.close();
			cout << "O ficheiro foi criado com o nome " << nome << endl;
		}
		else {
			cout << "Ocorreu um erro ao escrever o ficheiro!" << endl;
		}
	}

	/**
	* Função responsável por abrir o ficheiro dado como
	* parametro, colocando as letras e ocorrencias na lista
	* e colocando o codigo binario da segunda linha na variavel global
	*
	* @param nome     - nome do ficheiro a abrir
	* @param string  - conteudo do ficheiro
	*/
	void decodeRead(string value) {

		ifstream ficheiro;
		ficheiro.open(value);

		if (ficheiro.fail()) {
			cerr << "Erro ao abrir!" << endl;
			system("pause");
			exit(1);
		}
		string item, texto;
		while (!ficheiro.eof()) {
			getline(ficheiro, item);

			if (!ficheiro.eof()) {
				//cout << "passou" << endl;
				if (!nZeros)
					nZeros = item.at(0);

				for (unsigned i = 1; i < item.length() - 1; i += 2)
				{
					char c = item.at(i);
					int oc = item.at(i + 1);
					lista.addOrdered(c, oc);
				}
			}
			else {
				for (unsigned i = 0; i < item.length(); ++i)
				{
					char x = item.at(i);
					binario += chToBin(x);
				}
			}
		}
	}

	/**
	* Mensagem de ajuda mostrada ao utilizador
	*
	* @param numArgs - número de argumentos
	* @param args[]  - argumentos
	*/
	void mensagem(int numArgs, char *args[])
	{
		cout << "Utilizacao: \n" << returnPath(args, 2) << " [OPCAO] [FICHEIRO]" << endl;
		cout << "                 -h                 Mostra esta mensagem de ajuda" << endl;
		cout << "                 -c    [FICHEIRO]   Compacta o ficheiro" << endl;
		cout << "                 -d    [FICHEIRO]   Descompacta o ficheiro" << endl;
		cout << "                 -v    [FICHEIRO]   Mostra a arvore de codificacao do ficheiro" << endl;
		system("pause");
		exit(1);
	}

	/**
	* Função responsável por retornar a path ou
	* o nome do executavel conforme a flag
	*
	* @param  args[] - argumentos do main
	* @param  flag   - flag
	* @return string  - nome do executavel ou path
	*/
	string returnPath(char *args[], int flag) {
		// obtem a ultima posição do caracter '/'
		string aux(args[0]);

		// get '/' or '\\' depending on unix/mac or windows.
		#if defined(_WIN32) || defined(WIN32)
			int pos = aux.rfind('\\');
		#else
			int pos = aux.rfind('/');
		#endif

		// retorna a path do executavel sem o executavel
		if (flag == 1) {
			return aux.substr(0, pos + 1);
		}
		else { // retorna o nome do executavel
			return aux.substr(pos + 1);
		}
	}

	/**
	* Função responsável por retornar a path ou
	* o nome do executavel conforme a flag
	*
	* @param begin - argmentos recebidos pela main
	* @param end   - argmentos recebidos pela main + o numero de argumentos
	* @param option - parametro pretendido
	* @return char  - retorna o parametro seguinte ao parametro pretendido
	*/
	char* getCmdOption(char ** begin, char ** end, const string& option)
	{
		char ** itr = find(begin, end, option);
		if (itr != end && ++itr != end)
		{
			return *itr;
		}
		return 0;
	}

	/**
	* Função responsável por retornar um bool
	* caso um parametro esteja definido
	*
	* @param begin  - argmentos recebidos pela main
	* @param end    - argmentos recebidos pela main + o numero de argumentos
	* @param option - argumento pretendido
	* @return string  - nome do executavel ou path
	*/
	bool cmdOptionExists(char** begin, char** end, const string& option)
	{
		return find(begin, end, option) != end;
	}

};