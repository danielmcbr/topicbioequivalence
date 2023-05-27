#include "fda.h"

int main() {

    // Configura o código para ser compatível com o português
    configurar_locale();

    int continuar = 1;  // variável para controlar se o programa deve continuar sendo executado

    while(continuar == 1) {

    // Exibe o nome do programa e boas-vindas ao usuário
    printf("--------------------------------------------------------------------\n");
    printf("CÁLCULO DO INTERVALO DE 90%% DE CONFIANÇA DE ACORDO COM GUIA DA FDA \n");
    printf("   TOPICAL DERMATOLOGIC CORTICOSTEROIDS: IN VIVO BIOEQUIVALENCE     \n");
    printf("--------------------------------------------------------------------\n");
    printf("\n\n"); // adiciona uma linha em branco


    // Cria a estrutura de dados
    struct dados meusDados;

    // Lê os dados do usuário
    lerDados(&meusDados);

    // Calcula a média e a variância para o teste
    double mediaTeste = media(meusDados.teste, meusDados.n);
    double varianciaTeste = variancia(meusDados.teste, meusDados.n, mediaTeste);

    // Calcula a média e a variância para a referência
    double mediaRef = media(meusDados.ref, meusDados.n);
    double varianciaRef = variancia(meusDados.ref, meusDados.n, mediaRef);

    // Calcula a covariância entre os vetores
    double covarianciaTesteRef = covariancia(meusDados.teste, meusDados.ref, meusDados.n, mediaTeste, mediaRef);

    // Lê o valor do t-crítico
    double tCritico;
    printf("Digite o valor de t crítico encontrado em uma tabela t bilateral com significância de 0,1 e grau de liberdade n-1: ");
    scanf("%lf", &tCritico);

    // Calcula o valor de G
    double G = (pow(tCritico, 2) * varianciaRef) / (meusDados.n * pow(mediaRef, 2));

    // Começa a imprimir os resultados
    system("cls");
    printf("=================================================================\n");
    printf("                        RESULTADOS                               \n");
    printf("=================================================================\n\n");


    // Verifica se o valor de G é menor do que um
    if (G < 1) {
        printf("\nComo G é menor do que 1, o experimento atende aos requisitos de um estudo de bioequivalência in vivo.\n");
    } else {
        printf("\nComo G é igual ou maior do que 1, oexperimento não atende aos requisitos de um estudo de bioequivalência in vivo.\n");
    }

    // Calcula o valor de K
    double K = calcularK(mediaTeste, mediaRef, varianciaTeste, varianciaRef, covarianciaTesteRef, G);
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    printf("                        O valor de K é: %.3lf                    \n", K);
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");


    // Calcula I Inferior
    double iInferior = calcularIInferior(meusDados, G, covarianciaTesteRef, tCritico, K);

    // Imprime o texto sobre o intervalo de confiança de 90%
    printf("\nConsiderando um intervalo de 90%% de confiança, os limites inferiores e superiores são: \n");

    // Imprime o resultado de I inferior
    printf("=================================================================\n");
    printf("               Limite Inferior: %.1lf                            \n", iInferior);


    // Calcula I Superior
    double iSuperior = calcularISuperior(meusDados, G, covarianciaTesteRef, tCritico, K);

    // Imprime o resultado de I Superior

    printf("               Limite Superior: %.1lf                            \n", iSuperior);
    printf("=================================================================\n");

    printf("Deseja continuar? (1 para sim, outra tecla para não): ");
    if (scanf("%d", &continuar) != 1) {
    printf("Entrada inválida.\n");
    continuar = 0;  // Define continuar como 0 para encerrar o programa
    }
    system("cls");
   }
    return 0;
}



