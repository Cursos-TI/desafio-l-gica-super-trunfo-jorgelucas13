#include <stdio.h>
#include <string.h>

#define TOTAL_CARTAS 4 

typedef struct {
    char estado;
    char codigo[4];
    char nomeCidade[50];
    long int populacao;
    double area;
    double pib;
    int pontosTuristicos;
    double densidadePop;
    double pibPerCapita;
} Carta;

void calcularDerivados(Carta *c) {
    c->densidadePop = (c->area > 0) ?
        (double)c->populacao / c->area : 0;
    c->pibPerCapita = (c->populacao > 0) ?
        c->pib * 1e9 / c->populacao : 0;
}

void exibirCarta(Carta c) {
    printf("Estado: %c\n", c.estado);
    printf("Codigo: %s\n", c.codigo);
    printf("Cidade: %s\n", c.nomeCidade);
    printf("Populacao: %ld\n", c.populacao);
    printf("Area: %.2lf km2\n", c.area);
    printf("PIB: %.2lf bilhoes\n", c.pib);
    printf("Pontos Turisticos: %d\n", c.pontosTuristicos);
    printf("Densidade Populacional: %.2lf hab/km2\n", c.densidadePop);
    printf("PIB per Capita: %.2lf reais/hab\n", c.pibPerCapita);
}

double obterValorPorAtributo(Carta c, int atributo) {
    switch(atributo) {
        case 1: return (double)c.populacao;
        case 2: return c.area;
        case 3: return c.pib;
        case 4: return (double)c.pontosTuristicos;
        case 5: return c.densidadePop; 
        case 6: return c.pibPerCapita;
        default: return 0;
    }
}

int main() {
    Carta cartas[TOTAL_CARTAS];

    for (int i = 0; i < TOTAL_CARTAS; i++) {
        printf("\nCadastro da carta %d:\n", i + 1);

        printf("Estado (A-H): ");
        scanf(" %c", &cartas[i].estado);

        printf("Codigo da carta (ex: A01): ");
        scanf("%3s", cartas[i].codigo);

        printf("Nome da cidade: ");
        scanf(" %[^\n]", cartas[i].nomeCidade);

        printf("Populacao: ");
        scanf("%ld", &cartas[i].populacao);

        printf("Area (km2): ");
        scanf("%lf", &cartas[i].area);

        printf("PIB (em bilhoes): ");
        scanf("%lf", &cartas[i].pib);

        printf("Numero de pontos turisticos: ");
        scanf("%d", &cartas[i].pontosTuristicos);

        calcularDerivados(&cartas[i]);
    }

    printf("\n===== CARTAS CADASTRADAS =====\n");
    for (int i = 0; i < TOTAL_CARTAS; i++) {
        printf("\nCarta %d\n", i + 1);
        exibirCarta(cartas[i]);
    }

    int c1, c2, atributo1, atributo2;
    printf("\n=== COMPARAR DUAS CARTAS ===\n");
    printf("Digite o indice da primeira carta (1-%d): ", TOTAL_CARTAS);
    scanf("%d", &c1);
    printf("Digite o indice da segunda carta (1-%d): ", TOTAL_CARTAS);
    scanf("%d", &c2);
    c1--; c2--;

    printf("\nEscolha o primeiro atributo para comparar:\n");
    printf("1 - Populacao\n2 - Area\n3 - PIB\n4 - Pontos Turisticos\n");
    printf("5 - Densidade Populacional (vence menor)\n6 - PIB per Capita\n");
    scanf("%d", &atributo1);

    printf("\nEscolha o segundo atributo para comparar:\n");
    printf("1 - Populacao\n2 - Area\n3 - PIB\n4 - Pontos Turisticos\n");
    printf("5 - Densidade Populacional (vence menor)\n6 - PIB per Capita\n");
    scanf("%d", &atributo2);

    double val1a = obterValorPorAtributo(cartas[c1], atributo1);
    double val2a = obterValorPorAtributo(cartas[c2], atributo1);
    double val1b = obterValorPorAtributo(cartas[c1], atributo2);
    double val2b = obterValorPorAtributo(cartas[c2], atributo2);

    int menorVence1 = (atributo1 == 5);
    int menorVence2 = (atributo2 == 5);

    int resultado1 = (val1a == val2a) ? 0 :
        (menorVence1 ? (val1a < val2a ? 1 : 2) : (val1a > val2a ? 1 : 2));

    int resultado2 = (val1b == val2b) ? 0 :
        (menorVence2 ? (val1b < val2b ? 1 : 2) : (val1b > val2b ? 1 : 2));

    printf("\nResultado da comparacao:\n");
    printf("Atributo 1: ");
    if (resultado1 == 1) printf("Vence %s (%.2lf)\n", cartas[c1].codigo, val1a);
    else if (resultado1 == 2) printf("Vence %s (%.2lf)\n", cartas[c2].codigo, val2a);
    else printf("Empate\n");

    printf("Atributo 2: ");
    if (resultado2 == 1) printf("Vence %s (%.2lf)\n", cartas[c1].codigo, val1b);
    else if (resultado2 == 2) printf("Vence %s (%.2lf)\n", cartas[c2].codigo, val2b);
    else printf("Empate\n");

    if (resultado1 == 1 && resultado2 == 1)
        printf("\n>>> Carta vencedora geral: %s <<<\n", cartas[c1].codigo);
    else if (resultado1 == 2 && resultado2 == 2)
        printf("\n>>> Carta vencedora geral: %s <<<\n", cartas[c2].codigo);
    else if (resultado1 == 0 && resultado2 == 0)
        printf("\n>>> Empate geral <<<\n");
    else
        printf("\n>>> Nenhuma carta venceu ambos atributos (resultado misto) <<<\n");

    return 0;
}
