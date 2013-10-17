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
*  Autores: aw - Alexandre Werneck
*           fr - Fernanda Camelo Ribeiro
*			vo - Vinicius de Luiz de Oliveira
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       afv   19/out/2013 início desenvolvimento
*
*  $ED Descrição do módulo
*       Implementa vértices com contéudo string.
*
***************************************************************************/
 
#if defined( VERTICE_OWN )
   #define VERTICE_EXT
#else
   #define VERTICE_EXT extern
#endif


/***** Declarações exportadas pelo módulo *****/

typedef struct VER_tagVertice * VER_tppVerticeCont ;

/***********************************************************************
*
*  $TC Tipo de dados: VER Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções de vértice
*
***********************************************************************/

   typedef enum {

         VER_CondRetOK = 0,
               /* Concluiu corretamente */

         VER_CondRetNaoAchou = 1,
               /* Não encontrou o valor procurado */

		 VER_CondRetVerVazio = 2,
               /* Vertice vazio procurado */

         VER_CondRetFaltouMemoria = 9
               /* Faltou memória ao tentar criar um elemento de vértice */

   } VER_tpCondRet ;


/***********************************************************************
*
*  $FC Função: VER  &Criar vértice
*
*  $ED Descrição da função
*     Cria um vértice e recebe uma string a ser atribuída como valor
*     do elemento único da estrutura vértice.
*
*  $EP Parâmetros
*     pVertice  - ponteiro para o vertice a ser criado
*	  Nome      - String a ser inserida
*
*  $FV Valor retornado
*     VER_CondRetOK  - vértice criado com sucesso
*     VER_CondRetFaltouMemoria - vértice não foi criado.
*
***********************************************************************/

   VER_tpCondRet VER_CriarVertice( VER_tppVerticeCont * pVertice , char * Nome  ) ;


/***********************************************************************
*
*  $FC Função: VER  &Destruir vértice
*
*  $ED Descrição da função
*     Destrói o vértice fornecido.
*     Elimina primeiro o valor do elemento, setando nome como vazio.
*     Aponta o elemento vertice para null
*
*  $EP Parâmetros
*     pVertice  - vertice a ser excluído
*
*  $FV Valor retornado
*     VER_CondRetOK       - destruiu o vértice
*
***********************************************************************/

   VER_tpCondRet VER_DestruirVertice( VER_tppVerticeCont pVertice) ;

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
*     VER_CondRetOK       - modificou sem erros
*     VER_CondRetNaoAchou - vértice nulo
*     VER_CondRetVerVazio - vértice sem valor ou parametro Nome fornecido vazio
*
***********************************************************************/

   VER_tpCondRet VER_MudarNomeVertice( VER_tppVerticeCont pVertice , char * Nome  ) ;

/***********************************************************************
*
*  $FC Função: VER  &Obter valor do vértice
*
*  $ED Descrição da função
*     Compara o nome passado como parametro com o valor do vertice passado
*
*  $EP Parâmetros
*     pVertice  - vertice a ser comparado
*     Nome      - string a ser comparada
*
*  $FV Valor retornado
*     VER_CondRetOK       - valores iguais
*     VER_CondRetNaoAchou - vértice nulo
*     VER_CondRetVerVazio - vértice sem valor ou parametro Nome fornecido vazio
*
***********************************************************************/

VER_tpCondRet VER_ObterValor( VER_tppVerticeCont pVertice , char * Nome  ) ;


/***********************************************************************
*
*  $FC Função: VER  &Retornar valor do vértice
*
*  $ED Descrição da função
*     Retorna por parâmetro o valor do vértice também passado por parâmetro
*
*  $EP Parâmetros
*     pVertice  - vertice a ser analisado
*     Nome      - string a ser atribuída o valor do vértice
*
*  $FV Valor retornado
*     VER_CondRetOK       - valor do vértice válido, atribuição bem sucedida
*     VER_CondRetNaoAchou - vértice nulo
*     VER_CondRetVerVazio - vértice sem valor ou parametro Nome fornecido vazio
*
***********************************************************************/

VER_tpCondRet VER_RetornaValor( VER_tppVerticeCont pVertice , char * nome  ) ;



#undef VERTICE_EXT

/********** Fim do módulo de definição: VER  Vértice **********/

#else
#endif