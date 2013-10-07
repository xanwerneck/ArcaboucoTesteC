#if ! defined( GRAFO_ )
#define GRAFO_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo grafo
*
*  Arquivo gerado:              GRAFO.H
*  Letras identificadoras:      GRA
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: INF 1301 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: aw - Alexandre Werneck
*           fr - Fernanda Camelo Ribeiro
*			vo - Vinicius de Luiz de Oliveira
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       1.00   afv   09/out/2013 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo implementa a criação e manipulação de grafos dirigidos.
*	  Podem existir n grafos operando simultaneamente.
*	  O módulo grafo possui cabeça apontando para uma lista de origens,
*	  vértices e um ponteiro corrente que caminha pelo vértice.
*
*	  A lista de origens referencia a origem de cada sub-grafo, caso
*	  exista, no módulo grafo.
*
*	  A lista de vértices possui referência para todos os vértices do
*	  grafo.
*
***************************************************************************/
 
#if defined( GRAFO_OWN )
   #define GRAFO_EXT
#else
   #define GRAFO_EXT extern
#endif

#include "LISTA.H"
#include "VERTICE.H"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um grafo */
typedef struct GRA_tagGrafo * GRA_tppGrafo ;

/* Tipo referência para um vertice de grafo */
typedef struct tagVerticeGrafo * GRA_tppVerGrafo ;

/***********************************************************************
*
*  $TC Tipo de dados: GRA Condicoes de retorno
*
*
***********************************************************************/

typedef enum {

        GRA_CondRetOK = 0 ,
            /* Executou correto */

		GRA_CondRetValorNulo = 1 ,
			/* Valor fornecido nulo */

		GRA_CondRetVerticeNulo = 2 ,
			/* Vertice de parametro nulo */

		GRA_CondRetListaNula = 3 ,
			/* Valor lista nula */

		GRA_CondRetConteudoNulo = 4 ,
			/* Conteudo fornecido nulo */

	   GRA_CondRetGrafoNulo   = 5 ,
		    /* Grafo nulo */

       GRA_CondRetNaoAchou   = 6 ,
	       /* Condicao não encontrou */

       GRA_CondRetMaisdeUmaOrigem = 7 ,
	       /* Não foi possível inserir em origem */

        GRA_CondRetFaltouMemoria = 9 ,
            /* Faltou memória ao alocar dados */

} GRA_tpCondRet ;


/***********************************************************************
*
*  $FC Função: GRA Criar grafo
*
*  $ED Descrição da função
*     Cria um grafo vazio, sem apontamentos.
*
*  $EP Parâmetros
*     pGrafo  - Posição do vetor de grafos criado.
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetFaltouMemoria
*
*  $AE CondRet deve ter sido instanciado
*
*  $AS Se CondRet = GRA_CondRetOK
*	   Grafo criado em posição do vetor
*
*	   Se CondRet = GRA_CondRetFaltouMemoria
*	   Grafo não criado por falta de memória
*
***********************************************************************/

GRA_tpCondRet GRA_CriarGrafo (GRA_tppGrafo * pGrafo);

/***********************************************************************
*
*  $FC Função: GRA Criar vértice grafo
*
*  $ED Descrição da função
*     Cria um elemento vértice do grafo sem listas e sem conteúdo.
*
*  $EP Parâmetros
*     conteudo  - Ponteiro para elemento de conteúdo vértice (Modulo Vertice)
*	  id        - Identificador do vértice
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetFaltouMemoria
*
*  $AE Variável conteudo ponteiro não nulo
*      Variável id do tipo char não vazio
*      CondRet deve ter sido instanciado
*
*  $AS Se CondRet = GRA_CondRetOK
*	   Vértice criado com conteúdo e id
*      Os ponteiros de lista voltam vazio
*      ponteiro ListaAnt volta null
*      ponteiro ListaSuc volta null
*
*	   Se CondRet = GRA_CondRetFaltouMemoria
*	   Vértice não criado por falta de memória

*
***********************************************************************/

GRA_tpCondRet GRA_CriaVerticeGrafo(GRA_tppVerGrafo * pVertice, char * String , char id);

/***********************************************************************
*
*  $FC Função: GRA Insere Lista de antecessores no vértice
*
*  $ED Descrição da função
*     Recebe uma lista de antecessores e faz o apontamento no vértice fornecido.
*
*  $EP Parâmetros
*     pVertice  - Ponteiro para elemento de conteúdo vértice (Modulo Vertice)
*	  pLista    - Ponteiro para lista de antecessores criada
*
*  $FV Valor retornado
*     GRA_CondRetVerticeNulo
*     GRA_CondRetListaNula
*     GRA_CondRetOK
*
*
*  $AE Variável pVertice deve ter sido iniciada
*      Variável pLista deve ter sido iniciada
*      CondRet deve ter sido instanciado
*
*  $AS Se CondRet = GRA_CondRetVerticeNulo
*	   Vértice fornecido não iniciado ou nulo
*      Se CondRet = GRA_CondRetListaNula
*      Lista fornecida não iniciada ou nula
*
*	   Se CondRet = GRA_CondRetOK
*      Vértice fornecido recebe lista de antecessores
*      
*
*
***********************************************************************/

GRA_tpCondRet GRA_InsereAntecessoresVertice(GRA_tppVerGrafo pVertice);

/***********************************************************************
*
*  $FC Função: GRA Insere Lista de sucessores no vértice
*
*  $ED Descrição da função
*     Recebe uma lista de sucessores e faz o apontamento no vértice fornecido.
*
*  $EP Parâmetros
*     pVertice  - Ponteiro para elemento de conteúdo vértice (Modulo Vertice)
*	  pLista    - Ponteiro para lista de sucessores criada
*
*  $FV Valor retornado
*     GRA_CondRetVerticeNulo
*     GRA_CondRetListaNula
*     GRA_CondRetOK
*
*  $AE Variável pVertice deve ter sido iniciada
*      Variável pLista deve ter sido iniciada
*      CondRet deve ter sido instanciado
*
*  $AS Se CondRet = GRA_CondRetVerticeNulo
*	   Vértice fornecido não iniciado ou nulo
*      Se CondRet = GRA_CondRetListaNula
*      Lista fornecida não iniciada ou nula
*
*	   Se CondRet = GRA_CondRetOK
*      Vértice fornecido recebe lista de antecessores
*
***********************************************************************/

GRA_tpCondRet GRA_InsereSucessoresVertice(GRA_tppVerGrafo pVertice);

/***********************************************************************
*
*  $FC Função: GRA Insere conteúdo vértice
*
*  $ED Descrição da função
*     Insere ponteiro do tipo tpVertice no vértice do grafo
*
*  $EP Parâmetros
*     pVertice  - Ponteiro para elemento de conteúdo vértice (Modulo Vertice)
*	  pConteudo - Ponteiro para conteúdo do módulo vértice
*
*  $FV Valor retornado
*     GRA_CondRetVerticeNulo
*     GRA_CondRetConteudoNulo
*     GRA_CondRetOK
*
*
*  $AE Variável pVertice deve ter sido iniciada
*      Variável pConteudo deve ter sido iniciada
*      CondRet deve ter sido instanciado
*
*  $AS Se CondRet = GRA_CondRetVerticeNulo
*	   Vértice fornecido não iniciado ou nulo
*      Se CondRet = GRA_CondRetConteudoNulo
*      Conteudo fornecido deve ter sido iniciado no modulo vértice
*
*	   Se CondRet = GRA_CondRetOK
*      Vértice fornecido recebe conteúdo
*      
*
***********************************************************************/

GRA_tpCondRet GRA_InsereConteudoVertice(GRA_tppVerGrafo pVertice, char * dado);

/***********************************************************************
*
*  $FC Função: GRA Insere vértice no final da lista de vértices
*
*  $ED Descrição da função
*     Insere ponteiro do tipo tpVertice no vértice do grafo
*
*  $EP Parâmetros
*     pVertice  - Ponteiro para elemento de conteúdo vértice (Modulo Vertice)
*	  pConteudo - Ponteiro para conteúdo do módulo vértice
*
*  $FV Valor retornado
*     GRA_CondRetVerticeNulo
*     GRA_CondRetListaNula
*     GRA_CondRetOK
*
*
*  $AE Variável pVertice deve ter sido iniciada
*      Variável pListaVertices deve ter sido iniciada
*      Variável pListaVertices não pode estar vazia
*      CondRet deve ter sido instanciado
*
*  $AS Se CondRet = GRA_CondRetVerticeNulo
*	   Vértice fornecido não iniciado ou nulo
*      Se CondRet = GRA_CondRetListaNula
*      Lista fornecida está vazia ou não foi iniciada
*
*	   Se CondRet = GRA_CondRetOK
*      Vértice fornecido entra no final da lista de Vértices
*      pVertice se torna corrente da lista de Vértices
*
***********************************************************************/

GRA_tpCondRet GRA_InsereVerticeFinal(GRA_tppGrafo pGrafo , GRA_tppVerGrafo pVertice);

/***********************************************************************
*
*  $FC Função: GRA Insere vértice no início da lista de vértices
*
*  $ED Descrição da função
*     Insere ponteiro do tipo tpVertice no vértice do grafo
*
*  $EP Parâmetros
*     pVertice  - Ponteiro para elemento de conteúdo vértice (Modulo Vertice)
*	  pConteudo - Ponteiro para conteúdo do módulo vértice
*
*  $FV Valor retornado
*     GRA_CondRetVerticeNulo
*     GRA_CondRetListaNula
*     GRA_CondRetOK
*
*
*  $AE Variável pVertice deve ter sido iniciada
*      Variável pListaVertices deve ter sido iniciada
*      Variável pListaVertices não pode estar vazia
*	   CondRet deve ter sido instanciado
*
*  $AS Se CondRet = GRA_CondRetVerticeNulo
*	   Vértice fornecido não iniciado ou nulo
*      Se CondRet = GRA_CondRetListaNula
*      Lista fornecida está vazia ou não foi iniciada
*
*	   Se CondRet = GRA_CondRetOK
*      Vértice fornecido entra no início da lista de Vértices
*      pVertice se torna corrente da lista de Vértices
*
*
***********************************************************************/

GRA_tpCondRet GRA_InsereVerticeInicio(GRA_tppGrafo pGrafo , GRA_tppVerGrafo pVertice);

/***********************************************************************
*
*  $FC Função: GRA Excluir vértice
*
*  $ED Descrição da função
*     Excluir elemento vértice do grafo. Esta função percorre a lista de antecessores
*     e sucessores do vértice a excluir eliminando as referências. 
*	  A função também elimina, caso exista as referências em origens e vértice
*     do grafo.
*
*  $EP Parâmetros
*     pGrafo   - Ponteiro para o grafo contendo o vértice
*	  pVertice - Ponteiro para vértice a ser excluído
*
*  $FV Valor retornado
*     GRA_CondRetOK
*
*  $AE Variável pGrafo deve ter sido iniciado ou não nulo
*      Variável pVertice deve ter sido iniciado ou não nulo
*      CondRet deve ter sido instanciado
*      pVertice precisa conter elementos
*
*  $AS Se CondRet = GRA_CondRetOK
*      pVertice é excluído da lista de vértices do grafo
*      pVertice perde as referências nas listas de antecessores e sucessores
*      pVertice é excluído da lista de origens caso esteja na lista
*
***********************************************************************/

GRA_tpCondRet GRA_ExcluirVertice(GRA_tppGrafo pGrafo ,GRA_tppVerGrafo pVertice);

/***********************************************************************
*
*  $FC Função: GRA Excluir sucessores do vértice
*
*  $ED Descrição da função
*     Esta função pode ser definida como exclusão de arestas, com este procedimento
*     todas as referências existentes na lista de sucessores do vértice fornecido é
*     perdida.
*
*  $EP Parâmetros
*	  pVertice - Ponteiro para vértice contendo a lista a ser excluída
*
*  $FV Valor retornado
*     GRA_CondRetVerticeNulo
*     GRA_CondRetListaNula
*     GRA_CondRetOK
*
*
*  $AE Variável pVertice deve ter sido iniciado ou não nulo
*      CondRet deve ter sido instanciado
*
*  $AS Se CondRet = GRA_CondRetOK
*      pVertice perde a lista de sucessores 
*
***********************************************************************/

GRA_tpCondRet GRA_ExcluirSucessoresVertice(GRA_tppVerGrafo pVertice);

/***********************************************************************
*
*  $FC Função: GRA Excluir antecessores do vértice
*
*  $ED Descrição da função
*     Esta função pode ser definida como exclusão de arestas, com este procedimento
*     todas as referências existentes na lista de antecessores do vértice fornecido é
*     perdida.
*
*  $EP Parâmetros
*	  pVertice - Ponteiro para vértice contendo a lista a ser excluída
*
*  $FV Valor retornado
*     GRA_CondRetVerticeNulo
*     GRA_CondRetListaNula
*     GRA_CondRetOK
*
*
*  $AE Variável pVertice deve ter sido iniciado ou não nulo
*      CondRet deve ter sido instanciado
*
*  $AS Se CondRet = GRA_CondRetVerticeNulo
*      Vértice fornecida está nulo
*      Se CondRet = GRA_CondRetListaNula
*      Lista Nula ou não iniciada
*
*	   Se CondRet = GRA_CondRetOK
*      pVertice perde a lista de antecessores 
*
***********************************************************************/

GRA_tpCondRet GRA_ExcluirAntecessoresVertice(GRA_tppVerGrafo pVertice);


GRA_tpCondRet GRA_InsereVerticeemSucessores(GRA_tppVerGrafo pVerticeOrig , GRA_tppVerGrafo  pVerticeDest) ;

GRA_tpCondRet GRA_InsereVerticeemAntecessores(GRA_tppVerGrafo pVerticeOrig , GRA_tppVerGrafo pVerticeDest) ;

GRA_tpCondRet GRA_ObterValorVerticeCorrente (GRA_tppGrafo pGrafo , char * nomeForn) ;

GRA_tpCondRet GRA_MudarValorVerticeCorrente (GRA_tppGrafo pGrafo , char * nomeForn) ;

GRA_tpCondRet GRA_InsereVerticeOrigens(GRA_tppGrafo pGrafo , GRA_tppVerGrafo pVertice) ;

#undef MATRIZ_EXT

/********** Fim do módulo de definição: Módulo grafo **********/

#else
#endif
