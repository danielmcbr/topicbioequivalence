#include "fda.h"

// Define as regras de português como padrão.
void configurar_locale() {
  setlocale(LC_ALL, "Portuguese");
}

// Função que lê os dados do usuário e armazena na estrutura de dados
void lerDados(struct dados *dados) {

    printf("Digite o número total de voluntários detectores que serão avaliados (n): ");
    scanf("%d", &dados->n);
    system("cls");

    printf("Digite os valores das médias de ASCE de cada voluntário com relação ao produto teste\n(com vírgula para casas decimais): \n");
    for (int i = 0; i < dados->n; i++) {
        printf("\nVoluntário %d: ", i + 1);
        scanf("%lf", &dados->teste[i]);
    }
    system("cls");

    printf("Digite os valores médios de ASCE de cada voluntário com relação ao produto comparador\n(com vírgula para casas decimais): \n");
    for (int i = 0; i < dados->n; i++) {
        printf("\nVoluntário %d: ", i + 1);
        scanf("%lf", &dados->ref[i]);


    }
    system("cls");

}

// Função que calcula a média de um vetor de dados
double media(double *vetor, int n) {

    double soma = 0.0;
    
    for (int i = 0; i < n; i++) {
        soma += vetor[i];
    }
    
    return soma / n;
}

// Função que calcula a variância de um vetor de dados (com n-1 graus de liberdade)
double variancia(double *vetor, int n, double media) {

    double soma = 0.0;
    
    for (int i = 0; i < n; i++) {
        soma += pow(vetor[i] - media, 2);
    }
    
    return soma / (n - 1);
}

// Função que calcula a covariância entre dois vetores de dados (com n-1 graus de liberdade)
double covariancia(double *vetor1, double *vetor2, int n, double media1, double media2) {

    double soma = 0.0;
    
    for (int i = 0; i < n; i++) {
        soma += (vetor1[i] - media1) * (vetor2[i] - media2);
    }
    
    return soma / (n - 1);
}

// Função que calcula o valor de K
double calcularK(double mediaTeste, double mediaRef, double varianciaTeste, double varianciaRef, double covarianciaTesteRef, double G) {

    double termo1 = pow((mediaTeste / mediaRef), 2);
    double termo2 = (varianciaTeste * (1 - G)) / varianciaRef;
    double termo3 = (covarianciaTesteRef / varianciaRef) * (((G * covarianciaTesteRef) / varianciaRef) - ((2 * mediaTeste) / mediaRef));
    
    return termo1 + termo2 + termo3;
}

// Função que calcula I superior
double calcularISuperior(struct dados dados, double G, double covarianciaTesteRef, double t, double K) {

    double mediaTeste = media(dados.teste, dados.n);
    double mediaRef = media(dados.ref, dados.n);
    double varianciaRef = variancia(dados.ref, dados.n, mediaRef);
    double denominador = 1 - G;
    double numerador = ((mediaTeste / mediaRef) - ((G * covarianciaTesteRef) / varianciaRef));
    numerador -= (t / mediaRef) * sqrt((varianciaRef * K) / dados.n);
    
    return (numerador / denominador) *100;
}

// Função que calcula I inferior
double calcularIInferior(struct dados dados, double G, double covarianciaTesteRef, double t, double K) {

    double mediaTeste = media(dados.teste, dados.n);
    double mediaRef = media(dados.ref, dados.n);
    double varianciaRef = variancia(dados.ref, dados.n, mediaRef);
    double denominador = 1 - G;
    double numerador = ((mediaTeste / mediaRef) - ((G * covarianciaTesteRef) / varianciaRef));
    numerador += (t / mediaRef) * sqrt((varianciaRef * K) / dados.n);
    
    return (numerador / denominador) *100;
}


