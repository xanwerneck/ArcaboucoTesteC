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

typedef struct tgMatriz {

        tpElemMatriz * pNoRaiz ;
            /* Ponteiro para a raiz da matriz */

		tpElemMatriz * pNoIndLinha ;
            /* Ponteiro para a indice de linha da matriz */

        tpElemMatriz * pNoCorr ;
            /* Ponteiro para o nó corrente da matriz */

} tpMatriz ;


/*****  Dados encapsulados no módulo  *****/

static int numElementos = 0 ;
    /* Número de linhas e colunas da matriz (n x n) */

static tpMatriz * tpMat = NULL ;
    /* Ponteiro para a cabeça da matriz */

/***** Protótipos das funções encapsuladas no módulo *****/

static MAT_tpCondRet PreparaEstruturaMatriz( ) ;

static MAT_tpCondRet CriarNoRaiz( ) ;

static void DestroiMatriz( tpElemMatriz * tpMatExc ) ;

static tpElemMatriz * CriarNo( ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: MAT CriarMatriz - 05/09/2013
*  
****/

MAT_tpCondRet MAT_CriarMatriz( void ){
	   
		if(tpMat != NULL){
			DestroiMatriz( tpMat );
		} /* if */

	   tpMat = (tpMatriz *) malloc(sizeof(tpMatriz));
	   
	   if(tpMat == NULL){
		   return MAT_CondRetFaltouMemoria ;
	   } /* if */

	   tpMat->pNoCorr      = NULL;
	   tpMat->pNoRaiz      = NULL;
	   tpMat->pNoIndLinha  = NULL;

	   return MAT_CondRetOK;
}


/***************************************************************************
*
*  Função: MAT InsereListaMatriz - 05/09/2013
*
*	Percorre a estrutura da matriz procurando espaço vazio para
*	armazenar a lista criada.
*  
****/

MAT_tpCondRet MAT_InsereListaMatriz( LIS_tppLista * lt){

	if(tpMat == NULL){
		return MAT_CondRetFaltouMemoria ;
	} /* if */

	if ( tpMat->pNoCorr == NULL )
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
   
MAT_tpCondRet MAT_IrNoNorte(tpMatriz * tpMat){

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
   
MAT_tpCondRet MAT_IrNoNordeste(tpMatriz * tpMat){

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
   
MAT_tpCondRet MAT_IrNoLeste(tpMatriz * tpMat){

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
   
MAT_tpCondRet MAT_IrNoSudeste(tpMatriz * tpMat){

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
   
MAT_tpCondRet MAT_IrNoSul(tpMatriz * tpMat){

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
   
MAT_tpCondRet MAT_IrNoSudoeste(tpMatriz * tpMat){

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
   
MAT_tpCondRet MAT_IrNoOeste(tpMatriz * tpMat){

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
   
MAT_tpCondRet MAT_IrNoNoroeste(tpMatriz * tpMat){

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

MAT_tpCondRet MAT_ObterListaCorr( LIS_tppLista * lst_valor )
{

    if ( tpMat == NULL )
    {
        return MAT_CondRetMatrizNaoExiste  ;
    } /* if */
	if ( tpMat->pNoCorr == NULL )
    {
        return MAT_CondRetMatrizVazia ;
    } /* if */
    lst_valor = tpMat->pNoCorr->Lista ;

    return MAT_CondRetOK  ;

} /* Fim função: MAT Obter Lista corrente */


/***************************************************************************
*
*  Função: MAT Ir para nó raiz
*  ****/

MAT_tpCondRet MAT_IrRaiz( void )
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

void DestroiMatriz( tpMatriz * tpMatExc )
   {

	  if ( tpMatExc->pNoCorr->pNoSudeste != NULL )
      {
		 tpMatExc->pNoCorr = tpMatExc->pNoCorr->pNoSudeste;
         DestroiMatriz( tpMatExc ) ;
      } /* if */

	  if ( tpMatExc->pNoCorr->pNoSul != NULL )
      {
         tpMatExc->pNoCorr = tpMatExc->pNoCorr->pNoSul;
         DestroiMatriz( tpMatExc ) ;
      } /* if */

	  if ( tpMatExc->pNoCorr->pNoSudoeste != NULL )
      {
         tpMatExc->pNoCorr = tpMatExc->pNoCorr->pNoSudoeste;
         DestroiMatriz( tpMatExc ) ;
      } /* if */

	  if ( tpMatExc->pNoCorr->pNoLeste != NULL )
      {
         tpMatExc->pNoCorr = tpMatExc->pNoCorr->pNoOeste;
         DestroiMatriz( tpMatExc ) ;
      } /* if */

	  if ( tpMatExc->pNoCorr->pNoOeste != NULL )
      {
         tpMatExc->pNoCorr = tpMatExc->pNoCorr->pNoNoroeste;
         DestroiMatriz( tpMatExc ) ;
      } /* if */

	  if ( tpMatExc->pNoCorr->pNoNordeste != NULL )
      {
         tpMatExc->pNoCorr = tpMatExc->pNoCorr->pNoSul;
         DestroiMatriz( tpMatExc ) ;
      } /* if */

	  if ( tpMatExc->pNoCorr->pNoNorte != NULL )
      {
         tpMatExc->pNoCorr = tpMatExc->pNoCorr->pNoSul;
         DestroiMatriz( tpMatExc ) ;
      } /* if */

	  if ( tpMatExc->pNoCorr->pNoNoroeste != NULL )
      {
         tpMatExc->pNoCorr = tpMatExc->pNoCorr->pNoNoroeste;
         DestroiMatriz( tpMatExc ) ;
      } /* if */

      free( tpMatExc ) ;

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

MAT_tpCondRet PreparaEstruturaMatriz(){

	int i = 0, j = 0;

	for(;i<numElementos;i++){

		for(;j<numElementos;j++){	

				tpElemMatriz * tpElem = CriarNo( );
				if(tpElem != NULL){
					return MAT_CondRetFaltouMemoria ;
				}

				//checa se a matriz é um por um
				if(numElementos == 1){
					tpMat->pNoCorr       = tpElem;
					tpMat->pNoRaiz       = tpElem;
					tpMat->pNoIndLinha   = tpElem;
					return MAT_CondRetOK;
				}

				//if que testa a condicão para 3 adjacentes
				if((i==0 || j==0) && (i==numElementos || j==numElementos)){

					if(i==0 && j==0){
						tpMat->pNoCorr       = tpElem;
						tpMat->pNoRaiz       = tpElem;
						tpMat->pNoIndLinha   = tpElem;

						tpElemMatriz * tpElemLesteCabeca   = CriarNo( );
						tpElemMatriz * tpElemSudesteCabeca = CriarNo( );
						tpElemMatriz * tpElemSulCabeca     = CriarNo( );
						if(tpElemLesteCabeca==NULL || tpElemSudesteCabeca==NULL || tpElemSulCabeca==NULL){
							return MAT_CondRetFaltouMemoria ;
						}

						tpElem->pNoLeste     = tpElemLesteCabeca;
						tpElem->pNoSudeste   = tpElemSudesteCabeca;
						tpElem->pNoSul       = tpElemSulCabeca;
						tpElem->pNoSudoeste  = NULL;
						tpElem->pNoOeste     = NULL;
						tpElem->pNoNoroeste  = NULL;
						tpElem->pNoNorte     = NULL;
						tpElem->pNoNordeste  = NULL;
					}
					if(i==0 && j==numElementos){

						tpElem->pNoSul       = tpMat->pNoCorr->pNoSudeste;
						tpElem->pNoSudoeste  = tpMat->pNoCorr->pNoSul;
						tpElem->pNoOeste     = tpMat->pNoCorr;
						tpElem->pNoNoroeste  = NULL;
						tpElem->pNoNorte     = NULL;
						tpElem->pNoNordeste  = NULL;
						tpElem->pNoLeste     = NULL;
						tpElem->pNoSudoeste  = NULL;

						// no final sta como corrente
						tpMat->pNoCorr       = tpElem;

					}
					if(i==numElementos && j==0){

						tpElem->pNoNorte     = tpMat->pNoIndLinha;
						tpElem->pNoNordeste  = tpMat->pNoIndLinha->pNoLeste;
						tpElem->pNoLeste     = tpMat->pNoIndLinha->pNoSudeste;
						tpElem->pNoSudeste   = NULL;
						tpElem->pNoSul       = NULL;
						tpElem->pNoSudoeste  = NULL;
						tpElem->pNoOeste     = NULL;
						tpElem->pNoNoroeste  = NULL;

						// no final sta como corrente
						tpMat->pNoCorr      = tpElem;
						// no final aponta o indice da linha para o primeiro elemento da linha
						tpMat->pNoIndLinha  = tpElem;

					}
					if(i==numElementos && j==numElementos){

						tpElem->pNoNorte     = tpMat->pNoCorr->pNoNordeste;
						tpElem->pNoNoroeste  = tpMat->pNoCorr->pNoNorte;
						tpElem->pNoOeste     = tpMat->pNoCorr;
						tpElem->pNoNordeste  = NULL;
						tpElem->pNoLeste     = NULL;
						tpElem->pNoSudeste   = NULL;
						tpElem->pNoSul       = NULL;
						tpElem->pNoSudoeste  = NULL;

						// no final sta como corrente
						tpMat->pNoCorr  = tpElem;

					}

				}

				//if que testa a condição para 5 adjacentes
				else if(i==0 || i==numElementos || j==0 || j==numElementos){


					if(i==0 && (j!=numElementos || j!=0)){
			    
						tpElemMatriz * tpElemLesteNo   = CriarNo( );
						tpElemMatriz * tpElemSudesteNo = CriarNo( );
						if(tpElemLesteNo==NULL || tpElemSudesteNo==NULL){
							return MAT_CondRetFaltouMemoria ;
						}

						tpElem->pNoLeste    = tpElemLesteNo;
						tpElem->pNoSudeste  = tpElemSudesteNo;
						tpElem->pNoSul      = tpMat->pNoCorr->pNoSudeste;
						tpElem->pNoSudoeste = tpMat->pNoCorr->pNoSul;
						tpElem->pNoOeste    = tpMat->pNoCorr;
						tpElem->pNoNordeste = NULL;
						tpElem->pNoNorte    = NULL;
						tpElem->pNoNoroeste = NULL;


						// no final sta como corrente
						tpMat->pNoCorr  = tpElem;

					}
					if(j==0 && (i!=numElementos || i!=0)){

						tpElemMatriz * tpElemSulNo     = CriarNo( );
						tpElemMatriz * tpElemSudesteNo = CriarNo( );
						if(tpElemSulNo==NULL || tpElemSudesteNo==NULL){
							return MAT_CondRetFaltouMemoria ;
						}

						tpElem->pNoSudeste  = tpElemSudesteNo;
						tpElem->pNoSul      = tpElemSulNo;
						tpElem->pNoLeste    = tpMat->pNoCorr->pNoSudeste;				
						tpElem->pNoNordeste = tpMat->pNoCorr->pNoLeste;
						tpElem->pNoNorte    = tpMat->pNoCorr;
						tpElem->pNoNoroeste = NULL;
						tpElem->pNoOeste    = NULL;
						tpElem->pNoSudoeste = NULL;

						// no final sta como corrente
						tpMat->pNoCorr      = tpElem;
						// no final aponta o indice da linha para o primeiro elemento da linha
						tpMat->pNoIndLinha  = tpElem;

					}
					if(i==numElementos && (j!=numElementos || j!=0)){
			    
						tpElemMatriz * tpElemLesteNo   = CriarNo( );
						if(tpElemLesteNo==NULL){
							return MAT_CondRetFaltouMemoria ;
						}

						tpElem->pNoLeste    = tpElemLesteNo;
						tpElem->pNoNordeste = tpMat->pNoCorr->pNoNordeste->pNoLeste;
						tpElem->pNoNorte    = tpMat->pNoCorr->pNoNordeste;
						tpElem->pNoNoroeste = tpMat->pNoCorr->pNoNorte;
						tpElem->pNoOeste    = tpMat->pNoCorr->pNoNoroeste;
						tpElem->pNoSudoeste = NULL;
						tpElem->pNoSul      = NULL;
						tpElem->pNoSudeste  = NULL;

						// no final sta como corrente
						tpMat->pNoCorr  = tpElem;

					}
					if(j==numElementos && (i!=numElementos || i!=0)){

						tpElem->pNoNorte     = tpMat->pNoCorr->pNoNoroeste;
						tpElem->pNoSul       = tpMat->pNoCorr->pNoSudeste;
						tpElem->pNoSudoeste  = tpMat->pNoCorr->pNoSul;
						tpElem->pNoOeste     = tpMat->pNoCorr;
						tpElem->pNoNoroeste  = tpMat->pNoCorr->pNoNorte;
						tpElem->pNoNordeste  = NULL;
						tpElem->pNoLeste     = NULL;
						tpElem->pNoSudeste   = NULL;

						// no final sta como corrente
						tpMat->pNoCorr  = tpElem;

					}

				}
				//else com 8 adjacentes
				else{

						tpElemMatriz * tpElemSudesteNo   = CriarNo( );
						if(tpElemSudesteNo==NULL){
							return MAT_CondRetFaltouMemoria ;
						}


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

MAT_tpCondRet CriarNoRaiz()
{

    MAT_tpCondRet CondRet ;
    tpElemMatriz * tpElNo;

	if ( tpMat == NULL )
    {
		CondRet = MAT_CriarMatriz( ) ;

        if ( CondRet != MAT_CondRetOK )
        {
        return CondRet ;
        } /* if */
    } /* if */

	if ( tpMat->pNoRaiz == NULL )
    {

		CondRet = PreparaEstruturaMatriz();			
		if ( CondRet != MAT_CondRetOK )
        {
        return CondRet ;
        } /* if */

        tpElNo = CriarNo( ) ;
        if ( tpElNo == NULL )
        {
        return MAT_CondRetFaltouMemoria ;
        } /* if */
        tpMat->pNoRaiz     = tpElNo ;
        tpMat->pNoCorr     = tpElNo ;
		tpMat->pNoIndLinha = tpElNo ;

        return MAT_CondRetOK  ;
    } /* if */

    return MAT_CondRetNaoCriouRaiz ;

} /* Fim função: MAT Criar nó raiz da matriz */

/********** Fim do módulo de implementação: Módulo matriz **********/

