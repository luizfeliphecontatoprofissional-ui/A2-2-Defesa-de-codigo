#include <stdio.h>

struct Aluno {
    char nome[50];
    float media;
};

float lerMedia() {
    float nota, soma = 0;
    int j;
    for (j = 1; j <= 4; j++) {
        printf("Nota %d: ", j);
        scanf("%f", &nota);
        soma = soma + nota;       
    }
    return soma / 4;               
}

void mostrarSituacao(float media) {
    if (media >= 6)
        printf("Aprovado\n");
    else if (media >= 4)
        printf("Recuperacao\n");
    else
        printf("Reprovado\n");
}

int carregar(struct Aluno alunos[]) {
    FILE *arq = fopen("alunos.txt", "r");
    int qtd = 0;
    if (arq == NULL)              
        return 0;
    while (fscanf(arq, "%f %[^\n]", &alunos[qtd].media, alunos[qtd].nome) == 2)
        qtd++;
    fclose(arq);
    return qtd;
}

void salvar(struct Aluno alunos[], int qtd) {
    FILE *arq = fopen("alunos.txt", "w");
    int i;
    for (i = 0; i < qtd; i++)
        fprintf(arq, "%.1f %s\n", alunos[i].media, alunos[i].nome);
    fclose(arq);
}

int main() {
    struct Aluno alunos[50];       
    int qtd, novos, i, posicao = -1;

    qtd = carregar(alunos);
    printf("%d aluno(s) carregado(s) do arquivo.\n", qtd);

    printf("Quantos alunos deseja cadastrar? ");
    scanf("%d", &novos);
    for (i = 0; i < novos; i++) {
        printf("\nNome do aluno: ");
        scanf(" %[^\n]", alunos[qtd].nome);  
        alunos[qtd].media = lerMedia();
        qtd++;
    }

    salvar(alunos, qtd);           

    printf("\n%-20s %-8s %s\n", "ALUNO", "MEDIA", "SITUACAO");
    for (i = 0; i < qtd; i++) {
        printf("%-20s %-8.1f ", alunos[i].nome, alunos[i].media);
        mostrarSituacao(alunos[i].media);
    }

    for (i = 0; i < qtd; i++) {
        if (alunos[i].media < 4) {
            if (posicao == -1 || alunos[i].media < alunos[posicao].media)
                posicao = i;       
        }
    }

    if (posicao == -1)
        printf("\nNenhum aluno reprovado.\n");
    else
        printf("\nReprovado com a menor media: %s (media %.1f)\n", alunos[posicao].nome, alunos[posicao].media);

    return 0;
}
