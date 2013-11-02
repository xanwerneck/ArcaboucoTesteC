/***************************************************************************
*
*  $MCD Módulo de definição: JOG  JOGO do tabuleiro
*
*  Arquivo gerado:              JOGO.C
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
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>


#define JOGO_OWN
#include "JOGO.H"
#undef JOGO_OWN

#include "LISTA.H"
#include "PECA.H"

LIS_tpCondRet ListaRet;

/***********************************************************************
*
*  $TC Tipo de dados: JOG Descritor das pecas do JOGO
*
*
***********************************************************************/

typedef struct JOG_tagListaPeca{

	LIS_tppLista pListaTimeA;

	LIS_tppLista pListaTimeB;

}JOG_tpListaPeca;


   /***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor do elemento peca para Tabuleiro
*
*
***********************************************************************/

   typedef struct JOG_tagPecaJogo {

	   char Id;

	   	LIS_tppLista pListaDestino;
		
		LIS_tppLista pListaCaminho;

		PEC_tppPeca  pTipoPeca ;

   } JOG_tpPecaJogo ;

/***** Protótipos das funções encapsuladas no módulo *****/

   static void ExcluirJogo( void * pPeca );

   static void ExcluirPecaJogo( void * pPeca );

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: JOG  &Criar JOGO
*  ****/

JOG_tpCondRet JOG_CriarJogo(JOG_tppJogo * pJOGO)
{

	JOG_tppJogo mJOGO = NULL;
	
	mJOGO = (JOG_tppJogo) malloc(sizeof(JOG_tpListaPeca));

	if(mJOGO == NULL)
	{
		return JOG_CondRetFaltouMemoria ;
	}	
	
	LIS_CriarLista(ExcluirJogo , &mJOGO->pListaTimeA);

	LIS_CriarLista(ExcluirJogo , &mJOGO->pListaTimeB);
	
	(*pJOGO) = (JOG_tpListaPeca *) malloc(sizeof(JOG_tppJogo));
	
	(*pJOGO) = mJOGO;


	return JOG_CondRetOK;
	
} /* Fim função: JOG &Criar JOGO */

/***************************************************************************
*
*  Função: JOG  &InserirPecaTimeA
*  ****/

JOG_tpCondRet JOG_InserirPecaTimeA(JOG_tppJogo pJOGO , PEC_tppPeca pPecaSetar)
{

	JOG_tppPecaJogo mPeca = NULL ;

	mPeca = (JOG_tppPecaJogo) malloc(sizeof(JOG_tpPecaJogo));

	if(pJOGO == NULL)
	{
		return JOG_CondRetJogoNulo ;
	}	
	
	mPeca->pTipoPeca = pPecaSetar;

	LIS_CriarLista(ExcluirPecaJogo , &mPeca->pListaCaminho);

	LIS_CriarLista(ExcluirPecaJogo , &mPeca->pListaDestino);
	

	LIS_InserirElementoApos(pJOGO->pListaTimeA , mPeca);

	return JOG_CondRetOK;
	
} /* Fim função: JOG &InserirPecaTimeA */


/***************************************************************************
*
*  Função: JOG  &InserirPecaTimeB
*  ****/

JOG_tpCondRet JOG_InserirPecaTimeB(JOG_tppJogo pJOGO , PEC_tppPeca pPecaSetar)
{

	JOG_tppPecaJogo mPeca = NULL ;
	
	mPeca = (JOG_tppPecaJogo) malloc(sizeof(JOG_tpPecaJogo));

	if(pJOGO == NULL)
	{
		return JOG_CondRetJogoNulo ;
	}	
	
	mPeca->pTipoPeca = pPecaSetar;

	LIS_CriarLista(ExcluirPecaJogo , &mPeca->pListaCaminho);

	LIS_CriarLista(ExcluirPecaJogo , &mPeca->pListaDestino);

	LIS_InserirElementoApos(pJOGO->pListaTimeB , mPeca);
	
	return JOG_CondRetOK;
	
} /* Fim função: JOG &InserirPecaTimeB */

JOG_tpCondRet JOG_NumPecasTime(JOG_tppJogo pJOGO ,char Time, int * NumPecas)
{

	if(pJOGO == NULL)
	{
		return JOG_CondRetJogoNulo ;
	}	

	if(Time == 'A'){

		LIS_NumElem(pJOGO->pListaTimeA , NumPecas);

	}
	else if(Time == 'B'){

		LIS_NumElem(pJOGO->pListaTimeB , NumPecas);

	} /* if */

	return JOG_CondRetOK;

}

JOG_tpCondRet JOG_IrInicioPecas(JOG_tppJogo pJOGO , char Time)
{
	if(pJOGO == NULL)
	{
		return JOG_CondRetJogoNulo ;
	}	

	if(Time == 'A')
		LIS_IrInicioLista(pJOGO->pListaTimeA);

	else if(Time == 'B')
		LIS_IrInicioLista(pJOGO->pListaTimeB);

	return JOG_CondRetOK;
}

JOG_tpCondRet JOG_AvancarCorrrenteTime(JOG_tppJogo pJOGO , char Time , int val)
{
	if(pJOGO == NULL)
	{
		return JOG_CondRetJogoNulo ;
	}	

	if(Time == 'A')
		LIS_AvancarElementoCorrente(pJOGO->pListaTimeA, val);
	
	else if(Time == 'B')
		LIS_AvancarElementoCorrente(pJOGO->pListaTimeB, val);

	return JOG_CondRetOK;
}

JOG_tpCondRet JOG_ObterTipoPeca(JOG_tppJogo pJOGO , char Time, void ** pTipo)
{
	if(pJOGO == NULL)
	{
		return JOG_CondRetJogoNulo ;
	}	
	if(Time == 'A'){
		
		LIS_ObterValor(pJOGO->pListaTimeA , (void**)&pTipo);

	}
	else if(Time == 'B'){

		LIS_ObterValor(pJOGO->pListaTimeB , (void**)&pTipo);

	}
	return JOG_CondRetOK;
}

void ExcluirJogo( void * pPeca )
{

	free ( (void *) pPeca);

} /* Fim função: TST -Excluir peca */

void ExcluirPecaJogo( void * pPeca )
{

	free ( (void *) pPeca);

} /* Fim função: TST -Excluir peca */

/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/

