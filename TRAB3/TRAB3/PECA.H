#if ! defined( PECA_ )
#define PECA_
/***************************************************************************
*
*  $MCD Modulo de definicao: PEC  Peca do tabuleiro
*
*  Arquivo gerado:              PECA.H
*  Letras identificadoras:      PEC
*
*  Projeto: INF 1301 - Verificador de Xeque-mate
*  Gestor:  Flavio Bevilacqua
*  Autores: afv:  aw - Alexandre Werneck
*                 fr - Fernanda C Ribeiro
*			      vo - Vinicius de Luiz de Oliveira
*
*  $HA Historico de evolucao:
*     Versao  Autor    Data     Observacoes
*     1       afv   11/nov/2013 inicio do desenvolvimento do modulo
*
*  $ED Descricao do modulo
*      O presente modulo implementa a criacao e manipulacao de estruturas 
*     do tipo peca para tabuleiro.
*	   Podem existir n tipos de pecas em um tabuleiro simultaneamente.
*     Alem do tipo de pecas, podem existir n pecas de tipo repetido.
*
***************************************************************************/
 
#if defined( PECA_OWN )
   #define PECA_EXT
#else
   #define PECA_EXT extern
#endif

/***** Declaracoes exportadas pelo modulo *****/

/* Tipo referencia para uma peca */
typedef struct PEC_tagElemPeca * PEC_tppPeca ;


/**************************************************************************
*
*  $TC Tipo de dados: PEC Condicoes de retorno
*
*
*  $ED Descricao do tipo
*     Condicoes de retorno das funcoes da peca
*
**************************************************************************/

typedef enum {

	 PEC_CondRetOK = 0 ,
		   /* Concluiu corretamente */

	 PEC_CondRetPecaNula = 1 ,
	 	   /* Peca nula */

	 PEC_CondRetFaltouMemoria = 9
		   /* Faltou memoria ao criar um elemento de peca */

} PEC_tpCondRet ;


/***************************************************************************
*
*  $FC Funcao: PEC Criar tipo de peca
*
*  $ED Descricao da funcao
*     Cria um tipo de peca com diagonal, reta, quantidade e nome ja 
*      inicializados.
*
*  $EP Parāmetros
*     pPeca - Ponteiro de referencia para tipo de peca.
*     Diag  - Possibilidade de ir para a diagonal.
*             Valor igual a 1 se for possivel.
*             Valor igual a 0 se nao for possivel.
*     Reta  - Possibilidade de ir para a vertical e horizontal.
*             Valor igual a 1 se for possivel.
*             Valor igual a 0 se nao for possivel.
*     Qtde  - Numero de casas que ele pode se movimentar para diagonal 
*             ou horizontal/vertical;
*     Nome  - Nome do tipo de peca.
*     
*
*  $FV Valor retornado
*     PEC_CondRetOK
*     PEC_CondRetFaltouMemoria
*
*  $AE 'CondRet' deve ter sido instanciado
*      'Diag' eh valor inteiro 0 ou 1.
*      'Reta' eh valor inteiro 0 ou 1.
*      'Qtde' eh valor inteiro entre 1 e 7.
*      'Nome' eh string com no maximo 4 caracteres.
*
*  $AS Se CondRet = PEC_CondRetOK:
*         pPeca inicializada.
*	      Concluiu funcao com sucesso.
*
*	   Se CondRet = PEC_CondRetFaltouMemoria:
*         pPeca nao foi inicializada.
*	      Impossivel criar elemento, faltou memoria.
*
**************************************************************************/

PEC_tpCondRet PEC_CriarPeca(PEC_tppPeca * pPeca, int Diag , int Reta , 
                            int Qtde, char * Nome);


/**************************************************************************
*
*  $FC Funcao: PEC Obter nome
*
*  $ED Descricao da funcao
*     Retorna por parāmetro o peca nome.
*
*  $EP Parāmetros
*     pPeca - Referencia para a peca da qual sera retornado o valor.
*     NomePeca - Ponteiro para o qual sera retornado o nome da peca.
*
*  $FV Valor retornado
*     PEC_CondRetOK
*     PEC_CondRetPecaNula
*
*  $AE CondRet deve ter sido instanciado
*      Nome da peca tem que ser uma string nao nula.
*
*  $AS Se CondRet = PEC_CondRetOK
*	   Obteve nome da peca com sucesso;
*
*	   Se CondRet = PEC_CondRetPecaNula
*	   Peca nula, nao retorna nada no NomePeca;
*
***********************************************************************/

PEC_tpCondRet PEC_ObterNome (PEC_tppPeca pPeca ,  void **NomePeca);


/***********************************************************************
*
*  $FC Funcao: PEC Obter dados do tipo peca
*
*  $ED Descricao da funcao
*     Retorna por parāmetros o Nome, a Diag, a Reta e a Qtde de pPeca.
*
*  $EP Parāmetros
*     pPeca - Referencia para a peca da qual serao retornados 
*             os elementos.
*     Nome  - Ponteiro para o qual sera retornado o peca Nome.
*     Diag  - Ponteiro para o qual sera retornado o peca Diag.
*     Reta  - Ponteiro para o qual sera retornado o peca Reta.
*     Qtde  - Ponteiro para o qual sera retornado o peca Qtde.
*
*  $FV Valor retornado
*     PEC_CondRetOK
*     PEC_CondRetPecaNula
*
*  $AE CondRet deve ter sido instanciado
*      Nome da peca tem que ser uma string nao nula.
*      Diag, Reta e Qtde da variavel de tipo PEC_tppPeca tem que
*      nao nulos, valores inteiros.
*      Diag e Reta da pPeca valores inteiros entre 0 e 1;
*      Qtde da pPeca valor inteiro entre 1 e 7;
*
*  $AS Se CondRet = PEC_CondRetOK
*	   Obteve Nome, Diag, Reta e Qtde com sucesso;
*
*	   Se CondRet = PEC_CondRetPecaNula
*	   Peca nula, nao pode retornar elementos da pPeca;
*
***********************************************************************/

PEC_tpCondRet PEC_ObterDadosTipoPeca (PEC_tppPeca pPeca , void ** Nome, 
                                     int * Diag , int * Reta , 
                                     int * Qtde);

/***********************************************************************
*
*  $FC Funcao: PEC Modificar Peca
*
*  $ED Descricao da funcao
*     Modifica a configuracao do tipo de peca
*
*  $EP Parāmetros
*     pPeca - Referencia para a peca a ser modificada
*     Diag  - Novo valor para diagonal.
*     Reta  - Novo valor para reta.
*     Qtde  - Novo valor para quantidade de casas.
*
*  $FV Valor retornado
*     PEC_CondRetOK
*     PEC_CondRetPecaNula
*
*  $AE CondRet deve ter sido instanciado
*      Ponteiro para peca nao nula.
*      Diag, Reta e Qtde contendo valores validos.
*      Diag e Reta da pPeca valores inteiros entre 0 e 1;
*      Qtde da pPeca valor inteiro entre 1 e 7;
*
*  $AS Se CondRet = PEC_CondRetOK
*	   Peca modificada com sucesso.
*
*	   Se CondRet = PEC_CondRetPecaNula
*	   Peca nula, nao pode modificar a peca.
*
***********************************************************************/
PEC_tpCondRet PEC_ModificarPeca(PEC_tppPeca pPeca , int Diag , int Reta , int Qtde);

/***********************************************************************
*
*  $FC Funcao: PEC Destroi a Peca
*
*  $ED Descricao da funcao
*     Destroi a peca fornecida
*
*  $EP Parāmetros
*     pPeca - Referencia para a peca a ser excluida.
*
*  $FV Valor retornado
*     PEC_CondRetOK
*     PEC_CondRetPecaNula
*
*  $AE CondRet deve ter sido instanciado
*      Ponteiro para peca nao nula.
*
*  $AS Se CondRet = PEC_CondRetOK
*	   Peca destruida com sucesso.
*
*	   Se CondRet = PEC_CondRetPecaNula
*	   Peca nula fornecida, nao e possivel excluir.
*
***********************************************************************/
PEC_tpCondRet PEC_DestroiPeca(PEC_tppPeca pPeca);

#undef PECA_EXT

/******** Fim do modulo de definicao: PEC  Peca do tabuleiro **********/

#else
#endif
