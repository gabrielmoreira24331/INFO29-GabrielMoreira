#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "valida.h"
#define TAM_ALUNO 50
#define aluno_inexistente -1
#define pessoa_inexistente -2
#define excluido 0
#define vazio -3

typedef struct
{
    char nome[TAM_ALUNO];
    char matricula[TAM_ALUNO];
    char sexo;
    char data[TAM_ALUNO];
    char cpf[TAM_ALUNO];
    int cursando[TAM_ALUNO];
} pessoa;

char menugeral(void);
char menu_pessoa(char tipo[]);
void cadastrar_pessoa(int posicao, pessoa pessoas[]);
void listar_pessoas(int tamanho, pessoa pessoas[]);
int excluir_pessoa(int tamanho, pessoa pessoas[]);
int atualiza_pessoa(int tamanho, pessoa pessoas[]);

void listar_pessoas(int tamanho, pessoa pessoas[])
{
    if (tamanho == 0)
        printf("Nenhuma pessoa cadastrada\n");
    printf("\n--------------------------------- LISTA DE PESSOAS --------------------------------------\n");
    for(int i = 0; i < tamanho; i++)
    {
        printf("NOME: %s - MATRICULA: %s - DATA: %s - CPF: %s - SEXO: %c", pessoas[i].nome, pessoas[i].matricula, pessoas[i].data, pessoas[i].cpf, pessoas[i].sexo);
        printf("\n");
    }
    printf("\n");
    printf("--------------------------------------------------------------------------------------------\n");  
}

char menugeral(void)
{
    char resposta;

    printf("\n-------- MENU GERAL --------\n");
    printf("[0] - Sair\n");
    printf("[1] - Alunos\n");
    printf("[2] - Professores\n");
    printf("[3] - Disciplinas\n");
    printf("[4] - Relatórios\n");
    printf("----------------------------\n");
    printf("Opção: ");
    resposta = getchar();
    while (getchar() != '\n');
    return resposta;
}

char menu_pessoa(char tipo[])
{
    char resposta;

    printf("\n---------- %s ----------\n", tipo);
    printf("[0] - Voltar\n");
    printf("[1] - Cadastrar %s\n", tipo);
    printf("[2] - Listar %s\n", tipo);
    printf("[3] - Atualizar Cadastro\n");
    printf("[4] - Excluir %s\n", tipo);
    printf("----------------------------\n");
    printf("Opção: ");
    resposta = getchar();
    while (getchar() != '\n');
    return resposta;

}

void cadastrar_pessoa(int tamanho, pessoa pessoas[])
{
    printf("\n---------- CADASTRAR ----------\n");
    printf("NOME: ");
    fgets(pessoas[tamanho].nome, 50, stdin);
    pessoas[tamanho].nome[strcspn(pessoas[tamanho].nome, "\n")] = '\0';
    valida_nomeP(pessoas,tamanho);
    printf("MATRÍCULA: ");
    fgets(pessoas[tamanho].matricula, 50, stdin);
    pessoas[tamanho].matricula[strcspn(pessoas[tamanho].matricula, "\n")] = '\0';
    valida_matricula(pessoas, tamanho);
    printf("DATA: ");
    fgets(pessoas[tamanho].data, 50, stdin);
    pessoas[tamanho].data[strcspn(pessoas[tamanho].data, "\n")] = '\0';
    valida_nascimento(pessoas,tamanho);
    printf("CPF: ");
    fgets(pessoas[tamanho].cpf, 13, stdin);
    pessoas[tamanho].cpf[strcspn(pessoas[tamanho].cpf, "\n")] = '\0';
    valida_cpf(pessoas,tamanho);
    printf("SEXO: ");
    fgets(pessoas[tamanho].sexo, 13, stdin);
    valida_nomeP(pessoas,tamanho);
    pessoas[tamanho].sexo = getchar();
    while (getchar() != '\n');
    for(int x = 0; x < TAM_ALUNO; x++)
    {
        pessoas[tamanho].cursando[x] = 0;
    }
    printf("---------------------------------\n");
}

int atualiza_pessoa(int tamanho, pessoa pessoas[])
{
    if(tamanho == 0)
    {
        printf("nenhuma pessoa cadastrada\n");
        return vazio;
    }
    char matricula[TAM_ALUNO];
    printf("Digite a matricula: ");
    fgets(matricula, 50, stdin);
    matricula[strcspn(matricula, "\n")] = '\0';
    
    for(int i = 0; i < tamanho; i++)
    {
        if (strcmp(matricula, pessoas[i].matricula) == 0) 
        {
            cadastrar_pessoa(i, pessoas);
            return 0;
        }
        
    }
    return pessoa_inexistente;
}

int excluir_pessoa(int tamanho, pessoa pessoas[])
{
    if (tamanho == 0)
    {
        printf("Nenhuma pessoa cadastrada\n");
        return vazio;
    }
    char matric[20];
    int encontrado = 0;

    printf("Digite a matrícula: ");
    fgets(matric, 20, stdin);
    matric[strcspn(matric, "\n")] = '\0';
  
    for(int i = 0; i < tamanho; i++)
    {
        if(strcmp(pessoas[i].matricula, matric) == 0)
        {
            for(int j = i; j < tamanho; j++)
            {
                pessoas[j] = pessoas[j + 1];
            }
            encontrado = 1;
            break;
        }
        
    }
    if (encontrado == 1)
        return excluido;
    else
        return pessoa_inexistente;
    
}

