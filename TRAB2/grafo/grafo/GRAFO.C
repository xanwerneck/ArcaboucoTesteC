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
*           fr - Fernanda Camelo Ribeiro
*			vo - Vinicius Deluiz de Oliveira
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       1.00   afv   29/08/2013 Início do desenvolvimento
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>

#define GRAFO_OWN
#include "GRAFO.H"
#undef GRAFO_OWN

#include "LISTA.H"
#include "VERTICE.H"


/***********************************************************************
*
*  $TC Tipo de dados: MAT Descritor do elemento da matriz - 05/09/2013
*
*
*  $ED Descrição do tipo
*     Descreve a organização do elemento
*
***********************************************************************/

typedef struct tagVerticeGrafo {

	void * pConteudo ;
		/* Ponteiro para o nome do vértice, módulo vertice */

	LIS_tppLista pVerAnt ;
		/* Ponteiro para lista de antecessores */
	
	LIS_tppLista pVerSuc ;	
		/* Ponteiro para lista de sucessores */

	char pIdVertice;
		/* Identificador do vértice */

} tpVerticeGrafo ;


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

typedef struct GRA_tagGrafo {

	LIS_tppLista pListaOrigens;
	/* Ponteiro para lista de vértices de origens */

	LIS_tppLista pListaVertices;
	/* Ponteiro para lista com todos os vértices */

	tpVerticeGrafo * pCorrente;
	/* Ponteiro do Elemento vértice corrente */

} GRA_tpGrafo ;

/*
InserirVertice

Descricao = Insere vértice na lista de vértices da estrutura grafo
Parametros = tpVerticeGrafo
*/

/*
CriarVerticeGrafo 
Descricao = Cria tpVerticeGrafo
Parametros = char + conteudoVertive (modulo vertive)
Obs = Os dois ponteiros de listas iniciam com NULL

*/

/*
InsereAntecessoresVertice
Descricao = Insere uma lista no ponteiro de antecessores do tpVerticeGrafo
Parametros = tpVerticeGrafo + ListaAntecessores
Esta lista já possui os elementos referenciados
*/

/*
InsereSucessoresVertice
Descricao = Insere uma lista no ponteiro de sucessores do tpVerticeGrafo
Parametros = tpVerticeGrafo + ListaSucessores
Esta lista já possui os elementos referenciados
*/

/*
InserirConteudoVertice
Descricao = Insere um elemento do modulo Vertice no tpVerticeGrafo
Parametros = tpVerticeGrafo + Vertice
*/

/*
ExcluirVertice
Descricao = Percorre a propria lista de antecessores do elemento a ser excluido 
            indo em cada elemento da lista e checando se ele (elemento a ser excluido)
			está presente na lista de antecessores ou sucessores, se sim, 
			tira a referencia.
			Percorre a propria lista de sucessores do elemento a ser excluido 
            indo em cada elemento da lista e checando se ele (elemento a ser excluido)
			está presente na lista de antecessores ou sucessores, se sim, 
			tira a referencia.
			Percorre a lista de origens e procura a ocorrencia do elemento a ser
			excluído, se sim, tira a referencia da lista origens.
			Percorre a lista de vertices e procura a ocorrencia do elemento a ser
			excluído, se sim, tira a referencia da lista vertices.
			free (elemento)

Parametros = tpVerticeGrafo
*/

/*
Apagare
*/

//
//
//
//
//
//


/***** Protótipos das funções encapsuladas no módulo *****/

static MAT_tpCondRet PreparaEstruturaMatriz( MAT_tpMatriz * tpMat , int numElementos ) ;

static VER_tpCondRet CriarNoCabeca( VER_tpVertice * tpVertice ) ;

static void DestroiVertice( VER_tpVertice * tpVerticeExc ) ;

static void DestroiNoElem( VER_tpVertice * tpVerticeExc );

static VER_tpCondRet * CriarNoElem( VER_tpVertice * tpVertice ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: MAT CriarMatriz - 05/09/2013
*  
****/

VER_tpCondRet VER_CriarVertice(VER_tppVertice* tpVertice){

	VER_tpCondRet CondRet ;

	VER_tppVertice mVertice ;

	if((*tpVertice) != NULL)
	{
		DestroiVertice( (*tpVertice) ); 
	} /* if */

	mVertice = ( VER_tppVertice ) malloc ( sizeof ( VER_tpVertice ) );
	/* Malloc para gerar um ponteiro de matriz */


	if(mVertice == NULL)
	{
		return VER_CondRetFaltouMemoria ;
	} /* if */

	mVertice->pNoCorr      = NULL;
	mVertice->pNoProx      = NULL;

	CondRet = CriarNoCabeca( mVertice );
	/* Inicializo a estrutura da matriz setando a raiz */

	if(CondRet != VER_CondRetOK)
	{
		return CondRet;
	} /* if */


	(*tpVertice) = ( VET_tpVertice* ) malloc( sizeof( VET_tppVertice )) ;

	if ( (*tpVertice) == NULL )
	{
		return MAT_CondRetFaltouMemoria ;
	} /* if */

	(*tpVertice) = mVertice ;


	return VET_CondRetOK ;
}


/***************************************************************************
*
*  Função: MAT InsereListaMatriz - 05/09/2013
*
*	Percorre a estrutura da matriz procurando espaço vazio para
*	armazenar a lista criada.
*  
****/

MAT_tpCondRet MAT_InsereListaMatriz( LIS_tpMatLista * lt, MAT_tppMatriz tpMat){


	if( lt == NULL ){
		return MAT_CondRetListaVazia ;
	} /* if */

	if ( tpMat == NULL )
	{
		return MAT_CondRetMatrizNaoExiste ;
	} /* if */

	tpMat->pNoCorr     = tpMat->pNoRaiz;
	tpMat->pNoIndLinha = tpMat->pNoCorr;

	/* procura a próxima posição de memória vazia para inserir a lista */
	while(tpMat->pNoCorr != NULL){
		if(tpMat->pNoCorr->Lista == NULL){
			tpMat->pNoCorr->Lista = lt;
			return MAT_CondRetOK;
		}else{
			if(tpMat->pNoCorr->pNoLeste == NULL){
				tpMat->pNoCorr     = tpMat->pNoIndLinha->pNoSul;
				tpMat->pNoIndLinha = tpMat->pNoCorr;
			}else{
				tpMat->pNoCorr = tpMat->pNoCorr->pNoLeste;
			} /* if */
		}/* if */
	}

	return MAT_CondRetMatrizCheia ;
	/* sem lugar para inserir */

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

MAT_tpCondRet MAT_ObterListaCorr( LIS_tpMatLista * lst_valor , MAT_tpMatriz * tpMat)
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

	if(lst_valor == tpMat->pNoCorr->Lista)
	{
		return MAT_CondRetOK  ;
	}

	return MAT_CondRetNoListaDiferente ;
	/* Lista passada diferente da corrente */

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

void DestroiVertice( VER_tpVertice * tpVerticeExc )
{

	if ( tpVerticeExc != NULL )
	{
		if ( tpVerticeExc->pNoCorr != NULL )
		{
			if( tpVerticeExc->pNoProx != NULL){
				DestroiVertice ( tpVerticeExc->pNoProx );
				free ( tpVerticeExc->pNoProx );
				tpVerticeExc = NULL;
			}
			DestroiNoElem( tpVerticeExc ) ;
		} /* if */
		free( tpVerticeExc ) ;
		tpVerticeExc = NULL ;
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

void DestroiNoElem( VER_tpVertice * tpVerticeExc );
{

	if ( tpVerticeExc->pNoCorr->pValor != NULL )
	{
		 tpMatExc->pNoCorr = tpMatExc->pNoCorr->pNoSudeste;
		 free(tpMatExc->pNoCorr->pNoSudeste);
		 DestroiNoElem( tpMatExc ) ;
	} /* if */

	if ( tpMatExc->pNoCorr->pNoSul != NULL )
	{
	 	tpMatExc->pNoCorr = tpMatExc->pNoCorr->pNoSul;
		free(tpMatExc->pNoCorr->pNoSul);
		DestroiNoElem( tpMatExc ) ;
	} /* if */

	if ( tpMatExc->pNoCorr->pNoSudoeste != NULL )
	{
		tpMatExc->pNoCorr = tpMatExc->pNoCorr->pNoSudoeste;
		free(tpMatExc->pNoCorr->pNoSudoeste);
		DestroiNoElem( tpMatExc ) ;
	} /* if */

	if ( tpMatExc->pNoCorr->pNoLeste != NULL )
	{
		 tpMatExc->pNoCorr = tpMatExc->pNoCorr->pNoLeste;
		 free(tpMatExc->pNoCorr->pNoLeste);
		 DestroiNoElem( tpMatExc ) ;
	} /* if */

	if ( tpMatExc->pNoCorr->pNoOeste != NULL )
	{
		 tpMatExc->pNoCorr = tpMatExc->pNoCorr->pNoOeste;
		 free(tpMatExc->pNoCorr->pNoOeste);
		 DestroiNoElem( tpMatExc ) ;
	} /* if */

	if ( tpMatExc->pNoCorr->pNoNordeste != NULL )
	{
		 tpMatExc->pNoCorr = tpMatExc->pNoCorr->pNoNordeste;
		 free(tpMatExc->pNoCorr->pNoNordeste);
		 DestroiNoElem( tpMatExc ) ;
	} /* if */

	if ( tpMatExc->pNoCorr->pNoNorte != NULL )
	{
		 tpMatExc->pNoCorr = tpMatExc->pNoCorr->pNoNorte;
		 free(tpMatExc->pNoCorr->pNoNorte);
		 DestroiNoElem( tpMatExc ) ;
	} /* if */

	if ( tpMatExc->pNoCorr->pNoNoroeste != NULL )
	{
		 tpMatExc->pNoCorr = tpMatExc->pNoCorr->pNoNoroeste;
		 free(tpMatExc->pNoCorr->pNoNoroeste);
		 DestroiNoElem( tpMatExc ) ;
	} /* if */

	free( tpMatExc->pNoCorr ) ;

} /* Fim função: MAT Destruir a estrutura da matriz */






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

VER_tpCondRet CriarNoElem ( VER_tpVertice * tpVertice )
{

	tpElemVertice * pNoVertice ;
	pNoVertice = ( tpElemVertice * ) malloc( sizeof( tpElemVertice )) ;
	if ( pNoVertice == NULL )
	{
		return VER_CondRetFaltouMemoria ;
	} /* if */

	pNoVertice->pValor = NULL;
	pNoVertice->Lista  = NULL;
	pNoVertice->pAnt   = NULL;
	pNoVertice->pProx  = NULL;

	(*tpVertice)->pNoCorr = pNoVertice; 
	

	return VER_CondRetOK ;

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

VER_tpCondRet CriarNoCabeca( VER_tpVertice * tpVertice ) 
{

	VER_tpCondRet CondRet ;

	if ( tpVertice->pNoCorr == NULL )
	{

		CondRet = CriarNoElem( tpVertice->pNoCorr );		
		/* Criar a estrutura da matriz de acordo com a quantidade elementos passados */

		if ( CondRet != VER_CondRetOK )
		{
			return CondRet ;
		} /* if */


		return VER_CondRetOK  ;
	} /* if */

	return VER_CondRetNaoCriouRaiz ;

} /* Fim função: MAT Criar nó raiz da matriz */

/********** Fim do módulo de implementação: Módulo matriz **********/

