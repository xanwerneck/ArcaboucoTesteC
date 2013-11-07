#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD Modulo de definicao: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.H
*  Letras identificadoras:      LIS
*
*  Projeto: INF 1301 - Verificador de Xeque-Mate
*  Gestor:  Flavio Bevilacqua
*  Autores: afv:  aw - Alexandre Werneck
*                 fr - Fernanda C Ribeiro
*                 vo - Vinicius de Luiz de Oliveira
*
*  $HA Historico de evolucao:
*     Versão  Autor    Data     Observacoes
*     Y       afv   xx/xx/2013  finalizacao do desenvolvimento do modulo
*     1       afv   19/out/2013 inicio do desenvolvimento do modulo
*
*  $ED Descricao do modulo
*     Implementa listas genericas duplamente encadeadas.
*     Podem existir n listas em operacao simultaneamente.
*     As listas possuem uma cabeca encapsulando o seu estado.
*
*     Cada lista e homogenea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que contem.
*
*     Os ponteiros para os dados sao copiados para elementos da lista.
*     Não e copiado o valor apontado por estes ponteiros.
*
*     O controle da destruicao do valor de um elemento a ser excluido
*     e realizado por uma funcao fornecida pelo usuario do modulo.
*
*     Cada lista referencia uma funcao que determina como devem ser
*     desalocados os dados nela contidos.
*
*     A funcao de liberacao dos valores contidos nos elementos deve
*     assegurar a liberacao de todos os espacos referenciados pelo
*     valor contido em um elemento.
*     Esta funcao e chamada antes de se desalocar um elemento
*     de uma lista.
*     Caso não seja necessário desalocar o valor referenciado pelo
*     elemento, o ponteiro para a funcao de liberacao podera ser NULL .
*     Caso o elemento da lista seja a unica ancora do valor referenciado,
*     esta funcao deve promover a destruicao (free) desse valor e
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

/***********************************************************************
*
*  $FC Função: LIS  &Retorna quantidade de elementos
*
*  $ED Descrição da função
*     Retorna o numero de elementos presentes na lista.
*
*  $EP Parâmetros
*     pLista       - Ponteiro para a lista.
*
*  $FV Valor retornado
*     &numElem     - com o valor de pLista->numElem
*
***********************************************************************/

LIS_tpCondRet LIS_NumElem( LIS_tppLista pLista , int * numElem );

#undef LISTA_EXT

/********** Fim do módulo de definição: LIS  Lista duplamente encadeada **********/

#else
#endif
