#if ! defined( PECA_ )
#define PECA_
/***************************************************************************
*
*  $MCD Módulo de definição: PEC  Peca do tabuleiro
*
*  Arquivo gerado:              PECA.H
*  Letras identificadoras:      PEC
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
*     Implementa a criação de elementos do tipo peca para tabuleiro
*
***************************************************************************/
 
#if defined( PECA_OWN )
   #define PECA_EXT
#else
   #define PECA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma peca */

typedef struct PEC_tagElemPeca * PEC_tppPeca ;


/***********************************************************************
*
*  $TC Tipo de dados: PEC Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da peca
*
***********************************************************************/

typedef enum {

	 PEC_CondRetOK = 0 ,
		   /* Concluiu corretamente */

	 PEC_CondRetPecaNula = 1 ,

	 PEC_CondRetFaltouMemoria = 9
		   /* Faltou memória ao tentar criar um elemento de peca */

} PEC_tpCondRet ;


/***********************************************************************
*
*  $FC Função: PEC  &Criar peca
*
*
***********************************************************************/

PEC_tpCondRet PEC_CriarPeca(PEC_tppPeca * pPeca, int Diag , int Reta , int Qtde, char * Nome);

PEC_tpCondRet PEC_ObterNome (PEC_tppPeca pPeca ,  void **NomePeca);

#undef PECA_EXT

/********** Fim do módulo de definição: PEC  Peca do tabuleiro **********/

#else
#endif
