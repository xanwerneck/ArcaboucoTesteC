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
*       1.00   afv   09/out/2013 Início do desenvolvimento
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

	char Nome[80];
		/* Rotulo da aresta */

	tpVerticeGrafo * pVerticeDest;
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


} GRA_tpGrafo ;

/************* Funções encapsuladas no módulo *************************/

void GRA_ExcluirdeVertices(GRA_tppGrafo pGrafo , tpVerticeGrafo * pVertice);
 
void GRA_ExcluirdeOrigens(GRA_tppGrafo pGrafo , tpVerticeGrafo * pVertice);

void LimparCabecaGrafo( GRA_tppGrafo pGrafo );

void GRA_CriaListaVertices( GRA_tppGrafo pGrafo ) ;

void GRA_CriaListaOrigens( GRA_tppGrafo pGrafo ) ;

void * GRA_CriaContVertice( char * Conteudo );

void GRA_CriaListaSucessoresVertice(tpVerticeGrafo * pVertice) ;

void GRA_CriaListaAntecessoresVertice(tpVerticeGrafo * pVertice) ;

void LimparVerticeGrafo( GRA_tppVerGrafo pVertGrafo ,  char * String , char id );

void GRA_excluirValorLista ( void * pValor ) ;

static int GRA_comparaVerticeConteudo( void * pVerticeO , void * pValorO ) ;

static int GRA_comparaVerticeCorrConteudo( GRA_tppGrafo pGrafo, void * pValorO ) ;

static int ComparaValor (void * Corr, void * Busca) ;

void IrInicioVertices (GRA_tppGrafo pGrafo) ;

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

	LimparCabecaGrafo( mGrafo ) ;


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

GRA_tpCondRet GRA_CriaVerticeGrafo(GRA_tppVerGrafo * vert, char * String , char id)
{

	GRA_tppVerGrafo pVert;

	pVert = (GRA_tppVerGrafo) malloc (sizeof (tpVerticeGrafo));


	if(pVert == NULL){
		return GRA_CondRetFaltouMemoria ;
	}

	LimparVerticeGrafo (pVert ,  String , id);


	(*vert) = ( tpVerticeGrafo * ) malloc( sizeof( GRA_tppVerGrafo )) ;


	if(vert == NULL){
		return GRA_CondRetFaltouMemoria ;
	}

	(*vert) = pVert ;


	return GRA_CondRetOK ;

	
}

GRA_tpCondRet criarAresta (tpVerticeGrafo * pVertOrig , tpVerticeGrafo * pVertDest , GRA_tppArestaGrafo * pArestaGrafo , GRA_tppGrafo pGrafo){

	GRA_tppArestaGrafo pAres;

	pAres = (GRA_tppArestaGrafo) malloc (sizeof (tpArestaGrafo));


	if(pAres == NULL){
		return GRA_CondRetFaltouMemoria ;
	}

	LimparArestaGrafo (pAres ,  String , id);


	(*pArestaGrafo) = ( tpArestaGrafo * ) malloc( sizeof( GRA_tppVerGrafo )) ;


	if(pArestaGrafo == NULL){
		return GRA_CondRetFaltouMemoria ;
	}

	(*pArestaGrafo) = pAres ;


	return GRA_CondRetOK ;
}

/***************************************************************************
*
*  Função: GRA  &Insere antecessores no vértice
*  ****/

GRA_tpCondRet GRA_InsereAntecessoresVertice(tpVerticeGrafo * pVertice)
{

	LIS_tppLista pLista;

	pLista = LIS_CriarLista (GRA_excluirValorLista);
	
	if(pVertice == NULL){
		return GRA_CondRetVerticeNulo ;
	}
	else if(pLista == NULL){
		return GRA_CondRetListaNula ;
	} 
	else{

		pVertice->pVerAnt = pLista ;

	} /* if */

	return GRA_CondRetOK;
}

/***************************************************************************
*
*  Função: GRA  &Insere sucessores no vértice
*  ****/

GRA_tpCondRet GRA_InsereSucessoresVertice(tpVerticeGrafo * pVertice)
{

    LIS_tppLista pLista;

	pLista = LIS_CriarLista (GRA_excluirValorLista);

	if(pVertice == NULL){
		return GRA_CondRetVerticeNulo ;
	}
	else if(pLista == NULL){
		return GRA_CondRetListaNula ;
	}
	else{

		pVertice->pVerSuc = pLista ;

	} /* if */
	
	return GRA_CondRetOK;
}

/***************************************************************************
*
*  Função: GRA  &Insere conteudo no vértice
*  ****/

GRA_tpCondRet GRA_InsereConteudoVertice(tpVerticeGrafo * pVertice , char * dado)
{
	VER_tppVerticeCont pConteudo ;

	VER_CriarVertice( &pConteudo , dado );

	if(pVertice == NULL){
		return GRA_CondRetVerticeNulo ;
	}
	else if(pConteudo == NULL){
		return GRA_CondRetConteudoNulo ;
	}
	else{

		pVertice->pConteudo = pConteudo;

	}/* if */
	return GRA_CondRetOK;
}

/***************************************************************************
*
*  Função: GRA  &Insere vértice no final da lista de vértices do grafo
*  ****/

GRA_tpCondRet GRA_InsereVerticeFinal(GRA_tppGrafo pGrafo , tpVerticeGrafo * pVertice)
{


	if(pVertice == NULL){
		return GRA_CondRetVerticeNulo;
	}
	else  if(pGrafo->pListaVertices == NULL){
		return GRA_CondRetListaNula;
	}
	else{

		IrFinalLista(pGrafo->pListaVertices);
		ListaRet = LIS_InserirElementoApos(pGrafo->pListaVertices, pVertice);

	} /* if */

	pGrafo->pCorrente = pVertice ;

	return GRA_CondRetOK;
}

/***************************************************************************
*
*  Função: GRA  &Insere vértice no início da lista de vértices do grafo
*  ****/

GRA_tpCondRet GRA_InsereVerticeInicio(GRA_tppGrafo pGrafo , tpVerticeGrafo * pVertice)
{


	if(pVertice == NULL){
		return GRA_CondRetVerticeNulo;
	}

	else  if(pGrafo->pListaVertices == NULL){
		return GRA_CondRetListaNula;
	}

	else{
	
		IrInicioLista(pGrafo->pListaVertices);
		ListaRet = LIS_InserirElementoAntes(pGrafo->pListaVertices, pVertice);
	
	} /* if */
	
	pGrafo->pCorrente = pVertice ;

	return GRA_CondRetOK;
}

/***************************************************************************
*
*  Função: GRA  &Insere vértice no início da lista de origens do grafo
*  ****/

GRA_tpCondRet GRA_InsereVerticeOrigens(GRA_tppGrafo pGrafo , tpVerticeGrafo * pVertice)
{

	GrafoRet = GRA_BuscarOcorrenciaOrigens (pGrafo , pVertice) ;

	if(GrafoRet == GRA_CondRetOK){

		return GRA_CondRetMaisdeUmaOrigem;

	} /* Se achou a ocorrencia na lista origens retorna alerta */


	if(pVertice == NULL){
		return GRA_CondRetVerticeNulo;
	}

	else  if(pGrafo->pListaOrigens == NULL){
		return GRA_CondRetListaNula;
	}

	else{
	
		IrInicioLista(pGrafo->pListaOrigens);
		ListaRet = LIS_InserirElementoAntes(pGrafo->pListaOrigens, pVertice);
	
	} /* if */


	return GRA_CondRetOK;
}

/***************************************************************************
*
*  Função: GRA  &Insere vértice na lista de sucessores de vértice
*  ****/

GRA_tpCondRet GRA_InsereVerticeemSucessores(tpVerticeGrafo * pVerticeOrig , tpVerticeGrafo * pVerticeDest)
{

	LIS_tppLista caminho ; 

	caminho = pVerticeOrig->pVerSuc;

	if(pVerticeOrig == NULL){

		return GRA_CondRetVerticeNulo;

	}else{

		IrInicioLista(caminho);
		ListaRet = LIS_InserirElementoAntes(caminho, pVerticeDest);
	
	} /* if */

	pVerticeOrig->pVerSuc = caminho ;

	return GRA_CondRetOK;
}

/***************************************************************************
*
*  Função: GRA  &Insere vértice na lista de antecessores de vértice
*  ****/

GRA_tpCondRet GRA_InsereVerticeemAntecessores(tpVerticeGrafo * pVerticeOrig , tpVerticeGrafo * pVerticeDest)
{

	LIS_tppLista caminho ; 

	caminho = pVerticeOrig->pVerAnt;

	if(pVerticeOrig == NULL){

		return GRA_CondRetVerticeNulo;

	}else{
	
		IrInicioLista(caminho);
		ListaRet = LIS_InserirElementoAntes(caminho,pVerticeDest);
	
	} /* if */
	
	pVerticeOrig->pVerAnt = caminho ;

	return GRA_CondRetOK;
}

/***************************************************************************
*
*  Função: GRA  &Excluir vértice
*  ****/


GRA_tpCondRet GRA_ExcluirVertice(GRA_tppGrafo pGrafo , tpVerticeGrafo * pVertice)
{
	int retAv ;

	tpVerticeGrafo * pVerticeCaminho;

	pVerticeCaminho = pVertice;

	IrInicioLista(pVertice->pVerAnt);

	ListaRet = LIS_CondRetOK ;

	/* Checa se corrente */
	GrafoRet = GRA_ChecaSeCorrente (pGrafo , pVertice) ;

	while(GrafoRet == GRA_CondRetOK) {

		ListaRet = LIS_AvancarElementoCorrente(pGrafo->pListaVertices, 1);

		if(ListaRet == LIS_CondRetOK){

			GrafoRet = GRA_ChecaSeCorrente (pGrafo , pVertice) ;

		}else{

			GrafoRet = (GRA_tpCondRet)ListaRet;

		}
		
		
	}

	
	/* FIM Checa se corrente */

	if(ListaRet == LIS_CondRetOK)
	{

		while(ListaRet!=LIS_CondRetFimLista)
		{

			pVerticeCaminho = (tpVerticeGrafo *)LIS_ObterValor (pVertice->pVerAnt);
			
			retTmp = LIS_ProcurarValor( pVerticeCaminho->pVerSuc , 
                                         pVertice , 
                                         GRA_comparaVerticeConteudo ) ;

			if(retTmp==LIS_CondRetOK)
			{
				ListaRet = LIS_ExcluirElemento (pVerticeCaminho->pVerSuc);
			} /* if */

			ListaRet = LIS_AvancarElementoCorrente(pVertice->pVerAnt, 1);

		} /* while */

	} /* if */

	IrInicioLista(pVertice->pVerSuc);

	ListaRet = LIS_CondRetOK ;

	if(ListaRet == LIS_CondRetOK)
	{

		while(ListaRet!=LIS_CondRetFimLista)
		{

			pVerticeCaminho = (tpVerticeGrafo *)LIS_ObterValor (pVertice->pVerSuc);

			retTmp = LIS_ProcurarValor( pVerticeCaminho->pVerAnt , 
                                         pVertice , 
                                         GRA_comparaVerticeConteudo ) ;

			if(retTmp==LIS_CondRetOK)
			{
				LIS_ExcluirElemento (pVerticeCaminho->pVerAnt);
			} /* if */

			ListaRet = LIS_AvancarElementoCorrente(pVertice->pVerSuc, 1);

		} /* while */

	} /* if */
	
	LIS_DestruirLista (pVertice->pVerAnt);
		/* Destroi a lista de antecessores após eliminar as referencias */

	LIS_DestruirLista (pVertice->pVerSuc);
		/* Destroi a lista de antecessores após eliminar as referencias */


	GRA_ExcluirdeVertices(pGrafo,pVertice);
		/* Destroi a referência da lista de origens  */

	GRA_ExcluirdeOrigens(pGrafo,pVertice);
		/* Destroi a referência da lista de vértices */
	

	free (pVertice);

	pVertice->pIdVertice = '\0';
	pVertice->pConteudo = NULL;

	pVertice = NULL;

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
	return GRA_CondRetOK;
}

/***************************************************************************
*
*  Função: GRA  &Excluir aresta, apaga a lista de sucessores do vértice
*  ****/

GRA_tpCondRet GRA_ExcluirSucessoresVertice(tpVerticeGrafo * pVertice)
{
	LIS_tppLista pListaVertices = pVertice->pVerSuc ;

	if(pVertice == NULL){

		return GRA_CondRetVerticeNulo;

	}
	else  if(pListaVertices == NULL){

		return GRA_CondRetListaNula;

	} /* if */
	LIS_DestruirLista (pVertice->pVerSuc);

	pVertice->pVerSuc = NULL;
	
	return GRA_CondRetOK;
}

/***************************************************************************
*
*  Função: GRA  &Excluir aresta, apaga a lista de antecessores do vértice
*  ****/

GRA_tpCondRet GRA_ExcluirAntecessoresVertice(tpVerticeGrafo * pVertice)
{

	LIS_tppLista pListaVertices = pVertice->pVerAnt ;

	if(pVertice == NULL){

		return GRA_CondRetVerticeNulo;

	}
	else  if(pListaVertices == NULL){

		return GRA_CondRetListaNula;

	} /* if */

	LIS_DestruirLista (pVertice->pVerAnt);

	pVertice->pVerAnt = NULL;
	
	return GRA_CondRetOK;
}

/*****  Código das funções encapsuladas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: GRA  - Limpa o conteúdo da lista de vértices do grafo 
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
	

}

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



}

/***********************************************************************
*
*  $FC Função: GRA  - Limpa a cabeça do grafo
*
***********************************************************************/

 void LimparCabecaGrafo( GRA_tppGrafo pGrafo )
{
	pGrafo->pCorrente = NULL;
	GRA_CriaListaOrigens (pGrafo);
	GRA_CriaListaVertices (pGrafo);

} /* Fim função: GRA  - Limpa a cabeça do grafo */


/***********************************************************************
*
*  $FC Função: GRA  - Limpa o vertice do grafo
*
***********************************************************************/

 void LimparVerticeGrafo( GRA_tppVerGrafo pVertGrafo , char * String, char id )
{

	pVertGrafo->pIdVertice = id ;


	pVertGrafo->pConteudo = GRA_CriaContVertice (String) ;

	GRA_CriaListaSucessoresVertice (pVertGrafo);
	GRA_CriaListaAntecessoresVertice (pVertGrafo);

} /* Fim função: GRA  - Limpa o vertice do grafo */

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

}

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

}

void GRA_CriaListaSucessoresVertice(tpVerticeGrafo * pVertice)
{

	LIS_tppLista pListaSuc ;

	pListaSuc = LIS_CriarLista (GRA_excluirValorLista);

	pVertice->pVerSuc = pListaSuc ;

}

void GRA_CriaListaAntecessoresVertice(tpVerticeGrafo * pVertice)
{

	LIS_tppLista pListaAnt ;

	pListaAnt = LIS_CriarLista (GRA_excluirValorLista);

	pVertice->pVerAnt = pListaAnt ;

}

/***************************************************************************
*
*  Função: GRF  &Excluir lista
*
****************************************************************************/

void GRA_excluirValorLista ( void * pValor )
{

    VER_DestruirVertice ((VER_tppVerticeCont) pValor) ;

} /* Fim função: GRF  &Excluir nada */

int GRA_comparaVerticeCorrConteudo (GRA_tppGrafo pGrafo , void * pValor)
{
	
	if((VER_tppVerticeCont)pGrafo->pCorrente == (VER_tppVerticeCont)pValor){

		return 0;

	}else{

		return 1;
	}
	

}

int GRA_comparaVerticeConteudo( void * pVerticeO , void * pValorO )
{

	int ret = 0;
	char * Corrente ;
	char * Buscado ;

	tpVerticeGrafo * pValorVert ;
    LIS_tppLista pVerticeLista ;
	
	pVerticeLista = ( LIS_tppLista ) pVerticeO ;
    
	pValorVert = ( tpVerticeGrafo * ) LIS_ObterValor( pVerticeLista ) ;


	VER_RetornaValor ((VER_tppVerticeCont)pValorVert->pConteudo , Corrente) ;

	VER_RetornaValor ((VER_tppVerticeCont)pValorO , Buscado) ;
	
	if(strcmp(Corrente , Buscado) == 0){

		return 0;
	}

	return 1;


	/*
	tpVerticeGrafo * pValorVert ;
    LIS_tppLista pVerticeLista ;

	pVerticeLista = ( LIS_tppLista ) pVerticeO ;
    
	pValorVert = ( tpVerticeGrafo * ) LIS_ObterValor( pVerticeLista ) ;

	if((VER_tppVerticeCont)pValorVert->pConteudo == (VER_tppVerticeCont)pValorO){

		return 0;

	}else{

		return 1;
	}
	*/

} /* Fim função: GRF  &Compara valores */


void IrInicioVertices (GRA_tppGrafo pGrafo)
{

	GRA_tppVerGrafo pValorVert ;

	IrInicioLista (pGrafo->pListaVertices) ;

	pValorVert = ( tpVerticeGrafo * ) LIS_ObterValor( pGrafo->pListaVertices ) ;

	pGrafo->pCorrente = pValorVert ;

}

int AvancarVerticeCorrente (GRA_tppGrafo pGrafo , int numElem)
{

	GRA_tppVerGrafo pValorVert ;

	ListaRet = LIS_AvancarElementoCorrente (pGrafo->pListaVertices , 1);
	
	if(ListaRet == LIS_CondRetOK){

		pValorVert = ( tpVerticeGrafo * ) LIS_ObterValor( pGrafo->pListaVertices ) ;

	    pGrafo->pCorrente = pValorVert ;

		return 1 ;

	}

	return NULL ;
}

GRA_tpCondRet GRA_ChecaSeCorrente (GRA_tppGrafo pGrafo , tpVerticeGrafo * pVerticeA)
{
	int Res ;

	Res = GRA_comparaVerticeCorrConteudo (pGrafo, pVerticeA) ;

	if(Res == 0){
		return GRA_CondRetOK ;
	} /* if */
	return GRA_CondRetNaoAchou ;
}

GRA_tpCondRet GRA_BuscarOcorrenciaOrigens (GRA_tppGrafo pGrafo , tpVerticeGrafo * pVerticeA)
{

	tpVerticeGrafo * pVerticeB ;

	int cond ;

	IrInicioVertices (pGrafo);

	while (cond != NULL) {

		pVerticeA = pGrafo->pCorrente ;

		IrInicioLista (pVerticeA->pVerAnt);

		while (ListaRet == LIS_CondRetOK){

			pVerticeB = (tpVerticeGrafo *)LIS_ObterValor (pVerticeA->pVerAnt);

			ListaRetCaminho = LIS_ProcurarValor (pGrafo->pListaOrigens , pVerticeB , GRA_comparaVerticeConteudo) ;

			if(ListaRetCaminho == LIS_CondRetOK){

				return GRA_CondRetOK;

			}

			ListaRet = LIS_AvancarElementoCorrente(pVerticeA->pVerAnt, 1);
		}

		IrInicioLista (pVerticeA->pVerSuc);

		while (ListaRet == LIS_CondRetOK){

			pVerticeB = (tpVerticeGrafo *)LIS_ObterValor (pVerticeA->pVerSuc);

			ListaRetCaminho = LIS_ProcurarValor (pGrafo->pListaOrigens , pVerticeB , GRA_comparaVerticeConteudo) ;

			if(ListaRetCaminho == LIS_CondRetOK){

				return GRA_CondRetOK;

			}

			ListaRet = LIS_AvancarElementoCorrente(pVerticeA->pVerSuc, 1);
		}

	   cond = AvancarVerticeCorrente (pGrafo , 1) ;

	}
	return GRA_CondRetNaoAchou ;

}


/********** Fim do módulo de implementação: Módulo GRAFO **********/

