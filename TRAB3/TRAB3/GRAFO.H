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
*	  vértices e um ponteiro corrente que caminha pelo grafo apontando
*     para vértice.
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
#include "TABULEIRO.H"
#include "MATRIZ.H"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um grafo */
typedef struct GRA_tagGrafo * GRA_tppGrafo ;

/* Tipo referência para um vertice de grafo */
typedef struct tagVerticeGrafo * GRA_tppVerGrafo ;

/* Tipo referência para uma aresta do vertice de grafo */
typedef struct tagArestaGrafo * GRA_tppArestaGrafo ;

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

		GRA_ArestaJaExiste = 8 ,
	       /* Não foi possível criar aresta */

        GRA_CondRetFaltouMemoria = 9 ,
            /* Faltou memória ao alocar dados */

		GRA_VerticeJaExiste = 10 ,
			/* Vertice já existe na lista de vértices desse grafo */

		GRA_CondRetFimLista = 11
		    /*	Fim da lista de vértices */

} GRA_tpCondRet ;


/***********************************************************************
*
*  $FC Função: GRA Criar grafo
*
*  $ED Descrição da função
*     Inicia um grafo vazio, sem vértices.
*
*  $EP Parâmetros
*     pGrafo  - Posição do vetor de grafos criado.
*     ExcluirValor - Função de exclusão do grafo genérico
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetFaltouMemoria
*
*  $AE CondRet deve ter sido instanciado
*
*  $AS Se CondRet = GRA_CondRetOK
*	   Grafo criado em posição do vetor  de grafos
*
*	   Se CondRet = GRA_CondRetFaltouMemoria
*	   Grafo não criado por falta de memória
*
***********************************************************************/

GRA_tpCondRet GRA_CriarGrafo (GRA_tppGrafo * pGrafo, void   ( * ExcluirValor ) ( void * pDado ) );

/***********************************************************************
*
*  $FC Função: GRA Criar vértice grafo
*
*  $ED Descrição da função
*     Cria um elemento vértice do grafo e insere
*     este na lista de vértices do grafo, sentando
*     como corrente.
*
*  $EP Parâmetros
*     pGrafo    - Grafo que receberá o vertice criado
*     conteudo  - Ponteiro para elemento de conteúdo vértice
*	  id        - Identificador do vértice
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetFaltouMemoria
*
*  $AE Grafo criado
*      CondRet deve ter sido instanciado
*
*  $AS Se CondRet = GRA_CondRetOK
*	   Vértice criado com conteúdo e id
*      ponteiro ListaAnt é apontado para lista vazia criada
*      ponteiro ListaSuc é apontado para lista vazia criada
*      Vértice inserido na lista de vértices do grafo
*
*	   Se CondRet = GRA_CondRetFaltouMemoria
*	   Vértice não criado por falta de memória
*
*
***********************************************************************/

GRA_tpCondRet GRA_CriaVerticeGrafo(GRA_tppGrafo pGrafo, char * String , char * id , void   ( * ExcluirValor ) ( void * pDado ));


/***********************************************************************
*
*  $FC Função: GRA Excluir vértice
*
*  $ED Descrição da função
*     Excluir elemento vértice corrente do grafo. Esta função percorre 
*	  a lista de antecessores e sucessores do vértice a excluir 
*     eliminando as referências e as arestas da lista de sucessores. 
*     A função também elimina, caso exista as referências em origens.
*     Elimina da lista de vértices do grafo.
*
*  $EP Parâmetros
*     pGrafo   - Ponteiro para o grafo contendo o vértice corrente
*
*  $FV Valor retornado
*      GRA_CondRetOK
*
*  $AE Grafo já deve ter sido criado
*      Corrente do grafo não pode estar nulo
*      Grafo deverá conter vértices na lista de vértices
*
*  $AS Se CondRet = GRA_CondRetOK
*      pVertice é excluído da lista de vértices do grafo
*      Caso exista, pVertice é excluído da lista de origens
*      pVertice perde as referências nas listas de antecessores e sucessores
*      As listas do vértice são excluídas
*      pVértice é excluído
*
***********************************************************************/

GRA_tpCondRet GRA_ExcluirVerticeCorrente(GRA_tppGrafo pGrafo);


/***********************************************************************
*
*  $FC Função: GRA Obter valor do vértice corrente
*
*  $ED Descrição da função
*      Checa se a string fornecida é igual a do elemento
*      vértice corrente no grafo.     
*
*  $EP Parâmetros
*      pGrafo - Ponteiro para o grafo que contém o corrente
*      nomeForn - String de comparação     
*
*  $FV Valor retornado
*      GRA_CondRetGrafoNulo
*      GRA_CondRetConteudoNulo
*      GRA_CondRetOK
*
*  $AE Grafo deve estar iniciado
*      Corrente não pode estar apontando para NULL
*      String fornecida não vazia
*      Grafo não vazio, ou seja, sem vértices
*
*  $AS Se CondRet = GRA_CondRetGrafoNulo 
*      Grafo fornecido não criado
*
*	   Se CondRet = GRA_CondRetConteudoNulo
*      Valor não encontrado ou string fornecida vazia
*
*	   Se CondRet = GRA_CondRetOK
*      Valor fornecido igual ao do vértice corrente
*
***********************************************************************/

GRA_tpCondRet GRA_ChecarNomeVerticeCorrente (GRA_tppGrafo pGrafo , char * nomeForn) ;

/***********************************************************************
*
*  $FC Função: GRA Mudar valor do vértice corrente
*
*  $ED Descrição da função
*     Recebe uma string como segundo parâmetro e altera o valor
*     do conteúdo do vértice corrente do grafo.
*
*  $EP Parâmetros
*     pGrafo - Ponteiro para o grafo
*     nomeForn - String a ser usada como novo valor para o conteudo do vértice
*
*  $FV Valor retornado
*      GRA_CondRetVerticeNulo
*      GRA_CondRetConteudoNulo
*      GRA_CondRetOK
*
*  $AE Grafo deve estar iniciado
*      Corrente não pode estar apontando para NULL
*      String fornecida não vazia
*      Grafo não vazio, ou seja, sem vértices
*
*  $AS Se CondRet = GRA_CondRetGrafoNulo 
*      Grafo fornecido não criado
*
*	   Se CondRet = GRA_CondRetConteudoNulo
*	   String fornecida vazia
*
*	   Se CondRet = GRA_CondRetOK
*      Valor do conteúdo do vértice corrente do grafo alterado
*
***********************************************************************/

GRA_tpCondRet GRA_MudarNomeVerticeCorrente (GRA_tppGrafo pGrafo , char * nomeForn) ;

/***********************************************************************
*
*  $FC Função: GRA Inserir vértice na lista de origens
*
*  $ED Descrição da função
*      Insere o vértice corrente na lista de origens
*      do grafo fornecido.
*     
*
*  $EP Parâmetros
*      pGrafo - Ponteiro para o grafo contendo o vértice corrente
*      IdVert - Char contendo o conteudo de ID do vértice corrente     
*
*  $FV Valor retornado
*      GRA_CondRetNaoAchou
*      GRA_CondRetOK
*
*  $AE O grafo deve possuir vértice com id igual ao fornecido
*      Grafo deve estar iniciado
*
*  $AS Se CondRet = GRA_CondRetNaoAchou
*	   Nenhum vértice com este id foi encontrado
*
*	   Se CondRet = GRA_CondRetOK
*      Vértice inserido na lista de origens do grafo
*
***********************************************************************/

GRA_tpCondRet GRA_InsereOrigem(GRA_tppGrafo pGrafo, char * IdVert);


/***********************************************************************
*
*  $FC Função: GRA Criar Aresta
*
*  $ED Descrição da função
*      Ao receber dois char, a função procura os vértices correspondentes.
*      O primeiro representa a origem e portanto a aresta será criada e inserida
*      na lista de sucessores deste vértice. A aresta apontará para o vértice
*      do segundo parâmetro, o destino, que também insere o vértice origem 
*      em sua respectiva lista de antecessores.
*     
*
*  $EP Parâmetros
*      pVertOrig - Id do vértice de origem
*      pvertDest - id do vértice de destino
*      pGrafo    - Grafo que contém estes vértices
*      String    - Nome que será inserido em aresta     
*
*  $FV Valor retornado
*      GRA_CondRetFaltouMemoria
*      GRA_CondRetNaoAchou
*      GRA_CondRetOK
*
*  $AE Grafo já deve ter sido iniciado
*      Os vértices fornecidos devem fazer parte do grafo passado
*
*  $AS Se CondRet = GRA_CondRetFaltouMemoria
*	   Aresta não criada por falta de memória
*
*      Se CondRet = GRA_CondRetNaoAchou
*      Um dos vértices fornecidos não foi encontrado
*
*	   Se CondRet = GRA_CondRetOK
*      Aresta criada com sucesso fazendo a ligação entre vértices
*
***********************************************************************/

GRA_tpCondRet GRA_CriarAresta (char * pVertOrig , char * pVertDest , GRA_tppGrafo pGrafo, char * String);

/***********************************************************************
*
*  $FC Função: GRA Excluir Aresta
*
*  $ED Descrição da função
*      Excluir a aresta que faz a ligação entre os vértices fornecidos.
*      Excluir também a relação da lista de antecessores da lista do vértice destino.
*     
*
*  $EP Parâmetros
*      pVertOrig - Id do vértice de origem
*      pvertDest - id do vértice de destino
*      pGrafo    - Grafo que contém estes vértices    
*
*  $FV Valor retornado
*      GRA_CondRetNaoAchou
*      GRA_CondRetOK
*
*  $AE Grafo já deve ter sido iniciado
*      Os vértices fornecidos devem fazer parte do grafo passado
*
*  $AS Se CondRet = GRA_CondRetNaoAchou
*      Um dos vértices fornecidos não foi encontrado
*
*	   Se CondRet = GRA_CondRetOK
*      Aresta excluída com sucesso
*
***********************************************************************/

GRA_tpCondRet GRA_ExcluirAresta (char * pVertOrig , char * pVertDest , GRA_tppGrafo pGrafo);

/***********************************************************************
*
*  $FC Função: GRA Definir vértice corrente
*
*  $ED Descrição da função
*      Procura o vértice com base no id fornecido e seta este como corrente
*      do grafo.
*     
*
*  $EP Parâmetros
*      pGrafo    - Grafo que contém o vértice  
*      IdVert    - id do vértice a ser usado
*
*  $FV Valor retornado
*      GRA_CondRetNaoAchou
*      GRA_CondRetOK
*
*  $AE Grafo já deve ter sido iniciado
*      O vértices fornecido deve fazer parte do grafo passado
*
*  $AS Se CondRet = GRA_CondRetNaoAchou
*      O vértice fornecido não foi encontrado
*
*	   Se CondRet = GRA_CondRetOK
*      Vértice setado como corrente
*
***********************************************************************/

GRA_tpCondRet GRA_DefinirCorrente( GRA_tppGrafo pGrafo , char * IdVert);


/***********************************************************************
*
*  $FC Função: GRA Destruir grafo
*
*  $ED Descrição da função
*      Destrói o grafo fornecido como parâmetro
*     
*
*  $EP Parâmetros
*      pGrafo    - Grafo a ser excluído
*
*  $FV Valor retornado
*      GRA_CondRetGrafoNulo
*      GRA_CondRetOK
*
*  $AE Grafo já deve ter sido iniciado
*      A lista de Origens e Vértices não deve estar vazia
*
*  $AS Se CondRet = GRA_CondRetGrafoNulo
*      O grafo fornecido não foi criado ou está nulo
*
*	   Se CondRet = GRA_CondRetOK
*      Grafo excluído com sucesso
*
***********************************************************************/

GRA_tpCondRet GRA_DestruirGrafo( GRA_tppGrafo pGrafo);

/*

*/
GRA_tpCondRet GRA_ObterVertice(GRA_tppGrafo pGrafo , void ** pValor);

GRA_tpCondRet GRA_IrInicio(GRA_tppGrafo pGrafo);

GRA_tpCondRet GRA_BuscaIdVertice(GRA_tppGrafo pGrafo , char ** pValor);
GRA_tpCondRet GRA_AvancarCorrenteVert(GRA_tppGrafo pGrafo , int val);
GRA_tpCondRet GRA_NumeroVertices(GRA_tppGrafo pGrafo , int * val);

GRA_tpCondRet GRA_SetarCorrente(GRA_tppGrafo pGrafo , char * pValor);

GRA_tpCondRet GRA_InsereConteudoVertice(GRA_tppGrafo pGrafo , void * pConteudo);

GRA_tpCondRet GRA_PegaConteudo(GRA_tppGrafo pGrafo , void ** pConteudo);

GRA_tpCondRet GRA_ObterArestaVertice(GRA_tppGrafo pGrafo , void ** rVertice , char * Aresta);

GRA_tpCondRet GRA_IrInicioAresta(GRA_tppGrafo pGrafo);

GRA_tpCondRet GRA_AvancarArestaVertice(GRA_tppGrafo pGrafo , int val);

GRA_tpCondRet GRA_NumeroArestaVertice(GRA_tppGrafo pGrafo , int * Num);

GRA_tpCondRet GRA_PegaConteudoCorrente(GRA_tppGrafo pGrafo , void ** pConteudo);

GRA_tpCondRet GRA_PegaConteudoPeloVertice(void * Vertice , void ** pConteudo);

GRA_tpCondRet GRA_ResgatarIdVertice(GRA_tppVerGrafo pVertice, char ** IdVertice);

#undef GRAFO_EXT

/********** Fim do módulo de definição: Módulo grafo **********/

#else
#endif
