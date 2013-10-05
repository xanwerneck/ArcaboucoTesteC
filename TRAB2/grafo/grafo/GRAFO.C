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

#define GRAFO_OWN
#include "GRAFO.H"
#undef GRAFO_OWN

#include "LISTA.H"
#include "VERTICE.H"

LIS_tpCondRet ListaRet , ListaRetCaminho;
VER_tpCondRet ContVertRet;


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

GRA_tpCondRet GRA_CriaVerticeGrafo(tpVerticeGrafo * vert, char * String , char id)
{

	vert = (tpVerticeGrafo *) malloc (sizeof(tpVerticeGrafo));

	if(vert == NULL){
		return GRA_CondRetFaltouMemoria;
	}else{

		GRA_CriaContVertice ((VER_tppVerticeCont *)vert->pConteudo , String) ; 
		vert->pIdVertice= id;
		vert->pVerAnt   = NULL;
		vert->pVerSuc   = NULL;

	}/* if */
	return GRA_CondRetOK;
	
}

/***************************************************************************
*
*  Função: GRA  &Insere antecessores no vértice
*  ****/

GRA_tpCondRet GRA_InsereAntecessoresVertice(tpVerticeGrafo * pVertice, LIS_tppLista pLista)
{

	LIS_tppLista * pLista;

	LIS_CriarLista (&pLista);

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

    LIS_tppLista * pLista;

	LIS_CriarLista (&pLista);

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

GRA_tpCondRet GRA_InsereConteudoVertice(tpVerticeGrafo * pVertice, VER_tppVerticeCont pConteudo)
{
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

GRA_tpCondRet GRA_InsereVerticeFinal(tpVerticeGrafo * pVertice, LIS_tppLista pListaVertices)
{

	if(pVertice == NULL){
		return GRA_CondRetVerticeNulo;
	}
	else  if(pListaVertices == NULL){
		return GRA_CondRetListaNula;
	}
	else{
		IrFinalLista(pListaVertices);
		ListaRet = LIS_InserirElementoApos(pListaVertices, pVertice);
		if(ListaRet == 0)
			return GRA_CondRetOK;
	} /* if */

	return GRA_CondRetOK;
}

/***************************************************************************
*
*  Função: GRA  &Insere vértice no início da lista de vértices do grafo
*  ****/

GRA_tpCondRet GRA_InsereVerticeInicio(tpVerticeGrafo * pVertice, LIS_tppLista pListaVertices)
{

	if(pVertice == NULL){
		return GRA_CondRetVerticeNulo;
	}

	else  if(pListaVertices == NULL){
		return GRA_CondRetListaNula;
	}

	else{
		IrInicioLista(pListaVertices);
		ListaRet = LIS_InserirElementoAntes(pListaVertices, pVertice);
		if(ListaRet == 0)
			return GRA_CondRetOK;
	} /* if */

	return GRA_CondRetOK;
}

/***************************************************************************
*
*  Função: GRA  &Excluir vértice
*  ****/

GRA_tpCondRet GRA_ExcluirVertice(GRA_tppGrafo pGrafo , tpVerticeGrafo * pVertice)
{
	LIS_tppLista pCaminhoListaAnt , pCaminhoListaSuc;

	tpVerticeGrafo * pVerticeCaminho;

	pCaminhoListaAnt = pVertice->pVerAnt;

	pCaminhoListaSuc = pVertice->pVerSuc;

	pVerticeCaminho = pVertice;
	
	ListaRet = IrInicioLista(pCaminhoListaAnt);

	if(ListaRet == LIS_CondRetOK)
	{

		while(ListaRet!=LIS_CondRetFimLista)
		{

			LIS_RetornaConteudo(pCaminhoListaAnt, pVerticeCaminho);

			if(LIS_ProcurarValor(pVerticeCaminho->pVerSuc , pVertice)==LIS_CondRetOK)
			{
				LIS_ExcluirElemento (pVerticeCaminho->pVerSuc);
			} /* if */

			ListaRet = LIS_AvancarElementoCorrente(pCaminhoListaAnt, 1);

		} /* while */

	} /* if */

	ListaRet = IrInicioLista(pCaminhoListaSuc);

	if(ListaRet == LIS_CondRetOK)
	{

		while(ListaRet!=LIS_CondRetFimLista)
		{

			LIS_RetornaConteudo(pCaminhoListaSuc, pVerticeCaminho);

			if(LIS_ProcurarValor(pVerticeCaminho->pVerAnt , pVertice)==LIS_CondRetOK)
			{
				LIS_ExcluirElemento (pVerticeCaminho->pVerAnt);
			} /* if */

			ListaRet = LIS_AvancarElementoCorrente(pCaminhoListaSuc, 1);

		} /* while */

	} /* if */

	LIS_DestruirLista (pCaminhoListaAnt);
		/* Destroi a lista de antecessores após eliminar as referencias */

	LIS_DestruirLista (pCaminhoListaSuc);
		/* Destroi a lista de antecessores após eliminar as referencias */

	GRA_ExcluirdeVertices(pGrafo,pVertice);
		/* Destroi a referência da lista de vértices */

	GRA_ExcluirdeOrigens(pGrafo,pVertice);
		/* Destroi a referência da lista de origens  */

	free (pVertice);

	pVertice->pIdVertice = '\0';
	pVertice->pConteudo = NULL;

	if(pVertice == NULL){

		return GRA_CondRetOK;

	} /* if */

	return GRA_CondRetConteudoNulo;
}

/***************************************************************************
*
*  Função: GRA  &Obter valor do vértice corrente
*  ****/



GRA_tpCondRet GRA_ObterValorVerticeCorrente(tpVerticeGrafo * pVertice , char * nomeForn)
{
	VER_tppVerticeCont valorElem ;

	valorElem = (VER_tppVerticeCont)pVertice->pConteudo ;

	if(pVertice == NULL){
		return GRA_CondRetVerticeNulo;
	}
	if(VER_ObterValor(valorElem , nomeForn)==0){
		GRA_CondRetOK ;
	}
	return GRA_CondRetOK;
}

/***************************************************************************
*
*  Função: GRA  &Mudar valor do vértice corrente
*  ****/



GRA_tpCondRet GRA_MudarValorVerticeCorrente(tpVerticeGrafo * pVertice , char * nomeForn)
{
	VER_tppVerticeCont valorElem ;

	valorElem = (VER_tppVerticeCont)pVertice->pConteudo ;

	if(pVertice == NULL){
		return GRA_CondRetVerticeNulo;
	}
	if(VER_MudarNomeVertice(valorElem , nomeForn)==0){
		GRA_CondRetOK ;
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
	ListaRet = LIS_DestruirLista (pVertice->pVerSuc);

	if(ListaRet == LIS_CondRetOK){
		pVertice->pVerSuc = NULL;
		return GRA_CondRetOK;
	} /* if */

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

	ListaRet = LIS_DestruirLista (pVertice->pVerAnt);

	if(ListaRet == LIS_CondRetOK){
		pVertice->pVerAnt = NULL;
		return GRA_CondRetOK;
	} /* if */

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

	LIS_tppLista pListaCam = pGrafo->pListaVertices;

	IrInicioLista(pListaCam);

	while(LIS_AvancarElementoCorrente(pListaCam, 1)!=2)
	{

		if(LIS_ProcurarValor(pListaCam , pVertice)==0){
			LIS_ExcluirElemento (pListaCam);
		} /* if */

	} /* while */

}

/***********************************************************************
*
*  $FC Função: GRA  - Limpa o conteúdo da lista de origens do grafo 
*
***********************************************************************/

void GRA_ExcluirdeOrigens(GRA_tppGrafo pGrafo , tpVerticeGrafo * pVertice)
{

	LIS_tppLista pListaCam = pGrafo->pListaOrigens;

	IrInicioLista(pListaCam);

	while(LIS_AvancarElementoCorrente(pListaCam, 1)!=2)
	{

		if(LIS_ProcurarValor(pListaCam , pVertice)==0){
			LIS_ExcluirElemento (pListaCam);
		} /* if */

	} /* while */

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


 /***************************************************************************
*
*  Função: GRA  &Criar conteúdo do vértice do Grafo
*  
************************************************************************/

void GRA_CriaContVertice(VER_tppVerticeCont * pVerticeCont, char * Conteudo )
{
	
	ContVertRet = VER_CriarVertice(pVerticeCont , Conteudo);

} /* Fim função: GRA  &Criar conteúdo do vértice do Grafo */


/***************************************************************************
*
*  Função: GRA  &Criar Lista de origens Grafo
*
*************************************************************************/

void GRA_CriaListaOrigens( GRA_tppGrafo pGrafo )
{

	LIS_tppLista * pListaOrig ;

	ListaRet = LIS_CriarLista (pListaOrig);

	if(ListaRet == 0){

		pGrafo->pListaOrigens = (*pListaOrig) ;

	}

}

/***************************************************************************
*
*  Função: GRA  &Criar Lista de vértices Grafo
*
*************************************************************************/

void GRA_CriaListaVertices( GRA_tppGrafo pGrafo )
{

	LIS_tppLista * pListaOrig ;

	ListaRet = LIS_CriarLista (pListaOrig);

	if(ListaRet == 0){

		pGrafo->pListaVertices = (*pListaOrig) ;

	}

}


/********** Fim do módulo de implementação: Módulo GRAFO **********/

