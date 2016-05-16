#include "matriz.h"
#include <cstring>

int main(int argc, char *argv[])
{
	Matriz problema;
	bool ECHO = false;
	bool OBJETIVO = false;
	bool NO_RAND = false;
	int TAMANHO_POP = 500;
	float TAXA_MIN = 0.05;
	int MAX_GERACOES = 1000;
	vector <Matriz> populacao;
	int geracao = 0;
	time_t tempo_inicio = time(NULL);
	time_t tempo_decorrido;

	for(int i=0; i<argc; ++i)
	{
		if(!strcmp(argv[i],"--echo"))
			ECHO = true;
		else if(!strcmp(argv[i],"--norand"))
			NO_RAND = true;
		else if(!strcmp(argv[i],"-p") && argc > i+1)
			TAMANHO_POP = atoi(argv[i+1]);
		else if(!strcmp(argv[i],"-m") && argc > i+1)
			TAXA_MIN = atof(argv[i+1]);
		else if(!strcmp(argv[i],"-g") && argc > i+1)
			MAX_GERACOES = atoi(argv[i+1]);
	}

	if(NO_RAND)
	{
		cout << "Aviso: numeros aleatorios desabilitados!\n";
		srand(1);
	}
	else
		srand(time(NULL));

	if(problema.ler_Matriz_Stdin() != 0)
	{
		cout << "ERRO AO LER O ARQUIVO DE ENTRADA\n";
		return 1;
	}

	problema.gerar_Populacao_Inicial(populacao, TAMANHO_POP);
	sort(populacao.begin(),populacao.end());

	while(!OBJETIVO)
	{
		++geracao;
		float taxa_mutacao = calcula_Taxa_Mutacao(populacao, TAXA_MIN);
		problema.gerar_Descendente(populacao, taxa_mutacao);

		if(geracao >= MAX_GERACOES)
			OBJETIVO = true;

		if(ECHO)
		{
			tempo_decorrido = time(NULL) - tempo_inicio;
			cout << "####################################\n";
			cout << "ALGORITMO GENETICO PARA RESOLVER O PCC\n";
			cout << "GERACAO No " << geracao << " de " << MAX_GERACOES << '\n';
			cout << "Melhor solucao da populacao: " << populacao[0].aptidao << '\n';
			cout << "Pior solucao da populacao: " << populacao[populacao.size() -1].aptidao << '\n';
			cout << "Tempo decorrido: " << tempo_decorrido/60 << "m " << tempo_decorrido%60 << "s\n";
			if(NO_RAND)
				cout << "Numeros aleatorios desabilitados\n";
			else
				cout << "Numeros aleatorios habilitados\n";
			cout << "Tamanho da populacao: " << populacao.size() << '\n';
			cout << "Taxa minima de mutacao: " << TAXA_MIN * 100 << "\% \n";
			cout << "####################################\n";
		}
	}

	tempo_decorrido = time(NULL) - tempo_inicio;
	cout << "\nFIM DA EXECUCAO!\n";
	cout << "Tempo total de execucao: " << tempo_decorrido/60 << "m " << tempo_decorrido%60 << "s\n";
	cout << "MELHOR SOLUCAO ENCONTRADA:\n";
	populacao[0].imprime_Matriz();

	return 0;
}
