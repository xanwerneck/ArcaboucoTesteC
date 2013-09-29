/***************************************************************************
*  $MCI Módulo de implementação: VER Vertice
*
*  Arquivo gerado:              VERTICE.C
*  Letras identificadoras:      VER
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: afv
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       afv   19/09/2013 início desenvolvimento
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

	   char Nome[80];

   } VER_tpVertice ;


/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: VER  &Criar vértice
*  ****/

   VER_tpCondRet VER_CriarVertice( VER_tpVertice * pVertice , char * Nome )
   {

      VER_tpVertice * pVerticeM = ( VER_tpVertice * ) malloc( sizeof( VER_tpVertice )) ;
      if ( pVerticeM == NULL )
      {
		  return VER_CondRetFaltouMemoria ;
      } /* if */

	  strcpy(pVerticeM->Nome, Nome);

	  pVertice = ( VER_tpVertice * ) malloc( sizeof( VER_tpVertice )) ;
	  
	  if ( pVertice == NULL )
      {
		  return VER_CondRetFaltouMemoria ;
      } /* if */

	  pVertice = pVerticeM;

	  return VER_CondRetOK ;

   } /* Fim função: VER  &Criar vértice */

/***************************************************************************
*
*  Função: VER  &Destruir vértice
*  ****/

   VER_tpCondRet VER_DestruirVertice( VER_tppVertice pVertice )
   {

      #ifdef _DEBUG
         assert( pVertice != NULL ) ;
      #endif

      strcpy (pVertice->Nome , "");

      free( pVertice ) ;

	  if(pVertice == NULL)
	  {
		  return VER_CondRetOK ;
	  }

	  return VER_CondRetNaoAchou ;

   } /* Fim função: VER  &Destruir vértice */

/***************************************************************************
*
*  Função: VER  &Mudar valor do vértice
*  ****/

   VER_tpCondRet VER_MudarNomeVertice( VER_tppVertice pVertice , char * Nome  )
   {

      #ifdef _DEBUG
         assert( pVertice != NULL ) ;
      #endif

	  if(pVertice == NULL || !strcmp(Nome , ""))
	  {
		  return VER_CondRetNaoAchou ;
	  }
	  if(strcmp(pVertice->Nome , ""))
	  {
		  return VER_CondRetVerVazio;
	  }
	  
      strcpy (pVertice->Nome , Nome);

	  if(strcmp(pVertice->Nome , Nome))
	  {
		  return VER_CondRetOK;
	  }

	  return VER_CondRetNaoAchou ;

   } /* Fim função: VER  &Destruir vértice */


/********** Fim do módulo de implementação: VER  Vértice **********/
