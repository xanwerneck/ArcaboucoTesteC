#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD Módulo de definição: LIS  Lista de caracteres duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
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
*     1       afv   02/set/2013 início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa listas de caracteres duplamente encadeadas.
*     Podem existir n listas em operação simultaneamente.
*     As listas possuem uma cabeça encapsulando o seu estado.
*
*     Cada lista é homogênea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que contém do tipo char.
*
*     Os ponteiros para os dados são copiados para elementos da lista.
*        Não é copiado o valor apontado por estes ponteiros.
*
*     A função de liberação dos valores contidos nos elementos deve
*        assegurar a liberação de todos os espaços referenciados pelo
*        valor contido em um elemento.
*        Esta função é chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso não seja necessário desalocar o valor referenciado pelo
*        elemento, o ponteiro para a função de liberação poderá ser NULL .
*        Caso o elemento da lista seja a única âncora do valor referenciado,
*        esta função deve promover a destruição (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
*
***********************************************************************/

   typedef enum {

         LIS_CondRetOK = 0 ,
               /* Concluiu corretamente */

         LIS_CondRetListaVazia = 1 ,
               /* A lista não contém elementos */

         LIS_CondRetFimLista = 2 ,
               /* Foi atingido o fim de lista */

         LIS_CondRetNaoAchou = 3 ,
               /* Não encontrou o valor procurado */

		 LIS_CondRetNaoVazia = 4 ,
               /* Não foi possivel esvaziar a lista */

         LIS_CondRetFaltouMemoria = 9
               /* Faltou memória ao tentar criar um elemento de lista */

   } LIS_tpCondRet ;


/***********************************************************************
*
*  $FC Função: LIS  &Criar lista
*
*  $ED Descrição da função
*     Cria uma lista duplamente encadeada.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado à lista.
*
*  $EP Parâmetros
*     pLista - Ponteiro para a posição de vetor do tipo Lista
				para criação da Lista.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista que foi passado.
*     Este ponteiro será utilizado pelas funções que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará LIS_CondRetFaltouMemoria.
*
***********************************************************************/

   LIS_tpCondRet LIS_CriarLista( LIS_tppLista * pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Destruir lista
*
*  $ED Descrição da função
*     Destrói a lista fornecida.
*     O parâmetro ponteiro para a lista não é modificado.
*     Se ocorrer algum erro durante a destruição, a lista resultará
*     estruturalmente incorreta.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a ser destruida
*
*  $FV Valor retornado
*     LIS_CondRetOK    - destruiu sem problemas
*
***********************************************************************/

   LIS_tpCondRet LIS_DestruirLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Esvaziar lista
*
*  $ED Descrição da função
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a ser esvaziada
*
*  $FV Valor retornado
*	  LIS_CondRetListaVazia - Lista já vazia
*     LIS_CondRetOK    - destruiu sem problemas
*
***********************************************************************/

LIS_tpCondRet LIS_EsvaziarLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Inserir elemento antes
*
*  $ED Descrição da função
*     Insere novo elemento antes do elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista onde deve ser inserido o elemento
*     pValor - tipo char passado para inserção na Lista
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetFaltouMemoria
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           char pValor        ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Inserir elemento após
*
*  $ED Descrição da função
*     Insere novo elemento apás o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista onde deve ser inserido o elemento
*     pValor - tipo char passado para inserção na Lista
*           
*
*  $FV Valor retornado
*        LIS_CondRetOK
*        LIS_CondRetFaltouMemoria
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          char pValor        )
       ;


/***********************************************************************
*
*  $FC Função: LIS  &Excluir elemento
*
*  $ED Descrição da função
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento aa esquerda do corrente será o novo corrente.
*     Se não existir e existir o elemento à direita, este se tornará corrente.
*     Se este também não existir a lista tornou-se vazia.
*
*  $EP Parâmetros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetListaVazia
*
***********************************************************************/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Obter referência para o valor contido no elemento
*
*  $ED Descrição da função
*     Obtem a referência para o valor contido no elemento corrente da lista
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista de onde se quer o valor
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetNaoAchou
*
***********************************************************************/

   LIS_tpCondRet LIS_ObterValor( LIS_tppLista pLista, char pDado ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Ir para o elemento inicial
*
*  $ED Descrição da função
*     Torna corrente o primeiro elemento da lista.
*     Faz nada se a lista está vazia.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a manipular
*
*  $FV Valor retornado
*     Sem retorno
*
***********************************************************************/

   void IrInicioLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Ir para o elemento final
*
*  $ED Descrição da função
*     Torna corrente o elemento final da lista.
*     Faz nada se a lista está vazia.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a manipular
*
*  $FV Valor retornado
*     Sem retorno
*
***********************************************************************/

   void IrFinalLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Avançar elemento
*
*  $ED Descrição da função
*     Avança o elemento corrente numElem elementos na lista
*     Se numElem for positivo avança em direção ao final
*     Se numElem for negativo avança em direção ao início
*     numElem pode ser maior do que o númro de elementos existentes na
*               direção desejada
*     Se numElem for zero somente verifica se a lista está vazia
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista a ser manipulada
*     numElem - o número de elementos a andar
*
*  $FV Valor retornado
*     CondRetOK         - se numElem elementos tiverem sido andados
*     CondRetFimLista   - se encontrou o fim da lista antes de andar numElem
*                         elementos
*     CondRetListaVazia - se a lista está vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Procurar elemento contendo valor
*
*  $ED Descrição da função
*     Procura o elemento que referencia o valor dado.
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista onde procura
*     pValor  - char do valor procurado
*
*  $FV Valor retornado
*     LIS_CondRetOK  - se encontrou.
*                      O elemento corrente é o primeiro elemento do
*                      elemento corrente inclusive para o fim da lista
*                      e que contém o ponteiro procurado
*
*     LIS_CondRetNaoEncontrou - se o char não foi encontrado
*                      O elemento corrente continua o mesmo
*     LIS_CondRetListaVazia   - se a lista estiver vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    char pValor        ) ;

#undef LISTA_EXT

/********** Fim do módulo de definição: LIS  Lista duplamente encadeada com caracteres **********/

#else
#endif
