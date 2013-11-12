#if ! defined( TABULEIRO_ )
#define TABULEIRO_
/***************************************************************************
*
*  $MCD Módulo de definição: TAB  Tabuleiro de xadrez
*
*  Arquivo gerado:              TABULEIRO.H
*  Letras identificadoras:      TAB
*
*  Projeto: INF 1301 - Verificador de Xeque-mate
*  Gestor:  Flavio Bevilacqua
*  Autores: afv:  aw - Alexandre Werneck
*                 fr - Fernanda C Ribeiro
*                 vo - Vinicius de Luiz de Oliveira
*
*  $HA Historico de evolucao:
*     Versao  Autor    Data     Observacoes
*     1       afv   11/nov/2013  Inicio do desenvolvimento do modulo
*
*  $ED Descrição do módulo
*     Este modulo implementa a criacao e manipulacao de tabuleiro de xadrez.
*     Este modulo apresenta, alem de funcoes de manipulacao de tabuleiro, 
*     algumas funcoes de manipulacao de pecas com relacao a casa do 
*     tabuleiro onde a mesma esta situada.
*
***************************************************************************/
 
#if defined( TABULEIRO_OWN )
   #define TABULEIRO_EXT
#else
   #define TABULEIRO_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um tabuleiro */
typedef struct TAB_tagTabuleiro * TAB_tppTabuleiro ;

/***********************************************************************
*
*  $TC Tipo de dados: TAB Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
*
***********************************************************************/

   typedef enum {

      TAB_CondRetOK = 0,
            /* Concluiu corretamente */

		 TAB_TimeAVazio = 1 ,
            /* Time A vazio */

		 TAB_TimeBVazio = 2 ,
            /* Time B vazio */

		 TAB_CondRetNaoAchou = 3 ,
            /* Não achou */

		 TAB_CondRetFimLista = 4 ,
            /* Lista chegou ao final */

		 TAB_CondRetListaVazia = 5 ,
            /* Lista vazia */

		 TAB_CondRetTabuleiroNulo = 6 ,
            /* Tabuleiro nulo */
		 
       TAB_CondRetTabuleiroListaNula = 7 ,
            /* Lista do tabuleiro nula */

		 TAB_CondRetCorrenteNulo = 8 ,
            /* Corrente nulo */

       TAB_CondRetFaltouMemoria = 9
            /* Faltou memória ao criar um tabuleiro */

   } TAB_tpCondRet ;


/***********************************************************************
*
*  $FC Funcao: TAB Criar tabuleiro
*
*  $ED Descricao da funcao
*     Cria um tabuleiro vazio, sem pecas. 
*     Inicializa tabuleiro com estruturas de grafo e lista de pecas 
*      vazias.
*     Inicializa estrutura de grafo como matriz 8x8.
*     Cada casa do tabuleiro é um vértice do grafo e cada
*     aresta define o caminho possivel da casa.
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro de referencia para tabuleiro.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetFaltouMemoria
*
*  $AE 'CondRet' deve ter sido instanciado
*
*  $AS Se CondRet = TAB_CondRetOK
*         pTabuleiro inicializado.
*         Concluiu funcao com sucesso.
*
*     Se CondRet = TAB_CondRetFaltouMemoria
*        pTabuleiro nao foi inicializado.
*        Impossivel criar elemento, faltou memoria.
*
***********************************************************************/

   TAB_tpCondRet TAB_CriarTabuleiro( TAB_tppTabuleiro * pTabuleiro) ;

/***********************************************************************
*
*  $FC Funcao: TAB Apresenta tabuleiro
*
*  $ED Descricao da funcao
*     Imprime a configuracao de um tabuleiro vazio.
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro de referência para tabuleiro.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*
*  $AE CondRet deve ter sido instanciado
*
*  $AS Se CondRet = TAB_CondRetOK
*     Concluiu funcao com sucesso.
*
***********************************************************************/

   TAB_tpCondRet TAB_ApresentaTabuleiro( TAB_tppTabuleiro pTabuleiro );

/***********************************************************************
*
*  $FC Funcao: TAB Criar tipo de peça
*
*  $ED Descricao da funcao
*     Cria tipo de peça.
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro de referência para tabuleiro.
*     Nome        - Nome do tipo de peça.
*     Diagonal    - Possibilidade de ir para a diagonal.
*     Reta        - Possibilidade de ir para a vertical e horizontal.
*     QtdeMov     - Quantidade de casas que se pode andar.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNulo
*
*  $AE CondRet deve ter sido instanciado
*      'Diag' = valor inteiro 0 ou 1.
*      'Reta' = valor inteiro 0 ou 1.
*      'Qtde' = valor inteiro entre 1 e 7.
*      'Nome' = string com no maximo 10 caracteres.
*
*  $AS Se CondRet = TAB_CondRetOK
*     Concluiu funcao com sucesso.
*     Criado um tipo de peca
*     Tipo de peca criado incluido na lista de pecas do tabuleiro.
*
*     Se CondRet = TAB_CondRetTabuleiroNulo
*     Impossivel criar elemento, tabuleiro nulo.
*
***********************************************************************/

   TAB_tpCondRet TAB_CriarTipoPeca(TAB_tppTabuleiro pTabuleiro , char * Nome , int Diagonal , int Reta , int QtdeMov);

/***********************************************************************
*
*  $FC Funcao: TAB Apresentar tipo de peças - Mapa de Movimentos
*
*  $ED Descricao da funcao
*     Apresenta configuração dos tipos de peças criadas.
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro de referência para tabuleiro.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNulo
*     TAB_CondRetTabuleiroListaNula
*     TAB_TimeAVazio
*
*  $AE CondRet deve ter sido instanciado
*      Tabuleiro nao deve estar nulo.
*      Devem existir tipos de pecas criadas.
*
*  $AS Se CondRet = TAB_CondRetOK
*     Concluiu funcao com sucesso.
*
*     Se CondRet = TAB_CondRetTabuleiroNulo
*     Impossivel apresentar peças, tabuleiro nulo.
*
*     Se CondRet = TAB_CondRetTabuleiroListaNula
*     Impossivel apresentar peças, lista de peças nula.
*
*     Se CondRet = TAB_CondRetListaVazia
*     Impossivel apresentar peças, lista de peças vazia.
*
***********************************************************************/

   TAB_tpCondRet TAB_ApresentaTipoPecas(TAB_tppTabuleiro pTabuleiro) ;

 
/***********************************************************************
*
*  $FC Funcao: TAB Procurar peca
*
*  $ED Descricao da funcao
*     Procurar peca no tabuleiro com o nome fornecido.
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro de referência para tabuleiro.
*     NomeBuscado - Nome da peca para buscada
*     PecaBuscada - Ponteiro contendo a referencia da peca buscada, o valor retorna neste elemento.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetListaVazia
*     TAB_CondRetTabuleiroNulo
*     TAB_CondRetNaoAchou
*
*  $AE CondRet deve ter sido instanciado
*      Tabuleiro nao deve estar nulo
*      Devem existir tipos de pecas ja cadastradas
*      Nome deve estar valido e referente a um tipo existente.
*
*  $AS Se CondRet = TAB_CondRetOK
*     Concluiu funcao com sucesso.
*     PecaBuscada contém a referencia da peca buscada
*
*     Se CondRet = TAB_CondRetListaVazia
*     Nao existe elementos na lista de tipos de pecas do tabuleiro.
*
*     Se CondRet = TAB_CondRetNaoAchou
*     Nao existe um elemento na lista com o nome fornecido.
*
*     Se CondRet = TAB_CondRetTabuleiroNulo
*     Tabuleiro nao foi criado.
*
***********************************************************************/
   TAB_tpCondRet TAB_ProcuraPeca(TAB_tppTabuleiro pTabuleiro , char * NomeBuscado , void ** PecaBuscada);

/***********************************************************************
*
*  $FC Funcao: TAB Ir inicio da lista de pecas
*
*  $ED Descricao da funcao
*     Coloca o corrente no primeiro elemento da lista de tipo de pecas
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro de referência para tabuleiro.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNulo
*     TAB_CondRetListaVazia
*
*  $AE CondRet deve ter sido instanciado
*
*  $AS Se CondRet = TAB_CondRetOK
*     Concluiu funcao com sucesso.
*     Corrente aponta para o primeiro elemento.
*
*     Se CondRet = TAB_CondRetTabuleiroNulo
*     Tabuleiro nao existe.
*
*     Se CondRet = TAB_CondRetListaVazia
*     A lista de tipo de pecas do tabuleiro nao possui elementos.
*
***********************************************************************/
   TAB_tpCondRet TAB_IrInicioListaPecas(TAB_tppTabuleiro pTabuleiro);

/***********************************************************************
*
*  $FC Funcao: TAB Obter tipo de peca
*
*  $ED Descricao da funcao
*     Obtem o tipo de peca por referencia do corrente da lista de pecas do tabuleiro
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro para tabuleiro.
*     pPeca       - Ponteiro de referencia para retorno do tipo de peca.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNulo
*     TAB_CondRetListaVazia
*
*  $AE CondRet deve ter sido instanciado
*
*  $AS Se CondRet = TAB_CondRetOK
*     Concluiu funcao com sucesso.
*     pPeca contem o ponteiro para o tipo de peca corrente da lista de pecas
*
*     Se CondRet = TAB_CondRetTabuleiroNulo
*     Tabuleiro nao existe.
*
*     Se CondRet = TAB_CondRetListaVazia
*     A lista de tipo de pecas do tabuleiro nao possui elementos.
*
***********************************************************************/
   TAB_tpCondRet TAB_ObterTipoPeca(TAB_tppTabuleiro pTabuleiro , void ** pPeca);

/***********************************************************************
*
*  $FC Funcao: TAB Avancar tipo de peca
*
*  $ED Descricao da funcao
*     Avanca elemento na lista de pecas do tabuleiro.
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro para tabuleiro.
*     val         - Numero de elementos a andar na lista
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNulo
*     TAB_CondRetFimLista
*
*  $AE CondRet deve ter sido instanciado
*      Tabuleiro deve ter sido criado
*      Deve existe pecas criadas.
*
*  $AS Se CondRet = TAB_CondRetOK
*     Concluiu funcao com sucesso.
*     Corrente aponta para proxima elemento da lista de pecas.
*
*     Se CondRet = TAB_CondRetTabuleiroNulo
*     Tabuleiro nao existe.
*
*     Se CondRet = TAB_CondRetListaVazia
*     Ponteiro aponta para o proxima caso nao seja o ultimo, mas retorna informando que chegou
*     ao fim da lista.
*     Se ja esta no ultimo elemento a lista nao anda.
*
***********************************************************************/
   TAB_tpCondRet TAB_AvancarTipoPeca(TAB_tppTabuleiro pTabuleiro , int val);

/***********************************************************************
*
*  $FC Funcao: TAB Setar tipo de peca como corrente.
*
*  $ED Descricao da funcao
*     Seta um tipo de peca de acordo com o nome fornecido.
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro para tabuleiro.
*     NomeCasa    - Nome da peca buscada para ser corrente.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNulo
*     TAB_CondRetTabuleiroListaNula
*
*  $AE CondRet deve ter sido instanciado
*      Tabuleiro deve ter sido criado
*      NomeCasa deve ser uma string valida.
*
*  $AS Se CondRet = TAB_CondRetOK
*     Peca fornecida setada como corrente.
*
*     Se CondRet = TAB_CondRetTabuleiroNulo
*     Tabuleiro nao existe.
*
*     Se CondRet = TAB_CondRetTabuleiroListaNula
*     A lista de pecas esta nula.
*
***********************************************************************/
   TAB_tpCondRet TAB_SetarCorrente( TAB_tppTabuleiro pTabuleiro , char * NomeCasa );

/***********************************************************************
*
*  $FC Funcao: TAB Inserir conteudo na casa do tabuleiro.
*
*  $ED Descricao da funcao
*     Insere uma peca do jogo no vertice do grafo do tabuleiro.
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro para tabuleiro.
*     pPeca       - Ponteiro para elemento a ser inserido em conteudo do vertice.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNulo
*     TAB_CondRetNaoAchou
*
*  $AE CondRet deve ter sido instanciado
*      Tabuleiro deve ter sido criado
*      pPeca nao pode estar nulo.
*
*  $AS Se CondRet = TAB_CondRetOK
*     Peca fornecida inserida no tabuleiro.
*
*     Se CondRet = TAB_CondRetTabuleiroNulo
*     Tabuleiro nao existe.
*
*     Se CondRet = TAB_CondRetNaoAchou
*     Nao foi possivel inserir conteudo no tabuleiro.
*
***********************************************************************/
   TAB_tpCondRet TAB_InserirConteudoCasa(TAB_tppTabuleiro pTabuleiro , void * pPeca);


/***********************************************************************
*
*  $FC Funcao: TAB Ir Inicio casas do tabuleiro
*
*  $ED Descricao da funcao
*     Seta a primeira casa do tabuleiro como corrente.
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro para tabuleiro.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNulo
*     TAB_CondRetNaoAchou
*
*  $AE CondRet deve ter sido instanciado
*      Tabuleiro deve ter sido criado
*      Valem as AS de criacao do tabuleiro.
*
*  $AS Se CondRet = TAB_CondRetOK
*     Corrente e a primeira casa do tabuleiro.
*
*     Se CondRet = TAB_CondRetTabuleiroNulo
*     Tabuleiro nao existe.
*
*     Se CondRet = TAB_CondRetNaoAchou
*     Nao foi possivel ir ao inicio das casas.
*
***********************************************************************/

   TAB_tpCondRet TAB_IrInicioCasas( TAB_tppTabuleiro pTabuleiro  );

/***********************************************************************
*
*  $FC Funcao: TAB Avancar casas do tabuleiro
*
*  $ED Descricao da funcao
*     Avanca elementos na lista de casas do tabuleiro.
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro para tabuleiro.
*     val         - numero de elementos a andarem.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNulo
*     TAB_CondRetFimLista
*
*  $AE CondRet deve ter sido instanciado
*      Tabuleiro deve ter sido criado
*      Valem as AS de criacao do tabuleiro.
*      val deve ser maior que 0.
*
*  $AS Se CondRet = TAB_CondRetOK
*     Corrente e a proxima casa do tabuleiro.
*
*     Se CondRet = TAB_CondRetTabuleiroNulo
*     Tabuleiro nao existe.
*
*     Se CondRet = TAB_CondRetFimLista
*     Chegou na ultima casa do tabuleiro.
*
***********************************************************************/
   
   TAB_tpCondRet TAB_AvancarCasas( TAB_tppTabuleiro pTabuleiro , int val );

/***********************************************************************
*
*  $FC Funcao: TAB Obter conteudo da casa corrente
*
*  $ED Descricao da funcao
*     Obtem o conteudo do vertice corrente do grafo.
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro para tabuleiro.
*     pConteudo   - Ponteiro de referencia para retorno de conteudo.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNulo
*     TAB_CondRetNaoAchou
*
*  $AE CondRet deve ter sido instanciado
*      Tabuleiro deve ter sido criado
*      Valem as AS de criacao do tabuleiro.
*
*  $AS Se CondRet = TAB_CondRetOK
*     pConteudo contem a referencia do vertice corrente.
*
*     Se CondRet = TAB_CondRetTabuleiroNulo
*     Tabuleiro nao existe.
*
*     Se CondRet = TAB_CondRetNaoAchou
*     Nao foi possivel obter conteudo do corrente.
*
***********************************************************************/
   TAB_tpCondRet TAB_ObterConteudo( TAB_tppTabuleiro pTabuleiro , void ** pConteudo );


/***********************************************************************
*
*  $FC Funcao: TAB Ir inicio das arestas do vertice corrente
*
*  $ED Descricao da funcao
*     Seta o corrente como primeiro elemento das arestas do corrente.
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro para tabuleiro.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*
*  $AE CondRet deve ter sido instanciado
*      Tabuleiro deve ter sido criado
*      Valem as AS de criacao do tabuleiro.
*
*  $AS Se CondRet = TAB_CondRetOK
*     Corrente e o primeiro elemento da aresta do vertice corrente.
*
***********************************************************************/
   TAB_tpCondRet TAB_IrInicioArestasCorrente(TAB_tppTabuleiro pTabuleiro);

/***********************************************************************
*
*  $FC Funcao: TAB &Obtem o vertice contido na aresta.
*
*  $ED Descricao da funcao
*     Obtem o vertice contido na aresta fornecida do vertice corrente.
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro para tabuleiro
*     Vertice     - Ponteiro de referencia para o vertice a ser retornado.
*     Aresta      - Nome da aresta.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNulo
*
*  $AE CondRet deve ter sido instanciado
*      Tabuleiro deve ter sido criado
*      Valem as AS de criacao do tabuleiro.
*      Aresta deve ser uma string valida e referente a um nome de aresta.
*
*  $AS Se CondRet = TAB_CondRetOK
*     Vertice contem a referencia para o vertice buscado.
*
*     Se CondRet = TAB_CondRetTabuleiroNulo
*     Tabuleiro nao existe.
*
***********************************************************************/
   TAB_tpCondRet TAB_ObterVerticeAresta(TAB_tppTabuleiro pTabuleiro , void ** Vertice , char * Aresta);

/***********************************************************************
*
*  $FC Funcao: TAB Avancar aresta corrente
*
*  $ED Descricao da funcao
*     Avanca elementos na aresta corrente.
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro para tabuleiro.
*     val         - numero de elementos a andar.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*
*  $AE CondRet deve ter sido instanciado
*      Tabuleiro deve ter sido criado
*      Valem as AS de criacao do tabuleiro.
*      val deve ser um inteiro valido.
*
*  $AS Se CondRet = TAB_CondRetOK
*     Aresta corrente aponta para proxima.
*
*
***********************************************************************/
   TAB_tpCondRet TAB_AvancarArestaCorrente(TAB_tppTabuleiro pTabuleiro , int val);

/***********************************************************************
*
*  $FC Funcao: TAB Numero arestas do vertice corrente
*
*  $ED Descricao da funcao
*     Retorna o numero de arestas do vertice corrente.
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro para tabuleiro.
*     Num         - Ponteiro inteiro de referencia para retorno.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*
*  $AE CondRet deve ter sido instanciado
*      Tabuleiro deve ter sido criado
*      Valem as AS de criacao do tabuleiro.
*      val deve ser referencia do tipo inteiro.
*
*  $AS Se CondRet = TAB_CondRetOK
*     Retorna o numero de arestas do vertice corrente.
*
*
***********************************************************************/
   TAB_tpCondRet TAB_NumElementosArestasCorrente(TAB_tppTabuleiro pTabuleiro , int * Num);

/***********************************************************************
*
*  $FC Funcao: TAB Obter vertice corrente
*
*  $ED Descricao da funcao
*     Obtem id do vertice corrente.
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro para tabuleiro.
*     Id         - Ponteiro char * de referencia para retorno.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*
*  $AE CondRet deve ter sido instanciado
*      Tabuleiro deve ter sido criado
*      Valem as AS de criacao do tabuleiro.
*      Id deve ser referencia do tipo string.
*
*  $AS Se CondRet = TAB_CondRetOK
*     Retorna o Id por parametro do vertice corrente.
*
*
***********************************************************************/
   TAB_tpCondRet TAB_ObterVerticeCorrente(TAB_tppTabuleiro pTabuleiro , char ** Id);

/***********************************************************************
*
*  $FC Funcao: TAB Obter conteudo do vertice corrente
*
*  $ED Descricao da funcao
*     Obtem a referencia por ponteiro do conteudo do vertice corrente.
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro para tabuleiro.
*     VertConteudo- Ponteiro void de referencia para retorno.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNulo
*
*  $AE CondRet deve ter sido instanciado
*      Tabuleiro deve ter sido criado
*      Valem as AS de criacao do tabuleiro.
*      VertConteudo deve ser referencia do tipo void.
*
*  $AS Se CondRet = TAB_CondRetOK
*     Retorna o conteudo de referencia do vertice corrente em VertConteudo.
*
*      Se CondRet = TAB_CondRetTabuleiroNulo
*     Tabuleiro nao foi criado.
*
*
***********************************************************************/
   TAB_tpCondRet TAB_ObterConteudoVertice(TAB_tppTabuleiro pTabuleiro  , void ** VertConteudo);

/***********************************************************************
*
*  $FC Funcao: TAB Obter conteudo pelo vertice
*
*  $ED Descricao da funcao
*     Obtem a referencia por ponteiro do conteudo do vertice fornecido.
*
*  $EP Parametros
*     Vertice     - Ponteiro para vertice do tabuleiro.
*     VertConteudo- Ponteiro void de referencia para retorno.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNulo
*
*  $AE CondRet deve ter sido instanciado
*      Tabuleiro deve ter sido criado
*      Valem as AS de criacao do tabuleiro.
*      VertConteudo deve ser referencia do tipo void.
*      Vertice deve estar valido.
*
*  $AS Se CondRet = TAB_CondRetOK
*     Retorna o conteudo de referencia do vertice corrente em VertConteudo.
*
*      Se CondRet = TAB_CondRetTabuleiroNulo
*     Vertice fornecido nulo.
*
*
***********************************************************************/
   TAB_tpCondRet TAB_PecaConteudoPeloVertice(void * Vertice  , void ** VertConteudo);
   
/***********************************************************************
*
*  $FC Funcao: TAB Destroi o tabuleiro
*
*  $ED Descricao da funcao
*     Elimina a lista de pecas e destroi a estrutura grafo
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro de referência para tabuleiro.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetTabuleiroNulo
*
*  $AE CondRet deve ter sido instanciado
*
*  $AS Se CondRet = TAB_CondRetOK
*     Concluiu funcao com sucesso.
*
*     Se CondRet = TAB_CondRetFaltouMemoria
*     Tabuleiro já esta nulo.
*
***********************************************************************/
	TAB_tpCondRet TAB_FinalizarPartida(TAB_tppTabuleiro pTabuleiro);



#undef TABULEIRO_EXT

/********** Fim do módulo de definição: LIS  Lista duplamente encadeada **********/

#else
#endif
