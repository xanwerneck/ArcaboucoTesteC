#if ! defined( PECA_ )
#define PECA_
/***************************************************************************
*
*  $MCD Módulo de definição: PEC  Peça do tabuleiro
*
*  Arquivo gerado:              PECA.H
*  Letras identificadoras:      PEC
*
*  Projeto: INF 1301 - Verificador de Xeque-Mate
*  Gestor:  Flavio Bevilacqua
*  Autores: afv:  aw - Alexandre Werneck
*                 fr - Fernanda C Ribeiro
*			      vo - Vinicius de Luiz de Oliveira
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     Y       afv   xx/xx/2013  finalização do desenvolvimento do modulo
*     1       afv   24/out/2013 início do desenvolvimento do módulo
*
*  $ED Descrição do módulo
*     O presente módulo implementa a criação e manipulação de estruturas 
*     do tipo peça para tabuleiro.
*	  Podem existir n tipos de peças em um tabuleiro simultaneamente.
*     Além do tipo de peças, podem existir n peças de tipo repetido.
*
***************************************************************************/
 
#if defined( PECA_OWN )
   #define PECA_EXT
#else
   #define PECA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma peça */
typedef struct PEC_tagElemPeca * PEC_tppPeca ;


/***********************************************************************
*
*  $TC Tipo de dados: PEC Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da peça
*
***********************************************************************/

typedef enum {

	 PEC_CondRetOK = 0 ,
		   /* Concluiu corretamente */

	 PEC_CondRetPecaNula = 1 ,
	 	   /* Peça nula */

	 PEC_CondRetFaltouMemoria = 9
		   /* Faltou memória ao tentar criar um elemento de peça */

} PEC_tpCondRet ;


/***********************************************************************
*
*  $FC Função: PEC Criar peça
*
*  $ED Descrição da função
*     Inicia uma peça com elementos diagonal, reta, quantidade e nome.
*
*  $EP Parâmetros
*     pPeca - Referência para a peça que será criada.
*     Diag  - Se a peça pode se mover para diagonais;
*             Valor igual a 1 se for possível esse tipo de movimento;
*             Valor igual a 0 se não for possível;
*     Reta  - Se a peça pode se mover horizontalmente e verticalmente;
*             Valor igual a 1 se for possível esse tipo de movimento;
*             Valor igual a 0 se não for possível;
*     Qtde  - Número de casas que ele pode se movimentar para diagonal 
*             ou horizontal/vertical;
*     Nome  - String com o nome da peça que será criada;
*     
*
*  $FV Valor retornado
*     PEC_CondRetOK
*     PEC_CondRetFaltouMemoria
*
*  $AE CondRet deve ter sido instanciado
*      Diag é valor inteiro 0 ou 1;
*      Reta é valor inteiro 0 ou 1;
*      Qtde é valor inteiro entre 1 e 7;
*      String com 2 caracteres;
*
*  $AS Se CondRet = PEC_CondRetOK
*	   Peça criada com sucesso;
*
*	   Se CondRet = PEC_CondRetFaltouMemoria
*	   Peça não foi criada por falta de memória;
*
***********************************************************************/

PEC_tpCondRet PEC_CriarPeca(PEC_tppPeca * pPeca, int Diag , int Reta , int Qtde, char * Nome);


/***********************************************************************
*
*  $FC Função: PEC Obter nome
*
*  $ED Descrição da função
*     Retorna por parâmetro o peça nome.
*
*  $EP Parâmetros
*     pPeca - Referência para a peça da qual será retornado o valor.
*     NomePeca - Ponteiro para o qual será retornado o nome da peça.
*
*  $FV Valor retornado
*     PEC_CondRetOK
*     PEC_CondRetPecaNula
*
*  $AE CondRet deve ter sido instanciado
*      Nome da peça tem que ser uma string não nula.
*
*  $AS Se CondRet = PEC_CondRetOK
*	   Obteve nome da peça com sucesso;
*
*	   Se CondRet = PEC_CondRetPecaNula
*	   Peça nula, não retorna nada no NomePeca;
*
***********************************************************************/

PEC_tpCondRet PEC_ObterNome (PEC_tppPeca pPeca ,  void **NomePeca);


/***********************************************************************
*
*  $FC Função: PEC Obter dados do tipo peça
*
*  $ED Descrição da função
*     Retorna por parâmetros o Nome, a Diag, a Reta e a Qtde de pPeca.
*
*  $EP Parâmetros
*     pPeca - Referência para a peça da qual serão retornados 
*             os elementos.
*     Nome  - Ponteiro para o qual será retornado o peça Nome.
*     Diag  - Ponteiro para o qual será retornado o peça Diag.
*     Reta  - Ponteiro para o qual será retornado o peça Reta.
*     Qtde  - Ponteiro para o qual será retornado o peça Qtde.
*
*  $FV Valor retornado
*     PEC_CondRetOK
*     PEC_CondRetPecaNula
*
*  $AE CondRet deve ter sido instanciado
*      Nome da peça tem que ser uma string não nula.
*      Diag, Reta e Qtde da variável de tipo PEC_tppPeca tem que
*      não nulos, valores inteiros.
*      Diag e Reta da pPeca valores inteiros entre 0 e 1;
*      Qtde da pPeca valor inteiro entre 1 e 7;
*
*  $AS Se CondRet = PEC_CondRetOK
*	   Obteve Nome, Diag, Reta e Qtde com sucesso;
*
*	   Se CondRet = PEC_CondRetPecaNula
*	   Peça nula, não pode retornar elementos da pPeca;
*
***********************************************************************/

PEC_tpCondRet PEC_ObterDadosTipoPeca(PEC_tppPeca pPeca , void ** Nome, int * Diag , int * Reta , int * Qtde);

#undef PECA_EXT

/********** Fim do módulo de definição: PEC  Peca do tabuleiro **********/

#else
#endif
