/***************************************************************************
*
*  $MCD Módulo de definição: PEC  Peca do tabuleiro
*
*  Arquivo gerado:              PECA.C
*  Letras identificadoras:      PEC
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


#define PECA_OWN
#include "PECA.H"
#undef PECA_OWN

#include "LISTA.H"

/***********************************************************************
*
*  $TC Tipo de dados: PEC Descritor do elemento Peca
*
*
***********************************************************************/

   typedef struct PEC_tagElemPeca {

		char * Nome;
		
		int diagonal;
		
		int reta;
		
		int qtde;
		
		LIS_tppLista pListaDestino;
		
		LIS_tppLista pListaCaminho;
   
   } PEC_tpElemPeca ;

/***** Protótipos das funções encapsuladas no módulo *****/

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: PEC  &Criar peca
*  ****/

PEC_tpCondRet PEC_CriarPeca(PEC_tppPeca * pPeca, int Diag , int Reta , int Qtde )
{

	PEC_tppPeca mPeca = NULL;
	
	mPeca = (PEC_tppPeca *) malloc(sizeof(PEC_tpElemPeca));

	if(mPeca == NULL)
	{
		return PEC_CondRetFaltouMemoria ;
	}
	
	
	
	(*pPeca) = (PEC_tppPeca) malloc(sizeof(PEC_tpElemPeca));
	
	(*pPeca) = mPeca;
	
	return PEC_CondRetOK;
	
} /* Fim função: PEC &Criar Peca */



/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/

