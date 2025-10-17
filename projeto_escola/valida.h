#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "escola.h"
#include "disciplinas.h"
#define TAM_ALUNO 50

void valida_nomeP(pessoa *pessoas,int tamanho){
    int sai;
    size_t tamNOME = strlen(pessoas[tamanho].nome);
    while(sai == 0){
        sai = 1;
        for(int i = 0;i < (int)tamNOME;i++){
            if(! (isalpha((unsigned char)pessoas[i].nome) || (pessoas[i].nome == ' '))){ 
                sai = 0;
                printf("O nome deve conter apenas letras e espacos!\n");
                printf("NOME: ");
                fgets(pessoas[tamanho].nome, 50, stdin);
                pessoas[tamanho].nome[strcspn(pessoas[tamanho].nome, "\n")] = '\0';
                break;
            }
        }
    }   
}
void valida_matricula(pessoa *pessoas,int tamanho){
    int sai;
    size_t tam = strlen(pessoas[tamanho].matricula);
    while(sai = 0){
        sai = 1;
        for(int i = 0;i < (int)tam;i++){
            if(pessoas[i].matricula < '0' || pessoas[i].matricula > '9'){
                printf("Letras nao sao permitidas!\n");
                printf("MATRÍCULA: ");
                fgets(pessoas[tamanho].matricula, 50, stdin);
                pessoas[tamanho].matricula[strcspn(pessoas[tamanho].matricula, "\n")] = '\0';
                sai = 0;
                break;
            }
        }
    }
}

void valida_cpf(pessoa *pessoas,int tamanho){
    int sai;
    size_t tam = strlen(pessoas[tamanho].cpf);
    while(sai = 0){
        sai = 1;
        if((int)tam < 12 || (int)tam > 12){
            printf("Quantidade de numeros errada!\n");
            sai = 0;
        }
        else{
            for(int i = 0;i < (int)tam;i++){
                if(pessoas[tamanho].cpf < '0' || pessoas[tamanho].cpf > '9'){
                    printf("Letras nao sao permitidas!\n");
                    printf("CPF: ");
                    fgets(pessoas[tamanho].matricula, 50, stdin);
                    pessoas[tamanho].matricula[strcspn(pessoas[tamanho].matricula, "\n")] = '\0';
                    sai = 0;
                    break;
                }
            }
        }
    }
}
int valida_data(int dia, int mes, int ano){
    if(dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < 1){
        printf("Dia inexistente");
        return 0;
    }
    else{
        switch (mes){
            case 2:{
                if(dia > 29 || dia < 31){
                    return 0;
                }
                else if(dia == 29){
                    if(ano%4 == 0 &&(ano%100 != 0 || ano%400 == 0)){
                        return 1;
                    }
                    else{
                        printf("Fevereiro nesse ano eh menor que 29");
                        return 0;
                    }
                }
                else{
                    return 1;
                }
            }
            case 4: case 6: case 9: case 11:{
                if(dia > 30){
                    printf("Dia maior que 30");
                    return 0;
                }
                else
                    return 1;
            }
        }
    }
    return 1;
}
void valida_nascimento(pessoa *pessoas,int tamanho){
    int dia,mes,ano,sai;   
    while(sai == 0){
        sai = 1;
        if(sscanf(pessoas[tamanho].data,"%2d/%2d/%2d",&dia,&mes,&ano) == 3){
            if(valida_data(dia,mes,ano) == 0){
                sai = 0;
            }
            else
                sai = 1;
        }
        else{
            printf("Quantidade de numeros invalido!\n");
            sai = 0;
        }
        if (sai == 0){
            printf("DATA: ");
            fgets(pessoas[tamanho].data, 50, stdin);
            pessoas[tamanho].data[strcspn(pessoas[tamanho].data, "\n")] = '\0';
        }
    }
}


void valida_nomeD(discplina *disciplinas,int tamanho){
    int sai;
    size_t tamNOME = strlen(disciplinas[tamanho].nome);
    while(sai == 0){
        sai = 1;
        for(int i = 0;i < (int)tamNOME;i++){
            if(! (isalpha((unsigned char)disciplinas[i].nome) || (disciplinas[i].nome == ' '))){ 
                sai = 0;
                printf("O nome deve conter apenas letras e espacos!\n");
                printf("NOME: ");
                fgets(disciplinas[tamanho].nome, 50, stdin);
                disciplinas[tamanho].nome[strcspn(disciplinas[tamanho].nome, "\n")] = '\0';
                break;
            }
        }
    }   
}

void valida_codigo(disciplina *disciplinas,int tamanho){
    int sai;
    size_t tam = strlen(disciplinas[tamanho].codigo);
    while(sai = 0){
        sai = 1;
        for(int i = 0;i < (int)tam;i++){
            if(disciplinas[i].codigo < '0' || disciplinas[i].codigo > '9'){
                printf("Letras nao sao permitidas!\n");
                printf("CODIGO: ");
                fgets(disciplinas[tamanho].codigo, 50, stdin);
                disciplinas[tamanho].codigo[strcspn(disciplinas[tamanho].codigo, "\n")] = '\0';
                sai = 0;
                break;
            }
        }
    }
}

void valida_semestre(disciplina *disciplinas,int tamanho){
    int sai;
    size_t tam = strlen(disciplinas[tamanho].semestre);
    while(sai = 0){
        sai = 1;
        for(int i = 0;i < (int)tam;i++){
            if(disciplinas[i].semestre < '0' || disciplinas[i].semestre > '9'){
                printf("Letras nao sao permitidas!\n");
                printf("SEMESTRE: ");
                fgets(disciplinas[tamanho].semestre, 50, stdin);
                disciplinas[tamanho].semestre[strcspn(disciplinas[tamanho].semestre, "\n")] = '\0';
                sai = 0;
                break;
            }
        }
    }
}

void valida_professor(disciplina *disciplinas,int tamanho){
    int sai;
    size_t tamNOME = strlen(disciplinas[tamanho].professor);
    while(sai == 0){
        sai = 1;
        for(int i = 0;i < (int)tamNOME;i++){
            if(! (isalpha((unsigned char)disciplinas[i].professor) || (disciplinas[i].professor == ' '))){ 
                sai = 0;
                printf("O nome deve conter apenas letras e espacos!\n");
                printf("PROFESSOR: ");
                fgets(disciplinas[tamanho].professor, 50, stdin);
                disciplinas[tamanho].professor[strcspn(disciplinas[tamanho].professor, "\n")] = '\0';
                break;
            }
        }
    }   
}
