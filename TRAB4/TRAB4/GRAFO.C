/***************************************************************************
*  $MCI Modulo de implementacao: Modulo GRAFO
*
*  Arquivo gerado:              GRAFO.C
*  Letras identificadoras:      GRA
*
*  Projeto: INF 1301 - Estrutura de teste - Arcabouço de Testes
*  Gestor:  Flavio Bevilacqua
*  Autores: afv:  aw - Alexandre Werneck
*                 fr - Fernanda C Ribeiro
*                 vo - Vinicius de Luiz de Oliveira
*
*  $HA Historico de evolucao:
*     Versao  Autor    Data     Observacoes
*     1       afv   19/out/2013 inicio do desenvolvimento do modulo
*     2       afv   11/nov/2013 adaptacao do modulo para tabuleiro
*     3       afv   02/dez/2013 inclusao de auto verificação da estrutura
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>
#include   <string.h>

#define GRAFO_OWN
#include "GRAFO.H"
#undef GRAFO_OWN

#include "LISTA.H"

#ifdef _DEBUG
   #include "CESPDIN.H"
   #include "CONTA.H"
   #include "GENERICO.H"
   #include "IdTiposEspaco.def"
#endif

LIS_tpCondRet ListaRet , ListaRetCaminho;


/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da aresta do vertice do grafo
*
*
*  $ED Descricao do tipo
*     Possui as referencias para rotulo string e tpVerticeGrafo destino
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
*  $TC Tipo de dados: GRA Descritor do elemento vertice do grafo
*
*
***********************************************************************/

typedef struct tagVerticeGrafo {

	LIS_tppLista pVerAnt ;
		/* Ponteiro para lista de antecessores */
	
	LIS_tppLista pVerSuc ;	
		/* Ponteiro para lista de sucessores */

	void * pConteudo ;
		/* Ponteiro para o conteudo do vertice */

	char pIdVertice;
		/* Identificador do vertice */

	void (*destruirValorV)(void *pValor);
        /* Destruir Valor do conteudo do vertice */

	#ifdef _DEBUG

	    GRA_tppGrafo ptCabeca ;
			/* Armazena um identificador para a cabeça do grafo */

		int tpEncapsulado ;
            /* Armazena um identificador para o tipo de informação encapsulada */

	#endif
	
} tpVerticeGrafo ;


/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da cabeca do grafo
*
***********************************************************************/

typedef struct GRA_tagGrafo {

	LIS_tppLista pListaOrigens;
		/* Ponteiro para lista de vertices de origens */

	LIS_tppLista pListaVertices;
		/* Ponteiro para lista com todos os vertices */

	tpVerticeGrafo * pCorrente;
		/* Ponteiro para elemento vertice corrente */

	void (*destruirValor)(void *pValor);
		/* Ponteiro para implementacao do destruir grafo generico */

	#ifdef _DEBUG

        int qtVertices ;
            /* Armazena a quantidade de vertices */

		int qtOrigens ;
            /* Armazena a quantidade de vertices */

		int qtArestas ;
		    /* Armazena a quantidade total de arestas do grafo */

		int tpEncapsulado ;
            /* Armazena um identificador para o tipo de informação encapsulada */

    #endif


} GRA_tpGrafo ;

/************* Dados encapsuladas no modulo *************************/

#ifdef _DEBUG

	static char EspacoLixo[ 256 ] =
             "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" ;
            /* Espaço de dados lixo usado ao testar */

#endif

/************* Funcoes encapsuladas no modulo *************************/

	/* Funcao libera pVertice da lista de vertices do pGrafo, 
	   tratando o encadeamento */
	static void GRA_ExcluirdeVertices(GRA_tppGrafo pGrafo , 
		                              tpVerticeGrafo * pVertice);
 
	/* Funcao libera pVertice da lista de origens do pGrafo, 
	   tratando o encadeamento */
	static void GRA_ExcluirdeOrigens(GRA_tppGrafo pGrafo , 
		                             tpVerticeGrafo * pVertice);
 
	/* Funcao aloca memoria para lista de vertices do pGrafo */
	static void GRA_CriaListaVertices( GRA_tppGrafo pGrafo ) ;
 
	/* Funcao aloca memoria para lista de origens do pGrafo */
	static void GRA_CriaListaOrigens( GRA_tppGrafo pGrafo ) ;
 
	/* Funcao aloca memoria para lista de sucessores do pGrafo */
	static void GRA_CriaListaSucessoresVertice(tpVerticeGrafo * pVertice) ;
 
	/* Funcao aloca memoria para lista de antecessores do pGrafo */
	static void GRA_CriaListaAntecessoresVertice(tpVerticeGrafo * pVertice) ;
 
	/* Funcao libera espaco alocado para  pValor */
	static void GRA_excluirValorLista ( void * pValor ) ;
 
	/* Funcao libera espaco alocado para  pAresta */
	static void GRA_excluirValorListaAresta ( tpArestaGrafo * pAresta );
 
	/* Funcao retorna o vertice do pGrafo correspondente ao Id  */
	tpVerticeGrafo * GRA_BuscarVertice(GRA_tppGrafo pGrafo , 
		                               char Id             ) ;
 
	/* Funcao libera espaco alocado para pAres */
	static void LiberarAresta(GRA_tppArestaGrafo pAres);
 
	/* Funcao checa se a aresta e valida */
	static int ChecaArestaExiste (tpVerticeGrafo * pVertice , 
		                         char * String, 
								 char Dest                 );
 
	/* Funcao checa se o vertice e valido */
	static int ChecaVerticeExiste(GRA_tppGrafo pGrafo, 
		                          char Vert         );

	/* Funcao limpa as referências das arestas */
	static void GRA_TirarCorrenteDeQualquerSucessor(GRA_tppVerGrafo pVertice, GRA_tppGrafo pGrafo);

	#ifdef _DEBUG

		/* Funcao checa sucessores do vertice diferentes de NULL */
		static int VerificaSucessoresVertice(GRA_tppVerGrafo pVertice);

		static int VerificaAntecessoresVertice(GRA_tppVerGrafo pVertice);

		static int VerificaLixoSucessoresVertice(GRA_tppVerGrafo pVertice);

		static int VerificaLixoAntecessoresVertice(GRA_tppVerGrafo pVertice);
		
		/* funções de deturpacao */
		static void D_GRA_AtribuiNullAntecessor(GRA_tppGrafo pGrafo);

		static void D_GRA_AtribuiNullSucessor(GRA_tppGrafo pGrafo);

		static void D_GRA_AtribuiLixoSucessor(GRA_tppGrafo pGrafo);

		static void D_GRA_AtribuiLixoAntecessor(GRA_tppGrafo pGrafo);

		static void D_GRA_IsolaVertice(GRA_tppGrafo pGrafo);

		/* funções de verificação */
		static GRA_tpCondRet V_GRA_VerificaNullSucessor(GRA_tppGrafo pGrafo);

		static GRA_tpCondRet V_GRA_VerificaNullAntecessor(GRA_tppGrafo pGrafo);

		static GRA_tpCondRet V_GRA_VerificaLixoSucessor(GRA_tppGrafo pGrafo);

		static GRA_tpCondRet V_GRA_VerificaLixoAntecessor(GRA_tppGrafo pGrafo);

		static GRA_tpCondRet V_GRA_VerificaVerticeIsolado(GRA_tppGrafo pGrafo);

		static GRA_tpCondRet V_GRA_VerificaConteudoNulo(GRA_tppGrafo pGrafo);

		static GRA_tpCondRet V_GRA_VerificaTipoVertice(GRA_tppGrafo pGrafo);

		static GRA_tpCondRet V_GRA_VerificaOrigemNula(GRA_tppGrafo pGrafo);

	#endif

/************* Codigo das funcoes exportadas pelo modulo ******************/
	
/***************************************************************************
*
*  Funcao: GRA  &Criar Grafo
*  ****/

GRA_tpCondRet GRA_CriarGrafo (GRA_tppGrafo * pGrafo , void   ( * ExcluirValor ) ( void * pDado ) )
{

	(*pGrafo) = (GRA_tppGrafo) malloc ( sizeof( GRA_tpGrafo ));

	#ifdef _DEBUG
		CNT_CONTAR( "GRA_CriarGrafo" ) ;
    #endif

	if((*pGrafo) == NULL){

		return GRA_CondRetFaltouMemoria;

	} /* if */

	(*pGrafo)->pCorrente = NULL;
	(*pGrafo)->destruirValor = ExcluirValor;
	GRA_CriaListaOrigens ((*pGrafo));
	GRA_CriaListaVertices ((*pGrafo));


	#ifdef _DEBUG

         CED_DefinirTipoEspaco( (*pGrafo) , GRA_TipoEspacoCabeca ) ;

         (*pGrafo)->qtVertices = 0;
		 (*pGrafo)->qtOrigens  = 0;
		 (*pGrafo)->qtArestas  = 0;

    #endif
	

	return GRA_CondRetOK;
} /* Fim funcao: GRA &Criar Grafo */

/***************************************************************************
*
*  Funcao: GRA  &Criar Vertice Grafo
*  ****/

GRA_tpCondRet GRA_CriaVerticeGrafo(GRA_tppGrafo pGrafo, void * Conteudo , char id , void   ( * ExcluirValor ) ( void * pDado ))
{
	GRA_tppVerGrafo pVert;

	#ifdef _DEBUG
		GRA_tppVerGrafo pVertDeb = NULL;
	#endif

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

	#ifdef _DEBUG
		CNT_CONTAR( "GRA_CriarVerticeGrafo" ) ;
    #endif

	pVert->pIdVertice = id;
	pVert->pConteudo = Conteudo ;
	pVert->destruirValorV = ExcluirValor ;
	GRA_CriaListaSucessoresVertice (pVert);
	GRA_CriaListaAntecessoresVertice (pVert);
	
	LIS_InserirElementoApos(pGrafo->pListaVertices, pVert );
		/* Insere vertice na lista de vertices do grafo */

	#ifdef _DEBUG

		CED_DefinirTipoEspaco( pVert , GRA_TipoEspacoVertice ) ;	

        pGrafo->qtVertices++;

		pVert->ptCabeca = pGrafo;

    #endif

	pGrafo->pCorrente = pVert;
		
	return GRA_CondRetOK ;

	
} /* Fim funcao: GRA &Criar Vertice Grafo */

/***************************************************************************
*
*  Funcao: GRA  &Criar Aresta do vertice Grafo
*  ****/

GRA_tpCondRet GRA_CriarAresta (char pVertOrig , char pVertDest , GRA_tppGrafo pGrafo, char * String)
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

	#ifdef _DEBUG
		CNT_CONTAR( "GRA_CriarArestaGrafo" ) ;
    #endif
	
	pAres->Nome = String;
	pAres->pVerticeDest = pVertD;


	pGrafo->pCorrente = pVertO;
	LIS_InserirElementoApos(pGrafo->pCorrente->pVerSuc , pAres);
		/* Inserir aresta na lista de sucessores do vertorigem */

	pGrafo->pCorrente = pVertD;
	LIS_InserirElementoApos(pGrafo->pCorrente->pVerAnt , pVertO);
		/* Inserir vertice na lista de antecessores do vertdestino */

	#ifdef _DEBUG

		CED_DefinirTipoEspaco( pAres , GRA_TipoEspacoAresta ) ;

    #endif

	return GRA_CondRetOK ;
} /* Fim funcao: GRA &Criar Aresta do vertice Grafo */

/***************************************************************************
*
*  Funcao: GRA  &Insere vertice como origem do Grafo
*  ****/

GRA_tpCondRet GRA_InsereOrigem(GRA_tppGrafo pGrafo, char IdVert)
{
	tpVerticeGrafo * VerCorr;
	tpVerticeGrafo * pVertO;
	ListaRetCaminho = LIS_CondRetOK ;

	#ifdef _DEBUG
		CNT_CONTAR( "GRA_InserirOrigem" ) ;
    #endif

	VerCorr = GRA_BuscarVertice(pGrafo, IdVert);
	if(VerCorr == NULL){
		return GRA_CondRetNaoAchou ;
	} /* if */

	ListaRetCaminho = LIS_IrInicioLista(pGrafo->pListaOrigens);

	if(ListaRetCaminho == LIS_CondRetOK){

		do{
			LIS_ObterValor (pGrafo->pListaOrigens , (void**)&pVertO);

			if(VerCorr->pIdVertice == pVertO->pIdVertice){

				return GRA_CondRetMaisdeUmaOrigem;

			} /* if */

			ListaRetCaminho = LIS_AvancarElementoCorrente(pGrafo->pListaOrigens, 1);

		}while(ListaRetCaminho != LIS_CondRetFimLista); /* while */

	} /* if */

	LIS_InserirElementoApos(pGrafo->pListaOrigens , VerCorr);

	pGrafo->pCorrente = VerCorr;

	#ifdef _DEBUG	

		pGrafo->qtOrigens++;

    #endif

	return GRA_CondRetOK ;
} /* Fim funcao: GRA &Insere vertice como origem do Grafo */

/***************************************************************************
*
*  Funcao: GRA  &Excluir Aresta
*  ****/

GRA_tpCondRet GRA_ExcluirAresta(char pVertOrig , char pVertDest , GRA_tppGrafo pGrafo)
{
	tpVerticeGrafo * pVertO = NULL;
	tpVerticeGrafo * pVertD = NULL;
	tpArestaGrafo * pAres = NULL;
	
	#ifdef _DEBUG
		CNT_CONTAR( "GRA_ExcluirAresta" ) ;
    #endif

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

	if(ListaRetCaminho == LIS_CondRetOK){

		do{

			LIS_ObterValor (pVertO->pVerSuc , (void**)&pAres);

			if(pAres->pVerticeDest->pIdVertice == pVertDest){

				GRA_excluirValorListaAresta(pAres);

				break;

			} /* if */

			ListaRetCaminho = LIS_AvancarElementoCorrente(pVertO->pVerSuc, 1);

		}while(ListaRetCaminho != LIS_CondRetFimLista); /* while */

	} /* if */

	pGrafo->pCorrente = pVertD;

	#ifdef _DEBUG
		pGrafo->qtArestas--;
	#endif

	return GRA_CondRetOK;
} /* Fim funcao: GRA &Excluir Aresta */

/***************************************************************************
*
*  Funcao: GRA  &Definir vertice corrente
*  ****/

GRA_tpCondRet GRA_DefinirCorrente(GRA_tppGrafo pGrafo, char IdVert)
{

	tpVerticeGrafo * pVerticeBusca ;

	#ifdef _DEBUG
		CNT_CONTAR( "GRA_DefinirCorrente" ) ;
    #endif

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
} /* Fim funcao: GRA &Definir vertice corrente */


/***************************************************************************
*
*  Funcao: GRA  &Excluir vertice
*  ****/


GRA_tpCondRet GRA_ExcluirVerticeCorrente(GRA_tppGrafo pGrafo)

{
	int ts = 0;
	tpVerticeGrafo * pVertOrigem = NULL;
	tpVerticeGrafo * pVerticeCaminho = NULL;
	GRA_tppArestaGrafo pAres = NULL;

	#ifdef _DEBUG
		CNT_CONTAR( "GRA_ExcluirVerticeCorrente" ) ;
    #endif

	LIS_ObterValor(pGrafo->pListaVertices , (void**)&pVertOrigem);

	ListaRet = LIS_IrInicioLista(pVertOrigem->pVerAnt);

	if(ListaRet!=LIS_CondRetListaVazia){
		LIS_NumElem(pVertOrigem->pVerAnt , &ts);
		while(ts>0){

			LIS_ExcluirElemento(pVertOrigem->pVerAnt);

			LIS_NumElem(pVertOrigem->pVerAnt , &ts);

		}

	}
	
	ListaRet = LIS_IrInicioLista(pVertOrigem->pVerSuc);
	ts = 0;
	if(ListaRet!=LIS_CondRetListaVazia){

		LIS_NumElem(pVertOrigem->pVerSuc , &ts);

		while(ts>0){

			LIS_ObterValor (pVertOrigem->pVerSuc , (void**)&pAres);

			GRA_ExcluirAresta(pVertOrigem->pIdVertice , pAres->pVerticeDest->pIdVertice  , pGrafo);

			LIS_ExcluirElemento(pVertOrigem->pVerSuc);

			LIS_NumElem(pVertOrigem->pVerSuc , &ts);
			

		}

	}
	ts = 0;

	GRA_TirarCorrenteDeQualquerSucessor(pVertOrigem, pGrafo);

	pGrafo->pCorrente->destruirValorV(pVertOrigem->pConteudo);
	
	LIS_DestruirLista (pVertOrigem->pVerAnt);
		/* Destroi a lista de antecessores apos eliminar as referencias */

	LIS_DestruirLista (pVertOrigem->pVerSuc);
		/* Destroi a lista de antecessores apos eliminar as referencias */
	
	GRA_ExcluirdeVertices(pGrafo,pVertOrigem);
		/* Destroi a referencia da lista de origens  */

	#ifdef _DEBUG
         pGrafo->qtVertices--;
    #endif

	GRA_ExcluirdeOrigens(pGrafo,pVertOrigem);
		/* Destroi a referencia da lista de vertices */

	ListaRet = LIS_IrInicioLista(pGrafo->pListaVertices);

	if(ListaRet == LIS_CondRetOK){

		do{
			LIS_ObterValor(pGrafo->pListaVertices , (void**)&pVerticeCaminho);

			if(pVerticeCaminho->pIdVertice != pVertOrigem->pIdVertice){
				pGrafo->pCorrente = pVerticeCaminho;
				break;
			}

			LIS_AvancarElementoCorrente(pGrafo->pListaVertices, 1);
		}while(ListaRet != LIS_CondRetFimLista);

	}

	free (pVertOrigem);
	
	pVertOrigem->pIdVertice = '\0';
	pVertOrigem->pConteudo = NULL;

	return GRA_CondRetOK;
	
} /* Fim funcao: GRA &Excluir vertice */



/***************************************************************************
*
*  Função: GRA  &Obter valor do vértice corrente
*  ****/

GRA_tpCondRet GRA_ChecarNomeVerticeCorrente(GRA_tppGrafo pGrafo , char * nomeForn)
{
	char * valorElem;

	#ifdef _DEBUG
		CNT_CONTAR( "GRA_ChecarNomeVerticeCorrente" ) ;
    #endif

	if(pGrafo == NULL){

		return GRA_CondRetGrafoNulo;

	} /* if */
	if(pGrafo->pCorrente == NULL){

		return GRA_CondRetConteudoNulo ;

	} /* if */
	
	valorElem = (char *)pGrafo->pCorrente->pConteudo ;
	

	if(strcmp(valorElem, nomeForn)==0){

		return GRA_CondRetOK ;
 
	} /* if */

	return GRA_CondRetConteudoNulo ;
}

/***************************************************************************
*
*  Funcao: GRA  &Destruir Grafo
*  ****/

GRA_tpCondRet GRA_DestruirGrafo(GRA_tppGrafo pGrafo)
{

	int numElem = 0;

	if(pGrafo==NULL){

		return GRA_CondRetGrafoNulo;

	} /* if */

	#ifdef _DEBUG
		CNT_CONTAR( "GRA_DestruirGrafo" ) ;
    #endif

	LIS_IrInicioLista(pGrafo->pListaVertices);

	LIS_NumElem(pGrafo->pListaVertices , &numElem);

	while(numElem > 0){
		
		GRA_ExcluirVerticeCorrente(pGrafo);

		numElem--;

	} /* while */

	LIS_DestruirLista(pGrafo->pListaOrigens);

	LIS_DestruirLista(pGrafo->pListaVertices);

	#ifdef _DEBUG
		pGrafo->qtOrigens  = 0;
		pGrafo->qtVertices = 0;
		pGrafo->qtArestas  = 0;
    #endif

	free(pGrafo);

    pGrafo  = NULL;

	return GRA_CondRetOK;

} /* Fim funcao: GRA &Destruir Grafo */

/***************************************************************************
*
*  Funcao: GRA  &Avancar corrente
*  ****/

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
} /* Fim funcao: GRA &Avancar corrente */

/***************************************************************************
*
*  Funcao: GRA  &Ir inicio
*  ****/

GRA_tpCondRet GRA_IrInicio(GRA_tppGrafo pGrafo)
{

	ListaRet = LIS_IrInicioLista(pGrafo->pListaVertices);

	if(ListaRet == LIS_CondRetOK){
		return GRA_CondRetOK;
	} /* if */

	return GRA_CondRetNaoAchou;
} /* Fim funcao: GRA &Ir inicio */


#ifdef _DEBUG


static void D_GRA_AtribuiNullSucessor(GRA_tppGrafo pGrafo)
{

	GRA_tppArestaGrafo pAresta;

	LIS_ObterValor(pGrafo->pCorrente->pVerSuc, (void**)&pAresta);

	pAresta->pVerticeDest = NULL;
}

static GRA_tpCondRet V_GRA_VerificaNullSucessor(GRA_tppGrafo pGrafo)
{
	GRA_tppVerGrafo pVertice;
	GRA_tppArestaGrafo pAresta;
	
	if(LIS_IrInicioLista(pGrafo->pListaVertices)==LIS_CondRetOK){

		do{

			LIS_ObterValor(pGrafo->pListaVertices, (void**)&pVertice);

			if(pVertice != NULL){

				if(LIS_IrInicioLista(pVertice->pVerSuc)==LIS_CondRetOK){

					do{
						LIS_ObterValor(pVertice->pVerSuc, (void**)&pAresta);
						if(pAresta->pVerticeDest == NULL){
							CNT_CONTAR( "V_GRA_VerticeSucNulo" ) ;
							TST_NotificarFalha("Encontrado vertice sucessor nulo");
							return GRA_CondRetErroEstrutura;
						}
						ListaRet = LIS_AvancarElementoCorrente(pVertice->pVerSuc, 1);
					}while(ListaRet != LIS_CondRetFimLista);

				}

			}

			ListaRetCaminho = LIS_AvancarElementoCorrente(pGrafo->pListaVertices, 1);

		}while(ListaRetCaminho != LIS_CondRetFimLista);

	}

	return GRA_CondRetOK;
}

static void D_GRA_AtribuiNullAntecessor(GRA_tppGrafo pGrafo)
{

	LIS_ModificaValor(pGrafo->pCorrente->pVerAnt, NULL);

}

static GRA_tpCondRet V_GRA_VerificaNullAntecessor(GRA_tppGrafo pGrafo)
{
	GRA_tppVerGrafo pVertice, pVertCorr;

	if(LIS_IrInicioLista(pGrafo->pListaVertices)==LIS_CondRetOK){

		do{

			LIS_ObterValor(pGrafo->pListaVertices, (void**)&pVertice);

			if(pVertice != NULL){

				if(LIS_IrInicioLista(pVertice->pVerAnt)==LIS_CondRetOK){

					do{
						LIS_ObterValor(pVertice->pVerAnt, (void**)&pVertCorr);
						if(pVertCorr == NULL){
							CNT_CONTAR( "V_GRA_VerticeAntNulo" ) ;
							TST_NotificarFalha("Encontrado vertice antecessor nulo");
							return GRA_CondRetErroEstrutura;
						}
						ListaRet = LIS_AvancarElementoCorrente(pVertice->pVerAnt, 1);
					}while(ListaRet != LIS_CondRetFimLista);

				}

			}

			ListaRetCaminho = LIS_AvancarElementoCorrente(pGrafo->pListaVertices, 1);

		}while(ListaRetCaminho != LIS_CondRetFimLista);

	}

	return GRA_CondRetOK;
}

static void D_GRA_AtribuiLixoSucessor(GRA_tppGrafo pGrafo)
{
	
	GRA_tppArestaGrafo pAresta;

	LIS_ObterValor(pGrafo->pCorrente->pVerSuc, (void**)&pAresta);

	pAresta->pVerticeDest = (GRA_tppVerGrafo)EspacoLixo;

}

static GRA_tpCondRet V_GRA_VerificaLixoSucessor(GRA_tppGrafo pGrafo)
{
	GRA_tppVerGrafo pVertice;
	GRA_tppArestaGrafo pAresta;

	if(LIS_IrInicioLista(pGrafo->pListaVertices)==LIS_CondRetOK){

		do{

			LIS_ObterValor(pGrafo->pListaVertices, (void**)&pVertice);

			if(pVertice != NULL){

				if(LIS_IrInicioLista(pVertice->pVerSuc)==LIS_CondRetOK){

					do{
						LIS_ObterValor(pVertice->pVerSuc, (void**)&pAresta);
						if((CED_tpIdTipoEspaco)CED_ObterTipoEspaco(pAresta->pVerticeDest) != GRA_TipoEspacoVertice){
							CNT_CONTAR( "V_GRA_VerticeSucLixo" ) ;
							TST_NotificarFalha("Encontrado vertice sucessor com tipo incorreto");
							return GRA_CondRetErroEstrutura;
						}
						ListaRet = LIS_AvancarElementoCorrente(pVertice->pVerSuc, 1);
					}while(ListaRet != LIS_CondRetFimLista);

				}

			}

			ListaRetCaminho = LIS_AvancarElementoCorrente(pGrafo->pListaVertices, 1);

		}while(ListaRetCaminho != LIS_CondRetFimLista);

	}

	return GRA_CondRetOK;
}

static void D_GRA_AtribuiLixoAntecessor(GRA_tppGrafo pGrafo)
{
	
	LIS_ModificaValor(pGrafo->pCorrente->pVerAnt, (void*)&EspacoLixo);

}

static GRA_tpCondRet V_GRA_VerificaLixoAntecessor(GRA_tppGrafo pGrafo)
{
	GRA_tppVerGrafo pVertice, pVertCorr;

	if(LIS_IrInicioLista(pGrafo->pListaVertices)==LIS_CondRetOK){

		do{

			LIS_ObterValor(pGrafo->pListaVertices, (void**)&pVertice);

			if(pVertice != NULL){

				if(LIS_IrInicioLista(pVertice->pVerAnt)==LIS_CondRetOK){

					do{
						LIS_ObterValor(pVertice->pVerAnt, (void**)&pVertCorr);
						if((CED_tpIdTipoEspaco)CED_ObterTipoEspaco(pVertCorr) != GRA_TipoEspacoVertice){
							CNT_CONTAR( "V_GRA_VerticeAntLixo" ) ;
							TST_NotificarFalha("Encontrado vertice antecessor com tipo incorreto");
							return GRA_CondRetErroEstrutura;
						}
						ListaRet = LIS_AvancarElementoCorrente(pVertice->pVerAnt, 1);
					}while(ListaRet != LIS_CondRetFimLista);

				}

			}

			ListaRetCaminho = LIS_AvancarElementoCorrente(pGrafo->pListaVertices, 1);

		}while(ListaRetCaminho != LIS_CondRetFimLista);

	}

	return GRA_CondRetOK;
}

static void D_GRA_IsolaVertice(GRA_tppGrafo pGrafo)
{
	GRA_tppVerGrafo VertCorr, VertCorrRet;
	GRA_tppArestaGrafo pAresta;

	LIS_ObterValor(pGrafo->pListaVertices, (void**)&VertCorr);

	LIS_ExcluirElemento(pGrafo->pListaVertices);

	if(LIS_IrInicioLista(pGrafo->pListaOrigens)==LIS_CondRetOK){

		do{

			LIS_ObterValor(pGrafo->pListaOrigens, (void**)&VertCorrRet);

			if(VertCorrRet->pIdVertice == VertCorr->pIdVertice){
				LIS_ExcluirElemento(pGrafo->pListaOrigens);
				break;
			}

			ListaRetCaminho = LIS_AvancarElementoCorrente(pGrafo->pListaOrigens, 1);

		}while(ListaRetCaminho != LIS_CondRetFimLista);

	}

	if(LIS_IrInicioLista(VertCorr->pVerAnt)==LIS_CondRetOK){

		do{

			LIS_ObterValor(VertCorr->pVerAnt, (void**)&VertCorrRet);

			if(LIS_IrInicioLista(VertCorrRet->pVerSuc)==LIS_CondRetOK){
				do{
					LIS_ObterValor(VertCorrRet->pVerSuc, (void**)&pAresta);
					if(pAresta->pVerticeDest->pIdVertice == VertCorr->pIdVertice){
						GRA_ExcluirAresta(pAresta->pVerticeDest->pIdVertice, VertCorr->pIdVertice, pGrafo);
					}
					ListaRetCaminho = LIS_AvancarElementoCorrente(VertCorrRet->pVerSuc, 1);
				}while(ListaRet != LIS_CondRetFimLista);
			}

			ListaRetCaminho = LIS_AvancarElementoCorrente(VertCorr->pVerAnt, 1);

		}while(ListaRetCaminho != LIS_CondRetFimLista);

	}

	if(LIS_IrInicioLista(VertCorr->pVerSuc)==LIS_CondRetOK){

		do{

			LIS_ObterValor(VertCorr->pVerSuc, (void**)&pAresta);

			if(LIS_IrInicioLista(pAresta->pVerticeDest->pVerAnt)==LIS_CondRetOK){
				do{
					LIS_ObterValor(pAresta->pVerticeDest->pVerAnt, (void**)&VertCorrRet);
					if(VertCorrRet->pIdVertice == VertCorr->pIdVertice){
						LIS_ExcluirElemento(pAresta->pVerticeDest->pVerAnt);
					}
					ListaRetCaminho = LIS_AvancarElementoCorrente(pAresta->pVerticeDest->pVerAnt, 1);
				}while(ListaRet != LIS_CondRetFimLista);
			}

			ListaRetCaminho = LIS_AvancarElementoCorrente(VertCorr->pVerSuc, 1);

		}while(ListaRetCaminho != LIS_CondRetFimLista);

	}


}

static GRA_tpCondRet V_GRA_VerificaVerticeIsolado(GRA_tppGrafo pGrafo)
{
	int NumElem = 0, NumErros = 0;
	LIS_NumElem(pGrafo->pListaVertices, &NumElem);
	if(NumElem != pGrafo->qtVertices){
		CNT_CONTAR( "V_GRA_VerticeQtdeInvalida" ) ;
		TST_NotificarFalha("Encontrado vertice fora do grafo");
		NumErros++;
	}
	NumElem = 0;
	LIS_NumElem(pGrafo->pListaOrigens, &NumElem);
	if(NumElem != pGrafo->qtOrigens){
		CNT_CONTAR( "V_GRA_VerticeOrigemQtdeInvalida" ) ;
		TST_NotificarFalha("Encontrado vertice fora do grafo");
		NumErros++;
	}

	if(NumErros > 0){
		return GRA_CondRetErroEstrutura;
	}
	return GRA_CondRetOK;
}

static GRA_tpCondRet V_GRA_VerificaConteudoNulo(GRA_tppGrafo pGrafo)
{
    GRA_tppVerGrafo pVertice;

	if(LIS_IrInicioLista(pGrafo->pListaVertices)==LIS_CondRetOK){

		do{

			LIS_ObterValor(pGrafo->pListaVertices, (void**)&pVertice);

			if(pVertice->pConteudo == NULL){
				CNT_CONTAR( "V_GRA_VerticeContNulo" ) ;
				TST_NotificarFalha("Encontrado vertice com conteudo nulo.");
				return GRA_CondRetErroEstrutura;
			}

			ListaRetCaminho = LIS_AvancarElementoCorrente(pGrafo->pListaVertices, 1);

		}while(ListaRetCaminho != LIS_CondRetFimLista);

	}
	return GRA_CondRetOK;
}

static GRA_tpCondRet V_GRA_VerificaTipoVertice(GRA_tppGrafo pGrafo)
{
    GRA_tppVerGrafo pVertice;

	if(LIS_IrInicioLista(pGrafo->pListaVertices)==LIS_CondRetOK){

		do{

			LIS_ObterValor(pGrafo->pListaVertices, (void**)&pVertice);

			if(pVertice != NULL){
				if((CED_tpIdTipoEspaco)CED_ObterTipoEspaco(pVertice) != GRA_TipoEspacoVertice){
					CNT_CONTAR( "V_GRA_VerticeTipoErrado" ) ;
					TST_NotificarFalha("Encontrado elemento na lista de vertices que nao e vertice.");
					return GRA_CondRetErroEstrutura;
				}
			}

			ListaRetCaminho = LIS_AvancarElementoCorrente(pGrafo->pListaVertices, 1);

		}while(ListaRetCaminho != LIS_CondRetFimLista);

	}
	return GRA_CondRetOK;
}

static GRA_tpCondRet V_GRA_VerificaOrigemNula(GRA_tppGrafo pGrafo)
{
    GRA_tppVerGrafo pVertice;

	if(LIS_IrInicioLista(pGrafo->pListaOrigens)==LIS_CondRetOK){

		do{

			LIS_ObterValor(pGrafo->pListaOrigens, (void**)&pVertice);
			if(pVertice == NULL){
				CNT_CONTAR( "V_GRA_VerticeOrigNulo" ) ;
				TST_NotificarFalha("Encontrado elemento na lista de origens nulo.");
				return GRA_CondRetErroEstrutura;
			}

			ListaRetCaminho = LIS_AvancarElementoCorrente(pGrafo->pListaOrigens, 1);

		}while(ListaRetCaminho != LIS_CondRetFimLista);

	}
	return GRA_CondRetOK;
}

/***************************************************************************
*
*  Funcao: GRA  &Deturpar Grafo
*  ****/

GRA_tpCondRet GRA_DeturparGrafo(GRA_tppGrafo pGrafo,  GRA_tpTiposDeturpacao ModoDeturpar )
{

	 switch ( ModoDeturpar ) {

         case DeturpaEliminaCorr :
			 {
				 
				CNT_CONTAR( "D_GRA_DeturpaCorrente" ) ;

				free(pGrafo->pCorrente);

				break;

			 }

		 case DeturpaSucessorVertice:
			{
				CNT_CONTAR( "D_GRA_DeturpaNullSucessor" ) ;
				
				D_GRA_AtribuiNullSucessor(pGrafo);

				break;

			}
		 case DeturpaAntecessorVertice:
			 {
				 CNT_CONTAR( "D_GRA_DeturpaNullAntecessor" ) ;
				
				 D_GRA_AtribuiNullAntecessor(pGrafo);

				 break;
			 }

		 case DeturpaSucessorLixo:
			 {
				CNT_CONTAR( "D_GRA_DeturpaLixoSucessor" ) ;

				D_GRA_AtribuiLixoSucessor(pGrafo);

				break;
			 }

		 case DeturpaAntecessorLixo:
			 {
				 CNT_CONTAR( "D_GRA_DeturpaLixoAntecessor" ) ;
				
				 D_GRA_AtribuiLixoAntecessor(pGrafo);

				 break;
			 }

		 case DeturpaConteudoVertice:
			 {

				 CNT_CONTAR( "D_GRA_DeturpaNullConteudo" ) ;

				 pGrafo->pCorrente->pConteudo = NULL;

				 break;
			 }

		 case DeturpaAlteraTipoVertice:
			 {
				 CNT_CONTAR( "D_GRA_DeturpaAlteraTipo" ) ;

				 CED_DefinirTipoEspaco( pGrafo->pCorrente , CED_ID_TIPO_VALOR_NULO ) ;

				 break;
			 }

		 case DeturpaIsolaVertice:
			 {
				 
				 CNT_CONTAR( "D_GRA_DeturpaIsolaVertice" ) ;

				 D_GRA_IsolaVertice(pGrafo);

				 break;
			 }

		 case DeturpaNullCorrente:
			 {
				 CNT_CONTAR( "D_GRA_DeturpaNullCorrente" ) ;

				 pGrafo->pCorrente = NULL;

				 break;
			 }

		 case DeturpaNullOrigem:
			 {
				 CNT_CONTAR( "D_GRA_DeturpaNullOrigem" ) ;

				 LIS_IrInicioLista(pGrafo->pListaOrigens);

				 LIS_ModificaValor(pGrafo->pListaOrigens, NULL);

				 break;

			 }

	 }

	 return GRA_CondRetOK;
	
} /* Fim funcao: GRA &Deturpar Grafo */

#endif

#ifdef _DEBUG

/***************************************************************************
*
*  Funcao: GRA  &Verificar Grafo
*  ****/

GRA_tpCondRet GRA_VerificarGrafo(GRA_tppGrafo pGrafo)
{
	GRA_tpCondRet gRetorno;
	int NumElem = 0;

	int totalErros = 0;

	if ( ! pGrafo )
	{
		CNT_CONTAR( "V_GRA_GrafoInexistente" ) ;
		TST_NotificarFalha( "Tentou verificar grafo nao existente." ) ;
		return GRA_CondRetErroEstrutura;
	}

	LIS_NumElem(pGrafo->pListaVertices, &NumElem);
	if(NumElem > 0){
		if ( TST_CompararInt( CED_ID_TIPO_ILEGAL ,
			   CED_ObterTipoEspaco( pGrafo->pCorrente ) ,
			   "Tipo do espaço de dados não é vertice" ) == TST_CondRetOK ||
			   TST_CompararInt( CED_ID_TIPO_VALOR_NULO ,
			   CED_ObterTipoEspaco( pGrafo->pCorrente ) ,
			   "Tipo do espaço de dados não é vertice" ) == TST_CondRetOK 
			   )
		{
			CNT_CONTAR( "V_GRA_VerticeCorrNulo");
			return GRA_CondRetErroEstrutura;
		}
	}else{
		return GRA_CondRetOK;
	}

	if(pGrafo->pCorrente == NULL)
	{
		CNT_CONTAR( "V_GRA_VerticeCorrNulo");
		totalErros++;
	}

	 if (CED_ObterTipoEspaco( pGrafo ) != GRA_TipoEspacoCabeca )
    {
		CNT_CONTAR( "V_GRA_ErroTipoCabeca" ) ;
    } /* if */
	 
  
	gRetorno = V_GRA_VerificaNullSucessor (pGrafo);
	if(gRetorno != GRA_CondRetOK){
		totalErros++;
	}

    gRetorno = V_GRA_VerificaNullAntecessor (pGrafo);
	if(gRetorno != GRA_CondRetOK){
		totalErros++;
	}
	gRetorno = V_GRA_VerificaLixoSucessor (pGrafo);
	if(gRetorno != GRA_CondRetOK){
		totalErros++;
	}

	gRetorno = V_GRA_VerificaLixoAntecessor (pGrafo);
	if(gRetorno != GRA_CondRetOK){
		totalErros++;
	}

	gRetorno = V_GRA_VerificaConteudoNulo (pGrafo);
	if(gRetorno != GRA_CondRetOK){
		totalErros++;
	}

	gRetorno = V_GRA_VerificaVerticeIsolado (pGrafo);
	if(gRetorno != GRA_CondRetOK){
		totalErros++;
	}
	gRetorno = V_GRA_VerificaTipoVertice (pGrafo);
	if(gRetorno != GRA_CondRetOK){
		totalErros++;
	}
	
	gRetorno = V_GRA_VerificaOrigemNula (pGrafo);
	if(gRetorno != GRA_CondRetOK){
		totalErros++;
	}

	if(totalErros > 0){
		return GRA_CondRetErroEstrutura;
	}


	return GRA_CondRetOK;
	
} /* Fim funcao: GRA &Verificar Grafo */

#endif


/*****  Codigo das funcoes encapsuladas pelo modulo  *****/

/***********************************************************************
*
*  $FC Funcao: GRA  -Limpa o conteudo da lista de vertices do grafo 
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
			break;
		} /* if */
		if(ListaRet == LIS_CondRetFimLista){
			break;
		} /* if */
		ListaRet = LIS_AvancarElementoCorrente(pGrafo->pListaVertices, 1);

	} /* while */
	

} /* Fim funcao: GRA -Limpa o conteudo da lista de vertices do grafo  */


/***********************************************************************
*
*  $FC Funcao: GRA  -Limpa o conteudo da lista de origens do grafo 
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

			#ifdef _DEBUG
				pGrafo->qtOrigens--;
			#endif

			break;
		} /* if */
		if(ListaRet == LIS_CondRetFimLista){
			break;
		} /* if */
		ListaRet = LIS_AvancarElementoCorrente(pGrafo->pListaOrigens, 1);

	} /* while */



} /* Fim funcao: GRA -Limpa o conteudo da lista de origens do grafo  */

/***************************************************************************
*
*  Funcao: GRA  -Criar Lista de origens Grafo
*
*************************************************************************/

void GRA_CriaListaOrigens( GRA_tppGrafo pGrafo )
{

	LIS_tppLista pListaOrig ;

	LIS_CriarLista (GRA_excluirValorLista , &pListaOrig);

	pGrafo->pListaOrigens = pListaOrig ;

} /* Fim funcao: GRA  -Criar Lista de origens Grafo */


/***************************************************************************
*
*  Funcao: GRA  -Criar Lista de vertices Grafo
*
*************************************************************************/

void GRA_CriaListaVertices( GRA_tppGrafo pGrafo )
{
	
	LIS_tppLista pListaVert ;

	LIS_CriarLista (GRA_excluirValorLista, &pListaVert);

	pGrafo->pListaVertices= pListaVert ;

} /* Fim funcao: GRA  -Criar Lista de vertices Grafo */


/***************************************************************************
*
*  Funcao: GRA  -Criar Lista de sucessores do vertice do Grafo
*
*************************************************************************/

void GRA_CriaListaSucessoresVertice(tpVerticeGrafo * pVertice)
{

	LIS_tppLista pListaSuc ;

	LIS_CriarLista (GRA_excluirValorLista, &pListaSuc);

	pVertice->pVerSuc = pListaSuc ;

} /* Fim funcao: GRA  -Criar Lista de sucessores do vertice do Grafo */


/***************************************************************************
*
*  Funcao: GRA  -Criar Lista de antecessores do vertice do Grafo
*
*************************************************************************/

void GRA_CriaListaAntecessoresVertice(tpVerticeGrafo * pVertice)
{

	LIS_tppLista pListaAnt ;

	LIS_CriarLista (GRA_excluirValorLista , &pListaAnt);

	pVertice->pVerAnt = pListaAnt ;

} /* Fim funcao: GRA  -Criar Lista de antecessores do vertice do Grafo */


/***************************************************************************
*
*  Funcao: GRA  -Excluir valor lista
*
****************************************************************************/

void GRA_excluirValorLista ( void * pValor )
{



} /* Fim funcao: GRA  -Excluir valor lista */


/***************************************************************************
*
*  Funcao: GRA  -Excluir valor lista do tipo Aresta
*
****************************************************************************/

void GRA_excluirValorListaAresta ( tpArestaGrafo * pAresta )
{

	free(pAresta);

} /* Fim funcao: GRA  -Excluir valor lista do tipo Aresta */


/***************************************************************************
*
*  Funcao: GRA  -Avancar Vertice corrente
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
} /* Fim funcao: GRA  -Avancar Vertice corrente */


/***************************************************************************
*
*  Funcao: GRA  -Destruir valor do grafo
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

} /* Fim funcao: GRA  -Destruir valor do grafo */



/***************************************************************************
*
*  Funcao: GRA  -Buscar Vertice
*
****************************************************************************/

tpVerticeGrafo * GRA_BuscarVertice(GRA_tppGrafo pGrafo , char Id)
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

}  /* Fim funcao: GRA -Buscar Vertice */

/***************************************************************************
*
*  Funcao: GRA  -Limpar conteudo de aresta
*
****************************************************************************/

void LiberarAresta(GRA_tppArestaGrafo pAres)
{
	pAres->Nome = NULL;
	pAres->pVerticeDest = NULL;
	free(pAres);
	pAres = NULL;
} /* Fim funcao: GRA -Limpar conteudo de aresta */

/***************************************************************************
*
*  Funcao: GRA  -Checa se aresta existe
*
****************************************************************************/

int ChecaArestaExiste(tpVerticeGrafo * pVertice , char * String, char Dest)
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
} /* Fim funcao: GRA -Checa se aresta existe */

/***************************************************************************
*
*  Funcao: GRA  -Checa se vertice existe
*
****************************************************************************/

int ChecaVerticeExiste(GRA_tppGrafo pGrafo, char Vert)
{
	tpVerticeGrafo * pVertice;

	if(pGrafo==NULL){
		return 0;
	} /* if */

	ListaRetCaminho=LIS_IrInicioLista(pGrafo->pListaVertices);
	
	while(ListaRetCaminho==LIS_CondRetOK || ListaRetCaminho==LIS_CondRetFimLista){

		LIS_ObterValor(pGrafo->pListaVertices , (void**)&pVertice);

		if(pVertice->pIdVertice == Vert){

			return 1;

		} /* if */

		if(ListaRetCaminho == LIS_CondRetFimLista){

			return 0;

		} /* if */

		ListaRetCaminho = LIS_AvancarElementoCorrente(pGrafo->pListaVertices, 1);

	} /* while */

	pVertice = NULL;

	return 0;
} /* Fim funcao: GRA -Checa se vertice existe */

/***************************************************************************
*
*  Funcao: GRA  -Elimina referencias de aresta
*
****************************************************************************/
static void GRA_TirarCorrenteDeQualquerSucessor(GRA_tppVerGrafo pVertice, GRA_tppGrafo pGrafo)
{
	GRA_tppVerGrafo pVert, pVertCorr;
	GRA_tppArestaGrafo pAres;

	ListaRet = LIS_IrInicioLista(pGrafo->pListaVertices);
	if(ListaRet != LIS_CondRetListaVazia){

		do{
			LIS_ObterValor(pGrafo->pListaVertices, (void**)&pVert);

			if(pVert->pIdVertice != pVertice->pIdVertice){
				/* Elimina da lista de antecessores */
				ListaRetCaminho = LIS_IrInicioLista(pVert->pVerAnt);
				if(ListaRetCaminho != LIS_CondRetListaVazia){
					do{
						LIS_ObterValor(pVert->pVerAnt, (void**)&pVertCorr);
						if(pVertCorr->pIdVertice == pVertice->pIdVertice){
							LIS_ExcluirElemento(pVert->pVerAnt);
							break;
						}else{
						ListaRetCaminho = LIS_AvancarElementoCorrente(pVert->pVerAnt, 1);
						}
					}while(ListaRetCaminho != LIS_CondRetFimLista);
				}

				/* Elimina da lista de sucessores */
				ListaRetCaminho = LIS_IrInicioLista(pVert->pVerSuc);
				if(ListaRetCaminho != LIS_CondRetListaVazia){
					do{
						LIS_ObterValor(pVert->pVerSuc, (void**)&pAres);
						if(pAres->pVerticeDest->pIdVertice == pVertice->pIdVertice){
							GRA_ExcluirAresta(pVert->pIdVertice , pVertice->pIdVertice  , pGrafo);
							LIS_ExcluirElemento(pVert->pVerSuc);
							break;
						}else{
						ListaRetCaminho = LIS_AvancarElementoCorrente(pVert->pVerSuc, 1);
						}
					}while(ListaRetCaminho != LIS_CondRetFimLista);
				}
			}

			ListaRet = LIS_AvancarElementoCorrente(pGrafo->pListaVertices, 1);
		}while(ListaRet!=LIS_CondRetFimLista);

	}

	LIS_SetarCorrente(pGrafo->pListaVertices, pVertice);
	
} /* Fim funcao: GRA -Elimina referencias de aresta */


#ifdef _DEBUG

/***************************************************************************
*
*  Funcao: GRA  -Checa sucessores do vertice
*
****************************************************************************/

static int VerificaSucessoresVertice(GRA_tppVerGrafo pVertice)
{
	GRA_tppArestaGrafo pAres;

	if(LIS_IrInicioLista(pVertice->pVerSuc)==LIS_CondRetOK){

		do{

			LIS_ObterValor(pVertice->pVerSuc, (void**)&pAres);

			if(pAres->pVerticeDest == NULL){
				return 1;
			}

			ListaRetCaminho = LIS_AvancarElementoCorrente(pVertice->pVerSuc, 1);

		}while(ListaRetCaminho != LIS_CondRetFimLista);

	}
	return 0;
} /* Fim funcao: GRA -Checa sucessores do vertice */

static int VerificaAntecessoresVertice(GRA_tppVerGrafo pVertice)
{
	GRA_tppVerGrafo pVert;

	ListaRetCaminho = LIS_IrInicioLista(pVertice->pVerAnt);
	if(ListaRetCaminho == LIS_CondRetOK){
		do{
			
			LIS_ObterValor(pVertice->pVerAnt, (void**)&pVert);

			if(pVert == NULL){
				return 1;
			}

			ListaRetCaminho = LIS_AvancarElementoCorrente(pVertice->pVerAnt, 1);

		}while(ListaRetCaminho != LIS_CondRetFimLista);
	}

	return 0;
} /* Fim funcao: GRA -Checa sucessores do vertice */

static int VerificaLixoAntecessoresVertice(GRA_tppVerGrafo pVertice)
{

	GRA_tppVerGrafo pVert;
	ListaRetCaminho = LIS_IrInicioLista(pVertice->pVerAnt);
	if(ListaRetCaminho == LIS_CondRetOK){
		do{

			LIS_ObterValor(pVertice->pVerAnt, (void**)&pVert);

			if (  GRA_TipoEspacoVertice != CED_ObterTipoEspaco( pVert ) )
			  {
				 return 1 ;
			  } /* if */

			ListaRetCaminho = LIS_AvancarElementoCorrente(pVertice->pVerAnt, 1);

		}while(ListaRetCaminho != LIS_CondRetFimLista);
	}

	return 0;
}

static int VerificaLixoSucessoresVertice(GRA_tppVerGrafo pVertice)
{

	GRA_tppArestaGrafo pAres;
	ListaRetCaminho = LIS_IrInicioLista(pVertice->pVerSuc);

	if(ListaRetCaminho == LIS_CondRetOK){
		do{

			LIS_ObterValor(pVertice->pVerSuc, (void**)&pAres);

			if (  GRA_TipoEspacoVertice != CED_ObterTipoEspaco( pAres->pVerticeDest ) )
			  {
				 return 1 ;
			  } /* if */

			ListaRetCaminho = LIS_AvancarElementoCorrente(pVertice->pVerSuc, 1);

		}while(ListaRetCaminho != LIS_CondRetFimLista);
	}

	return 0;
}

#endif

/********** Fim do modulo de implementacao: Modulo GRAFO **********/
