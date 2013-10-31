#if ! defined( TABULEIRO_ )
#define TABULEIRO_
/***************************************************************************
*
*  $MCD Módulo de definição: TAB  Tabuleiro de xadrez
*
*  Arquivo gerado:              TABULEIRO.H
*  Letras identificadoras:      TAB
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
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
*     1       afv   19/out/2013 início desenvolvimento
*
*  $ED Descrição do módulo
*     Armazena as funções de tabuleiro, contem as instruções do jogo.
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

		 TAB_TimeBVazio = 2 ,

         TAB_CondRetFaltouMemoria = 9
               /* Faltou memória ao tentar criar um tabuleiro */

   } TAB_tpCondRet ;


/***********************************************************************
*
*  $FC Função: TAB  &Criar lista
*
*  $ED Descrição da função
*     Cria uma lista genérica duplamente encadeada.
*     Os possíveis tipos são desconhecidos inicialmente.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado à lista.
*
*  $EP Parâmetros
*     pLista  - ponteiro para o elemento do tipo de lista a ser alocado.
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*                     Esta função é criada no módulo que utiliza a lista.
*
*  $FV Valor retornado
*     TAB_CondRetFaltouMemoria - Não conseguiu criar a lista.
*     TAB_CondRetOK - Conseguiu criar a lista com sucesso.
*
***********************************************************************/

   TAB_tpCondRet TAB_CriarTabuleiro( TAB_tppTabuleiro * pTabuleiro) ;

   TAB_tpCondRet TAB_ApresentaTabuleiro( TAB_tppTabuleiro pTabuleiro );

   TAB_tpCondRet TAB_CriarPeca(TAB_tppTabuleiro pTabuleiro , char * Nome , int Diagonal , int Reta , int QtdeMov, int Time);

   TAB_tpCondRet TAB_ApresentaPecas(TAB_tppTabuleiro pTabuleiro);


#undef TABULEIRO_EXT

/********** Fim do módulo de definição: LIS  Lista duplamente encadeada **********/

#else
#endif
