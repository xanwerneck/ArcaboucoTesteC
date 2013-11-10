/***************************************************************************
*
*  $MCD Modulo de definicao: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.C
*  Letras identificadoras:      LIS
*
*  Projeto: INF 1301 - Verificador de Xeque-mate
*  Gestor:  Flavio Bevilacqua
*  Autores: afv:  aw - Alexandre Werneck
*                 fr - Fernanda C Ribeiro
*                 vo - Vinicius de Luiz de Oliveira
*
*  $HA Historico de evolucao:
*     Versao  Autor    Data     Observacoes
*     Y       afv   xx/xx/2013  finalizacao do desenvolvimento do modulo
*     1       afv   19/out/2013 inicio do desenvolvimento do modulo
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


/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/

   typedef struct tagElemLista {

         void * pValor ;
               /* Ponteiro para o valor contido no elemento */

         struct tagElemLista * pAnt ;
               /* Ponteiro para o elemento predecessor */

         struct tagElemLista * pProx ;
               /* Ponteiro para o elemento sucessor */

   } tpElemLista ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabeca de lista
*
*
***********************************************************************/

   typedef struct LIS_tagLista {

         tpElemLista * pOrigemLista ;
               /* Ponteiro para a origem da lista */

         tpElemLista * pFimLista ;
               /* Ponteiro para o final da lista */

         tpElemLista * pElemCorr ;
               /* Ponteiro para o elemento corrente da lista */

         int numElem ;
               /* Numero de elementos da lista */

         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a funcao de destruicao do valor contido 
                  em um elemento */

   } LIS_tpLista ;

/************* Prototipos das funcoes encapsuladas no modulo ***********/
   
   /* Funcao libera elemento da lista */
   static void LiberarElemento( LIS_tppLista   pLista ,
                               tpElemLista  * pElem   ) ;
   
   /* Funcao cria elemento de lista com pValor */
   static tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                       void *       pValor  ) ;

   /* Funcao seta elementos de pLista cabeca como NULL e num elem = 0, 
      ou seja tambem serve para criar elemento cabeca vazio */
   static void LimparCabeca( LIS_tppLista pLista ) ;

/*************  Codigo das funcoes exportadas pelo modulo  *************/

/************************************************************************
*
*  Funcao: LIS  &Criar lista
*  ****/

   LIS_tpCondRet LIS_CriarLista( void (* ExcluirValor) (void * pDado) , 
                               LIS_tppLista * pLista )
   {

      LIS_tpLista * pListaM = NULL ;

      pListaM = ( LIS_tpLista * ) malloc( sizeof( LIS_tpLista )) ;
      if ( pListaM == NULL )
      {
		  return LIS_CondRetFaltouMemoria ;
      } /* if */

      /* Funcao tambem serve para criar elemento cabeca */
      LimparCabeca( pListaM ) ;

      pListaM->ExcluirValor = ExcluirValor ;

	  (*pLista) = ( LIS_tppLista ) malloc( sizeof( LIS_tpLista )) ;
      if ( (*pLista) == NULL )
      {
        return LIS_CondRetFaltouMemoria ;
      } /* if */

	  (*pLista) = pListaM ;

	  return LIS_CondRetOK ;

   } /* Fim funcao: LIS  &Criar lista */

/***************************************************************************
*
*  Funcao: LIS  &Destruir lista
*  ****/

   LIS_tpCondRet LIS_DestruirLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      LIS_EsvaziarLista( pLista ) ;

      free( pLista ) ;

	  return LIS_CondRetOK ;

   } /* Fim funcao: LIS  &Destruir lista */

/***************************************************************************
*
*  Funcao: LIS  &Esvaziar lista
*  ****/

   LIS_tpCondRet LIS_EsvaziarLista( LIS_tppLista pLista )
   {
      tpElemLista * pElem ;
      tpElemLista * pProx ;

      if ( pLista == NULL )
      {
         return LIS_CondRetListaVazia;
      }

      pElem = pLista->pOrigemLista ;
      while ( pElem != NULL )
      {
         pProx = pElem->pProx ;
         LiberarElemento( pLista , pElem ) ;
         pElem = pProx ;
      } /* while */

      LimparCabeca( pLista ) ;
	  
	  return LIS_CondRetOK ;

   } /* Fim funcao: LIS  &Esvaziar lista */

/***************************************************************************
*
*  Funcao: LIS  &Inserir elemento antes
*  ****/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor        )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      tpElemLista * pElem ;


		/* Criar elemento a inserir antes */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL ){
            return LIS_CondRetFaltouMemoria ;
         } /* if */

		/* Encadear o elemento antes do elemento corrente */

         if ( pLista->pElemCorr == NULL ) {

            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;

         } else{

            if ( pLista->pElemCorr->pAnt != NULL ){
               pElem->pAnt  = pLista->pElemCorr->pAnt ;
               pLista->pElemCorr->pAnt->pProx = pElem ;
            } else{
               pLista->pOrigemLista = pElem ;
            } /* if */

            pElem->pProx = pLista->pElemCorr ;
            pLista->pElemCorr->pAnt = pElem ;
         } /* if */

         pLista->pElemCorr = pElem ;

         return LIS_CondRetOK ;

   } /* Fim funcao: LIS  &Inserir elemento antes */

/***************************************************************************
*
*  Funcao: LIS  &Inserir elemento apos
*  ****/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        )
      
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      tpElemLista * pElem ;

      /* Criar elemento a inerir apos */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL ){
            return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento apos o elemento */

         if ( pLista->pElemCorr == NULL ){

            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;

         } else{

            if ( pLista->pElemCorr->pProx != NULL ){
               pElem->pProx  = pLista->pElemCorr->pProx ;
               pLista->pElemCorr->pProx->pAnt = pElem ;
            } else{
               pLista->pFimLista = pElem ;
            } /* if */

            pElem->pAnt = pLista->pElemCorr ;
            pLista->pElemCorr->pProx = pElem ;

         } /* if */
                  
         pLista->pElemCorr = pElem ;
                  
         return LIS_CondRetOK ;

   } /* Fim funcao: LIS  &Inserir elemento apos */


/***************************************************************************
*
*  Funcao: LIS  &Checa se a origem e nula
*  ****/

LIS_tpCondRet LIS_ChecaOrigemNulo(LIS_tppLista pLista)
{

	#ifdef _DEBUG
         assert( pLista  != NULL ) ;
    #endif

	if(pLista->pOrigemLista == NULL){
		return LIS_CondRetListaVazia;
	} /* if */

	return LIS_CondRetOK;

}  /* Fim funcao: LIS  &Checa se a origem e nula */



/***************************************************************************
*
*  Funcao: LIS  &Excluir elemento
*  ****/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista )
   {
       
      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
      #endif


      tpElemLista * pElem ;

      if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */

      pElem = pLista->pElemCorr ;

      /* Desencadeia a esquerda */

         if ( pElem->pAnt != NULL ){
            pElem->pAnt->pProx   = pElem->pProx ;
            pLista->pElemCorr    = pElem->pAnt ;
         } else {
            pLista->pElemCorr    = pElem->pProx ;
            pLista->pOrigemLista = pLista->pElemCorr ;
         } /* if */

      /* Desencadeia a direita */

         if ( pElem->pProx != NULL ) {
            pElem->pProx->pAnt = pElem->pAnt ;
         } else {
            pLista->pFimLista = pElem->pAnt ;
         } /* if */

      LiberarElemento( pLista , pElem ) ;

      return LIS_CondRetOK ;

   } /* Fim funcao: LIS  &Excluir elemento */

/***************************************************************************
*
*  Funcao: LIS  &Obter referencia para o valor contido no elemento
*  ****/

   LIS_tpCondRet LIS_ObterValor( LIS_tppLista pLista , void **pContListaM )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL ){
		  return LIS_CondRetListaVazia ;
      } /* if */

      *pContListaM = pLista->pElemCorr->pValor ;

	  return LIS_CondRetOK ;

   } /* Fim funcao: LIS  &Obter referencia para o valor contido no elemento */

/***************************************************************************
*
*  Funcao: LIS  &Ir para o elemento inicial
*  ****/

   LIS_tpCondRet LIS_IrInicioLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif
	
	  if(pLista->pOrigemLista==NULL){
			return LIS_CondRetListaVazia;
      } /* if */

      pLista->pElemCorr = pLista->pOrigemLista ;

	  return LIS_CondRetOK ;

   } /* Fim funcao: LIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  Funcao: LIS  &Ir para o elemento final
*  ****/

   LIS_tpCondRet LIS_IrFinalLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif
      
	  if(pLista->pFimLista==NULL){
			return LIS_CondRetListaVazia;
      } /* if */

      pLista->pElemCorr = pLista->pFimLista ;

	  return LIS_CondRetOK ;

   } /* Fim funcao: LIS  &Ir para o elemento final */


/***************************************************************************
*
*  Funcao: LIS  &Numero de elementos
*  ****/

   LIS_tpCondRet LIS_NumElem( LIS_tppLista pLista , int * numElem )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif
	
	  (*numElem) = pLista->numElem;

	  return LIS_CondRetOK ;

   } /* Fim funcao: LIS  &Numero de elementos */

/***************************************************************************
*
*  Funcao: LIS  &Avancar elemento 
*  ****/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      int i ;

      tpElemLista * pElem ;


      /* Tratar lista vazia */

         if ( pLista->pElemCorr == NULL ){

            return LIS_CondRetListaVazia ;

         } /* fim ativa: Tratar lista vazia */

      /* Tratar avancar para frente */

         if ( numElem > 0 ) {

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i > 0 ; i-- ){
               if ( pElem == NULL ){
                  break ;
               } /* if */
               pElem    = pElem->pProx ;
            } /* for */

            if ( pElem != NULL ){
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pFimLista ;
            return LIS_CondRetFimLista ;

         } /*  fim ativa : Tratar avancar para frente */

      /* Tratar avancar para tras */

         else if ( numElem < 0 ){

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i < 0 ; i++ ) {
               if ( pElem == NULL ) {
                  break ;
               } /* if */
               pElem    = pElem->pAnt ;
            } /* for */

            if ( pElem != NULL ){
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pOrigemLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avancar para tras */

      /* Tratar nao avancar */

         return LIS_CondRetOK ;

   } /* Fim funcao: LIS  &Avancar elemento */

/***************************************************************************
*
*  Funcao: LIS  &Procurar elemento contendo valor
*  ****/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor ,
                                    int ( * ComparaValor ) ( void * pValorCorr , void * pValorBuscado ) )
   {

      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
      #endif
         
      tpElemLista * pElem ;


      if ( pLista->pElemCorr == NULL ){
         return LIS_CondRetListaVazia ;
      } /* if */

      for ( pElem  = pLista->pElemCorr ;
            pElem != NULL ;
            pElem  = pElem->pProx )
      {
         if ( ComparaValor( pElem->pValor , pValor ) == 0 ){
            pLista->pElemCorr = pElem ;
            return LIS_CondRetOK ;
         } /* if */
      } /* for */

      return LIS_CondRetNaoAchou ;

   } /* Fim funcao: LIS  &Procurar elemento contendo valor */


/************  Codigo das funcoes encapsuladas no modulo  *************/


/***********************************************************************
*
*  $FC Funcao: LIS  -Liberar elemento da lista
*
***********************************************************************/

   void LiberarElemento( LIS_tppLista   pLista ,
                         tpElemLista  * pElem   )
   {

      if ( ( pLista->ExcluirValor != NULL )
        && ( pElem->pValor != NULL        ))
      {
         pLista->ExcluirValor( pElem->pValor ) ;
      } /* if */

      free( pElem ) ;

      pLista->numElem-- ;

   } /* Fim funcao: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Funcao: LIS  -Criar o elemento sem encadeamento na estrutura
*
***********************************************************************/

   tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                void *       pValor  )
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

      pLista->numElem ++ ;

      return pElem ;

   } /* Fim funcao: LIS  -Criar o elemento */


/***********************************************************************
*
*  $FC Funcao: LIS  -Limpar a cabeca da lista
*
***********************************************************************/

   void LimparCabeca( LIS_tppLista pLista )
   {

      pLista->pOrigemLista = NULL ;
      pLista->pFimLista = NULL ;
      pLista->pElemCorr = NULL ;
      pLista->numElem   = 0 ;

   } /* Fim funcao: LIS  -Limpar a cabeca da lista */

/********** Fim do modulo de implementacao: LIS  Lista duplamente encadeada **********/

