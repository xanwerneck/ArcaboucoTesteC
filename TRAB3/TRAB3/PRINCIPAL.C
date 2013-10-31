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

static void imprimeMenuEscolhaTime ( void ) ;

/************* Função responsável pela execução da aplicação ***************/

int main (void)
{
	int contador = 0 ;
	char opcaoEscolhidaModificar ;
	int opcaoEscolhida ;
	int Time;
	
	/* Movimentos */
	char * NomePeca;
	int Diagonal;
	int Reta;
	int QtdeMov;

	TAB_tpCondRet TabRet;
	TAB_tppTabuleiro pTabuleiro;


	while ( 1 ) 
	{
		
		imprimeMenuPrincipal () ;
		scanf ( "%d", &opcaoEscolhida ) ;

		system ( "cls" ) ;
		
		switch ( opcaoEscolhida )
		{
		
		/* Cria tabuleiro */
		case 1:	/* Criando um segundo tabuleiro, o primeiro é destruído. */
				
				puts ( " Voce escolheu: 1- Criar tabuleiro." ) ;

				TabRet = TAB_CriarTabuleiro(&pTabuleiro);
				if(pTabuleiro==NULL){
					puts ( "O tabuleiro nao foi criado!" ) ; 
					break ;
				}

				puts ( "Tabuleiro  criado" ) ;
			
				break;
		/* Apresenta tabuleiro */
		case 2:	/* Mostra visualmente o tabuleiro */
				
				puts ( " Voce escolheu: 2- Apresentar tabuleiro." ) ;

				if(pTabuleiro==NULL){
					puts ( "O tabuleiro precisa ser criado!" ) ; 
					break ;
				}

				TabRet = TAB_ApresentaTabuleiro(pTabuleiro);

				puts ( "Percurso no Tabuleiro" ) ;
			
				break;

		/* Criar peca */
		case 3:	/* Efetua a criacao de peca */
				
				puts ( " Voce escolheu: 3- Criar peca." ) ;

				imprimeMenuEscolhaTime();
				scanf ( "%d", &Time ) ;

				if(pTabuleiro==NULL){
					puts ( "O tabuleiro precisa ser criado!" ) ; 
					break ;
				}
				printf("Informe o nome da peca:");
				scanf ( "%s", &NomePeca ) ;

				printf("Sua peca anda para DIAGONAL? (1 - Sim | 0 - Nao):");
				scanf ( "%d", &Diagonal ) ;
				if(Diagonal > 1){
					puts("Informacao errada!");
				}

				printf("Sua peca anda em linha RETA? (1 - Sim | 0 - Nao):");
				scanf ( "%d", &Reta ) ;
				if(Reta > 1){
					puts("Informacao errada!");
				}

				printf("Qual a quantidade de casas que sua peca anda? ");
				scanf ( "%d", &QtdeMov ) ;
				if(QtdeMov > 7){
					puts("Informacao inconsistente!");
				}

				TabRet = TAB_CriarPeca(pTabuleiro , NomePeca , Diagonal , Reta , QtdeMov , Time );

				printf ( "Peca criada para time %d \n" , Time ) ;
			
				break;

		/* Apresenta pecas */
		case 4:	/* Mostra visualmente as pecas */
				
				puts ( " Voce escolheu: 4 - Apresentar pecas." ) ;

				if(pTabuleiro==NULL){
					puts ( "O tabuleiro precisa ser criado!" ) ; 
					break ;
				}

				TabRet = TAB_ApresentaPecas(pTabuleiro);
				if(TabRet == TAB_CondRetOK){
					puts ( "Pecas do Tabuleiro" ) ;
				}else if(TabRet == TAB_TimeAVazio){
					puts ( "Time A vazio" ) ;
				}else{
					puts ( "Time B vazio" ) ;
				} /* if */
			
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
	puts ( "* 3- Criar Peca.                                                  *" ) ;
	puts ( "* 7- Salvar tabuleiro.  		                                  *" ) ;
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

