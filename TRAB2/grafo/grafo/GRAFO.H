#if ! defined( VERTICE_ )
#define VERTICE_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo matriz
*
*  Arquivo gerado:              MATRIZ.H
*  Letras identificadoras:      MAT
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
*       1.00   afv   29/08/2013 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     .......
*
***************************************************************************/
 
#if defined( GRAFO_OWN )
   #define GRAFO_EXT
#else
   #define GRAFO_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um grafo */
typedef struct GRA_tagGrafo * GRA_tppGrafo ;

/* Tipo referência para um vertice de grafo */
typedef struct tagVerticeGrafo * GRA_tppVerGrafo ;

/***********************************************************************
*
*  $TC Tipo de dados: MAT Condicoes de retorno
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

        GRA_CondRetFaltouMemoria = 9 ,
            /* Faltou memória ao alocar dados */

} GRA_tpCondRet ;


/***********************************************************************
*
*  $FC Função: MAT Criar matriz
*
*  $ED Descrição da função
*     Cria uma nova matriz vazia.
*     Caso já exista uma matriz, esta será destruída.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetFaltouMemoria
*
***********************************************************************/

GRA_tpCondRet GRA_CriarGrafo (GRA_tppGrafo * pGrafo);

/***********************************************************************
*
*/

GRA_tpCondRet GRA_CriaVerticeGrafo(void * conteudo, char id);

GRA_tpCondRet GRA_InsereAntecessoresVertice(tpVerticeGrafo * pVertice, LIS_tppLista pLista);

GRA_tpCondRet GRA_InsereSucessoresVertice(tpVerticeGrafo * pVertice, LIS_tppLista pLista);

GRA_tpCondRet GRA_InsereConteudoVertice(tpVerticeGrafo * pVertice, VER_tppVertice pConteudo);

GRA_tpCondRet GRA_InsereVerticeFinal(tpVerticeGrafo * pVertice, LIS_tppLista pListaVertices);

GRA_tpCondRet GRA_InsereVerticeInicio(tpVerticeGrafo * pVertice, LIS_tppLista pListaVertices);

GRA_tpCondRet GRA_ExcluirVertice(GRA_tppGrafo pGrafo , tpVerticeGrafo * pVertice);

GRA_tpCondRet GRA_ExcluirSucessoresVertice(tpVerticeGrafo * pVertice);

GRA_tpCondRet GRA_ExcluirAntecessoresVertice(tpVerticeGrafo * pVertice);


#undef MATRIZ_EXT

/********** Fim do módulo de definição: Módulo matriz **********/

#else
#endif
