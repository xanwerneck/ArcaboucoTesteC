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

LIS_tpCondRet ListaRet , ListaRetCaminho;

/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor do elemento da matriz - 05/09/2013
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
*  $TC Tipo de dados: GRA Descritor da raiz de uma matriz
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
CriarVerticeGrafo 
Descricao = Cria tpVerticeGrafo
Parametros = char + conteudoVertive (modulo vertive)
Obs = Os dois ponteiros de listas iniciam com NULL

*/

GRA_tpCondRet GRA_CriaVerticeGrafo(void * conteudo, char id)
{

	tpVerticeGrafo * vert = (tpVerticeGrafo *) malloc (sizeof(tpVerticeGrafo));

	if(vert == NULL)
		return GRA_CondRetFaltouMemoria;
	else if(id == NULL)
		return GRA_CondRetValorNulo;
	else{

		vert->pConteudo = conteudo;
		vert->pIdVertice= id;
		vert->pVerAnt   = NULL;
		vert->pVerSuc   = NULL;

	}
	return GRA_CondRetOK;

}

/*
InsereAntecessoresVertice
Descricao = Insere uma lista no ponteiro de antecessores do tpVerticeGrafo
Parametros = tpVerticeGrafo + ListaAntecessores
Esta lista já possui os elementos referenciados
*/
GRA_tpCondRet GRA_InsereAntecessoresVertice(tpVerticeGrafo * pVertice, LIS_tppLista pLista)
{

	if(pVertice == NULL)
		return GRA_CondRetVerticeNulo ;
	else if(pLista == NULL)
		return GRA_CondRetListaNula ;
	else{

		ListaRet = LIS_InserirElementoAntes(pLista, pVertice->pVerAnt);

		if(ListaRet == 0)
			return GRA_CondRetOK;

	}

}
/*
InsereSucessoresVertice
Descricao = Insere uma lista no ponteiro de sucessores do tpVerticeGrafo
Parametros = tpVerticeGrafo + ListaSucessores
Esta lista já possui os elementos referenciados
*/
GRA_tpCondRet GRA_InsereSucessoresVertice(tpVerticeGrafo * pVertice, LIS_tppLista pLista)
{

	if(pVertice == NULL)
		return GRA_CondRetVerticeNulo ;
	else if(pLista == NULL)
		return GRA_CondRetListaNula ;
	else{

		ListaRet = LIS_InserirElementoAntes(pLista, pVertice->pVerSuc);

		if(ListaRet == 0)
			return GRA_CondRetOK;

	}

}
/*
InserirConteudoVertice
Descricao = Insere um elemento do modulo Vertice no tpVerticeGrafo
Parametros = tpVerticeGrafo + Vertice
*/

GRA_tpCondRet GRA_InsereConteudoVertice(tpVerticeGrafo * pVertice, VER_tppVertice pConteudo)
{
	if(pVertice == NULL)
		return GRA_CondRetVerticeNulo ;
	else if(pConteudo == NULL)
		return GRA_CondRetConteudoNulo ;
	else{

		pVertice->pConteudo = pConteudo;

	}
	return GRA_CondRetOK;
}

/*
InserirVertice Final
Generica = Tanto para origens como para vértices
Descricao = Insere vértice na lista de vértices da estrutura grafo
Parametros = tpVerticeGrafo
*/

GRA_tpCondRet GRA_InsereVerticeFinal(tpVerticeGrafo * pVertice, LIS_tppLista pListaVertices)
{

	if(pVertice == NULL)
		return GRA_tpCondRetVerticeNulo;

	else  if(pListaVertices == NULL)
		return GRA_tpCondRetListaNula;

	else{
		IrFinalLista(pListaVertices);
		ListaRet = LIS_InserirElementoApos(pListaVertices, pVertice);
		if(ListaRet == 0)
			return GRA_CondRetOK;
	}
}

/*
InserirVertice Inicio
Generica = Tanto para origens como para vértices
Descricao = Insere vértice na lista de vértices da estrutura grafo
Parametros = tpVerticeGrafo
*/

GRA_tpCondRet GRA_InsereVerticeFinal(tpVerticeGrafo * pVertice, LIS_tppLista pListaVertices)
{

	if(pVertice == NULL)
		return GRA_tpCondRetVerticeNulo;

	else  if(pListaVertices == NULL)
		return GRA_tpCondRetListaNula;

	else{
		IrInicioLista(pListaVertices);
		ListaRet = LIS_InserirElementoAntes(pListaVertices, pVertice);
		if(ListaRet == 0)
			return GRA_CondRetOK;
	}
}

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

GRA_tpCondRet GRA_ExcluirVertice(GRA_tppGrafo pGrafo , tpVerticeGrafo * pVertice)
{
	LIS_tppLista pCaminhoListaAnt , pCaminhoListaSuc;

	tpVerticeGrafo * pVerticeCaminho;

	pCaminhoListaAnt = pVertice->pVerAnt;

	pCaminhoListaSuc = pVertice->pVerSuc;
	
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

	pVertice->pIdVertice = NULL;
	pVertice->pConteudo = NULL;

	if(pVertice == NULL){

		return GRA_CondRetOK;

	} /* if */
	return GRA_CondRetConteudoNulo;
}

/**
Excluir aresta = Lista de Sucessores
*/
GRA_tpCondRet GRA_ExcluirSucessoresVertice(tpVerticeGrafo * pVertice)
{

	if(pVertice == NULL)
		return GRA_tpCondRetVerticeNulo;

	else  if(pListaVertices == NULL)
		return GRA_tpCondRetListaNula;

	ListaRet = LIS_DestruirLista (pVertice->pVerSuc);

	if(ListaRet == LIS_CondRetOK){
		pVertice->pVerSuc = NULL;
		return GRA_CondRetOK;
	}

}


/**
Excluir aresta = Lista de Antecessores
*/
GRA_tpCondRet GRA_ExcluirAntecessoresVertice(tpVerticeGrafo * pVertice)
{

	if(pVertice == NULL)
		return GRA_tpCondRetVerticeNulo;

	else  if(pListaVertices == NULL)
		return GRA_tpCondRetListaNula;

	ListaRet = LIS_DestruirLista (pVertice->pVerAnt);

	if(ListaRet == LIS_CondRetOK){
		pVertice->pVerAnt = NULL;
		return GRA_CondRetOK;
	}

}

/*****  Código das funções encapsuladas pelo módulo  *****/

void GRA_ExcluirdeVertices(GRA_tppGrafo pGrafo , tpVerticeGrafo * pVertice)
{

	LIS_tppLista pListaCam = pGrafo->pListaVertices;

	IrInicioLista(pListaCam);

	while(LIS_AvancarElementoCorrente(pListaCam, 1)!=2)
	{

		if(LIS_ProcurarValor(pListaCam , pVertice)==0)
			LIS_ExcluirElemento (pListaCam);


	} /* while */

}

void GRA_ExcluirdeOrigens(GRA_tppGrafo pGrafo , tpVerticeGrafo * pVertice)
{

	LIS_tppLista pListaCam = pGrafo->pListaOrigens;

	IrInicioLista(pListaCam);

	while(LIS_AvancarElementoCorrente(pListaCam, 1)!=2)
	{

		if(LIS_ProcurarValor(pListaCam , pVertice)==0)
			LIS_ExcluirElemento (pListaCam);


	} /* while */

}


/********** Fim do módulo de implementação: Módulo GRAFO **********/

