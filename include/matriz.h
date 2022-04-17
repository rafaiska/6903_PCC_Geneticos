#ifndef MATRIZ_H_
#define MATRIZ_H_

#include <vector>
#include <iostream>
#include <string>
#include <set>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

vector <int> le_Inteiros(string entrada);
int interseccao(vector <int> a, vector <int> b); //retorna numero de elementos comuns entre dois conjuntos
vector <int>::iterator busca_Binaria(vector <int> &A, int a);

class ProblemInstance
{
	public:
		int nlinhas;
		int ncolunas;
		float *custo_coluna;
		size_t *ordem_custo; //ordem decrescente das colunas por custo
		float aptidao;
		vector <int> colunas_presentes; //lista de colunas que nao estao vazias. Usado nas matrizes solucao
		vector <vector<int> > colunas;
		vector <vector<int> > linhas;

		ProblemInstance();
		~ProblemInstance();
		const bool operator<(const ProblemInstance rhs) const;
		ProblemInstance& operator=(const ProblemInstance& p);
		bool checar_Validade();
		pair <int, int> escolher_Casal(vector <ProblemInstance> populacao);
		void criarMatrizFilha(ProblemInstance &destino);
		void gerar_Mutacao(vector <ProblemInstance> &populacao, size_t individuo);
		void gerar_Descendente(vector <ProblemInstance> &populacao, float taxa_mutacao);
		float calcula_Aptidao();
		void remover_Coluna(int r);
		int eliminar_Redundancia(); //elimina redundancia aleatoria nas colunas e retorna o numero total de redundancias encontradas
		void generateStartingPopulation(vector <ProblemInstance> &populacao, int n); //gera uma populacao inicial a partir dessa matriz
		void imprime_Matriz();
};

float calcula_Taxa_Mutacao(vector <ProblemInstance> populacao, float taxaminima);

#endif
