/***************************************************************************
*
*  $MCD Módulo de definição: TAB  Tabuleiro de Xadrez
*
*  Arquivo gerado:              TABULEIRO.C
*  Letras identificadoras:      TAB
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: INF 1301 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: aw - Alexandre Werneck
*           fr - Fernanda Camelo Ribeiro
*			vo - Vinicius de Luiz de Oliveira
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       afv   19/out/2013 início desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>


#define LISTA_OWN
#include "LISTA.H"
#undef LISTA_OWN

#include "GRAFO.H"
#include "PECA.H"
#include "JOGO.H" 

#define MAX_NOME 10

GRA_tpCondRet GrafRet;

LIS_tpCondRet ListaRet;

/***********************************************************************
*
*  $TC Tipo de dados: TAB Descritor do Tabuleiro
*
*
***********************************************************************/

   typedef struct TAB_tagTabuleiro {

         GRA_tppGrafo   tpGrafo;
		
		 TAB_tppEstCasa tpEstCasa;

		 LIS_tppLista   pListaPecas;

   } TAB_tpTabuleiro ;


/***********************************************************************
*
*  $TC Tipo de dados: TAB Descritor do elemento da casa do Tabuleiro
*
*
*  $ED Descrição do tipo
*     Descreve a organização do elemento
*
***********************************************************************/

typedef struct tpElemCasa {

        struct tpElemCasa * pNoNoroeste ; 
			/* Adjacente da quina superior esquerda */
		
        struct tpElemCasa * pNoNorte ;
			/* Adjacente de cima */

        struct tpElemCasa * pNoNordeste ;
            /* Adjacente da quina superior direita */
            
        struct tpElemCasa * pNoOeste ; 
            /* Adjacente da esqueda */
            
        struct tpElemCasa * pNoLeste ;
            /* Adjacente da direita */

        struct tpElemCasa * pNoSudoeste ;
            /* Adjacente da quina inferior esquerda */
            
        struct tpElemCasa * pNoSul ;
            /* Adjacente de baixo */

        struct tpElemCasa * pNoSudeste ;
            /* Adjacente da quina inferior direita */

        GRA_tppVerGrafo pVertice;
			/* Lista para o elemento do tipo Vértice */

} tpElemCasa ;

/***********************************************************************
*
*  $TC Tipo de dados: TAB Descritor da estrutura cabeca da matriz
*
*
***********************************************************************/

typedef struct TAB_tgEstCasa {

        tpElemCasa * pNoRaiz ;
            /* Ponteiro para a raiz da estrutura casa */

		tpElemCasa * pNoIndLinha ;
            /* Ponteiro para a indice de linha da estrutura casa */

        tpElemCasa * pNoCorr ;
            /* Ponteiro para o nó corrente da estrutura casa */

} TAB_tpEstCasa ;


/***** Protótipos das funções encapsuladas no módulo *****/

   static void ExcluirInfo ( void * pValor );
   
   static void ExcluirPeca( void * pPeca );

   static TAB_tpCondRet PreparaEstruturaMatriz( TAB_tpEstCasa * tpMat, GRA_tppGrafo pGrafo  , int numElementos ) ;

   static TAB_tpCondRet CriarNoRaiz( TAB_tpEstCasa * tpMat, GRA_tppGrafo pGrafo , int numElementos ) ;

   static tpElemCasa * CriarNo( GRA_tppGrafo pGrafo , char * Id ) ;

   static void ExcluirValorNo( void * pValor );

/*****  Código das funções exportadas pelo módulo  *****/


TAB_tpCondRet TAB_CriarTabuleiro( TAB_tppTabuleiro * pTabuleiro ){

	GRA_tppGrafo     pGrafo;
	TAB_tppEstCasa   pEstCasa;
	LIS_tppLista     ListaPecas;
	TAB_tppTabuleiro mTab;

	mTab = ( TAB_tppTabuleiro ) malloc ( sizeof ( TAB_tpTabuleiro ) );
			/* Malloc para gerar um ponteiro de matriz */
		   
	if(mTab == NULL)
	{
		return TAB_CondRetFaltouMemoria ;
	} /* if */

	GRA_CriarGrafo( &pGrafo , ExcluirInfo);

	TAB_CriarEstruturaCasa(&pEstCasa, pGrafo , 8);

	LIS_CriarLista(ExcluirPeca , &ListaPecas);

	mTab->tpGrafo      = pGrafo;

	mTab->tpEstCasa    = pEstCasa;

	mTab->pListaPecas  = ListaPecas;

	(*pTabuleiro) = (TAB_tpTabuleiro *) malloc (sizeof(TAB_tppTabuleiro));
	
	if( (*pTabuleiro) == NULL)
	{
		return TAB_CondRetFaltouMemoria ;
	} /* if */

	(*pTabuleiro) = mTab ;

	return TAB_CondRetOK;
}


TAB_tpCondRet TAB_SetarCorrente( TAB_tppTabuleiro pTabuleiro , char * NomeCasa )
{
	GRA_tppVerGrafo pVert;

	if(pTabuleiro == NULL){
		return TAB_CondRetTabuleiroNulo;
	}

	GrafRet = GRA_SetarCorrente(pTabuleiro->tpGrafo , NomeCasa);

	GRA_ObterVertice(pTabuleiro->tpGrafo , (void**)&pVert);

	return TAB_CondRetOK;

}

TAB_tpCondRet TAB_IrInicioCasas( TAB_tppTabuleiro pTabuleiro  )
{
	if(pTabuleiro == NULL){
		return TAB_CondRetTabuleiroNulo;
	}

	GRA_IrInicio(pTabuleiro->tpGrafo);

	pTabuleiro->tpEstCasa->pNoCorr = pTabuleiro->tpEstCasa->pNoRaiz;

	return TAB_CondRetOK;
}

TAB_tpCondRet TAB_AvancarCasas( TAB_tppTabuleiro pTabuleiro , int val )
{
	if(pTabuleiro == NULL){
		return TAB_CondRetTabuleiroNulo;
	}

	GrafRet = GRA_AvancarCorrenteVert(pTabuleiro->tpGrafo , val);

	if(GrafRet == GRA_CondRetOK){
		return TAB_CondRetOK;
	}
	return TAB_CondRetFimLista;
}

TAB_tpCondRet TAB_ObterConteudo( TAB_tppTabuleiro pTabuleiro , void ** pConteudo )
{

	if(pTabuleiro == NULL){
		return TAB_CondRetTabuleiroNulo;
	}
	
	GRA_PegaConteudo(pTabuleiro->tpGrafo , (void**)&pConteudo);

	return TAB_CondRetOK;

}

TAB_tpCondRet TAB_ObterCasa(TAB_tppTabuleiro pTabuleiro , void ** pConteudo)
{
	if(pTabuleiro == NULL){
		return TAB_CondRetTabuleiroNulo;
	}

	*pConteudo = pTabuleiro->tpEstCasa->pNoCorr;

	return TAB_CondRetOK;
}

TAB_tpCondRet TAB_ObterVertice(TAB_tppTabuleiro pTabuleiro , void ** Vertice)
{

	if(pTabuleiro == NULL){
		return TAB_CondRetTabuleiroNulo;
	}

	*Vertice = pTabuleiro->tpEstCasa->pNoCorr->pVertice;

	return TAB_CondRetOK;

}

TAB_tpCondRet TAB_InserirConteudoCasa(TAB_tppTabuleiro pTabuleiro , void * pPeca)
{

	if(pTabuleiro == NULL){
		return TAB_CondRetTabuleiroNulo;
	}

	GrafRet = GRA_InsereConteudoVertice(pTabuleiro->tpGrafo , pPeca);

	if(GrafRet == GRA_CondRetOK){
		return TAB_CondRetOK;
	}

	return TAB_CondRetNaoAchou;
}

TAB_tpCondRet TAB_ApresentaTabuleiro( TAB_tppTabuleiro pTabuleiro ){

	int cont = 0;
	char * id = NULL;
	char * NomeCasa = NULL;
	int numElem = 0;
	JOG_tppPecaJogo pPecaTab;

	GrafRet = GRA_NumeroVertices(pTabuleiro->tpGrafo , &numElem);
	if(GrafRet == GRA_CondRetOK ){
		printf("Numero de Casas do Tabuleiro %d \n\n" , numElem);
	} /* if */

	GrafRet = GRA_IrInicio(pTabuleiro->tpGrafo);

	do{

		cont++;

		GRA_BuscaIdVertice( pTabuleiro->tpGrafo , &id );

		GRA_PegaConteudo (pTabuleiro->tpGrafo , (void**)&pPecaTab);

		if(pPecaTab != NULL){
			printf( "| %s |" , "XX" );
		}else{
			printf( "| %s |" , id );
		}
		
		if(cont == 8){
			printf( "\n" );
			cont=0;
		}

		GrafRet = GRA_AvancarCorrenteVert(pTabuleiro->tpGrafo , 1);

	}while(GrafRet != GRA_CondRetFimLista);	
	printf("\n");
	return TAB_CondRetOK;

}

TAB_tpCondRet TAB_CriarTipoPeca(TAB_tppTabuleiro pTabuleiro , char * Nome , int Diagonal , int Reta , int QtdeMov)
{

	PEC_tppPeca pPeca;
	if(pTabuleiro == NULL){
		return TAB_CondRetTabuleiroNulo;
	}

	PEC_CriarPeca(&pPeca , Diagonal , Reta , QtdeMov , Nome );

	if(pPeca != NULL){
		LIS_InserirElementoApos(pTabuleiro->pListaPecas , pPeca);
	} /* if */

	return TAB_CondRetOK;
}

TAB_tpCondRet TAB_ApresentaTipoPecas(TAB_tppTabuleiro pTabuleiro)
{
	PEC_tppPeca pPeca;
	char * NomePeca;
	if(pTabuleiro==NULL){
		return TAB_CondRetTabuleiroNulo;
	}
	if(pTabuleiro->pListaPecas == NULL){
		return TAB_CondRetTabuleiroListaNula;
	}
	
	printf("Lista de tipo de pecas \n");
	ListaRet = LIS_IrInicioLista(pTabuleiro->pListaPecas);
	if(ListaRet == LIS_CondRetListaVazia)
		return TAB_TimeAVazio;
	do{
		LIS_ObterValor(pTabuleiro->pListaPecas , (void**)&pPeca);

		PEC_ObterNome (pPeca , (void**)&NomePeca);
		printf("Nome Peca: %s \n" , &NomePeca );


		ListaRet = LIS_AvancarElementoCorrente(pTabuleiro->pListaPecas , 1);


	}while(ListaRet != LIS_CondRetFimLista);

	
	return TAB_CondRetOK;

}

TAB_tpCondRet TAB_ProcuraPeca(TAB_tppTabuleiro pTabuleiro , char * NomeBuscado , void ** PecaBuscada)
{

	PEC_tppPeca pPeca;

	char NomeEnc[MAX_NOME];

	if(pTabuleiro==NULL){
		return TAB_CondRetTabuleiroNulo;
	}

	ListaRet = LIS_IrInicioLista(pTabuleiro->pListaPecas);
	
	if(ListaRet == LIS_CondRetListaVazia)
	
		return TAB_CondRetFaltouMemoria;

	do{
		LIS_ObterValor(pTabuleiro->pListaPecas , (void**)&pPeca);
		
		PEC_ObterNome (pPeca , (void**)&NomeEnc);

		if(strcmp(NomeBuscado , NomeEnc)==0){
			*PecaBuscada = pPeca;
			return TAB_CondRetOK;
		}

		ListaRet = LIS_AvancarElementoCorrente(pTabuleiro->pListaPecas , 1);


	}while(ListaRet != LIS_CondRetFimLista);

	
	return TAB_CondRetNaoAchou;

} /* if */

TAB_tpCondRet TAB_IrInicioListaPecas(TAB_tppTabuleiro pTabuleiro)
{
	if(pTabuleiro==NULL){
		return TAB_CondRetTabuleiroNulo;
	}

	ListaRet = LIS_IrInicioLista(pTabuleiro->pListaPecas);
	if(ListaRet == LIS_CondRetListaVazia)
		return TAB_CondRetListaVazia;
	return TAB_CondRetOK;
}

TAB_tpCondRet TAB_ObterTipoPeca(TAB_tppTabuleiro pTabuleiro , void ** pPeca)
{

	if(pTabuleiro==NULL){
		return TAB_CondRetTabuleiroNulo;
	}

	ListaRet = LIS_ObterValor(pTabuleiro->pListaPecas , (void**)&pPeca);


	if(ListaRet == LIS_CondRetListaVazia)
		return TAB_CondRetListaVazia;

	return TAB_CondRetOK;
}

TAB_tpCondRet TAB_AvancarTipoPeca(TAB_tppTabuleiro pTabuleiro , int val)
{
	if(pTabuleiro==NULL){
		return TAB_CondRetTabuleiroNulo;
	} /* if */
	ListaRet = LIS_AvancarElementoCorrente(pTabuleiro->pListaPecas , val);
	if(ListaRet == LIS_CondRetFimLista){
		return TAB_CondRetFimLista;
	} /* if */
	return TAB_CondRetOK;
}

void ExcluirInfo ( void * pValor )
{

    free( ( void * ) pValor ) ;

} /* Fim função: TST -Excluir informacao */

void ExcluirPeca( void * pPeca )
{

	free ( (void *) pPeca);

} /* Fim função: TST -Excluir peca */


/**** Novas funcoes da estrutura CASA ******/

/*** CRIAR MATRIZ ****/
TAB_tpCondRet TAB_CriarEstruturaCasa( TAB_tppEstCasa *tpMat, GRA_tppGrafo pGrafo , int numElementos){
	   
		TAB_tpCondRet CondRet ;

		TAB_tppEstCasa mMatriz ;
		
		mMatriz = ( TAB_tppEstCasa ) malloc ( sizeof ( TAB_tpEstCasa ) );
			/* Malloc para gerar um ponteiro de matriz */

		   
	   if(mMatriz == NULL)
	   {
		   return TAB_CondRetFaltouMemoria ;
	   } /* if */
	   
	   mMatriz->pNoCorr      = NULL;
	   mMatriz->pNoRaiz      = NULL;
	   mMatriz->pNoIndLinha  = NULL;

	   CondRet = CriarNoRaiz(mMatriz, pGrafo , numElementos);
			 /* Inicializo a estrutura da matriz setando a raiz */

	   if(CondRet != TAB_CondRetOK)
	   {
		return CondRet;
	   } /* if */


	   (*tpMat) = ( TAB_tpEstCasa* ) malloc( sizeof( MAT_tppMatriz )) ;

		if ( (*tpMat) == NULL )
		{
			return TAB_CondRetFaltouMemoria ;
		} /* if */

		(*tpMat) = mMatriz ;


		return TAB_CondRetOK ;
}

/***** PREPARA ESTRUTURA MATRIZ *****/

TAB_tpCondRet PreparaEstruturaMatriz( TAB_tpEstCasa * tpMat, GRA_tppGrafo pGrafo  , int numElementos ){

	int i = 0, j = 0;
	
	char * IdVertices[64] = 
	{
		"A1","A2","A3","A4","A5","A6","A7","A8","B1","B2","B3","B4","B5","B6","B7","B8","C1","C2","C3","C4","C5","C6","C7","C8","D1","D2","D3","D4","D5","D6","D7","D8","E1","E2","E3","E4","E5","E6","E7","E8","F1","F2","F3","F4","F5","F6","F7","F8","G1","G2","G3","G4","G5","G6","G7","G8","H1","H2","H3","H4","H5","H6","H7","H8"
	};

	tpElemCasa * tpElemLesteCabeca   = NULL;
	tpElemCasa * tpElemSudesteCabeca = NULL;
	tpElemCasa * tpElemSulCabeca     = NULL;
	tpElemCasa * tpElemLesteNo	     = NULL;
	tpElemCasa * tpElemSudesteNo	 = NULL;
	tpElemCasa * tpElemSulNo		 = NULL;
	tpElemCasa * tpElem			     = CriarNo( pGrafo , IdVertices[0] );
	if(tpElem == NULL)
	{
		return TAB_CondRetFaltouMemoria ;
	}

	if(numElementos == 1){
		tpMat->pNoCorr       = tpElem;
		tpMat->pNoRaiz       = tpElem;
		tpMat->pNoIndLinha   = tpElem;
		return TAB_CondRetOK;
	}

	numElementos = numElementos - 1;

	

	for(i=0;i<=numElementos;i++){

		for(j=0;j<=numElementos;j++){	

			
					/* testa a condicão para 3 adjacentes */
				if((i==0 || i==numElementos) && (j==0 || j==numElementos)){

					if(i==0 && j==0){
						tpMat->pNoCorr       = tpElem;
						tpMat->pNoRaiz       = tpElem;
						tpMat->pNoIndLinha   = tpElem;

						tpElemLesteCabeca   = CriarNo( pGrafo , IdVertices[1] );
						tpElemSudesteCabeca = CriarNo( pGrafo , IdVertices[9] );
						tpElemSulCabeca     = CriarNo( pGrafo , IdVertices[8]);
						if(tpElemLesteCabeca==NULL || tpElemSudesteCabeca==NULL || tpElemSulCabeca==NULL){
							return TAB_CondRetFaltouMemoria ;
						}						
						tpMat->pNoCorr->pNoLeste     = tpElemLesteCabeca;
						tpMat->pNoCorr->pNoSudeste   = tpElemSudesteCabeca;
						tpMat->pNoCorr->pNoSul       = tpElemSulCabeca;


					}
					if(i==0 && j==numElementos){
						
						tpMat->pNoCorr->pNoLeste->pNoSul       = tpMat->pNoCorr->pNoSudeste;
						tpMat->pNoCorr->pNoLeste->pNoSudoeste  = tpMat->pNoCorr->pNoSul;
						tpMat->pNoCorr->pNoLeste->pNoOeste     = tpMat->pNoCorr;


						tpMat->pNoCorr = tpMat->pNoCorr->pNoLeste ;
							/* seta como corrente */

					}
					if(i==numElementos && j==0){

						tpMat->pNoIndLinha->pNoSul->pNoNorte     = tpMat->pNoIndLinha;
						tpMat->pNoIndLinha->pNoSul->pNoNordeste  = tpMat->pNoIndLinha->pNoLeste;
						tpMat->pNoIndLinha->pNoSul->pNoLeste     = tpMat->pNoIndLinha->pNoSudeste;


						tpMat->pNoCorr      = tpMat->pNoIndLinha->pNoSul;
							/* seta como corrente */

						tpMat->pNoIndLinha  = tpMat->pNoIndLinha->pNoSul;
							/* seta como indice da linha */

					}
					if(i==numElementos && j==numElementos){

						tpMat->pNoCorr->pNoLeste->pNoNorte     = tpMat->pNoCorr->pNoNordeste;
						tpMat->pNoCorr->pNoLeste->pNoNoroeste  = tpMat->pNoCorr->pNoNorte;
						tpMat->pNoCorr->pNoLeste->pNoOeste     = tpMat->pNoCorr;

						tpMat->pNoCorr  = tpMat->pNoCorr->pNoLeste;
							/* seta como corrente */

					}

				}

					 /* testa a condição para 5 adjacentes */
				else if(i==0 || i==numElementos || j==0 || j==numElementos){


					if(i==0 && (j!=numElementos || j!=0)){
						
						tpMat->pNoCorr->pNoLeste->pNoSul      = tpMat->pNoCorr->pNoSudeste;
						tpMat->pNoCorr->pNoLeste->pNoSudoeste = tpMat->pNoCorr->pNoSul;
						tpMat->pNoCorr->pNoLeste->pNoOeste    = tpMat->pNoCorr;

						tpElemLesteNo   = CriarNo( pGrafo , IdVertices[j+1]);
						tpElemSudesteNo = CriarNo( pGrafo , IdVertices[(numElementos * (i+1)) + (j+2)]);
						if(tpElemLesteNo==NULL || tpElemSudesteNo==NULL){
							return TAB_CondRetFaltouMemoria ;
						}
						tpMat->pNoCorr->pNoLeste->pNoLeste    = tpElemLesteNo;
						tpMat->pNoCorr->pNoLeste->pNoSudeste  = tpElemSudesteNo;

						tpMat->pNoCorr  = tpMat->pNoCorr->pNoLeste;
							/* seta como corrente */

					}

					if(j==0 && (i!=numElementos || i!=0)){

						tpMat->pNoIndLinha->pNoSul->pNoLeste    = tpMat->pNoIndLinha->pNoSudeste;				
						tpMat->pNoIndLinha->pNoSul->pNoNordeste = tpMat->pNoIndLinha->pNoLeste;
						tpMat->pNoIndLinha->pNoSul->pNoNorte    = tpMat->pNoIndLinha;

						tpElemSulNo     = CriarNo( pGrafo , IdVertices[(numElementos * (i+1)) + (i+1)]);
						tpElemSudesteNo = CriarNo( pGrafo , IdVertices[(numElementos * (i+1)) + (i+2)]);
						if(tpElemSulNo==NULL || tpElemSudesteNo==NULL){
							return TAB_CondRetFaltouMemoria ;
						}
						tpMat->pNoIndLinha->pNoSul->pNoSudeste  = tpElemSudesteNo;
						tpMat->pNoIndLinha->pNoSul->pNoSul      = tpElemSulNo;

						tpMat->pNoCorr      = tpMat->pNoIndLinha->pNoSul;
							/* seta como corrente */

						tpMat->pNoIndLinha  = tpMat->pNoIndLinha->pNoSul;
							/* seta como indice da linha */

					}
					if(i==numElementos && (j!=numElementos || j!=0)){
			    
						tpMat->pNoCorr->pNoLeste->pNoLeste    = tpMat->pNoCorr->pNoNordeste->pNoSudeste;
						tpMat->pNoCorr->pNoLeste->pNoNordeste = tpMat->pNoCorr->pNoNordeste->pNoLeste;
						tpMat->pNoCorr->pNoLeste->pNoNorte    = tpMat->pNoCorr->pNoNordeste;
						tpMat->pNoCorr->pNoLeste->pNoNoroeste = tpMat->pNoCorr->pNoNorte;
						tpMat->pNoCorr->pNoLeste->pNoOeste    = tpMat->pNoCorr;

						tpMat->pNoCorr  = tpMat->pNoCorr->pNoLeste;
							/* seta como corrente */

					}
					if(j==numElementos && (i!=numElementos || i!=0)){

						tpMat->pNoCorr->pNoLeste->pNoNorte     = tpMat->pNoCorr->pNoNordeste;
						tpMat->pNoCorr->pNoLeste->pNoSul       = tpMat->pNoCorr->pNoSudeste;
						tpMat->pNoCorr->pNoLeste->pNoSudoeste  = tpMat->pNoCorr->pNoSul;
						tpMat->pNoCorr->pNoLeste->pNoOeste     = tpMat->pNoCorr;
						tpMat->pNoCorr->pNoLeste->pNoNoroeste  = tpMat->pNoCorr->pNoNorte;

						tpMat->pNoCorr  = tpMat->pNoCorr->pNoLeste;
							/* seta como corrente */

					}

				}
					/* 8 adjacentes */
				else{

						tpMat->pNoCorr->pNoLeste->pNoNorte     = tpMat->pNoCorr->pNoNordeste;
						tpMat->pNoCorr->pNoLeste->pNoNordeste  = tpMat->pNoCorr->pNoNordeste->pNoLeste;
						tpMat->pNoCorr->pNoLeste->pNoLeste     = tpMat->pNoCorr->pNoNordeste->pNoSudeste;
						tpMat->pNoCorr->pNoLeste->pNoSul       = tpMat->pNoCorr->pNoSudeste;
						tpMat->pNoCorr->pNoLeste->pNoSudoeste  = tpMat->pNoCorr->pNoSul;
						tpMat->pNoCorr->pNoLeste->pNoOeste     = tpMat->pNoCorr;
						tpMat->pNoCorr->pNoLeste->pNoNoroeste  = tpMat->pNoCorr->pNoNorte;
						tpElemSudesteNo   = CriarNo( pGrafo , IdVertices[(numElementos * (i+1)) + ((j+1)+(i+1))]);
						if(tpElemSudesteNo==NULL){
							return TAB_CondRetFaltouMemoria ;
						}
						tpMat->pNoCorr->pNoLeste->pNoSudeste   = tpElemSudesteNo;


						tpMat->pNoCorr = tpMat->pNoCorr->pNoLeste;
							/* seta como corrente */

				}
		}

	}

	 
	return TAB_CondRetOK;

}


/***** CRIAR NO RAIZ ****/

TAB_tpCondRet CriarNoRaiz( TAB_tpEstCasa * tpMat, GRA_tppGrafo pGrafo , int numElementos )
{

    TAB_tpCondRet CondRet ;

	if ( tpMat->pNoRaiz == NULL )
    {

		CondRet = PreparaEstruturaMatriz(tpMat, pGrafo, numElementos);		
				/* Criar a estrutura das casas de acordo com a quantidade elementos passados */

		if ( CondRet != MAT_CondRetOK )
        {
        return CondRet ;
        } /* if */


        return TAB_CondRetOK  ;
    } /* if */

	return TAB_CondRetFaltouMemoria ;

} 


/***** CRIAR NO *****/

tpElemCasa * CriarNo( GRA_tppGrafo pGrafo , char * Id )
   {
	  GRA_tppVerGrafo * pVertice;

      tpElemCasa * pNoMatriz ;
	  
	  GRA_CriaVerticeGrafo(pGrafo , NULL , Id , ExcluirValorNo);
	 
      pNoMatriz = ( tpElemCasa * ) malloc( sizeof( tpElemCasa )) ;
      if ( pNoMatriz == NULL )
      {
         return NULL ;
      } /* if */

	  GRA_ObterVertice(pGrafo, (void**)&pVertice) ;

	  pNoMatriz->pVertice    = *pVertice;
	  pNoMatriz->pNoLeste    = NULL ;
	  pNoMatriz->pNoNordeste = NULL ;
	  pNoMatriz->pNoNoroeste = NULL ;
	  pNoMatriz->pNoNorte    = NULL ;
	  pNoMatriz->pNoOeste    = NULL ;
	  pNoMatriz->pNoSudeste  = NULL ;
	  pNoMatriz->pNoSudoeste = NULL ;
	  pNoMatriz->pNoSul      = NULL ;

      return pNoMatriz ;

   } /* Fim função: ARV Criar nó da árvore */


/***** CAMINHO TABULEIRO *****/

TAB_tpCondRet TAB_IrNoNorte(TAB_tpEstCasa * tpTab){

	  if ( tpTab == NULL )
      {
		  return TAB_CondRetTabuleiroNulo;
      } /* if */

      if ( tpTab->pNoCorr == NULL )
      {
         return TAB_CondRetCorrenteNulo ;
      } /* if */

	  if ( tpTab->pNoCorr->pNoNorte == NULL )
      {
		  return TAB_CondRetNaoAchou ;
      } /* if */

      tpTab->pNoCorr = tpTab->pNoCorr->pNoNorte ;

      return TAB_CondRetOK ;

} /* Fim do IrNoNorte */

   
TAB_tpCondRet TAB_IrNoNordeste(TAB_tpEstCasa * tpTab){

	  if ( tpTab == NULL )
      {
         return TAB_CondRetTabuleiroNulo ;
      } /* if */

      if ( tpTab->pNoCorr == NULL )
      {
         return TAB_CondRetCorrenteNulo ;
      } /* if */

	  if ( tpTab->pNoCorr->pNoNordeste == NULL )
      {
         return TAB_CondRetNaoAchou ;
      } /* if */

      tpTab->pNoCorr = tpTab->pNoCorr->pNoNordeste ;

      return TAB_CondRetOK ;

} /* Fim do IrNoNordeste */

   
TAB_tpCondRet TAB_IrNoLeste(TAB_tpEstCasa * tpTab){

	  if ( tpTab == NULL )
      {
         return TAB_CondRetTabuleiroNulo ;
      } /* if */

      if ( tpTab->pNoCorr == NULL )
      {
         return TAB_CondRetCorrenteNulo ;
      } /* if */

	  if ( tpTab->pNoCorr->pNoLeste == NULL )
      {
         return TAB_CondRetNaoAchou ;
      } /* if */

	  tpTab->pNoCorr = tpTab->pNoCorr->pNoLeste ;

      return TAB_CondRetOK ;

} /* Fim do TAB IrNoLeste */

   
TAB_tpCondRet TAB_IrNoSudeste(TAB_tpEstCasa * tpTab){

	  if ( tpTab == NULL )
      {
         return TAB_CondRetTabuleiroNulo ;
      } /* if */

      if ( tpTab->pNoCorr == NULL )
      {
         return TAB_CondRetCorrenteNulo ;
      } /* if */

	  if ( tpTab->pNoCorr->pNoSudeste == NULL )
      {
         return TAB_CondRetNaoAchou ;
      } /* if */

      tpTab->pNoCorr = tpTab->pNoCorr->pNoSudeste ;

      return TAB_CondRetOK ;

} /* Fim do TAB IrNoSudeste */

   
TAB_tpCondRet TAB_IrNoSul(TAB_tpEstCasa * tpTab){

	  if ( tpTab == NULL )
      {
         return TAB_CondRetTabuleiroNulo ;
      } /* if */

      if ( tpTab->pNoCorr == NULL )
      {
         return TAB_CondRetCorrenteNulo ;
      } /* if */

	  if ( tpTab->pNoCorr->pNoSul == NULL )
      {
         return TAB_CondRetNaoAchou ;
      } /* if */

      tpTab->pNoCorr = tpTab->pNoCorr->pNoSul ;

      return TAB_CondRetOK ;

} /* Fim do TAB IrNoSul */

   
TAB_tpCondRet TAB_IrNoSudoeste(TAB_tpEstCasa * tpTab){

	  if ( tpTab == NULL )
      {
         return TAB_CondRetTabuleiroNulo ;
      } /* if */

      if ( tpTab->pNoCorr == NULL )
      {
         return TAB_CondRetCorrenteNulo ;
      } /* if */

	  if ( tpTab->pNoCorr->pNoSudoeste == NULL )
      {
         return TAB_CondRetNaoAchou ;
      } /* if */

      tpTab->pNoCorr = tpTab->pNoCorr->pNoSudoeste ;

      return TAB_CondRetOK ;

} /* Fim do TAB IrNoSudoeste */

   
TAB_tpCondRet TAB_IrNoOeste(TAB_tpEstCasa * tpTab){

	  if ( tpTab == NULL )
      {
         return TAB_CondRetTabuleiroNulo ;
      } /* if */

      if ( tpTab->pNoCorr == NULL )
      {
         return TAB_CondRetCorrenteNulo ;
      } /* if */

	  if ( tpTab->pNoCorr->pNoOeste == NULL )
      {
         return TAB_CondRetNaoAchou ;
      } /* if */

      tpTab->pNoCorr = tpTab->pNoCorr->pNoOeste ;


      return TAB_CondRetOK ;

} /* Fim do TAB IrNoOeste */

   
TAB_tpCondRet TAB_IrNoNoroeste(TAB_tpEstCasa * tpTab){

	  if ( tpTab == NULL )
      {
         return TAB_CondRetTabuleiroNulo ;
      } /* if */

      if ( tpTab->pNoCorr == NULL )
      {
         return TAB_CondRetCorrenteNulo ;
      } /* if */

	  if ( tpTab->pNoCorr->pNoNoroeste == NULL )
      {
         return TAB_CondRetNaoAchou ;
      } /* if */

      tpTab->pNoCorr = tpTab->pNoCorr->pNoNoroeste ;

      return TAB_CondRetOK ;

} /* Fim do TAB IrNoNoroeste */


void ExcluirValorNo( void * pValor )
{

    free( ( void * ) pValor ) ;

}

/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/

