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

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor do Tabuleiro
*
*
***********************************************************************/

   typedef struct TAB_tagTabuleiro {

         char * Nome;

   } TAB_tpTabuleiro ;

/***** Protótipos das funções encapsuladas no módulo *****/

   static void ExcluirInfo ( void * pValor );

/*****  Código das funções exportadas pelo módulo  *****/


TAB_tpCondRet TAB_CriarTabuleiro( TAB_tppTabuleiro * pTabuleiro , char * IdVertice ){

	GRA_tppGrafo * pGrafo;
	MAT_tppMatriz * pMatriz;

	GRA_CriarGrafo(pGrafo , ExcluirInfo);

	MAT_CriarMatriz(pMatriz, (*pGrafo) , 8);

	return TAB_CondRetOK;
}

void ExcluirInfo ( void * pValor )
{

    free( ( void * ) pValor ) ;

} /* Fim função: TST -Excluir informacao */

/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/

