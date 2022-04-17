#include "matriz.h"
#include "InstanceReader.h"
#include <cstring>

bool ECHO = false;
bool NO_RAND = false;
int POPULATION_SIZE = 500;
float MIN_MUTATION_RATE = 0.05;
int MAX_GENERATIONS = 1000;

void setArguments(int argc, char* argv[]) {
	for(int i=0; i<argc; ++i)
	{
		if(!strcmp(argv[i],"--echo"))
			ECHO = true;
		else if(!strcmp(argv[i],"--norand"))
			NO_RAND = true;
		else if(!strcmp(argv[i],"-p") && argc > i+1)
			POPULATION_SIZE = atoi(argv[i+1]);
		else if(!strcmp(argv[i],"-m") && argc > i+1)
			MIN_MUTATION_RATE = atof(argv[i+1]);
		else if(!strcmp(argv[i],"-g") && argc > i+1)
			MAX_GENERATIONS = atoi(argv[i+1]);
	}
}

int main(int argc, char* argv[])
{
	ProblemInstance instance;
	InstanceReader reader;

	vector <ProblemInstance> population;
	int geracao = 0;

	time_t tempo_inicio = time(NULL);
	time_t tempo_decorrido;
	bool objectiveWasReached = false;

	setArguments(argc, argv);

	if(NO_RAND)
	{
		cout << "Warning: using fixed random seed!\n";
		srand(1);
	}
	else
		srand(time(NULL));

	instance = reader.readFromStdin();
	instance.generateStartingPopulation(population, POPULATION_SIZE);
	sort(population.begin(),population.end());

	while(!objectiveWasReached)
	{
		++geracao;
		float taxa_mutacao = calcula_Taxa_Mutacao(population, MIN_MUTATION_RATE);
		instance.gerar_Descendente(population, taxa_mutacao);

		if(geracao >= MAX_GENERATIONS)
			objectiveWasReached = true;

		if(ECHO)
		{
			tempo_decorrido = time(NULL) - tempo_inicio;
			cout << "####################################\n";
			cout << "ALGORITMO GENETICO PARA RESOLVER O PCC\n";
			cout << "GERACAO No " << geracao << " de " << MAX_GENERATIONS << '\n';
			cout << "Melhor solucao da population: " << population[0].aptidao << '\n';
			cout << "Pior solucao da population: " << population[population.size() -1].aptidao << '\n';
			cout << "Tempo decorrido: " << tempo_decorrido/60 << "m " << tempo_decorrido%60 << "s\n";
			if(NO_RAND)
				cout << "Numeros aleatorios desabilitados\n";
			else
				cout << "Numeros aleatorios habilitados\n";
			cout << "Tamanho da population: " << population.size() << '\n';
			cout << "Taxa minima de mutacao: " << MIN_MUTATION_RATE * 100 << "\% \n";
			cout << "####################################\n";
		}
	}

	tempo_decorrido = time(NULL) - tempo_inicio;
	cout << "\nFIM DA EXECUCAO!\n";
	cout << "Tempo total de execucao: " << tempo_decorrido/60 << "m " << tempo_decorrido%60 << "s\n";
	cout << "MELHOR SOLUCAO ENCONTRADA:\n";
	population[0].imprime_Matriz();

	return 0;
}
