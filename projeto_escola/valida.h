#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int validar_nome(char nome[]) {
    int len = strlen(nome);
    if (len == 0) return 0; // vazio
    
    if (isspace(nome[0]) || isspace(nome[len-1]))
        return 0; // não pode começar ou terminar com espaço

    for (int i = 0; i < len; i++) {
        if (!isalpha(nome[i]) && !isspace(nome[i]))
            return 0; // caractere inválido
        // não permitir múltiplos espaços seguidos
        if (i > 0 && isspace(nome[i]) && isspace(nome[i-1]))
            return 0;
    }
    return 1;
}

int validar_matricula(char matricula[]) {
    int len = strlen(matricula);
    if (len == 0) return 0;
    for (int i = 0; i < len; i++) {
        if (!isalnum(matricula[i]))
            return 0;
    }
    return 1;
}

int validar_data(char data[]) {
    int dia, mes, ano;
    if (sscanf(data, "%d/%d/%d", &dia, &mes, &ano) != 3)
        return 0;
    if (ano < 1900 || mes < 1 || mes > 12 || dia < 1)
        return 0;

    int dias_mes[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    // ano bissexto
    if ((ano%4==0 && ano%100!=0) || (ano%400==0)) dias_mes[2]=29;
    if (dia > dias_mes[mes])
        return 0;

    return 1;
}

int validar_cpf(char cpf[]) {
    int len = strlen(cpf);
    if (len != 11) return 0; // CPF com 11 dígitos
    for (int i = 0; i < len; i++) {
        if (!isdigit(cpf[i]))
            return 0;
    }
    return 1;
}

int validar_sexo(char sexo) {
    if (sexo == 'M' || sexo == 'F')
        return 1;
    return 0;
}

int validar_codigo(char codigo[]) {
    int len = strlen(codigo);
    if (len == 0) return 0;
    for (int i = 0; i < len; i++) {
        if (!isalnum(codigo[i]))
            return 0;
    }
    return 1;
}

int validar_semestre(char semestre[]) {
    int len = strlen(semestre);
    if (len == 0) return 0;
    for (int i = 0; i < len; i++) {
        if (!isdigit(semestre[i]) && semestre[i] != '/')
            return 0;
    }
    return 1;
}
