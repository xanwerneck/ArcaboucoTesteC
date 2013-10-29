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

#define MAX_TAB 3

GRA_tpCondRet GrafRet;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor do Tabuleiro
*
*
***********************************************************************/

   typedef struct TAB_tagTabuleiro {

         GRA_tppGrafo  tpGrafo;
		
		 MAT_tppMatriz tpMatriz;

   } TAB_tpTabuleiro ;

/***** Protótipos das funções encapsuladas no módulo *****/

   static void ExcluirInfo ( void * pValor );

/*****  Código das funções exportadas pelo módulo  *****/


TAB_tpCondRet TAB_CriarTabuleiro( TAB_tppTabuleiro * pTabuleiro ){

	GRA_tppGrafo     pGrafo;
	MAT_tppMatriz    pMatriz;
	TAB_tppTabuleiro mTab;

	mTab = ( TAB_tppTabuleiro ) malloc ( sizeof ( TAB_tpTabuleiro ) );
			/* Malloc para gerar um ponteiro de matriz */
		   
	if(mTab == NULL)
	{
		return TAB_CondRetFaltouMemoria ;
	} /* if */

	GRA_CriarGrafo( &pGrafo , ExcluirInfo);

	MAT_CriarMatriz(&pMatriz, pGrafo , 8);

	mTab->tpGrafo = pGrafo;

	mTab->tpMatriz = pMatriz;

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
	char id;

	GrafRet = GRA_IrInicio(pTabuleiro->tpGrafo);

	while(GrafRet == GRA_CondRetFimLista || GrafRet == GRA_CondRetOK)
	{
		cont++;
		GRA_BuscaIdVertice(pTabuleiro->tpGrafo , &id);
		printf("| %c |" , id );
		if(cont == 8){
			printf("\n");
			cont=0;
		}
		if(GrafRet == GRA_CondRetFimLista)
			return TAB_CondRetOK;
		GrafRet = GRA_AvancarCorrenteVert(pTabuleiro->tpGrafo , 1);
	} /* while */

	return TAB_CondRetOK;
}

void ExcluirInfo ( void * pValor )
{

    free( ( void * ) pValor ) ;

} /* Fim função: TST -Excluir informacao */

/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/

