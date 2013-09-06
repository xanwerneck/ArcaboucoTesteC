/***************************************************************************
*  $MCI Módulo de implementação: TMAT Teste matriz de listas
*
*  Arquivo gerado:              TESTMAT.C
*  Letras identificadoras:      TMAT
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: aw - Alexandre Werneck
*           fe - Fernanda Ribeiro
*			vi - Vinicius
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       1.00   aw   04/09/2013 Início do desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_ESPC.H"

#include    "Generico.h"
#include    "LerParm.h"

#include    "MATRIZ.H"

static const char CRIAR_MATRIZ_CMD			[ ] = "=criarmatriz"     ;
static const char INSERIR_LISTA_MATRIZ_CMD	[ ] = "=inserirlistamat" ;
static const char IR_NORTE_CMD				[ ] = "=irnorte"         ;
static const char IR_NORDESTE_CMD			[ ] = "=irnordeste"      ;	
static const char IR_LESTE_CMD				[ ] = "=irleste"         ;
static const char IR_SUDESTE_CMD			[ ] = "=irsudeste"       ;
static const char IR_SUL_CMD				[ ] = "=irsul"           ;
static const char IR_SUDOESTE_CMD			[ ] = "=irsudoeste"      ;
static const char IR_OESTE_CMD				[ ] = "=iroeste"         ;
static const char IR_NOROESTE_CMD			[ ] = "=irnoroeste"      ;
static const char OBTER_LISTA_CORR_CMD		[ ] = "=obterlistacorr"  ;
static const char IR_INICIO_CMD				[ ] = "=irinicio"        ;

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_MATRIZ   10
#define DIM_VALOR       100

MAT_tppMatriz  vtMatrizes[ DIM_VT_MATRIZ ] ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TMAT Efetuar operações de teste específicas para matriz
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     matriz sendo testado.
*
*  $EP Parâmetros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      MAT_tpCondRet CondRetObtido   = MAT_CondRetOK ;
      MAT_tpCondRet CondRetEsperada = MAT_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      char ValorEsperado = '?'  ;
      char ValorObtido   = '!'  ;
      char ValorDado     = '\0' ;

      int  NumLidos = -1 ;

      TST_tpCondRet Ret ;

		/* Testar MAT Criar matriz */

		if ( strcmp( ComandoTeste , CRIAR_MATRIZ_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_CriarMatriz( ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar matriz." );

         } /* fim ativa: Testar MAT Criar matriz */

		Testes que faltam ser feitos
		/* Testar MAT Inserir Lista na Matriz */
		/* Testar MAT Ir norte do no corrente */
		/* Testar MAT Ir nordeste do no corrente */
		/* Testar MAT Ir leste do no corrente */
		/* Testar MAT Ir sudeste do no corrente */
		/* Testar MAT Ir sul do no corrente */
		/* Testar MAT Ir sudoeste do no corrente */
		/* Testar MAT Ir oeste do no corrente */
		/* Testar MAT Ir noroeste do no corrente */
		/* Testar MAT Obter lista do nó corrente */
		/* Testar MAT Ir para o início/raiz da matriz */

         
      /* Testar ARV Adicionar filho à direita */

         else if ( strcmp( ComandoTeste , INS_DIR_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ci" ,
                               &ValorDado , &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_InserirDireita( ValorDado ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado inserir àa direita." );

         } /* fim ativa: Testar ARV Adicionar filho à direita */

      /* Testar ARV Adicionar filho à esquerda */

         else if ( strcmp( ComandoTeste , INS_ESQ_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ci" ,
                               &ValorDado , &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_InserirEsquerda( ValorDado ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao inserir à esquerda." );

         } /* fim ativa: Testar ARV Adicionar filho à esquerda */

      /* Testar ARV Ir para nó pai */

         else if ( strcmp( ComandoTeste , IR_PAI_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_IrPai( ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para pai." );

         } /* fim ativa: Testar ARV Ir para nó pai */

      /* Testar ARV Ir para nó à esquerda */

         else if ( strcmp( ComandoTeste , IR_ESQ_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_IrNoEsquerda( ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para esquerda." );

         } /* fim ativa: Testar ARV Ir para nó à esquerda */

      /* Testar ARV Ir para nó à direita */

         else if ( strcmp( ComandoTeste , IR_DIR_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_IrNoDireita( ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para direita." );

         } /* fim ativa: Testar ARV Ir para nó à direita */

      /* Testar ARV Obter valor corrente */

         else if ( strcmp( ComandoTeste , OBTER_VAL_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ci" ,
                               &ValorEsperado , &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_ObterValorCorr( &ValorObtido ) ;

            Ret = TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao obter valor corrente." );

            if ( Ret != TST_CondRetOK )
            {
               return Ret ;
            } /* if */

            return TST_CompararChar( ValorEsperado , ValorObtido ,
                                     "Conteúdo do nó está errado." ) ;

         } /* fim ativa: Testar ARV Obter valor corrente */

      /* Testar ARV Destruir árvore */

         else if ( strcmp( ComandoTeste , DESTROI_CMD ) == 0 )
         {

            ARV_DestruirArvore( ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar ARV Destruir árvore */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TARV Efetuar operações de teste específicas para árvore */

/********** Fim do módulo de implementação: Módulo de teste específico **********/

