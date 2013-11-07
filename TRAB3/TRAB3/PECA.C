/***************************************************************************
*
*  $MCD Modulo de definicao: PEC  Peca do tabuleiro
*
*  Arquivo gerado:              PECA.H
*  Letras identificadoras:      PEC
*
*  Projeto: INF 1301 - Verificador de Xeque-mate
*  Gestor:  Flavio Bevilacqua
*  Autores: afv:  aw - Alexandre Werneck
*                 fr - Fernanda C Ribeiro
*			         vo - Vinicius de Luiz de Oliveira
*
*  $HA Historico de evolucao:
*     Versao  Autor    Data     Observacoes
*     Y       afv   xx/xx/2013  finalizacao do desenvolvimento do modulo
*     1       afv   24/out/2013 inicio do desenvolvimento do modulo
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

/**************************************************************************
*
*  $TC Tipo de dados: PEC Descritor do tipo de peca
*
*
**************************************************************************/

   typedef struct PEC_tagElemPeca {

		char Nome[MAX_NOME];
		/* String com o nome da peca */

		int diagonal;
		/* Se peca pode ir para diagonal 
		(1 para sim, 0 caso contrario) */

		int reta;
		/* Se peca pode ir para horizontal e vertical
		 (1 para sim, 0 caso contrario) */

		int qtde;
		/* Quantidade casas que a peca pode andar */
		  
   } PEC_tpElemPeca ;

/************* Prototipos das funcoes encapsuladas no modulo ***********/



/*************  Codigo das funcoes exportadas pelo modulo  *************/

/************************************************************************
*
*  Funcao: PEC  &Criar peca
*  ****/

PEC_tpCondRet PEC_CriarPeca(PEC_tppPeca * pPeca, int Diag , int Reta , 
									 int Qtde , char * Nome)
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
	
} /* Fim funcao: PEC &Criar Peca */

/************************************************************************
*
*  Funcao: PEC  &Obter nome
*  ****/

PEC_tpCondRet PEC_ObterNome (PEC_tppPeca pPeca ,  void ** NomePeca)
{
	if(pPeca == NULL)
	{
		return PEC_CondRetPecaNula ;
	} /* if */
	
	strcpy((char *)NomePeca , pPeca->Nome);

	
	return PEC_CondRetOK;
} /* Fim funcao: PEC &Obter nome */

/************************************************************************
*
*  Funcao: PEC  &Obter dados do tipo peca
*  ****/

PEC_tpCondRet PEC_ObterDadosTipoPeca (PEC_tppPeca pPeca , void ** Nome, 
                                      int * Diag , int * Reta , int * Qtde)
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

} /* Fim funcao: PEC &Obter dados do tipo peca */


/************  Codigo das funcoes encapsuladas no modulo  *************/


/****** Fim do modulo de implementacao: PEC  Peca do tabuleiro ********/

