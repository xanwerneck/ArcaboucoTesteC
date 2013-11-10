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

typedef struct tpElemCasa * TAB_ElemCasa ;

typedef struct TAB_tgEstCasa * TAB_tppEstCasa ;

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

		 TAB_CondRetNaoAchou = 3 ,

		 TAB_CondRetFimLista = 4 ,

		 TAB_CondRetListaVazia = 5 ,

		 TAB_CondRetTabuleiroNulo = 6 ,

		 TAB_CondRetTabuleiroListaNula = 7 ,

		 TAB_CondRetCorrenteNulo = 8 ,

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

   TAB_tpCondRet TAB_CriarTipoPeca(TAB_tppTabuleiro pTabuleiro , char * Nome , int Diagonal , int Reta , int QtdeMov);

   TAB_tpCondRet TAB_ApresentaTipoPecas(TAB_tppTabuleiro pTabuleiro) ;

   TAB_tpCondRet TAB_ProcuraPeca(TAB_tppTabuleiro pTabuleiro , char * NomeBuscado , void ** PecaBuscada);

   TAB_tpCondRet TAB_IrInicioListaPecas(TAB_tppTabuleiro pTabuleiro);

   TAB_tpCondRet TAB_ObterTipoPeca(TAB_tppTabuleiro pTabuleiro , void ** pPeca);

   TAB_tpCondRet TAB_AvancarTipoPeca(TAB_tppTabuleiro pTabuleiro , int val);

   TAB_tpCondRet TAB_SetarCorrente( TAB_tppTabuleiro pTabuleiro , char * NomeCasa );

   TAB_tpCondRet TAB_InserirConteudoCasa(TAB_tppTabuleiro pTabuleiro , void * pPeca);


   /** caminhos **/

   TAB_tpCondRet TAB_IrInicioCasas( TAB_tppTabuleiro pTabuleiro  );
   TAB_tpCondRet TAB_AvancarCasas( TAB_tppTabuleiro pTabuleiro , int val );
   TAB_tpCondRet TAB_ObterConteudo( TAB_tppTabuleiro pTabuleiro , void ** pConteudo );


   TAB_tpCondRet TAB_IrInicioArestasCorrente(TAB_tppTabuleiro pTabuleiro);
   TAB_tpCondRet TAB_ObterVerticeAresta(TAB_tppTabuleiro pTabuleiro , void ** Vertice , char * Aresta);
   TAB_tpCondRet TAB_AvancarArestaCorrente(TAB_tppTabuleiro pTabuleiro , int val);

   TAB_tpCondRet TAB_NumElementosArestasCorrente(TAB_tppTabuleiro pTabuleiro , int * Num);

   TAB_tpCondRet TAB_ObterVerticeCorrente(TAB_tppTabuleiro pTabuleiro , char ** Id);

   TAB_tpCondRet TAB_ObterConteudoVertice(TAB_tppTabuleiro pTabuleiro  , void ** VertConteudo);

   TAB_tpCondRet TAB_PecaConteudoPeloVertice(void * Vertice  , void ** VertConteudo);
   

#undef TABULEIRO_EXT

/********** Fim do módulo de definição: LIS  Lista duplamente encadeada **********/

#else
#endif
