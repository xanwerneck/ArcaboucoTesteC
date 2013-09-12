/***************************************************************************
*  $MCI Módulo de implementação: Módulo MATRIZ
*
*  Arquivo gerado:              MATRIZ.C
*  Letras identificadoras:      MAT
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: INF 1301 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: aw - Alexandre Werneck
*           fe - Fernanda Ribeiro
*			vi - Vinicius
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       1.00   aw   29/08/2013 Início do desenvolvimento
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
*  $TC Tipo de dados: MAT Descritor do elemento da matriz - 05/09/2013
*
*
*  $ED Descrição do tipo
*     Descreve a organização do elemento
*
***********************************************************************/

typedef struct tpElemMatriz {

        struct tpElemMatriz * pNoNoroeste ; 
			/* Adjacente da quina superior esquerda */
		
        struct tpElemMatriz * pNoNorte ;
			/* Adjacente de cima */

        struct tpElemMatriz * pNoNordeste ;
            /* Adjacente da quina superior direita */
            
        struct tpElemMatriz * pNoOeste ; 
            /* Adjacente da esqueda */
            
        struct tpElemMatriz * pNoLeste ;
            /* Adjacente da direita */

        struct tpElemMatriz * pNoSudoeste ;
            /* Adjacente da quina inferior esquerda */
            
        struct tpElemMatriz * pNoSul ;
            /* Adjacente de baixo */

        struct tpElemMatriz * pNoSudeste ;
            /* Adjacente da quina inferior direita */

        struct LIS_tppLista * Lista;
			/* Lista para o elemento da Matriz que armazena caracteres */

} tpElemMatriz ;

   // fe: Mudei os nomes de tipos e variáveis de Arvore para Matriz
   // fe: Mudei os elementos pNoPai, pNoEsq, pNoDir e Valor; Apaguei e criei a estrutura da Matriz.


/***********************************************************************
*
*  $TC Tipo de dados: MAT Descritor da raiz de uma matriz
*
*
*  $ED Descrição do tipo
*	  A raiz da matriz indica o início da matriz , refere-se ao elemento (0,0)
*	  A estrutura matriz também armazena uma referência ao nó indíce 
*	  de coluna para a criação da matriz.
*	  Através do nó corrente pode-se navegar a matriz.
*
***********************************************************************/

typedef struct MAT_tgMatriz {

        tpElemMatriz * pNoRaiz ;
            /* Ponteiro para a raiz da matriz */

		tpElemMatriz * pNoIndLinha ;
            /* Ponteiro para a indice de linha da matriz */

        tpElemMatriz * pNoCorr ;
            /* Ponteiro para o nó corrente da matriz */

} MAT_tpMatriz ;


/*****  Dados encapsulados no módulo  *****/


/***** Protótipos das funções encapsuladas no módulo *****/

static MAT_tpCondRet PreparaEstruturaMatriz( MAT_tpMatriz * tpMat , int numElementos ) ;

static MAT_tpCondRet CriarNoRaiz( MAT_tpMatriz * tpMat , int numElementos ) ;

static void DestroiMatriz( MAT_tpMatriz * tpMatExc ) ;

static void DestroiNoMatriz( MAT_tpMatriz * tpMatExc );

static tpElemMatriz * CriarNo( ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: MAT CriarMatriz - 05/09/2013
*  
****/

MAT_tpCondRet MAT_CriarMatriz( MAT_tppMatriz *tpMat , int numElementos){
	   
		MAT_tpCondRet CondRet ;

		MAT_tppMatriz mMatriz ;

		if((*tpMat) != NULL)
		{
			DestroiMatriz( (*tpMat) ); 
		} /* if */
		
		mMatriz = ( MAT_tppMatriz ) malloc ( sizeof ( MAT_tpMatriz ) );
			/* Malloc para gerar um ponteiro temporario */

		   
	   if(mMatriz == NULL)
	   {
		   return MAT_CondRetFaltouMemoria ;
	   } /* if */
	   
	   mMatriz->pNoCorr      = NULL;
	   mMatriz->pNoRaiz      = NULL;
	   mMatriz->pNoIndLinha  = NULL;

	   CondRet = CriarNoRaiz(mMatriz , numElementos);
			 /* Inicializo a estrutura da matriz setando a raiz */

	   if(CondRet != MAT_CondRetOK)
	   {
		return CondRet;
	   } /* if */


	   (*tpMat) = ( MAT_tpMatriz* ) malloc( sizeof( MAT_tppMatriz )) ;

		if ( (*tpMat) == NULL )
		{
			return MAT_CondRetFaltouMemoria ;
		} /* if */

		(*tpMat) = mMatriz ;


		return MAT_CondRetOK ;
}


/***************************************************************************
*
*  Função: MAT InsereListaMatriz - 05/09/2013
*
*	Percorre a estrutura da matriz procurando espaço vazio para
*	armazenar a lista criada.
*  
****/

MAT_tpCondRet MAT_InsereListaMatriz( LIS_tppLista * lt, MAT_tpMatriz * tpMat){

	if( lt == NULL ){
		return MAT_CondRetListaVazia ;
	} /* if */

	if ( tpMat == NULL )
    {
        return MAT_CondRetMatrizVazia ; // Devemos apresentar a mensagem de que a matriz deverá ser montada antes
    } /* if */

	tpMat->pNoCorr     = tpMat->pNoRaiz;
	tpMat->pNoIndLinha = tpMat->pNoCorr;

	// procura a próxima posição de memória vazia para inserir a lista
	while(tpMat->pNoCorr != NULL){
		if(tpMat->pNoCorr->Lista == NULL){
				tpMat->pNoCorr->Lista = lt;
				return MAT_CondRetOK; // Como interrompo o while
		}else{
			if(tpMat->pNoCorr->pNoLeste == NULL){
				tpMat->pNoCorr     = tpMat->pNoIndLinha->pNoSul;
				tpMat->pNoIndLinha = tpMat->pNoCorr;
			}else{
				tpMat->pNoCorr = tpMat->pNoCorr->pNoLeste;
			} /* if */
		}/* if */
	}
	return MAT_CondRetMatrizCheia ; // retorno que a matriz está cheia

}

/***************************************************************************
*
*  Função: MAT IrNoNorte - 05/09/2013
*  
****/
   
MAT_tpCondRet MAT_IrNoNorte(MAT_tpMatriz * tpMat){

	  if ( tpMat == NULL )
      {
         return MAT_CondRetMatrizNaoExiste ;
      } /* if */

      if ( tpMat->pNoCorr == NULL )
      {
         return MAT_CondRetMatrizVazia ;
      } /* if */

	  if ( tpMat->pNoCorr->pNoNorte == NULL )
      {
         return MAT_CondRetNaoPossuiNo ;
      } /* if */

      tpMat->pNoCorr = tpMat->pNoCorr->pNoNorte ;

      return MAT_CondRetOK ;

} /* Fim do IrNoNorte */

/***************************************************************************
*
*  Função: MAT IrNoNordeste - 05/09/2013
*  
****/
   
MAT_tpCondRet MAT_IrNoNordeste(MAT_tpMatriz * tpMat){

	  if ( tpMat == NULL )
      {
         return MAT_CondRetMatrizNaoExiste ;
      } /* if */

      if ( tpMat->pNoCorr == NULL )
      {
         return MAT_CondRetMatrizVazia ;
      } /* if */

	  if ( tpMat->pNoCorr->pNoNordeste == NULL )
      {
         return MAT_CondRetNaoPossuiNo ;
      } /* if */

      tpMat->pNoCorr = tpMat->pNoCorr->pNoNordeste ;

      return MAT_CondRetOK ;

} /* Fim do IrNoNordeste */

/***************************************************************************
*
*  Função: MAT IrNoLeste - 05/09/2013
*  
****/
   
MAT_tpCondRet MAT_IrNoLeste(MAT_tpMatriz * tpMat){

	  if ( tpMat == NULL )
      {
         return MAT_CondRetMatrizNaoExiste ;
      } /* if */

      if ( tpMat->pNoCorr == NULL )
      {
         return MAT_CondRetMatrizVazia ;
      } /* if */

	  if ( tpMat->pNoCorr->pNoLeste == NULL )
      {
         return MAT_CondRetNaoPossuiNo ;
      } /* if */

	  tpMat->pNoCorr = tpMat->pNoCorr->pNoLeste ;

      return MAT_CondRetOK ;

} /* Fim do MAT IrNoLeste */

/***************************************************************************
*
*  Função: MAT IrNoSudeste - 05/09/2013
*  
****/
   
MAT_tpCondRet MAT_IrNoSudeste(MAT_tpMatriz * tpMat){

	  if ( tpMat == NULL )
      {
         return MAT_CondRetMatrizNaoExiste ;
      } /* if */

      if ( tpMat->pNoCorr == NULL )
      {
         return MAT_CondRetMatrizVazia ;
      } /* if */

	  if ( tpMat->pNoCorr->pNoSudeste == NULL )
      {
         return MAT_CondRetNaoPossuiNo ;
      } /* if */

      tpMat->pNoCorr = tpMat->pNoCorr->pNoSudeste ;

      return MAT_CondRetOK ;

} /* Fim do MAT IrNoSudeste */

/***************************************************************************
*
*  Função: MAT IrNoSul - 05/09/2013
*  
****/
   
MAT_tpCondRet MAT_IrNoSul(MAT_tpMatriz * tpMat){

	  if ( tpMat == NULL )
      {
         return MAT_CondRetMatrizNaoExiste ;
      } /* if */

      if ( tpMat->pNoCorr == NULL )
      {
         return MAT_CondRetMatrizVazia ;
      } /* if */

	  if ( tpMat->pNoCorr->pNoSul == NULL )
      {
         return MAT_CondRetNaoPossuiNo ;
      } /* if */

      tpMat->pNoCorr = tpMat->pNoCorr->pNoSul ;

      return MAT_CondRetOK ;

} /* Fim do MAT IrNoSul */

/***************************************************************************
*
*  Função: MAT IrNoSudoeste - 05/09/2013
*  
****/
   
MAT_tpCondRet MAT_IrNoSudoeste(MAT_tpMatriz * tpMat){

	  if ( tpMat == NULL )
      {
         return MAT_CondRetMatrizNaoExiste ;
      } /* if */

      if ( tpMat->pNoCorr == NULL )
      {
         return MAT_CondRetMatrizVazia ;
      } /* if */

	  if ( tpMat->pNoCorr->pNoSudoeste == NULL )
      {
         return MAT_CondRetNaoPossuiNo ;
      } /* if */

      tpMat->pNoCorr = tpMat->pNoCorr->pNoSudoeste ;

      return MAT_CondRetOK ;

} /* Fim do MAT IrNoSudoeste */

/***************************************************************************
*
*  Função: MAT IrNoOeste - 05/09/2013
*  
****/
   
MAT_tpCondRet MAT_IrNoOeste(MAT_tpMatriz * tpMat){

	  if ( tpMat == NULL )
      {
         return MAT_CondRetMatrizNaoExiste ;
      } /* if */

      if ( tpMat->pNoCorr == NULL )
      {
         return MAT_CondRetMatrizVazia ;
      } /* if */

	  if ( tpMat->pNoCorr->pNoOeste == NULL )
      {
         return MAT_CondRetNaoPossuiNo ;
      } /* if */

      tpMat->pNoCorr = tpMat->pNoCorr->pNoOeste ;

      return MAT_CondRetOK ;

} /* Fim do MAT IrNoOeste */

/***************************************************************************
*
*  Função: MAT IrNoNoroeste - 05/09/2013
*  
****/
   
MAT_tpCondRet MAT_IrNoNoroeste(MAT_tpMatriz * tpMat){

	  if ( tpMat == NULL )
      {
         return MAT_CondRetMatrizNaoExiste ;
      } /* if */

      if ( tpMat->pNoCorr == NULL )
      {
         return MAT_CondRetMatrizVazia ;
      } /* if */

	  if ( tpMat->pNoCorr->pNoNoroeste == NULL )
      {
         return MAT_CondRetNaoPossuiNo ;
      } /* if */

      tpMat->pNoCorr = tpMat->pNoCorr->pNoNoroeste ;

      return MAT_CondRetOK ;

} /* Fim do MAT IrNoNoroeste */




/***************************************************************************
*
*  Função: MAT Obter Lista corrente
*  ****/

MAT_tpCondRet MAT_ObterListaCorr( LIS_tppLista * lst_valor , MAT_tpMatriz * tpMat)
{

    if ( tpMat == NULL )
    {
        return MAT_CondRetMatrizNaoExiste  ;
    } /* if */
	if ( tpMat->pNoCorr == NULL )
    {
        return MAT_CondRetMatrizVazia ;
    } /* if */
	if ( tpMat->pNoCorr->Lista == NULL )
    {
        return MAT_CondRetNoMatrizSemLista ;
    } /* if */
    lst_valor = tpMat->pNoCorr->Lista ;

    return MAT_CondRetOK  ;

} /* Fim função: MAT Obter Lista corrente */


/***************************************************************************
*
*  Função: MAT Ir para nó raiz
*  ****/

MAT_tpCondRet MAT_IrRaiz( MAT_tpMatriz * tpMat )
{

    if ( tpMat == NULL )
    {
        return MAT_CondRetMatrizNaoExiste  ;
    } /* if */
    if ( tpMat->pNoCorr == NULL )
    {
        return MAT_CondRetMatrizVazia ;
    } /* if */

    if ( tpMat->pNoRaiz != NULL )
    {
		tpMat->pNoCorr = tpMat->pNoRaiz ;
        return MAT_CondRetOK ;
    } else {
        return MAT_CondRetNohEhRaiz ;
    } /* if */

} /* Fim função: MAT Ir para nó raiz */


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: MAT Destruir a estrutura da matriz
*		Chamada recursiva que percorre os elementos do nó corrente
*		da um free quando chega no último elemento
*
*  $EAE Assertivas de entradas esperadas
*     pMatriz != NULL
*
***********************************************************************/

void DestroiMatriz( MAT_tpMatriz * tpMatExc )
   {

	   if ( tpMatExc != NULL )
      {
         if ( tpMatExc->pNoCorr != NULL )
         {
			 DestroiNoMatriz( tpMatExc ) ;
         } /* if */
         free( tpMatExc ) ;
         tpMatExc = NULL ;
      } /* if */

	   

   } /* Fim função: MAT Destruir a estrutura da matriz */

/***********************************************************************
*
*  $FC Função: MAT Destruir a estrutura da matriz
*		Chamada recursiva que percorre os elementos do nó corrente
*		da um free quando chega no último elemento
*
*  $EAE Assertivas de entradas esperadas
*     pMatriz != NULL
*
***********************************************************************/

void DestroiNoMatriz( MAT_tpMatriz * tpMatExc )
   {

	  if ( tpMatExc->pNoCorr->pNoSudeste != NULL )
      {
		 tpMatExc->pNoCorr = tpMatExc->pNoCorr->pNoSudeste;
         free(tpMatExc->pNoCorr->pNoSudeste);
		 DestroiNoMatriz( tpMatExc ) ;
      } /* if */

	  if ( tpMatExc->pNoCorr->pNoSul != NULL )
      {
         tpMatExc->pNoCorr = tpMatExc->pNoCorr->pNoSul;
         free(tpMatExc->pNoCorr->pNoSul);
		 DestroiNoMatriz( tpMatExc ) ;
      } /* if */

	  if ( tpMatExc->pNoCorr->pNoSudoeste != NULL )
      {
         tpMatExc->pNoCorr = tpMatExc->pNoCorr->pNoSudoeste;
         free(tpMatExc->pNoCorr->pNoSudoeste);
		 DestroiNoMatriz( tpMatExc ) ;
      } /* if */

	  if ( tpMatExc->pNoCorr->pNoLeste != NULL )
      {
         tpMatExc->pNoCorr = tpMatExc->pNoCorr->pNoLeste;
		 free(tpMatExc->pNoCorr->pNoLeste);
		 DestroiNoMatriz( tpMatExc ) ;
      } /* if */

	  if ( tpMatExc->pNoCorr->pNoOeste != NULL )
      {
         tpMatExc->pNoCorr = tpMatExc->pNoCorr->pNoOeste;
         free(tpMatExc->pNoCorr->pNoOeste);
		 DestroiNoMatriz( tpMatExc ) ;
      } /* if */

	  if ( tpMatExc->pNoCorr->pNoNordeste != NULL )
      {
         tpMatExc->pNoCorr = tpMatExc->pNoCorr->pNoNordeste;
         free(tpMatExc->pNoCorr->pNoNordeste);
		 DestroiNoMatriz( tpMatExc ) ;
      } /* if */

	  if ( tpMatExc->pNoCorr->pNoNorte != NULL )
      {
         tpMatExc->pNoCorr = tpMatExc->pNoCorr->pNoNorte;
         free(tpMatExc->pNoCorr->pNoNorte);
		 DestroiNoMatriz( tpMatExc ) ;
      } /* if */

	  if ( tpMatExc->pNoCorr->pNoNoroeste != NULL )
      {
         tpMatExc->pNoCorr = tpMatExc->pNoCorr->pNoNoroeste;
         free(tpMatExc->pNoCorr->pNoNoroeste);
		 DestroiNoMatriz( tpMatExc ) ;
      } /* if */

	  free( tpMatExc->pNoCorr ) ;

   } /* Fim função: MAT Destruir a estrutura da matriz */


/***********************************************************************
*
*  $FC Função: MAT Prepara a estrutura da matriz - 05/09/2013
*
*  $FV Valor retornado
*     MAT_CondRetOK
*	  MAT_CondRetFaltouMemoria
*	  ....
*
***********************************************************************/

MAT_tpCondRet PreparaEstruturaMatriz( MAT_tpMatriz * tpMat , int numElementos ){

	int i = 0, j = 0;


	//tpElemMatriz * tpElemt = (tpElemMatriz *) malloc (sizeof (tpElemMatriz) );


	//checa se a matriz é um por um
	tpElemMatriz * tpElemLesteCabeca   = NULL;
	tpElemMatriz * tpElemSudesteCabeca = NULL;
	tpElemMatriz * tpElemSulCabeca     = NULL;
	tpElemMatriz * tpElemLesteNo	   = NULL;
	tpElemMatriz * tpElemSudesteNo	   = NULL;
	tpElemMatriz * tpElemSulNo		   = NULL;
	tpElemMatriz * tpElem			   = CriarNo( );
	if(tpElem == NULL)
	{
		return MAT_CondRetFaltouMemoria ;
	}

	if(numElementos == 1){
		tpMat->pNoCorr       = tpElem;
		tpMat->pNoRaiz       = tpElem;
		tpMat->pNoIndLinha   = tpElem;
		return MAT_CondRetOK;
	}

	numElementos = numElementos - 1;

	

	for(i=0;i<=numElementos;i++){

		for(j=0;j<=numElementos;j++){	

								
				//if que testa a condicão para 3 adjacentes
				if((i==0 || i==numElementos) && (j==0 || j==numElementos)){

					if(i==0 && j==0){
						tpMat->pNoCorr       = tpElem;
						tpMat->pNoRaiz       = tpElem;
						tpMat->pNoIndLinha   = tpElem;

						tpElemLesteCabeca   = CriarNo( );
						tpElemSudesteCabeca = CriarNo( );
						tpElemSulCabeca     = CriarNo( );
						if(tpElemLesteCabeca==NULL || tpElemSudesteCabeca==NULL || tpElemSulCabeca==NULL){
							return MAT_CondRetFaltouMemoria ;
						}						
						tpMat->pNoCorr->pNoLeste     = tpElemLesteCabeca;
						tpMat->pNoCorr->pNoSudeste   = tpElemSudesteCabeca;
						tpMat->pNoCorr->pNoSul       = tpElemSulCabeca;


					}
					if(i==0 && j==numElementos){
						
						tpMat->pNoCorr->pNoLeste->pNoSul       = tpMat->pNoCorr->pNoSudeste;
						tpMat->pNoCorr->pNoLeste->pNoSudoeste  = tpMat->pNoCorr->pNoSul;
						tpMat->pNoCorr->pNoLeste->pNoOeste     = tpMat->pNoCorr;

						// no final sta como corrente
						tpMat->pNoCorr = tpMat->pNoCorr->pNoLeste ;

					}
					if(i==numElementos && j==0){

						tpMat->pNoIndLinha->pNoSul->pNoNorte     = tpMat->pNoIndLinha;
						tpMat->pNoIndLinha->pNoSul->pNoNordeste  = tpMat->pNoIndLinha->pNoLeste;
						tpMat->pNoIndLinha->pNoSul->pNoLeste     = tpMat->pNoIndLinha->pNoSudeste;

						// no final seta como corrente
						tpMat->pNoCorr      = tpMat->pNoIndLinha->pNoSul;
						// no final aponta o indice da linha para o primeiro elemento da linha
						tpMat->pNoIndLinha  = tpMat->pNoIndLinha->pNoSul;

					}
					if(i==numElementos && j==numElementos){

						tpMat->pNoCorr->pNoLeste->pNoNorte     = tpMat->pNoCorr->pNoNordeste;
						tpMat->pNoCorr->pNoLeste->pNoNoroeste  = tpMat->pNoCorr->pNoNorte;
						tpMat->pNoCorr->pNoLeste->pNoOeste     = tpMat->pNoCorr;

						// no final sta como corrente
						tpMat->pNoCorr  = tpMat->pNoCorr->pNoLeste;

					}

				}

				//if que testa a condição para 5 adjacentes
				else if(i==0 || i==numElementos || j==0 || j==numElementos){


					if(i==0 && (j!=numElementos || j!=0)){
						
						tpMat->pNoCorr->pNoLeste->pNoSul      = tpMat->pNoCorr->pNoSudeste;
						tpMat->pNoCorr->pNoLeste->pNoSudoeste = tpMat->pNoCorr->pNoSul;
						tpMat->pNoCorr->pNoLeste->pNoOeste    = tpMat->pNoCorr;

						tpElemLesteNo   = CriarNo( );
						tpElemSudesteNo = CriarNo( );
						if(tpElemLesteNo==NULL || tpElemSudesteNo==NULL){
							return MAT_CondRetFaltouMemoria ;
						}
						tpMat->pNoCorr->pNoLeste->pNoLeste    = tpElemLesteNo;
						tpMat->pNoCorr->pNoLeste->pNoSudeste  = tpElemSudesteNo;


						// no final sta como corrente
						tpMat->pNoCorr  = tpMat->pNoCorr->pNoLeste;

					}

					if(j==0 && (i!=numElementos || i!=0)){

						tpMat->pNoIndLinha->pNoSul->pNoLeste    = tpMat->pNoIndLinha->pNoSudeste;				
						tpMat->pNoIndLinha->pNoSul->pNoNordeste = tpMat->pNoIndLinha->pNoLeste;
						tpMat->pNoIndLinha->pNoSul->pNoNorte    = tpMat->pNoIndLinha;

						tpElemSulNo     = CriarNo( );
						tpElemSudesteNo = CriarNo( );
						if(tpElemSulNo==NULL || tpElemSudesteNo==NULL){
							return MAT_CondRetFaltouMemoria ;
						}
						tpMat->pNoIndLinha->pNoSul->pNoSudeste  = tpElemSudesteNo;
						tpMat->pNoIndLinha->pNoSul->pNoSul      = tpElemSulNo;


						// no final sta como corrente
						tpMat->pNoCorr      = tpMat->pNoIndLinha->pNoSul;
						// no final aponta o indice da linha para o primeiro elemento da linha
						tpMat->pNoIndLinha  = tpMat->pNoIndLinha->pNoSul;

					}
					if(i==numElementos && (j!=numElementos || j!=0)){
			    
						tpMat->pNoCorr->pNoLeste->pNoLeste    = tpMat->pNoCorr->pNoNordeste->pNoSudeste;
						tpMat->pNoCorr->pNoLeste->pNoNordeste = tpMat->pNoCorr->pNoNordeste->pNoLeste;
						tpMat->pNoCorr->pNoLeste->pNoNorte    = tpMat->pNoCorr->pNoNordeste;
						tpMat->pNoCorr->pNoLeste->pNoNoroeste = tpMat->pNoCorr->pNoNorte;
						tpMat->pNoCorr->pNoLeste->pNoOeste    = tpMat->pNoCorr->pNoNoroeste;

						// no final sta como corrente
						tpMat->pNoCorr  = tpMat->pNoCorr->pNoLeste;

					}
					if(j==numElementos && (i!=numElementos || i!=0)){

						tpMat->pNoCorr->pNoLeste->pNoNorte     = tpMat->pNoCorr->pNoNordeste;
						tpMat->pNoCorr->pNoLeste->pNoSul       = tpMat->pNoCorr->pNoSudeste;
						tpMat->pNoCorr->pNoLeste->pNoSudoeste  = tpMat->pNoCorr->pNoSul;
						tpMat->pNoCorr->pNoLeste->pNoOeste     = tpMat->pNoCorr;
						tpMat->pNoCorr->pNoLeste->pNoNoroeste  = tpMat->pNoCorr->pNoNorte;

						// no final sta como corrente
						tpMat->pNoCorr  = tpMat->pNoCorr->pNoLeste;

					}

				}
				//else com 8 adjacentes
				else{

						tpMat->pNoCorr->pNoLeste->pNoNorte     = tpMat->pNoCorr->pNoNordeste;
						tpMat->pNoCorr->pNoLeste->pNoNordeste  = tpMat->pNoCorr->pNoNordeste->pNoLeste;
						tpMat->pNoCorr->pNoLeste->pNoLeste     = tpMat->pNoCorr->pNoNordeste->pNoSudeste;
						tpMat->pNoCorr->pNoLeste->pNoSul       = tpMat->pNoCorr->pNoSudeste;
						tpMat->pNoCorr->pNoLeste->pNoSudoeste  = tpMat->pNoCorr->pNoSul;
						tpMat->pNoCorr->pNoLeste->pNoOeste     = tpMat->pNoCorr;
						tpMat->pNoCorr->pNoLeste->pNoNoroeste  = tpMat->pNoCorr->pNoNorte;
						tpElemSudesteNo   = CriarNo( );
						if(tpElemSudesteNo==NULL){
							return MAT_CondRetFaltouMemoria ;
						}
						tpMat->pNoCorr->pNoLeste->pNoSudeste   = tpElemSudesteNo;


						tpMat->pNoCorr = tpMat->pNoCorr->pNoLeste;

				}
		}

	}

	 
	return MAT_CondRetOK;

}

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

   tpElemMatriz * CriarNo( )
   {

      tpElemMatriz * pNoMatriz ;
      pNoMatriz = ( tpElemMatriz * ) malloc( sizeof( tpElemMatriz )) ;
      if ( pNoMatriz == NULL )
      {
         return NULL ;
      } /* if */

	  pNoMatriz->Lista       = NULL ;
	  pNoMatriz->pNoLeste    = NULL ;
	  pNoMatriz->pNoNordeste = NULL ;
	  pNoMatriz->pNoNoroeste = NULL ;
	  pNoMatriz->pNoNorte    = NULL ;
	  pNoMatriz->pNoOeste    = NULL ;
	  pNoMatriz->pNoSudeste  = NULL ;
	  pNoMatriz->pNoSudoeste = NULL ;
	  pNoMatriz->pNoSul      = NULL ;

      return pNoMatriz ;

   } /* Fim função: ARV Criar nó da árvore */


/***********************************************************************
*
*  $FC Função: MAT Criar nó raiz da matriz
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetFaltouMemoria
*     MAT_CondRetNaoCriouRaiz
*
***********************************************************************/

MAT_tpCondRet CriarNoRaiz( MAT_tpMatriz* tpMat , int numElementos )
{

    MAT_tpCondRet CondRet ;

	if ( tpMat->pNoRaiz == NULL )
    {

		CondRet = PreparaEstruturaMatriz(tpMat, numElementos);		
				/* Criar a estrutura da matriz de acordo com a quantidade elementos passados */

		if ( CondRet != MAT_CondRetOK )
        {
        return CondRet ;
        } /* if */


        return MAT_CondRetOK  ;
    } /* if */

    return MAT_CondRetNaoCriouRaiz ;

} /* Fim função: MAT Criar nó raiz da matriz */

/********** Fim do módulo de implementação: Módulo matriz **********/

