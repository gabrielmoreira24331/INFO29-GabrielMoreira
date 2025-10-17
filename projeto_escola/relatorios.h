#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_ALUNO 50
#define invalido -5
#define pessoa_inexistente -2
#define vazio -3
#define excluido 0

int now(int tipo);

int menu_relatorio(void)
{
    int resposta;

    printf("\n------------------------------ Relatórios ----------------------------------\n");
    printf("[0] - Voltar\n");
    printf("[1] - Listar Disciplinas\n");
    printf("[2] - Listar uma Disciplina\n");
    printf("[3] - Listar Alunos por sexo\n");
    printf("[4] - Listar Alunos ordenados por Nome\n");
    printf("[5] - Listar Alunos ordenados por data de nascimento\n");
    printf("[6] - Listar Professores por sexo\n");
    printf("[7] - Listar Professores ordenados por Nome\n");
    printf("[8] - Listar Professores ordenados por data de nascimento\n");
    printf("[9] - Aniversariante do mês\n");
    printf("[10] - Busca com 3 letras\n");
    printf("[11] - Lista de alunos matriculados em menos de 3 disciplinas\n");
    printf("[12] - Lista de Disciplinas, com nome do professor, que extrapolam 40 vagas\n");        
    printf("-------------------------------------------------------------------------------\n");
    printf("Opção: ");
    scanf("%d", &resposta);
    while (getchar() != '\n');
    return resposta;
}

void exibir_disciplinas(int tamanho, disciplina disciplinas[])
{   
    printf("\nDisciplinas: \n");
    for(int x = 0; x < tamanho; x++)
    {
        printf("%s - %s\n", disciplinas[x].nome, disciplinas[x].codigo);
    }
}

int exibir_disciplina(int tamanho, disciplina disciplinas[], int q_alunos, pessoa alunos[])
{
    char codigo[20];
    int posicao = -1;

    if (tamanho == 0)
    {
        printf("nenhuma pessoa disciplina cadastrada\n");
        return vazio;
    }

    printf("Digite o código da disciplina: ");
    fgets(codigo, 20, stdin);
    codigo[strcspn(codigo, "\n")] = '\0';
  
    for (int i = 0; i < tamanho; i++)
    {
        if(strcmp(disciplinas[i].codigo, codigo) == 0)
        {
            posicao = i;
            printf("\nDisciplina: %s\n", disciplinas[i].nome);
            break;
        }
    }

    if(posicao == -1)
    {
        printf("A disciplina digitada não existe\n");
    }

    for (int j = 0; j < q_alunos; j++)
    {
        if (alunos[j].cursando[posicao] == 1)
        {
            printf("%s - %s\n", alunos[j].nome, alunos[j].matricula);
        }
    }
    return 0;      
}

int listar_alunos_sexo(int tamanho, pessoa alunos[])
{   
    char modo;

    if (tamanho == 0)
    {
        printf("Nenhum aluno cadastrado\n");
        return vazio;
    }
    printf("[M] -> listar homens\n");
    printf("[F] -> listar mulheres\n");

    do{
        scanf("%c", &modo);
        while (getchar() != '\n');
    }
    while(modo != 'M' && modo != 'F');
    
    printf("%c:\n", modo);
    for(int x = 0; x < tamanho; x++)
    {
        if (alunos[x].sexo == modo)
        {
            printf("%s - %s\n", alunos[x].nome, alunos[x].matricula);
        }
    }
}

void ordenar_lista(int tamanho, pessoa alunos[])
{
    for (int i = 0; i < tamanho - 1; i++)
    {
        int pos_menor = i;

        for (int j = i + 1; j < tamanho; j++)
        {
            if (strcmp(alunos[j].nome, alunos[pos_menor].nome) < 0)
            {
                pos_menor = j;
            }
        }

        if (pos_menor != i)
        {
            pessoa temp = alunos[i];
            alunos[i] = alunos[pos_menor];
            alunos[pos_menor] = temp;
        }
    }
}

void matriculados(int tamanho, pessoa alunos[])
{
    int count = 0;

    printf("\nAlunos que estão matriculados em menos 3 disciplinas: \n");
    for(int x = 0; x < tamanho; x++)
    {
        for(int y = 0; y < 50; y++)
        {
            if(alunos[x].cursando[y] == 1)
            {
                count++;
            }
        }
        if (count < 3)
        {
            printf("%s - %s\n", alunos[x].nome, alunos[x].matricula);
        }
        count = 0;
    }
}

void disciplinas_cheias(int tamanho, pessoa alunos[], int q_disciplinas, disciplina disciplinas[])
{
    int count = 0;
    int d = 0;

    printf("\ndisciplinas que estão com mais de 40 alunos matriculados: \n");
    
    for(int d = 0; d < q_disciplinas; d++)
    {
        for(int y = 0; y < tamanho; y++)
        {
            if(alunos[y].cursando[d] == 1)
            {   
                count++;
            }
        }
        if (count > 40)
        {
            printf("%s - %s\n", disciplinas[d].nome, disciplinas[d].codigo);
        }
        count = 0;
    }   
}

int separa_data(char data[], int tipo)
{
    char *parte;
    char copia[50];
    int dia, mes, ano;

    strcpy(copia, data);
    parte = strtok(copia, "/");
    dia = atoi(parte);
    parte = strtok(NULL, "/");
    mes = atoi(parte);
    parte = strtok(NULL, "/");
    ano = atoi(parte);
    if (tipo == 2)
        return ano;
    else if (tipo == 1)
        return mes;
    else if (tipo == 0)
        return dia;
    else if (tipo == -1)
    {
        return (now(2) * 365 + now(1) * 30 + now(0)) - (ano * 365 + mes * 30 + dia);
    }
}

int now(int tipo)
{
    time_t segundos;
    time(&segundos);
    struct tm *data_local = localtime(&segundos);

    int dia = data_local->tm_mday;
    int mes = data_local->tm_mon + 1;
    int ano = data_local->tm_year + 1900;

    if (tipo == 0)
        return dia;
    else if (tipo == 1)
        return mes;
    else if (tipo == 2)
        return ano;
}

void aniversarintes_mes(int q_alunos, pessoa alunos[], int q_professores, pessoa professores[])
{
    int teste1 = 0, teste2 = 0;

    printf("Alunos que fazem aniversário esse mês: ");
    for(int x = 0; x < q_alunos; x++)
    {   
        if(separa_data(alunos[x].data, 1) == now(1))
        {
            printf("\nNome: %s - Matricula: %s - Data: %.2d/%.2d", alunos[x].nome, alunos[x].matricula, separa_data(alunos[x].data, 0), separa_data(alunos[x].data, 1));
            teste1 = 1;
        }
    }
    if(teste1 == 0)
        printf("Nenhum aluno faz aniversário nesse mês\n");

    printf("\nProfessores que fazem aniversário esse mês: ");
    for(int y = 0; y < q_professores; y++)
    {   
        if(separa_data(professores[y].data, 1) == now(1))
        {
            printf("\nNome: %s - Matricula: %s - Data: %.2d/%.2d\n", professores[y].nome, professores[y].matricula, separa_data(professores[y].data, 0), separa_data(professores[y].data, 1));
            teste2 = 1;
        }
    }
    if(teste2 == 0)
        printf("Nenhum professor faz aniversário nesse mês\n");
}

void ordenar_data(int tamanho, pessoa alunos[])
{
    int menor = 0;
    int posicao = 0;
    pessoa backup;

    for(int x = 0; x < tamanho-1; x++)
    {
        menor = separa_data(alunos[x].data, -1);
        for(int y = x; y < tamanho; y++)
        {
            if(menor > separa_data(alunos[y].data, -1))
            {
                menor = separa_data(alunos[y].data, -1);
                posicao = y;
            }
        }
        if(x != posicao)
        {
            backup = alunos[posicao];
            alunos[posicao] = alunos[x];
            alunos[x] = backup;
        }
    }
}

void busca_3letras(int tamanho, pessoa alunos[], int q_professores, pessoa professores[])
{
    char resposta[4];
    int teste = 0;

    do{
        printf("Digite três letras: ");
        fgets(resposta, 4, stdin); 
        resposta[strcspn(resposta, "\n")] = '\0';   
    }
    while(strlen(resposta) != 3);

    printf("Alunos: \n");
    for (int x = 0; x < tamanho; x++)
    {
        if (strncmp(resposta, alunos[x].nome, 3) == 0)
        {
            printf("Nome: %s - Matricula: %s\n", alunos[x].nome, alunos[x].matricula);
            teste = 1;
        }
    }
    if(teste == 0)
        printf("Nenhuma aluno encontrado\n");

    printf("Professores: \n");
    for (int x = 0; x < q_professores; x++)
    {
        if (strncmp(resposta, professores[x].nome, 3) == 0)
        {
            printf("Nome: %s - Matricula: %s\n", professores[x].nome, professores[x].matricula);
            teste = 1;
        }
    }
    if(teste == 0)
        printf("Nenhuma professor encontrado\n");

}


