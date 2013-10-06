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

LIS_tpCondRet ListaRet , ListaRetCaminho, retTmp;
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

	LIS_tppLista pVerAnt ;
		/* Ponteiro para lista de antecessores */
	
	LIS_tppLista pVerSuc ;	
		/* Ponteiro para lista de sucessores */

	void * pConteudo ;
		/* Ponteiro para o nome do vértice, módulo vertice */

	char pIdVertice;
		/* Identificador do vértice */

	int ( * ComparaValor ) ( void * pValorCorr , void * pValorBuscado ) ;
               /* Ponteiro comparacao de valores entre vértices */

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

void GRA_CriaContVertice(VER_tppVerticeCont pVerticeCont, char * Conteudo );

void GRA_CriaListaSucessoresVertice(tpVerticeGrafo * pVertice) ;

void GRA_CriaListaAntecessoresVertice(tpVerticeGrafo * pVertice) ;

void LimparVerticeGrafo( GRA_tppVerGrafo pVertGrafo ,  char * String , char id );

void GRA_excluirLista ( void * pValor ) ;

static int GRA_comparaVerticeConteudo( void * pVerticeParm , void * pValorParm ) ;

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

/***************************************************************************
*
*  Função: GRA  &Insere antecessores no vértice
*  ****/

GRA_tpCondRet GRA_InsereAntecessoresVertice(tpVerticeGrafo * pVertice)
{

	LIS_tppLista pLista;

	pLista = LIS_CriarLista (GRA_excluirLista);
	
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

	pLista = LIS_CriarLista (GRA_excluirLista);

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
	
		ListaRet = LIS_InserirElementoAntes(caminho,pVerticeDest);
	
	} /* if */
	
	return GRA_CondRetOK;
}

/***************************************************************************
*
*  Função: GRA  &Excluir vértice
*  ****/


GRA_tpCondRet GRA_ExcluirVertice(GRA_tppGrafo pGrafo , tpVerticeGrafo * pVertice)
{
	/*
	if(pVertice == NULL){
		return GRA_CondRetConteudoNulo ;
	}
	
	if(pGrafo == NULL){
		return GRA_CondRetConteudoNulo ;
	}
	
	ListaRet = LIS_AvancarElementoCorrente (pGrafo->pListaOrigens , 2);

	printf("Resultado de avanco V: %d" , ListaRet);

	
	return GRA_CondRetOK;
	*/

	tpVerticeGrafo * pVerticeCaminho;

	LIS_tppLista camant , camsuc;

	camant = pVertice->pVerAnt ;

	camsuc = pVertice->pVerSuc ;

	pVerticeCaminho = pVertice;

	IrInicioLista(pVertice->pVerAnt);

	ListaRet = LIS_CondRetOK ;

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

	return GRA_CondRetOK; // até aqui certo

	GRA_ExcluirdeVertices(pGrafo,pVertice);
		/* Destroi a referência da lista de origens  */
	
	GRA_ExcluirdeOrigens(pGrafo,pVertice);
		/* Destroi a referência da lista de vértices */

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

	while(ListaRet!=LIS_CondRetFimLista)
	{

		if(ListaRet == LIS_CondRetListaVazia){

			ListaRet=LIS_CondRetFimLista ;

		}else{


			retTmp = LIS_ProcurarValor(pGrafo->pListaVertices , pVertice , GRA_comparaVerticeConteudo) ;

			if(retTmp==0){

				LIS_ExcluirElemento (pGrafo->pListaVertices);

			} /* if */
		
			ListaRet = LIS_AvancarElementoCorrente(pGrafo->pListaVertices, 1);

			printf ("Resultado %d" , ListaRet);


		}

	} /* while */

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

	while(ListaRet!=LIS_CondRetFimLista)
	{
		if(ListaRet == LIS_CondRetListaVazia){

			ListaRet=LIS_CondRetFimLista ;

		}else{

			retTmp = LIS_ProcurarValor(pGrafo->pListaOrigens , pVertice , GRA_comparaVerticeConteudo) ;

			if(retTmp==0){

				LIS_ExcluirElemento (pGrafo->pListaOrigens);

			} /* if */
		
			ListaRet = LIS_AvancarElementoCorrente(pGrafo->pListaOrigens, 1);

		}

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


/***********************************************************************
*
*  $FC Função: GRA  - Limpa o vertice do grafo
*
***********************************************************************/

 void LimparVerticeGrafo( GRA_tppVerGrafo pVertGrafo , char * String, char id )
{

	pVertGrafo->pIdVertice = id ;
	GRA_CriaContVertice ((VER_tppVerticeCont)pVertGrafo->pConteudo , String) ; 
	GRA_CriaListaSucessoresVertice (pVertGrafo);
	GRA_CriaListaAntecessoresVertice (pVertGrafo);

} /* Fim função: GRA  - Limpa o vertice do grafo */

 /***************************************************************************
*
*  Função: GRA  &Criar conteúdo do vértice do Grafo
*  
************************************************************************/

void GRA_CriaContVertice(VER_tppVerticeCont pVerticeCont, char * Conteudo )
{
	
	ContVertRet = VER_CriarVertice(&pVerticeCont , Conteudo);

} /* Fim função: GRA  &Criar conteúdo do vértice do Grafo */


/***************************************************************************
*
*  Função: GRA  &Criar Lista de origens Grafo
*
*************************************************************************/

void GRA_CriaListaOrigens( GRA_tppGrafo pGrafo )
{


	LIS_tppLista pListaOrig ;

	pListaOrig = LIS_CriarLista (GRA_excluirLista);

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

	pListaVert = LIS_CriarLista (GRA_excluirLista);

	pGrafo->pListaVertices= pListaVert ;

}

void GRA_CriaListaSucessoresVertice(tpVerticeGrafo * pVertice)
{

	LIS_tppLista pListaSuc ;

	pListaSuc = LIS_CriarLista (GRA_excluirLista);

	pVertice->pVerSuc = pListaSuc ;

}

void GRA_CriaListaAntecessoresVertice(tpVerticeGrafo * pVertice)
{

	LIS_tppLista pListaAnt ;

	pListaAnt = LIS_CriarLista (GRA_excluirLista);

	pVertice->pVerAnt = pListaAnt ;

}

/***************************************************************************
*
*  Função: GRF  &Excluir lista
*
****************************************************************************/

void GRA_excluirLista ( void * pValor )
{

    LIS_DestruirLista( ( LIS_tppLista ) pValor ) ;

} /* Fim função: GRF  &Excluir nada */



int GRA_comparaVerticeConteudo( void * pVerticeParm , void * pValorParm )
{
	tpVerticeGrafo * pValorVert ;
    LIS_tppLista pVertice ;
	
	pVertice = ( LIS_tppLista ) pVerticeParm ;
    
	pValorVert = ( tpVerticeGrafo * ) LIS_ObterValor( pVertice ) ;

	return pValorVert->ComparaValor( pValorVert->pConteudo , pValorParm ) ;

} /* Fim função: GRF  &Compara valores simples */


/********** Fim do módulo de implementação: Módulo GRAFO **********/

