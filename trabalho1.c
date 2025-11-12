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

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
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
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[])
{
    int datavalida = 1;
    DataQuebrada datas; 

    //quebrar a string data em strings sDia, sMes, sAno
    datas = quebraData(data);

    //printf("%s\n", data);
    if (datas.valido == 0)
        return 0;
    if (datas.iMes < 1 || datas.iMes > 12 || datas.iAno < 10 || datas.iAno > 9999 || datas.iDia < 1 || datas.iDia > 31) 
        return 0;
    if (datas.iMes == 4 || datas.iMes == 6 || datas.iMes == 9 || datas.iMes == 11 && datas.iDia > 30)
        return 0;
    if ((datas.iAno % 4) != 0 || (datas.iAno % 4) == 0 && (datas.iAno % 100) == 0 && (datas.iAno % 400) != 0)
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



/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{

    //calcule os dados e armazene nas três variáveis a seguir
    DiasMesesAnos dma;
    DataQuebrada idata = quebraData(datainicial);
    DataQuebrada fdata = quebraData(datafinal);
    int mdias = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int i = 0, f = 0;

    if (q1(datainicial) == 0){
      dma.retorno = 2;
      return dma;
    }
    else if (q1(datafinal) == 0){
      dma.retorno = 3;
      return dma;
    }
    else if(idata.iAno > fdata.iAno || idata.iAno == fdata.iAno && idata.iMes > fdata.iMes || idata.iAno == fdata.iAno && idata.iMes == fdata.iMes && idata.iDia > fdata.iDia)
    {
        dma.retorno = 4;
        return dma;
    }
    else{
       

        dma.retorno = 1;
        return dma;
    }
    
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
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
            if(c >= 'a' && c <= 'z')
            {
                if(c == texto[x] || c-32 == texto[x])
                    qtdOcorrencias++;
            }
            else
            {
                if(c == texto[x] || c+32 == texto[x])
                    qtdOcorrencias++;
            }
        }
    }

    return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
    int qtdOcorrencias = -1;

    return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
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
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{
     int qtdOcorrencias = 0;
    int bk = numerobusca;
    int m = 1;

    while (bk > 0) {
        bk /= 10;
        m *= 10;
    }

    while (numerobase > 0) {
        if ((numerobase % m) == numerobusca)
            qtdOcorrencias++;

        numerobase /= 10;  // avança um dígito
    }

    return qtdOcorrencias;
}
   
/*
 Q7 = jogo busca palavras
 @objetivo
    Verificar se existe uma string em uma matriz de caracteres em todas as direções e sentidos possíves
 @entrada
    Uma matriz de caracteres e uma string de busca (palavra).
 @saida
    1 se achou 0 se não achou
 */

 int q7(char matriz[8][10], char palavra[5])
{       
    int achou = 1;
    for(int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 10; y++)
        {
            if(matriz[x][y] == palavra[0])
            {
               if(down(x, y, matriz, palavra) == 0 ||  up(x, y, matriz, palavra) == 0 ||  left(x, y, matriz, palavra) == 0 ||  right(x, y, matriz, palavra) == 0)
                    return achou;
            }
        }
    }
    return achou-1;       
 }



DataQuebrada quebraData(char data[]){
  DataQuebrada dq;
  char sDia[3];
	char sMes[3];
	char sAno[5];
	int i; 

	for (i = 0; data[i] != '/'; i++){
		sDia[i] = data[i];	
	}
	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sDia[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }  
	

	int j = i + 1; //anda 1 cada para pular a barra
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sMes[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }
	

	j = j + 1; //anda 1 cada para pular a barra
	i = 0;
	
	for(; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
		sAno[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno); 

	dq.valido = 1;
    
  return dq;
}

int down(int x, int y, char matriz[8][10], char palavra[5])
{
    if(x + strlen(palavra) <= 8)
    {
        for(int a = 1; a < strlen(palavra); a++)
        {
            if(matriz[x+a][y] != palavra[a])
                return -1;
        }
        return 0;
    }
    else
        return -1;
}

int up(int x, int y, char matriz[8][10], char palavra[5])
{
    if(x - strlen(palavra) + 1 >= 0)
    {
        for(int a = 1; a < strlen(palavra); a++)
        {
            if(matriz[x - a][y] != palavra[a])
                return -1;
        }
        return 0;
    }
    else
        return -1;
}

int left(int x, int y, char matriz[8][10], char palavra[5]){
    if(y + strlen(palavra) <= 10)
    {
        for(int a = 1; a < strlen(palavra); a++)
        {
            if(matriz[x][y+a] != palavra[a])
                return -1;
        }
        return 0;
    }
    else
        return -1;
}

int right(int x, int y, char matriz[8][10], char palavra[5])
{
    if(y - strlen(palavra) + 1 >= 0)
    {
        for(int a = 1; a < strlen(palavra); a++)
        {
            if(matriz[x][y-a] != palavra[a])
                return -1;
        }
        return 0;
    }
    else
        return -1;
}
    