#############################################################################

Centro de Tecnologia - Departamento de Informática

Ciência da Computação

6903 - Modelagem e Otimização Algoritmica

Professor Ademir Constantino

#############################################################################


TERCEIRA AVALIAÇÃO: Algoritmos Genéticos para resolver o Problema de
Cobertura de Conjuntos (PCC)
Aluno: Rafael Cortez Sanches

RA: 82357

Maringá, 29 de fevereiro de 2016


#############################################################################


##############################################
###############################
INSTRUÇÕES PARA COMPILAR E EXECUTAR O PROGRAMA

##############################################

###############################

A aplicação está dividida em 3 arquivos de código, os quais estão listados a
seguir:


./include/matriz.h

./matriz.cpp

./main.cpp



COMPILANDO EM LINUX:

*Abrir o terminal
*Mudar o bash para o diretório onde estão os arquivos.

	Ex.: $cd ~/Downloads/geneticos_pcc

*Executar o comando "make"

*Se compilado com êxito, o executável "pcc_geneticos.out" será criado na

	pasta "./bin".



EXECUTANDO EM LINUX:

*Mudar o bash para o diretório "./bin"

*Executar o programa com o seguinte comando:

	$./pcc_geneticos.out < ARQUIVO_ENTRADA_ -p TAMANHO_POPULACAO -g

		NUMERO_MAXIMO_GERACOES -m TAXA_MINIMA_MUTACAO --echo

	Sendo ARQUIVO_ENTRADA_ um dentre os 8 arquivos de testes presentes

		no diretório "./bin", cujos nomes são "Teste_01.dat",
		"Teste_02.dat",

... "Wren_01.dat", ... "Wren_03.dat"

	TAMANHO_POPULACAO é o tamanho da população, parâmetro do algoritmo
		genético. Seu valor padrão é 500.
	NUMERO_MAXIMO_GERACOES é o número de novas soluções geradas até o
		fim da execução. Seu valor padrão é 1000.
	TAXA_MINIMA_MUTACAO é a frequência mínima com que novas soluções
		sofrem mutação a cada geração. Deve ser um decimal entre
		0 e 1. Seu valor padrão é 0.05
	O parâmetro "--echo" mostra mensagens informativas sobre o processo

		durante a execução
	Exemplo de execução:
	$./pcc_geneticos.out < ./Teste_01.dat -p 500 -g 1000 -m 0.05 --echo





COMPILANDO EM WINDOWS:

*Está disponível um executável já compilado no diretório "./bin". O arquivo

	se chama "pcc_geneticos.exe". Ele foi compilado em uma máquina
	de arquitetura x86_64



EXECUTANDO EM WINDOWS:

*Abra o diretório "./bin" no navegador de arquivos do Windows.

*Segurando o botão shift esquerdo, clique com o botão direito na tela.

*No menu, selecione a opção "Abrir janela de comando aqui".

*Execute o programa com o seguinte comando:

	pcc_geneticos.exe < ARQUIVO_ENTRADA_ -p TAMANHO_POPULACAO -g

		NUMERO_MAXIMO_GERACOES -m TAXA_MINIMA_MUTACAO --echo

	Sendo ARQUIVO_ENTRADA_ um dentre os 8 arquivos de testes presentes

		no diretório "./bin", cujos nomes são "Teste_01.dat",
		"Teste_02.dat",

... "Wren_01.dat", ... "Wren_03.dat"

	TAMANHO_POPULACAO é o tamanho da população, parâmetro do algoritmo
		genético. Seu valor padrão é 500
	NUMERO_MAXIMO_GERACOES é o número de novas soluções geradas até o
		fim da execução. Seu valor padrão é 1000
	TAXA_MINIMA_MUTACAO é a frequência mínima com que novas soluções
		sofrem mutação a cada geração. Deve ser um decimal entre
		0 e 1. Seu valor padrão é 0.05
	O parâmetro "--echo" mostra mensagens informativas sobre o processo

		durante a execução
	Exemplo de execução:
	pcc_geneticos.exe < ./Teste_01.dat -p 500 -g 1000 -m 0.05 --echo


*Obs.: O projeto .dev também pode ser carregado pelo programa DevC++ para
	Windows. Nesse caso, os parâmetros de execução podem ser passados
	pelo menu Executar -> Parâmetros..., mas o arquivo de entrada deve
	ser copiado e colado na tela de depuração do DevC++ para que o
	entrada seja devidamente processada.

ATENÇÃO: CÓDIGO FONTE PARA O run.codes:

Na pasta ./runcodes se encontra o arquivo pcc_geneticos.cpp, que é uma
concatenação dos 3 arquivos de código fonte. Da forma em que se apresenta,
o arquivo pcc_geneticos.cpp pode ser submetido ao run.codes sem problemas


#############################################################################
