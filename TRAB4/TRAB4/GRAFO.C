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

	#ifdef _DEBUG

		GRA_tppVerGrafo pVerticeOrig;
		/* Ponteiro do Elemento tpVerticeGrafo origem */

	#endif

	
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

	char pIdVertice[2];
		/* Identificador do vertice */

	void (*destruirValorV)(void *pValor);
        /* Destruir Valor do conteudo do vertice */

	#ifdef _DEBUG

	    GRA_tppGrafo ptCabeca ;
			/* Armazena um identificador para o tipo de informação encapsulada */

		int qtArestas ;
		   /* Armazena a quantidade de arestas */

		int qtAntecessores;
		    /* Armazena a quantidade de antecessores */

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

    #endif


} GRA_tpGrafo ;

/************* Dados encapsuladas no modulo *************************/

#ifdef _DEBUG

	static char EspLixo[ 10 ] = "ABCDEFGHI" ;
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
		                               char * Id             ) ;
 
	/* Funcao libera espaco alocado para pAres */
	static void LiberarAresta(GRA_tppArestaGrafo pAres);
 
	/* Funcao checa se a aresta e valida */
	static int ChecaArestaExiste (tpVerticeGrafo * pVertice , 
		                         char * String, 
								 char * Dest                 );
 
	/* Funcao checa se o vertice e valido */
	static int ChecaVerticeExiste(GRA_tppGrafo pGrafo, 
		                          char * Vert         );

	#ifdef _DEBUG

		/* Funcao checa sucessores do vertice diferentes de NULL */
		static int VerificaSucessoresVertice(GRA_tppVerGrafo pVertice);

	#endif

/************* Codigo das funcoes exportadas pelo modulo ******************/
	
/***************************************************************************
*
*  Funcao: GRA  &Criar Grafo
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

	#ifdef _DEBUG

         CED_DefinirTipoEspaco( pGrafo , GRA_TipoEspacoCabeca ) ;

         mGrafo->qtVertices = 0;
		 mGrafo->qtOrigens  = 0;
		 mGrafo->qtArestas  = 0;

    #endif

	(*pGrafo) = mGrafo;

	
	return GRA_CondRetOK;
} /* Fim funcao: GRA &Criar Grafo */

/***************************************************************************
*
*  Funcao: GRA  &Criar Vertice Grafo
*  ****/

GRA_tpCondRet GRA_CriaVerticeGrafo(GRA_tppGrafo pGrafo, char * String , char * id, void   ( * ExcluirValor ) ( void * pDado ))
{
	GRA_tppVerGrafo pVert;
	int ret = 0;

	if(pGrafo==NULL){

		#ifdef _DEBUG
			TST_NotificarFalha( "Tentou verificar GRAFO inexistente." ) ;
            return GRA_CondRetErroEstrutura ;
		#endif
		
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
	pVert->pConteudo = String ;
	pVert->destruirValorV = ExcluirValor ;
	GRA_CriaListaSucessoresVertice (pVert);
	GRA_CriaListaAntecessoresVertice (pVert);
	
	LIS_InserirElementoApos(pGrafo->pListaVertices, pVert );
		/* Insere vertice na lista de vertices do grafo */

	
	pGrafo->pCorrente = pVert;

	#ifdef _DEBUG

		CED_DefinirTipoEspaco( pGrafo , GRA_TipoEspacoVertice ) ;	

        pGrafo->qtVertices++;

		pGrafo->pCorrente->ptCabeca = pGrafo;

    #endif

	return GRA_CondRetOK ;

	
} /* Fim funcao: GRA &Criar Vertice Grafo */

/***************************************************************************
*
*  Funcao: GRA  &Criar Aresta do vertice Grafo
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

	#ifdef _DEBUG
		pAres->pVerticeOrig = pVertO;
	#endif

	pGrafo->pCorrente = pVertO;
	LIS_InserirElementoApos(pGrafo->pCorrente->pVerSuc , pAres);
		/* Inserir aresta na lista de sucessores do vertorigem */

	pGrafo->pCorrente = pVertD;
	LIS_InserirElementoApos(pGrafo->pCorrente->pVerAnt , pVertO);
		/* Inserir vertice na lista de antecessores do vertdestino */

	#ifdef _DEBUG

		CED_DefinirTipoEspaco( pAres , GRA_TipoEspacoAresta ) ;

		pVertO->qtArestas++;

		pVertD->qtAntecessores++;

    #endif

	return GRA_CondRetOK ;
} /* Fim funcao: GRA &Criar Aresta do vertice Grafo */

/***************************************************************************
*
*  Funcao: GRA  &Insere vertice como origem do Grafo
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

	#ifdef _DEBUG	

		pGrafo->qtOrigens++;

    #endif

	return GRA_CondRetOK ;
} /* Fim funcao: GRA &Insere vertice como origem do Grafo */

/***************************************************************************
*
*  Funcao: GRA  &Excluir Aresta
*  ****/

GRA_tpCondRet GRA_ExcluirAresta(char * pVertOrig , char * pVertDest , GRA_tppGrafo pGrafo)
{
	tpVerticeGrafo * pVertO = NULL;
	tpVerticeGrafo * pVertD = NULL;
	tpArestaGrafo * pAres = NULL;
	
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

		if(strcmp(pAres->pVerticeDest->pIdVertice, pVertDest)==0){

			GRA_excluirValorListaAresta(pAres);

			LIS_ExcluirElemento(pVertO->pVerSuc);

			#ifdef _DEBUG
				pVertO->qtArestas--;
			#endif

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

		if(strcmp(pVertO->pIdVertice, pVertOrig)==0){

			LIS_ExcluirElemento(pVertD->pVerAnt);

			#ifdef _DEBUG
				pVertD->qtAntecessores--;
			#endif

			break;

		} /* if */
		if(ListaRetCaminho == LIS_CondRetFimLista){
			break;
		} /* if */
		ListaRetCaminho = LIS_AvancarElementoCorrente(pVertD->pVerAnt, 1);

	} /* while */


	return GRA_CondRetOK;
} /* Fim funcao: GRA &Excluir Aresta */

/***************************************************************************
*
*  Funcao: GRA  &Definir vertice corrente
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

	if(ListaRet!=LIS_CondRetListaVazia){

		do{

			LIS_ObterValor (pVertOrigem->pVerSuc , (void**)&pAres);

			GRA_ExcluirAresta(pVertOrigem->pIdVertice , pAres->pVerticeDest->pIdVertice  , pGrafo);

			LIS_ExcluirElemento(pVertOrigem->pVerSuc);

			LIS_NumElem(pVertOrigem->pVerSuc , &ts);

		}while(ListaRet != LIS_CondRetFimLista);

	}

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

	#ifdef _DEBUG
		pGrafo->qtOrigens--;
    #endif


	ListaRet = LIS_IrInicioLista(pGrafo->pListaVertices);
	if(ListaRet == LIS_CondRetOK){
		LIS_ObterValor(pGrafo->pListaVertices , (void**)&pVerticeCaminho);
		pGrafo->pCorrente = pVerticeCaminho;
	}
	
	free (pVertOrigem);
	
	strcpy(pVertOrigem->pIdVertice , "");
	pVertOrigem->pConteudo = NULL;

	return GRA_CondRetOK;
	
} /* Fim funcao: GRA &Excluir vertice */

/***************************************************************************
*
*  Funcao: GRA  &Obter valor por referencia
*  ****/

GRA_tpCondRet GRA_ObterValorCorrente(GRA_tppGrafo pGrafo , void ** pValor)
{

	if(pGrafo == NULL){

		return GRA_CondRetGrafoNulo;

	} /* if */
	
	*pValor = pGrafo->pCorrente->pConteudo;

	return GRA_CondRetOK ;
} /* Fim funcao: GRA &Obter valor por referencia */

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

	pGrafo  = NULL;

	free(pGrafo);



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

/***************************************************************************
*
*  Funcao: GRA  &Buscar Id do vertice
*  ****/

GRA_tpCondRet GRA_BuscaIdVertice(GRA_tppGrafo pGrafo , char ** pValor)
{
	GRA_tppVerGrafo pVert;

	if(pGrafo == NULL){
		return GRA_CondRetGrafoNulo;
	} /* if */

	LIS_ObterValor(pGrafo->pListaVertices , (void**)&pVert);

	*pValor = pVert->pIdVertice;

	return GRA_CondRetOK;
} /* Fim funcao: GRA &Buscar Id do vertice */


/***************************************************************************
*
*  Funcao: GRA  &Numero de aresta do vertice
*  ****/

GRA_tpCondRet GRA_NumeroArestaVertice(GRA_tppGrafo pGrafo , int * Num)
{

	if(pGrafo == NULL){
		return GRA_CondRetGrafoNulo;
	} /* if */

	LIS_NumElem(pGrafo->pCorrente->pVerSuc , Num);

	return GRA_CondRetOK;

} /* Fim funcao: GRA &Numero de aresta do vertice */


/***************************************************************************
*
*  Funcao: GRA  &Setar corrente
*  ****/

GRA_tpCondRet GRA_SetarCorrente(GRA_tppGrafo pGrafo , char * pValor)
{

	GRA_tppVerGrafo mVert;

	ListaRet = LIS_IrInicioLista(pGrafo->pListaVertices);

	do{

		LIS_ObterValor(pGrafo->pListaVertices , (void**)&mVert);

		if(mVert != NULL){
			if(strcmp(mVert->pIdVertice , pValor)==0){
				pGrafo->pCorrente = mVert;
				return GRA_CondRetOK;
			}
		}
		ListaRet = LIS_AvancarElementoCorrente(pGrafo->pListaVertices , 1);

	}while(ListaRet!=LIS_CondRetFimLista);

	return GRA_CondRetListaNula;
} /* Fim funcao: GRA &Setar corrente */

/***************************************************************************
*
*  Funcao: GRA  &Numero de vertices
*  ****/

GRA_tpCondRet GRA_NumeroVertices(GRA_tppGrafo pGrafo , int * val)
{

	ListaRet  = LIS_NumElem(pGrafo->pListaVertices , val);


	return GRA_CondRetOK;

} /* Fim funcao: GRA &Numero de vertices */


/***************************************************************************
*
*  Funcao: GRA  &Insere conteudo do vertice
*  ****/

GRA_tpCondRet GRA_InsereConteudoVertice(GRA_tppGrafo pGrafo , void * pConteudo)
{

	if(pGrafo == NULL) {
		return GRA_CondRetGrafoNulo;
	} /* if */

	pGrafo->pCorrente->pConteudo = pConteudo;

	return GRA_CondRetOK;
} /* Fim funcao: GRA &Insere conteudo do vertice */


/***************************************************************************
*
*  Funcao: GRA  &Pega conteudo
*  ****/

GRA_tpCondRet GRA_PegaConteudoCorrente(GRA_tppGrafo pGrafo , void ** pConteudo)
{
	GRA_tppVerGrafo  Vert = NULL;

	if(pGrafo == NULL) {
		return GRA_CondRetGrafoNulo;
	} /* if */

	LIS_ObterValor(pGrafo->pListaVertices , (void**)&Vert);

	*pConteudo = Vert->pConteudo;

	return GRA_CondRetOK;

} /* Fim funcao: GRA &Pega conteudo */

/***************************************************************************
*
*  Funcao: GRA  &Ir inicio da aresta
*  ****/

GRA_tpCondRet GRA_IrInicioAresta(GRA_tppGrafo pGrafo)
{

	LIS_tppLista pLista;

	pLista = pGrafo->pCorrente->pVerSuc;

	LIS_IrInicioLista(pLista);

	return GRA_CondRetOK;

} /* Fim funcao: GRA &Ir inicio da aresta */


/***************************************************************************
*
*  Funcao: GRA  &Obter aresta do vertice
*  ****/

GRA_tpCondRet GRA_ObterArestaVertice(GRA_tppGrafo pGrafo , void ** rVertice , char * Aresta)
{

	LIS_tppLista pLista;
	GRA_tppVerGrafo pCorr;
	GRA_tppArestaGrafo pAresta;

	LIS_ObterValor(pGrafo->pListaVertices , (void**)&pCorr);

	pLista = pCorr->pVerSuc;

	ListaRet = LIS_IrInicioLista(pLista);

	if(ListaRet == LIS_CondRetListaVazia){
		return GRA_CondRetListaNula;
	}

	do{

		LIS_ObterValor(pLista , (void**)&pAresta);

		if(strcmp(pAresta->Nome ,Aresta)==0){
			*rVertice = pAresta->pVerticeDest;
			GRA_SetarCorrente(pGrafo , pAresta->pVerticeDest->pIdVertice);
			break;
		}

		ListaRet = LIS_AvancarElementoCorrente(pLista , 1);

	}while(ListaRet != LIS_CondRetFimLista);

	return GRA_CondRetOK;

} /* Fim funcao: GRA &Obter aresta do vertice */


/***************************************************************************
*
*  Funcao: GRA  &Avancar Aresta do Vertice
*  ****/

GRA_tpCondRet GRA_AvancarArestaVertice(GRA_tppGrafo pGrafo , int val)
{

	LIS_tppLista pLista;

	pLista = pGrafo->pCorrente->pVerSuc;

	LIS_AvancarElementoCorrente(pLista , val);

	return GRA_CondRetOK;
	
} /* Fim funcao: GRA &Avancar Aresta do Vertice */


#ifdef _DEBUG

/***************************************************************************
*
*  Funcao: GRA  &Deturpar Grafo
*  ****/

GRA_tpCondRet GRA_DeturparGrafo(GRA_tppGrafo pGrafo,  GRA_tpTiposDeturpacao ModoDeturpar )
{

	 switch ( ModoDeturpar ) {

         case DeturpaEliminaCorr :
			 {
				 
				free(pGrafo->pCorrente);

				break;

			 }

		 case DeturpaSucessorVertice:
			{
				GRA_tppVerGrafo pVertice;
				GRA_tppArestaGrafo pAresta;

				LIS_IrInicioLista(pGrafo->pListaVertices);

				LIS_ObterValor(pGrafo->pListaVertices, (void**)&pVertice);

				LIS_IrInicioLista(pVertice->pVerSuc);

				LIS_ObterValor(pVertice->pVerSuc, (void**)&pAresta);

				pAresta->pVerticeDest = NULL;

				break;

			}
		 case DeturpaAntecessorVertice:
			 {
				GRA_tppVerGrafo pVertice;
				GRA_tppVerGrafo pVerticeAnt;

				LIS_IrInicioLista(pGrafo->pListaVertices);

				LIS_ObterValor(pGrafo->pListaVertices, (void**)&pVertice);

				LIS_IrInicioLista(pVertice->pVerAnt);

				LIS_ObterValor(pVertice->pVerSuc, (void**)&pVerticeAnt);

				pVerticeAnt = NULL;

				 break;
			 }

		 case DeturpaSucessorLixo:
			 {
				 GRA_tppVerGrafo pVertice;
				 GRA_tppVerGrafo pVerticeDet;
				 LIS_ObterValor(pGrafo->pListaVertices, (void**)&pVertice);

				 LIS_ObterValor(pVertice->pVerSuc, (void**)&pVerticeDet);

				 pVerticeDet = (GRA_tppVerGrafo)EspLixo;

				 break;
			 }

		 case DeturpaAntecessorLixo:
			 {
				 GRA_tppVerGrafo pVertice;
				 GRA_tppVerGrafo pVerticeDet;
				 LIS_ObterValor(pGrafo->pListaVertices, (void**)&pVertice);

				 LIS_ObterValor(pVertice->pVerAnt, (void**)&pVerticeDet);

				 pVerticeDet = (GRA_tppVerGrafo)EspLixo;

				 break;
			 }

		 case DeturpaConteudoVertice:
			 {
				 void * pConteudo;

				 GRA_PegaConteudoCorrente(pGrafo, (void**)&pConteudo);

				 pConteudo = NULL;

				 break;
			 }

		 case DeturpaAlteraTipoVertice:
			 {
				 CED_DefinirTipoEspaco( pGrafo->pCorrente , CED_ID_TIPO_VALOR_NULO ) ;
				 CED_DefinirTipoEspaco( pGrafo->pCorrente , CED_ID_TIPO_ILEGAL ) ;

				 break;
			 }

		 case DeturpaIsolaVertice:
			 {
				 LIS_ExcluirElemento(pGrafo->pListaVertices);

				 break;
			 }

		 case DeturpaNullCorrente:
			 {
				 pGrafo->pCorrente = NULL;

				 break;
			 }

		 case DeturpaNullOrigem:
			 {
				 GRA_tppVerGrafo pVertice;
				 LIS_IrInicioLista(pGrafo->pListaOrigens);

				 LIS_ObterValor(pGrafo->pListaOrigens, (void**)&pVertice);

				 pVertice = NULL;

				 break;

			 }

	 }
	
} /* Fim funcao: GRA &Deturpar Grafo */

#endif

#ifdef _DEBUG

/***************************************************************************
*
*  Funcao: GRA  &Verificar Grafo
*  ****/

GRA_tpCondRet GRA_VerificarGrafo(GRA_tppGrafo pGrafo)
{
	GRA_tppVerGrafo pVertice;
	GRA_tppArestaGrafo pAresta;
	GRA_tppVerGrafo pVerticeAnt;

	int retorno = 0;

	/* Verifica condicao 1 */
	if ( pGrafo->pCorrente == NULL )
    {
		CNT_CONTAR( "CorrenteNulo" ) ;
		TST_NotificarFalha( "Tentou verificar corrente nao existente" ) ;
		return GRA_CondRetErroEstrutura ;
    } /* if */
	
	if (LIS_IrInicioLista(pGrafo->pListaVertices) == LIS_CondRetOK)
    {
		do{
			LIS_ObterValor(pGrafo->pListaVertices, (void**)&pVertice);
			retorno = VerificaSucessoresVertice(pVertice);

			if(retorno == 1){
				CNT_CONTAR( "SucessorNulo" ) ;
				TST_NotificarFalha( "Tentou verificar corrente nao existente" ) ;
				return GRA_CondRetErroEstrutura ;
			}

			ListaRet = LIS_AvancarElementoCorrente(pGrafo->pListaVertices, 1);

		}while(ListaRet != LIS_CondRetFimLista);
    } /* if */

	

	
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
		if(strcmp(pVertice->pIdVertice,pVert->pIdVertice)==0){
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

tpVerticeGrafo * GRA_BuscarVertice(GRA_tppGrafo pGrafo , char * Id)
{
	tpVerticeGrafo * pVerticeRes;

	ListaRet = LIS_IrInicioLista(pGrafo->pListaVertices);
	
	while (ListaRet == LIS_CondRetOK || ListaRet == LIS_CondRetFimLista){
	
		LIS_ObterValor (pGrafo->pListaVertices , (void**)&pVerticeRes);

		if(strcmp(pVerticeRes->pIdVertice, Id)==0){
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
} /* Fim funcao: GRA -Checa se aresta existe */

/***************************************************************************
*
*  Funcao: GRA  -Checa se vertice existe
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
} /* Fim funcao: GRA -Checa se vertice existe */

#ifdef _DEBUG

/***************************************************************************
*
*  Funcao: GRA  -Checa sucessores do vertice
*
****************************************************************************/

static int VerificaSucessoresVertice(GRA_tppVerGrafo pVertice)
{
	GRA_tppArestaGrafo pAres;
	LIS_IrInicioLista(pVertice->pVerSuc);

	do{

		LIS_ObterValor(pVertice->pVerSuc, (void**)&pAres);

		if(pAres->pVerticeDest ==NULL){
			return 1;
		}

		ListaRetCaminho = LIS_AvancarElementoCorrente(pVertice->pVerSuc, 1);

	}while(ListaRetCaminho != LIS_CondRetFimLista);

	return 0;
} /* Fim funcao: GRA -Checa sucessores do vertice */

#endif

/********** Fim do modulo de implementacao: Modulo GRAFO **********/
