#if ! defined( JOGO_ )
#define JOGO_
/***************************************************************************
*
*  $MCD Modulo de definicao: JOG  Jogo do tabuleiro
*
*  Arquivo gerado:              JOGO.H
*  Letras identificadoras:      JOG
*
*  Projeto: INF 1301 - Verificador de Xeque-Mate
*  Gestor:  Flavio Bevilacqua
*  Autores: afv:  aw - Alexandre Werneck
*                 fr - Fernanda C Ribeiro
*			      vo - Vinicius de Luiz de Oliveira
*
*  $HA Historico de evolucao:
*     Versao  Autor    Data     Observacoes
*     Y       afv   xx/xx/2013  finalizacao do desenvolvimento do modulo
*     1       afv   19/out/2013 inicio do desenvolvimento do modulo
*
*  $ED Descricao do modulo
*     O presente modulo implementa a criacao e manipulacao de estruturas 
*     do tipo jogo para tabuleiro.
*
***************************************************************************/
 
#if defined( JOGO_OWN )
   #define JOGO_EXT
#else
   #define JOGO_EXT extern
#endif

#include "PECA.H"

/***** Declaracoes exportadas pelo modulo *****/

/* Tipo referencia para um jogo */
typedef struct JOG_tagListaPeca * JOG_tppJogo ;


/* Tipo referencia para uma peca do jogo */
typedef struct JOG_tagPecaJogo * JOG_tppPecaJogo ;

/***********************************************************************
*
*  $TC Tipo de dados: JOG Condicoes de retorno
*
*
*  $ED Descricao do tipo
*     Condicoes de retorno das funcoes do jogo
*
***********************************************************************/

typedef enum {

	 JOG_CondRetOK = 0 ,
		   /* Concluiu corretamente */

	 JOG_CondRetJogoNulo = 1 ,
		   /* Jogo nulo */

	 JOG_CondRetFimLista = 2 ,
		   /* Final de lista */
		   
	 JOG_CondRetFaltouMemoria = 9
		   /* Faltou memoria ao tentar criar um elemento jogo */

} JOG_tpCondRet ;


/***************************************************************************
*
*  $FC Funcao: JOG Criar jogo
*
*  $ED Descricao da funcao
*     Inicia um jogo vazio.
*
*  $EP Parametros
*     pJogo - Referencia para o estrutura de jogo que sera criado.     
*
*  $FV Valor retornado
*     JOG_CondRetOK
*     JOG_CondRetFaltouMemoria
*
*  $AE CondRet deve ter sido instanciado
*
*  $AS Se CondRet = JOG_CondRetOK
*	   Jogo criado com sucesso;
*
*	   Se CondRet = JOG_CondRetFaltouMemoria
*	   Jogo nao foi criado por falta de memoria;
*
**************************************************************************/

JOG_tpCondRet JOG_CriarJogo(JOG_tppJogo * pJogo);


/***********************************************************************
*
*  $FC Funcao: JOG Inserir peca no time A
*
*  $ED Descricao da funcao
*     A funcao insere um tipo peca na estrutura de tipo jogo.
*
*  $EP Parametros
*     pJOGO     - Referencia para o estrutura de jogo que sera criado.  
*     pPecaSetar - Ponteiro para a peça a qual será inserida no jogo.
*
*  $FV Valor retornado
*     JOG_CondRetOK
*     JOG_CondRetFaltouMemoria
*
*  $AE CondRet deve ter sido instanciado
*      pPecaSetar tem que ser uma estrutura válida, com elementos internos 
*       setados e igualmente válidos.
*
*  $AS Se CondRet = JOG_CondRetOK
*	   Obteve Nome, Diag, Reta e Qtde com sucesso;
*
*	   Se CondRet = JOG_CondRetFaltouMemoria
*	   Não pode inserir elemento peça no jogo;
*
***********************************************************************/

JOG_tpCondRet JOG_InserirPecaTimeA(JOG_tppJogo pJOGO , PEC_tppPeca pPecaSetar);



/***********************************************************************
*
*  $FC Funcao: JOG Inserir peca no time B
*
*  $ED Descricao da funcao
*     A funcao insere um tipo peca na estrutura de tipo jogo.
*
*  $EP Parametros
*     pJOGO     - Referencia para o estrutura de jogo que sera criado.  
*     pPecaSetar - Ponteiro para a peça a qual será inserida no jogo.
*
*  $FV Valor retornado
*     JOG_CondRetOK
*     JOG_CondRetFaltouMemoria
*
*  $AE CondRet deve ter sido instanciado
*      pPecaSetar tem que ser uma estrutura válida, com elementos internos 
*       setados e igualmente válidos.
*
*  $AS Se CondRet = JOG_CondRetOK
*	   Obteve Nome, Diag, Reta e Qtde com sucesso;
*
*	   Se CondRet = JOG_CondRetFaltouMemoria
*	   Não pode inserir elemento peça no jogo;
*
***********************************************************************/

JOG_tpCondRet JOG_InserirPecaTimeB(JOG_tppJogo pJOGO , PEC_tppPeca pPecaSetar);



/***********************************************************************
*
*  $FC Funcao: JOG Numero de pecas do time
* 
*  $ED Descricao da funcao
*     A funcao retorna por parametro a quantidade de pecas do time que 
*     tambem foi passado por parametro.
*
*  $EP Parametros
*     pJOGO    - Referencia para o estrutura de jogo ao qual se obtem 
*                quantidade de pecas.  
*     Time     - O time sobre o qual sera obtido o numero de pecas.
*     NumPecas - Ponteiro para onde será retornado a quantidade de pecas.
*
*  $FV Valor retornado
*     JOG_CondRetOK
*     JOG_CondRetJogoNulo
*
*  $AE CondRet deve ter sido instanciado
*      pJOGO tem que ter a lista de jogos A e B declarados e válidos.
*      Time tem que ser um char 'A' ou 'B'.      
*
*  $AS Se CondRet = JOG_CondRetOK
*      Retornou a quantidade de pecas corretamente.
*
*	   Se CondRet = JOG_CondRetFaltouMemoria
*	   Jogo vazio, logo nao ha pecas.
*
***********************************************************************/

JOG_tpCondRet JOG_NumPecasTime(JOG_tppJogo pJOGO ,char Time, int * NumPecas);



/***********************************************************************
*
*  $FC Funcao: JOG Numero de pecas do time
* 
*  $ED Descricao da funcao
*     A funcao retorna por parametro a quantidade de pecas do time que 
*     tambem foi passado por parametro.
*
*  $EP Parametros
*     pJOGO    - Referencia para o estrutura de jogo ao qual se obtem 
*                quantidade de pecas.  
*     Time     - O time sobre o qual sera obtido o numero de pecas.
*     NumPecas - Ponteiro para onde será retornado a quantidade de pecas.
*
*  $FV Valor retornado
*     JOG_CondRetOK
*     JOG_CondRetJogoNulo
*
*  $AE CondRet deve ter sido instanciado
*      pJOGO tem que ter a lista de jogos A e B declarados e válidos.
*      Time tem que ser um char 'A' ou 'B'.      
*
*  $AS Se CondRet = JOG_CondRetOK
*      Retornou a quantidade de pecas corretamente.
*
*	   Se CondRet = JOG_CondRetFaltouMemoria
*	   Jogo vazio, logo nao ha pecas.
*
***********************************************************************/

JOG_tpCondRet JOG_ObterTipoPeca(JOG_tppJogo pJOGO , char Time, void ** pTipo);

JOG_tpCondRet JOG_IrInicioPecas(JOG_tppJogo pJOGO , char Time);

JOG_tpCondRet JOG_AvancarCorrrenteTime(JOG_tppJogo pJOGO , char Time , int val);

JOG_tpCondRet JOG_ObterPecaJogo(JOG_tppJogo pJOGO , char Time, void ** pTipo);

#undef JOGO_EXT

/********** Fim do módulo de definição: JOG  JOGO do tabuleiro **********/

#else
#endif
