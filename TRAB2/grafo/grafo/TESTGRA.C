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
static const char CRIAR_GRAFO_CMD			[ ] = "=criargrafo"         ;
static const char CRIAR_VERTIVE_GRAFO_CMD	[ ] = "=criarverticegrafo"  ;
static const char INSERE_ANT_VERT_CMD		[ ] = "=insereantvertive"   ;
static const char INSERE_SUC_VERT_CMD		[ ] = "=inseresucvertive"   ;
static const char INSERE_CONT_VERT_CMD		[ ] = "=inserecontvertive"  ;
static const char INSERE_VERT_FINAL_CMD		[ ] = "=inserevertivefinal" ;
static const char INSERE_VERT_INIC_CMD		[ ] = "=inserevertiveinic"  ;
static const char EXCLUIR_VERT_CMD   		[ ] = "=excluirvertice"     ;
static const char EXCLUIR_ANT_VERT_CMD		[ ] = "=excluirantvertive"  ;
static const char EXCLUIR_SUC_VERT_CMD		[ ] = "=excluirsucvertive"  ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_GRAFO       10
#define DIM_VT_LISTA       10
#define DIM_VT_CONTEUDO    10
#define DIM_VT_VERTICES    10
#define DIM_VALOR          100

GRA_tppGrafo    vtGrafo[ DIM_VT_GRAFO ] ;

GRA_tppVerGrafo  vtVertice [ DIM_VT_VERTICES ] ;

LIS_tppLista    vtListas[ DIM_VT_LISTA ] ;

VER_tppVertice  vtVerCont[ DIM_VT_CONTEUDO ] ;


/***** Protótipos das funções encapuladas no módulo *****/

static void DestruirLista( void * pLista ) ;

static int ValidarInxGrafo( int inxGrafo , int Modo ) ;

static int ValidarInxLista( int inxLista , int Modo ) ;

static int ValidarInxVertices( int inxVertices , int Modo ) ;

static int ValidarInxContVertices( int inxContVertices , int Modo ) ;

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
	  LIS_tpCondRet CondRetLista    = LIS_CondRetOK ;
      GRA_tpCondRet CondRetEsperada = GRA_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      char ValorEsperado = '?'  ;
      char ValorObtido   = '!'  ;
      char ValorDado     = '\0' ;
	  char CharDado ;

	  int inxGrafo     = -1 ,
		  inxLista     = -1 ,
		  inxVertices  = -1 ,
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

            if ( (NumLidos != 3) || ( ! ValidarInxGrafo(inxGrafo, VAZIO) ) )
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

			NumLidos = LER_LerParametros ( "ici" ,&inxVertices , CharDado , &CondRetEsperada );
			if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */
			
			CondRetObtido = GRA_CriaVerticeGrafo( &vtVertice[ inxVertices ] ,  CharDado );

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar vertice no grafo." );


		} /* fim ativa: Testar GRA Criar vertice para grafo */

		/* Testar MAT Ir norte do no corrente */

		else if(strcmp (ComandoTeste, INSERE_ANT_VERT_CMD) == 0)
		{
			NumLidos = LER_LerParametros ( "iii" , &inxLista , &inxVertices , &CondRetEsperada );

			if(NumLidos != 3){
				return TST_CondRetParm;
			}
			
			CondRetObtido = GRA_InsereAntecessoresVertice( vtVertice[ inxVertices ] , vtGrafo[ inxGrafo ] );

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao inserir lista de antecessores no vertice." );

		} /* fim ativa: Testar MAT Ir norte do no corrente */

		/* Testar MAT Ir nordeste do no corrente */

		if(strcmp (ComandoTeste, IR_NORDESTE_CMD) == 0)
		{
			NumLidos = LER_LerParametros ( "ii" , &inxGrafo, &CondRetEsperada );
			if(NumLidos != 2){
				return TST_CondRetParm;
			}
			
			CondRetObtido = MAT_IrNoNordeste( vtGrafo[ inxGrafo ]);

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para nordeste do nó corrente." );

		} /* fim ativa: Testar MAT Ir nordeste do no corrente */

		/* Testar MAT Ir leste do no corrente */

		if(strcmp (ComandoTeste, IR_LESTE_CMD) == 0)
		{
			NumLidos = LER_LerParametros ( "ii" , &inxGrafo, &CondRetEsperada );
			if(NumLidos != 2){
				return TST_CondRetParm;
			}
			
			CondRetObtido = MAT_IrNoLeste( vtGrafo[ inxGrafo ]);

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para leste do nó corrente." );

		} /* fim ativa: Testar MAT Ir leste do no corrente */

		
		/* Testar MAT Ir sudeste do no corrente */

		if(strcmp (ComandoTeste, IR_SUDESTE_CMD) == 0)
		{
			NumLidos = LER_LerParametros ( "ii" , &inxGrafo, &CondRetEsperada );
			if(NumLidos != 2){
				return TST_CondRetParm;
			}
			
			CondRetObtido = MAT_IrNoSudeste( vtGrafo[ inxGrafo ]);

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para sudeste do nó corrente." );

		} /* fim ativa: Testar MAT Ir sudeste do no corrente */
		
		
		/* Testar MAT Ir sul do no corrente */

		if(strcmp (ComandoTeste, IR_SUL_CMD) == 0)
		{
			NumLidos = LER_LerParametros ( "ii" , &inxGrafo, &CondRetEsperada );
			if(NumLidos != 2){
				return TST_CondRetParm;
			}
			
			CondRetObtido = MAT_IrNoSul( vtGrafo[ inxGrafo ]);

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para sul do nó corrente." );

		} /* fim ativa: Testar MAT Ir sul do no corrente */
		
		
		/* Testar MAT Ir sudoeste do no corrente */

		if(strcmp (ComandoTeste, IR_SUDOESTE_CMD) == 0)
		{
			NumLidos = LER_LerParametros ( "ii" , &inxGrafo, &CondRetEsperada );
			if(NumLidos != 2){
				return TST_CondRetParm;
			}
			
			CondRetObtido = MAT_IrNoSudoeste( vtGrafo[ inxGrafo ]);

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para sudoeste do nó corrente." );

		} /* fim ativa: Testar MAT Ir sudoeste do no corrente */

		/* Testar MAT Ir oeste do no corrente */

		if(strcmp (ComandoTeste, IR_OESTE_CMD) == 0)
		{
			NumLidos = LER_LerParametros ( "ii" , &inxGrafo, &CondRetEsperada );
			if(NumLidos != 2){
				return TST_CondRetParm;
			}
			
			CondRetObtido = MAT_IrNoOeste( vtGrafo[ inxGrafo ]);

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para oeste do nó corrente." );

		} /* fim ativa: Testar MAT Ir oeste do no corrente */
		
		
		
		/* Testar MAT Ir noroeste do no corrente */

		if(strcmp (ComandoTeste, IR_NOROESTE_CMD) == 0)
		{
			NumLidos = LER_LerParametros ( "ii" , &inxGrafo, &CondRetEsperada );
			if(NumLidos != 2){
				return TST_CondRetParm;
			}
			
			CondRetObtido = MAT_IrNoNoroeste( vtGrafo[ inxGrafo ]);

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para noroeste do nó corrente." );

		} /* fim ativa: Testar MAT Ir noroeste do no corrente */
		
		
		/* Testar MAT Obter lista do nó corrente */

		if(strcmp (ComandoTeste, OBTER_LISTA_CORR_CMD) == 0)
		{
			NumLidos = LER_LerParametros ( "iii" , &inxLista, &inxGrafo, &CondRetEsperada );
			if(NumLidos != 3){
				return TST_CondRetParm;
			}
			
			CondRetObtido = MAT_ObterListaCorr( &vtListas[ inxLista ] , vtGrafo[ inxGrafo ]);

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao obter lista corrente." );

		} /* fim ativa: Testar MAT Obter lista do nó corrente */
		
		
		/* Testar MAT Ir para o início/raiz da matriz */

		if(strcmp (ComandoTeste, IR_INICIO_CMD) == 0)
		{
			NumLidos = LER_LerParametros ( "ii" , &inxGrafo, &CondRetEsperada );
			if(NumLidos != 2){
				return TST_CondRetParm;
			}
			
			CondRetObtido = MAT_IrRaiz( vtGrafo[ inxGrafo ] );

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para razi da matriz." );

		} /* fim ativa: Testar MAT Ir para o início/raiz da matriz */


      return TST_CondRetNaoConhec ;

   } /* Fim função: TMAT Efetuar operações de teste específicas para matriz */


/***********************************************************************
*
*  $FC Função: TMAT -Validar indice de matriz
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

   } /* Fim função: TMAT -Validar indice de matriz */

/***********************************************************************
*
*  $FC Função: TMAT -Validar indice de lista
*
***********************************************************************/

   int ValidarInxLista( int inxLista , int Modo )
   {

      if ( ( inxLista <  0 )
		  || ( inxLista >= DIM_VT_LISTA ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtListas[ inxLista ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtListas[ inxLista ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim função: TMAT -Validar indice de lista */
  
/***********************************************************************
*
*  $FC Função: TMAT - Validar indice de conteudo do vertice
*
***********************************************************************/

	 int ValidarInxContVertices( int inxContVertices , int Modo ) 
	 {

	  if ( ( inxContVertices <  0 )
		  || ( inxContVertices >= DIM_VT_CONTEUDO ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
		  if ( vtVerCont[ inxContVertices ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtVerCont[ inxContVertices ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

	 }
	/* Fim função: TMAT - Validar indice de conteudo do vertice */

/***********************************************************************
*
*  $FC Função: TLIS -Destruir valor
*
***********************************************************************/

   void DestruirLista( void * pLista )
   {

      free( pLista ) ;

   } /* Fim função: TLIS -Destruir valor */

/********** Fim do módulo de implementação: Módulo de teste específico **********/

