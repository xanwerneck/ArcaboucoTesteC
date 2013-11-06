#if ! defined( JOGO_ )
#define JOGO_
/***************************************************************************
*
*  $MCD Modulo de definicao: JOG  Jogo do tabuleiro
*
*  Arquivo gerado:              JOGO.H
*  Letras identificadoras:      JOG
*
*  Projeto: INF 1301 - Verificador de Xeque-Mate
*  Gestor:  Flavio Bevilacqua
*  Autores: afv:  aw - Alexandre Werneck
*                 fr - Fernanda C Ribeiro
*			      vo - Vinicius de Luiz de Oliveira
*
*  $HA Historico de evolucao:
*     Versão  Autor    Data     Observacoes
*     Y       afv   xx/xx/2013  finalizacao do desenvolvimento do modulo
*     1       afv   19/out/2013 inicio do desenvolvimento do modulo
*
*  $ED Descricao do modulo
*     O presente modulo implementa a criacao e manipulacao de estruturas 
*      do tipo jogo para tabuleiro, que se limitam a uma estrutura 
*      de encapsulamento que consiste em duas listas duplamente encadeadas
*      e outra estrutura que consiste em um identificador, 
*      duas listas duplamente encadeadas e um tipo de peca do jogo.
*     Vide declaracao das estruturas no modulo de desenvolvimento.
*     O jogo consiste basicamente em funcoes para manutencao de uma partida 
*      verificadora de Xeque-mate de tabuleiro de xadrez, na qual so sera 
*      manipulado uma partida por vez, podendo haver a necessidade de salvar 
*      a partida. 
*
***************************************************************************/
 
#if defined( JOGO_OWN )
   #define JOGO_EXT
#else
   #define JOGO_EXT extern
#endif

#include "PECA.H"
#include "TABULEIRO.H"

/***** Declaracoes exportadas pelo modulo *****/

/* Tipo referencia para um jogo */
typedef struct JOG_tagListaPeca * JOG_tppJogo ;


/* Tipo referencia para uma peca do jogo */
typedef struct JOG_tagPecaJogo * JOG_tppPecaJogo ;

/***********************************************************************
*
*  $TC Tipo de dados: JOG Condicoes de retorno
*
*  $ED Descricao do tipo
*     Condicoes de retorno das funcoes do jogo
*
***********************************************************************/

typedef enum {

	 JOG_CondRetOK = 0 ,
		   /* Concluiu corretamente */

	 JOG_CondRetJogoNulo = 1 ,
		   /* Jogo nulo */

	 JOG_CondRetFimLista = 2 ,
		   /* Final de lista */
		   
	 JOG_CondRetFaltouMemoria = 9
		   /* Faltou memoria ao tentar criar um elemento jogo */

} JOG_tpCondRet ;


/***************************************************************************
*
*  $FC Funcao: JOG Criar jogo
*
*  $ED Descricao da funcao
*     Inicia um jogo vazio.
*
*  $EP Parâmetros
*     pJogo - Ponteiro para o jogo que sera criado.     
*
*  $FV Valor retornado
*     JOG_CondRetOK
*     JOG_CondRetFaltouMemoria
*
*  $AE CondRet deve ter sido instanciado
*
*  $AS Se CondRet = JOG_CondRetOK
*	   Jogo criado com sucesso.
*
*	   Se CondRet = JOG_CondRetFaltouMemoria
*	   Jogo nao foi criado, nao foi possivel alocar memoria.
*
**************************************************************************/

JOG_tpCondRet JOG_CriarJogo(JOG_tppJogo * pJogo);


/***********************************************************************
*
*  $FC Funcao: JOG Inserir peca no time A
*
*  $ED Descricao da funcao
*     Insere um tipo peca numa estrutura de tipo jogo.
*
*  $EP Parametros
*     pJogo      - Ponteiro para o jogo.     
*     pPecaSetar - Ponteiro para a peca que sera inserida em jogo.
*
*  $FV Valor retornado
*     JOG_CondRetOK
*     JOG_CondRetFaltouMemoria
*     JOG_CondRetJogoNulo
*     JOG_CondRetFimLista
*
*  $AE CondRet deve ter sido instanciado
*      pPecaSetar tem que ter estrutura valida e definida.
*
*  $AS Se CondRet = JOG_CondRetOK
*	   Inseriu peca com sucesso.
*
*      Se CondRet = JOG_CondRetFaltouMemoria
*      Peca nao foi inserida, faltou memoria.
*
*	   Se CondRet = JOG_CondRetJogoNulo
*	   Peca nao foi inserida, jogo nulo.
*
*      Se CondRet = JOG_CondRetFimLista
*      Peca nao foi inserida, pPecaSetar nulo.
*
***********************************************************************/

JOG_tpCondRet JOG_InserirPecaTimeA(JOG_tppJogo pJOGO , PEC_tppPeca pPecaSetar);


/***********************************************************************
*
*  $FC Funcao: JOG Inserir peca no time B
*
*  $ED Descricao da funcao
*     Insere um tipo peca numa estrutura de tipo jogo.
*
*  $EP Parametros
*     pJogo      - Ponteiro para o jogo.     
*     pPecaSetar  - Ponteiro para a peca que sera inserida em jogo.
*
*  $FV Valor retornado
*     JOG_CondRetOK
*     JOG_CondRetFaltouMemoria
*     JOG_CondRetJogoNulo
*     JOG_CondRetFimLista
*
*  $AE CondRet deve ter sido instanciado.
*      pPecaSetar tem que ter estrutura valida e definida.
*
*  $AS Se CondRet = JOG_CondRetOK
*	   Inseriu peca com sucesso.
*
*      Se CondRet = JOG_CondRetFaltouMemoria
*      Peca nao foi inserida, faltou memoria.
*
*	   Se CondRet = JOG_CondRetJogoNulo
*	   Peca nao foi inserida, jogo nulo.
*
*      Se CondRet = JOG_CondRetFimLista
*      Peca nao foi inserida, pPecaSetar nulo.
*
***********************************************************************/

JOG_tpCondRet JOG_InserirPecaTimeB(JOG_tppJogo pJOGO , PEC_tppPeca pPecaSetar);


/***********************************************************************
*
*  $FC Funcao: JOG Preenche caminho
*
*  $ED Descricao da funcao
*     Preenchendo a lista de caminhos das pecas do time passado por parametro
*     com as casas do tabuleiro segundo o tipo de peca de cada peca.
*
*  $EP Parametros
*     pJOGO	   - Referencia para o jogo.  
*     Time     - Qual o time cuja lista de caminho das pecas sera preenchida.
*
*  $FV Valor retornado
*     JOG_CondRetOK
*     JOG_CondRetJogoNulo
*
*  $AE CondRet deve ter sido instanciado
*      Time tem que ser um caracter 'A' ou 'B'.
*      Lista de pecas do time passado por parametro tem que ser valido.
*
*  $AS Se CondRet = JOG_CondRetOK
*	   Preencheu o caminho com sucesso.
*
*	   Se CondRet = JOG_CondRetJogoNulo
*	   Lista de caminho nao foi preenchida, jogo nulo.
*
***********************************************************************/

JOG_tpCondRet JOG_PreencheCaminho(JOG_tppJogo pJOGO , char Time);


/***********************************************************************
*
*  $FC Funcao: JOG Numero de pecas do time
*
*  $ED Descricao da funcao
*     Retorna por parametro a quantidade de pecas do time do jogo, ambos
*     tambem passados por parametro.
*
*  $EP Parametros
*     pJOGO	   - Referencia para o jogo.  
*     Time     - Qual o time que sera obtido o numero de pecas.
*     NumPecas - Ponteiro para o qual sera retornado o numero de pecas
*
*  $FV Valor retornado
*     JOG_CondRetOK
*     JOG_CondRetJogoNulo
*
*  $AE CondRet deve ter sido instanciado
*      Time tem que ser um caracter 'A' ou 'B'.
*      Lista de pecas do time passado por parametro tem que ser valido.
*
*  $AS Se CondRet = PEC_CondRetOK
*	   Retornou o numero de pecas com sucesso.
*
*	   Se CondRet = JOG_CondRetJogoNulo
*	   Nao retornou peca, jogo nulo.
*
***********************************************************************/

JOG_tpCondRet JOG_NumPecasTime(JOG_tppJogo pJOGO ,char Time, int * NumPecas);


/***********************************************************************
*
*  $FC Funcao: JOG Obter tipo de peca
*
*  $ED Descricao da funcao
*     Retorna por parametro o tipo peca do time do jogo, ambos tambem
*     passados por parametro.
*
*  $EP Parametros
*     pJOGO	   - Referencia para o jogo.  
*     Time     - Qual o time que sera obtido o tipo de peca.
*     pTipo    - Ponteiro para retornar o tipo de peca.
*
*  $FV Valor retornado
*     JOG_CondRetOK
*     JOG_CondRetJogoNulo
*
*  $AE CondRet deve ter sido instanciado
*      Time tem que ser um caracter 'A' ou 'B'.
*      A lista do time do jogo em questão tem que ser válida.
*
*  $AS Se CondRet = JOG_CondRetOK
*	   Retornou o tipo de peca do time com sucesso.
*
*	   Se CondRet = JOG_CondRetJogoNulo
*	   Nao conseguiu retornar tipo de peca, jogo nulo.
*
***********************************************************************/

JOG_tpCondRet JOG_ObterTipoPeca(JOG_tppJogo pJOGO , char Time, void ** pTipo);


/***********************************************************************
*
*  $FC Funcao: JOG Ir inicio das pecas
*
*  $ED Descricao da funcao
*     Faz com que o corrente da lista de pecas do time passado por 
*     parametro va para o inicio dessa lista.
*
*  $EP Parametros
*     pJOGO	   - Referencia para o jogo com os times e suas respectivas 
*                listas de pecas.  
*     Time     - Qual o time cujo corrente da lista de pecas ira para 
*                o inicio da lista.
*
*  $FV Valor retornado
*     JOG_CondRetOK
*     JOG_CondRetJogoNulo
*     JOG_CondRetFimLista     
*
*  $AE CondRet deve ter sido instanciado
*      Time tem que ser um caracter 'A' ou 'B'.
*      A lista do time do jogo em questão tem que ser válida.
*
*  $AS Se CondRet = JOG_CondRetOK
*	   Conseguiu com sucesso ir para inicio da lista de pecas do jogo 
*      em questao.
*
*      Se CondRet = JOG_CondRetJogoNulo
*	   Nao conseguiu ir para o inicio da lista de pecas, jogo nulo.
*
*	   Se CondRet = JOG_CondRetFimLista
*	   Nao conseguiu ir para o inicio da lista de pecas, lista fazia. 
*
***********************************************************************/

JOG_tpCondRet JOG_IrInicioPecas(JOG_tppJogo pJOGO , char Time);


/***********************************************************************
*
*  $FC Funcao: JOG Obter peca do jogo
*
*  $ED Descricao da funcao
*     Retorna por parametro a peca do time do jogo, ambos também passados
*     por parametros.
*
*  $EP Parametros
*     pJOGO	   - Jogo do qual sera obtido a peca.  
*     Time     - Sobre qual e o time que sera obtido a peca.
*     pTipo    - Ponteiro para retorno do tipo de peca do time.
*
*  $FV Valor retornado
*     JOG_CondRetOK
*     JOG_CondRetJogoNulo
*
*  $AE CondRet deve ter sido instanciado
*      Time tem que ser um caracter 'A' ou 'B'.
*      A lista do time do jogo em questão tem que ser válida.
*
*  $AS Se CondRet = JOG_CondRetOK
*	   retornou peca com sucesso.
*
*	   Se CondRet = JOG_CondRetJogoNulo
*	   Não foi possivel obter peca, jogo nulo.
*
***********************************************************************/

JOG_tpCondRet JOG_ObterPecaJogo(JOG_tppJogo pJOGO , char Time, void ** pTipo);


JOG_tpCondRet JOG_PreencheCaminho(JOG_tppJogo pJOGO, TAB_tppTabuleiro pTabuleiro);

JOG_tpCondRet JOG_AvancarCorrrenteTime(JOG_tppJogo pJOGO , char Time , int val);

#undef JOGO_EXT

/********** Fim do modulo de definicao: JOG  JOGO do tabuleiro **********/

#else
#endif
