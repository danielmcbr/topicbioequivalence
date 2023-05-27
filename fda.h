#ifndef _FDA_H
#define _FDA_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

// Define o tamanho máximo dos vetores
#define MAX_N 100

// Define a estrutura de dados que armazena os vetores
struct dados {
    int n;           // Número de voluntários
    double teste[MAX_N];   // Vetor com os dados do teste
    double ref[MAX_N];     // Vetor com os dados da referência
};

// Define as regras de português como padrão.
void configurar_locale();

// Função que lê os dados do usuário e armazena na estrutura de dados
void lerDados(struct dados *dados);

// Função que calcula a média de um vetor de dados
double media(double *vetor, int n);

// Função que calcula a variância de um vetor de dados (com n-1 graus de liberdade)
double variancia(double *vetor, int n, double media);

// Função que calcula a covariância entre dois vetores de dados (com n-1 graus de liberdade)
double covariancia(double *vetor1, double *vetor2, int n, double media1, double media2);

// Função que calcula o valor de K
double calcularK(double mediaTeste, double mediaRef, double varianciaTeste, double varianciaRef, double covarianciaTesteRef, double G);

// Função que calcula I superior
double calcularISuperior(struct dados dados, double G, double covarianciaTesteRef, double t, double K);

// Função que calcula I inferior
double calcularIInferior(struct dados dados, double G, double covarianciaTesteRef, double t, double K);

#endif /* FDA_H */ 
