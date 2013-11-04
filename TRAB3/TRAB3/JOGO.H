#if ! defined( JOGO_ )
#define JOGO_
/***************************************************************************
*
*  $MCD Módulo de definição: JOG  Jogo do tabuleiro
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
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     Y       afv   xx/xx/2013  finalização do desenvolvimento do modulo
*     1       afv   19/out/2013 início do desenvolvimento do módulo
*
*  $ED Descrição do módulo
*     O presente módulo implementa a criação e manipulação de estruturas 
*     do tipo jogo para tabuleiro.
*
***************************************************************************/
 
#if defined( JOGO_OWN )
   #define JOGO_EXT
#else
   #define JOGO_EXT extern
#endif

#include "PECA.H"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma JOGO */

typedef struct JOG_tagListaPeca * JOG_tppJogo ;


/* Tipo referência para uma peça do jogo */
typedef struct JOG_tagPecaJogo * JOG_tppPecaJogo ;

/***********************************************************************
*
*  $TC Tipo de dados: JOG Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do jogo
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
		   /* Faltou memória ao tentar criar um elemento jogo */

} JOG_tpCondRet ;


/***************************************************************************
*
*  $FC Função: PEC Criar jogo
*
*  $ED Descrição da função
*     Inicia um jogo vazio.
*
*  $EP Parâmetros
*     pJogo - Referência para o jogo que será criado.     
*
*  $FV Valor retornado
*     JOG_CondRetOK
*     JOG_CondRetFaltouMemoria
*
*  $AE CondRet deve ter sido instanciado
*
*  $AS Se CondRet = PEC_CondRetOK
*	   Peça criada com sucesso;
*
*	   Se CondRet = PEC_CondRetFaltouMemoria
*	   Peça não foi criada por falta de memória;
*
**************************************************************************/

JOG_tpCondRet JOG_CriarJogo(JOG_tppJogo * pJogo);


/***********************************************************************
*
*  $FC Função: JOG Inserir peça no tima A
*
*  $ED Descrição da função
*     A funão insere um tipo peça na estrutura de tipo jogo.
*
*  $EP Parâmetros
*     pPeca - Referência para a peça da qual serão retornados 
*             os elementos.
*     Nome  - Ponteiro para o qual será retornado o peça Nome.
*     Diag  - Ponteiro para o qual será retornado o peça Diag.
*     Reta  - Ponteiro para o qual será retornado o peça Reta.
*     Qtde  - Ponteiro para o qual será retornado o peça Qtde.
*
*  $FV Valor retornado
*     PEC_CondRetOK
*     PEC_CondRetPecaNula
*
*  $AE CondRet deve ter sido instanciado
*      Nome da peça tem que ser uma string não nula.
*      Diag, Reta e Qtde da variável de tipo PEC_tppPeca tem que
*      não nulos, valores inteiros.
*      Diag e Reta da pPeca valores inteiros entre 0 e 1;
*      Qtde da pPeca valor inteiro entre 1 e 7;
*
*  $AS Se CondRet = PEC_CondRetOK
*	   Obteve Nome, Diag, Reta e Qtde com sucesso;
*
*	   Se CondRet = PEC_CondRetPecaNula
*	   Peça nula, não pode retornar elementos da pPeca;
*
***********************************************************************/

JOG_tpCondRet JOG_InserirPecaTimeA(JOG_tppJogo pJOGO , PEC_tppPeca pTipoPeca);

JOG_tpCondRet JOG_InserirPecaTimeB(JOG_tppJogo pJOGO , PEC_tppPeca pTipoPeca);


JOG_tpCondRet JOG_NumPecasTime(JOG_tppJogo pJOGO ,char Time, int * NumPecas);

JOG_tpCondRet JOG_ObterTipoPeca(JOG_tppJogo pJOGO , char Time, void ** pTipo);

JOG_tpCondRet JOG_IrInicioPecas(JOG_tppJogo pJOGO , char Time);

JOG_tpCondRet JOG_AvancarCorrrenteTime(JOG_tppJogo pJOGO , char Time , int val);

JOG_tpCondRet JOG_ObterPecaJogo(JOG_tppJogo pJOGO , char Time, void ** pTipo);

#undef JOGO_EXT

/********** Fim do módulo de definição: JOG  JOGO do tabuleiro **********/

#else
#endif
