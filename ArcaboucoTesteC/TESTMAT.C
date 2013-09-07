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

#include    "LISTA.H"

static const char CRIAR_MATRIZ_CMD			[ ] = "=criarmatriz"     ;
static const char CRIAR_LISTA_CMD			[ ] = "=criarlista"     ;
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
#define DIM_VT_LISTA    10
#define DIM_VALOR       100

MAT_tppMatriz  vtMatrizes[ DIM_VT_MATRIZ ] ;

LIS_tppLista   vtListas[ DIM_VT_LISTA ] ;


/***** Protótipos das funções encapuladas no módulo *****/

static void DestruirLista( void * pLista ) ;

static int ValidarInxMatriz( int inxMatriz , int Modo ) ;

static int ValidarInxLista( int inxLista , int Modo ) ;

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
	  LIS_tpCondRet CondRetLista    = LIS_CondRetOK ;
      MAT_tpCondRet CondRetEsperada = MAT_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      char ValorEsperado = '?'  ;
      char ValorObtido   = '!'  ;
      char ValorDado     = '\0' ;

	  int inxMatriz  = -1 ,
		  inxLista  = -1 ,
          NumLidos   = -1 ,
		  NumElementos   = 0 ,
          CondRetEsp = -1  ;

		/* Testar MAT Criar matriz */

		if ( strcmp( ComandoTeste , CRIAR_MATRIZ_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "iii" ,
                               &inxMatriz , &NumElementos , &CondRetEsperada ) ;

            if ( (NumLidos != 3) || ( ! ValidarInxMatriz(inxMatriz, VAZIO) ) )
            {
               return TST_CondRetParm ;
            } /* if */
			
			CondRetObtido = MAT_CriarMatriz( vtMatrizes[ inxMatriz ] , NumElementos ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar matriz." );

         } /* fim ativa: Testar MAT Criar matriz */

		/* Testar MAT Criar lista */

		if ( strcmp( ComandoTeste , CRIAR_LISTA_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                               &inxLista , &CondRetEsperada ) ;
            if ( (NumLidos != 2) || ( ! ValidarInxLista(inxLista, VAZIO) ) )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetLista = LIS_CriarLista( DestruirLista , vtListas[ inxLista ] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar lista." );

         } /* fim ativa: Testar MAT Criar lista */


		/* Testar MAT Inserir Lista na Matriz */

		if( strcmp( ComandoTeste , INSERIR_LISTA_MATRIZ_CMD ) == 0 )
		{

			NumLidos = LER_LerParametros ( "iii" ,&inxLista, &inxMatriz, &CondRetEsperada );
			if ( (NumLidos != 3) )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = MAT_InsereListaMatriz( &vtListas[ inxLista ] ,  &vtMatrizes[ inxMatriz ] );

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar lista." );


		} /* fim ativa: Testar MAT Inserir Lista na Matriz */

		/* Testar MAT Ir norte do no corrente */

		if(strcmp (ComandoTeste, IR_NORTE_CMD) == 0)
		{
			NumLidos = LER_LerParametros ( "ii" , &inxMatriz, &CondRetEsperada );
			if(NumLidos != 2){
				return TST_CondRetParm;
			}
			
			CondRetObtido = MAT_IrNoNorte( &vtMatrizes[ inxMatriz ]);

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para norte do nó corrente." );

		} /* fim ativa: Testar MAT Ir norte do no corrente */

		/* Testar MAT Ir nordeste do no corrente */

		if(strcmp (ComandoTeste, IR_NORDESTE_CMD) == 0)
		{
			NumLidos = LER_LerParametros ( "ii" , &inxMatriz, &CondRetEsperada );
			if(NumLidos != 2){
				return TST_CondRetParm;
			}
			
			CondRetObtido = MAT_IrNoNordeste( &vtMatrizes[ inxMatriz ]);

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para nordeste do nó corrente." );

		} /* fim ativa: Testar MAT Ir nordeste do no corrente */

		/* Testar MAT Ir leste do no corrente */

		if(strcmp (ComandoTeste, IR_LESTE_CMD) == 0)
		{
			NumLidos = LER_LerParametros ( "ii" , &inxMatriz, &CondRetEsperada );
			if(NumLidos != 2){
				return TST_CondRetParm;
			}
			
			CondRetObtido = MAT_IrNoLeste( &vtMatrizes[ inxMatriz ]);

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para leste do nó corrente." );

		} /* fim ativa: Testar MAT Ir leste do no corrente */

		
		/* Testar MAT Ir sudeste do no corrente */

		if(strcmp (ComandoTeste, IR_SUDESTE_CMD) == 0)
		{
			NumLidos = LER_LerParametros ( "ii" , &inxMatriz, &CondRetEsperada );
			if(NumLidos != 2){
				return TST_CondRetParm;
			}
			
			CondRetObtido = MAT_IrNoSudeste( &vtMatrizes[ inxMatriz ]);

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para sudeste do nó corrente." );

		} /* fim ativa: Testar MAT Ir sudeste do no corrente */
		
		
		/* Testar MAT Ir sul do no corrente */

		if(strcmp (ComandoTeste, IR_SUL_CMD) == 0)
		{
			NumLidos = LER_LerParametros ( "ii" , &inxMatriz, &CondRetEsperada );
			if(NumLidos != 2){
				return TST_CondRetParm;
			}
			
			CondRetObtido = MAT_IrNoSul( &vtMatrizes[ inxMatriz ]);

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para sul do nó corrente." );

		} /* fim ativa: Testar MAT Ir sul do no corrente */
		
		
		/* Testar MAT Ir sudoeste do no corrente */

		if(strcmp (ComandoTeste, IR_SUDOESTE_CMD) == 0)
		{
			NumLidos = LER_LerParametros ( "ii" , &inxMatriz, &CondRetEsperada );
			if(NumLidos != 2){
				return TST_CondRetParm;
			}
			
			CondRetObtido = MAT_IrNoSudoeste( &vtMatrizes[ inxMatriz ]);

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para sudoeste do nó corrente." );

		} /* fim ativa: Testar MAT Ir sudoeste do no corrente */

		/* Testar MAT Ir oeste do no corrente */

		if(strcmp (ComandoTeste, IR_OESTE_CMD) == 0)
		{
			NumLidos = LER_LerParametros ( "ii" , &inxMatriz, &CondRetEsperada );
			if(NumLidos != 2){
				return TST_CondRetParm;
			}
			
			CondRetObtido = MAT_IrNoOeste( &vtMatrizes[ inxMatriz ]);

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para oeste do nó corrente." );

		} /* fim ativa: Testar MAT Ir oeste do no corrente */
		
		
		
		/* Testar MAT Ir noroeste do no corrente */

		if(strcmp (ComandoTeste, IR_NOROESTE_CMD) == 0)
		{
			NumLidos = LER_LerParametros ( "ii" , &inxMatriz, &CondRetEsperada );
			if(NumLidos != 2){
				return TST_CondRetParm;
			}
			
			CondRetObtido = MAT_IrNoNoroeste( &vtMatrizes[ inxMatriz ]);

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para noroeste do nó corrente." );

		} /* fim ativa: Testar MAT Ir noroeste do no corrente */
		
		
		/* Testar MAT Obter lista do nó corrente */

		if(strcmp (ComandoTeste, OBTER_LISTA_CORR_CMD) == 0)
		{
			NumLidos = LER_LerParametros ( "iii" , &inxLista, &inxMatriz, &CondRetEsperada );
			if(NumLidos != 3){
				return TST_CondRetParm;
			}
			
			CondRetObtido = MAT_ObterListaCorr( &vtListas[ inxLista ] , &vtMatrizes[ inxMatriz ]);

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao obter lista corrente." );

		} /* fim ativa: Testar MAT Obter lista do nó corrente */
		
		
		/* Testar MAT Ir para o início/raiz da matriz */

		if(strcmp (ComandoTeste, IR_INICIO_CMD) == 0)
		{
			NumLidos = LER_LerParametros ( "ii" , &inxMatriz, &CondRetEsperada );
			if(NumLidos != 2){
				return TST_CondRetParm;
			}
			
			CondRetObtido = MAT_IrRaiz( &vtMatrizes[ inxMatriz ]);

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

   int ValidarInxMatriz( int inxMatriz , int Modo )
   {

      if ( ( inxMatriz <  0 )
		  || ( inxMatriz >= DIM_VT_MATRIZ ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtMatrizes[ inxMatriz ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtMatrizes[ inxMatriz ] == 0 )
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
*  $FC Função: TLIS -Destruir valor
*
***********************************************************************/

   void DestruirLista( void * pLista )
   {

      free( pLista ) ;

   } /* Fim função: TLIS -Destruir valor */

/********** Fim do módulo de implementação: Módulo de teste específico **********/

