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
*     Y       afv   xx/xx/2013  finalizacao do desenvolvimento do modulo
*     1       afv   19/out/2013 inicio do desenvolvimento do modulo
*
*  $ED Descrição do módulo
*     Este modulo implementa a criacao e manipulacao de tabuleiro de xadrez.
*     Só pode existir um tabuleiro por vez.
*     Este modulo apresenta, alem de funcoes de manipulacao de tabuleiro, 
*    algumas funcoes de manipulacao de pecas com relacao a casa do 
*    tabuleiro onde a mesma esta situada.
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
*
*  $AS Se CondRet = TAB_CondRetOK
*     Concluiu funcao com sucesso.
*
*     Se CondRet = TAB_CondRetTabuleiroNulo
*     Impossivel criar elemento, tabuleiro nulo.
*
***********************************************************************/

   TAB_tpCondRet TAB_CriarTipoPeca(TAB_tppTabuleiro pTabuleiro , char * Nome , int Diagonal , int Reta , int QtdeMov);

/***********************************************************************
*
*  $FC Funcao: TAB Apresentar tipo de peças
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
*     Se CondRet = TAB_TimeAVazio
*     Impossivel apresentar peças, lista de peças vazia.
*
***********************************************************************/

   TAB_tpCondRet TAB_ApresentaTipoPecas(TAB_tppTabuleiro pTabuleiro) ;

/***********************************************************************
*
*  $FC Funcao: TAB Criar tabuleiro
*
*  $ED Descricao da funcao
*     Inicia um tabuleiro vazio, sem peças.
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro de referência para tabuleiro.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetFaltouMemoria
*
*  $AE CondRet deve ter sido instanciado
*
*  $AS Se CondRet = TAB_CondRetOK
*     Concluiu funcao com sucesso.
*
*     Se CondRet = TAB_CondRetFaltouMemoria
*     Impossivel criar elemento, faltou memoria.
*
***********************************************************************/
   TAB_tpCondRet TAB_ProcuraPeca(TAB_tppTabuleiro pTabuleiro , char * NomeBuscado , void ** PecaBuscada);

/***********************************************************************
*
*  $FC Funcao: TAB Criar tabuleiro
*
*  $ED Descricao da funcao
*     Inicia um tabuleiro vazio, sem peças.
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro de referência para tabuleiro.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetFaltouMemoria
*
*  $AE CondRet deve ter sido instanciado
*
*  $AS Se CondRet = TAB_CondRetOK
*     Concluiu funcao com sucesso.
*
*     Se CondRet = TAB_CondRetFaltouMemoria
*     Impossivel criar elemento, faltou memoria.
*
***********************************************************************/
   TAB_tpCondRet TAB_IrInicioListaPecas(TAB_tppTabuleiro pTabuleiro);

/***********************************************************************
*
*  $FC Funcao: TAB Criar tabuleiro
*
*  $ED Descricao da funcao
*     Inicia um tabuleiro vazio, sem peças.
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro de referência para tabuleiro.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetFaltouMemoria
*
*  $AE CondRet deve ter sido instanciado
*
*  $AS Se CondRet = TAB_CondRetOK
*     Concluiu funcao com sucesso.
*
*     Se CondRet = TAB_CondRetFaltouMemoria
*     Impossivel criar elemento, faltou memoria.
*
***********************************************************************/
   TAB_tpCondRet TAB_ObterTipoPeca(TAB_tppTabuleiro pTabuleiro , void ** pPeca);

/***********************************************************************
*
*  $FC Funcao: TAB Criar tabuleiro
*
*  $ED Descricao da funcao
*     Inicia um tabuleiro vazio, sem peças.
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro de referência para tabuleiro.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetFaltouMemoria
*
*  $AE CondRet deve ter sido instanciado
*
*  $AS Se CondRet = TAB_CondRetOK
*     Concluiu funcao com sucesso.
*
*     Se CondRet = TAB_CondRetFaltouMemoria
*     Impossivel criar elemento, faltou memoria.
*
***********************************************************************/
   TAB_tpCondRet TAB_AvancarTipoPeca(TAB_tppTabuleiro pTabuleiro , int val);

/***********************************************************************
*
*  $FC Funcao: TAB Criar tabuleiro
*
*  $ED Descricao da funcao
*     Inicia um tabuleiro vazio, sem peças.
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro de referência para tabuleiro.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetFaltouMemoria
*
*  $AE CondRet deve ter sido instanciado
*
*  $AS Se CondRet = TAB_CondRetOK
*     Concluiu funcao com sucesso.
*
*     Se CondRet = TAB_CondRetFaltouMemoria
*     Impossivel criar elemento, faltou memoria.
*
***********************************************************************/
   TAB_tpCondRet TAB_SetarCorrente( TAB_tppTabuleiro pTabuleiro , char * NomeCasa );

/***********************************************************************
*
*  $FC Funcao: TAB Criar tabuleiro
*
*  $ED Descricao da funcao
*     Inicia um tabuleiro vazio, sem peças.
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro de referência para tabuleiro.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetFaltouMemoria
*
*  $AE CondRet deve ter sido instanciado
*
*  $AS Se CondRet = TAB_CondRetOK
*     Concluiu funcao com sucesso.
*
*     Se CondRet = TAB_CondRetFaltouMemoria
*     Impossivel criar elemento, faltou memoria.
*
***********************************************************************/
   TAB_tpCondRet TAB_InserirConteudoCasa(TAB_tppTabuleiro pTabuleiro , void * pPeca);


/***********************************************************************
*
*  $FC Funcao: TAB Criar tabuleiro
*
*  $ED Descricao da funcao
*     Inicia um tabuleiro vazio, sem peças.
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro de referência para tabuleiro.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetFaltouMemoria
*
*  $AE CondRet deve ter sido instanciado
*
*  $AS Se CondRet = TAB_CondRetOK
*     Concluiu funcao com sucesso.
*
*     Se CondRet = TAB_CondRetFaltouMemoria
*     Impossivel criar elemento, faltou memoria.
*
***********************************************************************/

   TAB_tpCondRet TAB_IrInicioCasas( TAB_tppTabuleiro pTabuleiro  );

/***********************************************************************
*
*  $FC Funcao: TAB Criar tabuleiro
*
*  $ED Descricao da funcao
*     Inicia um tabuleiro vazio, sem peças.
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro de referência para tabuleiro.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetFaltouMemoria
*
*  $AE CondRet deve ter sido instanciado
*
*  $AS Se CondRet = TAB_CondRetOK
*     Concluiu funcao com sucesso.
*
*     Se CondRet = TAB_CondRetFaltouMemoria
*     Impossivel criar elemento, faltou memoria.
*
***********************************************************************/
   
   TAB_tpCondRet TAB_AvancarCasas( TAB_tppTabuleiro pTabuleiro , int val );

/***********************************************************************
*
*  $FC Funcao: TAB Criar tabuleiro
*
*  $ED Descricao da funcao
*     Inicia um tabuleiro vazio, sem peças.
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro de referência para tabuleiro.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetFaltouMemoria
*
*  $AE CondRet deve ter sido instanciado
*
*  $AS Se CondRet = TAB_CondRetOK
*     Concluiu funcao com sucesso.
*
*     Se CondRet = TAB_CondRetFaltouMemoria
*     Impossivel criar elemento, faltou memoria.
*
***********************************************************************/
   TAB_tpCondRet TAB_ObterConteudo( TAB_tppTabuleiro pTabuleiro , void ** pConteudo );


/***********************************************************************
*
*  $FC Funcao: TAB Criar tabuleiro
*
*  $ED Descricao da funcao
*     Inicia um tabuleiro vazio, sem peças.
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro de referência para tabuleiro.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetFaltouMemoria
*
*  $AE CondRet deve ter sido instanciado
*
*  $AS Se CondRet = TAB_CondRetOK
*     Concluiu funcao com sucesso.
*
*     Se CondRet = TAB_CondRetFaltouMemoria
*     Impossivel criar elemento, faltou memoria.
*
***********************************************************************/
   TAB_tpCondRet TAB_IrInicioArestasCorrente(TAB_tppTabuleiro pTabuleiro);

/***********************************************************************
*
*  $FC Funcao: TAB Criar tabuleiro
*
*  $ED Descricao da funcao
*     Inicia um tabuleiro vazio, sem peças.
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro de referência para tabuleiro.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetFaltouMemoria
*
*  $AE CondRet deve ter sido instanciado
*
*  $AS Se CondRet = TAB_CondRetOK
*     Concluiu funcao com sucesso.
*
*     Se CondRet = TAB_CondRetFaltouMemoria
*     Impossivel criar elemento, faltou memoria.
*
***********************************************************************/
   TAB_tpCondRet TAB_ObterVerticeAresta(TAB_tppTabuleiro pTabuleiro , void ** Vertice , char * Aresta);

/***********************************************************************
*
*  $FC Funcao: TAB Criar tabuleiro
*
*  $ED Descricao da funcao
*     Inicia um tabuleiro vazio, sem peças.
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro de referência para tabuleiro.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetFaltouMemoria
*
*  $AE CondRet deve ter sido instanciado
*
*  $AS Se CondRet = TAB_CondRetOK
*     Concluiu funcao com sucesso.
*
*     Se CondRet = TAB_CondRetFaltouMemoria
*     Impossivel criar elemento, faltou memoria.
*
***********************************************************************/
   TAB_tpCondRet TAB_AvancarArestaCorrente(TAB_tppTabuleiro pTabuleiro , int val);

/***********************************************************************
*
*  $FC Funcao: TAB Criar tabuleiro
*
*  $ED Descricao da funcao
*     Inicia um tabuleiro vazio, sem peças.
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro de referência para tabuleiro.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetFaltouMemoria
*
*  $AE CondRet deve ter sido instanciado
*
*  $AS Se CondRet = TAB_CondRetOK
*     Concluiu funcao com sucesso.
*
*     Se CondRet = TAB_CondRetFaltouMemoria
*     Impossivel criar elemento, faltou memoria.
*
***********************************************************************/
   TAB_tpCondRet TAB_NumElementosArestasCorrente(TAB_tppTabuleiro pTabuleiro , int * Num);

/***********************************************************************
*
*  $FC Funcao: TAB Criar tabuleiro
*
*  $ED Descricao da funcao
*     Inicia um tabuleiro vazio, sem peças.
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro de referência para tabuleiro.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetFaltouMemoria
*
*  $AE CondRet deve ter sido instanciado
*
*  $AS Se CondRet = TAB_CondRetOK
*     Concluiu funcao com sucesso.
*
*     Se CondRet = TAB_CondRetFaltouMemoria
*     Impossivel criar elemento, faltou memoria.
*
***********************************************************************/
   TAB_tpCondRet TAB_ObterVerticeCorrente(TAB_tppTabuleiro pTabuleiro , char ** Id);

/***********************************************************************
*
*  $FC Funcao: TAB Criar tabuleiro
*
*  $ED Descricao da funcao
*     Inicia um tabuleiro vazio, sem peças.
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro de referência para tabuleiro.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetFaltouMemoria
*
*  $AE CondRet deve ter sido instanciado
*
*  $AS Se CondRet = TAB_CondRetOK
*     Concluiu funcao com sucesso.
*
*     Se CondRet = TAB_CondRetFaltouMemoria
*     Impossivel criar elemento, faltou memoria.
*
***********************************************************************/
   TAB_tpCondRet TAB_ObterConteudoVertice(TAB_tppTabuleiro pTabuleiro  , void ** VertConteudo);

/***********************************************************************
*
*  $FC Funcao: TAB Criar tabuleiro
*
*  $ED Descricao da funcao
*     Inicia um tabuleiro vazio, sem peças.
*
*  $EP Parametros
*     pTabuleiro  - Ponteiro de referência para tabuleiro.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetFaltouMemoria
*
*  $AE CondRet deve ter sido instanciado
*
*  $AS Se CondRet = TAB_CondRetOK
*     Concluiu funcao com sucesso.
*
*     Se CondRet = TAB_CondRetFaltouMemoria
*     Impossivel criar elemento, faltou memoria.
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
