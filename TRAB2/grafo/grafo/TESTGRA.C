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
static const char INSERE_ANT_VERT_CMD		[ ] = "=insereantvertive"     ;
static const char INSERE_SUC_VERT_CMD		[ ] = "=inseresucvertive"     ;
static const char INSERE_CONT_VERT_CMD		[ ] = "=inserecontvertive"    ;
static const char INSERE_VERT_FINAL_CMD		[ ] = "=inserevertivefinal"   ;
static const char INSERE_VERT_INIC_CMD		[ ] = "=inserevertiveinic"    ;
static const char INSERIR_VERT_SUC_VERT_CMD	[ ] = "=inserevertivesucvert" ;
static const char INSERIR_VERT_ANT_VERT_CMD	[ ] = "=inserevertiveantvert" ;
static const char EXCLUIR_VERT_CMD   		[ ] = "=excluirvertice"       ;
static const char EXCLUIR_ANT_VERT_CMD		[ ] = "=excluirantvertive"    ;
static const char EXCLUIR_SUC_VERT_CMD		[ ] = "=excluirsucvertive"    ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_GRAFO       10
#define DIM_VT_VERTICES    100
#define DIM_VALOR          100

GRA_tppGrafo    vtGrafo[ DIM_VT_GRAFO ] ;

GRA_tppVerGrafo  vtVertice[ DIM_VT_VERTICES ] ;


/***** Protótipos das funções encapuladas no módulo *****/

static int ValidarInxGrafo( int inxGrafo , int Modo ) ;

static int ValidarInxVertices( int inxVertices , int Modo ) ;

/*****  Código das funções exportadas pelo módulo  *****/


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
      char ValorDado ;
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

			CondRetObtido = GRA_CriarGrafo( &vtGrafo[ inxGrafo ] ) ;


            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar grafo." );

         } /* fim ativa: Testar GRA Criar grafo */		


		/* Testar GRA Criar vertice para grafo */

		else if( strcmp( ComandoTeste , CRIAR_VERTIVE_GRAFO_CMD ) == 0 )
		{

			NumLidos = LER_LerParametros ( "isci" , &inxVertices , &StringDado , &ValorDado , &CondRetEsperada );

			if ( NumLidos != 4 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = GRA_CriaVerticeGrafo( &vtVertice[ inxVertices ] , StringDado , ValorDado );

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar vertice no grafo." );


		} /* fim ativa: Testar GRA Criar vertice para grafo */

		/* Testar GRA Inserir lista de antecessores no vértice  */

		else if(strcmp (ComandoTeste, INSERE_ANT_VERT_CMD) == 0)
		{

			NumLidos = LER_LerParametros ( "ii" , &inxVertices , &CondRetEsperada );

			if(NumLidos != 2){
				return TST_CondRetParm;
			}
			
			CondRetObtido = GRA_InsereAntecessoresVertice( vtVertice[ inxVertices ] );

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao inserir lista de antecessores no vertice." );

		} /* fim ativa: Testar GRA Inserir lista de antecessores no vértice */

		/* Testar GRA Inserir lista de sucessores no vértice */

		else if(strcmp (ComandoTeste, INSERE_SUC_VERT_CMD) == 0)
		{
			NumLidos = LER_LerParametros ( "ii"  , &inxVertices , &CondRetEsperada );
			if(NumLidos != 2){
				return TST_CondRetParm;
			}
			
			CondRetObtido = GRA_InsereSucessoresVertice( vtVertice[ inxVertices ]  );

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao inserir lista de sucessores no vertice." );

		} /* fim ativa: Testar GRA Inserir lista de sucessores no vértice */

		/* Testar GRA Inserir conteúdo no vértice */

		else if(strcmp ( ComandoTeste, INSERE_CONT_VERT_CMD ) == 0)
		{
			NumLidos = LER_LerParametros ( "isi" , &inxVertices, &StringDado , &CondRetEsperada );
			if(NumLidos != 3){
				return TST_CondRetParm;
			}
			
			CondRetObtido = GRA_InsereConteudoVertice( vtVertice[ inxVertices ] , StringDado  );

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao inserir conteúdo no vértice." );

		} /* fim ativa: Testar GRA Inserir conteúdo no vértice */

		
		/* Testar GRA Inserir vértice no final da lista de vértices */

		else if(strcmp (ComandoTeste, INSERE_VERT_FINAL_CMD ) == 0)
		{
			NumLidos = LER_LerParametros ( "iii" , &inxGrafo , &inxVertices , &CondRetEsperada );
			if(NumLidos != 3){
				return TST_CondRetParm;
			}
			
			CondRetObtido = GRA_InsereVerticeFinal(vtGrafo[ inxGrafo ] , vtVertice[ inxVertices ]);

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao inserir vertice no final da lista de vertices" );

		} /* fim ativa: Testar GRA Inserir vértice no final da lista de vértices */
		
		
		/* Testar GRA Inserir vértice no início da lista de vértices */

		else if(strcmp (ComandoTeste, INSERE_VERT_INIC_CMD ) == 0)
		{
			NumLidos = LER_LerParametros ( "iii" , &inxGrafo , &inxVertices , &CondRetEsperada );
			if(NumLidos != 3){
				return TST_CondRetParm;
			}
			
			CondRetObtido = GRA_InsereVerticeInicio(vtGrafo[ inxGrafo ] , vtVertice[ inxVertices ]);

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao inserir vertice no final da lista de vertices" );

		} /* fim ativa: Testar GRA Inserir vértice no início da lista de vértices */
		
		/* Testar GRA Inserir sucessores na lista de sucessores no vértice */

		else if (strcmp (ComandoTeste, INSERIR_VERT_SUC_VERT_CMD) == 0)
		{
			NumLidos = LER_LerParametros ( "iii" , &inxVerticesOr, &inxVertices , &CondRetEsperada );
			if(NumLidos != 3){
				return TST_CondRetParm;
			}
			
			CondRetObtido = GRA_InsereVerticeemSucessores( vtVertice[inxVerticesOr] , vtVertice[inxVertices] );

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao inserir sucessores na lista de sucessores no vértice." );

		} /* fim ativa: Testar GRA Inserir sucessores na lista de sucessores no vértice */


		/* Testar GRA Inserir sucessores na lista de sucessores no vértice */

		else if (strcmp (ComandoTeste, INSERIR_VERT_ANT_VERT_CMD) == 0)
		{
			NumLidos = LER_LerParametros ( "iii" , &inxVerticesOr, &inxVertices , &CondRetEsperada );
			if(NumLidos != 3){
				return TST_CondRetParm;
			}
			
			CondRetObtido = GRA_InsereVerticeemAntecessores( vtVertice[inxVerticesOr] , vtVertice[inxVertices] );

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao inserir sucessores na lista de sucessores no vértice." );

		} /* fim ativa: Testar GRA Inserir sucessores na lista de sucessores no vértice */

		
		/* Testar GRA Excluir vértice */

		else if (strcmp (ComandoTeste, EXCLUIR_VERT_CMD) == 0)
		{
			NumLidos = LER_LerParametros ( "iii" , &inxGrafo, &inxVertices , &CondRetEsperada );
			if(NumLidos != 3){
				return TST_CondRetParm;
			}

			CondRetObtido = GRA_ExcluirVertice( vtGrafo[ inxGrafo ] , vtVertice[inxVertices] );

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao excluir vértice." );

		} /* fim ativa: Testar GRA Excluir vértice */

		/* Testar GRA Excluir aresta de antecessores */

		else if(strcmp (ComandoTeste, EXCLUIR_ANT_VERT_CMD) == 0)
		{
			NumLidos = LER_LerParametros ( "ii" , &inxVertices, &CondRetEsperada );
			if(NumLidos != 2){
				return TST_CondRetParm;
			}
			
			CondRetObtido = GRA_ExcluirAntecessoresVertice( vtVertice[inxVertices] );

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para oeste do nó corrente." );

		} /* fim ativa: Testar GRA Excluir aresta de antecessores */
		
		
		
		/* Testar GRA Excluir aresta de sucessores */

		else if(strcmp (ComandoTeste, EXCLUIR_SUC_VERT_CMD) == 0)
		{
			NumLidos = LER_LerParametros ( "ii" , &inxVertices, &CondRetEsperada );
			if(NumLidos != 2){
				return TST_CondRetParm;
			}
			
			CondRetObtido = GRA_ExcluirSucessoresVertice( vtVertice[inxVertices] );

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para oeste do nó corrente." );

		} /* fim ativa: Testar GRA Excluir aresta de sucessores */
		
		


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
*  $FC Função: TGRA - Validar indice de vertice
*
***********************************************************************/

	 int ValidarInxVertices( int inxVertices , int Modo ) 
	 {

	  if ( ( inxVertices <  0 )
		  || ( inxVertices >= DIM_VT_VERTICES ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
		  if ( vtVertice[ inxVertices ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtVertice[ inxVertices ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

	 }
	/* Fim função: TGRA - Validar indice do vertice */


/********** Fim do módulo de implementação: Módulo de teste específico **********/

