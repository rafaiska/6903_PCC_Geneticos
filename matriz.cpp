#include "matriz.h"

vector <int> le_Inteiros(string entrada)
{
	char c;
	int i = 0;
	vector <int> saida;

	while((c = entrada.c_str()[i]) != '\0')
	{
		if(c != ' ' && c != '\t')
		{
			int tamanho = 1;
			int inicio = i;

			while(entrada.c_str()[i+1] != ' ' && entrada.c_str()[i+1] != '\t' && entrada.c_str()[i+1] != '\0')
			{
				++tamanho;
				++i;
			}

			char numero[tamanho+1];

			int j;
			for(j=0; j<tamanho; ++j)
				numero[j] = entrada.c_str()[inicio+j];
			numero[j] = '\0';

			saida.push_back(atoi(numero));
		}
		++i;
	}
	return saida;
}

int interseccao(vector <int> a, vector <int> b)
{
	int retorno = 0;

	for(int i=0; i< a.size(); ++i)
		for(int j=0; j< b.size(); ++j)
			if(a[i] == b[j])
				++retorno;

	return retorno;
}

float calcula_Taxa_Mutacao(vector <Matriz> populacao, float taxaminima)
{
	return((taxaminima/(1- (exp((-(populacao[0].aptidao) -(populacao[populacao.size() -1].aptidao))/(populacao[0].aptidao))))));
}

vector <int>::iterator busca_Binaria(vector <int> &A, int a)
{
	size_t p, q, r;

	p = 0;
	r = A.size() -1;
	q = size_t((r+p)/2);

	while(A[q] != a && p < r)
	{
		if(A[q] > a)
			r = q-1;
		else
			p = q+1;

		q = size_t((r+p)/2);
	}

	if(A[q] == a)
		return(A.begin() + q);
	else
	{
		cout << "ERRO AO BUSCAR UM ELEMENTO NO VETOR: ELEMENTO NAO ENCONTRADO!\n";
		return A.end();
	}
}

Matriz::Matriz()
{
	this->custo_coluna = NULL;
	this->ncolunas = 0;
	this->nlinhas = 0;
	this->aptidao = 0;
}

const bool Matriz::operator<(const Matriz rhs) const
{
	if(this->aptidao < rhs.aptidao)
		return true;
	else
		return false;
}

void Matriz::criarMatrizFilha(Matriz &destino)
{
	destino.ncolunas = this->ncolunas;
	destino.nlinhas = this->nlinhas;
	destino.aptidao = 0;

	destino.custo_coluna = new float[this->ncolunas];
	for(int i=0; i< destino.ncolunas; ++i)
	{
		vector <int> nova_coluna;
		destino.custo_coluna[i] = this->custo_coluna[i];
		destino.colunas.push_back(nova_coluna); //insere coluna vazia
	}

	for(int i=0; i< destino.nlinhas; ++i)
	{
		vector <int> nova_linha;
		destino.linhas.push_back(nova_linha); //insere linha vazia
	}
}

Matriz::~Matriz()
{
//	if(this->custo_coluna != NULL)
//		delete this->custo_coluna;
}

bool Matriz::checar_Validade()
{
	for(int i =0; i<this->linhas.size(); ++i)
		if(this->linhas[i].size() < 1)
			return false;

	return true;
}

pair <int, int> Matriz::escolher_Casal(vector <Matriz> populacao)
{
	vector <int> probabilidades; //em fracoes de 10000
	double soma=0;
	int sorteio;
	int i;
	pair <int, int> retorno;

	for(i=0; i<populacao.size(); ++i)
		soma += populacao[i].aptidao;

	for(i=0; i<populacao.size(); ++i) //vetor de probabilidades
		probabilidades.push_back(int(((populacao[populacao.size() -1 -i].aptidao) * 10000)/soma));

	for(i=1; i<probabilidades.size(); ++i) //vetor de probabilidades acumuladas
		probabilidades[i] += probabilidades[i-1];

	sorteio = rand() % (probabilidades[probabilidades.size() -1]);

	for(i=0; i<probabilidades.size(); ++i)
	{
		if(i == 0 && sorteio < probabilidades[i])
			break;
		else if(sorteio >= probabilidades[i-1] && sorteio < probabilidades[i])
			break;	
	}

	retorno.first = i;
	retorno.second = retorno.first;

	while(retorno.first == retorno.second)
	{

		sorteio = rand() % (probabilidades[probabilidades.size() -1]);

		for(i=0; i<probabilidades.size(); ++i)
		{
			if(i == 0 && sorteio < probabilidades[i])
				break;
			else if(sorteio >= probabilidades[i-1] && sorteio < probabilidades[i])
				break;	
		}

		retorno.second = i;
	}

	return retorno;
}

void Matriz::gerar_Mutacao(vector <Matriz> &populacao, size_t individuo)
{
	vector <int> colunas_auxiliares;
	vector <int> novas_colunas;

	for(int i=0; i<populacao[individuo].colunas_presentes.size(); ++i)
	{
		int nova_coluna = (rand() % this->ncolunas) +1;
		int j;

		for(j=0; j<colunas_auxiliares.size(); ++j)
			if(colunas_auxiliares[j] == nova_coluna) break; //coluna ja estava presente

		if(j == colunas_auxiliares.size())
			colunas_auxiliares.push_back(nova_coluna);
	}
	sort(colunas_auxiliares.begin(), colunas_auxiliares.end());

	set_union(	populacao[individuo].colunas_presentes.begin(),
			populacao[individuo].colunas_presentes.end(),
			colunas_auxiliares.begin(),
			colunas_auxiliares.end(),
			back_inserter(novas_colunas)
		 );

	populacao[individuo].colunas_presentes = novas_colunas;
	for(int i=0; i<populacao[individuo].linhas.size(); ++i)
		populacao[individuo].linhas[i].clear();

	for(size_t i=0; i<populacao[individuo].colunas_presentes.size(); ++i)
	{
		int coluna_atual = populacao[individuo].colunas_presentes[i];
		populacao[individuo].colunas[coluna_atual -1] = this->colunas[coluna_atual -1];
		for(size_t j=0; j<populacao[individuo].colunas[coluna_atual -1].size(); ++j)
		{
			int linha_atual = populacao[individuo].colunas[coluna_atual -1][j];
			populacao[individuo].linhas[linha_atual -1].push_back(coluna_atual);
		}
	}

	while(populacao[individuo].eliminar_Redundancia() > 0);
}

void Matriz::gerar_Descendente(vector <Matriz> &populacao, float taxa_mutacao)
{
	pair <int,int> casal = this->escolher_Casal(populacao);
	Matriz nova;
	this->criarMatrizFilha(nova);
	populacao.push_back(nova);
	size_t inova = populacao.size() -1;

	set_union(	populacao[casal.first].colunas_presentes.begin(),
			populacao[casal.first].colunas_presentes.end(),
			populacao[casal.second].colunas_presentes.begin(),
			populacao[casal.second].colunas_presentes.end(),
			back_inserter(populacao[inova].colunas_presentes)
	     );

	for(size_t i=0; i<populacao[inova].colunas_presentes.size(); ++i)
	{
		int coluna_atual = populacao[inova].colunas_presentes[i];
		populacao[inova].colunas[coluna_atual -1] = this->colunas[coluna_atual -1];
		for(size_t j=0; j<populacao[inova].colunas[coluna_atual -1].size(); ++j)
		{
			int linha_atual = populacao[inova].colunas[coluna_atual -1][j];
			populacao[inova].linhas[linha_atual -1].push_back(coluna_atual);
		}
	}


	int mutacao = int(taxa_mutacao * 10000); //transforma taxa em fracao de dez mil
	if((rand() %10000 +1) < mutacao)
		this->gerar_Mutacao(populacao, inova);
	else
		while(populacao[inova].eliminar_Redundancia() > 0);

	populacao[inova].calcula_Aptidao();

	populacao.erase(populacao.begin() + size_t(1 + (rand() % (populacao.size() -2))));
	sort(populacao.begin(), populacao.end());
}

int Matriz::ler_Matriz_Stdin()
{
	string ler_str;
	int ler_int;
	float ler_float;

	cin >> ler_str;
	if(ler_str == "LINHAS")
		cin >> this->nlinhas;
	else
		return 1;

	cin >> ler_str;
	if(ler_str == "COLUNAS")
		cin >> this->ncolunas;
	else
		return 1;

	cin >> ler_str;
	if(ler_str != "DADOS")
		return 1;

	this->custo_coluna = new float [this->ncolunas];
	for(int i=0; i<this->nlinhas; ++i)
	{
		vector <int> col;
		this->linhas.push_back(col);
	}

	for(int i=0; i<this->ncolunas; ++i)
	{
		cin >> ler_int;
		if(ler_int != i+1)
			return 1;

		cin >> ler_float;
		if(ler_float < 0.0)
			return 1;

		this->custo_coluna[i] = ler_float;
		getline(cin, ler_str);
		vector <int> linhas;
		linhas = le_Inteiros(ler_str);

		for(int j=0; j< linhas.size(); ++j)
			this->linhas[linhas[j]-1].push_back(i+1);

		this->colunas.push_back(linhas);
		this->colunas_presentes.push_back(i+1);	
	}

	return 0;			
}

float Matriz::calcula_Aptidao()
{
	float retorno = 0;

	for(size_t i =0; i< this->colunas_presentes.size(); ++i)
		retorno += this->custo_coluna[this->colunas_presentes[i] -1];

	this->aptidao = retorno;
	return retorno;
}

void Matriz::remover_Coluna(int r)
{
	if(r<1 || r > this->colunas.size())
	{
		cout << "Erro ao tentar remover coluna " << r << " da solucao";
		return;
	}

	for(size_t i=0; i<this->colunas[r-1].size(); ++i)
	{
		int linha_removida = this->colunas[r-1][i];
		this->linhas[linha_removida -1].erase(busca_Binaria(this->linhas[linha_removida -1], r));
		/*
		for(size_t j=0; j<this->linhas[linha_removida -1].size(); ++j)
			if(this->linhas[linha_removida -1][j] == r)
			{
				this->linhas[linha_removida -1].erase(this->linhas[linha_removida -1].begin() + j);
				break;
			}
			*/
	}
	this->colunas[r-1].clear();

	this->colunas_presentes.erase(busca_Binaria(this->colunas_presentes, r));
	/*for(size_t i=0; i<this->colunas_presentes.size(); ++i)
	{
		if(this->colunas_presentes[i] == r)
		{
			this->colunas_presentes.erase(this->colunas_presentes.begin() +i);
			break;
		}
	}
	*/
}

int Matriz::eliminar_Redundancia()
{
	vector <int> redundancias;

	for(size_t i=0; i<this->colunas_presentes.size(); ++i)
	{
		size_t j;
		int coluna_atual = this->colunas_presentes[i];

		for(j=0; j<this->colunas[coluna_atual -1].size(); ++j)
		{
			int linha_atual = this->colunas[coluna_atual -1][j];
			if(this->linhas[linha_atual -1].size() < 2)
				break;
		}

		if(j == colunas[coluna_atual -1].size()) //coluna eh redundante
			redundancias.push_back(coluna_atual);
	}

	if(redundancias.size() > 0)
	{
		int removida = redundancias[rand() % redundancias.size()];
		this->remover_Coluna(removida);
		this->calcula_Aptidao();
	}

	return int(redundancias.size());
}

void Matriz::gerar_Populacao_Inicial(vector <Matriz> &populacao, int n)
{
	for(int i=0; i<n; ++i)
	{
		Matriz nova;
		this->criarMatrizFilha(nova);
		size_t index_nova = populacao.size();
		populacao.push_back(nova);

		vector <int> nao_cobertas; //linhas ainda nao cobertas

		for(int j=0; j< this->nlinhas; ++j)
			nao_cobertas.push_back(j+1); //todas linhas nao estao cobertas no inicio
		
		while(nao_cobertas.size() > 0)
		{
			size_t coluna_escolhida; //para cobrir a linha escolhida da nova matriz
			int linha_escolhida = nao_cobertas[size_t(rand() % nao_cobertas.size())];
			float razao = 99999;
			float razao_n;
		
			//Esse laco encontra a melhor coluna da matriz inicial para cobrir a linha definida aleatoriamente
			//6a linha da funcao GERAR INDIVIDUO do slide O ALGORITMO 2/7
			for(size_t k=0; k< this->linhas[linha_escolhida -1].size(); ++k)
			{
				size_t index_coluna = this->linhas[linha_escolhida -1][k] -1;
				if((razao_n = float((this->custo_coluna[index_coluna])/(interseccao(this->colunas[index_coluna], nao_cobertas)))) < razao)
				{
					razao = razao_n;
					coluna_escolhida = index_coluna +1;
				}
			}

			for(size_t k=0; k<this->colunas[coluna_escolhida -1].size(); ++k)
				populacao[index_nova].colunas[coluna_escolhida -1].push_back(this->colunas[coluna_escolhida -1][k]);
			populacao[index_nova].colunas_presentes.push_back(coluna_escolhida);

			for(size_t k=0; k< populacao[index_nova].colunas[coluna_escolhida -1].size(); ++k)
			{
				populacao[index_nova].linhas[size_t(populacao[index_nova].colunas[coluna_escolhida -1][k]) -1].push_back(coluna_escolhida);
				for(size_t l=0; l< nao_cobertas.size(); ++l)	
					if(nao_cobertas[l] == populacao[index_nova].colunas[coluna_escolhida -1][k])
					{
						nao_cobertas.erase(nao_cobertas.begin() + l);
						break;
					}
			}
		}
		for(size_t z=0; z<populacao[index_nova].linhas.size(); ++z)
			sort(populacao[index_nova].linhas[z].begin(), populacao[index_nova].linhas[z].end()); 
		sort(populacao[index_nova].colunas_presentes.begin(), populacao[index_nova].colunas_presentes.end());
		populacao[index_nova].calcula_Aptidao();
		//populacao[index_nova].imprime_Matriz();
		while(populacao[index_nova].eliminar_Redundancia() > 0);
	}
}

void Matriz::imprime_Matriz()
{
	cout << "Aptidao = " << this->aptidao << '\n';
	cout << "Colunas presentes:\n";

	for(int i=0; i<this->colunas_presentes.size(); ++i)
	{
		cout << "\tColuna " << this->colunas_presentes[i] << ": ";
		for(int j=0; j<this->colunas[this->colunas_presentes[i] -1].size(); ++j)
			cout << this->colunas[this->colunas_presentes[i] -1][j] << ' ';
		cout << '\n';
	}

	cout << "Cobertura de linhas:\n";
	for(int i=0; i<this->linhas.size(); ++i)
	{
		cout << "\tLinha " << i+1 << ": ";
		for(int j=0; j<this->linhas[i].size(); ++j)
			cout << this->linhas[i][j] << ' ';
		cout << '\n';
	}
}
