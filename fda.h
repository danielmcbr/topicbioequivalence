#ifndef _FDA_H
#define _FDA_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

// Define o tamanho m�ximo dos vetores
#define MAX_N 100

// Define a estrutura de dados que armazena os vetores
struct dados {
    int n;           // N�mero de volunt�rios
    double teste[MAX_N];   // Vetor com os dados do teste
    double ref[MAX_N];     // Vetor com os dados da refer�ncia
};

// Define as regras de portugu�s como padr�o.
void configurar_locale();

// Fun��o que l� os dados do usu�rio e armazena na estrutura de dados
void lerDados(struct dados *dados);

// Fun��o que calcula a m�dia de um vetor de dados
double media(double *vetor, int n);

// Fun��o que calcula a vari�ncia de um vetor de dados (com n-1 graus de liberdade)
double variancia(double *vetor, int n, double media);

// Fun��o que calcula a covari�ncia entre dois vetores de dados (com n-1 graus de liberdade)
double covariancia(double *vetor1, double *vetor2, int n, double media1, double media2);

// Fun��o que calcula o valor de K
double calcularK(double mediaTeste, double mediaRef, double varianciaTeste, double varianciaRef, double covarianciaTesteRef, double G);

// Fun��o que calcula I superior
double calcularISuperior(struct dados dados, double G, double covarianciaTesteRef, double t, double K);

// Fun��o que calcula I inferior
double calcularIInferior(struct dados dados, double G, double covarianciaTesteRef, double t, double K);

#endif /* FDA_H */ 
