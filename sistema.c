#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_RELATOS 1000
#define PI 3.14159265358979323846
#define RAIO_TERRA_KM 6371.0

typedef struct {
    char nome[100];
    char cpf[15];
    char telefone[20];
    char email[100];
} Pessoa;

typedef struct {
    Pessoa pessoa;
    char tipo[50];
    char data[11]; // formato DD/MM/AAAA
    double latitude;
    double longitude;
} Relato;

Relato relatos[MAX_RELATOS];
int totalRelatos = 0;

// Função para converter graus para radianos
double grausParaRadianos(double grau) {
    return grau * (PI / 180.0);
}

// Fórmula de Haversine
double calcularDistancia(double lat1, double lon1, double lat2, double lon2) {
    double dLat = grausParaRadianos(lat2 - lat1);
    double dLon = grausParaRadianos(lon2 - lon1);

    lat1 = grausParaRadianos(lat1);
    lat2 = grausParaRadianos(lat2);

    double a = sin(dLat/2) * sin(dLat/2) +
               cos(lat1) * cos(lat2) * sin(dLon/2) * sin(dLon/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));

    return RAIO_TERRA_KM * c;
}

void cadastrarRelato() {
    if (totalRelatos >= MAX_RELATOS) {
        printf("Limite de relatos atingido.\n");
        return;
    }

    Relato r;
    printf("Nome: ");
    fgets(r.pessoa.nome, sizeof(r.pessoa.nome), stdin);
    r.pessoa.nome[strcspn(r.pessoa.nome, "\n")] = 0;

    printf("CPF: ");
    fgets(r.pessoa.cpf, sizeof(r.pessoa.cpf), stdin);
    r.pessoa.cpf[strcspn(r.pessoa.cpf, "\n")] = 0;

    printf("Telefone: ");
    fgets(r.pessoa.telefone, sizeof(r.pessoa.telefone), stdin);
    r.pessoa.telefone[strcspn(r.pessoa.telefone, "\n")] = 0;

    printf("Email: ");
    fgets(r.pessoa.email, sizeof(r.pessoa.email), stdin);
    r.pessoa.email[strcspn(r.pessoa.email, "\n")] = 0;

    printf("Tipo de desastre: ");
    fgets(r.tipo, sizeof(r.tipo), stdin);
    r.tipo[strcspn(r.tipo, "\n")] = 0;

    printf("Data (DD/MM/AAAA): ");
    fgets(r.data, sizeof(r.data), stdin);
    r.data[strcspn(r.data, "\n")] = 0;

    printf("Latitude: ");
    scanf("%lf", &r.latitude);
    printf("Longitude: ");
    scanf("%lf", &r.longitude);
    getchar(); // limpar buffer

    relatos[totalRelatos++] = r;

    printf("Relato cadastrado com sucesso!\n");
}

void listarRelatos() {
    for (int i = 0; i < totalRelatos; i++) {
        printf("\n--- RELATO %d ---\n", i+1);
        printf("Nome: %s\n", relatos[i].pessoa.nome);
        printf("CPF: %s\n", relatos[i].pessoa.cpf);
        printf("Telefone: %s\n", relatos[i].pessoa.telefone);
        printf("Email: %s\n", relatos[i].pessoa.email);
        printf("Tipo: %s\n", relatos[i].tipo);
        printf("Data: %s\n", relatos[i].data);
        printf("Local: (%.4lf, %.4lf)\n", relatos[i].latitude, relatos[i].longitude);
    }
}

void salvarEmArquivo() {
    FILE *f = fopen("relatos.txt", "w");
    for (int i = 0; i < totalRelatos; i++) {
        fprintf(f, "%s|%s|%s|%s|%s|%s|%.6lf|%.6lf\n",
            relatos[i].pessoa.nome,
            relatos[i].pessoa.cpf,
            relatos[i].pessoa.telefone,
            relatos[i].pessoa.email,
            relatos[i].tipo,
            relatos[i].data,
            relatos[i].latitude,
            relatos[i].longitude
        );
    }
    fclose(f);
    printf("Relatos salvos em 'relatos.txt'.\n");
}

void carregarDeArquivo() {
    FILE *f = fopen("relatos.txt", "r");
    if (!f) return;

    Relato r;
    while (fscanf(f, "%99[^|]|%14[^|]|%19[^|]|%99[^|]|%49[^|]|%10[^|]|%lf|%lf\n",
        r.pessoa.nome, r.pessoa.cpf, r.pessoa.telefone, r.pessoa.email,
        r.tipo, r.data, &r.latitude, &r.longitude) == 8) {
        relatos[totalRelatos++] = r;
    }
    fclose(f);
}

void filtrarPorRaio() {
    double lat, lon;
    printf("Digite sua latitude: ");
    scanf("%lf", &lat);
    printf("Digite sua longitude: ");
    scanf("%lf", &lon);
    getchar();

    printf("\nRelatos num raio de 10 km:\n");
    for (int i = 0; i < totalRelatos; i++) {
        double d = calcularDistancia(lat, lon, relatos[i].latitude, relatos[i].longitude);
        if (d <= 10.0) {
            printf("\nNome: %s\n", relatos[i].pessoa.nome);
            printf("Tipo: %s\n", relatos[i].tipo);
            printf("Distância: %.2lf km\n", d);
        }
    }
}

int compararPorData(const void *a, const void *b) {
    return strcmp(((Relato*)a)->data, ((Relato*)b)->data);
}

void ordenarPorData() {
    qsort(relatos, totalRelatos, sizeof(Relato), compararPorData);
    printf("Relatos ordenados por data.\n");
}

int main() {
    carregarDeArquivo();
    int opcao;

    do {
        printf("\n=== MENU ===\n");
        printf("1. Cadastrar relato\n");
        printf("2. Listar relatos\n");
        printf("3. Filtrar por distância (10 km)\n");
        printf("4. Ordenar por data\n");
        printf("5. Salvar e sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // limpar \n

        switch (opcao) {
            case 1: cadastrarRelato(); break;
            case 2: listarRelatos(); break;
            case 3: filtrarPorRaio(); break;
            case 4: ordenarPorData(); break;
            case 5: salvarEmArquivo(); break;
            default: printf("Opção inválida.\n");
        }
    } while (opcao != 5);

    return 0;
}
