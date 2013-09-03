/***************************************************************************
*  $MCI Módulo de implementação: Módulo árvore
*
*  Arquivo gerado:              MATRIZ.C
*  Letras identificadoras:      ARV
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: avs - Arndt von Staa
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       3.00   avs   28/02/2003 Uniformização da interface das funções e
*                               de todas as condições de retorno.
*       2.00   avs   03/08/2002 Eliminação de código duplicado, reestruturação
*       1.00   avs   15/08/2001 Início do desenvolvimento
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>

#define MATRIZ_OWN
#include "MATRIZ.H"
#undef MATRIZ_OWN

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor do nó da árvore
*
*
*  $ED Descrição do tipo
*     Descreve a organização do nó
*
***********************************************************************/

   typedef struct tgNoMATRIZ {

         struct tgNoMATRIZ * pNoPai ;
               /* Ponteiro para pai
               *
               *$EED Assertivas estruturais
               *   É NULL sse o nó é raiz
               *   Se não for raiz, um de pNoEsq ou pNoDir de pNoPai do nó
               *   corrente apontam para o nó corrente */

         struct tgNoMATRIZ * pNoEsq ;
               /* Ponteiro para filho à esquerda
               *
               *$EED Assertivas estruturais
               *   se pNoEsq do nó X != NULL então pNoPai de pNoEsq aponta para o nó X */

         struct tgNoMATRIZ * pNoDir ;
               /* Ponteiro para filho à direita
               *
               *$EED Assertivas estruturais
               *   se pNoDir do nó X != NULL então pNoPai de pNoDir aponta para o nó X */

         char Valor ;
               /* Valor do nó */

   } tpNoMATRIZ ;

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor da cabeça de uma árvore
*
*
*  $ED Descrição do tipo
*     A cabe‡a da árvore é o ponto de acesso para uma determinada árvore.
*     Por intermédio da referência para o nó corrente e do ponteiro
*     pai pode-se navegar a árvore sem necessitar de uma pilha.
*     Pode-se, inclusive, operar com a árvore em forma de co-rotina.
*
***********************************************************************/

   typedef struct tgMATRIZ {

         tpNoMATRIZ * pNoRaiz ;
               /* Ponteiro para a raiz da árvore */

         tpNoMATRIZ * pNoCorr ;
               /* Ponteiro para o nó corrente da árvore */

   } tpMATRIZ ;

/*****  Dados encapsulados no módulo  *****/

      static tpMATRIZ * pMATRIZ = NULL ;
            /* Ponteiro para a cabe‡a da árvore */

/***** Protótipos das funções encapuladas no módulo *****/

   static tpNoMATRIZ * CriarNo( char ValorParm ) ;

   static ARV_tpCondRet CriarNoRaiz( char ValorParm ) ;

   static void DestroiMATRIZ( tpNoMATRIZ * pNo ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: ARV Criar árvore
*  ****/

   ARV_tpCondRet ARV_CriarMATRIZ( void )
   {

      if ( pMATRIZ != NULL )
      {
         ARV_DestruirMATRIZ( ) ;
      } /* if */

      pMATRIZ = ( tpMATRIZ * ) malloc( sizeof( tpMATRIZ )) ;
      if ( pMATRIZ == NULL )
      {
         return ARV_CondRetFaltouMemoria ;
      } /* if */

      pMATRIZ->pNoRaiz = NULL ;
      pMATRIZ->pNoCorr = NULL ;

      return ARV_CondRetOK ;

   } /* Fim função: ARV Criar árvore */

/***************************************************************************
*
*  Função: ARV Destruir árvore
*  ****/

   void ARV_DestruirMATRIZ( void )
   {

      if ( pMATRIZ != NULL )
      {
         if ( pMATRIZ->pNoRaiz != NULL )
         {
            DestroiMATRIZ( pMATRIZ->pNoRaiz ) ;
         } /* if */
         free( pMATRIZ ) ;
         pMATRIZ = NULL ;
      } /* if */

   } /* Fim função: ARV Destruir árvore */

/***************************************************************************
*
*  Função: ARV Adicionar filho à esquerda
*  ****/

   ARV_tpCondRet ARV_InserirEsquerda( char ValorParm )
   {

      ARV_tpCondRet CondRet ;

      tpNoMATRIZ * pCorr ;
      tpNoMATRIZ * pNo ;

      /* Tratar vazio, esquerda */

         CondRet = CriarNoRaiz( ValorParm ) ;
         if ( CondRet != ARV_CondRetNaoCriouRaiz )
         {
            return CondRet ;
         } /* if */

      /* Criar nó à esquerda de folha */

         pCorr = pMATRIZ->pNoCorr ;
         if ( pCorr == NULL )
         {
            return ARV_CondRetErroEstrutura ;
         } /* if */
               
         if ( pCorr->pNoEsq == NULL )
         {
            pNo = CriarNo( ValorParm ) ;
            if ( pNo == NULL )
            {
               return ARV_CondRetFaltouMemoria ;
            } /* if */
            pNo->pNoPai      = pCorr ;
            pCorr->pNoEsq    = pNo ;
            pMATRIZ->pNoCorr = pNo ;

            return ARV_CondRetOK ;
         } /* if */

      /* Tratar não folha à esquerda */

         return ARV_CondRetNaoEhFolha ;

   } /* Fim função: ARV Adicionar filho à esquerda */

/***************************************************************************
*
*  Função: ARV Adicionar filho à direita
*  ****/

   ARV_tpCondRet ARV_InserirDireita( char ValorParm )
   {

      ARV_tpCondRet CondRet ;

      tpNoMATRIZ * pCorr ;
      tpNoMATRIZ * pNo ;

      /* Tratar vazio, direita */

         CondRet = CriarNoRaiz( ValorParm ) ;
         if ( CondRet != ARV_CondRetNaoCriouRaiz )
         {
            return CondRet ;
         } /* if */

      /* Criar nó à direita de folha */

         pCorr = pMATRIZ->pNoCorr ;
         if ( pCorr == NULL )
         {
            return ARV_CondRetErroEstrutura ;
         } /* if */

         if ( pCorr->pNoDir == NULL )
         {
            pNo = CriarNo( ValorParm ) ;
            if ( pNo == NULL )
            {
               return ARV_CondRetFaltouMemoria ;
            } /* if */
            pNo->pNoPai      = pCorr ;
            pCorr->pNoDir    = pNo ;
            pMATRIZ->pNoCorr = pNo ;

            return ARV_CondRetOK ;
         } /* if */

      /* Tratar não folha à direita */

         return ARV_CondRetNaoEhFolha ;

   } /* Fim função: ARV Adicionar filho à direita */

/***************************************************************************
*
*  Função: ARV Ir para nó pai
*  ****/

   ARV_tpCondRet ARV_IrPai( void )
   {

      if ( pMATRIZ == NULL )
      {
         return ARV_CondRetMATRIZNaoExiste ;
      } /* if */
      if ( pMATRIZ->pNoCorr == NULL )
      {
         return ARV_CondRetMATRIZVazia ;
      } /* if */

      if ( pMATRIZ->pNoCorr->pNoPai != NULL )
      {
         pMATRIZ->pNoCorr = pMATRIZ->pNoCorr->pNoPai ;
         return ARV_CondRetOK ;
      } else {
         return ARV_CondRetNohEhRaiz ;
      } /* if */

   } /* Fim função: ARV Ir para nó pai */

/***************************************************************************
*
*  Função: ARV Ir para nó à esquerda
*  ****/

   ARV_tpCondRet ARV_IrNoEsquerda( void )
   {

      if ( pMATRIZ == NULL )
      {
         return ARV_CondRetMATRIZNaoExiste ;
      } /* if */

      if ( pMATRIZ->pNoCorr == NULL )
      {
         return ARV_CondRetMATRIZVazia ;
      } /* if */

      if ( pMATRIZ->pNoCorr->pNoEsq == NULL )
      {
         return ARV_CondRetNaoPossuiFilho ;
      } /* if */

      pMATRIZ->pNoCorr = pMATRIZ->pNoCorr->pNoEsq ;
      return ARV_CondRetOK ;

   } /* Fim função: ARV Ir para nó à esquerda */

/***************************************************************************
*
*  Função: ARV Ir para nó à direita
*  ****/

   ARV_tpCondRet ARV_IrNoDireita( void )
   {

      if ( pMATRIZ == NULL )
      {
         return ARV_CondRetMATRIZNaoExiste ;
      } /* if */

      if ( pMATRIZ->pNoCorr == NULL )
      {
         return ARV_CondRetMATRIZVazia ;
      } /* if */

      if ( pMATRIZ->pNoCorr->pNoDir == NULL )
      {
         return ARV_CondRetNaoPossuiFilho ;
      } /* if */

      pMATRIZ->pNoCorr = pMATRIZ->pNoCorr->pNoDir ;
      return ARV_CondRetOK ;

   } /* Fim função: ARV Ir para nó à direita */

/***************************************************************************
*
*  Função: ARV Obter valor corrente
*  ****/

   ARV_tpCondRet ARV_ObterValorCorr( char * ValorParm )
   {

      if ( pMATRIZ == NULL )
      {
         return ARV_CondRetMATRIZNaoExiste ;
      } /* if */
      if ( pMATRIZ->pNoCorr == NULL )
      {
         return ARV_CondRetMATRIZVazia ;
      } /* if */
      * ValorParm = pMATRIZ->pNoCorr->Valor ;

      return ARV_CondRetOK ;

   } /* Fim função: ARV Obter valor corrente */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: ARV Criar nó da árvore
*
*  $FV Valor retornado
*     Ponteiro para o nó criado.
*     Será NULL caso a memória tenha se esgotado.
*     Os ponteiros do nó criado estarão nulos e o valor é igual ao do
*     parâmetro.
*
***********************************************************************/

   tpNoMATRIZ * CriarNo( char ValorParm )
   {

      tpNoMATRIZ * pNo ;

      pNo = ( tpNoMATRIZ * ) malloc( sizeof( tpNoMATRIZ )) ;
      if ( pNo == NULL )
      {
         return NULL ;
      } /* if */

      pNo->pNoPai = NULL ;
      pNo->pNoEsq = NULL ;
      pNo->pNoDir = NULL ;
      pNo->Valor  = ValorParm ;
      return pNo ;

   } /* Fim função: ARV Criar nó da árvore */


/***********************************************************************
*
*  $FC Função: ARV Criar nó raiz da árvore
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetFaltouMemoria
*     ARV_CondRetNaoCriouRaiz
*
***********************************************************************/

   ARV_tpCondRet CriarNoRaiz( char ValorParm )
   {

      ARV_tpCondRet CondRet ;
      tpNoMATRIZ * pNo ;

      if ( pMATRIZ == NULL )
      {
         CondRet = ARV_CriarMATRIZ( ) ;

         if ( CondRet != ARV_CondRetOK )
         {
            return CondRet ;
         } /* if */
      } /* if */

      if ( pMATRIZ->pNoRaiz == NULL )
      {
         pNo = CriarNo( ValorParm ) ;
         if ( pNo == NULL )
         {
            return ARV_CondRetFaltouMemoria ;
         } /* if */
         pMATRIZ->pNoRaiz = pNo ;
         pMATRIZ->pNoCorr = pNo ;

         return ARV_CondRetOK ;
      } /* if */

      return ARV_CondRetNaoCriouRaiz ;

   } /* Fim função: ARV Criar nó raiz da árvore */


/***********************************************************************
*
*  $FC Função: ARV Destruir a estrutura da árvore
*
*  $EAE Assertivas de entradas esperadas
*     pNoMATRIZ != NULL
*
***********************************************************************/

   void DestroiMATRIZ( tpNoMATRIZ * pNo )
   {

      if ( pNo->pNoEsq != NULL )
      {
         DestroiMATRIZ( pNo->pNoEsq ) ;
      } /* if */

      if ( pNo->pNoDir != NULL )
      {
         DestroiMATRIZ( pNo->pNoDir ) ;
      } /* if */

      free( pNo ) ;

   } /* Fim função: ARV Destruir a estrutura da árvore */

/********** Fim do módulo de implementação: Módulo árvore **********/

