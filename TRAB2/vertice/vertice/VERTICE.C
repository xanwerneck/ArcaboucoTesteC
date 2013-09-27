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

#include "LISTA.H"

// verificar quais bibliotecas iremos realmente utilizar no projeto

#define VERTICE_OWN
#include "VERTICE.H"
#undef VERTICE_OWN

VER_tpCondRet Ret;

/***********************************************************************
*
*  $TC Tipo de dados: VER Elemento Vértice
*
*
***********************************************************************/

   typedef struct tagElemVertice {

	   char Nome[80];
		/* Nome do vértice */

	   struct LIS_tppLista * listaAntecessores;
		/* ponteiro para lista de antecessores */

	   struct LIS_tppLista * listaSucessores;
	    /* ponteiro para lista de sucessores */

   } tpElemVertice ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabeça de lista
*
*
***********************************************************************/

   typedef struct VER_tagVertice {

	   tpElemVertice * tpElemVer;

	   VER_tagVertice * tpElemProx;

   } VER_tpVertice ;

/***** Protótipos das funções encapuladas no módulo *****/

void SetarVertice( VER_tppVertice pVertice ) ;

void limparNome(char Nome[]) ;


/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: LIS  &Criar lista
*  ****/

   VER_tpCondRet VER_CriarVertice( VER_tpVertice * pVertice )
   {

      VER_tpVertice * pVerticeM = ( VER_tpVertice * ) malloc( sizeof( VER_tpVertice )) ;
      if ( pVerticeM == NULL )
      {
		  return VER_CondRetFaltouMemoria ;
      } /* if */

      SetarVertice( pVerticeM ) ;

	  pVertice = ( VER_tpVertice * ) malloc( sizeof( VER_tpVertice )) ;

	  pVertice = pVerticeM;

	  return VER_CondRetOK ;

   } /* Fim função: LIS  &Criar lista */

/***************************************************************************
*
*  Função: LIS  &Destruir lista
*  ****/

   VER_tpCondRet VER_DestruirVertice( VER_tppVertice pVertice )
   {

      #ifdef _DEBUG
         assert( pVertice != NULL ) ;
      #endif

      Ret = VER_EsvaziarVertice( pVertice ) ;

	  if(Ret != VER_CondRetOK)
	  {
		  return Ret;
	  }

      free( pVertice ) ;

	  if(pVertice == NULL)
	  {
		  return VER_CondRetOK ;
	  }

	  return VER_CondRetNaoAchou ;

   } /* Fim função: LIS  &Destruir lista */

/***************************************************************************
*
*  Função: LIS  &Esvaziar lista
*  ****/

   VER_tpCondRet VER_EsvaziarVertice( VER_tppVertice pVertice )
   {

	  tpElemVertice * pElem ;

      #ifdef _DEBUG
         assert( pVertice != NULL ) ;
      #endif

	  pElem = pVertice->tpElemVer ;

      while ( pElem != NULL )
      {
		  pElem->listaAntecessores = NULL;
		  pElem->listaSucessores   = NULL;
		  limparNome(pElem->Nome);
      } /* while */

      SetarVertice( pVertice ) ;

	  return VER_CondRetOK;

   } /* Fim função: LIS  &Esvaziar lista */

/***************************************************************************
*
*  Função: VER  &Criar elemento de Vértice
*  ****/

   VER_tpCondRet VER_CriarElementoVertice( LIS_tppLista * pLista1, LIS_tppLista * pLista2, char Nome[]  ){

	   tpElemVertice * tpVert = (tpElemVertice *) malloc ( sizeof(tpElemVertice) );

	   if(tpVert == NULL){
		   return VER_CondRetFaltouMemoria ;
	   }

	   if(pLista1 == NULL || pLista2 == NULL){
		   return VER_CondRetListaVerticeVazia ;
	   }

	   tpVert->listaAntecessores = pLista1;

	   tpVert->listaSucessores   = pLista2;

	   strcpy(tpVert->Nome, Nome);

	   return VER_CondRetOK;

   } /* Fim função: LIS  &Esvaziar lista */

/***************************************************************************
*
*  Função: LIS  &Inserir elemento antes
*  ****/

   VER_tpCondRet VER_InserirElementoNoVertice ( VER_tppVertice tpVertice, VER_tppElemVertice pVertice   )
   {

	   #ifdef _DEBUG
         assert( tpVertice != NULL ) ;
      #endif

	  #ifdef _DEBUG
         assert( pVertice != NULL ) ;
      #endif
      	   		 
        if (tpVertice == NULL)
        {
        return VER_CondRetVerticeNaoExiste ;
        } /* if */

		if (pVertice == NULL)
        {
        return VER_CondRetElemVerticeNaoExiste ;
        } /* if */

		tpVertice->tpElemVer  = pVertice;

		tpVertice->tpElemProx = tpVertice;

        return VER_CondRetOK ;

   } /* Fim função: LIS  &Inserir elemento antes */


/***************************************************************************
*
*  Função: LIS  &Excluir elemento
*  ****/

   VER_tpCondRet VER_ExcluirVertice( VER_tppVertice tpVertice )
   {

      #ifdef _DEBUG
         assert( tpVertice  != NULL ) ;
      #endif

      if ( tpVertice == NULL )
      {
         return VER_CondRetVerticeNulo ;
      } /* if */

	  if( tpVertice->tpElemVer != NULL )
	  {
		  return VER_CondRetVerticeContemElemento;
	  }

	  tpVertice->tpElemProx = NULL;

	  free(tpVertice);

      return VER_CondRetOK ;
      
   } /* Fim função: LIS  &Excluir elemento */


   VER_tpCondRet VER_ExcluirElementoVertice( VER_tppVertice tpVertice )
   {

	   if ( tpVertice == NULL )
      {
         return VER_CondRetVerticeNulo ;
      } /* if */

	  if( tpVertice->tpElemVer == NULL )
	  {
		  return VER_CondRetVerticeVazio;
	  }

	  if(tpVertice->tpElemVer != NULL)
	  {
		  tpVertice->tpElemVer->listaAntecessores = NULL;
		  tpVertice->tpElemVer->listaSucessores   = NULL;
		  limparNome(tpVertice->tpElemVer->Nome);
	  }

	   return VER_CondRetOK;

   }
/***************************************************************************
*
*  Função: LIS  &Obter referência para o valor contido no elemento
*  ****/

   VER_tpCondRet VER_ObterValorElemVertice( VER_tppVertice tpVertice , char Nome[] )
   {

      #ifdef _DEBUG
         assert( tpVertice != NULL ) ;
      #endif

		 if( strcmp (tpVertice->tpElemVer->Nome , Nome) )
		{
			return VER_CondRetOK;			
		}

		return VER_CondRetNaoAchou;

   } /* Fim função: LIS  &Obter referência para o valor contido no elemento */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento inicial
*  ****/

   VER_tpCondRet VER_ConheceCaminho(  VER_tppVertice tpVerticeOrig ,  VER_tppVertice tpVerticeDest )
   {
	   LIS_tppLista * listaTmp;

      #ifdef _DEBUG
         assert( tpVerticeOrig != NULL ) ;
      #endif

      #ifdef _DEBUG
         assert( tpVerticeDest != NULL ) ;
      #endif

		 listaTmp = tpVerticeOrig->tpElemVer->listaSucessores;
	
		 while(listaTmp != NULL)
		 {
			 if(listaTmp->pOrigemLista == tpVerticeDest->tpElemVer)
			 {
				 return VER_CondRetOK;	
			 }
		 }		
	  

   } /* Fim função: LIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento final
*  ****/

   LIS_tpCondRet IrFinalLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      if(pLista->pElemCorr == NULL)
	  {
		  return LIS_CondRetListaVazia;
	  }
	  if(pLista->pFimLista == NULL)
	  {
		  return LIS_CondRetNaoAchou;
	  }

      pLista->pElemCorr = pLista->pFimLista ;

	  return LIS_CondRetOK;


   } /* Fim função: LIS  &Ir para o elemento final */

/***************************************************************************
*
*  Função: LIS  &Avançar elemento
*  ****/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem )
   {

      int i ;

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Tratar lista vazia */

         if ( pLista->pElemCorr == NULL )
         {

            return LIS_CondRetListaVazia ;

         } /* fim ativa: Tratar lista vazia */

      /* Tratar avançar para frente */

         if ( numElem > 0 )
         {

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i > 0 ; i-- )
            {
               if ( pElem == NULL )
               {
                  break ;
               } /* if */
               pElem    = pElem->pProx ;
            } /* for */

            if ( pElem != NULL )
            {
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pFimLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avançar para frente */

      /* Tratar avançar para trás */

         else if ( numElem < 0 )
         {

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i < 0 ; i++ )
            {
               if ( pElem == NULL )
               {
                  break ;
               } /* if */
               pElem    = pElem->pAnt ;
            } /* for */

            if ( pElem != NULL )
            {
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pOrigemLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avançar para trás */

      /* Tratar não avançar */

         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Avançar elemento */

/***************************************************************************
*
*  Função: LIS  &Procurar elemento contendo valor
*  ****/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor        )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */

      for ( pElem  = pLista->pElemCorr ;
            pElem != NULL ;
            pElem  = pElem->pProx )
      {
         if ( pElem->pValor == pValor )
         {
            pLista->pElemCorr = pElem ;
            return LIS_CondRetOK ;
         } /* if */
      } /* for */

      return LIS_CondRetNaoAchou ;

   } /* Fim função: LIS  &Procurar elemento contendo valor */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: LIS  -Liberar elemento da lista
*
*  $ED Descrição da função
*     Elimina os espaços apontados pelo valor do elemento e o
*     próprio elemento.
*
***********************************************************************/

   void LiberarElemento( LIS_tppLista   pLista ,
                         tpElemLista  * pElem   )
   {

      if ( pElem->pValor != NULL )
      {
         ExcluirValor( pElem ) ;
      } /* if */

      free( pElem ) ;

	  if(pLista->numElem >= 0)
	  {
		  pLista->numElem-- ;
	  } /* if */


   } /* Fim função: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Função: LIS  -Excluir o valor do elemento
*
***********************************************************************/

   void ExcluirValor (tpElemLista  * pElem )
   {
	   free (pElem->pValor);
   }


/***********************************************************************
*
*  $FC Função: LIS  -Criar o elemento
*
***********************************************************************/

   tpElemLista * CriarElemento( void * pValor  )
   {

      tpElemLista * pElem ;

      pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )) ;
      if ( pElem == NULL )
      {
         return NULL ;
      } /* if */

      pElem->pValor = pValor ;
      pElem->pAnt   = NULL  ;
      pElem->pProx  = NULL  ;

      return pElem ;

   } /* Fim função: LIS  -Criar o elemento */


/***********************************************************************
*
*  $FC Função: LIS  -Limpar a cabeça da lista
*
***********************************************************************/

   void SetarVertice( VER_tppVertice pVertice )
   {

	   pVertice->tpElemProx = NULL;
	   pVertice->tpElemVer  = NULL;

   } /* Fim função: LIS  -Limpar a cabeça da lista */

   void limparNome(char Nome[]){

	   int i = 0;
	   while( Nome != NULL ){
		   Nome[i] = NULL;
		   i++;
	   }

   }

/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/

