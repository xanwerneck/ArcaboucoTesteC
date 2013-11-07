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


/***** Protótipos das funções encapsuladas no módulo *****/

   static void ExcluirInfo ( void * pValor );
   
   static void ExcluirPeca( void * pPeca );

   static TAB_tpCondRet PreparaEstruturaMatriz( GRA_tppGrafo pGrafo  , int numElementos ) ;

   static GRA_tppVerGrafo CriarNo( GRA_tppGrafo pGrafo , char * Id ) ;

   static void ExcluirValorNo( void * pValor );

/*****  Código das funções exportadas pelo módulo  *****/


TAB_tpCondRet TAB_CriarTabuleiro( TAB_tppTabuleiro * pTabuleiro ){

	GRA_tppGrafo     pGrafo;
	LIS_tppLista     ListaPecas;
	TAB_tppTabuleiro mTab;

	mTab = ( TAB_tppTabuleiro ) malloc ( sizeof ( TAB_tpTabuleiro ) );
			/* Malloc para gerar um ponteiro de matriz */
		   
	if(mTab == NULL)
	{
		return TAB_CondRetFaltouMemoria ;
	} /* if */

	GRA_CriarGrafo( &pGrafo , ExcluirInfo);

	PreparaEstruturaMatriz( pGrafo , 8);

	LIS_CriarLista(ExcluirPeca , &ListaPecas);

	mTab->tpGrafo      = pGrafo;

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

	if(pTabuleiro == NULL){
		return TAB_CondRetTabuleiroNulo;
	}

	GrafRet = GRA_SetarCorrente(pTabuleiro->tpGrafo , NomeCasa);

	return TAB_CondRetOK;

}

TAB_tpCondRet TAB_IrInicioCasas( TAB_tppTabuleiro pTabuleiro  )
{

	if(pTabuleiro == NULL){

		return TAB_CondRetTabuleiroNulo;

	}

	GrafRet = GRA_IrInicio(pTabuleiro->tpGrafo);

	if(GrafRet == GRA_CondRetOK){

		return TAB_CondRetOK;

	}
	
	return TAB_CondRetNaoAchou;
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
	JOG_tppPecaJogo pPeca; 

	if(pTabuleiro == NULL){
		return TAB_CondRetTabuleiroNulo;
	}
	
	GRA_PegaConteudo(pTabuleiro->tpGrafo , (void**)&pPeca);

	*pConteudo = pPeca;

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

/***** ARESTA ******/
TAB_tpCondRet TAB_IrInicioArestasCorrente(TAB_tppTabuleiro pTabuleiro)
{
	GRA_IrInicioAresta(pTabuleiro->tpGrafo);

	return TAB_CondRetOK;
}

TAB_tpCondRet TAB_ObterVerticeAresta(TAB_tppTabuleiro pTabuleiro  , void ** Vertice , char * Aresta)
{
	GRA_tppVerGrafo pVertice = NULL;

	if(pTabuleiro==NULL){
		return TAB_CondRetTabuleiroNulo;
	} /* if */
	
	GRA_ObterArestaVertice(pTabuleiro->tpGrafo , (void**)&pVertice , Aresta);

	*Vertice = pVertice;

	return TAB_CondRetOK;

}

TAB_tpCondRet TAB_ObterVerticeCorrente(TAB_tppTabuleiro pTabuleiro , void ** Id)
{

	char * IdVert;

	GRA_BuscaIdVertice(pTabuleiro->tpGrafo , (char**)&IdVert);

	*Id = IdVert;

	return TAB_CondRetOK;
}

TAB_tpCondRet TAB_AvancarArestaCorrente(TAB_tppTabuleiro pTabuleiro , int val)
{
	GRA_AvancarArestaVertice(pTabuleiro->tpGrafo , val);

	return TAB_CondRetOK;
}

TAB_tpCondRet TAB_NumElementosArestasCorrente(TAB_tppTabuleiro pTabuleiro , int * Num)
{

	GRA_NumeroArestaVertice(pTabuleiro->tpGrafo , Num);

	return TAB_CondRetOK;
}

/***** ARESTA ******/

void ExcluirInfo ( void * pValor )
{

    free( ( void * ) pValor ) ;

} /* Fim função: TST -Excluir informacao */

void ExcluirPeca( void * pPeca )
{

	free ( (void *) pPeca);

} /* Fim função: TST -Excluir peca */


/**** Novas funcoes da estrutura CASA ******/


/***** PREPARA ESTRUTURA TABULEIRO *****/

TAB_tpCondRet PreparaEstruturaMatriz( GRA_tppGrafo pGrafo  , int numElementos ){

	int i = 0, j = 0;
	
	char * IdTmp;

	char * IdVertices[64] = 
	{
		"A1","A2","A3","A4","A5","A6","A7","A8","B1","B2","B3","B4","B5","B6","B7","B8","C1","C2","C3","C4","C5","C6","C7","C8","D1","D2","D3","D4","D5","D6","D7","D8","E1","E2","E3","E4","E5","E6","E7","E8","F1","F2","F3","F4","F5","F6","F7","F8","G1","G2","G3","G4","G5","G6","G7","G8","H1","H2","H3","H4","H5","H6","H7","H8"
	};
	
	GRA_tppVerGrafo tpElem			 = CriarNo( pGrafo , IdVertices[0] );

	if(tpElem == NULL)
	{
		return TAB_CondRetFaltouMemoria ;
	}
	
	numElementos = numElementos - 1;

	

	for(i=0;i<=numElementos;i++){

		for(j=0;j<=numElementos;j++){	

			
					/* testa a condicão para 3 adjacentes */
				if((i==0 || i==numElementos) && (j==0 || j==numElementos)){

					if(i==0 && j==0){


						CriarNo( pGrafo , IdVertices[1] );
						CriarNo( pGrafo , IdVertices[8]);
						CriarNo( pGrafo , IdVertices[9] );

						GRA_CriarAresta(IdVertices[0],IdVertices[1],pGrafo,"LESTE");
						GRA_CriarAresta(IdVertices[0],IdVertices[8],pGrafo,"SUL");
						GRA_CriarAresta(IdVertices[0],IdVertices[9],pGrafo,"SUDESTE");



					}
					if(i==0 && j==numElementos){

						GRA_AvancarCorrenteVert(pGrafo , 1);

						GRA_BuscaIdVertice(pGrafo , (char**)&IdTmp);

						GRA_CriarAresta(IdTmp,IdVertices[j-1],pGrafo,"OESTE");
						GRA_CriarAresta(IdTmp,IdVertices[(j+numElementos) + 1],pGrafo,"SUL");
						GRA_CriarAresta(IdTmp,IdVertices[j+numElementos],pGrafo,"SUDOESTE");


					}
					if(i==numElementos && j==0){
						
						GRA_AvancarCorrenteVert(pGrafo , 1);

						GRA_BuscaIdVertice(pGrafo , (char**)&IdTmp);

						GRA_CriarAresta(IdTmp,IdVertices[(i * numElementos)-1],pGrafo,"NORTE");
						GRA_CriarAresta(IdTmp,IdVertices[i * numElementos],pGrafo,"NORDESTE");
						GRA_CriarAresta(IdTmp,IdVertices[(i * (numElementos + 1))+1],pGrafo,"LESTE");


					}
					if(i==numElementos && j==numElementos){
						
						GRA_AvancarCorrenteVert(pGrafo , 1);

						GRA_BuscaIdVertice(pGrafo , (char**)&IdTmp);

						GRA_CriarAresta(IdTmp,IdVertices[(i * (numElementos + 1))-1],pGrafo,"NORTE");
						GRA_CriarAresta(IdTmp,IdVertices[(i * (numElementos + 1))-2],pGrafo,"NOROESTE");
						GRA_CriarAresta(IdTmp,IdVertices[((numElementos + 1) * (numElementos + 1))-2],pGrafo,"OESTE");
					}

				}

					 /* testa a condição para 5 adjacentes */
				else if(i==0 || i==numElementos || j==0 || j==numElementos){


					if(i==0 && (j!=numElementos || j!=0)){
						
						GRA_AvancarCorrenteVert(pGrafo , 1);

						GRA_BuscaIdVertice(pGrafo , (char**)&IdTmp);

						GRA_CriarAresta(IdTmp,IdVertices[j-1],pGrafo,"OESTE");
						GRA_CriarAresta(IdTmp,IdVertices[(j+numElementos) + 1],pGrafo,"SUL");
						GRA_CriarAresta(IdTmp,IdVertices[(j+numElementos)],pGrafo,"SUDOESTE");
						
						CriarNo( pGrafo , IdVertices[j+1]);                    /* Cria no leste */
						CriarNo( pGrafo , IdVertices[(j + numElementos) + 2]); /* Cria no sudeste */

						GRA_CriarAresta(IdTmp,IdVertices[j+1],pGrafo,"LESTE");
						GRA_CriarAresta(IdTmp,IdVertices[(j + numElementos) + 2],pGrafo,"SUDESTE");


					}

					if(j==0 && (i!=numElementos || i!=0)){

						GRA_AvancarCorrenteVert(pGrafo , 1);

						GRA_BuscaIdVertice(pGrafo , (char**)&IdTmp);

						GRA_CriarAresta(IdTmp,IdVertices[(i - 1) * (numElementos + 1)],pGrafo,"NORTE");
						GRA_CriarAresta(IdTmp,IdVertices[((i - 1) * (numElementos + 1)) + 1],pGrafo,"NORDESTE");
						GRA_CriarAresta(IdTmp,IdVertices[(i * (numElementos + 1)) + 1],pGrafo,"LESTE");
						
						CriarNo( pGrafo , IdVertices[(numElementos * (i+1)) + (i+1)]); /* Cria sul */
						CriarNo( pGrafo , IdVertices[(numElementos * (i+1)) + (i+2)]); /* Cria sudeste */

						GRA_CriarAresta(IdTmp,IdVertices[(numElementos * (i+1)) + (i+1)],pGrafo,"SUL");
						GRA_CriarAresta(IdTmp,IdVertices[(numElementos * (i+1)) + (i+2)],pGrafo,"SUDESTE");


						
					}
					if(i==numElementos && (j!=numElementos || j!=0)){

						GRA_AvancarCorrenteVert(pGrafo , 1);

						GRA_BuscaIdVertice(pGrafo , (char**)&IdTmp);

						GRA_CriarAresta(IdTmp,IdVertices[(i * (numElementos + 1) + (j+1))],pGrafo,"LESTE");
						GRA_CriarAresta(IdTmp,IdVertices[((i - 1) * (numElementos + 1) + (j+1))],pGrafo,"NORDESTE");
						GRA_CriarAresta(IdTmp,IdVertices[((i - 1) * (numElementos + 1) + j)],pGrafo,"NORTE");
						GRA_CriarAresta(IdTmp,IdVertices[((i - 1) * (numElementos + 1) + (j-1))],pGrafo,"NOROESTE");
						GRA_CriarAresta(IdTmp,IdVertices[(i * (numElementos + 1) + (j-1))],pGrafo,"OESTE");

					}
					if(j==numElementos && (i!=numElementos || i!=0)){

						GRA_AvancarCorrenteVert(pGrafo , 1);

						GRA_BuscaIdVertice(pGrafo , (char**)&IdTmp);

						GRA_CriarAresta(IdTmp,IdVertices[(i * (numElementos + 1) )- 1],pGrafo,"NORTE");
						GRA_CriarAresta(IdTmp,IdVertices[((i+1) * (numElementos + 1) )+numElementos],pGrafo,"SUL");
						GRA_CriarAresta(IdTmp,IdVertices[((i+1) * (numElementos + 1) )+(numElementos - 1)],pGrafo,"SUDOESTE");
						GRA_CriarAresta(IdTmp,IdVertices[(i * (numElementos + 1) )+(numElementos-1)],pGrafo,"OESTE");
						GRA_CriarAresta(IdTmp,IdVertices[(i * (numElementos + 1) )- 2],pGrafo,"NOROESTE");

					}

				}
					/* 8 adjacentes */
				else{

						GRA_AvancarCorrenteVert(pGrafo , 1);

						GRA_BuscaIdVertice(pGrafo , (char**)&IdTmp);

						GRA_CriarAresta(IdTmp,IdVertices[((i-1) * (numElementos + 1)) + j],pGrafo,"NORTE");
						GRA_CriarAresta(IdTmp,IdVertices[((i+1) * (numElementos + 1)) + j],pGrafo,"SUL");
						GRA_CriarAresta(IdTmp,IdVertices[(i * (numElementos + 1)) + (j+1)],pGrafo,"LESTE");
						GRA_CriarAresta(IdTmp,IdVertices[(i * (numElementos + 1)) + (j-1)],pGrafo,"OESTE");
						GRA_CriarAresta(IdTmp,IdVertices[((i-1) * (numElementos + 1)) + (j+1)],pGrafo,"NORDESTE");
						GRA_CriarAresta(IdTmp,IdVertices[((i-1) * (numElementos + 1)) + (j-1)],pGrafo,"NOROESTE");
						GRA_CriarAresta(IdTmp,IdVertices[((i+1) * (numElementos + 1)) + (j-1)],pGrafo,"SUDOESTE");

						CriarNo( pGrafo , IdVertices[((i+1) * (numElementos + 1)) + (j+1)]); /* Cria Sudeste */

						GRA_CriarAresta(IdTmp, IdVertices[((i+1) * (numElementos + 1)) + (j+1)],pGrafo,"SUDESTE");


				}
		}

	}

	 
	return TAB_CondRetOK;

}


/***** CRIAR NO *****/

GRA_tppVerGrafo CriarNo( GRA_tppGrafo pGrafo , char * Id )
   {
	  GRA_tppVerGrafo pVertice;
	  
	  GRA_CriaVerticeGrafo(pGrafo , NULL , Id , ExcluirValorNo);

	  GRA_ObterVertice(pGrafo, (void**)&pVertice) ;
	  
      return pVertice ;

   } /* Fim função: ARV Criar nó da árvore */




void ExcluirValorNo( void * pValor )
{

    free( ( void * ) pValor ) ;

}

/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/

