#include "fda.h"

// Define as regras de portugu�s como padr�o.
void configurar_locale() {
  setlocale(LC_ALL, "Portuguese");
}

// Fun��o que l� os dados do usu�rio e armazena na estrutura de dados
void lerDados(struct dados *dados) {

    printf("Digite o n�mero total de volunt�rios detectores que ser�o avaliados (n): ");
    scanf("%d", &dados->n);
    system("cls");

    printf("Digite os valores das m�dias de ASCE de cada volunt�rio com rela��o ao produto teste\n(com v�rgula para casas decimais): \n");
    for (int i = 0; i < dados->n; i++) {
        printf("\nVolunt�rio %d: ", i + 1);
        scanf("%lf", &dados->teste[i]);
    }
    system("cls");

    printf("Digite os valores m�dios de ASCE de cada volunt�rio com rela��o ao produto comparador\n(com v�rgula para casas decimais): \n");
    for (int i = 0; i < dados->n; i++) {
        printf("\nVolunt�rio %d: ", i + 1);
        scanf("%lf", &dados->ref[i]);


    }
    system("cls");

}

// Fun��o que calcula a m�dia de um vetor de dados
double media(double *vetor, int n) {

    double soma = 0.0;
    
    for (int i = 0; i < n; i++) {
        soma += vetor[i];
    }
    
    return soma / n;
}

// Fun��o que calcula a vari�ncia de um vetor de dados (com n-1 graus de liberdade)
double variancia(double *vetor, int n, double media) {

    double soma = 0.0;
    
    for (int i = 0; i < n; i++) {
        soma += pow(vetor[i] - media, 2);
    }
    
    return soma / (n - 1);
}

// Fun��o que calcula a covari�ncia entre dois vetores de dados (com n-1 graus de liberdade)
double covariancia(double *vetor1, double *vetor2, int n, double media1, double media2) {

    double soma = 0.0;
    
    for (int i = 0; i < n; i++) {
        soma += (vetor1[i] - media1) * (vetor2[i] - media2);
    }
    
    return soma / (n - 1);
}

// Fun��o que calcula o valor de K
double calcularK(double mediaTeste, double mediaRef, double varianciaTeste, double varianciaRef, double covarianciaTesteRef, double G) {

    double termo1 = pow((mediaTeste / mediaRef), 2);
    double termo2 = (varianciaTeste * (1 - G)) / varianciaRef;
    double termo3 = (covarianciaTesteRef / varianciaRef) * (((G * covarianciaTesteRef) / varianciaRef) - ((2 * mediaTeste) / mediaRef));
    
    return termo1 + termo2 + termo3;
}

// Fun��o que calcula I superior
double calcularISuperior(struct dados dados, double G, double covarianciaTesteRef, double t, double K) {

    double mediaTeste = media(dados.teste, dados.n);
    double mediaRef = media(dados.ref, dados.n);
    double varianciaRef = variancia(dados.ref, dados.n, mediaRef);
    double denominador = 1 - G;
    double numerador = ((mediaTeste / mediaRef) - ((G * covarianciaTesteRef) / varianciaRef));
    numerador -= (t / mediaRef) * sqrt((varianciaRef * K) / dados.n);
    
    return (numerador / denominador) *100;
}

// Fun��o que calcula I inferior
double calcularIInferior(struct dados dados, double G, double covarianciaTesteRef, double t, double K) {

    double mediaTeste = media(dados.teste, dados.n);
    double mediaRef = media(dados.ref, dados.n);
    double varianciaRef = variancia(dados.ref, dados.n, mediaRef);
    double denominador = 1 - G;
    double numerador = ((mediaTeste / mediaRef) - ((G * covarianciaTesteRef) / varianciaRef));
    numerador += (t / mediaRef) * sqrt((varianciaRef * K) / dados.n);
    
    return (numerador / denominador) *100;
}


