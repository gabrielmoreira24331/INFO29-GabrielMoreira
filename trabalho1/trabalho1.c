// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Gabriel Moreira Lima
//  email: 20251160039@ifba.edu.br
//  Matrícula: 20251160039
//  Semestre: 2

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016 - 17/10/2025

// #################################################

#include <stdio.h>
#include "trabalho1.h" 
#include <stdlib.h>
#include <string.h>

DataQuebrada quebraData(char data[]);
int down(int x, int y, char matriz[8][10], char palavra[5]);
int up(int x, int y, char matriz[8][10], char palavra[5]);
int left(int x, int y, char matriz[8][10], char palavra[5]);
int right(int x, int y, char matriz[8][10], char palavra[5]);
int ehBissexto(int ano);

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = calcular o fatorial de um número
@objetivo
    Calcular o fatorial de um número inteiro passado por parâmetro
@entrada
    um inteiro x
@saida
    fatorial de x (x!)
 */
int fatorial(int x)
{ 
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos válidos: d/m/aaaa, dd/mm/aaaa, d/mm/aaaa, dd/m/aaaa
@saida
    0 -> se data inválida
    1 -> se data válida
    vazio
 */
int q1(char data[])
{
    int datavalida = 1;
    DataQuebrada datas; 

    datas = quebraData(data);

    if (datas.valido == 0)
        return 0;
    if (datas.iMes < 1 || datas.iMes > 12 || datas.iAno < 10 || datas.iAno > 9999 || datas.iDia < 1 || datas.iDia > 31) 
        return 0;
    
    if ((datas.iMes == 4 || datas.iMes == 6 || datas.iMes == 9 || datas.iMes == 11) && datas.iDia > 30)
        return 0;
        
    if (!ehBissexto(datas.iAno))
    {
        if(datas.iMes == 2 && datas.iDia > 28)
            return 0;
    }
    else
    {
        if(datas.iMes == 2 && datas.iDia > 29)
            return 0;
    }

    if (datavalida)
        return 1;
    else
        return 0;
}

int ehBissexto(int ano)
{
    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0))
        return 1;
    return 0;
}

/*
 Q2 = diferença entre duas datas
@objetivo
    Calcular a diferença em dias, meses e anos entre duas datas
@entrada
    uma string data Inicial, uma string data Final. Formatos válidos: d/m/aaaa, dd/mm/aaaa, d/mm/aaaa, dd/m/aaaa
@saida
    DiasMesesAnos - Estrutura DiasMesesAnos com cada quantidade com seu respectivo valor
    DiasMesesAnos.retorno = 1 -> cálculo realizado com sucesso
    DiasMesesAnos.retorno = 2 -> data inicial inválida
    DiasMesesAnos.retorno = 3 -> data final inválida
    DiasMesesAnos.retorno = 4 -> data inicial maior que data final
 */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{
    DiasMesesAnos dma;
    DataQuebrada idata = quebraData(datainicial);
    DataQuebrada fdata = quebraData(datafinal);
    
    int mdias[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (q1(datainicial) == 0){
      dma.retorno = 2;
      return dma;
    }
    else if (q1(datafinal) == 0){
      dma.retorno = 3;
      return dma;
    }
    else if(idata.iAno > fdata.iAno || (idata.iAno == fdata.iAno && idata.iMes > fdata.iMes) || (idata.iAno == fdata.iAno && idata.iMes == fdata.iMes && idata.iDia > fdata.iDia))
    {
        dma.retorno = 4;
        return dma;
    }
    else{
        int anos = fdata.iAno - idata.iAno;
        int meses = fdata.iMes - idata.iMes;
        int dias = fdata.iDia - idata.iDia;

        if (dias < 0) {
            meses--;
            int mesAnterior = fdata.iMes - 1;
            if (mesAnterior == 0) mesAnterior = 12;
            int diasNoMes = mdias[mesAnterior - 1];
            if (mesAnterior == 2 && ehBissexto(fdata.iAno)) {
                diasNoMes = 29;
            }
            dias += diasNoMes;
        }

        if (meses < 0) {
            anos--;
            meses += 12;
        }

        dma.qtdDias = dias;
        dma.qtdMeses = meses;
        dma.qtdAnos = anos;
        dma.retorno = 1;
        return dma;
    }
}

/*
 Q3 = encontrar caracter em texto
@objetivo
    Contar a quantidade de ocorrências de um caracter em um texto
@entrada
    uma string texto, um caracter c, um inteiro isCaseSensitive (1 - considerado maiúsculo diferete de minúsculo, 0 - não considerado)
@saida
    Um inteiro com a quantidade de ocorrências do caracter c no texto
 */
int q3(char *texto, char c, int isCaseSensitive)
{
    int qtdOcorrencias = 0;

    if(isCaseSensitive == 1){
        for(int x = 0; texto[x] != '\0'; x++)
        {
            if(texto[x] == c)
            {
                qtdOcorrencias++;
            }
        }
    }
    else{
        for(int x = 0; texto[x] != '\0'; x++)
        {
            char tAtual = texto[x];
            char cBusca = c;
            if (tAtual >= 'A' && tAtual <= 'Z') tAtual += 32;
            if (cBusca >= 'A' && cBusca <= 'Z') cBusca += 32;

            if(tAtual == cBusca)
                qtdOcorrencias++;
        }
    }

    return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
@objetivo
    Contar a quantidade de ocorrências de uma palavra em um texto e listar as posições iniciais e finais de cada ocorrência da palavra no texto
@entrada
    uma string texto, uma string busca, um vetor de inteiros com tamanho 30
@saida
    Um inteiro com a quantidade de ocorrências da palavra no texto
 */
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
    int qtdOcorrencias = 0;
    int p_inicial = 0;
    int p_final = 0;
    int t = -1;
    int count = 0;
    int tamBusca = 0;

    while(strBusca[tamBusca] != '\0') tamBusca++;

    for(int x = 0; strTexto[x] != '\0'; x++)
    {
        if(strTexto[x] == strBusca[0])
        {
            p_inicial = x + 1;
            p_final = x + 1; 

            t = -1;

            for(int y = 1; y < tamBusca; y++)
            {
                if(strTexto[x+y] == '\0' || strTexto[x+y] != strBusca[y])
                {
                    t = 1;
                    break;
                }

                p_final = x + y + 1;
            }

            if(t == -1 && count < 30)
            {
                posicoes[count] = p_inicial;
                count++;

                posicoes[count] = p_final;
                count++;

                qtdOcorrencias++;
            }
        }
    }

    return qtdOcorrencias;
}

/*
 Q5 = inverte número
@objetivo
    Inverter número inteiro
@entrada
    uma int num
@saida
    Número invertido
 */
int q5(int num)
{
    int m = 1;
    int backup = num;
    while(backup > 0)
    {
        backup = backup / 10;
        m *= 10;
    }

    while(m != 1)
    {
        backup += (num % 10) * m;
        num = num / 10;
        m = m / 10;
    }
    num = backup;
    return num/10;
}

/*
 Q6 = ocorrência de um número em outro
@objetivo
    Verificar quantidade de vezes que um número de busca aparece em um número de base
@entrada
    um inteiro numeroBase, um inteiro numeroBusca
@saida
    Um inteiro com a quantidade de ocorrências
 */
int q6(int numerobase, int numerobusca)
{
    int qtdOcorrencias = 0;
    int bk = numerobusca;
    int m = 1;

    if (numerobusca == 0) m = 10;
    else {
        while (bk > 0) {
            bk /= 10;
            m *= 10;
        }
    }

    while (numerobase > 0) {
        if ((numerobase % m) == numerobusca)
            qtdOcorrencias++;

        numerobase /= 10;  
    }

    return qtdOcorrencias;
}
   
/*
 Q7 = jogo busca palavras
@objetivo
    Verificar se uma palavra está cadastrada em uma matriz de caça palavras
@entrada
    uma matriz de caracteres 8x10 e uma string palavra a ser buscada
@saida
    1 -> se encontrou a palavra
    0 -> se não encontrou a palavra
 */
int q7(char matriz[8][10], char palavra[5])
{       
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 10; y++)
        {
            if(matriz[x][y] == palavra[0])
            {
               if(down(x, y, matriz, palavra) == 0 || up(x, y, matriz, palavra) == 0 || left(x, y, matriz, palavra) == 0 || right(x, y, matriz, palavra) == 0)
                    return 1;
            }
        }
    }
    return 0;       
}

/*
## função utilizada para testes  ##

 quebraData = quebra uma string de data em três inteiros (dia, mês, ano)
@objetivo
    Quebrar uma string de data nos inteiros correspondentes de dia, mês e ano
@entrada
    uma string data. Formatos válidos: d/m/aaaa, dd/mm/aaaa, d/mm/aaaa, dd/m/aaaa
@saida
    Estrutura DataQuebrada com os inteiros de dia, mês e ano e um campo válido (1 data válida, 0 data inválida)
 */
DataQuebrada quebraData(char data[]){
    DataQuebrada dq;
    char sDia[3];
    char sMes[3];
    char sAno[5];
    int i; 

    for (i = 0; data[i] != '/'; i++){
        sDia[i] = data[i];  
    }
    if(i == 1 || i == 2){ 
        sDia[i] = '\0';  
    }else {
        dq.valido = 0;
        return dq;
    }  

    int j = i + 1; 
    i = 0;

    for (; data[j] != '/'; j++){
        sMes[i] = data[j];
        i++;
    }

    if(i == 1 || i == 2){ 
        sMes[i] = '\0';  
    }else {
        dq.valido = 0;
        return dq;
    }

    j = j + 1; 
    i = 0;
    
    for(; data[j] != '\0'; j++){
        sAno[i] = data[j];
        i++;
    }

    if(i == 2 || i == 4){ 
        sAno[i] = '\0';  
    }else {
        dq.valido = 0;
        return dq;
    }

    dq.iDia = atoi(sDia);
    dq.iMes = atoi(sMes);
    dq.iAno = atoi(sAno); 

    if (i == 2) {
        if (dq.iAno >= 0 && dq.iAno <= 26) dq.iAno += 2000;
        else dq.iAno += 1900;
    }

    dq.valido = 1;
    
    return dq;
}

int down(int x, int y, char matriz[8][10], char palavra[5])
{
    int tam = strlen(palavra);
    if(x + tam <= 8)
    {
        for(int a = 1; a < tam; a++)
        {
            if(matriz[x+a][y] != palavra[a])
                return -1;
        }
        return 0;
    }
    return -1;
}

int up(int x, int y, char matriz[8][10], char palavra[5])
{
    int tam = strlen(palavra);
    if(x - tam + 1 >= 0)
    {
        for(int a = 1; a < tam; a++)
        {
            if(matriz[x - a][y] != palavra[a])
                return -1;
        }
        return 0;
    }
    return -1;
}

int left(int x, int y, char matriz[8][10], char palavra[5])
{
    int tam = strlen(palavra);
    if(y - tam + 1 >= 0)
    {
        for(int a = 1; a < tam; a++)
        {
            if(matriz[x][y - a] != palavra[a])
                return -1;
        }
        return 0;
    }
    return -1;
}

int right(int x, int y, char matriz[8][10], char palavra[5])
{
    int tam = strlen(palavra);
    if(y + tam <= 10)
    {
        for(int a = 1; a < tam; a++)
        {
            if(matriz[x][y + a] != palavra[a])
                return -1;
        }
        return 0;
    }
    return -1;
}
