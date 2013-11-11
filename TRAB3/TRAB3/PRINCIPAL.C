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
#include <Windows.h>

#include "TABULEIRO.H"
#include "JOGO.H"
#include "PECA.H"

#define MAX_NOME 10

#define PRETO 0 
#define AZUL  1 
#define VERDE 2 

/************  Protótipo das funções encapsuladas no módulo  *************/

static void imprimeMenuPrincipal ( void ) ;

static void imprimeMenuEscolhaTime ( void ) ;

static void gravarArquivo( TAB_tppTabuleiro pTabuleiro , JOG_tppJogo pJogo );

static void AbrirArquivo( TAB_tppTabuleiro * pTabuleiro , JOG_tppJogo * pJogo );

static void SetColor(char cor);

char * LimparEspacos(char * input);   

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
	int Diagonal = -1;
	int Reta = -1;
	int QtdeMov = -1;

	/* Disposicao */
	int NumPecas;
	int NumPecasA;
	int NumPecasB;

	/*Xeque Mate */
	char * CasaCausadora = NULL;
	char SairDoXeque;

	TAB_tpCondRet TabRet;
	TAB_tppTabuleiro pTabuleiro;

	JOG_tpCondRet JogRet;
	JOG_tpCondRet JogRetXeque;
	JOG_tppJogo   pJogo;

	JOG_tppPecaJogo pPecaBuscaJogo;

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

				SetColor('a');

				puts ( "*********************************************" ) ;

				TabRet = TAB_ApresentaTabuleiro(pTabuleiro);
			
				puts ( "*********************************************\n" ) ;

				SetColor('w');
			
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

				while(Diagonal != 0 && Diagonal != 1){
					printf("Sua peca anda para DIAGONAL? (1 - Sim | 0 - Nao):");
					scanf ( "%d", &Diagonal ) ;
					if(Diagonal > 1){
						puts("Informacao errada!");
					}
				}

				while(Reta != 0 && Reta != 1){
					printf("Sua peca anda em linha RETA? (1 - Sim | 0 - Nao):");
					scanf ( "%d", &Reta ) ;
					if(Reta > 1){
						puts("Informacao errada!");
					}
				}

				while(QtdeMov < 0 || QtdeMov > 8){
					printf("Qual a quantidade de casas que sua peca anda? ");
					scanf ( "%d", &QtdeMov ) ;
					if(QtdeMov < 0 || QtdeMov > 8){
						puts("Informacao inconsistente!");
					}
				}
				
				TabRet = TAB_CriarTipoPeca(pTabuleiro , NomePeca , Diagonal , Reta , QtdeMov );
				
				Diagonal = Reta = QtdeMov = -1;

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

				Time = 0;
				while(Time != 1 && Time != 2){
					imprimeMenuEscolhaTime();
					scanf ( "%d", &Time ) ;
					if(Time != 1 && Time != 2){
						puts ( "Time invalido!" ) ;
					}
				}

				/* Cria tipo REI */
				TabRet = TAB_CriarTipoPeca(pTabuleiro , "REI" , 1 , 1 , 1 );

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
						if(Time == 1){
							JogRet = JOG_InserirPecaTimeA(pJogo , pPecaBusca);
						}else{
							JogRet = JOG_InserirPecaTimeB(pJogo , pPecaBusca);
						}
						NumPecas--;
					}
				}

				/* Inserir REI no time A */
				TabRet = TAB_ProcuraPeca (pTabuleiro , "REI" , (void**)&pPecaBusca);

				if(Time == 1){
					JogRet = JOG_InserirPecaTimeA(pJogo , pPecaBusca);
					Time = 2;
					puts ( "\n************************ Time BRANCO selecionado ****************************\n" ) ;
				}else{
					JogRet = JOG_InserirPecaTimeB(pJogo , pPecaBusca);
					Time = 1;
					puts ( "\n************************ Time PRETO selecionado ****************************\n" ) ;
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
						if(Time == 1){
							JogRet = JOG_InserirPecaTimeA(pJogo , pPecaBusca);
						}else{
							JogRet = JOG_InserirPecaTimeB(pJogo , pPecaBusca);
						}
						NumPecas--;
					}
				}

				/* Inserir REI no time B */
				TabRet = TAB_ProcuraPeca (pTabuleiro , "REI" , (void**)&pPecaBusca);
				
				if(Time == 1){
					JogRet = JOG_InserirPecaTimeA(pJogo , pPecaBusca);
				}else{
					JogRet = JOG_InserirPecaTimeB(pJogo , pPecaBusca);
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

					/** Colocar a peca na casa do tabuleiro **/

					JOG_ObterPecaJogo(pJogo , 'A' , (void**)&pPecaBuscaJogo);

					TAB_SetarCorrente(pTabuleiro , NomePosicao);

					TAB_InserirConteudoCasa(pTabuleiro , pPecaBuscaJogo );

					/** Fim do colocar a peca na casa do tabuleiro **/

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

					/** Colocar a peca na casa do tabuleiro **/

					JOG_ObterPecaJogo(pJogo , 'B' , (void**)&pPecaBuscaJogo);

					TAB_SetarCorrente(pTabuleiro , NomePosicao);

					TAB_InserirConteudoCasa(pTabuleiro , pPecaBuscaJogo );

					/** Fim do colocar a peca na casa do tabuleiro **/

					JOG_AvancarCorrrenteTime(pJogo , 'B' , 1);

					NumPecasB--;
				}

				JOG_PreencheCaminho(pJogo , pTabuleiro );
				
				
				break;

		/* XEQUE MATE */
		case 7: /* Verificar XEQUE MATE. */

			puts ( " Voce escolheu: 7 - Verificar XEQUE MATE." ) ;

			JogRet = JOG_VerificaXequeMate(pJogo, pTabuleiro , &CasaCausadora);


			if(JogRet == JOG_CondRetXequeMateS){
				SetColor('v');
				puts ("*********************************");
				puts ("Esta em Xeque Mate               ");
				puts ("                                 ");
				puts ("*********************************");
				SetColor('w');

				printf("Deseja tentar sair do XEQUE ? (S - Sim | N - Nao)");
				scanf ( "%s", &SairDoXeque ) ;
				
				if(SairDoXeque == 'S' || SairDoXeque == 's'){
					
					JogRetXeque = JOG_VerificaSairXequeMate(pJogo  , pTabuleiro , CasaCausadora);

					if(JogRetXeque == JOG_CondRetXequeMateN){
						SetColor('v');
						puts ("Continua em XEQUE MATE!               ");
						SetColor('w');
					}else{
						SetColor('e');
						puts ("E possivel sair do XEQUE MATE!              ");
						SetColor('w');
					}

				}

			}else{
				SetColor('e');
				puts ("*********************************");
				puts ("Nao esta em Xeque Mate           ");
				puts ("                                 ");
				puts ("*********************************");
				SetColor('w');
			}

			break;

		/* Salvar partida */
		case 8: /* Salvar atual configuração do jogo. */

			puts ( " Voce escolheu: 8 - Salvar JOGO." ) ;

			gravarArquivo(pTabuleiro , pJogo);
			
			break;

		/* Abrir partida */
		case 9: /* Abre configuração salva do Jogo. */

			puts ( " Voce escolheu: 9 - Abrir JOGO." ) ;

			AbrirArquivo(&pTabuleiro , &pJogo);
			
			break;

<<<<<<< HEAD
		/* Fechar programa */
		case 10: /* Sair do programa. */
			exit(1);

		/* Modificar peca */
		case 11: /* Modificar configuracao da peca */

			pPecaBusca = NULL;

			printf( "Informe o nome da peca : " );
			scanf ( "%s", &NomePeca ) ;

			TAB_ProcuraPeca (pTabuleiro , NomePeca , (void**)&pPecaBusca);
			

			while(Diagonal != 0 && Diagonal != 1){
				printf("Sua peca anda para DIAGONAL? (1 - Sim | 0 - Nao):");
				scanf ( "%d", &Diagonal ) ;
				if(Diagonal > 1){
					puts("Informacao errada!");
				}
			}

			while(Reta != 0 && Reta != 1){
				printf("Sua peca anda em linha RETA? (1 - Sim | 0 - Nao):");
				scanf ( "%d", &Reta ) ;
				if(Reta > 1){
					puts("Informacao errada!");
				}
			}

			while(QtdeMov < 0 || QtdeMov > 8){
				printf("Qual a quantidade de casas que sua peca anda? ");
				scanf ( "%d", &QtdeMov ) ;
				if(QtdeMov < 0 || QtdeMov > 8){
					puts("Informacao inconsistente!");
				}
			}

			PecaRet = PEC_ModificarPeca(pPecaBusca , Diagonal , Reta , QtdeMov );

			if(PecaRet == PEC_CondRetOK){
				puts("Peca atualizada com sucesso!");
			}

			Diagonal = Reta = QtdeMov = -1;

			strcpy(NomePeca , "");

			JOG_PreencheCaminho(pJogo , pTabuleiro );

			/* Usu�rio com caracter n�o esperado */
=======
		/* Fecha aṕlicacao */
		case 10:
			exit(1);

			/* Usuário com caracter não esperado */
>>>>>>> 794a489874c8b02e3c382daa3bc77ca2c64861ad
		default: puts ( "Favor entre com uma das opcoes abaixo." ) ; 
				 break ;

		} /* switch */

	} /* while */
	
	return 0;
}


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: PRI  - Imprimir menu principal
*
*  $ED Descrição da função
*     Imprime o menu principal para a aplicação.
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
	puts ( "* 7- Verificar XequeMate.                                         *" ) ;
	puts ( "* 8- Armazenar partida.                                           *" ) ;
	puts ( "* 9- Abrir partida salva.                                         *" ) ;
	puts ( "* 10- Fechar aplicacao.                                           *" ) ;
	puts ( "*                                                                 *" ) ;
	puts ( "**********             FUNCOES AUXILIARES               ***********" ) ;
	puts ( "* 11- Configurar Peca.                                            *" ) ;
	puts ( "*******************************************************************" ) ;

}


/***********************************************************************
*
*  $FC Função: PRI  - Imprimi menu de escolha de time
*
*  $ED Descrição da função
*     Imprime o menu principal para a aplicação.
*
***********************************************************************/

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


/***********************************************************************
*
*  $FC Função: PRI  -Apresenta tipo de peça
*
*  $ED Descrição da função
*     Imprime o menu de apresentacao de peça.
*
***********************************************************************/
static void apresentaTipoPeca( void )
{

	puts ( "*******************************************************************" ) ;
	puts ( "*  Escolha o tipo de peca:                                        *" ) ;
	puts ( "*******************************************************************" ) ;

}


/***********************************************************************
*
*  $FC Função: PRI  - Salvar tabuleiro em arquivo texto
*
*  $ED Descrição da função
*     Cria um arquivo de texto com as configurações do tabuleiro.
*
***********************************************************************/
static void gravarArquivo( TAB_tppTabuleiro pTabuleiro , JOG_tppJogo pJogo )
{
	
	FILE *fp;
	char TipoPeca[250];
	TAB_tpCondRet TabRetorno;
	PEC_tppPeca pTipoPecaFile ;
	TAB_tpCondRet TabRet;
	JOG_tppPecaJogo pPecaJ;
	
	/* Detalhes da peca */
	char  NomePecaFile[MAX_NOME];
	int Diag;
	int Reta;
	int Qtde;
	char ToInt[MAX_NOME];

	char NomeNaCasa[MAX_NOME];
	char Time;
	char * Id = NULL;

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
			sprintf(ToInt, "%d", Diag);
			strcat (TipoPeca, ToInt);

			strcat (TipoPeca, " ");			
			sprintf(ToInt, "%d", Reta);
			strcat (TipoPeca, ToInt);

			strcat (TipoPeca, " ");			
			sprintf(ToInt, "%d", Qtde);
			strcat (TipoPeca, ToInt);

			fputs(TipoPeca, fp);
			fputs("\n", fp);

			strcpy(NomePecaFile , "");
			Diag = Reta = Qtde = 0;

			TabRetorno = TAB_AvancarTipoPeca(pTabuleiro , 1);


		}while (TabRetorno != TAB_CondRetFimLista);
	}

	/* Grava as pecas dos times */
	/* Time A */
	TabRet = TAB_IrInicioCasas(pTabuleiro);

	do{
		TAB_ObterConteudo(pTabuleiro , (void**)&pPecaJ);

		if(pPecaJ != NULL){
			TAB_ObterVerticeCorrente(pTabuleiro , (char**)&Id);

			JOG_ObterDadosPeca(pPecaJ , (void**)&NomeNaCasa , &Time);
			if(Time == 'A'){
				strcpy (TipoPeca, "PECAS A ");
				strcat (TipoPeca,  (char *)&NomeNaCasa);
				strcat (TipoPeca,  " ");
				strcat (TipoPeca,  Id);
				fputs(TipoPeca, fp);
				fputs("\n", fp);
			}
		}
		TabRet = TAB_AvancarCasas(pTabuleiro , 1);

	}while(TabRet != TAB_CondRetFimLista);

	/* Time B */
	TabRet = TAB_IrInicioCasas(pTabuleiro);

	do{
		TAB_ObterConteudo(pTabuleiro , (void**)&pPecaJ);

		if(pPecaJ != NULL){
			TAB_ObterVerticeCorrente(pTabuleiro , (char**)&Id);

			JOG_ObterDadosPeca(pPecaJ , (void**)&NomeNaCasa , &Time);
			if(Time == 'B'){
				strcpy (TipoPeca, "PECAS B ");
				strcat (TipoPeca,  (char *)&NomeNaCasa);
				strcat (TipoPeca,  " ");
				strcat (TipoPeca,  Id);
				fputs(TipoPeca, fp);
				fputs("\n", fp);
			}
		}
		TabRet = TAB_AvancarCasas(pTabuleiro , 1);

	}while(TabRet != TAB_CondRetFimLista);

    printf ("Jogo salvo com sucesso.\n");
    fclose (fp);
}



/***********************************************************************
*
*  $FC Função: PRI  - Abrir tabuleiro salvo em arquivo texto
*
*  $ED Descrição da função
*     Abre o arquivo de texto salvo com as configurações do tabuleiro.
*
***********************************************************************/
static void AbrirArquivo( TAB_tppTabuleiro * pTabuleiro , JOG_tppJogo * pJogo )
{
	FILE *fp;
	TAB_tpCondRet TabRet;
	char Linha[256];
	int LinhaArq = 0;
	char * Tipo;
	int ContadorLinha = 0;
	char TipoParam[MAX_NOME];

	/*Sobre tipo peca */
	char NomePeca[MAX_NOME];
	int  Diag;
	int  Reta;
	int  Qtde;

	/* Sobre pecas */
	char Time;
	char NomePecaP[MAX_NOME];
	char Posicao[2];
	PEC_tppPeca pPecaBusca;
	JOG_tppPecaJogo pPecaBuscaJogo;

	TabRet = TAB_CriarTabuleiro(pTabuleiro);
	if(TabRet == TAB_CondRetFaltouMemoria){
		printf("Impossivel criar Tabuleiro!");
		exit;
	}

	JOG_CriarJogo(pJogo);

	fp = fopen ("Jogo.txt", "r");	

    while (!feof(fp)){
		fgets(Linha, sizeof(Linha), fp);
		if(LinhaArq != 0 && LinhaArq != 1){
			Tipo = strtok(Linha, " ");
			while(Tipo!=NULL){
				if(ContadorLinha == 0){
					printf("TIPO %s" , Tipo);
					if(strcmp(Tipo , "TIPOPECA")==0){
						strcpy(TipoParam , Tipo); 
					}else if(strcmp(Tipo , "PECAS")==0){
						strcpy(TipoParam , Tipo);
					}
				}else{
					if(strcmp(TipoParam , "TIPOPECA")==0){
						if(ContadorLinha == 1){
							strcpy(NomePeca , Tipo);
						}
						if(ContadorLinha == 2){
							Diag = atoi(Tipo);
						}
						if(ContadorLinha == 3){
							Reta = atoi(Tipo);
						}
						if(ContadorLinha == 4){
							Qtde = atoi(Tipo);
						}
						
					}
					else if(strcmp(TipoParam , "PECAS")==0){
						
						if(ContadorLinha == 1){
							Time = Tipo[0];
						}
						if(ContadorLinha == 2){
							strcpy(NomePecaP , Tipo);
						}
						if(ContadorLinha == 3){
							strcpy(Posicao , Tipo);
						}
					}
				}
				Tipo = strtok(NULL, " ");
				ContadorLinha++;
			}

			if(strcmp(TipoParam , "TIPOPECA")==0 && ContadorLinha == 5){
				printf("Diag %d " , Diag);
				TabRet = TAB_CriarTipoPeca(*pTabuleiro , NomePeca , Diag , Reta , Qtde );
			}
			if(strcmp(TipoParam , "PECAS")==0 && ContadorLinha == 4){
								
				TabRet = TAB_ProcuraPeca(*pTabuleiro , NomePecaP , (void**)&pPecaBusca);

				if(Time == 'A'){
							JOG_InserirPecaTimeA(*pJogo , pPecaBusca);

							JOG_ObterPecaJogo(*pJogo , 'A' , (void**)&pPecaBuscaJogo);

							TAB_SetarCorrente(*pTabuleiro , LimparEspacos(Posicao));

							TAB_InserirConteudoCasa(*pTabuleiro , pPecaBuscaJogo );

				}
				if(Time == 'B'){
							JOG_InserirPecaTimeB(*pJogo , pPecaBusca);

							JOG_ObterPecaJogo(*pJogo , 'B' , (void**)&pPecaBuscaJogo);

							TAB_SetarCorrente(*pTabuleiro , LimparEspacos(Posicao));

							TAB_InserirConteudoCasa(*pTabuleiro , pPecaBuscaJogo );
				}

			}
			ContadorLinha=0;
		}		
		LinhaArq++;   
		
    }

    JOG_PreencheCaminho(*pJogo , *pTabuleiro );


	fclose (fp);
}


/***********************************************************************
*
*  $FC Função: PRI  - Seta cor
*
*  $ED Descrição da função
*     Define uma cor para o tabuleiro a ser mostrado ao usuario.
*
***********************************************************************/

static void SetColor(char cor)
{
	int newColor;
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	switch(cor)
	{
	case 'a':	
		newColor = (3 * 16) + 15;
		break;

	case 'v': 	
		newColor = (12 * 16) + 15;
		break;

	case 'c':	
		newColor = (7 * 16) + 0;
		break;

	case 'w':	
		newColor = (0 * 16) + 7;
		break;

	case 'e':	
		newColor = (14 * 16) + 0;
		break;
	}
	SetConsoleTextAttribute(consoleHandle, newColor);
	
}/* Fim da função: static void SetColor(char cor) */ 

char * LimparEspacos(char * input)                                         
{
	int i , j;
    char * output=input;
    for (i = 0, j = 0; i<strlen(input); i++,j++)          
    {
        if (input[i]!='\n' && input[i]!=' ')                           
            output[j]=input[i];                     
		else
            j--;                                     
    }
    output[j]=0;
    return output;
}