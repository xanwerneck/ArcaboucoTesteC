/***************************************************************************
*
*  $MCD Módulo de definição: TAB  Tabuleiro de Xadrez
*
*  Arquivo gerado:              TABULEIRO.C
*  Letras identificadoras:      TAB
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


#define LISTA_OWN
#include "LISTA.H"
#undef LISTA_OWN

#include "MATRIZ.H"
#include "GRAFO.H"
#include "PECA.H"

#define MAX_NOME 10

GRA_tpCondRet GrafRet;

LIS_tpCondRet ListaRet;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor do Tabuleiro
*
*
***********************************************************************/

   typedef struct TAB_tagTabuleiro {

         GRA_tppGrafo  tpGrafo;
		
		 MAT_tppMatriz tpMatriz;

		 LIS_tppLista  pListaPecas;

   } TAB_tpTabuleiro ;


/***** Protótipos das funções encapsuladas no módulo *****/

   static void ExcluirInfo ( void * pValor );
   
   static void ExcluirPeca( void * pPeca );

/*****  Código das funções exportadas pelo módulo  *****/


TAB_tpCondRet TAB_CriarTabuleiro( TAB_tppTabuleiro * pTabuleiro ){

	GRA_tppGrafo     pGrafo;
	MAT_tppMatriz    pMatriz;
	LIS_tppLista     ListaPecas;
	TAB_tppTabuleiro mTab;

	mTab = ( TAB_tppTabuleiro ) malloc ( sizeof ( TAB_tpTabuleiro ) );
			/* Malloc para gerar um ponteiro de matriz */
		   
	if(mTab == NULL)
	{
		return TAB_CondRetFaltouMemoria ;
	} /* if */

	GRA_CriarGrafo( &pGrafo , ExcluirInfo);

	MAT_CriarMatriz(&pMatriz, pGrafo , 8);

	LIS_CriarLista(ExcluirPeca , &ListaPecas);

	mTab->tpGrafo     = pGrafo;

	mTab->tpMatriz    = pMatriz;

	mTab->pListaPecas = ListaPecas;

	(*pTabuleiro) = (TAB_tpTabuleiro *) malloc (sizeof(TAB_tppTabuleiro));
	
	if( (*pTabuleiro) == NULL)
	{
		return TAB_CondRetFaltouMemoria ;
	} /* if */

	(*pTabuleiro) = mTab ;

	return TAB_CondRetOK;
}

TAB_tpCondRet TAB_ApresentaTabuleiro( TAB_tppTabuleiro pTabuleiro ){

	int cont = 0;
	char * id = NULL;
	int numElem = 0;

	GrafRet = GRA_NumeroVertices(pTabuleiro->tpGrafo , &numElem);
	if(GrafRet == GRA_CondRetOK ){
		printf("Numero de Casas do Tabuleiro %d \n\n" , numElem);
	} /* if */

	GrafRet = GRA_SetarCorrente(pTabuleiro->tpGrafo , "A1");

	GrafRet = GRA_IrInicio(pTabuleiro->tpGrafo);

	do{

		cont++;
		GRA_BuscaIdVertice(pTabuleiro->tpGrafo , &id);
		printf( "| %s |" , id );
		if(cont == 8){
			printf( "\n" );
			cont=0;
		}
		id = NULL;
		GrafRet = GRA_AvancarCorrenteVert(pTabuleiro->tpGrafo , 1);

	}while(GrafRet != GRA_CondRetFimLista);	
	printf("\n");
	return TAB_CondRetOK;

}

TAB_tpCondRet TAB_CriarTipoPeca(TAB_tppTabuleiro pTabuleiro , char * Nome , int Diagonal , int Reta , int QtdeMov)
{

	PEC_tppPeca pPeca;
	if(pTabuleiro == NULL){
		return TAB_CondRetTabuleiroNulo;
	}

	PEC_CriarPeca(&pPeca , Diagonal , Reta , QtdeMov , Nome );

	if(pPeca != NULL){
		LIS_InserirElementoApos(pTabuleiro->pListaPecas , pPeca);
	} /* if */

	return TAB_CondRetOK;
}

TAB_tpCondRet TAB_ApresentaTipoPecas(TAB_tppTabuleiro pTabuleiro)
{
	PEC_tppPeca pPeca;
	char * NomePeca;
	if(pTabuleiro==NULL){
		return TAB_CondRetTabuleiroNulo;
	}
	if(pTabuleiro->pListaPecas == NULL){
		return TAB_CondRetTabuleiroListaNula;
	}
	
	printf("Lista de tipo de pecas \n");
	ListaRet = LIS_IrInicioLista(pTabuleiro->pListaPecas);
	if(ListaRet == LIS_CondRetListaVazia)
		return TAB_TimeAVazio;
	do{
		LIS_ObterValor(pTabuleiro->pListaPecas , (void**)&pPeca);

		PEC_ObterNome (pPeca , (void**)&NomePeca);
		printf("Nome Peca: %s \n" , &NomePeca );


		ListaRet = LIS_AvancarElementoCorrente(pTabuleiro->pListaPecas , 1);


	}while(ListaRet != LIS_CondRetFimLista);

	
	return TAB_CondRetOK;

}

TAB_tpCondRet TAB_ProcuraPeca(TAB_tppTabuleiro pTabuleiro , char * NomeBuscado , void ** PecaBuscada)
{

	PEC_tppPeca pPeca;

	char NomeEnc[MAX_NOME];

	if(pTabuleiro==NULL){
		return TAB_CondRetTabuleiroNulo;
	}

	ListaRet = LIS_IrInicioLista(pTabuleiro->pListaPecas);
	
	if(ListaRet == LIS_CondRetListaVazia)
	
		return TAB_CondRetFaltouMemoria;

	do{
		LIS_ObterValor(pTabuleiro->pListaPecas , (void**)&pPeca);
		
		PEC_ObterNome (pPeca , (void**)&NomeEnc);

		if(strcmp(NomeBuscado , NomeEnc)==0){
			*PecaBuscada = pPeca;
			return TAB_CondRetOK;
		}

		ListaRet = LIS_AvancarElementoCorrente(pTabuleiro->pListaPecas , 1);


	}while(ListaRet != LIS_CondRetFimLista);

	
	return TAB_CondRetNaoAchou;

} /* if */

TAB_tpCondRet TAB_IrInicioListaPecas(TAB_tppTabuleiro pTabuleiro)
{
	if(pTabuleiro==NULL){
		return TAB_CondRetTabuleiroNulo;
	}

	ListaRet = LIS_IrInicioLista(pTabuleiro->pListaPecas);
	if(ListaRet == LIS_CondRetListaVazia)
		return TAB_CondRetListaVazia;
	return TAB_CondRetOK;
}

TAB_tpCondRet TAB_ObterTipoPeca(TAB_tppTabuleiro pTabuleiro , void ** pPeca)
{
	
	if(pTabuleiro==NULL){
		return TAB_CondRetTabuleiroNulo;
	}

	ListaRet = LIS_ObterValor(pTabuleiro->pListaPecas , (void**)&pPeca);
	
	if(ListaRet == LIS_CondRetListaVazia)
		return TAB_CondRetListaVazia;

	return TAB_CondRetOK;
}

TAB_tpCondRet TAB_AvancarTipoPeca(TAB_tppTabuleiro pTabuleiro , int val)
{
	if(pTabuleiro==NULL){
		return TAB_CondRetTabuleiroNulo;
	} /* if */
	ListaRet = LIS_AvancarElementoCorrente(pTabuleiro->pListaPecas , val);
	if(ListaRet == LIS_CondRetFimLista){
		return TAB_CondRetFimLista;
	} /* if */
	return TAB_CondRetOK;
}

void ExcluirInfo ( void * pValor )
{

    free( ( void * ) pValor ) ;

} /* Fim função: TST -Excluir informacao */

void ExcluirPeca( void * pPeca )
{

	free ( (void *) pPeca);

} /* Fim função: TST -Excluir peca */

/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/

