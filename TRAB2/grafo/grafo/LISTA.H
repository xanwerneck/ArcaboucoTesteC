#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD Módulo de definição: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.H
*  Letras identificadoras:      LIS
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
*     Implementa listas genéricas duplamente encadeadas.
*     Podem existir n listas em operação simultaneamente.
*     As listas possuem uma cabeça encapsulando o seu estado.
*
*     Cada lista é homogênea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que contém.
*
*     Os ponteiros para os dados são copiados para elementos da lista.
*     Não é copiado o valor apontado por estes ponteiros.
*
*     O controle da destruição do valor de um elemento a ser excluído
*     é realizado por uma função fornecida pelo usuário do módulo.
*
*     Cada lista referencia uma função que determina como devem ser
*     desalocados os dados nela contidos.
*
*     A função de liberação dos valores contidos nos elementos deve
*     assegurar a liberação de todos os espaços referenciados pelo
*     valor contido em um elemento.
*     Esta função é chamada antes de se desalocar um elemento
*     de uma lista.
*     Caso não seja necessário desalocar o valor referenciado pelo
*     elemento, o ponteiro para a função de liberação poderá ser NULL .
*     Caso o elemento da lista seja a única âncora do valor referenciado,
*     esta função deve promover a destruição (free) desse valor e
*     de todos os dados nele ancorados.
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

         LIS_CondRetOK = 0,
               /* Concluiu corretamente */

         LIS_CondRetListaVazia = 1 ,
               /* A lista não contém elementos */

         LIS_CondRetFimLista = 2,
               /* Foi atingido o fim de lista */

         LIS_CondRetNaoAchou = 3,
               /* Não encontrou o valor procurado */

         LIS_CondRetFaltouMemoria = 9
               /* Faltou memória ao tentar criar um elemento de lista ou uma lista */

   } LIS_tpCondRet ;


/***********************************************************************
*
*  $FC Função: LIS  &Criar lista
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
*     LIS_CondRetFaltouMemoria - Não conseguiu criar a lista.
*     LIS_CondRetOK - Conseguiu criar a lista com sucesso.
*
***********************************************************************/

   LIS_tpCondRet LIS_CriarLista(
             void   ( * ExcluirValor ) ( void * pDado ) , LIS_tppLista * pLista ) ;

/***********************************************************************
*
*  $FC Função: LIS  &Destruir lista
*
*  $ED Descrição da função
*     Destrói a lista fornecida.
*     O parâmetro ponteiro para a lista não é modificado.
*     Se ocorrer algum erro durante a destruição, a lista resultará
*     estruturalmente incorreta.
*     Inicialmente a lista torna-se vazia para depois a liberação.
*     *Não existe previsão para possíveis falhas de execução.
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
*     pLista - ponteiro para a lista a ser esvaziada.
*     A lista fornecida não deverá esta vazia.
*
*  $FV Valor retornado
*     LIS_CondRetOK - Elementos eliminados com sucesso.
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
*     pValor - ponteiro para o valor do novo elemento, tipo definido 
               pelo usuário.
*              Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK - Se conseguiu inserir o elemento corretamente.
*     LIS_CondRetFaltouMemoria - Elemento não foi inserido.
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor        ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Inserir elemento após
*
*  $ED Descrição da função
*     Insere novo elemento apás o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
*     Parâmetros
*        pLista - ponteiro para a lista onde deve ser inserido o elemento
*        pValor - ponteiro para o valor do novo elemento, tipo definido 
*                 pelo usuário.
*                 Pode ser NULL
*           
*
*  $FV Valor retornado
*        LIS_CondRetOK - Se conseguiu inserir o elemento corretamente.
*        LIS_CondRetFaltouMemoria - Elemento não foi inserido.
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Excluir elemento
*
*  $ED Descrição da função
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento à esquerda do corrente, este será o novo corrente.
*     Se não existir e existir o elemento à direita, este se tornará corrente.
*     Se este também não existir a lista tornou-se vazia.
*
*  $EP Parâmetros
*     pLista    - Ponteiro para a lista na qual deve excluir o corrente.
*
*  $FV Valor retornado
*     LIS_CondRetOK - Se o elemento foi excluído com sucesso.
*     LIS_CondRetListaVazia - Se a lista está vazia.
*     LIS_CondRetFaltouMemoria - Se não conseguiu excluir o elemento.
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
*     pLista      - Ponteiro para a lista onde está o corrente.
*     pContListaM - Ponteiro ao qual será atribuído o valor a ser retornado.
*
*  $FV Valor retornado
*     LIS_CondRetOK           - Se o elemento corrente da lista existe, retorna.
*     LIS_CondRetListaVazia   - Se a lista estiver vazia, não é possível retornar valor.
*
***********************************************************************/

  LIS_tpCondRet LIS_ObterValor( LIS_tppLista pLista , void **pContListaM ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Ir para o elemento inicial
*
*  $ED Descrição da função
*     Torna corrente o primeiro elemento da lista.
*     Faz nada se a lista está vazia.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a manipular.
*
*  $FV Valor retornado
*     LIS_CondRetOK - Foi ao início da lista.
*
***********************************************************************/

   LIS_tpCondRet LIS_IrInicioLista( LIS_tppLista pLista ) ;


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
*     LIS_CondRetOK - Foi ao final da lista.
*
***********************************************************************/

   LIS_tpCondRet LIS_IrFinalLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Avançar elemento
*
*  $ED Descrição da função
*     Avança o elemento corrente numElem elementos na lista
*     Se numElem for positivo avança em direção ao final
*     Se numElem for negativo avança em direção ao início
*     numElem pode ser maior do que o número de elementos existentes na
*     direção desejada
*     Se numElem for zero somente verifica se a lista está vazia
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista a ser manipulada
*     numElem - o número de elementos a andar
*
*  $FV Valor retornado
*     CondRetOK         - Se numElem elementos tiverem sido andados
*     CondRetFimLista   - Se encontrou o fim da lista antes de andar numElem
*                         elementos
*     CondRetListaVazia - Se a lista está vazia
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
*     A função compara ponteiro e não conteúdo apontado com a função do usuário.
*
*  $EP Parâmetros
*     pLista       - Ponteiro para a lista onde procura.
*     pValor       - Ponteiro para o valor procurado;
*                    Pode ser NULL.
*     ComparaValor - Ponteiro para funcao de comparacao
*                    de valores encontrados e procurados
*
*  $FV Valor retornado
*     LIS_CondRetOK  - Se encontrou;
*                      O elemento corrente é o elemento encontrado.
*
*     LIS_CondRetNaoAchou     - Se o ponteiro não foi encontrado.
*                               O elemento corrente continua o mesmo.
*     LIS_CondRetListaVazia   - Se a lista estiver vazia.
*
***********************************************************************/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor ,
                                    int ( * ComparaValor ) ( void * pValorCorr , void * pValorBuscado ) ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Checa se a origem é nula
*
*  $ED Descrição da função
*     Faz uma verificação se o ponteiro para origem da lista é NULL.
*     Com isso a lista está vazia.
*
*  $EP Parâmetros
*     pLista       - Ponteiro para a lista.
*
*  $FV Valor retornado
*     LIS_CondRetOK           - Se existe elemento na lista.
*     LIS_CondRetListaVazia   - Se a lista estiver vazia e Origem é NULL.
*
***********************************************************************/

LIS_tpCondRet LIS_ChecaOrigemNulo(LIS_tppLista pLista) ;

LIS_tpCondRet LIS_NumElem( LIS_tppLista pLista , int * numElem );

#undef LISTA_EXT

/********** Fim do módulo de definição: LIS  Lista duplamente encadeada **********/

#else
#endif
