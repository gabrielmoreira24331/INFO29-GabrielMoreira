#include <stdio.h>
#include <string.h>
int valida_nome(char *nome){

    int invalido;
    size_t tam = strlen(nome);
    invalido = 1;
    for(int i = 0;i < (int)tam+1;i++){
        if(((nome[i] < 'A' || nome[i] > 'Z') && (nome[i] < 'a' || nome[i] > 'z')) || (nome[i] != ' ')){ 
            invalido = 1;
            break;
        }
        else{
            invalido = 0;
        }
    }
    if(invalido == 0){
        return 1;
    }   
    else{
        printf("O nome deve conter so letras e espacos!\n");
        return 0;
    }
        
}
int valida_numero(char *numero,int tamNUM){
    int invalido;
    size_t tam = strlen(numero);
    if((int)tam < tamNUM){
        printf("Numeros insuficientes!\n");
        return 0;
    }
    else{
        invalido = 1;
        for(int i = 0;i < (int)tam+1;i++){
            if(numero[i] < '0' || numero[i] > '9'){
                printf("Letras nao sao permitidas!\n");
                invalido = 0;
                break;
            }
        }
        if(invalido == 0)
            return 0;
        else
            return 1;
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
}
int valida_nascimento(char *nascimento){
    int dia,mes,ano;
   
    if(sscanf(nascimento,"%2d/%2d/%2d",&dia,&mes,&ano) == 3){
        if(valida_data(dia,mes,ano) == 0){
            return 0;
        }
        else
            return 1;
    }
    else{
        printf("Quantidade de numeros invalido!\n");
        return 0;
    }
    return 1;
}
