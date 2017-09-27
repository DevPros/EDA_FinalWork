#include <iostream>
#include <algorithm>
#include <string>
#include "huffman.h"

using namespace std;

int main(int numArgs, char *args[]) {
	// lista declarada no ficheiro huffman.h
	extern LinkedDupleList lista;

	//string declaradas no ficheiro Tree.h
	extern string binario, binChOcorrencia;

	huffman huff;

	string conteudoFicheiro;

	// se o numero de argumentos no programa for mais que 4 e menor que 2
	if (numArgs < 2 || numArgs > 4) {
		huff.mensagem(numArgs, args);
	}

	if (huff.cmdOptionExists(args, args + numArgs, "-h"))
	{
		huff.mensagem(numArgs, args);
	}

	char *compacta = huff.getCmdOption(args, args + numArgs, "-c");
	if (compacta)
	{
		string nome = compacta;
		// Lê o conteudo do ficheiro para dentro da variavel
		conteudoFicheiro = huff.abreFicheiro(nome);

		// cria a lista com o conteudo do ficheiro
		huff.criaLista(conteudoFicheiro);

		//lista.mostra();

		while (lista.head != lista.tail) {
			Tree *left = lista.RemoveFirst();
			Tree *rigth = lista.RemoveFirst();
			ItemDL * novo = lista.addOrdered('\0', left->root->ocorrencia + rigth->root->ocorrencia);
			novo->data->root->left = left->root;
			novo->data->root->right = rigth->root;
		}

		// codifica a arvore com o codigo binario
		lista.codifica();

		// coloca o binario na var global
		lista.colocaBinario(conteudoFicheiro);

		// coloca o binario das letras e ocorrencias na variavel global
		lista.encodeLetrasOc();

		// cria o ficheiro final com as conversoes binario para char
		huff.guardaFicheiroCompactado(nome);
	}

	char * descompacta = huff.getCmdOption(args, args + numArgs, "-d");
	if (descompacta)
	{
		string nome = descompacta;
		size_t found = nome.find(".huff");
		if (found != string::npos)
		{

			huff.decodeRead(nome);

			while (lista.head != lista.tail) {
				Tree *left = lista.RemoveFirst();
				Tree *rigth = lista.RemoveFirst();
				ItemDL * novo = lista.addOrdered('\0', left->root->ocorrencia + rigth->root->ocorrencia);
				novo->data->root->left = left->root;
				novo->data->root->right = rigth->root;
			}

			lista.codifica();

			string converte = lista.converteTexto(binario);

			huff.guardaFicheiroDescompactado(nome, converte);
		}
		else {
			cout << "O tipo de ficheiro especificado nao e valido!" << endl;
		}
	}

	char *mostraArvore = huff.getCmdOption(args, args + numArgs, "-v");
	if (mostraArvore)
	{
		string nome = mostraArvore;
		size_t found = nome.find(".huff");
		if (found != string::npos)
		{

			huff.decodeRead(nome);

			while (lista.head != lista.tail) {
				Tree *left = lista.RemoveFirst();
				Tree *rigth = lista.RemoveFirst();
				ItemDL * novo = lista.addOrdered('\0', left->root->ocorrencia + rigth->root->ocorrencia);
				novo->data->root->left = left->root;
				novo->data->root->right = rigth->root;
			}

			lista.codifica();

			lista.mostra();
		}
		else {
			cout << "O tipo de ficheiro especificado nao e valido!" << endl;
		}
	}
	system("pause");
	return 0;
}