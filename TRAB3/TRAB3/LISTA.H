#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD Modulo de definicao: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.H
*  Letras identificadoras:      LIS
*
*  Projeto: INF 1301 - Verificador de Xeque-mate
*  Gestor:  Flavio Bevilacqua
*  Autores: afv:  aw - Alexandre Werneck
*                 fr - Fernanda C Ribeiro
*                 vo - Vinicius de Luiz de Oliveira
*
*  $HA Historico de evolucao:
*     Versao  Autor    Data     Observacoes
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
*     Nao e copiado o valor apontado por estes ponteiros.
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
*     Caso nao seja necessario desalocar o valor referenciado pelo
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

/***** Declaracoes exportadas pelo modulo *****/

/* Tipo referencia para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condicoes de retorno
*
*
*  $ED Descricao do tipo
*     Condicoes de retorno das funcoes da lista
*
***********************************************************************/

   typedef enum {

         LIS_CondRetOK = 0,
               /* Concluiu corretamente */

         LIS_CondRetListaVazia = 1 ,
               /* A lista nao contem elementos */

         LIS_CondRetFimLista = 2,
               /* Foi atingido o fim de lista */

         LIS_CondRetNaoAchou = 3,
               /* Nao encontrou o valor procurado */

         LIS_CondRetFaltouMemoria = 9
               /* Faltou memoria ao tentar criar um elemento de lista ou uma lista */

   } LIS_tpCondRet ;


/***********************************************************************
*
*  $FC Funcao: LIS  &Criar lista
*
*  $ED Descricao da funcao
*     Cria uma lista generica duplamente encadeada.
*     Os possiveis tipos sao desconhecidos inicialmente.
*     A tipagem e implicita.
*     Nao existe identificador de tipo associado a lista.
*
*  $EP Parametros
*     pLista        - Ponteiro para o elemento do tipo de lista a ser 
*                     alocado.
*     ExcluirValor  - Ponteiro para a funcao que processa a exclusao do 
*                     valor referenciado pelo elemento a ser excluido.
*                     Ver descricao do modulo.
*
*  $FV Valor retornado
*     LIS_CondRetFaltouMemoria
*     LIS_CondRetOK
*
*  $AE CondRet deve ter sido instanciado
*      ExcluirValor deve ser instanciado no modulo que utiliza essa funcao.
*
*  $AS Se CondRet = LIS_CondRetOK
*    Lista criada com sucesso.
*
*    Se CondRet = LIS_CondRetFaltouMemoria
*    Lista nao foi criada, nao foi possivel alocar memoria.
*
***********************************************************************/

  LIS_tpCondRet LIS_CriarLista( void (* ExcluirValor) (void * pDado) , 
                               LIS_tppLista * pLista ) ;

/***********************************************************************
*
*  $FC Funcao: LIS  &Destruir lista
*
*  $ED Descricao da funcao
*     Desaloca a lista fornecida.
*     O parametro ponteiro para a lista nao e modificado.
*     Se ocorrer algum erro durante a destruicao, a lista estara
*     estruturalmente incorreta.
*     Inicialmente a lista torna-se vazia para depois haver a liberacao.
*
*  $FV Valor retornado
*     LIS_CondRetOK    - destruiu sem problemas
*
*  $AE CondRet deve ter sido instanciado
*
*  $AS Se CondRet = LIS_CondRetOK
*      Lista desalocada com sucesso.
*
*      Nao existe previsao para possiveis falhas de execucao.
*
***********************************************************************/

   LIS_tpCondRet LIS_DestruirLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Funcao: LIS  &Esvaziar lista
*
*  $ED Descricao da funcao
*     Desaloca/libera todos os elementos, sem contudo desalocar a lista.
*
*  $EP Parametros
*     pLista - ponteiro para a lista a ser esvaziada.
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetListaVazia
*
*  $AE CondRet deve ter sido instanciado
*
*  $AS Se CondRet = LIS_CondRetOK
*      Elementos eliminados com sucesso.
*
*      Se CondRet = LIS_CondRetListaVazia
*      Nao eliminou elemenetos, lista nula.
*
*      Nao existe previsao para possiveis falhas de execucao.
*
***********************************************************************/

   LIS_tpCondRet LIS_EsvaziarLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Funcao: LIS  &Inserir elemento antes
*
*  $ED Descricao da funcao
*     Insere novo elemento antes do elemento corrente.
*
*  $EP Parametros
*     pLista - Ponteiro para a lista onde deve ser inserido o elemento
*     pValor - Ponteiro para o valor do novo elemento, tipo definido 
*               pelo usuario.
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetFaltouMemoria
*
*  $AE CondRet deve ter sido instanciado
*      pValor pode ser NULL
*
*  $AS Se CondRet = LIS_CondRetOK
*      Inseriu elemento na lista corretamente.
*
*      Se CondRet = LIS_CondRetFaltouMemoria
*      Nao inseriu elemento, faltou memoria.
*
*     Caso a lista esteja vazia, insere no primeiro elemento da lista.
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor        ) ;


/***********************************************************************
*
*  $FC Funcao: LIS  &Inserir elemento apos
*
*  $ED Descricao da funcao
*     Insere novo elemento apos o elemento corrente.
*     Caso a lista esteja vazia, insere no primeiro elemento da lista.
*
*  $EP Parametros
*     Parametros
*        pLista - Ponteiro para a lista onde deve ser inserido o elemento
*        pValor - Ponteiro para o valor do novo elemento, tipo definido 
*                 pelo usuario.
*           
*
*  $FV Valor retornado
*        LIS_CondRetOK
*        LIS_CondRetFaltouMemoria
*
*  $AE CondRet deve ter sido instanciado
*      pValor pode ser NULL
*
*  $AS Se CondRet = LIS_CondRetOK
*      Inseriu elemento na lista corretamente.
*
*      Se CondRet = LIS_CondRetFaltouMemoria
*      Nao inseriu elemento, faltou memoria.
*
*     Caso a lista esteja vazia, insere no primeiro elemento da lista.
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        ) ;


/***********************************************************************
*
*  $FC Funcao: LIS  &Excluir elemento
*
*  $ED Descricao da funcao
*     Exclui o elemento corrente da lista dada, tratando o encadeamento.
*
*  $EP Parametros
*     pLista    - Ponteiro para a lista na qual deve excluir o corrente.
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetListaVazia
*
*  $AE CondRet deve ter sido instanciado
*      Lista passada não pode ser nula.
*
*  $AS Se CondRet = LIS_CondRetOK
*      Excluiu corrente com sucesso.
*
*      Se CondRet = LIS_CondRetListaVazia
*      Nao excluiu corrente, corrente ja esta nulo.
*
*     Nao existe previsao para possiveis falhas de execucao.
***********************************************************************/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Funcao: LIS  &Obter referencia para o valor contido no elemento
*
*  $ED Descricao da funcao
*     Obtem a referencia para o valor contido no elemento corrente da 
*      lista.
*
*  $EP Parametros
*     pLista      - Ponteiro para a lista onde esta o corrente.
*     pContListaM - Ponteiro ao qual sera atribuido o valor a ser 
*                   retornado.
*
*  $FV Valor retornado
*     LIS_CondRetOK          
*     LIS_CondRetListaVazia 
*
*  $AE CondRet deve ter sido instanciado
*      Lista passada não pode ser nula.
*
*  $AS Se CondRet = LIS_CondRetOK
*      Retornou valor com sucesso.
*
*      Se CondRet = LIS_CondRetListaVazia
*      Nao retornou valor, corrente nulo.
* 
***********************************************************************/

  LIS_tpCondRet LIS_ObterValor( LIS_tppLista pLista , void **pContListaM ) ;


/***********************************************************************
*
*  $FC Funcao: LIS  &Ir para o elemento inicial
*
*  $ED Descricao da funcao
*     Torna corrente o primeiro elemento da lista.
*
*  $EP Parametros
*     pLista - Ponteiro para a lista.
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetListaVazia
*
*  $AE CondRet deve ter sido instanciado
*      Lista passada não pode ser nula.
*      Se o corrente for nulo, ele ja e o elemento inicial.
*
*  $AS Se CondRet = LIS_CondRetOK
*      Concluiu com sucesso.
*
*      Se CondRet = LIS_CondRetListaVazia
*      Lista vazia, nao ha elemento para retornar.
*
***********************************************************************/

   LIS_tpCondRet LIS_IrInicioLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Funcao: LIS  &Ir para o elemento final
*
*  $ED Descricao da funcao
*     Torna corrente o elemento final da lista.
*     Faz nada se a lista esta vazia.
*
*  $EP Parametros
*     pLista - ponteiro para a lista a manipular
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetListaVazia
*
*  $AE CondRet deve ter sido instanciado
*      Lista passada não pode ser nula.
*      Se o corrente for nulo, ele ja e o elemento inicial.
*
*  $AS Se CondRet = LIS_CondRetOK
*      Concluiu com sucesso.
*
*      Se CondRet = LIS_CondRetListaVazia
*      Lista vazia, nao ha elemento para retornar.
*
***********************************************************************/

   LIS_tpCondRet LIS_IrFinalLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Funcao: LIS  &Avancar elemento
*
*  $ED Descricao da funcao
*     Avanca o elemento corrente numElem elementos na lista.
*     Se numElem for positivo avanca em direcao ao final.
*     Se numElem for negativo avanca em direcao ao inicio.
*     numElem pode ser maior do que o numero de elementos existentes na
*     direcao desejada, fazendo entao o corrente apontar para o inicio 
*     ou para o final da lista.
*     Se numElem for zero somente verifica se a lista esta vazia.
*
*  $EP Parametros
*     pLista  - Ponteiro para a lista a ser manipulada.
*     numElem - Numero de elementos a andar a partir do corrente.
*
*  $FV Valor retornado
*     CondRetOK          
*     CondRetFimLista    
*     CondRetListaVazia 
*
*  $AE CondRet deve ter sido instanciado
*      Lista passada não pode ser nula.
*      numElem pode ser qualquer valor natural.
*
*  $AS Se CondRet = LIS_CondRetOK
*      Concluiu com sucesso.
*
*      Se CondRet = CondRetFimLista
*      Encontrou o fim da lista antes de andar numElem elementos.
*      Setou corrente como final de lista (se numElem >0) 
*      ou inicio de lista (se numElem <0).
*
*      Se CondRet = LIS_CondRetListaVazia
*      Lista vazia, nao ha elemento para andar.
*
***********************************************************************/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem ) ;


/***********************************************************************
*
*  $FC Funcao: LIS  &Procurar elemento contendo valor
*
*  $ED Descricao da funcao
*     Procura o elemento que referencia o valor dado.
*     A funcao compara ponteiro e nao conteudo apontado com a 
*     funcao passada pelo usuario.
*
*  $EP Parametros
*     pLista       - Ponteiro para a lista.
*     pValor       - Ponteiro para o valor procurado.
*                    Pode ser NULL.
*     ComparaValor - Ponteiro para funcao de comparacao
*                    de valores encontrados e procurados.
*
*  $FV Valor retornado
*     LIS_CondRetOK  
*     LIS_CondRetNaoAchou     
*     LIS_CondRetListaVazia   
*
*  $AE CondRet deve ter sido instanciado
*      Lista passada não pode ser nula.
*      pValor pode ser nulo.
*      Funcao passada por parametro nao pode ser nula.
*
*  $AS Se CondRet = LIS_CondRetOK
*      Concluiu com sucesso.
*      O elemento corrente e o elemento encontrado.
* 
*      Se CondRet = LIS_CondRetNaoAchou
*      O ponteiro nao foi encontrado.
*      O elemento corrente continua o mesmo. 
*
*      Se CondRet = LIS_CondRetListaVazia
*      Lista vazia, nao ha elemento comparar.
*
***********************************************************************/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor ,
                                    int ( * ComparaValor ) ( void * pValorCorr , void * pValorBuscado ) ) ;


/***********************************************************************
*
*  $FC Funcao: LIS  &Checa se a origem e nula
*
*  $ED Descricao da funcao
*     Faz uma verificacao se o ponteiro para origem da lista e NULL.
*     Com isso a lista esta vazia.
*
*  $EP Parametros
*     pLista       - Ponteiro para a lista.
*
*  $FV Valor retornado
*     LIS_CondRetOK           
*     LIS_CondRetListaVazia   
*
*  $AE CondRet deve ter sido instanciado
*      Lista passada não pode ser nula.
*
*  $AS Se CondRet = LIS_CondRetOK
*      Existe elemento na lista.
*
*      Se CondRet = LIS_CondRetListaVazia
*      Lista vazia.
*
***********************************************************************/

LIS_tpCondRet LIS_ChecaOrigemNulo(LIS_tppLista pLista) ;

/***********************************************************************
*
*  $FC Funcao: LIS  &Retorna quantidade de elementos
*
*  $ED Descricao da funcao
*     Retorna o numero de elementos presentes na lista.
*
*  $EP Parametros
*     pLista       - Ponteiro para a lista.
*     numElem      - Ponteiro para atribuicao da quantidade de elementos 
*                    da lista.
* 
*  $FV Valor retornado
*     LIS_CondRetOK     
*
*  $AE CondRet deve ter sido instanciado
*      Lista passada não pode ser nula.
*
*  $AS Se CondRet = LIS_CondRetOK
*      Concluiu com sucesso.
*
***********************************************************************/

LIS_tpCondRet LIS_NumElem( LIS_tppLista pLista , int * numElem );

#undef LISTA_EXT

/********** Fim do modulo de definicao: LIS  Lista duplamente encadeada **********/

#else
#endif
