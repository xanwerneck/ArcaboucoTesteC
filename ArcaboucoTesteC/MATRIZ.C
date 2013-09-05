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
#include "LISTA.H"

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

   typedef struct tpElemMatriz {

         struct tpElemMatriz * pNoNoroeste ; // fe: Adjacente da quina superior esquerda.
               /* Ponteiro para pai
               *
               *$EED Assertivas estruturais
               *   É NULL sse o nó é raiz
               *   Se não for raiz, um de pNoEsq ou pNoDir de pNoPai do nó
               *   corrente apontam para o nó corrente */

         struct tpElemMatriz * pNoNorte ; // fe: Adjacente de cima.
               /* Ponteiro para pai
               *
               *$EED Assertivas estruturais
               *   É NULL sse o nó é raiz
               *   Se não for raiz, um de pNoEsq ou pNoDir de pNoPai do nó
               *   corrente apontam para o nó corrente */

         struct tpElemMatriz * pNoNordeste ; // fe: Adjacente da quina superior direita.
               /* Ponteiro para pai
               *
               *$EED Assertivas estruturais
               *   É NULL sse o nó é raiz
               *   Se não for raiz, um de pNoEsq ou pNoDir de pNoPai do nó
               *   corrente apontam para o nó corrente */

         struct tpElemMatriz * pNoOeste ; // fe: Adjacente da esqueda.
               /* Ponteiro para pai
               *
               *$EED Assertivas estruturais
               *   É NULL sse o nó é raiz
               *   Se não for raiz, um de pNoEsq ou pNoDir de pNoPai do nó
               *   corrente apontam para o nó corrente */

         struct tpElemMatriz * pNoLeste ; // fe: Adjacente da direita.
               /* Ponteiro para pai
               *
               *$EED Assertivas estruturais
               *   É NULL sse o nó é raiz
               *   Se não for raiz, um de pNoEsq ou pNoDir de pNoPai do nó
               *   corrente apontam para o nó corrente */

         struct tpElemMatriz * pNoSudoeste ; // fe: Adjacente da quina inferior esquerda.
               /* Ponteiro para pai
               *
               *$EED Assertivas estruturais
               *   É NULL sse o nó é raiz
               *   Se não for raiz, um de pNoEsq ou pNoDir de pNoPai do nó
               *   corrente apontam para o nó corrente */

         struct tpElemMatriz * pNoSul ; // fe: Adjacente de baixo.
               /* Ponteiro para pai
               *
               *$EED Assertivas estruturais
               *   É NULL sse o nó é raiz
               *   Se não for raiz, um de pNoEsq ou pNoDir de pNoPai do nó
               *   corrente apontam para o nó corrente */

         struct tpElemMatriz * pNoSudeste ; // fe: Adjacente da quina inferior direita.
               /* Ponteiro para pai
               *
               *$EED Assertivas estruturais
               *   É NULL sse o nó é raiz
               *   Se não for raiz, um de pNoEsq ou pNoDir de pNoPai do nó
               *   corrente apontam para o nó corrente */


         struct LIS_tppLista * Lista;

   } tpElemMatriz ;

   // fe: Mudei os nomes de tipos e variáveis de Arvore para Matriz
   // fe: Mudei os elementos pNoPai, pNoEsq, pNoDir e Valor; Apaguei e criei a estrutura da Matriz.


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

   typedef struct tgMatriz {

         tpElemMatriz * pNoRaiz ;
               /* Ponteiro para a raiz da árvore */

         tpElemMatriz * pNoCorr ;
               /* Ponteiro para o nó corrente da árvore */

   } tpMatriz ;


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


MAT_tpCondRet MAT_CriarMatriz( void ){

	   int i=0, j=0;

	   tpMatriz * tpMat = (tpMatriz *) malloc(sizeof(tpMatriz));
	   tpMat->pNoCorr = NULL;
	   tpMat->pNoRaiz = NULL;

	   LIS_tppLista * lista = (LIS_tppLista *) malloc (sizeof(LIS_tppLista));

	   for(;i<num;i++)
		   for(;j<num;j++)
			   MAT_CriarElementoMatriz(tpMat,lista,i,j, num-1);
}


  MAT_tpCondRet MAT_CriarElementoMatriz(tpMatriz * tpMat, LIS_tppLista * lt, int i, int j, int num){

	   tpElemMatriz * tpElem = (tpElemMatriz *) malloc(sizeof(tpElemMatriz));
	   
	   tpElem->Lista = lt;

	   //checa se a matriz é um por um
	   if(num == 1){
		   tpElem->Lista = lt;
		   tpMat->pNoCorr  = tpElem;
		   tpMat->pNoRaiz  = tpElem;
	   }

	   //if que testa a condicão para 3 adjacentes
	   if((i==0 || j==0) && (i==num || j==num)){

		   if(i==0 && j==0){
				tpMat->pNoCorr  = tpElem;
				tpMat->pNoRaiz  = tpElem;

				tpElemMatriz * tpElemLesteCabeca   = (tpElemMatriz *) malloc(sizeof(tpElemMatriz));
				tpElemMatriz * tpElemSudesteCabeca = (tpElemMatriz *) malloc(sizeof(tpElemMatriz));
				tpElemMatriz * tpElemSulCabeca     = (tpElemMatriz *) malloc(sizeof(tpElemMatriz));

				tpElem->pNoLeste   = tpElemLesteCabeca;
				tpElem->pNoSudeste = tpElemSudesteCabeca;
				tpElem->pNoSul     = tpElemSulCabeca;
		   }
		   if(i==0 && j==num){

				tpElem->pNoSul      = tpMat->pNoCorr->pNoSudeste;
				tpElem->pNoSudoeste = tpMat->pNoCorr->pNoSul;
				tpElem->pNoOeste    = tpMat->pNoCorr;

				// no final sta como corrente
				tpMat->pNoCorr  = tpElem;
				tpMat->pNoRaiz  = tpElem;

		   }
		   if(i==num && j==0){

			   tpElem->pNoNorte    = tpMat->pNoRaiz;
			   tpElem->pNoNordeste = tpMat->pNoRaiz->pNoLeste;
			   tpElem->pNoLeste    = tpMat->pNoRaiz->pNoSudeste;

				// no final sta como corrente
				tpMat->pNoCorr  = tpElem;

		   }
		   if(i==num && j==num){

			   tpElem->pNoNorte     = tpMat->pNoCorr->pNoNordeste;
			   tpElem->pNoNoroeste  = tpMat->pNoCorr->pNoNorte;
			   tpElem->pNoOeste     = tpMat->pNoCorr;

				// no final sta como corrente
				tpMat->pNoCorr  = tpElem;
				tpMat->pNoRaiz  = tpElem;

		   }

	   }

	   //if que testa a condição para 5 adjacentes
	   else if(i==0 || i==num || j==0 || j==num){


		   if(i==0 && (j!=num || j!=0)){
			    
				tpElemMatriz * tpElemLesteNo   = (tpElemMatriz *) malloc(sizeof(tpElemMatriz));
				tpElemMatriz * tpElemSudesteNo = (tpElemMatriz *) malloc(sizeof(tpElemMatriz));

				tpElem->pNoLeste    = tpElemLesteNo;
				tpElem->pNoSudeste  = tpElemSudesteNo;
				tpElem->pNoSul      = tpMat->pNoCorr->pNoSudeste;
				tpElem->pNoSudoeste = tpMat->pNoCorr->pNoSul;
				tpElem->pNoOeste    = tpMat->pNoCorr;

				// no final sta como corrente
				tpMat->pNoCorr  = tpElem;

		   }
		   if(j==0 && (i!=num || i!=0)){

			    tpElemMatriz * tpElemSulNo     = (tpElemMatriz *) malloc(sizeof(tpElemMatriz));
				tpElemMatriz * tpElemSudesteNo = (tpElemMatriz *) malloc(sizeof(tpElemMatriz));

				tpElem->pNoSudeste  = tpElemSudesteNo;
				tpElem->pNoSul      = tpElemSulNo;
				tpElem->pNoLeste    = tpMat->pNoCorr->pNoSudeste;				
				tpElem->pNoNordeste = tpMat->pNoCorr->pNoLeste;
				tpElem->pNoNorte    = tpMat->pNoCorr;

				// no final sta como corrente
				tpMat->pNoCorr  = tpElem;

		   }
		   if(i==num && (j!=num || j!=0)){
			    
				tpElemMatriz * tpElemLesteNo   = (tpElemMatriz *) malloc(sizeof(tpElemMatriz));

				tpElem->pNoLeste    = tpElemLesteNo;
				tpElem->pNoNordeste = tpMat->pNoCorr->pNoNordeste->pNoLeste;
				tpElem->pNoNorte    = tpMat->pNoCorr->pNoNordeste;
				tpElem->pNoNoroeste = tpMat->pNoCorr->pNoNorte;
				tpElem->pNoOeste    = tpMat->pNoCorr->pNoNoroeste;

				// no final sta como corrente
				tpMat->pNoCorr  = tpElem;

		   }
		   if(j==num && (i!=num || i!=0)){

			    tpElemMatriz * tpElemLesteNo   = (tpElemMatriz *) malloc(sizeof(tpElemMatriz));

				tpElem->pNoNorte     = tpMat->pNoCorr->pNoNoroeste;
				tpElem->pNoSul       = tpMat->pNoCorr->pNoSudeste;
				tpElem->pNoSudoeste  = tpMat->pNoCorr->pNoSul;
				tpElem->pNoOeste     = tpMat->pNoCorr;
				tpElem->pNoNoroeste  = tpMat->pNoCorr->pNoNorte;

				// no final sta como corrente
				tpMat->pNoCorr  = tpElem;

		   }

	   }
	   //else com 8 adjacentes
	   else{

				tpElemMatriz * tpElemSudesteNo   = (tpElemMatriz *) malloc(sizeof(tpElemMatriz));

		        tpElem->pNoNorte     = tpMat->pNoCorr->pNoNoroeste;
				tpElem->pNoNordeste  = tpMat->pNoCorr->pNoNordeste->pNoLeste;
				tpElem->pNoLeste     = tpMat->pNoCorr->pNoNordeste->pNoLeste->pNoSul;
				tpElem->pNoSudeste   = tpElemSudesteNo;
				tpElem->pNoSul       = tpMat->pNoCorr->pNoSudeste;
				tpElem->pNoSudoeste  = tpMat->pNoCorr->pNoSul;
				tpElem->pNoOeste     = tpMat->pNoCorr;
				tpElem->pNoNoroeste  = tpMat->pNoCorr->pNoNorte;

	   }
	   

   }


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

