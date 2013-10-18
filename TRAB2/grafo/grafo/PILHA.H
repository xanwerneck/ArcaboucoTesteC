#if ! defined( PILHA_ )
#define PILHA_ 

/***************************************************************************
*
*  $MCD Módulo de definição: PIL  Pilha baseada em lista com cabeça
*
*  Arquivo gerado:              PILHA.h
*  Letras identificadoras:      PIL
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\PILHA.BSW
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
*     Implementa pilhas genéricas.
*
***************************************************************************/
 
#if defined( PILHA_OWN )
   #define PILHA_EXT
#else
   #define PILHA_EXT extern
#endif

#include "LISTA.H"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma pilha */

typedef LIS_tppLista PIL_tppPilha ;

/***********************************************************************
*
*  $TC Tipo de dados: PIL Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da pilha
*
***********************************************************************/

   typedef enum {

         PIL_CondRetOK = 0 ,
               /* Concluiu corretamente */

         PIL_CondRetPilhaVazia = 1 ,
               /* A pilha não contém elementos */

         PIL_CondRetFimPilha = 2,
               /* Foi atingido o fim de pilha */

         PIL_CondRetNaoAchou = 3,
               /* Não encontrou o valor procurado */

         PIL_CondRetFaltouMemoria = 9
               /* Faltou memória ao tentar criar um elemento de pilha */

   } PIL_tpCondRet ;


/***********************************************************************
*
*  $FC Função: PIL  &Criar pilha
*
*  $ED Descrição da função
*     Cria uma pilha genérica.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado à pilha.
*
*  $EP Parâmetros
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pela estrutura do elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a pilha.
*     Este ponteiro será utilizado pelas funções que manipulem esta pilha.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
*  Assertivas de entrada:
*	  Lista a ser criada
*	  Ponteiro para uma função válida para exclusão do conteúdo
*
*  Assertivas de saída:
*     A pilha criada
* 	  Condição de retorno
*
***********************************************************************/

	PIL_tpCondRet PIL_CriarPilha( PIL_tppPilha* pPilha, 
				  void   ( * ExcluirValor ) ( void * pDado ) ) ;


/***********************************************************************
*
*  $FC Função: PIL  &Destruir pilha
*
*  $ED Descrição da função
*     Destrói a pilha fornecida.
*     O parâmetro ponteiro para a pilha não é modificado.
*     Se ocorrer algum erro durante a destruição, a pilha resultará
*     estruturalmente incorreta.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  $FV Valor retornado
*     PIL_CondRetOK    - destruiu sem problemas
*
*  Assertivas de entrada:
*     Pilha que será destruída( liberada da memória)
*
*  Assertivas de saída:
*     Condição de retorno
*
***********************************************************************/

   PIL_tpCondRet PIL_DestruirPilha( PIL_tppPilha pPilha ) ;


/***********************************************************************
*
*  $FC Função: PIL  &Pilha Vazia
*
*  $ED Descrição da função
*     Caso a pilha esteja vazia, a função retorna 1.
*	  Caso contrário o retorno é 0.
*
*  $EP Parâmetros
*     pPilha - ponteiro para a pilha que está sendo analisada
*
*  Assertivas de entrada:
*	  Pilha que será verificada
*
*  Assertivas de saída:
*     Condição de retorno
*
***********************************************************************/

   PIL_tpCondRet PIL_PilhaVazia (  PIL_tppPilha pPilha  ) ;
   
   
/***********************************************************************
*
*  $FC Função: PIL  &Empilha um elemento
*
*  $ED Descrição da função
*     Insere novo elemento antes do elemento corrente.
*     Caso a pilha esteja vazia, insere o primeiro elemento da pilha.
*
*  $EP Parâmetros
*     pPilha - ponteiro para a pilha onde deve ser inserido o elemento
*     pValor - ponteiro para o valor do novo elemento
*              Pode ser NULL
*
*  $FV Valor retornado
*     PIL_CondRetOK
*     PIL_CondRetFaltouMemoria
*
*  Assertivas de entrada:
*	  A pilha que terá um ponteiro para uma estrutura adicionado ao topo
*	  Ponteiro para uma estrutura a ser adicionada na pilha
*
*  Assertivas de saída:
*	  A pilha com o valor adicionado
*	  Condição de retorno
*
***********************************************************************/

   PIL_tpCondRet PIL_PilhaPush (  PIL_tppPilha pPilha  ,
								void * pValor  ) ;
   
   
/***********************************************************************
*
*  $FC Função: PIL  &Desempilha um elemento
*
*  $ED Descrição da função
*     Retira um elemento do topo da pilha.
*     Caso a pilha esteja vazia, a função retorna NULL.
*
*  $EP Parâmetros
*     pPilha - ponteiro para a pilha onde deve ser inserido o elemento
*
*  $FV Valor retornado
*     não NULL - se o elemento corrente existe
*     NULL     - se a pilha estiver vazia
*                Pode retornar NULL se o valor inserido no elemento for NULL.
*
*  Assertivas de entrada:
*	  Pilha que terá um ponteiro para uma estrutura retirado do topo
*	  Ponteiro para um enderço que aponta para uma estrutura que será desempilhada da pilha
*
*  Assertivas de saída:
*	  A pilha com o valor retirado
*	  Valor retirado da pilha
*
***********************************************************************/

   PIL_tpCondRet PIL_PilhaPop (  PIL_tppPilha pPilha  ,  void ** pResp  ) ;

#undef PILHA_EXT

/********** Fim do módulo de definição: PIL  Pilha duplamente encadeada **********/

#endif