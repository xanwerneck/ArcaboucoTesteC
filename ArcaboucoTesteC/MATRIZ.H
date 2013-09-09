#if ! defined( MATRIZ_ )
#define MATRIZ_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo árvore
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
*           fe - Fernanda Ribeiro
*			vi - Vinicius
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       1.00   aw   29/08/2013 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     .......
*
***************************************************************************/
 
#if defined( MATRIZ_OWN )
   #define MATRIZ_EXT
#else
   #define MATRIZ_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma matriz */

typedef struct MAT_tgMatriz * MAT_tppMatriz ;

/* Tipo referência para uma lista */

typedef struct LIS_tagLista * LIS_tpMatLista ;


/***********************************************************************
*
*  $TC Tipo de dados: ARV Condicoes de retorno
*
*
***********************************************************************/

typedef enum {

        MAT_CondRetOK = 0 ,
            /* Executou correto */

        MAT_CondRetNaoCriouRaiz = 1 ,
            /* Não criou nó raiz */

        MAT_CondRetErroEstrutura = 2 ,
            /* Estrutura da matriz está errada */
			
        MAT_CondRetMatrizNaoExiste = 3 ,
            /* Matriz não existe */

        MAT_CondRetMatrizVazia = 4 ,
            /* Matriz está vazia */

        MAT_CondRetNohEhRaiz = 5 ,
            /* Nó corrente é raiz */

		MAT_CondRetNaoPossuiNo = 6 ,
            /* No nao encontrado */

		MAT_CondRetMatrizCheia  = 7 ,
            /* Faltou espaço para inserir listas */

		 MAT_CondRetListaVazia = 8 ,
            /* Lista está vazia */		

        MAT_CondRetFaltouMemoria = 9 ,
            /* Faltou memória ao alocar dados */

		MAT_CondRetNoMatrizSemLista = 10
            /* No nao possui lista */

} MAT_tpCondRet ;


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

MAT_tpCondRet MAT_CriarMatriz(MAT_tppMatriz* tpMatrizModulo, int numElementos);

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
*  $FC Função: MAT Destruir matriz
*
*  $ED Descrição da função
///////////////////////////////////////////////////////////
*     Destrói o corpo e a cabeça da árvore, anulando a árvore corrente.
*     Faz nada caso a árvore corrente não exista.
*
***********************************************************************/

void DestroiMatriz( MAT_tppMatriz tpMatrizModulo ) ;


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

MAT_tpCondRet MAT_ObterListaCorr( LIS_tpMatLista lst_valor , MAT_tppMatriz tpMatrizModulo ) ;


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
