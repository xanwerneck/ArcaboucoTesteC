#if ! defined( GRAFO_ )
#define GRAFO_
/***************************************************************************
*
*  $MCD Modulo de definicao: GRA Modulo grafo
*
*  Arquivo gerado:              GRAFO.H
*  Letras identificadoras:      GRA
*
*  Projeto: INF 1301 - Verificador de Xeque-mate
*  Gestor:  Flavio Bevilacqua
*  Autores: afv:  aw - Alexandre Werneck
*                 fr - Fernanda C Ribeiro
*                 vo - Vinicius de Luiz de Oliveira
*
*  $HA Historico de evolucao:
*     Versao  Autor    Data     Observacoes
*     Y       afv   xx/xx/2013  finalizacao do desenvolvimento do modulo
*     1       afv   19/out/2013 inicio do desenvolvimento do modulo
*
*  $ED Descricao do modulo
*     Este modulo implementa a criacao e manipulacao de grafos dirigidos.
*	  Podem existir n grafos operando simultaneamente.
*	  O modulo grafo possui cabeca apontando para uma lista de origens,
*	  vertices e um ponteiro corrente que caminha pelo grafo apontando
*     para vertice.
*	  A lista de origens referencia a origem de cada sub-grafo, caso
*	  exista, no modulo grafo.
*	  A lista de vertices possui referencia para todos os vertices do
*	  grafo.
*
***************************************************************************/
 
#if defined( GRAFO_OWN )
   #define GRAFO_EXT
#else
   #define GRAFO_EXT extern
#endif

#include "LISTA.H"
#include "TABULEIRO.H"
#include "MATRIZ.H"

/***** Declaracoes exportadas pelo modulo *****/

/* Tipo referencia para um grafo */
typedef struct GRA_tagGrafo * GRA_tppGrafo ;

/* Tipo referencia para um vertice de grafo */
typedef struct tagVerticeGrafo * GRA_tppVerGrafo ;

/* Tipo referencia para uma aresta do vertice de grafo */
typedef struct tagArestaGrafo * GRA_tppArestaGrafo ;

/***********************************************************************
*
*  $TC Tipo de dados: GRA Condicoes de retorno
*
*
***********************************************************************/

typedef enum {

        GRA_CondRetOK = 0 ,
            /* Executou correto */

		GRA_CondRetValorNulo = 1 ,
			/* Valor fornecido nulo */

		GRA_CondRetVerticeNulo = 2 ,
			/* Vertice de parametro nulo */

		GRA_CondRetListaNula = 3 ,
			/* Valor lista nula */

		GRA_CondRetConteudoNulo = 4 ,
			/* Conteudo fornecido nulo */

	   GRA_CondRetGrafoNulo   = 5 ,
		    /* Grafo nulo */

       GRA_CondRetNaoAchou   = 6 ,
	       /* Condicao nao encontrou */

       GRA_CondRetMaisdeUmaOrigem = 7 ,
	       /* Nao foi possivel inserir em origem */

		GRA_ArestaJaExiste = 8 ,
	       /* Nao foi possivel criar aresta */

        GRA_CondRetFaltouMemoria = 9 ,
            /* Faltou memoria ao alocar dados */

		GRA_VerticeJaExiste = 10 ,
			/* Vertice ja existe na lista de vertices desse grafo */

		GRA_CondRetFimLista = 11
		    /*	Fim da lista de vertices */

} GRA_tpCondRet ;


/***********************************************************************
*
*  $FC Funcao: GRA Criar grafo
*
*  $ED Descricao da funcao
*     Inicia um grafo vazio, sem vertices.
*
*  $EP Parametros
*     pGrafo  - Posicao do vetor de grafos criado.
*     ExcluirValor - Funcao de exclusao do grafo generico
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetFaltouMemoria
*
*  $AE CondRet deve ter sido instanciado
*
*  $AS Se CondRet = GRA_CondRetOK
*	   Grafo criado em posicao do vetor  de grafos
*
*	   Se CondRet = GRA_CondRetFaltouMemoria
*	   Grafo nao criado por falta de memoria
*
***********************************************************************/

GRA_tpCondRet GRA_CriarGrafo (GRA_tppGrafo * pGrafo, void   ( * ExcluirValor ) ( void * pDado ) );

/***********************************************************************
*
*  $FC Funcao: GRA Criar vertice grafo
*
*  $ED Descricao da funcao
*     Cria um elemento vertice do grafo e insere
*     este na lista de vertices do grafo, sentando
*     como corrente.
*
*  $EP Parametros
*     pGrafo    - Grafo que recebera o vertice criado
*     conteudo  - Ponteiro para elemento de conteudo vertice
*	  id        - Identificador do vertice
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetFaltouMemoria
*
*  $AE Grafo criado
*      CondRet deve ter sido instanciado
*
*  $AS Se CondRet = GRA_CondRetOK
*	   Vertice criado com conteudo e id
*      ponteiro ListaAnt e apontado para lista vazia criada
*      ponteiro ListaSuc e apontado para lista vazia criada
*      Vertice inserido na lista de vertices do grafo
*
*	   Se CondRet = GRA_CondRetFaltouMemoria
*	   Vertice nao criado por falta de memoria
*
*
***********************************************************************/

GRA_tpCondRet GRA_CriaVerticeGrafo(GRA_tppGrafo pGrafo, char * String , char * id , void   ( * ExcluirValor ) ( void * pDado ));


/***********************************************************************
*
*  $FC Funcao: GRA Excluir vertice
*
*  $ED Descricao da funcao
*     Excluir elemento vertice corrente do grafo. Esta funcao percorre 
*	  a lista de antecessores e sucessores do vertice a excluir 
*     eliminando as referencias e as arestas da lista de sucessores. 
*     A funcao tambem elimina, caso exista as referencias em origens.
*     Elimina da lista de vertices do grafo.
*
*  $EP Parametros
*     pGrafo   - Ponteiro para o grafo contendo o vertice corrente
*
*  $FV Valor retornado
*      GRA_CondRetOK
*
*  $AE Grafo ja deve ter sido criado
*      Corrente do grafo nao pode estar nulo
*      Grafo devera conter vertices na lista de vertices
*
*  $AS Se CondRet = GRA_CondRetOK
*      pVertice e excluido da lista de vertices do grafo
*      Caso exista, pVertice e excluido da lista de origens
*      pVertice perde as referencias nas listas de antecessores e sucessores
*      As listas do vertice sao excluidas
*      pVertice e excluido
*
***********************************************************************/

GRA_tpCondRet GRA_ExcluirVerticeCorrente(GRA_tppGrafo pGrafo);


/***********************************************************************
*
*  $FC Funcao: GRA Obter valor do vertice corrente
*
*  $ED Descricao da funcao
*      Checa se a string fornecida e igual a do elemento
*      vertice corrente no grafo.     
*
*  $EP Parametros
*      pGrafo - Ponteiro para o grafo que contem o corrente
*      nomeForn - String de comparacao     
*
*  $FV Valor retornado
*      GRA_CondRetGrafoNulo
*      GRA_CondRetConteudoNulo
*      GRA_CondRetOK
*
*  $AE Grafo deve estar iniciado
*      Corrente nao pode estar apontando para NULL
*      String fornecida nao vazia
*      Grafo nao vazio, ou seja, sem vertices
*
*  $AS Se CondRet = GRA_CondRetGrafoNulo 
*      Grafo fornecido nao criado
*
*	   Se CondRet = GRA_CondRetConteudoNulo
*      Valor nao encontrado ou string fornecida vazia
*
*	   Se CondRet = GRA_CondRetOK
*      Valor fornecido igual ao do vertice corrente
*
***********************************************************************/

GRA_tpCondRet GRA_ChecarNomeVerticeCorrente (GRA_tppGrafo pGrafo , char * nomeForn) ;

/***********************************************************************
*
*  $FC Funcao: GRA Mudar valor do vertice corrente
*
*  $ED Descricao da funcao
*     Recebe uma string como segundo parametro e altera o valor
*     do conteudo do vertice corrente do grafo.
*
*  $EP Parametros
*     pGrafo - Ponteiro para o grafo
*     nomeForn - String a ser usada como novo valor para o conteudo do vertice
*
*  $FV Valor retornado
*      GRA_CondRetVerticeNulo
*      GRA_CondRetConteudoNulo
*      GRA_CondRetOK
*
*  $AE Grafo deve estar iniciado
*      Corrente nao pode estar apontando para NULL
*      String fornecida nao vazia
*      Grafo nao vazio, ou seja, sem vertices
*
*  $AS Se CondRet = GRA_CondRetGrafoNulo 
*      Grafo fornecido nao criado
*
*	   Se CondRet = GRA_CondRetConteudoNulo
*	   String fornecida vazia
*
*	   Se CondRet = GRA_CondRetOK
*      Valor do conteudo do vertice corrente do grafo alterado
*
***********************************************************************/

GRA_tpCondRet GRA_MudarNomeVerticeCorrente (GRA_tppGrafo pGrafo , char * nomeForn) ;

/***********************************************************************
*
*  $FC Funcao: GRA Inserir vertice na lista de origens
*
*  $ED Descricao da funcao
*      Insere o vertice corrente na lista de origens
*      do grafo fornecido.
*     
*
*  $EP Parametros
*      pGrafo - Ponteiro para o grafo contendo o vertice corrente
*      IdVert - Char contendo o conteudo de ID do vertice corrente     
*
*  $FV Valor retornado
*      GRA_CondRetNaoAchou
*      GRA_CondRetOK
*
*  $AE O grafo deve possuir vertice com id igual ao fornecido
*      Grafo deve estar iniciado
*
*  $AS Se CondRet = GRA_CondRetNaoAchou
*	   Nenhum vertice com este id foi encontrado
*
*	   Se CondRet = GRA_CondRetOK
*      Vertice inserido na lista de origens do grafo
*
***********************************************************************/

GRA_tpCondRet GRA_InsereOrigem(GRA_tppGrafo pGrafo, char * IdVert);


/***********************************************************************
*
*  $FC Funcao: GRA Criar Aresta
*
*  $ED Descricao da funcao
*      Ao receber dois char, a funcao procura os vertices correspondentes.
*      O primeiro representa a origem e portanto a aresta sera criada e inserida
*      na lista de sucessores deste vertice. A aresta apontara para o vertice
*      do segundo parametro, o destino, que tambem insere o vertice origem 
*      em sua respectiva lista de antecessores.
*     
*
*  $EP Parametros
*      pVertOrig - Id do vertice de origem
*      pvertDest - id do vertice de destino
*      pGrafo    - Grafo que contem estes vertices
*      String    - Nome que sera inserido em aresta     
*
*  $FV Valor retornado
*      GRA_CondRetFaltouMemoria
*      GRA_CondRetNaoAchou
*      GRA_CondRetOK
*
*  $AE Grafo ja deve ter sido iniciado
*      Os vertices fornecidos devem fazer parte do grafo passado
*
*  $AS Se CondRet = GRA_CondRetFaltouMemoria
*	   Aresta nao criada por falta de memoria
*
*      Se CondRet = GRA_CondRetNaoAchou
*      Um dos vertices fornecidos nao foi encontrado
*
*	   Se CondRet = GRA_CondRetOK
*      Aresta criada com sucesso fazendo a ligacao entre vertices
*
***********************************************************************/

GRA_tpCondRet GRA_CriarAresta (char * pVertOrig , char * pVertDest , GRA_tppGrafo pGrafo, char * String);

/***********************************************************************
*
*  $FC Funcao: GRA Excluir Aresta
*
*  $ED Descricao da funcao
*      Excluir a aresta que faz a ligacao entre os vertices fornecidos.
*      Excluir tambem a relacao da lista de antecessores da lista do vertice destino.
*     
*
*  $EP Parametros
*      pVertOrig - Id do vertice de origem
*      pvertDest - id do vertice de destino
*      pGrafo    - Grafo que contem estes vertices    
*
*  $FV Valor retornado
*      GRA_CondRetNaoAchou
*      GRA_CondRetOK
*
*  $AE Grafo ja deve ter sido iniciado
*      Os vertices fornecidos devem fazer parte do grafo passado
*
*  $AS Se CondRet = GRA_CondRetNaoAchou
*      Um dos vertices fornecidos nao foi encontrado
*
*	   Se CondRet = GRA_CondRetOK
*      Aresta excluida com sucesso
*
***********************************************************************/

GRA_tpCondRet GRA_ExcluirAresta (char * pVertOrig , char * pVertDest , GRA_tppGrafo pGrafo);

/***********************************************************************
*
*  $FC Funcao: GRA Definir vertice corrente
*
*  $ED Descricao da funcao
*      Procura o vertice com base no id fornecido e seta este como corrente
*      do grafo.
*     
*
*  $EP Parametros
*      pGrafo    - Grafo que contem o vertice  
*      IdVert    - id do vertice a ser usado
*
*  $FV Valor retornado
*      GRA_CondRetNaoAchou
*      GRA_CondRetOK
*
*  $AE Grafo ja deve ter sido iniciado
*      O vertices fornecido deve fazer parte do grafo passado
*
*  $AS Se CondRet = GRA_CondRetNaoAchou
*      O vertice fornecido nao foi encontrado
*
*	   Se CondRet = GRA_CondRetOK
*      Vertice setado como corrente
*
***********************************************************************/

GRA_tpCondRet GRA_DefinirCorrente( GRA_tppGrafo pGrafo , char * IdVert);


/***********************************************************************
*
*  $FC Funcao: GRA Destruir grafo
*
*  $ED Descricao da funcao
*      Destroi o grafo fornecido como parametro
*     
*
*  $EP Parametros
*      pGrafo    - Grafo a ser excluido
*
*  $FV Valor retornado
*      GRA_CondRetGrafoNulo
*      GRA_CondRetOK
*
*  $AE Grafo ja deve ter sido iniciado
*      A lista de Origens e Vertices nao deve estar vazia
*
*  $AS Se CondRet = GRA_CondRetGrafoNulo
*      O grafo fornecido nao foi criado ou esta nulo
*
*	   Se CondRet = GRA_CondRetOK
*      Grafo excluido com sucesso
*
***********************************************************************/

GRA_tpCondRet GRA_DestruirGrafo( GRA_tppGrafo pGrafo);



/***********************************************************************
*
*  $FC Funcao: GRA Obter vertice
*
*  $ED Descricao da funcao
*      Retorna por paramentro o vertice corrente do grafo.
*     
*
*  $EP Parametros
*      pGrafo    - Grafo a ser excluido
*      pValor    - Ponteiro para retorno do vertice.
*
*  $FV Valor retornado
*      GRA_CondRetGrafoNulo
*      GRA_CondRetOK
*
*  $AE Grafo ja deve ter sido iniciado
*      A lista de Origens e Vertices nao deve estar vazia
*
*  $AS Se CondRet = GRA_CondRetGrafoNulo
*      O grafo fornecido nao foi criado ou esta nulo
*
*	   Se CondRet = GRA_CondRetOK
*      Concluiu com sucesso
*
***********************************************************************/
GRA_tpCondRet GRA_ObterVertice(GRA_tppGrafo pGrafo , void ** pValor);


/***********************************************************************
*
*  $FC Funcao: GRA Ir inicio
*
*  $ED Descricao da funcao
*      Seta o corrente do vetor de vertices do grafo como inicio.
*     
*
*  $EP Parametros
*      pGrafo    - Ponteiro para o grafo.
*
*  $FV Valor retornado
*      GRA_CondRetNaoAchou
*      GRA_CondRetOK
*
*  $AE Grafo ja deve ter sido iniciado
*      A lista de Origens e Vertices nao deve estar vazia
*
*  $AS Se CondRet = GRA_CondRetNaoAchou
*      Lista de vertices vazia.
*
*	   Se CondRet = GRA_CondRetOK
*      Concluiu com sucesso
*
***********************************************************************/
GRA_tpCondRet GRA_IrInicio(GRA_tppGrafo pGrafo);


/***********************************************************************
*
*  $FC Funcao: GRA Buscar Id do vertice
*
*  $ED Descricao da funcao
*      Retorna por paramentro o Id do grafo.
*     
*
*  $EP Parametros
*      pGrafo    - Ponteiro para o grafo.
*      pValor    - Ponteiro para retorno do Id.
*
*  $FV Valor retornado
*      GRA_CondRetGrafoNulo
*      GRA_CondRetOK
*
*  $AE Grafo ja deve ter sido iniciado
*      A lista de Origens e Vertices nao deve estar vazia
*
*  $AS Se CondRet = GRA_CondRetGrafoNulo
*      O grafo fornecido nao foi criado ou esta nulo
*
*	   Se CondRet = GRA_CondRetOK
*      Concluiu com sucesso.
*
***********************************************************************/
GRA_tpCondRet GRA_BuscaIdVertice(GRA_tppGrafo pGrafo , char ** pValor);


/***********************************************************************
*
*  $FC Funcao: GRA Avancar corrente do vertice
*
*  $ED Descricao da funcao
*      Avanca val vezes o elemento corrente do vertice.
*     
*
*  $EP Parametros
*      pGrafo    - Ponteiro para o grafo.
*      val       - Quantidade de vezes que ele avanca.
*
*  $FV Valor retornado
*      GRA_CondRetFimLista
*      GRA_CondRetOK
*
*  $AE Grafo ja deve ter sido iniciado
*      A lista de Origens e Vertices nao deve estar vazia
*
*  $AS Se CondRet = GRA_CondRetGrafoNulo
*      Atingiu o final da lista, corrente e inicio ou final da lista.
*
*	   Se CondRet = GRA_CondRetOK
*      Concluiu com sucesso
*
***********************************************************************/
GRA_tpCondRet GRA_AvancarCorrenteVert(GRA_tppGrafo pGrafo , int val);


/***********************************************************************
*
*  $FC Funcao: GRA Numero de vertices
*
*  $ED Descricao da funcao
*      Retorna por paramentro o numero de elementos da lista de vertices 
*       do pGrafo.
*     
*
*  $EP Parametros
*      pGrafo    - Grafo a ser excluido
*      val       - Ponteiro para o valor a ser retornado. 
*
*  $FV Valor retornado
*      GRA_CondRetOK
*
*  $AE Grafo ja deve ter sido iniciado
*      A lista de Origens e Vertices nao deve estar vazia
*
*  $AS Se CondRet = GRA_CondRetOK
*      Retornou numero de vertices com sucesso.
*
***********************************************************************/
GRA_tpCondRet GRA_NumeroVertices(GRA_tppGrafo pGrafo , int * val);


/***********************************************************************
*
*  $FC Funcao: GRA Setar corrente
*
*  $ED Descricao da funcao
*      Insere pValor no corrente do pGrafo.
*     
*
*  $EP Parametros
*      pGrafo    - Grafo cujo corrente sera atualizado com pValor.
*      pValor    - Ponteiro para o valor a ser inserido no pGrafo.
*
*  $FV Valor retornado
*      GRA_CondRetGrafoNulo
*      GRA_CondRetOK
*
*  $AE Grafo ja deve ter sido iniciado
*      A lista de Origens e Vertices nao deve estar vazia
*
*  $AS Se CondRet = GRA_CondRetGrafoNulo
*      O grafo fornecido nao foi criado ou esta nulo
*
*	   Se CondRet = GRA_CondRetOK
*      pValor inserido com sucesso.
*
***********************************************************************/
GRA_tpCondRet GRA_SetarCorrente(GRA_tppGrafo pGrafo , char * pValor);


/***********************************************************************
*
*  $FC Funcao: GRA Insere conteudo do vertice
*
*  $ED Descricao da funcao
*      Insere pConteudo em pGrafo
*     
*
*  $EP Parametros
*      pGrafo    - Ponteiro para grafo cujo conteudo sera pConteudo.
*      pConteudo - Ponteiro para elemento a ser inserido em pGrafo.
*
*  $FV Valor retornado
*      GRA_CondRetGrafoNulo
*      GRA_CondRetOK
*
*  $AE Grafo ja deve ter sido iniciado
*      A lista de Origens e Vertices nao deve estar vazia.
*
*  $AS Se CondRet = GRA_CondRetGrafoNulo
*      O grafo fornecido nao foi criado ou esta nulo.
*
*	   Se CondRet = GRA_CondRetOK
*      pConteudo foi inserido com sucesso.
*
***********************************************************************/
GRA_tpCondRet GRA_InsereConteudoVertice(GRA_tppGrafo pGrafo , void * pConteudo);


/***********************************************************************
*
*  $FC Funcao: GRA Pega conteudo
*
*  $ED Descricao da funcao
*      Retorna por parametro conteudo do pGrafo
*     
*
*  $EP Parametros
*      pGrafo    - Grafo cujo conteudo sera retornado.
*      pConteudo - conteudo a ser retornado.
*
*  $FV Valor retornado
*      GRA_CondRetGrafoNulo
*      GRA_CondRetOK
*
*  $AE Grafo ja deve ter sido iniciado
*      A lista de Origens e Vertices nao deve estar vazia
*
*  $AS Se CondRet = GRA_CondRetGrafoNulo
*      O grafo fornecido nao foi criado ou esta nulo
*
*	   Se CondRet = GRA_CondRetOK
*      Conteudo retornado com sucesso
*
***********************************************************************/
GRA_tpCondRet GRA_PegaConteudo(GRA_tppGrafo pGrafo , void ** pConteudo);


/***********************************************************************
*
*  $FC Funcao: GRA Obter aresta do vertice
*
*  $ED Descricao da funcao
*      Retorna por paramentro a aresta do vertice do pGrafo ambos tambem 
*      passado por parametro.
*
*  $EP Parametros
*      pGrafo    - Grafo de cujo vertice sera retornado aresta.
*
*  $FV Valor retornado
*      GRA_CondRetListaNula
*      GRA_CondRetOK
*
*  $AE Grafo ja deve ter sido iniciado
*      A lista de Origens e Vertices nao deve estar vazia
*
*  $AS Se CondRet = GRA_CondRetListaNula
*      A lista do grafo fornecido nao foi criada ou esta nula
*
*	   Se CondRet = GRA_CondRetOK
*      Aresta retornada com sucesso
*
***********************************************************************/
GRA_tpCondRet GRA_ObterArestaVertice(GRA_tppGrafo pGrafo , void ** rVertice , char * Aresta);


/***********************************************************************
*
*  $FC Funcao: GRA Ir inicio da aresta
*
*  $ED Descricao da funcao
*      Faz o corrente da aresta do pGrafo apontar para o inicio.
*     
*
*  $EP Parametros
*      pGrafo    - Grafo cujo corrente da lista de arestas vai para o inicio.
*
*  $FV Valor retornado
*      GRA_CondRetOK
*
*  $AE Grafo ja deve ter sido iniciado
*      A lista de Origens e Vertices nao deve estar vazia
*
*  $AS Se CondRet = GRA_CondRetOK
*      Foi para o inicio das arestas com sucesso
*
***********************************************************************/
GRA_tpCondRet GRA_IrInicioAresta(GRA_tppGrafo pGrafo);


/***********************************************************************
*
*  $FC Funcao: GRA Avancar Aresta do Vertice
*
*  $ED Descricao da funcao
*      Avanca val aresta a partir do corrente.
*     
*
*  $EP Parametros
*      pGrafo    - Grafo cuja aresta sera avancada
*
*  $FV Valor retornado
*      GRA_CondRetOK
*
*  $AE Grafo ja deve ter sido iniciado
*      A lista de Origens e Vertices nao deve estar vazia.
*
*  $AS Se CondRet = GRA_CondRetOK
*      Avancou arestas com sucesso com sucesso.
*
***********************************************************************/
GRA_tpCondRet GRA_AvancarArestaVertice(GRA_tppGrafo pGrafo , int val);


/***********************************************************************
*
*  $FC Funcao: GRA Numero de aresta do vertice 
*
*  $ED Descricao da funcao
*      Retorna por parametro o numero de arestas do vertice do pGrafo
*     
*
*  $EP Parametros
*      pGrafo    - Grafo para retornar numero de arestas.
*
*  $FV Valor retornado
*      GRA_CondRetGrafoNulo
*      GRA_CondRetOK
*
*  $AE Grafo ja deve ter sido iniciado
*      A lista de Origens e Vertices nao deve estar vazia
*
*  $AS Se CondRet = GRA_CondRetGrafoNulo
*      O grafo fornecido nao foi criado ou esta nulo
*
*	   Se CondRet = GRA_CondRetOK
*      Numero de arestas retornado com sucesso
*
***********************************************************************/
GRA_tpCondRet GRA_NumeroArestaVertice(GRA_tppGrafo pGrafo , int * Num);

GRA_tpCondRet GRA_PegaConteudoCorrente(GRA_tppGrafo pGrafo , void ** pConteudo);

GRA_tpCondRet GRA_PegaConteudoPeloVertice(void * Vertice , void ** pConteudo);

GRA_tpCondRet GRA_ResgatarIdVertice(GRA_tppVerGrafo pVertice, char ** IdVertice);

#undef GRAFO_EXT

/********** Fim do modulo de definicao: Modulo grafo **********/

#else
#endif
