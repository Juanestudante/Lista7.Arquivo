#include <stdio.h>
#include <stdlib.h>

// Estrutura para armazenar os dados do usuário
struct Usuario {
    char nome[50];
    int idade;
    char email[50];
};

// Função para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    FILE *arquivo;
    int numeroUsuarios, i;

    // Solicita ao usuário o número de usuários
    printf("Informe o número de usuários: ");
    while (scanf("%d", &numeroUsuarios) != 1 || numeroUsuarios <= 0) {
        limparBuffer();
        printf("Por favor, insira um número válido de usuários: ");
    }

    // Aloca dinamicamente um array de estruturas de usuários
    struct Usuario *usuarios = (struct Usuario*)malloc(numeroUsuarios * sizeof(struct Usuario));
    
    if (usuarios == NULL) {
        printf("Erro ao alocar memória.");
        return 1;
    }

    // Abre o arquivo para escrita
    arquivo = fopen("usuarios.csv", "w");

    // Verifica se o arquivo foi aberto corretamente
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.");
        free(usuarios);
        return 1;
    }

    // Escreve o cabeçalho no arquivo CSV
    fprintf(arquivo, "Nome,Idade,Email\n");

    // Loop para obter dados de cada usuário
    for (i = 0; i < numeroUsuarios; i++) {
        limparBuffer(); // Limpar o buffer do teclado antes de ler a string

        // Solicita ao usuário os dados do usuário
        printf("\nDigite os dados do usuário %d:\n", i + 1);

        printf("Nome: ");
        fgets(usuarios[i].nome, sizeof(usuarios[i].nome), stdin);
        usuarios[i].nome[strcspn(usuarios[i].nome, "\n")] = '\0';

        printf("Idade: ");
        while (scanf("%d", &usuarios[i].idade) != 1 || usuarios[i].idade <= 0) {
            limparBuffer();
            printf("Por favor, insira uma idade válida: ");
        }

        limparBuffer(); // Limpar o buffer do teclado antes de ler a string

        printf("Email: ");
        fgets(usuarios[i].email, sizeof(usuarios[i].email), stdin);
        usuarios[i].email[strcspn(usuarios[i].email, "\n")] = '\0';

        // Escreve os dados no arquivo CSV
        fprintf(arquivo, "%s,%d,%s\n", usuarios[i].nome, usuarios[i].idade, usuarios[i].email);
    }

    // Fecha o arquivo e libera a memória alocada
    fclose(arquivo);
    free(usuarios);

    printf("\nDados gravados com sucesso no arquivo usuarios.csv.\n");

    return 0;
}
