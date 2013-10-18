/***************************************************************************
*  $MCI Módulo de implementação: PIL  Pilha de elementos
*
*  Arquivo gerado:              PILHA.c
*  Letras identificadoras:      PIL
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
#include   <memory.h>
#include   <malloc.h>

#define PILHA_OWN
#include "PILHA.H"
#undef PILHA_OWN

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: PIL  &Criar pilha
*  ****/

	PIL_tpCondRet PIL_CriarPilha( PIL_tppPilha* pPilha, 
			      void   ( * ExcluirValor ) ( void * pDado ) )
	{

		return  ( PIL_tpCondRet ) LIS_CriarLista( ExcluirValor , pPilha);

    } /* Fim função: PIL  &Criar pilha */

/***************************************************************************
*
*  Função: PIL  &Destruir pilha
*  ****/

	PIL_tpCondRet PIL_DestruirPilha( PIL_tppPilha pPilha )
   {
	   return ( PIL_tpCondRet ) LIS_DestruirLista( pPilha ) ;
   } /* Fim função: PIL  &Destruir pilha */

/***************************************************************************
*
*  Função: PIL  &Empilha um char em uma Pilha
*  ****/

   PIL_tpCondRet PIL_PilhaPush (  PIL_tppPilha pPilha  ,  void * pValor  )
   {
	   LIS_IrFinalLista( pPilha ) ;
	   return ( PIL_tpCondRet ) LIS_InserirElementoApos( pPilha , pValor );

   } /* Fim função: PIL  &Empilha um char em uma Pilha */

/***************************************************************************
*
*  Função: PIL  &Desempilha um elemento em uma Pilha
*  ****/

   PIL_tpCondRet PIL_PilhaPop (  PIL_tppPilha pPilha  ,  void ** pResp  )
   {
	   PIL_tpCondRet CondRet1, CondRet2;

	   LIS_IrFinalLista( pPilha ) ;
	   CondRet1 = ( PIL_tpCondRet ) LIS_ObterValor( pPilha, &(*pResp) ) ;
	   CondRet2 = ( PIL_tpCondRet ) LIS_ExcluirElemento( pPilha ) ;

	   if( CondRet1 != PIL_CondRetOK ||  CondRet2 != PIL_CondRetOK )
		   return (CondRet1 != PIL_CondRetOK)? CondRet1 : CondRet2;

	   return CondRet1;

   } /* Fim função: PIL  &Desempilha um elemento em uma Pilha */

   /********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/
