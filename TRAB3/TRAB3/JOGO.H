#if ! defined( JOGO_ )
#define JOGO_
/***************************************************************************
*
*  $MCD Módulo de definição: JOG  JOGO do tabuleiro
*
*  Arquivo gerado:              JOGO.H
*  Letras identificadoras:      JOG
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
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
*     1       afv   19/out/2013 início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa a criação de elementos do tipo JOGO para tabuleiro
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


/* Tipo referência para uma PECA DO JOGO */

typedef struct JOG_tagPecaJogo * JOG_tppPecaJogo ;

/***********************************************************************
*
*  $TC Tipo de dados: JOG Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da JOGO
*
***********************************************************************/

typedef enum {

	 JOG_CondRetOK = 0 ,
		   /* Concluiu corretamente */

	 JOG_CondRetJogoNulo = 1 ,

	 JOG_CondRetFaltouMemoria = 9
		   /* Faltou memória ao tentar criar um elemento de JOGO */

} JOG_tpCondRet ;


/***********************************************************************
*
*  $FC Função: JOG  &Criar JOGO
*
*
***********************************************************************/

JOG_tpCondRet JOG_CriarJogo(JOG_tppJogo * pJogo);

JOG_tpCondRet JOG_InserirPecaTimeB(JOG_tppJogo pJOGO , PEC_tppPeca pTipoPeca);

JOG_tpCondRet JOG_InserirPecaTimeA(JOG_tppJogo pJOGO , PEC_tppPeca pTipoPeca);

JOG_tpCondRet JOG_NumPecasTime(JOG_tppJogo pJOGO ,char Time, int * NumPecas);

JOG_tpCondRet JOG_ObterTipoPeca(JOG_tppJogo pJOGO , char Time, void ** pTipo);

JOG_tpCondRet JOG_IrInicioPecas(JOG_tppJogo pJOGO , char Time);

JOG_tpCondRet JOG_AvancarCorrrenteTime(JOG_tppJogo pJOGO , char Time , int val);

#undef JOGO_EXT

/********** Fim do módulo de definição: JOG  JOGO do tabuleiro **********/

#else
#endif
