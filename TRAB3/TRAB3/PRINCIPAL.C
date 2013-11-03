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
#include "JOGO.H"
#include "PECA.H"

#define MAX_NOME 10

/************  Protótipo das funções encapsuladas no módulo  *************/

static void imprimeMenuPrincipal ( void ) ;

static void imprimeMenuEscolhaTime ( void ) ;

static void gravarArquivo( TAB_tppTabuleiro pTabuleiro , JOG_tppJogo pJogo , PEC_tppPeca pPecaFile );

/************* Função responsável pela execução da aplicação ***************/

int main (void)
{
	int contador = 0 ;
	char opcaoEscolhidaModificar ;
	int opcaoEscolhida ;
	int Time;
	
	/* Movimentos */
	char NomePeca[MAX_NOME];
	char NomePosicao[2];
	char * NomeBusca;
	int Diagonal;
	int Reta;
	int QtdeMov;

	/* Disposicao */
	int NumPecas;
	int NumPecasA;
	int NumPecasB;

	TAB_tpCondRet TabRet;
	TAB_tppTabuleiro pTabuleiro;

	JOG_tpCondRet JogRet;
	JOG_tppJogo   pJogo;

	PEC_tpCondRet PecaRet;
	PEC_tppPeca pPecaBusca;

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
				
				TabRet = TAB_CriarTipoPeca(pTabuleiro , NomePeca , Diagonal , Reta , QtdeMov );
				
				strcpy(NomePeca , "");

				puts ( "Peca criada \n" ) ;
			
				break;

		/* Apresenta pecas */
		case 4:	/* Mostra visualmente as pecas */
				
				puts ( " Voce escolheu: 4 - Apresentar tipo pecas." ) ;

				if(pTabuleiro==NULL){
					puts ( "O tabuleiro precisa ser criado!" ) ; 
					break ;
				}

				TabRet = TAB_ApresentaTipoPecas(pTabuleiro);
				if(TabRet == TAB_CondRetOK){
					puts ( "Pecas do Tabuleiro" ) ;
				} /* if */
			
				break;

		/* Montar time */
		case 5:	/* Montar time com pecas */
				
				puts ( " Voce escolheu: 5 - Montar time." ) ;

				JOG_CriarJogo(&pJogo);

				imprimeMenuEscolhaTime();
				scanf ( "%d", &Time ) ;

				if(pTabuleiro==NULL){
					puts ( "O tabuleiro precisa ser criado!" ) ; 
					break ;
				}

				printf ( "Informe o numero de pecas do time %d : " , Time ) ;
				scanf ("%d" , &NumPecas);

				while(NumPecas > 0){

					printf( "Informe o nome da peca : " );
					scanf ( "%s", &NomePeca ) ;
					
					TabRet = TAB_ProcuraPeca (pTabuleiro , NomePeca , (void**)&pPecaBusca);

					if(TabRet != TAB_CondRetOK){
						puts("Peca nao localizada\n");
					}else{
						JogRet = JOG_InserirPecaTimeA(pJogo , pPecaBusca);
						NumPecas--;
					}
				}

				imprimeMenuEscolhaTime();
				scanf ( "%d", &Time ) ;

				printf ( "Informe o numero de pecas do time %d : " , Time ) ;
				scanf ("%d" , &NumPecas);
				
				while(NumPecas > 0){

					printf( "Informe o nome da peca : " );
					scanf ( "%s", &NomePeca ) ;
					
					TabRet = TAB_ProcuraPeca (pTabuleiro , NomePeca , (void**)&pPecaBusca);

					if(TabRet != TAB_CondRetOK){
						puts("Peca nao localizada\n");
					}else{
						JogRet = JOG_InserirPecaTimeB(pJogo , pPecaBusca);
						NumPecas--;
					}
				}

			
				break;


		/* Dispor pecas */
		case 6:	/* Colocar as pecas nas casas */
				
				puts ( " Voce escolheu: 6 - Dispor pecas." ) ;

				if(pTabuleiro==NULL){
					puts ( "O tabuleiro precisa ser criado!" ) ; 
					break ;
				}

				JOG_NumPecasTime(pJogo , 'A' , &NumPecasA);
				if(NumPecasA==0){
					puts ( "Time A nao possui pecas definidas" ) ; 
					break ;
				}


				JOG_NumPecasTime(pJogo , 'B' , &NumPecasB);
				if(NumPecasB==0){
					puts ( "Time B nao possui pecas definidas" ) ; 
					break ;
				}

				/* Colocacao time A */
				JOG_IrInicioPecas(pJogo , 'A');
				puts("**** Disposicao das pecas do time A: ****\n");
				while (NumPecasA > 0){
					JOG_ObterTipoPeca(pJogo , 'A' , (void**)&pPecaBusca);

					PEC_ObterNome(pPecaBusca , (void**)&NomePeca);

					printf("Indique a posicao da peca %s : " , NomePeca);
					scanf ( "%s", &NomePosicao ) ;

					JOG_AvancarCorrrenteTime(pJogo , 'A' , 1);

					NumPecasA--;
				}

				/* Colocacao time B */
				JOG_IrInicioPecas(pJogo , 'B');
				puts("**** Disposicao das pecas do time B: ****\n");
				while (NumPecasB > 0){
					JOG_ObterTipoPeca(pJogo , 'B' , (void**)&pPecaBusca);

					PEC_ObterNome(pPecaBusca , (void**)&NomePeca);

					printf("Indique a posicao da peca %s : " , NomePeca);
					scanf ( "%s", &NomePosicao ) ;

					JOG_AvancarCorrrenteTime(pJogo , 'B' , 1);

					NumPecasB--;
				}

				
				break;

		/* Salvar partida */
		case 7: /* Salvar atual configuração do jogo. */

			puts ( " Voce escolheu: 7 - Salvar JOGO." ) ;

			gravarArquivo(pTabuleiro , pJogo , pPecaBusca);
			
			break;


		case 10:
			exit(1);

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
	puts ( "* 2- Apresenta tabuleiro.                                         *" ) ;
	puts ( "* 3- Criar tipo Peca.                                             *" ) ;
	puts ( "* 4- Apresenta tipos de peca.                                     *" ) ;
	puts ( "* 5- Montar time.                                                 *" ) ;
	puts ( "* 6- Dispor pecas.                                                *" ) ;
	puts ( "* 7- Armazenar partida.                                           *" ) ;
	puts ( "* 10- Fechar aplicacao.                                           *" ) ;
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

static void apresentaTipoPeca( void )
{

	puts ( "*******************************************************************" ) ;
	puts ( "*  Escolha o tipo de peca:                                        *" ) ;
	puts ( "*******************************************************************" ) ;

}

static void gravarArquivo( TAB_tppTabuleiro pTabuleiro , JOG_tppJogo pJogo , PEC_tppPeca pTipoPecaFile  )
{
	
	FILE *fp;
	char TipoPeca[250];
	TAB_tpCondRet TabRetorno;
	JOG_tpCondRet JogRet;

	
	/* Detalhes da peca */
	char  * NomePecaFile;
	int Diag;
	int Reta;
	int Qtde;

    fp = fopen ("Jogo.txt", "w+");
    if (fp == NULL) {
       printf ("Houve um erro ao abrir o arquivo.\n");
    }

	fputs ("***************** Verificador de XEQUE MATE ***********************\n" , fp);
	fputs ("*****************    AFV - Novembro 2013    ***********************\n" , fp);

	/* Grava os tipos de peca */
	TabRetorno = TAB_IrInicioListaPecas(pTabuleiro);

	if(TabRetorno != TAB_CondRetListaVazia){

		do{

			TAB_ObterTipoPeca(pTabuleiro , (void**)&pTipoPecaFile);

			PEC_ObterDadosTipoPeca(pTipoPecaFile, (void**)&NomePecaFile , &Diag , &Reta , &Qtde);
			
			
			strcpy (TipoPeca, "TIPOPECA ");
			strcat (TipoPeca, (char *)&NomePecaFile);
			strcat (TipoPeca, " ");
			
			strcat (TipoPeca, (char *)&Diag);
			strcat (TipoPeca, " ");
			strcat (TipoPeca, (char *)&Reta);
			strcat (TipoPeca, " ");
			strcat (TipoPeca, (char *)&Qtde);

			fputs(TipoPeca, fp);
			fputs("\n", fp);

			TabRetorno = TAB_AvancarTipoPeca(pTabuleiro , 1);


		}while (TabRetorno != TAB_CondRetFimLista);
	}

	/* Grava as pecas dos times */
	/* Time A */
	JogRet = JOG_IrInicioPecas(pJogo , 'A');

	if(JogRet != JOG_CondRetJogoNulo){

		do{

			JOG_ObterTipoPeca(pJogo , 'A' , (void**)&pTipoPecaFile);

			PEC_ObterNome(pTipoPecaFile , (void**)&NomePecaFile);

			strcpy (TipoPeca, "PECAS A ");
			strcat (TipoPeca,  (char *)&NomePecaFile);
			fputs(TipoPeca, fp);
			fputs("\n", fp);

			JogRet = JOG_AvancarCorrrenteTime(pJogo , 'A' , 1);

		}while (JogRet != JOG_CondRetFimLista);
	}

	/* Time B */
	JogRet = JOG_IrInicioPecas(pJogo , 'B');

	if(JogRet != JOG_CondRetJogoNulo){

		do{

			JOG_ObterTipoPeca(pJogo , 'B' , (void**)&pTipoPecaFile);

			PEC_ObterNome(pTipoPecaFile , (void**)&NomePecaFile);

			strcpy (TipoPeca, "PECAS B ");
			strcat (TipoPeca,  (char *)&NomePecaFile);
			fputs(TipoPeca, fp);
			fputs("\n", fp);

			JogRet = JOG_AvancarCorrrenteTime(pJogo , 'B' , 1);

		}while (JogRet != JOG_CondRetFimLista);
	}

	fputs ("*****************       FIM DO ARQUIVO      ***********************" , fp);
    printf ("Jogo salvo com sucesso.\n");
    fclose (fp);
}
