#if ! defined( VERTICE_ )
#define VERTICE_
/***************************************************************************
*
*  $MCI Módulo de definição: VER Vertice
*
*  Arquivo gerado:              VERTICE.H
*  Letras identificadoras:      VER
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: afv
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       afv   19/09/2013 início desenvolvimento
*
*  $ED Descrição do módulo
*
***************************************************************************/
 
#if defined( VERTICE_OWN )
   #define VERTICE_EXT
#else
   #define VERTICE_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

typedef struct VER_tagVertice * VER_tppVertice ;

/***********************************************************************
*
*  $TC Tipo de dados: VER Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
*
***********************************************************************/

   typedef enum {

         VER_CondRetOK = 0,
               /* Concluiu corretamente */

         VER_CondRetNaoAchou = 1,
               /* Não encontrou o valor procurado */

		 VER_CondRetVerVazio = 2,
               /* Não encontrou o valor procurado */

         VER_CondRetFaltouMemoria = 9
               /* Faltou memória ao tentar criar um elemento de lista */

   } VER_tpCondRet ;


/***********************************************************************
*
*  $FC Função: VER  &Criar vértice
*
*  $ED Descrição da função
*     Cria um vértice e recebe uma string a ser atribuída como valor
*
*  $EP Parâmetros
*     pVertice  - ponteiro para o vertice a ser inserido
*	  Nome      - ponteiro para a string a ser inserida
*
*  $FV Valor retornado
*     VER_CondRetOK  - vértice criado com sucesso
*
***********************************************************************/

   VER_tpCondRet VER_CriarVertice( VER_tppVertice * pVertice , char * Nome  ) ;


/***********************************************************************
*
*  $FC Função: VER  &Destruir vértice
*
*  $ED Descrição da função
*     Destrói o vértice fornecido.
*     Elimina primeiro o valor do elemento, setando nome como vazio.
*     Da um free no elemento pVertice fornecido.
*
*  $EP Parâmetros
*     pVertice  - vertice a ser excluído
*
*  $FV Valor retornado
*     VER_CondRetOK       - destruiu sem problemas
*     VER_CondRetNaoAchou - vértice nulo           //////////////////////////////////// ANALISAR ESSE RETORNO //////////////////////////////////////
*
***********************************************************************/

   VER_tpCondRet VER_DestruirVertice( VER_tppVertice pVertice) ;

/***********************************************************************
*
*  $FC Função: VER  &Mudar valor do vértice
*
*  $ED Descrição da função
*     Modifica o valor do vértice
*     Objetivo da função é modificar o rótulo da string armazenada no vértice
*
*  $EP Parâmetros
*     pVertice  - vertice a ser modificado
*     Nome      - nova string que irá substituir o valor anterior
*
*  $FV Valor retornado
*     VER_CondRetOK       - modificou sem problemas
*     VER_CondRetNaoAchou - vértice nulo
*     VER_CondRetVerVazio - vértice sem valor / parametro passado vazio
*
***********************************************************************/

   VER_tpCondRet VER_MudarNomeVertice( VER_tppVertice pVertice , char * Nome  )

#undef VERTICE_EXT

/********** Fim do módulo de definição: VER  Vértice **********/

#else
#endif