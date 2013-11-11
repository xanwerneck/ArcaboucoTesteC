/***************************************************************************
*
*  $MCD Modulo de definicao: TAB  Tabuleiro de Xadrez
*
*  Arquivo gerado:              TABULEIRO.C
*  Letras identificadoras:      TAB
*
*  Projeto: INF 1301 - Verificador de Xeque-mate
*  Gestor:  Flavio Bevilacqua
*  Autores: afv:  aw - Alexandre Werneck
*                 fr - Fernanda C Ribeiro
*                 vo - Vinicius de Luiz de Oliveira
*
*  $HA Historico de evolucao:
*     Versao  Autor    Data     Observacoes
*     Y       afv   xx/xx/2013  finalizacao do desenvolvimento do modulo
*     1       afv   19/out/2013 inicio do desenvolvimento do modulo
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
*  $TC Tipo de dados: TAB Descritor do tabuleiro
*
*  $ED Descricao do tipo
*     Contem referencia para estrutura do tipo grafo que representa o 
*      tabuleiro de xadrez vazio e referencia para a estrutura de pecas 
*      que estao no tabuleiro.
*
***********************************************************************/

   typedef struct TAB_tagTabuleiro {

         GRA_tppGrafo   tpGrafo;
		/* Ponteiro para estrutura de grafo que representa o 
		    tabuleiro de xadrez */

		 LIS_tppLista   pListaPecas;
		/* Ponteiro para estrutura de lista de pecas que representa as 
		    pecas que serao inseridas no tabuleiro. */

   } TAB_tpTabuleiro ;


/************* Funcoes encapsuladas no modulo *************************/

   /* Funcao libera espaco alocado na memoria para o elemento do 
      paramentro */
   static void ExcluirInfo ( void * pValor );

   /* Funcao libera espaco alocado na memoria para o elemento do 
      paramentro */
   static void ExcluirPeca( void * pPeca );

   /* Funcao cria tipo grafo como uma matriz nxn para inicializar o 
      tabuleiro */
   static TAB_tpCondRet PreparaEstruturaMatriz( GRA_tppGrafo pGrafo  , int numElementos ) ;

   /* Funcao cria no vazio de vertice de grafo */
   static GRA_tppVerGrafo CriarNo( GRA_tppGrafo pGrafo , char * Id ) ;

   /* Funcao libera espaco alocado na memoria para o elemento do 
      paramentro */
   static void ExcluirValorNo( void * pValor );

/************* Codigo das funcoes exportadas pelo modulo ******************/

/************************************************************************
*
*  Funcao: TAB  &Criar tabuleiro
*  ****/

TAB_tpCondRet TAB_CriarTabuleiro( TAB_tppTabuleiro * pTabuleiro ){

	GRA_tppGrafo     pGrafo;
	LIS_tppLista     ListaPecas;
	TAB_tppTabuleiro mTab;

	mTab = ( TAB_tppTabuleiro ) malloc ( sizeof ( TAB_tpTabuleiro ) );
			/* Malloc para gerar um ponteiro de tabuleiro */		   
	if(mTab == NULL)
	{
		return TAB_CondRetFaltouMemoria ;
	} /* if */

	GrafRet = GRA_CriarGrafo( &pGrafo , ExcluirInfo);
	if(GrafRet == GRA_CondRetFaltouMemoria)
	{
		return TAB_CondRetFaltouMemoria ;
	} /* if */


	PreparaEstruturaMatriz( pGrafo , 8);

	ListaRet = LIS_CriarLista(ExcluirPeca , &ListaPecas);
	if(GrafRet == LIS_CondRetFaltouMemoria)
	{
		return TAB_CondRetFaltouMemoria ;
	} /* if */


	mTab->tpGrafo      = pGrafo;

	mTab->pListaPecas  = ListaPecas;

	(*pTabuleiro) = (TAB_tpTabuleiro *) malloc (sizeof(TAB_tppTabuleiro));	
	if( (*pTabuleiro) == NULL)
	{
		return TAB_CondRetFaltouMemoria ;
	} /* if */

	(*pTabuleiro) = mTab ;

	return TAB_CondRetOK;

} /* Fim funcao: TAB &Criar tabuleiro */

/************************************************************************
*
*  Funcao: TAB  &Setar corrente
*  ****/

TAB_tpCondRet TAB_SetarCorrente( TAB_tppTabuleiro pTabuleiro , char * NomeCasa )
{

	if(pTabuleiro == NULL){
		return TAB_CondRetTabuleiroNulo;
	} /* if */

	GrafRet = GRA_SetarCorrente(pTabuleiro->tpGrafo , NomeCasa);

	if (GrafRet == GRA_CondRetListaNula){
		return TAB_CondRetTabuleiroListaNula ;
	} /* if */

	return TAB_CondRetOK;

} /* Fim funcao: TAB &Setar corrente */

/************************************************************************
*
*  Funcao: TAB  &Ir inicio das casas
*  ****/

TAB_tpCondRet TAB_IrInicioCasas( TAB_tppTabuleiro pTabuleiro  )
{

	if(pTabuleiro == NULL){
		return TAB_CondRetTabuleiroNulo;
	} /* if */

	GrafRet = GRA_IrInicio(pTabuleiro->tpGrafo);
	if(GrafRet == GRA_CondRetOK){
		return TAB_CondRetOK;
	} /* if */
	
	return TAB_CondRetNaoAchou;

} /* Fim funcao: TAB &Ir inicio das casas */


/************************************************************************
*
*  Funcao: TAB  &Avancar casas
*  ****/
TAB_tpCondRet TAB_AvancarCasas( TAB_tppTabuleiro pTabuleiro , int val )
{
	if(pTabuleiro == NULL){
		return TAB_CondRetTabuleiroNulo;
	} /* if */

	GrafRet = GRA_AvancarCorrenteVert(pTabuleiro->tpGrafo , val);
	if(GrafRet == GRA_CondRetOK){
		return TAB_CondRetOK;
	} /* if */

	return TAB_CondRetFimLista;

} /* Fim funcao: TAB  &Avancar casas */


/************************************************************************
*
*  Funcao: TAB  &Obter conteudo tabuleiro
*  ****/

TAB_tpCondRet TAB_ObterConteudo( TAB_tppTabuleiro pTabuleiro , void ** pConteudo )
{
	JOG_tppPecaJogo pPeca; 

	if(pTabuleiro == NULL){
		return TAB_CondRetTabuleiroNulo;
	} /* if */
	
	GrafRet = GRA_PegaConteudo(pTabuleiro->tpGrafo , (void**)&pPeca);
	if (GrafRet == GRA_CondRetOK){
		*pConteudo = pPeca;
		return TAB_CondRetOK;
	} /* if */

	return TAB_CondRetNaoAchou;

} /* Fim funcao: TAB  &Obter conteudo tabuleiro */


/************************************************************************
*
*  Funcao: TAB  &Inserir conteudo na casa do tabuleiro
*  ****/

TAB_tpCondRet TAB_InserirConteudoCasa(TAB_tppTabuleiro pTabuleiro , void * pPeca)
{
	if(pTabuleiro == NULL){
		return TAB_CondRetTabuleiroNulo;
	} /* if */

	GrafRet = GRA_InsereConteudoVertice(pTabuleiro->tpGrafo , pPeca);

	if(GrafRet == GRA_CondRetOK){
		return TAB_CondRetOK;
	} /* if */

	return TAB_CondRetNaoAchou;

} /* Fim funcao: TAB  &Inserir conteudo na casa do tabuleiro */

/************************************************************************
*
*  Funcao: TAB  &Apresenta tabuleiro
*  ****/
TAB_tpCondRet TAB_ApresentaTabuleiro( TAB_tppTabuleiro pTabuleiro ){

	char * IdVertices[64] = 
	{
		"A1","A2","A3","A4","A5","A6","A7","A8","B1","B2","B3","B4","B5","B6","B7","B8","C1","C2","C3","C4","C5","C6","C7","C8","D1","D2","D3","D4","D5","D6","D7","D8","E1","E2","E3","E4","E5","E6","E7","E8","F1","F2","F3","F4","F5","F6","F7","F8","G1","G2","G3","G4","G5","G6","G7","G8","H1","H2","H3","H4","H5","H6","H7","H8"
	};

	int cont = 0;
	int contador = 0;
	char * id = NULL;
	char * NomeCasa = NULL;
	char NomeNaCasa[10];
	char Time;
	JOG_tppPecaJogo pPecaTab;

	char casas[7] = {'B' , 'C' , 'D' , 'E' , 'F' , 'G' , 'H'};

	GrafRet = GRA_IrInicio(pTabuleiro->tpGrafo);

	puts( "| - || 1 || 2 || 3 || 4 || 5 || 6 || 7 || 8 |" );

	printf( "| A |" );

	while(cont < 64){

		GRA_SetarCorrente(pTabuleiro->tpGrafo , IdVertices[cont]);

		GRA_PegaConteudo (pTabuleiro->tpGrafo , (void**)&pPecaTab);

		if(pPecaTab != NULL){
			JOG_ObterDadosPeca(pPecaTab , (void**)&NomeNaCasa , &Time);
			printf( "|%c-%c|" , NomeNaCasa[0], Time );
		}else{
			printf( "| - |" );
		}
		cont++;
		if((cont % 8) == 0){
			if(contador < 7)
				printf( "\n| %c |" , casas[contador] );
			contador++;
			
		}
		
	}
	
	printf("\n");

	return TAB_CondRetOK;

} /* Fim funcao: TAB  &Apresenta tabuleiro */

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

	/* Caracteristicas das PECAS */
	char NomePeca[MAX_NOME];
	int Diag;
	int Reta;
	int Qtde;


	if(pTabuleiro==NULL){
		return TAB_CondRetTabuleiroNulo;
	}
	if(pTabuleiro->pListaPecas == NULL){
		return TAB_CondRetTabuleiroListaNula;
	}
	
	printf("\n MAPA DE MOVIMENTOS \n");
	ListaRet = LIS_IrInicioLista(pTabuleiro->pListaPecas);

	printf("\n");
	printf("( Em Diagonal e Reta: 1 = Sim | 0 = Nao )\n");
	printf("******************************************************************* \n");

	if(ListaRet == LIS_CondRetListaVazia)
		return TAB_TimeAVazio;
	do{

		LIS_ObterValor(pTabuleiro->pListaPecas , (void**)&pPeca);

		PEC_ObterDadosTipoPeca (pPeca , (void**)&NomePeca , &Diag , &Reta , &Qtde);

		printf("Nome Peca: %s Diagonal => %d Reta => %d Quantidade => %d \n" , &NomePeca , Diag , Reta , Qtde );

		ListaRet = LIS_AvancarElementoCorrente(pTabuleiro->pListaPecas , 1);


	}while(ListaRet != LIS_CondRetFimLista);

	printf("******************************************************************* \n");
	printf("\n");
	
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
	PEC_tppPeca tpPeca;
	if(pTabuleiro==NULL){
		return TAB_CondRetTabuleiroNulo;
	}

	ListaRet = LIS_ObterValor(pTabuleiro->pListaPecas , (void**)&tpPeca);

	*pPeca = tpPeca;


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

TAB_tpCondRet TAB_FinalizarPartida(TAB_tppTabuleiro pTabuleiro)
{
	PEC_tppPeca pPeca;
	if(pTabuleiro==NULL){
		return TAB_CondRetTabuleiroNulo;
	} /* if */

	ListaRet = LIS_IrInicioLista(pTabuleiro->pListaPecas);
	do{
		LIS_ObterValor(pTabuleiro->pListaPecas , (void**)&pPeca);

		PEC_DestroiPeca(pPeca);

		ListaRet = LIS_AvancarElementoCorrente(pTabuleiro->pListaPecas , 1);

	}while(ListaRet != LIS_CondRetFimLista);

	free(pTabuleiro->pListaPecas);

	GRA_DestruirGrafo(pTabuleiro->tpGrafo);

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
	GRA_tppVerGrafo pVert = NULL;

	if(pTabuleiro==NULL){
		return TAB_CondRetTabuleiroNulo;
	} /* if */
	
	GRA_ObterArestaVertice(pTabuleiro->tpGrafo , (void**)&pVert , Aresta);
	
	*Vertice = pVert;

	return TAB_CondRetOK;

}

TAB_tpCondRet TAB_PecaConteudoPeloVertice(void * Vertice  , void ** VertConteudo)
{

	if(Vertice==NULL){
		return TAB_CondRetTabuleiroNulo;
	} /* if */
	
	GRA_PegaConteudoPeloVertice(Vertice , (void**)&VertConteudo);

	return TAB_CondRetOK;
}

TAB_tpCondRet TAB_ObterConteudoVertice(TAB_tppTabuleiro pTabuleiro  , void ** VertConteudo)
{
	JOG_tppPecaJogo pPeca = NULL;

	if(pTabuleiro==NULL){
		return TAB_CondRetTabuleiroNulo;
	} /* if */

	GRA_PegaConteudoCorrente(pTabuleiro->tpGrafo , (void**)&pPeca);

	*VertConteudo = pPeca;

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


TAB_tpCondRet TAB_ObterVerticeCorrente(TAB_tppTabuleiro pTabuleiro , char ** Id)
{
	char * Busca;

	GRA_BuscaIdVertice(pTabuleiro->tpGrafo , &Busca);

	*Id = Busca;

	return TAB_CondRetOK;
}

/***** ARESTA ******/

void ExcluirInfo ( void * pValor )
{

    free( ( void * ) pValor ) ;

} /* Fim funcao: TST -Excluir informacao */

void ExcluirPeca( void * pPeca )
{

	free ( (void *) pPeca);

} /* Fim funcao: TST -Excluir peca */


/**** Novas funcoes da estrutura CASA ******/


/***** PREPARA ESTRUTURA TABULEIRO *****/

TAB_tpCondRet PreparaEstruturaMatriz( GRA_tppGrafo pGrafo  , int numElementos ){

	int i = 0, j = 0;
	
	char * IdVertices[64] = 
	{
		"A1","A2","A3","A4","A5","A6","A7","A8","B1","B2","B3","B4","B5","B6","B7","B8","C1","C2","C3","C4","C5","C6","C7","C8","D1","D2","D3","D4","D5","D6","D7","D8","E1","E2","E3","E4","E5","E6","E7","E8","F1","F2","F3","F4","F5","F6","F7","F8","G1","G2","G3","G4","G5","G6","G7","G8","H1","H2","H3","H4","H5","H6","H7","H8"
	};
	
	GRA_tppVerGrafo tpElem			 = CriarNo( pGrafo , IdVertices[0] );
	if(tpElem == NULL)
	{
		return TAB_CondRetFaltouMemoria ;
	} /* if */
	
	numElementos = numElementos - 1;

	

	for(i=0;i<=numElementos;i++){

		for(j=0;j<=numElementos;j++){	

			
					/* testa a condicao para 3 adjacentes */
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
						
						GRA_CriarAresta(IdVertices[j],IdVertices[j-1],pGrafo,"OESTE");
						GRA_CriarAresta(IdVertices[j],IdVertices[(j+numElementos) + 1],pGrafo,"SUL");
						GRA_CriarAresta(IdVertices[j],IdVertices[j+numElementos],pGrafo,"SUDOESTE");

					}
					if(i==numElementos && j==0){
						GRA_AvancarCorrenteVert(pGrafo , 1);

						GRA_CriarAresta(IdVertices[(i *(numElementos+1))],IdVertices[(i * numElementos)-1],pGrafo,"NORTE");
						GRA_CriarAresta(IdVertices[(i *(numElementos+1))],IdVertices[i * numElementos],pGrafo,"NORDESTE");
						GRA_CriarAresta(IdVertices[(i *(numElementos+1))],IdVertices[(i * (numElementos + 1))+1],pGrafo,"LESTE");


					}
					if(i==numElementos && j==numElementos){

						GRA_CriarAresta(IdVertices[((numElementos+1)*(numElementos+1)) - 1],IdVertices[(i * (numElementos + 1))-1],pGrafo,"NORTE");
						GRA_CriarAresta(IdVertices[((numElementos+1)*(numElementos+1)) - 1],IdVertices[(i * (numElementos + 1))-2],pGrafo,"NOROESTE");
						GRA_CriarAresta(IdVertices[((numElementos+1)*(numElementos+1)) - 1],IdVertices[((numElementos + 1) * (numElementos + 1))-2],pGrafo,"OESTE");


					}

				}

					 /* testa a condicao para 5 adjacentes */
				else if(i==0 || i==numElementos || j==0 || j==numElementos){


					if(i==0 && (j!=numElementos || j!=0)){
						GRA_AvancarCorrenteVert(pGrafo , 1);

						GRA_CriarAresta(IdVertices[j],IdVertices[j-1],pGrafo,"OESTE");
						GRA_CriarAresta(IdVertices[j],IdVertices[(j+numElementos) + 1],pGrafo,"SUL");
						GRA_CriarAresta(IdVertices[j],IdVertices[(j+numElementos)],pGrafo,"SUDOESTE");
						
						CriarNo( pGrafo , IdVertices[j+1]);                    /* Cria no leste */
						CriarNo( pGrafo , IdVertices[(j + numElementos) + 2]); /* Cria no sudeste */

						GRA_CriarAresta(IdVertices[j],IdVertices[j+1],pGrafo,"LESTE");
						GRA_CriarAresta(IdVertices[j],IdVertices[(j + numElementos) + 2],pGrafo,"SUDESTE");


					}

					if(j==0 && (i!=numElementos || i!=0)){
						GRA_AvancarCorrenteVert(pGrafo , 1);

						GRA_CriarAresta(IdVertices[i * (numElementos + 1)],IdVertices[(i - 1) * (numElementos + 1)],pGrafo,"NORTE");
						GRA_CriarAresta(IdVertices[i * (numElementos + 1)],IdVertices[((i - 1) * (numElementos + 1)) + 1],pGrafo,"NORDESTE");
						GRA_CriarAresta(IdVertices[i * (numElementos + 1)],IdVertices[(i * (numElementos + 1)) + 1],pGrafo,"LESTE");
						
						CriarNo( pGrafo , IdVertices[(numElementos * (i+1)) + (i+1)]); /* Cria sul */
						CriarNo( pGrafo , IdVertices[(numElementos * (i+1)) + (i+2)]); /* Cria sudeste */

						GRA_CriarAresta(IdVertices[i * (numElementos + 1)],IdVertices[(numElementos * (i+1)) + (i+1)],pGrafo,"SUL");
						GRA_CriarAresta(IdVertices[i * (numElementos + 1)],IdVertices[(numElementos * (i+1)) + (i+2)],pGrafo,"SUDESTE");


						
					}
					if(i==numElementos && (j!=numElementos || j!=0)){
						GRA_AvancarCorrenteVert(pGrafo , 1);

						GRA_CriarAresta(IdVertices[(i * (i + 1) + j)],IdVertices[(i * (numElementos + 1) + (j+1))],pGrafo,"LESTE");
						GRA_CriarAresta(IdVertices[(i * (i + 1) + j)],IdVertices[((i - 1) * (numElementos + 1) + (j+1))],pGrafo,"NORDESTE");
						GRA_CriarAresta(IdVertices[(i * (i + 1) + j)],IdVertices[((i - 1) * (numElementos + 1) + j)],pGrafo,"NORTE");
						GRA_CriarAresta(IdVertices[(i * (i + 1) + j)],IdVertices[((i - 1) * (numElementos + 1) + (j-1))],pGrafo,"NOROESTE");
						GRA_CriarAresta(IdVertices[(i * (i + 1) + j)],IdVertices[(i * (numElementos + 1) + (j-1))],pGrafo,"OESTE");

					}
					if(j==numElementos && (i!=numElementos || i!=0)){
						GRA_AvancarCorrenteVert(pGrafo , 1);

						GRA_CriarAresta(IdVertices[((i + 1) * (numElementos + 1)) - 1],IdVertices[(i * (numElementos + 1) )- 1],pGrafo,"NORTE");
						GRA_CriarAresta(IdVertices[((i + 1) * (numElementos + 1)) - 1],IdVertices[((i+1) * (numElementos + 1) )+numElementos],pGrafo,"SUL");
						GRA_CriarAresta(IdVertices[((i + 1) * (numElementos + 1)) - 1],IdVertices[((i+1) * (numElementos + 1) )+(numElementos - 1)],pGrafo,"SUDOESTE");
						GRA_CriarAresta(IdVertices[((i + 1) * (numElementos + 1)) - 1],IdVertices[(i * (numElementos + 1) )+(numElementos-1)],pGrafo,"OESTE");
						GRA_CriarAresta(IdVertices[((i + 1) * (numElementos + 1)) - 1],IdVertices[(i * (numElementos + 1) )- 2],pGrafo,"NOROESTE");

					}

				}
					/* 8 adjacentes */
				else{

						GRA_AvancarCorrenteVert(pGrafo , 1);

						GRA_CriarAresta(IdVertices[(i * (numElementos + 1)) + j],IdVertices[((i-1) * (numElementos + 1)) + j],pGrafo,"NORTE");
						GRA_CriarAresta(IdVertices[(i * (numElementos + 1)) + j],IdVertices[((i+1) * (numElementos + 1)) + j],pGrafo,"SUL");
						GRA_CriarAresta(IdVertices[(i * (numElementos + 1)) + j],IdVertices[(i * (numElementos + 1)) + (j+1)],pGrafo,"LESTE");
						GRA_CriarAresta(IdVertices[(i * (numElementos + 1)) + j],IdVertices[(i * (numElementos + 1)) + (j-1)],pGrafo,"OESTE");
						GRA_CriarAresta(IdVertices[(i * (numElementos + 1)) + j],IdVertices[((i-1) * (numElementos + 1)) + (j+1)],pGrafo,"NORDESTE");
						GRA_CriarAresta(IdVertices[(i * (numElementos + 1)) + j],IdVertices[((i-1) * (numElementos + 1)) + (j-1)],pGrafo,"NOROESTE");
						GRA_CriarAresta(IdVertices[(i * (numElementos + 1)) + j],IdVertices[((i+1) * (numElementos + 1)) + (j-1)],pGrafo,"SUDOESTE");

						CriarNo( pGrafo , IdVertices[((i+1) * (numElementos + 1)) + (j+1)]); /* Cria Sudeste */

						GRA_CriarAresta(IdVertices[(i * (numElementos + 1)) + j], IdVertices[((i+1) * (numElementos + 1)) + (j+1)],pGrafo,"SUDESTE");


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

   } /* Fim funcao: ARV Criar no da arvore */




void ExcluirValorNo( void * pValor )
{
	   

}

/********** Fim do modulo de implementacao: LIS  Lista duplamente encadeada **********/
