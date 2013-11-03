/***************************************************************************
*
*  $MCD Módulo de definição: PEC  Peça do tabuleiro
*
*  Arquivo gerado:              PECA.H
*  Letras identificadoras:      PEC
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
*     1       afv   24/out/2013 início do desenvolvimento do módulo
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>


#define PECA_OWN
#include "PECA.H"
#undef PECA_OWN

#include "LISTA.H"

#define MAX_NOME 10

/***********************************************************************
*
*  $TC Tipo de dados: PEC Descritor do tipo de peca
*
*
***********************************************************************/

   typedef struct PEC_tagElemPeca {

		char Nome[MAX_NOME];
		/* String com o nome da peça */

		int diagonal;
		/* Se peça pode ir para diagonal 
		(1 para sim, 0 caso contrário) */

		int reta;
		/* Se peça pode ir para horizontal e vertical
		 (1 para sim, 0 caso contrário) */

		int qtde;
		/* Quantidade casas que a peça pode andar */
		  
   } PEC_tpElemPeca ;

/***** Protótipos das funções encapsuladas no módulo *****/



/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: PEC  &Criar peca
*  ****/

PEC_tpCondRet PEC_CriarPeca(PEC_tppPeca * pPeca, int Diag , int Reta , int Qtde , char * Nome)
{
	
	PEC_tppPeca mPeca = NULL;
	
	mPeca = (PEC_tppPeca) malloc(sizeof(PEC_tpElemPeca));

	if(mPeca == NULL)
	{
		return PEC_CondRetFaltouMemoria ;
	} /* if */
	
	mPeca->diagonal = Diag;
	mPeca->reta     = Reta;
	mPeca->qtde     = Qtde;
	strcpy(mPeca->Nome , Nome);
	
	(*pPeca) = (PEC_tpElemPeca *) malloc(sizeof(PEC_tppPeca));

	if(pPeca == NULL)
	{
		return PEC_CondRetFaltouMemoria ;
	} /* if */
	
	(*pPeca) = mPeca;
	
	return PEC_CondRetOK;
	
} /* Fim função: PEC &Criar Peca */

/***************************************************************************
*
*  Função: PEC  &Obter nome
*  ****/

PEC_tpCondRet PEC_ObterNome (PEC_tppPeca pPeca ,  void ** NomePeca)
{
	if(pPeca == NULL)
	{
		return PEC_CondRetPecaNula ;
	} /* if */
	
	strcpy((char *)NomePeca , pPeca->Nome);

	
	return PEC_CondRetOK;
} /* Fim função: PEC &Obter nome */

/***************************************************************************
*
*  Função: PEC  &Obter dados do tipo peça
*  ****/

PEC_tpCondRet PEC_ObterDadosTipoPeca (PEC_tppPeca pPeca , void ** Nome, int * Diag , int * Reta , int * Qtde)
{
	if(pPeca == NULL)
	{
		return PEC_CondRetPecaNula ;
	} /* if */

	strcpy((char *)Nome , pPeca->Nome);
	*Diag = pPeca->diagonal;
	*Reta = pPeca->reta;
	*Qtde = pPeca->qtde;

	return PEC_CondRetOK;

} /* Fim função: PEC &Obter dados do tipo peça */


/*****  Código das funções encapsuladas pelo módulo  *****/


/********** Fim do módulo de implementação: PEC  Peça do tabuleiro **********/

