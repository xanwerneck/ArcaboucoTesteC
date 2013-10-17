/***************************************************************************
*  $MCI Módulo de implementação: VER Vertice
*
*  Arquivo gerado:              VERTICE.C
*  Letras identificadoras:      VER
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\VERTICE.BSW
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

#define VERTICE_OWN
#include "VERTICE.H"
#undef VERTICE_OWN

VER_tpCondRet Ret;

/***********************************************************************
*
*  $TC Tipo de dados: VER Descritor do vértice
*
*
***********************************************************************/

   typedef struct VER_tagVertice {

	   char Nome[20];

   } VER_tpVertice ;


/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: VER  &Criar vértice
*  ****/

   VER_tpCondRet VER_CriarVertice( VER_tppVerticeCont * pVertice , char * Nome )
   {

      VER_tppVerticeCont pVerticeM = ( VER_tppVerticeCont ) malloc( sizeof( VER_tpVertice )) ;
      if ( pVerticeM == NULL )
      {
		  return VER_CondRetFaltouMemoria ;
      } /* if */

	  strcpy (pVerticeM->Nome, Nome);

	  (*pVertice) = ( VER_tpVertice * ) malloc( sizeof( VER_tpVertice )) ;
	  
	  if ( pVertice == NULL )
      {
		  return VER_CondRetFaltouMemoria ;
      } /* if */

	  (*pVertice) = pVerticeM;


	  return VER_CondRetOK ;

   } /* Fim função: VER  &Criar vértice */

/***************************************************************************
*
*  Função: VER  &Destruir vértice
*  ****/

   VER_tpCondRet VER_DestruirVertice( VER_tppVerticeCont pVertice )
   {

      #ifdef _DEBUG
         assert( pVertice != NULL ) ;
      #endif

      strcpy (pVertice->Nome , "");

	  pVertice       = NULL;

	  return VER_CondRetOK ;

   } /* Fim função: VER  &Destruir vértice */

/***************************************************************************
*
*  Função: VER  &Mudar valor do vértice
*  ****/

   VER_tpCondRet VER_MudarNomeVertice( VER_tppVerticeCont pVertice , char * Nome  )
   {

      #ifdef _DEBUG
         assert( pVertice != NULL ) ;
      #endif

	  if(pVertice == NULL)
	  {
		  return VER_CondRetNaoAchou ;
	  } /* if */
	  if(strcmp(pVertice->Nome , "")==0)
	  {
		  return VER_CondRetVerVazio;
	  } /* if */

      strcpy (pVertice->Nome , Nome);

	  if(strcmp(pVertice->Nome , Nome)==0)
	  {
		  return VER_CondRetOK;
	  } /* if */

	  return VER_CondRetNaoAchou ;

   } /* Fim função: VER  &Mudar valor do vértice */

/***************************************************************************
*
*  Função: VER  &Obter valor do vértice
*  ****/

   VER_tpCondRet VER_ObterValor( VER_tppVerticeCont pVertice , char * Nome  )
   {

      #ifdef _DEBUG
         assert( pVertice != NULL ) ;
      #endif

	  if(strcmp( pVertice->Nome , "") == 0)
	  {
		  return VER_CondRetVerVazio;
	  } /* if */

	  if(strcmp(pVertice->Nome , Nome) == 0)
	  {
		  return VER_CondRetOK;
	  } /* if */

	  return VER_CondRetNaoAchou ;

   } /* Fim função: VER  &Obter valor do vértice */

   /***************************************************************************
*
*  Função: VER  &Retorna valor do vértice
*  ****/

   VER_tpCondRet VER_RetornaValor( VER_tppVerticeCont pVertice , char * Nome )
   {

      #ifdef _DEBUG
         assert( pVertice != NULL ) ;
      #endif

	  if(pVertice == NULL)
	  {
		  return VER_CondRetNaoAchou ;
	  } /* if */

	  if(strcmp( pVertice->Nome , "") == 0)
	  {
		  Nome = pVertice->Nome;
		  return VER_CondRetVerVazio;
	  } /* if */

	  Nome = pVertice->Nome;
	  return VER_CondRetOK;
	
   } /* Fim função: VER  &Retorna valor do vértice */

/********** Fim do módulo de implementação: VER  Vértice **********/
