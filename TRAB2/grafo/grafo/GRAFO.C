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

#include "LISTA.H"

#include "VERTICE.H"

LIS_tpCondRet ListaRet , ListaRetCaminho, retTmp;
VER_tpCondRet ContVertRet;
GRA_tpCondRet GrafoRet ;



/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da aresta do vértice do grafo
*
*
*  $ED Descrição do tipo
*     Possui as referências para rótulo string e vertice destino
*
***********************************************************************/

typedef struct tagArestaGrafo {

	char * Nome;
		/* Rotulo da aresta */

	GRA_tppVerGrafo pVerticeDest;
		/* Ponteiro do Elemento vértice destino */

	
} tpArestaGrafo ;


/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor do elemento vértice do grafo
*
*
*  $ED Descrição do tipo
*     Possui as referências para lista de sucessores e antecessores
*
***********************************************************************/

typedef struct tagVerticeGrafo {

	LIS_tppLista pVerAnt ;
		/* Ponteiro para lista de antecessores */
	
	LIS_tppLista pVerSuc ;	
		/* Ponteiro para lista de sucessores */

	void * pConteudo ;
		/* Ponteiro para o nome do vértice, módulo vertice */

	char pIdVertice;
		/* Identificador do vértice */
	
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

void GRA_ExcluirdeVertices(GRA_tppGrafo pGrafo , tpVerticeGrafo * pVertice);
 
void GRA_ExcluirdeOrigens(GRA_tppGrafo pGrafo , tpVerticeGrafo * pVertice);

void GRA_CriaListaVertices( GRA_tppGrafo pGrafo ) ;

void GRA_CriaListaOrigens( GRA_tppGrafo pGrafo ) ;

void * GRA_CriaContVertice( char * Conteudo );

void GRA_CriaListaSucessoresVertice(tpVerticeGrafo * pVertice) ;

void GRA_CriaListaAntecessoresVertice(tpVerticeGrafo * pVertice) ;

void GRA_excluirValorLista ( void * pValor ) ;

static int GRA_comparaVerticeConteudo( void * pVerticeO , void * pValorO ) ;

tpVerticeGrafo * GRA_BuscarVertice(GRA_tppGrafo pGrafo , char Id) ;

void LiberarAresta(GRA_tppArestaGrafo pAres);

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: GRA  &Criar Grafo
*  ****/

GRA_tpCondRet GRA_CriarGrafo (GRA_tppGrafo * pGrafo)
{
	
	GRA_tppGrafo mGrafo ;

	mGrafo = (GRA_tppGrafo) malloc ( sizeof( GRA_tpGrafo ));


	if(mGrafo == NULL){

		return GRA_CondRetFaltouMemoria;

	} /* if */

	mGrafo->pCorrente = NULL;
	GRA_CriaListaOrigens (mGrafo);
	GRA_CriaListaVertices (mGrafo);


	(*pGrafo) = ( GRA_tpGrafo * ) malloc( sizeof( GRA_tppGrafo )) ;


	if(pGrafo == NULL){

		return GRA_CondRetFaltouMemoria;

	} /* if */

	(*pGrafo) = mGrafo;


	return GRA_CondRetOK;
}


/***************************************************************************
*
*  Função: GRA  &Criar Vértice Grafo
*  ****/

GRA_tpCondRet GRA_CriaVerticeGrafo(GRA_tppGrafo pGrafo, char * String , char id)
{

	GRA_tppVerGrafo pVert;

	pVert = (GRA_tppVerGrafo) malloc (sizeof (tpVerticeGrafo));


	if(pVert == NULL){
		return GRA_CondRetFaltouMemoria ;
	}

	pVert->pIdVertice = id ;
	pVert->pConteudo = GRA_CriaContVertice (String) ;
	GRA_CriaListaSucessoresVertice (pVert);
	GRA_CriaListaAntecessoresVertice (pVert);
	
	LIS_InserirElementoApos(pGrafo->pListaVertices, pVert );
		/* Insere vertice na lista de vértices do grafo */

	pGrafo->pCorrente = pVert;

	return GRA_CondRetOK ;

	
}

GRA_tpCondRet GRA_CriarAresta (char pVertOrig , char pVertDest , GRA_tppGrafo pGrafo, char * String)
{

	GRA_tppArestaGrafo pAres;
	tpVerticeGrafo * pVertO;
	tpVerticeGrafo * pVertD;

	pAres = (GRA_tppArestaGrafo) malloc (sizeof (tpArestaGrafo));

	if(pAres == NULL){
		return GRA_CondRetFaltouMemoria ;
	} /* if */

	pVertO = GRA_BuscarVertice(pGrafo, pVertOrig);
	if(pVertO == NULL){
		return GRA_CondRetNaoAchou ;
	} /* if */

	pVertD = GRA_BuscarVertice(pGrafo, pVertDest);
	if(pVertD == NULL){
		return GRA_CondRetNaoAchou ;
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
*  Função: GRA  &Insere conteudo no vértice
*  ****/

GRA_tpCondRet GRA_InsereOrigem(GRA_tppGrafo pGrafo, char IdVert)
{
	tpVerticeGrafo * VerCorr;

	VerCorr = GRA_BuscarVertice(pGrafo, IdVert);
	if(VerCorr == NULL){
		return GRA_CondRetNaoAchou ;
	} /* if */

	LIS_InserirElementoApos(pGrafo->pListaOrigens , VerCorr);

	pGrafo->pCorrente = VerCorr;

	return GRA_CondRetOK ;
}

//AlterarConteudoVertice

/***************************************************************************
*
*  Função: GRA  &Excluir Aresta
*  ****/

GRA_tpCondRet GRA_ExcluirAresta(char pVertOrig , char pVertDest , GRA_tppGrafo pGrafo)
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

	pAres = (tpArestaGrafo *)LIS_ObterValor (pGrafo->pCorrente->pVerSuc);
	LiberarAresta(pAres);
	LIS_ExcluirElemento(pGrafo->pCorrente->pVerSuc);

	pGrafo->pCorrente = pVertD;
	LIS_ExcluirElemento(pGrafo->pCorrente->pVerAnt);

	return GRA_CondRetOK;
}

/***************************************************************************
*
*  Função: GRA  &Definir vértice corrente
*  ****/

GRA_tpCondRet GRA_DefinirCorrente(GRA_tppGrafo pGrafo, char IdVert)
{
	
	tpVerticeGrafo * pVerticeBusca ;
	IrInicioLista(pGrafo->pListaVertices);

	while(ListaRet != LIS_CondRetFimLista){

		pVerticeBusca = (tpVerticeGrafo *)LIS_ObterValor (pGrafo->pListaVertices);

		if(pVerticeBusca->pIdVertice == IdVert){
			pGrafo->pCorrente = pVerticeBusca;
			return GRA_CondRetOK;
		}

		ListaRet = LIS_AvancarElementoCorrente(pGrafo->pListaVertices, 1);

	}

	return GRA_CondRetNaoAchou ;
}


/***************************************************************************
*
*  Função: GRA  &Excluir vértice
*  ****/


GRA_tpCondRet GRA_ExcluirVerticeCorrente(GRA_tppGrafo pGrafo)
{
	
	tpVerticeGrafo * pVertOrigem;
	tpVerticeGrafo * pVerticeCaminho;
	GRA_tppArestaGrafo pAres;

	pVertOrigem = pGrafo->pCorrente;

	IrInicioLista(pVertOrigem->pVerAnt);

	ListaRet        = LIS_CondRetOK ;
	ListaRetCaminho = LIS_CondRetOK;
	
	while(ListaRet!=LIS_CondRetListaVazia)
	{

		pVerticeCaminho = (tpVerticeGrafo *)LIS_ObterValor (pVertOrigem->pVerAnt);
		
		IrInicioLista(pVerticeCaminho->pVerSuc);
		
		while(ListaRetCaminho==LIS_CondRetOK || ListaRetCaminho==LIS_CondRetFimLista){
			
			pAres = (tpArestaGrafo *) LIS_ObterValor (pVerticeCaminho->pVerSuc);

			if(pAres->pVerticeDest->pIdVertice == pVertOrigem->pIdVertice){

				GRA_ExcluirAresta(pVerticeCaminho->pIdVertice , pVertOrigem->pIdVertice , pGrafo);

				break;

			}
			if(ListaRetCaminho == LIS_CondRetFimLista){
				break;
			}
			ListaRetCaminho = LIS_AvancarElementoCorrente(pVerticeCaminho->pVerSuc, 1);


		}

		ListaRet = LIS_ChecaOrigemNulo(pVertOrigem->pVerAnt);

	} /* while */

	IrInicioLista(pVertOrigem->pVerSuc);

	ListaRet = LIS_CondRetOK ;

	while(ListaRet!=LIS_CondRetListaVazia)
	{

		pAres = (tpArestaGrafo *) LIS_ObterValor (pVertOrigem->pVerSuc);

		IrInicioLista((LIS_tppLista)pAres->pVerticeDest->pVerAnt);


		while(ListaRetCaminho==LIS_CondRetOK || ListaRetCaminho==LIS_CondRetFimLista){

			pVerticeCaminho = (tpVerticeGrafo *) LIS_ObterValor (pAres->pVerticeDest->pVerAnt);


			if(pVerticeCaminho->pIdVertice == pVertOrigem->pIdVertice){

				GRA_ExcluirAresta(pAres->pVerticeDest->pIdVertice , pVertOrigem->pIdVertice , pGrafo);

				break;

			}
			if(ListaRetCaminho == LIS_CondRetFimLista){

				break;

			}
			ListaRetCaminho = LIS_AvancarElementoCorrente(pAres->pVerticeDest->pVerAnt, 1);


		}

		ListaRet = LIS_ChecaOrigemNulo(pVertOrigem->pVerAnt);

	} /* while */
	

	LIS_DestruirLista (pVertOrigem->pVerAnt);
		/* Destroi a lista de antecessores após eliminar as referencias */

	LIS_DestruirLista (pVertOrigem->pVerSuc);
		/* Destroi a lista de antecessores após eliminar as referencias */


	GRA_ExcluirdeVertices(pGrafo,pVertOrigem);
		/* Destroi a referência da lista de origens  */

	GRA_ExcluirdeOrigens(pGrafo,pVertOrigem);
		/* Destroi a referência da lista de vértices */
	

	free (pVertOrigem);

	pVertOrigem->pIdVertice = '\0';
	pVertOrigem->pConteudo = NULL;

	pVertOrigem = NULL;

	return GRA_CondRetOK;
	
}


/***************************************************************************
*
*  Função: GRA  &Obter valor do vértice corrente
*  ****/

GRA_tpCondRet GRA_ObterValorVerticeCorrente(GRA_tppGrafo pGrafo , char * nomeForn)
{

	VER_tppVerticeCont valorElem ;

	valorElem = (VER_tppVerticeCont)pGrafo->pCorrente->pConteudo ;

	if(pGrafo == NULL){

		return GRA_CondRetGrafoNulo;

	}
	
	ContVertRet = VER_ObterValor((VER_tppVerticeCont)pGrafo->pCorrente->pConteudo , nomeForn) ;

	if(ContVertRet == VER_CondRetOK){

		return GRA_CondRetOK ;

	}
	return GRA_CondRetConteudoNulo ;
}

/***************************************************************************
*
*  Função: GRA  &Mudar valor do vértice corrente
*  ****/



GRA_tpCondRet GRA_MudarValorVerticeCorrente(GRA_tppGrafo pGrafo , char * nomeForn)
{


	if(pGrafo == NULL){

		return GRA_CondRetVerticeNulo;

	}
	if(VER_MudarNomeVertice((VER_tppVerticeCont)pGrafo->pCorrente->pConteudo , nomeForn)==0){

		return GRA_CondRetOK ;

	}
	return GRA_CondRetConteudoNulo;
}


/*****  Código das funções encapsuladas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: GRA  - &Limpa o conteúdo da lista de vértices do grafo 
*
***********************************************************************/

void GRA_ExcluirdeVertices(GRA_tppGrafo pGrafo , tpVerticeGrafo * pVertice)
{


	IrInicioLista(pGrafo->pListaVertices);

	ListaRet = LIS_CondRetOK ;

	retTmp = LIS_ProcurarValor(pGrafo->pListaVertices , pVertice , GRA_comparaVerticeConteudo) ;


	if(retTmp==0){

		LIS_ExcluirElemento (pGrafo->pListaVertices);

	}
	return ;
	

} /* Fim função: GRA &Limpa o conteúdo da lista de vértices do grafo  */


/***********************************************************************
*
*  $FC Função: GRA  - Limpa o conteúdo da lista de origens do grafo 
*
***********************************************************************/

void GRA_ExcluirdeOrigens(GRA_tppGrafo pGrafo , tpVerticeGrafo * pVertice)
{


	IrInicioLista(pGrafo->pListaOrigens);

	ListaRet = LIS_CondRetOK ;

	retTmp = LIS_ProcurarValor(pGrafo->pListaOrigens , pVertice , GRA_comparaVerticeConteudo) ;


	if(retTmp==0){

		LIS_ExcluirElemento (pGrafo->pListaOrigens);

	}
	return ;


} /* Fim função: GRA &Limpa o conteúdo da lista de origens do grafo  */


 /***************************************************************************
*
*  Função: GRA  &Criar conteúdo do vértice do Grafo
*  
************************************************************************/

void * GRA_CriaContVertice(char * Conteudo )
{
	
	VER_tppVerticeCont pVerticeCont ;

	ContVertRet = VER_CriarVertice(&pVerticeCont , Conteudo);

	if(ContVertRet == VER_CondRetOK){

		return pVerticeCont ;

	} 
	return NULL;

} /* Fim função: GRA  &Criar conteúdo do vértice do Grafo */


/***************************************************************************
*
*  Função: GRA  &Criar Lista de origens Grafo
*
*************************************************************************/

void GRA_CriaListaOrigens( GRA_tppGrafo pGrafo )
{


	LIS_tppLista pListaOrig ;

	pListaOrig = LIS_CriarLista (GRA_excluirValorLista);

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

	pListaVert = LIS_CriarLista (GRA_excluirValorLista);

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

	pListaSuc = LIS_CriarLista (GRA_excluirValorLista);

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

	pListaAnt = LIS_CriarLista (GRA_excluirValorLista);

	pVertice->pVerAnt = pListaAnt ;

} /* Fim função: GRA  &Criar Lista de antecessores do vertice do Grafo */


/***************************************************************************
*
*  Função: GRA  &Excluir lista
*
****************************************************************************/

void GRA_excluirValorLista ( void * pValor )
{

    VER_DestruirVertice ((VER_tppVerticeCont) pValor) ;

} /* Fim função: GRA  &Excluir nada */


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
    
	pValorVert = ( tpVerticeGrafo * ) LIS_ObterValor( pVerticeLista ) ;


	VER_RetornaValor ((VER_tppVerticeCont)pValorVert->pConteudo , Corrente) ;

	VER_RetornaValor ((VER_tppVerticeCont)pValorO , Buscado) ;
	
	if(strcmp(Corrente , Buscado) == 0){

		return 0;
	}

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

		pValorVert = ( tpVerticeGrafo * ) LIS_ObterValor( pGrafo->pListaVertices ) ;

	    pGrafo->pCorrente = pValorVert ;

		return 1 ;

	}

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
	}

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

tpVerticeGrafo * GRA_BuscarVertice(GRA_tppGrafo pGrafo , char Id)
{
	tpVerticeGrafo * pVerticeRes;

	IrInicioLista(pGrafo->pListaVertices);

	ListaRet = LIS_CondRetOK;

	while (ListaRet != LIS_CondRetFimLista){
	
		pVerticeRes = (tpVerticeGrafo *)LIS_ObterValor(pGrafo->pListaVertices);

		if(pVerticeRes->pIdVertice == Id){
			return pVerticeRes ;
		}

		ListaRet = LIS_AvancarElementoCorrente(pGrafo->pListaVertices, 1);
	}

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

/********** Fim do módulo de implementação: Módulo GRAFO **********/

