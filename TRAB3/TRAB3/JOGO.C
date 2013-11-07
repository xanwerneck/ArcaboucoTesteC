/***********************************************************************
*
*  $MCD Modulo de definicao: JOG  Jogo do tabuleiro
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
*  $HA Historico de evolucao:
*     Versao  Autor    Data     Observacoes
*     Y       afv   xx/xx/2013  finalizacao do desenvolvimento do modulo
*     1       afv   19/out/2013 inicio do desenvolvimento do modulo
*
***********************************************************************/

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
*  $TC Tipo de dados: JOG Descritor das pecas do jogo
*
*
***********************************************************************/

typedef struct JOG_tagListaPeca{

	LIS_tppLista pListaTimeA;
	/* Ponteiro para lista de pecas do time A */

	LIS_tppLista pListaTimeB;
	/* Ponteiro para lista de pecas do time B */

}JOG_tpListaPeca;


/***********************************************************************
*
*  $TC Tipo de dados: JOG Descritor do elemento peca para Tabuleiro
*
*
***********************************************************************/

typedef struct JOG_tagPecaJogo {

	char Id;
	/* Identificador da casa do tabuleiro onde a peca se 
	   encontra */

	LIS_tppLista pListaDestino;
	/* Ponteiro para lista de casas possiveis pelo movimento
	   da peca que chegam ate ao Rei */		

	LIS_tppLista pListaCaminho;
	/* Ponteiro para lista de casas possiveis pelo 
	   movimento da peca */

	PEC_tppPeca  pTipoPeca ;
	/* Ponteiro para o tipo da peca */

} JOG_tpPecaJogo ;

/***** Prototipos das funcoes encapsuladas no modulo *****/

   static void ExcluirJogo( void * pPeca );

   static void ExcluirPecaJogo( void * pPeca );

/*****  Codigo das funcoes exportadas pelo modulo  *****/

/************************************************************************
*
*  Funcao: JOG  &Criar jogo
*  ****/

JOG_tpCondRet JOG_CriarJogo(JOG_tppJogo * pJOGO)
{

	JOG_tppJogo mJOGO = NULL;
	
	mJOGO = (JOG_tppJogo) malloc(sizeof(JOG_tpListaPeca));
	if(mJOGO == NULL)
	{
		return JOG_CondRetFaltouMemoria ;
	} /* if */
	
	ListaRet = LIS_CriarLista(ExcluirJogo , &mJOGO->pListaTimeA);
	if(ListaRet == LIS_CondRetFaltouMemoria)
	{
		return JOG_CondRetFaltouMemoria;
	} /* if */
	
	LIS_CriarLista(ExcluirJogo , &mJOGO->pListaTimeB);
	if(ListaRet == LIS_CondRetFaltouMemoria)
	{
		return JOG_CondRetFaltouMemoria;
	} /* if */
	
	(*pJOGO) = (JOG_tpListaPeca *) malloc(sizeof(JOG_tppJogo));
	if(pJOGO == NULL)
	{
		return JOG_CondRetFaltouMemoria ;
	} /* if */
	
	(*pJOGO) = mJOGO;

	return JOG_CondRetOK;
	
} /* Fim funcao: JOG &Criar jogo */


/***************************************************************************
*
*  Funcao: JOG  &Inserir peca no tima A
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
	
} /* Fim funcao: JOG &Inserir peca no time A */


/***************************************************************************
*
*  Funcao: JOG  &Inserir peca no time B
*  ****/

JOG_tpCondRet JOG_InserirPecaTimeB(JOG_tppJogo pJOGO , PEC_tppPeca pPecaSetar)
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

	ListaRet = LIS_InserirElementoApos(pJOGO->pListaTimeB , mPeca);
	if(ListaRet == LIS_CondRetFaltouMemoria)
	{
		return JOG_CondRetFaltouMemoria;
	} /* if */

	return JOG_CondRetOK;
	
} /* Fim funcao: JOG &Inserir peca no time B */

/***************************************************************************
*
*  Funcao: JOG  &Preenche caminho
*  ****/
JOG_tpCondRet JOG_PreencheCaminho(JOG_tppJogo pJOGO, TAB_tppTabuleiro pTabuleiro)
{
	
	JOG_tppPecaJogo pPecaJogo;
	TAB_tpCondRet TabRet;

	char * Nome;
	int Diag;
	int Reta;
	int Qtde;

	int QtdeTmp;

	void ** Vertice;
	
	if(pJOGO == NULL)
	{
		return JOG_CondRetJogoNulo ;
	}

	TabRet = TAB_IrInicioCasas(pTabuleiro);
	
	do{

		TAB_ObterConteudo(pTabuleiro , (void**)&pPecaJogo);
		
		if(pPecaJogo != NULL){

			PEC_ObterDadosTipoPeca(pPecaJogo->pTipoPeca , (void**)&Nome, &Diag, &Reta, &Qtde);

			if(Diag == 1){
				
				QtdeTmp = Qtde;
				while(QtdeTmp > 0){
					TAB_Caminhar(pTabuleiro , "NORDESTE"  , (void**)&Vertice);
					if(pPecaJogo != NULL){
						JOG_InsereElemApos(pPecaJogo , Vertice);
					}
					QtdeTmp--;
				}
				QtdeTmp = Qtde;
				while(QtdeTmp > 0){
					TAB_ObterCasa(pTabuleiro , (void**)&pCasa);
					TAB_IrNoNoroeste(pCasa);
					if(pPecaJogo != NULL){
						TAB_ObterVertice(pTabuleiro , &Vertice);
						JOG_InsereElemApos(pPecaJogo , Vertice);
					}
					QtdeTmp--;
				}
				QtdeTmp = Qtde;
				while(QtdeTmp > 0){
					TAB_ObterCasa(pTabuleiro , (void**)&pCasa);
					TAB_IrNoSudeste(pCasa);
					if(pPecaJogo != NULL){
						TAB_ObterVertice(pTabuleiro , &Vertice);
						JOG_InsereElemApos(pPecaJogo , Vertice);
					}
					QtdeTmp--;
				}
				QtdeTmp = Qtde;
				while(QtdeTmp > 0){
					TAB_ObterCasa(pTabuleiro , (void**)&pCasa);
					TAB_IrNoSudoeste(pCasa);
					if(pPecaJogo != NULL){
						TAB_ObterVertice(pTabuleiro , &Vertice);
						JOG_InsereElemApos(pPecaJogo , Vertice);
					}
					QtdeTmp--;
				}
				
			}
			if(Reta == 1){

			}

		}

		TabRet = TAB_AvancarCasas(pTabuleiro , 1);

	}while(TabRet != TAB_CondRetFimLista);

	
	

	return JOG_CondRetOK;

}

JOG_tpCondRet JOG_InsereElemApos(JOG_tppPecaJogo pPeca , void * Conteudo)
{
	int Num;
	if(pPeca == NULL){
		return JOG_CondRetJogoNulo;
	}
	
	LIS_NumElem(pPeca->pListaCaminho , &Num);
	printf("Numero de elementos %d" , Num);

	LIS_InserirElementoApos(pPeca->pListaCaminho , Conteudo);

	return JOG_CondRetOK;
}


/***************************************************************************
*
*  Funcao: JOG  &Avancar corrente do time
*  ****/

JOG_tpCondRet JOG_AvancarCorrrenteTime(JOG_tppJogo pJOGO , char Time , int val)
{
	if(pJOGO == NULL)
	{
		return JOG_CondRetJogoNulo ;
	} /* if */

	if(Time == 'A'){
		ListaRet = LIS_AvancarElementoCorrente(pJOGO->pListaTimeA, val);
	}
	else if(Time == 'B'){
		ListaRet = LIS_AvancarElementoCorrente(pJOGO->pListaTimeB, val);
	} /* if */
	
	if(ListaRet == LIS_CondRetFimLista || LIS_CondRetListaVazia ){
		return JOG_CondRetFimLista;
	} /* if */
	
	return JOG_CondRetOK;
	
} /* Fim funcao: JOG &Avancar corrente do time */



/***************************************************************************
*
*  Funcao: JOG  &Numero de pecas do time
*  ****/

JOG_tpCondRet JOG_NumPecasTime(JOG_tppJogo pJOGO ,char Time, int * NumPecas)
{
	if(pJOGO == NULL)
	{
		return JOG_CondRetJogoNulo ;
	} /* if */

	if(Time == 'A'){
		LIS_NumElem(pJOGO->pListaTimeA , NumPecas);
	}
	else if(Time == 'B'){
		LIS_NumElem(pJOGO->pListaTimeB , NumPecas);
	} /* if */

	return JOG_CondRetOK;

} /* Fim funcao: JOG &Inserir peca no tima B */

/***************************************************************************
*
*  Funcao: JOG  &Obter tipo de peca
*  ****/

JOG_tpCondRet JOG_ObterTipoPeca(JOG_tppJogo pJOGO , char Time, void ** pTipo)
{
	JOG_tppPecaJogo pPecaJogo ;
	if(pJOGO == NULL)
	{
		return JOG_CondRetJogoNulo ;
	} /* if */
	if(Time == 'A'){
		
		ListaRet = LIS_ObterValor(pJOGO->pListaTimeA , (void**)&pPecaJogo);
		if(ListaRet == LIS_CondRetListaVazia)
		{
			return JOG_CondRetJogoNulo;
		} /* if */

	}
	else if(Time == 'B'){

		ListaRet = LIS_ObterValor(pJOGO->pListaTimeB , (void**)&pPecaJogo);
		if(ListaRet == LIS_CondRetListaVazia)
		{
			return JOG_CondRetJogoNulo;
		} /* if */
		
	} /* if */

	*pTipo = pPecaJogo->pTipoPeca;

	return JOG_CondRetOK;
} /* Fim funcao: JOG &Obter tipo de peca */

/***************************************************************************
*
*  Funcao: JOG  &Ir inicio das pecas
*  ****/

JOG_tpCondRet JOG_IrInicioPecas(JOG_tppJogo pJOGO , char Time)
{
	if(pJOGO == NULL)
	{
		return JOG_CondRetJogoNulo ;
	} /* if */

	if(Time == 'A'){
		ListaRet = LIS_IrInicioLista(pJOGO->pListaTimeA);
		if(ListaRet == LIS_CondRetListaVazia)
		{
			return JOG_CondRetFimLista;
		} /* if */

	}
	else if(Time == 'B'){
		ListaRet = LIS_IrInicioLista(pJOGO->pListaTimeB);
		if(ListaRet == LIS_CondRetListaVazia)
		{
			return JOG_CondRetFimLista;
		} /* if */
	}
	return JOG_CondRetOK;
} /* Fim funcao: JOG &Ir inicio das pecas */

/***************************************************************************
*
*  Funcao: JOG  &Obter peca do jogo
*  ****/

JOG_tpCondRet JOG_ObterPecaJogo(JOG_tppJogo pJOGO , char Time, void ** pTipo)
{
	JOG_tppPecaJogo pPecaJogo;
	
	if(pJOGO == NULL)
	{
		return JOG_CondRetJogoNulo ;
	} /* if */
	
	if(Time == 'A'){		
		ListaRet = LIS_ObterValor(pJOGO->pListaTimeA , (void**)&pPecaJogo);
		if(ListaRet == LIS_CondRetListaVazia)
		{
			return JOG_CondRetJogoNulo;
		} /* if */
	}
	else if(Time == 'B'){
		ListaRet = LIS_ObterValor(pJOGO->pListaTimeB , (void**)&pPecaJogo);
		if(ListaRet == LIS_CondRetListaVazia)
		{
			return JOG_CondRetJogoNulo;
		} /* if */
		
	} /* if */

	*pTipo = pPecaJogo;

	return JOG_CondRetOK;
	
} /* Fim funcao: JOG &Obter peca do jogo */



/*****  Codigo das funcoes encapsuladas no modulo  *****/


/***********************************************************************
*
*  $FC Funcao: JOG  -Excluir jogo
*
*  $ED Descricao da funcao
*      Libera o espaco alocado na memoria para o jogo.
*
***********************************************************************/

	void ExcluirJogo( void * pPeca )
	{

		free ( (void *) pPeca);

	} /* Fim funcao: JOG -Excluir jogo */

/***********************************************************************
*
*  $FC Funcao: JOG  -Excluir peca do jogo
*
*  $ED Descricao da funcao
*      Libera o espaco alocado na memoria para a peca do jogo.
*
***********************************************************************/

	void ExcluirPecaJogo( void * pPeca )
	{

		free ( (void *) pPeca);

	} /* Fim funcao: JOG -Excluir peca do jogo */


/********** Fim do modulo de implementacao: JOG  Lista duplamente encadeada **********/

