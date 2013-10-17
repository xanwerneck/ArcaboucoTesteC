/***************************************************************************
*  $MCI Módulo de implementação: TGRAF Testa módulo grafo de vértices
*
*  Arquivo gerado:              TESTGRA.C
*  Letras identificadoras:      TGRA
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
*       1.00   afv   03/out/2013 Início do desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_ESPC.H"

#include    "Generico.h"
#include    "LerParm.h"

#include	"GRAFO.H"
#include    "VERTICE.H"
#include    "LISTA.H"


/***********************************************************************
* Operações em Grafo
*
***********************************************************************/
static const char CRIAR_GRAFO_CMD			[ ] = "=criargrafo"           ;
static const char CRIAR_VERTIVE_GRAFO_CMD	[ ] = "=criarverticegrafo"    ;
static const char CRIA_ARESTA_CMD       	[ ] = "=criararesta"          ;
static const char EXCLUIR_VERT_CMD   		[ ] = "=excluirvertice"       ;
static const char EXCLUIR_ARES_CMD   		[ ] = "=excluiraresta"        ;
static const char INSERE_VERT_ORIG_CMD      [ ] = "=inserirvertorigens"   ;
static const char OBTER_VALOR_VERT_CMD		[ ] = "=obtervalorvertcorr"   ;
static const char MUDAR_VALOR_VERT_CMD      [ ] = "=mudarvalorvertcorr"   ;
static const char DEFINIR_CORR_GRA_CMD      [ ] = "=definircorrentegra"   ;
static const char DESTRUIR_GRA_CMD          [ ] = "=destruirgrafo"        ;



#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_GRAFO       10
#define DIM_VALOR          100

GRA_tppGrafo    vtGrafo[ DIM_VT_GRAFO ] ;


/***** Protótipos das funções encapuladas no módulo *****/

static int ValidarInxGrafo( int inxGrafo , int Modo ) ;

static void TES_excluirInfo (void * pValor);

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
* Função: TGRA Testar grafo
*
*    Comandos disponíveis:
*
*    =criargrafo                   inxGrafo  DestruirVal CondRetEsp
*    =criarverticegrafo            inxGrafo  nome        casa       CondRetEsp
*    =criararesta                  casa      casa        inxGrafo   nome         CondRetEsp
*    =excluirvertice               inxGrafo  CondRetEsp
*    =excluiraresta                casa      casa        inxGrafo   CondRetEsp
*    =inserirvertorigens           inxGrafo  casa        CondRetEsp
*    =obtervalorvertcorr           inxGrafo  nome        CondRetEsp
*    =mudarvalorvertcorr           inxGrafo  nome        CondRetEsp
*    =definircorrentegra           inxGrafo  casa        CondRetEsp
*    =destruirgrafo                inxGrafo  CondRetEsp
*
***********************************************************************/


/***********************************************************************
*
*  $FC Função: TGRA Efetuar operações de teste específicas para grafo
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

	  GRA_tpCondRet CondRetObtido   = GRA_CondRetOK ;
      GRA_tpCondRet CondRetEsperada = GRA_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      char ValorEsperado = '?'  ;
      char ValorObtido   = '!'  ;
      char ValorDado     = '\0' ;
	  char ValorOrig     = '\0' ;
	  char ValorDest     = '\0' ;

	  char StringDado[DIM_VALOR];

	  int inxGrafo     = -1 ,
		  inxLista     = -1 ,
		  inxVertices  = -1 ,
		  inxVerticesOr= -1 ,
		  inxVerCont   = -1 ,
          NumLidos     = -1 ,
		  NumElementos = 0 ,
          CondRetEsp   = -1 ,
		  i            = 0 ;

		/* Testar GRA Criar grafo */

		if ( strcmp( ComandoTeste , CRIAR_GRAFO_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                               &inxGrafo , &CondRetEsperada ) ;

            if ( (NumLidos != 2) || ( ! ValidarInxGrafo(inxGrafo, VAZIO) ) )
            {
               return TST_CondRetParm ;
            } /* if */

			vtGrafo[ inxGrafo ] = NULL;

			CondRetObtido = GRA_CriarGrafo( &vtGrafo[ inxGrafo ] , TES_excluirInfo );


            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar grafo." );

         } /* fim ativa: Testar GRA Criar grafo */		


		/* Testar GRA Criar vertice para grafo */

		else if( strcmp( ComandoTeste , CRIAR_VERTIVE_GRAFO_CMD ) == 0 )
		{

			NumLidos = LER_LerParametros ( "isci" , &inxGrafo , &StringDado , &ValorDado , &CondRetEsperada );

			if ( NumLidos != 4 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = GRA_CriaVerticeGrafo( vtGrafo[ inxGrafo ] , StringDado , ValorDado );

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar vertice no grafo." );


		} /* fim ativa: Testar GRA Criar vertice para grafo */


		/* Testar GRA Inserir aresta */

		else if(strcmp ( ComandoTeste, CRIA_ARESTA_CMD ) == 0)
		{
			NumLidos = LER_LerParametros ( "ccisi" , &ValorOrig, &ValorDest , &inxGrafo, &StringDado , &CondRetEsperada );
			if(NumLidos != 5){
				return TST_CondRetParm;
			}

			CondRetObtido = GRA_CriarAresta( ValorOrig, ValorDest , vtGrafo[ inxGrafo ] , StringDado  );

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao inserir conteúdo no vértice." );

		} /* fim ativa: Testar GRA Inserir aresta */

				
		/* Testar GRA Excluir vértice */

		else if (strcmp (ComandoTeste, EXCLUIR_VERT_CMD) == 0)
		{
			NumLidos = LER_LerParametros ( "ii" , &inxGrafo , &CondRetEsperada );
			if(NumLidos != 2){

				return TST_CondRetParm;

			}

			CondRetObtido = GRA_ExcluirVerticeCorrente( vtGrafo[ inxGrafo ] );

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao excluir vértice." );

		} /* fim ativa: Testar GRA Excluir vértice */

		
		
		/* Testar GRA Obter valor do vértice corrente */

		else if(strcmp (ComandoTeste, OBTER_VALOR_VERT_CMD) == 0)
		{
			NumLidos = LER_LerParametros ( "isi" , &inxGrafo , &StringDado , &CondRetEsperada );
			if(NumLidos != 3){
				return TST_CondRetParm;
			}
			
			CondRetObtido = GRA_ChecarNomeVerticeCorrente( vtGrafo[inxGrafo] , StringDado );

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao obter valor do vértice corrente." );

		} /* fim ativa: Testar GRA Obter valor do vértice corrente */

		/* Testar GRA Mudar valor do vértice corrente */

		else if(strcmp (ComandoTeste, MUDAR_VALOR_VERT_CMD) == 0)
		{
			NumLidos = LER_LerParametros ( "isi" , &inxGrafo , &StringDado , &CondRetEsperada );
			if(NumLidos != 3){
				return TST_CondRetParm;
			}
			
			CondRetObtido = GRA_MudarNomeVerticeCorrente( vtGrafo[inxGrafo] , StringDado );

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao obter valor do vértice corrente." );

		} /* fim ativa: Testar GRA Mudar valor do vértice corrente */


		/* Testar GRA Inserir vértice no início da lista de origens */

		else if(strcmp (ComandoTeste, INSERE_VERT_ORIG_CMD ) == 0)
		{
			NumLidos = LER_LerParametros ( "ici" , &inxGrafo , &ValorDado , &CondRetEsperada );

			if(NumLidos != 3){
				return TST_CondRetParm;
			}
			
			CondRetObtido = GRA_InsereOrigem(vtGrafo[ inxGrafo ] , ValorDado);

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao inserir vertice na lista de origens" );

		} /* fim ativa: Testar GRA Inserir vértice no início da lista de origens */

		/* Testar GRA Inserir vértice no início da lista de origens */

		else if(strcmp (ComandoTeste, EXCLUIR_ARES_CMD ) == 0)
		{
			NumLidos = LER_LerParametros ( "ccii" , &ValorDado , &ValorDest ,  &inxGrafo , &CondRetEsperada );

			if(NumLidos != 4){
				return TST_CondRetParm;
			}
			
			CondRetObtido = GRA_ExcluirAresta( ValorDado , ValorDest , vtGrafo[ inxGrafo ]);

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao inserir vertice na lista de origens" );

		} /* fim ativa: Testar GRA Inserir vértice no início da lista de origens */

		else if(strcmp (ComandoTeste, DEFINIR_CORR_GRA_CMD ) == 0)
		{

			NumLidos = LER_LerParametros ( "ici" , &inxGrafo , &ValorDado , &CondRetEsperada );

			if(NumLidos != 3){
				return TST_CondRetParm;
			}

			CondRetObtido = GRA_DefinirCorrente( vtGrafo[ inxGrafo ] , ValorDado);

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao inserir vertice na lista de origens" );

		} /* fim ativa: Testar GRA Inserir vértice no início da lista de origens */

		else if(strcmp (ComandoTeste, DESTRUIR_GRA_CMD ) == 0)
		{

			NumLidos = LER_LerParametros ( "ii" , &inxGrafo , &CondRetEsperada );

			if(NumLidos != 2){
				return TST_CondRetParm;
			}

			CondRetObtido = GRA_DestruirGrafo( &vtGrafo[ inxGrafo ]);

			vtGrafo[ inxGrafo ] = NULL;

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao destruir grafo!" );

		} /* fim ativa: Testar GRA Destruir Grafo */


      return TST_CondRetNaoConhec ;

   } /* Fim função: TGRA Efetuar operações de teste específicas para grafo */


/***********************************************************************
*
*  $FC Função: TGRA -Validar indice de grafo
*
***********************************************************************/

   int ValidarInxGrafo( int inxGrafo , int Modo )
   {

      if ( ( inxGrafo <  0 )
		  || ( inxGrafo >= DIM_VT_GRAFO ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtGrafo[ inxGrafo ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtGrafo[ inxGrafo ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim função: TGRA -Validar indice de grafo */

/***********************************************************************
*
*  $FC Função: TES -Excluir conteudo alocado em grafo
*
***********************************************************************/


   void TES_excluirInfo ( void * pValor )
   {

      free( ( void * ) pValor ) ;

   } /* Fim função: TST -Excluir informacao */


/********** Fim do módulo de implementação: Módulo de teste específico **********/

