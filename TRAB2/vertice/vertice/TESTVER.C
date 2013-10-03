/***************************************************************************
*  $MCI Módulo de implementação: TVER Teste vértice
*
*  Arquivo gerado:              TESTVER.c
*  Letras identificadoras:      TVER
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\TESTVER.BSW
*
*  Projeto: INF 1301 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: aw - Alexandre Werneck
*           fr - Fernanda Camelo Ribeiro
*	        vo - Vinicius de Luiz de Oliveira
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       afv   01/out/2013 início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Vertice.h"


static const char RESET_VERTICE_CMD			 [ ] = "=resetteste"       ;
static const char CRIAR_VERTICE_CMD			 [ ] = "=criavertice"      ;
static const char DESTRUIR_VERTICE_CMD		 [ ] = "=destruirvertice"  ;
static const char MUDAR_VALOR_VERTICE_CMD	 [ ] = "=mudarvalorvert"   ;
static const char OBTER_VALOR_VERTICE_CMD	 [ ] = "=obtervalorvert"   ;
static const char RETORNAR_VALOR_VERTICE_CMD [ ] = "=retornarvalorvert"   ;

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_VERTICE   10
#define DIM_VT_VALOR     80

VER_tppVertice   vtVertices[ DIM_VT_VERTICE ] ;

/***** Protótipos das funções encapuladas no módulo *****/

static int ValidarInxVertice( int inxVertice , int Modo ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TVER &Testar vértice
*
*  $ED Descrição da função
*     Podem ser criadas até 10 vértices, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de vértices. Provoca vazamento de memória
*     =criavertice                   inxVertice string CondRetEsp
*     =destruirvertice               inxVertice CondRetEsp
*     =mudarvalorvert                inxVertice string CondRetEsp
*     =obtervalorvert                inxVertice string CondRetEsp
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxVertice  = -1 ,
          numLidos    = -1 ,
          CondRetEsp  = -1  ;

	  int i = 0;

	  char StringDado[DIM_VT_VALOR];

	  VER_tpCondRet CondRetObtido ;

      /* Efetuar reset de teste de vértice */

         if ( strcmp( ComandoTeste , RESET_VERTICE_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_VERTICE ; i++ )
            {
               vtVertices[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de vértice */

      /* Testar Criarvértice */

         else if ( strcmp( ComandoTeste , CRIAR_VERTICE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxVertice , StringDado , &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxVertice( inxVertice , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = VER_CriarVertice( &vtVertices[ inxVertice ] , StringDado ) ;

            return TST_CompararInt( CondRetEsp , CondRetObtido ,
               "Erro ao criar novo vértice."  ) ;

         } /* fim ativa: Testar Criarvértice */

      /* Testar Destruir vértice */

         else if ( strcmp( ComandoTeste , DESTRUIR_VERTICE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                               &inxVertice , &CondRetEsp ) ;

            if ( numLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = VER_DestruirVertice( vtVertices[ inxVertice ] ) ;

            vtVertices[ inxVertice ] = NULL ;

            return TST_CompararInt( CondRetEsp , CondRetObtido ,
               "Não foi possível destruir vértice."  ) ;

         } /* fim ativa: Testar Destruir vértice */

		  /* Testar Mudar valor do vértice */

         else if ( strcmp( ComandoTeste , MUDAR_VALOR_VERTICE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                               &inxVertice , StringDado , &CondRetEsp ) ;

            if ( numLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = VER_MudarNomeVertice( vtVertices[ inxVertice ] , StringDado ) ;

            return TST_CompararInt( CondRetEsp , CondRetObtido ,
               "Não foi possível mudar valor do vértice."  ) ;

         } /* fim ativa: Testar Mudar valor do vértice */

		  /* Testar Obter valor do vértice */

         else if ( strcmp( ComandoTeste , OBTER_VALOR_VERTICE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                               &inxVertice , StringDado , &CondRetEsp ) ;

            if ( numLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = VER_ObterValor( vtVertices[ inxVertice ] , StringDado ) ;

            return TST_CompararInt( CondRetEsp , CondRetObtido ,
               "Não foi possível obter valor do vértice."  ) ;

         } /* fim ativa: Testar Obter valor do vértice */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TVER &Testar vértice */


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: TVER -Validar indice de vértice
*
***********************************************************************/

   int ValidarInxVertice( int inxVertice , int Modo )
   {

      if ( ( inxVertice <  0 )
        || ( inxVertice >= DIM_VT_VERTICE ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtVertices[ inxVertice ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtVertices[ inxVertice ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim função: TVER -Validar indice de vértice */

/********** Fim do módulo de implementação: TVER Teste vértices **********/

