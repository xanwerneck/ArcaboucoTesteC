/***************************************************************************
*
*  $MCD Módulo de definição: JOG  Jogo do tabuleiro
*
*  Arquivo gerado:              JOGO.C
*  Letras identificadoras:      JOG
*
*  Projeto: INF 1301 - Verificador de Xeque-Mate
*  Gestor:  Flavio Bevilacqua
*  Autores: afv:  aw - Alexandre Werneck
*                 fr - Fernanda C Ribeiro
*                 vo - Vinicius de Luiz de Oliveira
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     Y       afv   xx/xx/2013  finalização do desenvolvimento do modulo
*     1       afv   19/out/2013 início do desenvolvimento do módulo
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
#include "TABULEIRO.H"

LIS_tpCondRet ListaRet;

/***********************************************************************
*
*  $TC Tipo de dados: JOG Descritor das peças do jogo
*
*
***********************************************************************/

	typedef struct JOG_tagListaPeca{

		LIS_tppLista pListaTimeA;
		/* Ponteiro para lista de peças do time A */

		LIS_tppLista pListaTimeB;
		/* Ponteiro para lista de peças do time B */
		
	}JOG_tpListaPeca;


/***********************************************************************
*
*  $TC Tipo de dados: JOG Descritor do elemento peca para Tabuleiro
*
*
***********************************************************************/

   typedef struct JOG_tagPecaJogo {

	   char Id;
		/* Identificador da casa do tabuleiro onde a peça se encontra */

	   LIS_tppLista pListaDestino;
		/* Ponteiro para lista de casas possíveis pelo movimento da peça 
         que chegam até ao Rei */		
		
		LIS_tppLista pListaCaminho;
		/* Ponteiro para lista de casas possíveis pelo movimento da peça */

		PEC_tppPeca  pTipoPeca ;
		/* Ponteiro para o tipo da peça */

   } JOG_tpPecaJogo ;

/***** Protótipos das funções encapsuladas no módulo *****/

   static void ExcluirJogo( void * pPeca );

   static void ExcluirPecaJogo( void * pPeca );

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: JOG  &Criar jogo
*  ****/

JOG_tpCondRet JOG_CriarJogo(JOG_tppJogo * pJOGO)
{

	JOG_tppJogo mJOGO = NULL;
	
	mJOGO = (JOG_tppJogo) malloc(sizeof(JOG_tpListaPeca));

	if(mJOGO == NULL)
	{
		return JOG_CondRetFaltouMemoria ;
	} /* if */
	
	LIS_CriarLista(ExcluirJogo , &mJOGO->pListaTimeA);

	LIS_CriarLista(ExcluirJogo , &mJOGO->pListaTimeB);
	
	(*pJOGO) = (JOG_tpListaPeca *) malloc(sizeof(JOG_tppJogo));

	if(pJOGO == NULL)
	{
		return JOG_CondRetFaltouMemoria ;
	} /* if */
	
	(*pJOGO) = mJOGO;


	return JOG_CondRetOK;
	
} /* Fim função: JOG &Criar jogo */

/***************************************************************************
*
*  Função: JOG  &Inserir peça no tima A
*  ****/

JOG_tpCondRet JOG_InserirPecaTimeA(JOG_tppJogo pJOGO , PEC_tppPeca pPecaSetar)
{

	JOG_tppPecaJogo mPeca = NULL ;


	mPeca = (JOG_tppPecaJogo) malloc(sizeof(JOG_tpPecaJogo));

	if(pJOGO == NULL)
	{
		return JOG_CondRetJogoNulo ;
	} /* if */
	
	mPeca->pTipoPeca = pPecaSetar;

	ListaRet = LIS_CriarLista(ExcluirPecaJogo , &mPeca->pListaCaminho);
	if(ListaRet == LIS_CondRetFaltouMemoria)
	{
		return JOG_CondRetFaltouMemoria;
	} /* if */

	ListaRet = LIS_CriarLista(ExcluirPecaJogo , &mPeca->pListaDestino);
	if(ListaRet == LIS_CondRetFaltouMemoria)
	{
		return JOG_CondRetFaltouMemoria;
	} /* if */

	ListaRet = LIS_InserirElementoApos(pJOGO->pListaTimeA , mPeca);
	if(ListaRet == LIS_CondRetFaltouMemoria)
	{
		return JOG_CondRetFaltouMemoria;
	} /* if */

	return JOG_CondRetOK;
	
} /* Fim função: JOG &Inserir peça no tima A */


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
		ListaRet = LIS_AvancarElementoCorrente(pJOGO->pListaTimeA, val);
	
	else if(Time == 'B')
		ListaRet = LIS_AvancarElementoCorrente(pJOGO->pListaTimeB, val);

	if(ListaRet == LIS_CondRetFimLista)
		return JOG_CondRetFimLista;

	return JOG_CondRetOK;
}

JOG_tpCondRet JOG_ObterTipoPeca(JOG_tppJogo pJOGO , char Time, void ** pTipo)
{
	JOG_tppPecaJogo pPecaJogo ;
	if(pJOGO == NULL)
	{
		return JOG_CondRetJogoNulo ;
	}	
	if(Time == 'A'){
		
		LIS_ObterValor(pJOGO->pListaTimeA , (void**)&pPecaJogo);

	}
	else if(Time == 'B'){

		LIS_ObterValor(pJOGO->pListaTimeB , (void**)&pPecaJogo);

	}

	*pTipo = pPecaJogo->pTipoPeca;

	return JOG_CondRetOK;
}

JOG_tpCondRet JOG_ObterPecaJogo(JOG_tppJogo pJOGO , char Time, void ** pTipo)
{
	JOG_tppPecaJogo pPecaJogo;
	if(pJOGO == NULL)
	{
		return JOG_CondRetJogoNulo ;
	}	
	if(Time == 'A'){
		
		LIS_ObterValor(pJOGO->pListaTimeA , (void**)&pPecaJogo);

	}
	else if(Time == 'B'){

		LIS_ObterValor(pJOGO->pListaTimeB , (void**)&pPecaJogo);

	}

	*pTipo = pPecaJogo;

	return JOG_CondRetOK;
}

JOG_tpCondRet JOG_PreencheCaminho(JOG_tppJogo pJOGO , char Time)
{
	
	JOG_tppPecaJogo pPecaJogo;
	TAB_tppEstCasa pCasa;
	

	char * Nome;
	int Diag;
	int Reta;
	int Qtde;

	int QtdeTmp;

	if(pJOGO == NULL)
	{
		return JOG_CondRetJogoNulo ;
	}	
	if(Time == 'A'){
		
		LIS_ObterValor(pJOGO->pListaTimeA , (void**)&pPecaJogo);

	}
	else if(Time == 'B'){

		LIS_ObterValor(pJOGO->pListaTimeB , (void**)&pPecaJogo);

	}

	/*
	PEC_ObterDadosTipoPeca(pPecaJogo->pTipoPeca , (void**)&Nome, &Diag, &Reta, &Qtde);
	
	if(Diag == 1){
		QtdeTmp = Qtde;
		while(QtdeTmp > 0){
			TAB_IrNoNordeste(pCasa);
			if(pPecaJogo != NULL){
				//LIS_InserirElementoApos(pPecaJogo->pListaCaminho);
			}
			QtdeTmp--;
		}
	}
	if(Reta == 1){

	}
	*/

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

