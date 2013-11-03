/***************************************************************************
*  $MCI Módulo de implementação: Módulo GRAFO
*
*  Arquivo gerado:              GRAFO.C
*  Letras identificadoras:      GRA
*
*  Nome da base de software:    Exemplo de teste automatizado
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
*       1.00   afv   19/out/2013 Início do desenvolvimento
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>
#include   <string.h>

#define GRAFO_OWN
#include "GRAFO.H"
#undef GRAFO_OWN

#include "VERTICE.H"

LIS_tpCondRet ListaRet , ListaRetCaminho;
VER_tpCondRet ContVertRet;

/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da aresta do vértice do grafo
*
*
*  $ED Descrição do tipo
*     Possui as referências para rótulo string e tpVerticeGrafo destino
*
***********************************************************************/

typedef struct tagArestaGrafo {

	char * Nome;
		/* Rotulo da aresta */

	GRA_tppVerGrafo pVerticeDest;
		/* Ponteiro do Elemento tpVerticeGrafo destino */

	
} tpArestaGrafo ;


/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor do elemento vértice do grafo
*
*
*  $ED Descrição do tipo
*     Possui as referências para lista de sucessores e antecessores
*     Possui ponteiro para tipo VER_tppVertice
*     Possui id como referência do elemento vértice
*
***********************************************************************/

typedef struct tagVerticeGrafo {

	LIS_tppLista pVerAnt ;
		/* Ponteiro para lista de antecessores */
	
	LIS_tppLista pVerSuc ;	
		/* Ponteiro para lista de sucessores */

	void * pConteudo ;
		/* Ponteiro para o conteúdo do vértice */

	char pIdVertice[2];
		/* Identificador do vértice */

	void (*destruirValorV)(void *pValor);
        /* Destruir Valor do conteúdo do vértice */
	
} tpVerticeGrafo ;


/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da cabeça do grafo
*
*
*  $ED Descrição do tipo
*     A cabeça do grafo indica o início do grafo, possui referências para
*     lista de origens e vértices do grafo, o nó corrente referenciado
*     na cabeça, permite apontar em qual vértice está o elemento corrente.
*
***********************************************************************/

typedef struct GRA_tagGrafo {

	LIS_tppLista pListaOrigens;
		/* Ponteiro para lista de vértices de origens */

	LIS_tppLista pListaVertices;
		/* Ponteiro para lista com todos os vértices */

	tpVerticeGrafo * pCorrente;
		/* Ponteiro do Elemento vértice corrente */

	void (*destruirValor)(void *pValor);
		/* Ponteiro para implementação do destruir grafo genérico */


} GRA_tpGrafo ;

/************* Funções encapsuladas no módulo *************************/

static void GRA_ExcluirdeVertices(GRA_tppGrafo pGrafo , tpVerticeGrafo * pVertice);
 
static void GRA_ExcluirdeOrigens(GRA_tppGrafo pGrafo , tpVerticeGrafo * pVertice);

static void GRA_CriaListaVertices( GRA_tppGrafo pGrafo ) ;

static void GRA_CriaListaOrigens( GRA_tppGrafo pGrafo ) ;

static void GRA_CriaListaSucessoresVertice(tpVerticeGrafo * pVertice) ;

static void GRA_CriaListaAntecessoresVertice(tpVerticeGrafo * pVertice) ;

static void GRA_excluirValorLista ( void * pValor ) ;

static void GRA_excluirValorListaAresta ( void * pValor );

static int GRA_comparaVerticeConteudo( void * pVerticeO , void * pValorO ) ;

tpVerticeGrafo * GRA_BuscarVertice(GRA_tppGrafo pGrafo , char * Id) ;

static void LiberarAresta(GRA_tppArestaGrafo pAres);

static int ChecaArestaExiste(tpVerticeGrafo * pVertice , char * String, char * Dest);

static int ChecaVerticeExiste(GRA_tppGrafo pGrafo, char * Vert);

static void DestruirMalloc(LIS_tppLista pLista);


/*****  Código das funções exportadas pelo módulo  *****/


/***************************************************************************
*
*  Função: GRA  &Criar Grafo
*  ****/

GRA_tpCondRet GRA_CriarGrafo (GRA_tppGrafo * pGrafo , void   ( * ExcluirValor ) ( void * pDado ) )
{
	
	GRA_tppGrafo mGrafo ;

	mGrafo = (GRA_tppGrafo) malloc ( sizeof( GRA_tpGrafo ));

	if(mGrafo == NULL){

		return GRA_CondRetFaltouMemoria;

	} /* if */

	mGrafo->pCorrente = NULL;
	mGrafo->destruirValor = ExcluirValor;
	GRA_CriaListaOrigens (mGrafo);
	GRA_CriaListaVertices (mGrafo);


	(*pGrafo) = ( GRA_tpGrafo * ) malloc( sizeof( GRA_tppGrafo )) ;

	if(pGrafo == NULL){

		return GRA_CondRetFaltouMemoria;

	} /* if */

	(*pGrafo) = mGrafo;

	
	return GRA_CondRetOK;
}

GRA_tpCondRet GRA_ObterVertice(GRA_tppGrafo pGrafo , void ** pValor){
	if(pGrafo == NULL)
	{
		return GRA_CondRetGrafoNulo;
	} /* if */
	*pValor = pGrafo->pCorrente;
	return GRA_CondRetOK;
}

/***************************************************************************
*
*  Função: GRA  &Criar Vértice Grafo
*  ****/

GRA_tpCondRet GRA_CriaVerticeGrafo(GRA_tppGrafo pGrafo, char * String , char * id, void   ( * ExcluirValor ) ( void * pDado ))
{

	GRA_tppVerGrafo pVert;
	int ret = 0;

	if(pGrafo==NULL){
		return GRA_CondRetGrafoNulo ;
	} /* if */
	
	ret = ChecaVerticeExiste(pGrafo, id);
	if(ret == 1){
		return GRA_VerticeJaExiste ;
	} /* if */
	
	pVert = (GRA_tppVerGrafo) malloc (sizeof (tpVerticeGrafo));
	
	if(pVert == NULL){
		return GRA_CondRetFaltouMemoria ;
	} /* if */
	
	strcpy(pVert->pIdVertice , id);
	//pVert->pIdVertice = id ;
	pVert->pConteudo = String ;
	pVert->destruirValorV = ExcluirValor ;
	GRA_CriaListaSucessoresVertice (pVert);
	GRA_CriaListaAntecessoresVertice (pVert);
	
	LIS_InserirElementoApos(pGrafo->pListaVertices, pVert );
		/* Insere vértice na lista de vértices do grafo */

	
	pGrafo->pCorrente = pVert;

	return GRA_CondRetOK ;

	
}

/***************************************************************************
*
*  Função: GRA  &Criar Aresta do vértice Grafo
*  ****/

GRA_tpCondRet GRA_CriarAresta (char * pVertOrig , char * pVertDest , GRA_tppGrafo pGrafo, char * String)
{

	GRA_tppArestaGrafo pAres;
	tpVerticeGrafo * pVertO;
	tpVerticeGrafo * pVertD;
	int ret = 0;

	if(pGrafo==NULL){
		return GRA_CondRetGrafoNulo ;
	} /* if */ 

	pVertO = GRA_BuscarVertice(pGrafo, pVertOrig);
	if(pVertO == NULL){
		return GRA_CondRetNaoAchou ;
	} /* if */
	
	pVertD = GRA_BuscarVertice(pGrafo, pVertDest);
	if(pVertD == NULL){
		return GRA_CondRetNaoAchou ;
	} /* if */
	
	ret = ChecaArestaExiste(pVertO , String, pVertD->pIdVertice);
	if(ret==1){
		return GRA_ArestaJaExiste ;
	} /* if */

	pAres = (GRA_tppArestaGrafo) malloc (sizeof (tpArestaGrafo));

	if(pAres == NULL){
		return GRA_CondRetFaltouMemoria ;
	} /* if */
	
	pAres->Nome = String;
	pAres->pVerticeDest = pVertD;

	pGrafo->pCorrente = pVertO;
	LIS_InserirElementoApos(pGrafo->pCorrente->pVerSuc , pAres);
		/* Inserir aresta na lista de sucessores do vertorigem */

	pGrafo->pCorrente = pVertD;
	LIS_InserirElementoApos(pGrafo->pCorrente->pVerAnt , pVertO);
		/* Inserir vertice na lista de antecessores do vertdestino */

	return GRA_CondRetOK ;
}

/***************************************************************************
*
*  Função: GRA  &Insere vértice como origem do Grafo
*  ****/

GRA_tpCondRet GRA_InsereOrigem(GRA_tppGrafo pGrafo, char * IdVert)
{
	tpVerticeGrafo * VerCorr;
	tpVerticeGrafo * pVertO;
	ListaRetCaminho = LIS_CondRetOK ;

	VerCorr = GRA_BuscarVertice(pGrafo, IdVert);
	if(VerCorr == NULL){
		return GRA_CondRetNaoAchou ;
	} /* if */

	LIS_IrInicioLista(pGrafo->pListaOrigens);

	while(ListaRetCaminho==LIS_CondRetOK || ListaRetCaminho==LIS_CondRetFimLista){

		LIS_ObterValor (pGrafo->pListaOrigens , (void**)&pVertO);

		if(VerCorr->pIdVertice == pVertO->pIdVertice){

			return GRA_CondRetMaisdeUmaOrigem;

		} /* if */

		if(ListaRetCaminho == LIS_CondRetFimLista){
			break;
		} /* if */
		ListaRetCaminho = LIS_AvancarElementoCorrente(pGrafo->pListaOrigens, 1);

	} /* while */

	LIS_InserirElementoApos(pGrafo->pListaOrigens , VerCorr);

	pGrafo->pCorrente = VerCorr;

	return GRA_CondRetOK ;
}

/***************************************************************************
*
*  Função: GRA  &Excluir Aresta
*  ****/

GRA_tpCondRet GRA_ExcluirAresta(char * pVertOrig , char * pVertDest , GRA_tppGrafo pGrafo)
{
	tpVerticeGrafo * pVertO;
	tpVerticeGrafo * pVertD;
	tpArestaGrafo * pAres;
	
	pVertO = GRA_BuscarVertice(pGrafo, pVertOrig);
	if(pVertO == NULL){
		return GRA_CondRetNaoAchou ;
	} /* if */

	pVertD = GRA_BuscarVertice(pGrafo, pVertDest);
	if(pVertD == NULL){
		return GRA_CondRetNaoAchou ;
	} /* if */

	pGrafo->pCorrente = pVertO;

	ListaRetCaminho = LIS_IrInicioLista(pVertO->pVerSuc);
		
	while(ListaRetCaminho==LIS_CondRetOK || ListaRetCaminho==LIS_CondRetFimLista){
			
		LIS_ObterValor (pVertO->pVerSuc , (void**)&pAres);

		if(pAres->pVerticeDest->pIdVertice == pVertDest){

			GRA_excluirValorListaAresta(pAres);

			LIS_ExcluirElemento(pVertO->pVerSuc);

			break;

		} /* if */
		if(ListaRetCaminho == LIS_CondRetFimLista){
			break;
		} /* if */
		ListaRetCaminho = LIS_AvancarElementoCorrente(pVertO->pVerSuc, 1);

	} /* while */

	pGrafo->pCorrente = pVertD;

	ListaRetCaminho = LIS_IrInicioLista(pVertD->pVerAnt);
		
	while(ListaRetCaminho==LIS_CondRetOK || ListaRetCaminho==LIS_CondRetFimLista){
			
		LIS_ObterValor (pVertD->pVerAnt , (void**)&pVertO);

		if(pVertO->pIdVertice == pVertOrig){

			LIS_ExcluirElemento(pVertD->pVerAnt);

			break;

		} /* if */
		if(ListaRetCaminho == LIS_CondRetFimLista){
			break;
		} /* if */
		ListaRetCaminho = LIS_AvancarElementoCorrente(pVertD->pVerAnt, 1);

	} /* while */


	return GRA_CondRetOK;
}

/***************************************************************************
*
*  Função: GRA  &Definir vértice corrente
*  ****/

GRA_tpCondRet GRA_DefinirCorrente(GRA_tppGrafo pGrafo, char * IdVert)
{

	tpVerticeGrafo * pVerticeBusca ;

	ListaRet = LIS_IrInicioLista(pGrafo->pListaVertices);

	while(ListaRet == LIS_CondRetOK || ListaRet == LIS_CondRetFimLista){

		LIS_ObterValor (pGrafo->pListaVertices , (void**)&pVerticeBusca);

		if(pVerticeBusca->pIdVertice == IdVert){
			pGrafo->pCorrente = pVerticeBusca;
			return GRA_CondRetOK;
		} /* if */

		if(ListaRet==LIS_CondRetFimLista){
			break;
		} /* if */

		ListaRet = LIS_AvancarElementoCorrente(pGrafo->pListaVertices, 1);

	} /* while */

	return GRA_CondRetNaoAchou ;
}


/***************************************************************************
*
*  Função: GRA  &Excluir vértice
*  ****/


GRA_tpCondRet GRA_ExcluirVerticeCorrente(GRA_tppGrafo pGrafo)
{
	int ts;
	tpVerticeGrafo * pVertOrigem;
	tpVerticeGrafo * pVerticeCaminho;
	GRA_tppArestaGrafo pAres;

	pVertOrigem = pGrafo->pCorrente;

	LIS_IrInicioLista(pVertOrigem->pVerAnt);

	ListaRet        = LIS_CondRetOK ;
	ListaRetCaminho = LIS_CondRetOK;	

	LIS_NumElem(pVertOrigem->pVerAnt,&ts);

	if(ts > 0 ){

		while(ListaRet!=LIS_CondRetListaVazia)
		{

			LIS_ObterValor (pVertOrigem->pVerAnt , (void**)&pVerticeCaminho);
		
			ListaRetCaminho = LIS_IrInicioLista(pVerticeCaminho->pVerSuc);		


			while(ListaRetCaminho==LIS_CondRetOK || ListaRetCaminho==LIS_CondRetFimLista){
			
				LIS_ObterValor (pVerticeCaminho->pVerSuc , (void**)&pAres);

				if(pAres->pVerticeDest->pIdVertice == pVertOrigem->pIdVertice){

					GRA_ExcluirAresta(pVerticeCaminho->pIdVertice , pVertOrigem->pIdVertice , pGrafo);
					
				} /* if */
				if(ListaRetCaminho == LIS_CondRetFimLista){
					break;
				} /* if */
				ListaRetCaminho = LIS_AvancarElementoCorrente(pVerticeCaminho->pVerSuc, 1);


			} /* while */

		
			ListaRet = LIS_ChecaOrigemNulo(pVertOrigem->pVerAnt);

		} /* while */
	} /* if */

	ListaRet = LIS_IrInicioLista(pVertOrigem->pVerSuc);

	ListaRet = LIS_CondRetOK ;

	LIS_NumElem(pVertOrigem->pVerSuc,&ts);
	
	if(ts > 0 ){

		while(ListaRet!=LIS_CondRetListaVazia)
		{
		
			LIS_ObterValor (pVertOrigem->pVerSuc , (void**)&pAres);

			ListaRetCaminho = LIS_IrInicioLista((LIS_tppLista)pAres->pVerticeDest->pVerAnt);

			while(ListaRetCaminho==LIS_CondRetOK || ListaRetCaminho==LIS_CondRetFimLista){

				LIS_ObterValor (pAres->pVerticeDest->pVerAnt , (void**)&pVerticeCaminho);
			
				if(pVerticeCaminho->pIdVertice == pVertOrigem->pIdVertice){

					GRA_ExcluirAresta(pVertOrigem->pIdVertice , pAres->pVerticeDest->pIdVertice  , pGrafo);

					break;

				} /* if */
				if(ListaRetCaminho == LIS_CondRetFimLista){

					break;

				} /* if */

				ListaRetCaminho = LIS_AvancarElementoCorrente(pAres->pVerticeDest->pVerAnt, 1);


			} /* while */


			ListaRet = LIS_ChecaOrigemNulo(pVertOrigem->pVerAnt);

		} /* while */

	} /* if */
		
	LIS_DestruirLista (pVertOrigem->pVerAnt);
		/* Destroi a lista de antecessores após eliminar as referencias */

	LIS_DestruirLista (pVertOrigem->pVerSuc);
		/* Destroi a lista de antecessores após eliminar as referencias */

	GRA_ExcluirdeVertices(pGrafo,pVertOrigem);
		/* Destroi a referência da lista de origens  */

	GRA_ExcluirdeOrigens(pGrafo,pVertOrigem);
		/* Destroi a referência da lista de vértices */
	
	pGrafo->pCorrente->destruirValorV(pVertOrigem->pConteudo);

	ListaRet = LIS_IrInicioLista(pGrafo->pListaVertices);
	if(ListaRet == LIS_CondRetOK){
		LIS_ObterValor(pGrafo->pListaVertices , (void**)&pVerticeCaminho);
		pGrafo->pCorrente = pVerticeCaminho;
	}

	free (pVertOrigem);
	
	strcpy(pVertOrigem->pIdVertice , "");
	pVertOrigem->pConteudo = NULL;

	pVertOrigem = NULL;

	return GRA_CondRetOK;
	
}


/***************************************************************************
*
*  Função: GRA  &Obter valor do vértice corrente
*  ****/

GRA_tpCondRet GRA_ChecarNomeVerticeCorrente(GRA_tppGrafo pGrafo , char * nomeForn)
{

	VER_tppVerticeCont valorElem ;

	if(pGrafo == NULL){

		return GRA_CondRetGrafoNulo;

	} /* if */
	if(pGrafo->pCorrente == NULL){

		return GRA_CondRetConteudoNulo ;

	} /* if */
	
	valorElem = (VER_tppVerticeCont)pGrafo->pCorrente->pConteudo ;
	
	ContVertRet = VER_ObterValor((VER_tppVerticeCont)pGrafo->pCorrente->pConteudo , nomeForn) ;

	if(ContVertRet == VER_CondRetOK){

		return GRA_CondRetOK ;
 
	} /* if */

	return GRA_CondRetConteudoNulo ;
}

/***************************************************************************
*
*  Função: GRA  &Mudar valor do vértice corrente
*  ****/

GRA_tpCondRet GRA_MudarNomeVerticeCorrente(GRA_tppGrafo pGrafo , char * nomeForn)
{
	
	if(pGrafo == NULL){

		return GRA_CondRetVerticeNulo;

	} /* if */
	if(VER_MudarNomeVertice((VER_tppVerticeCont)pGrafo->pCorrente->pConteudo , nomeForn)==0){

		return GRA_CondRetOK ;

	} /* if */

	return GRA_CondRetConteudoNulo;
}

/***************************************************************************
*
*  Função: GRA  &Obter valor por referência
*  ****/

GRA_tpCondRet GRA_ObterValorCorrente(GRA_tppGrafo pGrafo , void ** pValor)
{

	if(pGrafo == NULL){

		return GRA_CondRetGrafoNulo;

	} /* if */
	
	*pValor = pGrafo->pCorrente->pConteudo;

	return GRA_CondRetOK ;
}

/***************************************************************************
*
*  Função: GRA  &Destruir Grafo
*  ****/

GRA_tpCondRet GRA_DestruirGrafo(GRA_tppGrafo pGrafo)
{
	int numElem = 0;
	tpVerticeGrafo * pVert ;

	if(pGrafo==NULL){

		return GRA_CondRetGrafoNulo;

	} /* if */

	LIS_IrInicioLista(pGrafo->pListaVertices);

	LIS_NumElem(pGrafo->pListaVertices , &numElem);

	while(numElem > 0){

		LIS_IrInicioLista(pGrafo->pListaVertices);

		LIS_ObterValor(pGrafo->pListaVertices , (void**)&pVert);

		pGrafo->pCorrente = pVert;

	    GRA_ExcluirVerticeCorrente(pGrafo);
		
		LIS_NumElem(pGrafo->pListaVertices , &numElem);


	} /* while */

	LIS_DestruirLista(pGrafo->pListaOrigens);

	LIS_DestruirLista(pGrafo->pListaVertices);

	free(pGrafo);

	pGrafo  = NULL;

	return GRA_CondRetOK;

}

GRA_tpCondRet GRA_AvancarCorrente(GRA_tppGrafo pGrafo , int val)
{
	
	tpVerticeGrafo * pVert;

	if(pGrafo == NULL){
		return GRA_CondRetGrafoNulo ;
	} /* if */
	if(pGrafo->pCorrente == NULL){
		return GRA_CondRetConteudoNulo ;
	} /* if */

	LIS_IrInicioLista(pGrafo->pListaVertices);

	LIS_ObterValor(pGrafo->pListaVertices , (void **)&pVert);

	pGrafo->pCorrente = pVert;

	return GRA_CondRetOK ;
}

GRA_tpCondRet GRA_IrInicio(GRA_tppGrafo pGrafo)
{

	ListaRet = LIS_IrInicioLista(pGrafo->pListaVertices);

	if(ListaRet == LIS_CondRetOK)
	{
		return GRA_CondRetOK;
	}

	return GRA_CondRetNaoAchou;
}

GRA_tpCondRet GRA_BuscaIdVertice(GRA_tppGrafo pGrafo , char ** pValor)
{
	if(pGrafo == NULL){
		return GRA_CondRetGrafoNulo;
	} /* if */

	*pValor = pGrafo->pCorrente->pIdVertice;

	return GRA_CondRetOK;
}

GRA_tpCondRet GRA_SetarCorrente(GRA_tppGrafo pGrafo , char * pValor)
{
	GRA_tppVerGrafo mVert;
	ListaRet = LIS_IrInicioLista(pGrafo->pListaVertices);
	do{

		LIS_ObterValor(pGrafo->pListaVertices , (void**)&mVert);

		if(strcmp(mVert->pIdVertice , pValor)==0){
			pGrafo->pCorrente = mVert;
			return GRA_CondRetOK;
		}

		ListaRet = LIS_AvancarElementoCorrente(pGrafo->pListaVertices , 1);

	}while(ListaRet!=LIS_CondRetFimLista);

	return GRA_CondRetListaNula;
}

GRA_tpCondRet GRA_AvancarCorrenteVert(GRA_tppGrafo pGrafo , int val)
{

	ListaRet = LIS_AvancarElementoCorrente(pGrafo->pListaVertices , val);

	if(ListaRet == LIS_CondRetFimLista)
	{
		return GRA_CondRetFimLista;
	}

	return GRA_CondRetOK;
}

GRA_tpCondRet GRA_NumeroVertices(GRA_tppGrafo pGrafo , int * val)
{

	ListaRet  = LIS_NumElem(pGrafo->pListaVertices , val);

	if(ListaRet == LIS_CondRetOK){

		return GRA_CondRetOK;

	} /* if */
	return GRA_CondRetNaoAchou;

}

/*****  Código das funções encapsuladas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: GRA  - &Limpa o conteúdo da lista de vértices do grafo 
*
***********************************************************************/

void GRA_ExcluirdeVertices(GRA_tppGrafo pGrafo , tpVerticeGrafo * pVertice)
{

	tpVerticeGrafo * pVert;

	ListaRet = LIS_IrInicioLista(pGrafo->pListaVertices);

	while(ListaRet == LIS_CondRetOK || ListaRet == LIS_CondRetFimLista)
	{

		LIS_ObterValor(pGrafo->pListaVertices , (void**)&pVert);
		if(pVertice->pIdVertice == pVert->pIdVertice){
			LIS_ExcluirElemento (pGrafo->pListaVertices);
		} /* if */
		if(ListaRet == LIS_CondRetFimLista){
			break;
		} /* if */
		ListaRet = LIS_AvancarElementoCorrente(pGrafo->pListaVertices, 1);

	} /* while */
	

} /* Fim função: GRA &Limpa o conteúdo da lista de vértices do grafo  */


/***********************************************************************
*
*  $FC Função: GRA  - Limpa o conteúdo da lista de origens do grafo 
*
***********************************************************************/

void GRA_ExcluirdeOrigens(GRA_tppGrafo pGrafo , tpVerticeGrafo * pVertice)
{

	
	tpVerticeGrafo * pVert;

	ListaRet = LIS_IrInicioLista(pGrafo->pListaOrigens);


	while(ListaRet == LIS_CondRetOK || ListaRet == LIS_CondRetFimLista)
	{
		LIS_ObterValor(pGrafo->pListaOrigens , (void**)&pVert);
		if(pVertice->pIdVertice == pVert->pIdVertice){
			LIS_ExcluirElemento (pGrafo->pListaOrigens);
		} /* if */
		if(ListaRet == LIS_CondRetFimLista){
			break;
		} /* if */
		ListaRet = LIS_AvancarElementoCorrente(pGrafo->pListaOrigens, 1);

	} /* while */


} /* Fim função: GRA &Limpa o conteúdo da lista de origens do grafo  */

/***************************************************************************
*
*  Função: GRA  &Criar Lista de origens Grafo
*
*************************************************************************/

void GRA_CriaListaOrigens( GRA_tppGrafo pGrafo )
{


	LIS_tppLista pListaOrig ;

	LIS_CriarLista (GRA_excluirValorLista , &pListaOrig);

	pGrafo->pListaOrigens = pListaOrig ;

} /* Fim função: GRA  &Criar Lista de origens Grafo */


/***************************************************************************
*
*  Função: GRA  &Criar Lista de vértices Grafo
*
*************************************************************************/

void GRA_CriaListaVertices( GRA_tppGrafo pGrafo )
{

	
	LIS_tppLista pListaVert ;

	LIS_CriarLista (GRA_excluirValorLista, &pListaVert);

	pGrafo->pListaVertices= pListaVert ;

} /* Fim função: GRA  &Criar Lista de vértices Grafo */


/***************************************************************************
*
*  Função: GRA  &Criar Lista de sucessores do vertice do Grafo
*
*************************************************************************/

void GRA_CriaListaSucessoresVertice(tpVerticeGrafo * pVertice)
{

	LIS_tppLista pListaSuc ;

	LIS_CriarLista (GRA_excluirValorLista, &pListaSuc);

	pVertice->pVerSuc = pListaSuc ;

} /* Fim função: GRA  &Criar Lista de sucessores do vertice do Grafo */


/***************************************************************************
*
*  Função: GRA  &Criar Lista de antecessores do vertice do Grafo
*
*************************************************************************/

void GRA_CriaListaAntecessoresVertice(tpVerticeGrafo * pVertice)
{

	LIS_tppLista pListaAnt ;

	LIS_CriarLista (GRA_excluirValorLista , &pListaAnt);

	pVertice->pVerAnt = pListaAnt ;

} /* Fim função: GRA  &Criar Lista de antecessores do vertice do Grafo */


/***************************************************************************
*
*  Função: GRA  &Excluir valor lista
*
****************************************************************************/

void GRA_excluirValorLista ( void * pValor )
{


} /* Fim função: GRA  &Excluir valor lista */


/***************************************************************************
*
*  Função: GRA  &Excluir valor lista do tipo Aresta
*
****************************************************************************/

void GRA_excluirValorListaAresta ( tpArestaGrafo * pAresta )
{

	free(pAresta);

} /* Fim função: GRA  &Excluir valor lista */


/***************************************************************************
*
*  Função: GRA  &Compara conteudo do vertice
*
****************************************************************************/

int GRA_comparaVerticeConteudo( void * pVerticeO , void * pValorO )
{

	int ret = 0;
	char * Corrente ;
	char * Buscado ;
	tpVerticeGrafo * pValorVert ;
    LIS_tppLista pVerticeLista ;

	Corrente = "";
	Buscado  = "";
	
	pVerticeLista = ( LIS_tppLista ) pVerticeO ;
    
	LIS_ObterValor (pVerticeLista , (void**)&pValorVert);


	VER_RetornaValor ((VER_tppVerticeCont)pValorVert->pConteudo , Corrente) ;

	VER_RetornaValor ((VER_tppVerticeCont)pValorO , Buscado) ;
	
	if(strcmp(Corrente , Buscado) == 0){

		return 0;
	} /* if */

	return 1;


} /* Fim função: GRA  &Compara valores */

/***************************************************************************
*
*  Função: GRA  &Avancar Vertice corrente
*
****************************************************************************/

int AvancarVerticeCorrente (GRA_tppGrafo pGrafo , int numElem)
{

	GRA_tppVerGrafo pValorVert ;

	ListaRet = LIS_AvancarElementoCorrente (pGrafo->pListaVertices , 1);
	
	if(ListaRet == LIS_CondRetOK){

		LIS_ObterValor (pGrafo->pListaVertices , (void**)&pValorVert);

	    pGrafo->pCorrente = pValorVert ;

		return 1 ;

	} /* if */

	return 0 ;
} /* Fim função: GRA  &Avancar Vertice corrente */


/***************************************************************************
*
*  Função: GRA  &Destruir valor do grafo
*
****************************************************************************/

GRA_tpCondRet destruirValor(GRA_tppGrafo pGrafo)
{

	if(pGrafo==NULL){
		return GRA_CondRetGrafoNulo;
	} /* if */

	pGrafo->pCorrente = NULL;

	LIS_DestruirLista(pGrafo->pListaOrigens);
	LIS_DestruirLista(pGrafo->pListaVertices);

	free(pGrafo);

	pGrafo = NULL;

	return GRA_CondRetOK;

} /* Fim função: GRA  &Destruir valor do grafo */



/***************************************************************************
*
*  Função: GRA  &Buscar Vertice
*
****************************************************************************/

tpVerticeGrafo * GRA_BuscarVertice(GRA_tppGrafo pGrafo , char * Id)
{
	tpVerticeGrafo * pVerticeRes;

	ListaRet = LIS_IrInicioLista(pGrafo->pListaVertices);
	
	while (ListaRet == LIS_CondRetOK || ListaRet == LIS_CondRetFimLista){
	
		LIS_ObterValor (pGrafo->pListaVertices , (void**)&pVerticeRes);

		if(pVerticeRes->pIdVertice == Id){
			return pVerticeRes ;
		} /* if */
		if(ListaRet ==LIS_CondRetFimLista){
			break;
		} /* if */

		ListaRet = LIS_AvancarElementoCorrente(pGrafo->pListaVertices, 1);
	} /* while */

	return NULL ;

}  /* Fim função: GRA &Buscar Vertice */

/***************************************************************************
*
*  Função: GRA  &Limpar conteúdo de aresta
*
****************************************************************************/

void LiberarAresta(GRA_tppArestaGrafo pAres)
{
	pAres->Nome = NULL;
	pAres->pVerticeDest = NULL;
	free(pAres);
	pAres = NULL;
} /* Fim função: GRA &Limpar conteúdo de aresta */

/***************************************************************************
*
*  Função: GRA  &Checa se aresta existe
*
****************************************************************************/

int ChecaArestaExiste(tpVerticeGrafo * pVertice , char * String, char * Dest)
{
	tpArestaGrafo * pAres ;

	if(pVertice==NULL){
		return 0;
	} /* if */

	ListaRetCaminho=LIS_IrInicioLista(pVertice->pVerSuc);

	
	while(ListaRetCaminho==LIS_CondRetOK || ListaRetCaminho==LIS_CondRetFimLista){

		LIS_ObterValor(pVertice->pVerSuc , (void**)&pAres);

		if(strcmp(pAres->Nome , String)==0 && pAres->pVerticeDest->pIdVertice == Dest){

			return 1;

		} /* if */

		if(ListaRetCaminho == LIS_CondRetFimLista){
			return 0;
		} /* if */
		ListaRetCaminho = LIS_AvancarElementoCorrente(pVertice->pVerSuc, 1);

	} /* while */

	pAres = NULL;

	return 0;
} /* Fim função: GRA &Checa se aresta existe */

/***************************************************************************
*
*  Função: GRA  &Checa se vértice existe
*
****************************************************************************/

int ChecaVerticeExiste(GRA_tppGrafo pGrafo, char * Vert)
{
	tpVerticeGrafo * pVertice;

	if(pGrafo==NULL){
		return 0;
	} /* if */

	ListaRetCaminho=LIS_IrInicioLista(pGrafo->pListaVertices);
	
	while(ListaRetCaminho==LIS_CondRetOK || ListaRetCaminho==LIS_CondRetFimLista){

		LIS_ObterValor(pGrafo->pListaVertices , (void**)&pVertice);

		if(strcmp(pVertice->pIdVertice, Vert)==0){

			return 1;

		} /* if */

		if(ListaRetCaminho == LIS_CondRetFimLista){
			return 0;
		} /* if */
		ListaRetCaminho = LIS_AvancarElementoCorrente(pGrafo->pListaVertices, 1);

	} /* while */

	pVertice = NULL;

	return 0;
} /* Fim função: GRA &Checa se vertice existe */


/********** Fim do módulo de implementação: Módulo GRAFO **********/
