/***********************************************************************
*
*  $MCD Modulo de definicao: JOG  Jogo do tabuleiro
*
*  Arquivo gerado:              JOGO.C
*  Letras identificadoras:      JOG
*
*  Projeto: INF 1301 - Verificador de Xeque-mate
*  Gestor:  Flavio Bevilacqua
*  Autores: afv:  aw - Alexandre Werneck
*                 fr - Fernanda C Ribeiro
*                 vo - Vinicius de Luiz de Oliveira
*
*  $HA Historico de evolucao:
*     Versao  Autor    Data     Observacoes
*     1       afv   11/nov/2013 inicio do desenvolvimento do modulo
*
***********************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>


#define JOGO_OWN
#include "JOGO.H"
#undef JOGO_OWN

#define MAX_NOME 10

LIS_tpCondRet ListaRet;
LIS_tpCondRet ListaRetAresta;

/***********************************************************************
*
*  $TC Tipo de dados: JOG Descritor das pecas do jogo
*
*
***********************************************************************/

typedef struct JOG_tagListaPeca{

	LIS_tppLista pListaTimeA;
	/* Ponteiro para lista de pecas do time A */

	LIS_tppLista pListaTimeB;
	/* Ponteiro para lista de pecas do time B */

}JOG_tpListaPeca;


/***********************************************************************
*
*  $TC Tipo de dados: JOG Descritor do elemento peca para tabuleiro
*
*
***********************************************************************/

typedef struct JOG_tagPecaJogo {

	char Time;
	/* Identificador do time */

	LIS_tppLista pListaDestino;
	/* Ponteiro para lista de casas possiveis pelo movimento
	   da peca, limitando-se as casas que chegam ate ao Rei */		

	LIS_tppLista pListaCaminho;
	/* Ponteiro para lista de todas as casas possiveis pelo 
	   movimento da peca */

	PEC_tppPeca  pTipoPeca ;
	/* Ponteiro para o tipo da peca */

} JOG_tpPecaJogo ;

/************* Prototipos das funcoes encapsuladas no modulo ***********/

   /* Funcao desaloca da memoria o jogo */
   static void ExcluirJogo( void * pPeca );

   /* Funcao desaloca da memoria peca do jogo */
   static void ExcluirPecaJogo( void * pPeca );

   /* Funcao verificar se existem pecas no caminho da peca fornecida */
   static int VerificaPecasCaminho(JOG_tppJogo pJogo ,TAB_tppTabuleiro pTabuleiro  , char * pPeca , char ** PecaCausadora , char ** CasaCausadora , char Time);

/*************  Codigo das funcoes exportadas pelo modulo  *************/

/************************************************************************
*
*  Funcao: JOG  &Criar jogo
*  ****/

JOG_tpCondRet JOG_CriarJogo(JOG_tppJogo * pJOGO)
{

	JOG_tppJogo mJOGO = NULL;
	
	mJOGO = (JOG_tppJogo) malloc(sizeof(JOG_tpListaPeca));
	if(mJOGO == NULL)
	{
		return JOG_CondRetFaltouMemoria ;
	} /* if */
	
	ListaRet = LIS_CriarLista(ExcluirJogo , &mJOGO->pListaTimeA);
	if(ListaRet == LIS_CondRetFaltouMemoria)
	{
		return JOG_CondRetFaltouMemoria;
	} /* if */
	
	LIS_CriarLista(ExcluirJogo , &mJOGO->pListaTimeB);
	if(ListaRet == LIS_CondRetFaltouMemoria)
	{
		return JOG_CondRetFaltouMemoria;
	} /* if */
	
	(*pJOGO) = (JOG_tpListaPeca *) malloc(sizeof(JOG_tppJogo));
	if(pJOGO == NULL)
	{
		return JOG_CondRetFaltouMemoria ;
	} /* if */
	
	(*pJOGO) = mJOGO;

	return JOG_CondRetOK;
	
} /* Fim funcao: JOG &Criar jogo */


/***************************************************************************
*
*  Funcao: JOG  &Inserir peca no tima A
*  ****/

JOG_tpCondRet JOG_InserirPecaTimeA(JOG_tppJogo pJOGO , PEC_tppPeca pPecaSetar)
{

	JOG_tppPecaJogo mPeca = NULL ;

	mPeca = (JOG_tppPecaJogo) malloc(sizeof(JOG_tpPecaJogo));
	if(mPeca == NULL)
	{
		return JOG_CondRetFaltouMemoria;
	} /* if */

	if(pJOGO == NULL)
	{
		return JOG_CondRetJogoNulo ;
	} /* if */

	if (pPecaSetar == NULL)
	{
		return JOG_CondRetFimLista ;
	} /* if */
	
	mPeca->Time = 'A';
	mPeca->pTipoPeca = pPecaSetar;

	ListaRet = LIS_CriarLista(ExcluirPecaJogo , &mPeca->pListaCaminho);
	if(ListaRet == LIS_CondRetFaltouMemoria)
	{
		return JOG_CondRetFaltouMemoria;
	} /* if */

	ListaRet = LIS_CriarLista(ExcluirPecaJogo , &mPeca->pListaDestino);
	if(ListaRet == LIS_CondRetFaltouMemoria)
	{
		return JOG_CondRetFaltouMemoria;
	} /* if */

	ListaRet = LIS_InserirElementoApos(pJOGO->pListaTimeA , mPeca);
	if(ListaRet == LIS_CondRetFaltouMemoria)
	{
		return JOG_CondRetFaltouMemoria;
	} /* if */

	return JOG_CondRetOK;
	
} /* Fim funcao: JOG &Inserir peca no time A */


/***************************************************************************
*
*  Funcao: JOG  &Inserir peca no time B
*  ****/

JOG_tpCondRet JOG_InserirPecaTimeB(JOG_tppJogo pJOGO , PEC_tppPeca pPecaSetar)
{

	JOG_tppPecaJogo mPeca = NULL ;

	mPeca = (JOG_tppPecaJogo) malloc(sizeof(JOG_tpPecaJogo));
	if(mPeca == NULL)
	{
		return JOG_CondRetFaltouMemoria;
	} /* if */

	if(pJOGO == NULL)
	{
		return JOG_CondRetJogoNulo ;
	} /* if */

	if (pPecaSetar == NULL)
	{
		return JOG_CondRetFimLista ;
	} /* if */
	
	mPeca->Time = 'B';
	mPeca->pTipoPeca = pPecaSetar;

	ListaRet = LIS_CriarLista(ExcluirPecaJogo , &mPeca->pListaCaminho);
	if(ListaRet == LIS_CondRetFaltouMemoria)
	{
		return JOG_CondRetFaltouMemoria;
	} /* if */

	ListaRet = LIS_CriarLista(ExcluirPecaJogo , &mPeca->pListaDestino);
	if(ListaRet == LIS_CondRetFaltouMemoria)
	{
		return JOG_CondRetFaltouMemoria;
	} /* if */

	ListaRet = LIS_InserirElementoApos(pJOGO->pListaTimeB , mPeca);
	if(ListaRet == LIS_CondRetFaltouMemoria)
	{
		return JOG_CondRetFaltouMemoria;
	} /* if */

	return JOG_CondRetOK;
	
} /* Fim funcao: JOG &Inserir peca no time B */

/***************************************************************************
*
*  Funcao: JOG  &Preenche caminho
*  ****/
JOG_tpCondRet JOG_PreencheCaminho(JOG_tppJogo pJOGO, TAB_tppTabuleiro pTabuleiro)
{
	
	JOG_tppPecaJogo pPecaJogo;
	JOG_tppPecaJogo pecaOcupada;
	TAB_tpCondRet TabRet;

	char Nome[MAX_NOME];
	int Diag;
	int Reta;
	int Qtde;

	int QtdeTmp = 0;

	int contador = 0;

	int JaConheceRei = 0;
	char SeRei[MAX_NOME];

	int NumElemL  ;

	GRA_tppVerGrafo Vertice;

	char * corrente = NULL;

	if(pJOGO == NULL)
	{
		return JOG_CondRetJogoNulo ;
	}
	
	TabRet = TAB_IrInicioCasas(pTabuleiro);

	do{

		TAB_ObterConteudo(pTabuleiro , (void**)&pPecaJogo);
		
		if(pPecaJogo != NULL){
			
			/* Limpa a lista da peca caso haja modificacao nos  movimentos */
			LIS_NumElem(pPecaJogo->pListaDestino , &NumElemL);

			if(NumElemL > 0)
				LIS_EsvaziarLista(pPecaJogo->pListaDestino);

			LIS_NumElem(pPecaJogo->pListaCaminho , &NumElemL);

			if(NumElemL > 0)
				LIS_EsvaziarLista(pPecaJogo->pListaCaminho);
			/* Fim limpa lista */

			TAB_ObterVerticeCorrente(pTabuleiro , &corrente);


			PEC_ObterDadosTipoPeca(pPecaJogo->pTipoPeca , (void**)&Nome, &Diag, &Reta, &Qtde);


			if(Diag == 1){

				QtdeTmp = Qtde;
				while(QtdeTmp > 0){
					TAB_ObterVerticeAresta(pTabuleiro  , (void**)&Vertice , "NORDESTE");
					if(Vertice != NULL){				
						TAB_ObterConteudoVertice(pTabuleiro , (void**)&pecaOcupada);							
						if(pecaOcupada != NULL){
							if(pecaOcupada->Time == pPecaJogo->Time){
								break;
							}else{
								PEC_ObterNome(pecaOcupada->pTipoPeca , (void**)&SeRei);
								if(strcmp(SeRei , "REI")==0){
									LIS_InserirElementoApos(pPecaJogo->pListaDestino , (void*)&Vertice);
									JaConheceRei = 1;
								}else{
									JOG_InsereElemApos(pPecaJogo , Vertice);
									break;
								}
							}
						}								
						JOG_InsereElemApos(pPecaJogo , Vertice);
						if(JaConheceRei == 0)
							LIS_InserirElementoApos(pPecaJogo->pListaDestino , (void*)&Vertice);
					}else{
						break;
					}
					QtdeTmp--;
				}
				if(JaConheceRei == 0){
					LIS_EsvaziarLista(pPecaJogo->pListaDestino);
				}
				TAB_SetarCorrente(pTabuleiro , corrente);

				QtdeTmp = Qtde;
				while(QtdeTmp > 0){
					TAB_ObterVerticeAresta(pTabuleiro  , (void**)&Vertice , "NOROESTE");
					if(Vertice != NULL){						
						TAB_ObterConteudoVertice(pTabuleiro , (void**)&pecaOcupada);
						if(pecaOcupada != NULL){
							if(pecaOcupada->Time == pPecaJogo->Time){
								break;
							}else{
								PEC_ObterNome(pecaOcupada->pTipoPeca , (void**)&SeRei);
								if(strcmp(SeRei , "REI")==0){
									LIS_InserirElementoApos(pPecaJogo->pListaDestino , (void*)&Vertice);
									JaConheceRei = 1;
								}else{
									JOG_InsereElemApos(pPecaJogo , Vertice);
									break;
								}
							}
						}	
						JOG_InsereElemApos(pPecaJogo , Vertice);
						if(JaConheceRei == 0)
							LIS_InserirElementoApos(pPecaJogo->pListaDestino , (void*)&Vertice);
					}else{
						break;
					}
					QtdeTmp--;
				}
				if(JaConheceRei == 0){
					LIS_EsvaziarLista(pPecaJogo->pListaDestino);
				}
				TAB_SetarCorrente(pTabuleiro , corrente);

				QtdeTmp = Qtde;
				while(QtdeTmp > 0){
					TAB_ObterVerticeAresta(pTabuleiro  , (void**)&Vertice , "SUDOESTE");
					if(Vertice != NULL){						
						TAB_ObterConteudoVertice(pTabuleiro , (void**)&pecaOcupada);
						if(pecaOcupada != NULL){
							if(pecaOcupada->Time == pPecaJogo->Time){
								break;
							}else{
								PEC_ObterNome(pecaOcupada->pTipoPeca , (void**)&SeRei);
								if(strcmp(SeRei , "REI")==0){
									LIS_InserirElementoApos(pPecaJogo->pListaDestino , (void*)&Vertice);
									JaConheceRei = 1;
								}else{
									JOG_InsereElemApos(pPecaJogo , Vertice);
									break;
								}
							}
						}							
						JOG_InsereElemApos(pPecaJogo , Vertice);
						if(JaConheceRei == 0)
							LIS_InserirElementoApos(pPecaJogo->pListaDestino , (void*)&Vertice);
					}else{
						break;
					}
					QtdeTmp--;
				}
				if(JaConheceRei == 0){
					LIS_EsvaziarLista(pPecaJogo->pListaDestino);
				}
				TAB_SetarCorrente(pTabuleiro , corrente);

				QtdeTmp = Qtde;
				while(QtdeTmp > 0){
					TAB_ObterVerticeAresta(pTabuleiro  , (void**)&Vertice , "SUDESTE");
					if(Vertice != NULL){						
						TAB_ObterConteudoVertice(pTabuleiro , (void**)&pecaOcupada);
						if(pecaOcupada != NULL){
							if(pecaOcupada->Time == pPecaJogo->Time){
								break;
							}else{
								PEC_ObterNome(pecaOcupada->pTipoPeca , (void**)&SeRei);
								if(strcmp(SeRei , "REI")==0){
									LIS_InserirElementoApos(pPecaJogo->pListaDestino , (void*)&Vertice);
									JaConheceRei = 1;
								}else{
									JOG_InsereElemApos(pPecaJogo , Vertice);
									break;
								}
							}
						}							
						JOG_InsereElemApos(pPecaJogo , Vertice);
						if(JaConheceRei == 0)
							LIS_InserirElementoApos(pPecaJogo->pListaDestino , (void*)&Vertice);
					}else{
						break;
					}
					QtdeTmp--;
				}
				if(JaConheceRei == 0){
					LIS_EsvaziarLista(pPecaJogo->pListaDestino);
				}
				TAB_SetarCorrente(pTabuleiro , corrente);
				
			}
			if(Reta == 1){

				QtdeTmp = Qtde;
				while(QtdeTmp > 0){
					TAB_ObterVerticeAresta(pTabuleiro  , (void**)&Vertice , "NORTE");
					if(Vertice != NULL){						
						TAB_ObterConteudoVertice(pTabuleiro , (void**)&pecaOcupada);
						if(pecaOcupada != NULL){
							if(pecaOcupada->Time == pPecaJogo->Time){
								break;
							}else{
								PEC_ObterNome(pecaOcupada->pTipoPeca , (void**)&SeRei);
								if(strcmp(SeRei , "REI")==0){
									LIS_InserirElementoApos(pPecaJogo->pListaDestino , (void*)&Vertice);
									JaConheceRei = 1;
								}else{
									JOG_InsereElemApos(pPecaJogo , Vertice);
									break;
								}
							}
						}							
						JOG_InsereElemApos(pPecaJogo , Vertice);
						if(JaConheceRei == 0)
							LIS_InserirElementoApos(pPecaJogo->pListaDestino , (void*)&Vertice);
					}else{
						break;
					}
					QtdeTmp--;
				}
				if(JaConheceRei == 0){
					LIS_EsvaziarLista(pPecaJogo->pListaDestino);
				}
				TAB_SetarCorrente(pTabuleiro , corrente);

				QtdeTmp = Qtde;
				while(QtdeTmp > 0){
					TAB_ObterVerticeAresta(pTabuleiro  , (void**)&Vertice , "SUL");
					if(Vertice != NULL){						
						TAB_ObterConteudoVertice(pTabuleiro , (void**)&pecaOcupada);
						if(pecaOcupada != NULL){
							if(pecaOcupada->Time == pPecaJogo->Time){
								break;
							}else{
								PEC_ObterNome(pecaOcupada->pTipoPeca , (void**)&SeRei);
								if(strcmp(SeRei , "REI")==0){
									LIS_InserirElementoApos(pPecaJogo->pListaDestino , (void*)&Vertice);
									JaConheceRei = 1;
								}else{
									JOG_InsereElemApos(pPecaJogo , Vertice);
									break;
								}
							}
						}							
						JOG_InsereElemApos(pPecaJogo , Vertice);
						if(JaConheceRei == 0)
							LIS_InserirElementoApos(pPecaJogo->pListaDestino , (void*)&Vertice);
					}else{
						break;
					}
					QtdeTmp--;
				}
				if(JaConheceRei == 0){
					LIS_EsvaziarLista(pPecaJogo->pListaDestino);
				}
				TAB_SetarCorrente(pTabuleiro , corrente);

				QtdeTmp = Qtde;
				while(QtdeTmp > 0){
					TAB_ObterVerticeAresta(pTabuleiro  , (void**)&Vertice , "LESTE");
					if(Vertice != NULL){						
						TAB_ObterConteudoVertice(pTabuleiro , (void**)&pecaOcupada);
						if(pecaOcupada != NULL){
							if(pecaOcupada->Time == pPecaJogo->Time){
								break;
							}else{
								PEC_ObterNome(pecaOcupada->pTipoPeca , (void**)&SeRei);
								if(strcmp(SeRei , "REI")==0){
									LIS_InserirElementoApos(pPecaJogo->pListaDestino , (void*)&Vertice);
									JaConheceRei = 1;
								}else{
									JOG_InsereElemApos(pPecaJogo , Vertice);
									break;
								}
							}
						}							
						JOG_InsereElemApos(pPecaJogo , Vertice);
						if(JaConheceRei == 0)
							LIS_InserirElementoApos(pPecaJogo->pListaDestino , (void*)&Vertice);
					}else{
						break;
					}
					QtdeTmp--;
				}
				if(JaConheceRei == 0){
					LIS_EsvaziarLista(pPecaJogo->pListaDestino);
				}
				TAB_SetarCorrente(pTabuleiro , corrente);

				QtdeTmp = Qtde;
				while(QtdeTmp > 0){
					TAB_ObterVerticeAresta(pTabuleiro  , (void**)&Vertice , "OESTE");
					if(Vertice != NULL){						
						TAB_ObterConteudoVertice(pTabuleiro , (void**)&pecaOcupada);
						if(pecaOcupada != NULL){
							if(pecaOcupada->Time == pPecaJogo->Time){
								break;
							}else{
								PEC_ObterNome(pecaOcupada->pTipoPeca , (void**)&SeRei);
								if(strcmp(SeRei , "REI")==0){
									LIS_InserirElementoApos(pPecaJogo->pListaDestino , (void*)&Vertice);
									JaConheceRei = 1;
								}else{
									JOG_InsereElemApos(pPecaJogo , Vertice);
									break;
								}
							}
						}							
						JOG_InsereElemApos(pPecaJogo , Vertice);
						if(JaConheceRei == 0)
							LIS_InserirElementoApos(pPecaJogo->pListaDestino , (void*)&Vertice);
					}else{
						break;
					}
					QtdeTmp--;
				}
				if(JaConheceRei == 0){
					LIS_EsvaziarLista(pPecaJogo->pListaDestino);
				}
				TAB_SetarCorrente(pTabuleiro , corrente);

			}

			JaConheceRei = QtdeTmp = Reta = Qtde = Diag = 0;	
			
		}

		TabRet = TAB_AvancarCasas(pTabuleiro , 1);
		
	}while(TabRet != TAB_CondRetFimLista);

	
	

	return JOG_CondRetOK;

} /* Fim funcao: JOG &Preenche caminho */

/***************************************************************************
*
*  Funcao: JOG  &Verifica Xeque
*  ****/

JOG_tpCondRet JOG_VerificaXequeMate(JOG_tppJogo pJogo, TAB_tppTabuleiro pTabuleiro , char ** CasaCausa)
{
	char * pPeca;
	char PecaCausadora[MAX_NOME];
	char CasaCausadora[2];
	int Pecas2Caminho = 0;

	/*Obter REI do time A */
	JOG_ObterCasaRei(pTabuleiro , &pPeca);
	
	/* Vai em busca do REI */
	Pecas2Caminho = VerificaPecasCaminho(pJogo, pTabuleiro, pPeca , (char**)&PecaCausadora , (char**)&CasaCausadora , 'A');

	strcpy((char *)CasaCausa , CasaCausadora);

	if(Pecas2Caminho == 1){
		printf(" EXISTE PECA CAUSANDO XEQUE \n");
		return JOG_CondRetXequeMateS;
	}

	strcpy(PecaCausadora , "");

	return JOG_CondRetXequeMateN;
 
} /* Fim funcao: JOG &Verifica Xeque */

/***************************************************************************
*
*  Funcao: JOG  &Tentar sair do Xeque Mate
*  ****/

JOG_tpCondRet JOG_VerificaSairXequeMate(JOG_tppJogo pJogo, TAB_tppTabuleiro pTabuleiro , char * CasaDestino)
{

	char PecaCausadora[MAX_NOME];
	char * CasaComedora;
	int Pecas2Caminho = 0;

	Pecas2Caminho = VerificaPecasCaminho(pJogo, pTabuleiro, CasaDestino , (char**)&PecaCausadora , (char**)&CasaComedora , 'B');

	if(Pecas2Caminho == 1){
		printf("Peca que tira o Xeque Mate %s \n" , CasaComedora);
		return JOG_CondRetXequeMateS;
	}

	return JOG_CondRetXequeMateN;

} /* Fim funcao: JOG &Tentar sair do Xeque Mate */

/***************************************************************************
*
*  Funcao: JOG  &Obter casa do rei
*  ****/

JOG_tpCondRet JOG_ObterCasaRei(TAB_tppTabuleiro pTabuleiro , char ** pPecaO)
{
	char NomePeca[MAX_NOME];
	char * NomeCasa = NULL;
	JOG_tppPecaJogo pPecaJogo;
	TAB_tpCondRet TabRet;

	TabRet = TAB_IrInicioCasas(pTabuleiro);
	do{
		TAB_ObterConteudo(pTabuleiro , (void**)&pPecaJogo);


		if(pPecaJogo != NULL){

			PEC_ObterNome(pPecaJogo->pTipoPeca , (void**)&NomePeca);
			if(pPecaJogo->Time == 'B' && strcmp(NomePeca , "REI")==0){
				TAB_ObterVerticeCorrente(pTabuleiro , (char**)&NomeCasa);
				*pPecaO = NomeCasa;
				break;
			}
		}
		TabRet = TAB_AvancarCasas(pTabuleiro , 1);

	}while(TabRet != TAB_CondRetFimLista);

	return JOG_CondRetOK;
} /* Fim funcao: JOG &Obter casa do rei */

/***************************************************************************
*
*  Funcao: JOG  &Obter dados de uma peca
*  ****/
JOG_tpCondRet JOG_ObterDadosPeca(JOG_tppPecaJogo pPeca , void ** NomeNaCasa , char * Time)
{

	char NomePeca[MAX_NOME];

	PEC_ObterNome(pPeca->pTipoPeca , (void**)&NomePeca);

	strcpy((char *)NomeNaCasa , NomePeca);

	*Time = pPeca->Time;

	return JOG_CondRetOK;
} /* Fim funcao: JOG &Obter dados de uma peca */

/***************************************************************************
*
*  Funcao: JOG  &Destruir Jogo
*  ****/
JOG_tpCondRet JOG_DestruirJogo(JOG_tppJogo pJogo)
{
	JOG_tppPecaJogo pPecaBusca;

	ListaRet = LIS_IrInicioLista(pJogo->pListaTimeA);
	do{
		LIS_ObterValor(pJogo->pListaTimeA , (void**)&pPecaBusca);

		pPecaBusca->Time = '\0';
		LIS_EsvaziarLista(pPecaBusca->pListaCaminho);
		LIS_EsvaziarLista(pPecaBusca->pListaDestino);
		pPecaBusca->pTipoPeca = NULL;

		free(pPecaBusca);

		ListaRet = LIS_AvancarElementoCorrente(pJogo->pListaTimeA , 1);

	}while(ListaRet != LIS_CondRetFimLista);

	ListaRet = LIS_IrInicioLista(pJogo->pListaTimeB);
	do{
		LIS_ObterValor(pJogo->pListaTimeB , (void**)&pPecaBusca);

		pPecaBusca->Time = '\0';
		LIS_DestruirLista(pPecaBusca->pListaCaminho);
		LIS_DestruirLista(pPecaBusca->pListaDestino);
		pPecaBusca->pTipoPeca = NULL;

		free(pPecaBusca);

		ListaRet = LIS_AvancarElementoCorrente(pJogo->pListaTimeB , 1);

	}while(ListaRet != LIS_CondRetFimLista);

	LIS_DestruirLista(pJogo->pListaTimeA);

	LIS_DestruirLista(pJogo->pListaTimeB);

	return JOG_CondRetOK;

} /* Fim funcao: JOG &Destruir Jogo */

/***************************************************************************
*  Funcao: JOG  &Insere elemento apos
*
*  ****/
JOG_tpCondRet JOG_InsereElemApos(JOG_tppPecaJogo pPeca , void * Conteudo)
{

	if(pPeca == NULL)
	{
		return JOG_CondRetFimLista;
	} /* if */
	
	ListaRet = LIS_InserirElementoApos(pPeca->pListaCaminho , Conteudo);


	if(ListaRet == LIS_CondRetFaltouMemoria)
	{
		return JOG_CondRetFaltouMemoria;
	} /* if */

	return JOG_CondRetOK;
} /* Fim funcao: JOG &Insere elemento apos */


/***************************************************************************
*
*  Funcao: JOG  &Avancar corrente do time
*  ****/

JOG_tpCondRet JOG_AvancarCorrrenteTime(JOG_tppJogo pJOGO , char Time , int qtdPecas)
{
	if(pJOGO == NULL)
	{
		return JOG_CondRetJogoNulo ;
	} /* if */

	if(Time == 'A'){
		ListaRet = LIS_AvancarElementoCorrente(pJOGO->pListaTimeA, qtdPecas);
		if((ListaRet == LIS_CondRetListaVazia) || (ListaRet == LIS_CondRetFimLista))
		{
			return JOG_CondRetFimLista;
		} /* if */
	}
	else if(Time == 'B'){
		ListaRet = LIS_AvancarElementoCorrente(pJOGO->pListaTimeB, qtdPecas);
		if((ListaRet == LIS_CondRetListaVazia) || (ListaRet == LIS_CondRetFimLista))
		{
			return JOG_CondRetFimLista;
		} /* if */
	} /* if */
		
	return JOG_CondRetOK;
	
} /* Fim funcao: JOG &Avancar corrente do time */



/***************************************************************************
*
*  Funcao: JOG  &Numero de pecas do time
*  ****/

JOG_tpCondRet JOG_NumPecasTime(JOG_tppJogo pJOGO ,char Time, int * NumPecas)
{
	if(pJOGO == NULL)
	{
		return JOG_CondRetJogoNulo ;
	} /* if */

	if(Time == 'A'){
		LIS_NumElem(pJOGO->pListaTimeA , NumPecas);
	}
	else if(Time == 'B'){
		LIS_NumElem(pJOGO->pListaTimeB , NumPecas);
	} /* if */

	return JOG_CondRetOK;

} /* Fim funcao: JOG &Numero de pecas do time */

/***************************************************************************
*
*  Funcao: JOG  &Obter tipo de peca
*  ****/

JOG_tpCondRet JOG_ObterTipoPeca(JOG_tppJogo pJOGO , char Time, void ** pTipo)
{
	JOG_tppPecaJogo pPecaJogo ;

	if(pJOGO == NULL)
	{
		return JOG_CondRetJogoNulo ;
	} /* if */
		
	if(Time == 'A'){
		
		ListaRet = LIS_ObterValor(pJOGO->pListaTimeA , (void**)&pPecaJogo);
		if(ListaRet == LIS_CondRetListaVazia)
		{
			return JOG_CondRetJogoNulo;
		} /* if */

	}
	else if(Time == 'B'){

		ListaRet = LIS_ObterValor(pJOGO->pListaTimeB , (void**)&pPecaJogo);
		if(ListaRet == LIS_CondRetListaVazia)
		{
			return JOG_CondRetJogoNulo;
		} /* if */
		
	} /* if */

	*pTipo = pPecaJogo->pTipoPeca;

	return JOG_CondRetOK;
} /* Fim funcao: JOG &Obter tipo de peca */

/***************************************************************************
*
*  Funcao: JOG  &Ir inicio das pecas
*  ****/

JOG_tpCondRet JOG_IrInicioPecas(JOG_tppJogo pJOGO , char Time)
{
	if(pJOGO == NULL)
	{
		return JOG_CondRetJogoNulo ;
	} /* if */

	if(Time == 'A'){
		ListaRet = LIS_IrInicioLista(pJOGO->pListaTimeA);
		if(ListaRet == LIS_CondRetListaVazia)
		{
			return JOG_CondRetFimLista;
		} /* if */

	}
	else if(Time == 'B'){
		ListaRet = LIS_IrInicioLista(pJOGO->pListaTimeB);
		if(ListaRet == LIS_CondRetListaVazia)
		{
			return JOG_CondRetFimLista;
		} /* if */
	}
	return JOG_CondRetOK;
} /* Fim funcao: JOG &Ir inicio das pecas */

/***************************************************************************
*
*  Funcao: JOG  &Obter peca do jogo
*  ****/

JOG_tpCondRet JOG_ObterPecaJogo(JOG_tppJogo pJOGO , char Time, void ** pTipo)
{
	JOG_tppPecaJogo pPecaJogo;
	
	if(pJOGO == NULL)
	{
		return JOG_CondRetJogoNulo ;
	} /* if */
	
	if(Time == 'A'){		
		ListaRet = LIS_ObterValor(pJOGO->pListaTimeA , (void**)&pPecaJogo);
		if(ListaRet == LIS_CondRetListaVazia)
		{
			return JOG_CondRetJogoNulo;
		} /* if */
	}
	else if(Time == 'B'){
		ListaRet = LIS_ObterValor(pJOGO->pListaTimeB , (void**)&pPecaJogo);
		if(ListaRet == LIS_CondRetListaVazia)
		{
			return JOG_CondRetJogoNulo;
		} /* if */
		
	} /* if */

	*pTipo = pPecaJogo;

	return JOG_CondRetOK;
	
} /* Fim funcao: JOG &Obter peca do jogo */


/************  Codigo das funcoes encapsuladas no modulo  *************/

/***********************************************************************
*
*  $FC Funcao: JOG  -Excluir jogo
*
***********************************************************************/

void ExcluirJogo( void * pPeca )
{


} /* Fim funcao: JOG -Excluir jogo */

/***********************************************************************
*
*  $FC Funcao: JOG  -Excluir peca do jogo
*
***********************************************************************/

void ExcluirPecaJogo( void * pPeca )
{
		
		

} /* Fim funcao: JOG -Excluir peca do jogo */

/***********************************************************************
*
*  $FC Funcao: JOG  -Verifica pecas no caminho
*
***********************************************************************/
 int VerificaPecasCaminho(JOG_tppJogo pJogo ,TAB_tppTabuleiro pTabuleiro  , char * pPeca , char ** PecaCausadora , char ** CasaCausadora , char Time)
{
	JOG_tppPecaJogo pPecaJogo;
	TAB_tpCondRet TabRet;
	GRA_tppVerGrafo Vertice = NULL;
	char NomePeca[MAX_NOME];
	char NomeCausa[2];
	char * NomeCasa = NULL;
	int EncontrouRei = 0;

	TabRet = TAB_IrInicioCasas(pTabuleiro);
	do{
		TAB_ObterConteudo(pTabuleiro , (void**)&pPecaJogo);

		if(pPecaJogo != NULL){
			PEC_ObterNome(pPecaJogo->pTipoPeca , (void**)&NomePeca);
			TAB_ObterVerticeCorrente(pTabuleiro , (char**)&NomeCausa);
			if(pPecaJogo->Time == Time){
				ListaRet = LIS_IrInicioLista(pPecaJogo->pListaCaminho);
				if(ListaRet == LIS_CondRetOK){
					do{
						LIS_ObterValor(pPecaJogo->pListaCaminho , (void**)&Vertice);

						GRA_ResgatarIdVertice(Vertice , &NomeCasa);

						if(strcmp(pPeca,NomeCasa)==0){
							EncontrouRei = 1;
						}

						ListaRet = LIS_AvancarElementoCorrente(pPecaJogo->pListaCaminho , 1);

						NomeCasa = NULL;

					}while(ListaRet != LIS_CondRetFimLista);
				}
			}
		}
		TabRet = TAB_AvancarCasas(pTabuleiro , 1);

	}while(TabRet != TAB_CondRetFimLista);

	return EncontrouRei;

} /* Fim funcao: JOG -Verificar pecas no caminho */

/********** Fim do modulo de implementacao: JOG  Lista duplamente encadeada **********/

