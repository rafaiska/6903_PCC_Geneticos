#include "InstanceReader.h"

const char* ProblemInstanceFileError::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW {
	return "Invalid problem instance file";
}

ProblemInstance InstanceReader::readFromStdin() {
	ProblemInstance problemInstance;
	string ler_str;
	int ler_int;
	float ler_float;

	cin >> ler_str;
	if(ler_str == "LINHAS")
		cin >> problemInstance.nlinhas;
	else
		throw ProblemInstanceFileError(ler_str);

	cin >> ler_str;
	if(ler_str == "COLUNAS")
		cin >> problemInstance.ncolunas;
	else
		throw ProblemInstanceFileError(ler_str);

	cin >> ler_str;
	if(ler_str != "DADOS")
		throw ProblemInstanceFileError(ler_str);

	problemInstance.custo_coluna = new float [problemInstance.ncolunas];
	for(int i=0; i<problemInstance.nlinhas; ++i)
	{
		vector <int> col;
		problemInstance.linhas.push_back(col);
	}

	for(int i=0; i<problemInstance.ncolunas; ++i)
	{
		cin >> ler_int;
		if(ler_int != i+1)
			throw ProblemInstanceFileError(std::to_string(ler_int));

		cin >> ler_float;
		if(ler_float < 0.0)
			throw ProblemInstanceFileError(std::to_string(ler_float));

		problemInstance.custo_coluna[i] = ler_float;
		getline(cin, ler_str);
		vector <int> linhas;
		linhas = le_Inteiros(ler_str);

		for(int j=0; j< linhas.size(); ++j)
			problemInstance.linhas[linhas[j]-1].push_back(i+1);

		problemInstance.colunas.push_back(linhas);
		problemInstance.colunas_presentes.push_back(i+1);	
	}
	return problemInstance;
}