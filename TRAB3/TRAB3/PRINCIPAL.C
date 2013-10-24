/***************************************************************************
*  $MCI Módulo de implementação: PART PARTIDA
*
*  Arquivo gerado:              PRINCIPAL.C
*  Letras identificadoras:      PRI
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
*     1       afv   11/nov/2013 início desenvolvimento
*
***************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

//#include "GRAFO.H"
//#include "TABULEIRO.H"
//#include "PECA.H"

/************  Protótipo das funções encapsuladas no módulo  *************/


/************* Função responsável pela execução da aplicação ***************/

int main (void){
	int val;
	char tecla;
	printf("\nVERIFICADOR DE XEQUE MATE - AFV\n\n");
	printf("\n_________________________\n\n");
	printf("Informe o número de peças por time");

	scanf("%d" , &val);
	printf("O valor informado é: %d\n" , val);

	printf("Pressione qualquer tecla para sair\n");
	scanf("%c" , &tecla);
	if(tecla != 0){
		exit(1);
	}
}


 /************* Código das funções encapsuladas no módulo *****************/
