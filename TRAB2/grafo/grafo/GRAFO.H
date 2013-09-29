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


/***********************************************************************
*
*  $TC Tipo de dados: MAT Condicoes de retorno
*
*
***********************************************************************/

typedef enum {

        VER_CondRetOK = 0 ,
            /* Executou correto */

        VER_CondRetNaoCriouRaiz = 1 ,
            /* Não criou nó raiz */

        VER_CondRetErroEstrutura = 2 ,
            /* Estrutura da matriz está errada */
			
        VER_CondRetMatrizNaoExiste = 3 ,
            /* Matriz não existe */

        VER_CondRetMatrizVazia = 4 ,
            /* Matriz está vazia */

        VER_CondRetNohEhRaiz = 5 ,
            /* Nó corrente é raiz */

		VER_CondRetNaoPossuiNo = 6 ,
            /* No nao encontrado */

		VER_CondRetMatrizCheia  = 7 ,
            /* Faltou espaço para inserir listas */

		 VER_CondRetListaVazia = 8 ,
            /* Lista está vazia */		

        VER_CondRetFaltouMemoria = 9 ,
            /* Faltou memória ao alocar dados */

		VER_CondRetNoMatrizSemLista = 10 ,
            /* No nao possui lista */
			
		VER_CondRetNoListaDiferente = 11
            /* Lista nao corresponde a corrente */

} VER_tpCondRet ;


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

VER_tpCondRet VER_CriarMatriz(VER_tppVertice* tpVertice);

/***********************************************************************
*
*  $FC Função: MAT Inserir Lista na matriz corrente
*
*  $ED Descrição da função
*     Insere uma lista na matriz corrente
*
*  $FV Valor retornado
*     MAT_CondRetFaltouMemoria
*     MAT_CondRetMatrizVazia
*	  MAT_CondRetOK
*	  MAT_CondRetMatrizCheia
*
***********************************************************************/

MAT_tpCondRet MAT_InsereListaMatriz( LIS_tpMatLista * lt, MAT_tppMatriz tpMatrizModulo);

/***********************************************************************
*
*  $FC Função: MAT Ir para nó norte
*
*  $FV Valor retornado
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNaoPossuiNo
*     MAT_CondRetOK
*
***********************************************************************/

MAT_tpCondRet MAT_IrNoNorte(MAT_tppMatriz tpMatrizModulo);


/***********************************************************************
*
*  $FC Função: MAT Ir para nó nordeste
*
*  $FV Valor retornado
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNaoPossuiNo
*     MAT_CondRetOK
*
***********************************************************************/

MAT_tpCondRet MAT_IrNoNordeste(MAT_tppMatriz tpMatrizModulo) ;


/***********************************************************************
*
*  $FC Função: MAT Ir para nó leste
*
*  $FV Valor retornado
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNaoPossuiNo
*     MAT_CondRetOK
*
***********************************************************************/

MAT_tpCondRet MAT_IrNoLeste(MAT_tppMatriz tpMatrizModulo) ;

/***********************************************************************
*
*  $FC Função: MAT Ir para nó sudeste
*
*  $FV Valor retornado
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNaoPossuiNo
*     MAT_CondRetOK
*
***********************************************************************/

MAT_tpCondRet MAT_IrNoSudeste(MAT_tppMatriz tpMatrizModulo) ;


/***********************************************************************
*
*  $FC Função: MAT Ir para nó sul
*
*  $FV Valor retornado
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNaoPossuiNo
*     MAT_CondRetOK
*
***********************************************************************/

MAT_tpCondRet MAT_IrNoSul(MAT_tppMatriz tpMatrizModulo) ;

/***********************************************************************
*
*  $FC Função: MAT Ir para nó sudoeste
*
*  $FV Valor retornado
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNaoPossuiNo
*     MAT_CondRetOK
*
***********************************************************************/

MAT_tpCondRet MAT_IrNoSudoeste(MAT_tppMatriz tpMatrizModulo) ;

/***********************************************************************
*
*  $FC Função: MAT Ir para nó oeste
*
*  $FV Valor retornado
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNaoPossuiNo
*     MAT_CondRetOK
*
***********************************************************************/

MAT_tpCondRet MAT_IrNoOeste(MAT_tppMatriz tpMatrizModulo) ;

/***********************************************************************
*
*  $FC Função: MAT Ir para nó noroeste
*
*  $FV Valor retornado
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNaoPossuiNo
*     MAT_CondRetOK
*
***********************************************************************/

MAT_tpCondRet MAT_IrNoNoroeste(MAT_tppMatriz tpMatrizModulo) ;

/***********************************************************************
*
*  $FC Função: MAT Obter valor corrente
*
*  $EP Parâmetros
*     $P ValorParm - é o parâmetro que receberá o valor contido 
* 	 				 no ponteiro da lista
*
*  $FV Valor retornado
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetOK
*
***********************************************************************/

MAT_tpCondRet MAT_ObterListaCorr( LIS_tpMatLista * lst_valor , MAT_tppMatriz tpMatrizModulo ) ;


/***********************************************************************
*
*  $FC Função: MAT Ir raiz
*
*
*  $FV Valor retornado
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*	  MAT_CondRetOK
*     MAT_CondRetNohEhRaiz
*
***********************************************************************/

MAT_tpCondRet MAT_IrRaiz( MAT_tppMatriz tpMatrizModulo );

#undef MATRIZ_EXT

/********** Fim do módulo de definição: Módulo matriz **********/

#else
#endif
