/***************************************************************************
*  $MCI Módulo de implementação: PRI Principal
*
*  Arquivo gerado:              PRINCIPAL.C
*  Letras identificadoras:      PRI
*
*
*  Projeto: INF 1301 - Verificador de Xeque-mate
*  Gestor:  Flavio Bevilacqua
*  Autores: afv
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     Y       afv   xx/xx/2013  finalização do desenvolvimento do modulo
*     X       afv   xx/xx/2013  continuação do desenvolvimento do modulo
*     1       afv   24/out/2013 início do desenvolvimento do módulo
*
***************************************************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#include "TABULEIRO.H"

/************  Protótipo das funções encapsuladas no módulo  *************/

static void imprimeMenuPrincipal ( void ) ;

/************* Função responsável pela execução da aplicação ***************/

int main (void)
{
	int x, y, contador = 0 ;
	char opcaoEscolhidaModificar ;
	int opcaoEscolhida ;
	char caminhoParaOArquivo [ 201 ] ;
	TAB_tpCondRet TabRet;
	TAB_tppTabuleiro * pTabuleiro;


	char IdVertice[4] = {'A','B','C','D'};

	while ( 1 ) 
	{
		
		imprimeMenuPrincipal () ;
		scanf ( "%d", &opcaoEscolhida ) ;

		system ( "cls" ) ;
		
		switch ( opcaoEscolhida )
		{
		
		/* Cria tabuleiro */
		case 1:	/* Criando um segundo tabuleiro, o primeiro é destruído. */
				
				puts ( " Você escolheu: '1- Criar tabuleiro.'" ) ;

				printf("Teste %c" , IdVertice[0]);

				TabRet = TAB_CriarTabuleiro(pTabuleiro , IdVertice);
			
				system ( "cls" ) ;
				puts ( "Labirinito  criado" ) ;
			
				break;
		case 6:
			exit(0);

			/* Usuário com caracter não esperado */
		default: puts ( "Favor entre com uma das opcoes abaixo." ) ; 
				 break ;

		} /* switch */

	} /* while */
	
	return 0;
}


/*****  Código das funções encapsuladas no módulo  *****/

static void CriarTabuleiro()
{


}

/***********************************************************************
*
*  $FC Função: PRI  - Imprimir Menu
*
*  $ED Descrição da função
*     Imprime o menu para a aplicação.
*
***********************************************************************/

static void imprimeMenuPrincipal ( void ) 
{
	puts ( "*******************************************************************" ) ;
	puts ( "*               AFV - VERIFICADOR DE XEQUE-MATE                   *" ) ;
	puts ( "*-----------------------------------------------------------------*" ) ;
	puts ( "*  Entre com o numero correspondente a opcao desejada:            *" ) ;
	puts ( "*                                                                 *" ) ;
	puts ( "* 1- Criar tabuleiro.                                             *" ) ;
	puts ( "* 2- Modificar tabuleiro.                                         *" ) ;
	puts ( "* 3- Salvar tabuleiro.  		                                  *" ) ;
	puts ( "* 4- Recuperar tabuleiro. 		                                  *" ) ;
	puts ( "* 5- Verificar Xeque-mate.                                        *" ) ;
	puts ( "* 6- Fechar aplicacao.                                            *" ) ;
	puts ( "*                                                                 *" ) ;
	puts ( "*******************************************************************" ) ;

}

static void imprimeMenuEscolhaTime ( void ) 
{
	puts ( "*******************************************************************" ) ;
	puts ( "*  Escolha seu time:                                              *" ) ;
	puts ( "*                                                                 *" ) ;
	puts ( "* 1- Preto.                                                       *" ) ;
	puts ( "* 2- Branco.                                                      *" ) ;
	puts ( "*                                                                 *" ) ;
	puts ( "*******************************************************************" ) ;

}

