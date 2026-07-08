#include <stdio.h>
#include <stdlib.h>
//eu adicionei essa biblioteca:
#include <limits.h>
#define TAM 10

#include "trabalho2.h"

int *vetorPrincipal[TAM];

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho)
{
    
    int retorno = 0;

    // se posição é um valor válido {entre 1 e 10}
    //gabriel: aparentemente ele não que o usuário escreva zero para a primeira posicao. 
    if(posicao < 1 || posicao > 10)
        return POSICAO_INVALIDA;

    // o tamanho nao pode ser menor que 1
    if(tamanho < 1){
        return TAMANHO_INVALIDO;
    }
    
    if (vetorPrincipal[posicao - 1] != NULL) {
        return JA_TEM_ESTRUTURA_AUXILIAR;
    }

    vetorPrincipal[posicao - 1] = (int *)malloc((tamanho + 1) * sizeof(int));

    if (vetorPrincipal[posicao - 1] == NULL) {
        return SEM_ESPACO_DE_MEMORIA;
    }

    for (int i = 0; i < tamanho; i++) {
        vetorPrincipal[posicao - 1][i] = INT_MAX;
    }

    vetorPrincipal[posicao - 1][tamanho] = INT_MIN;

    return SUCESSO;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor)
{
    int retorno = 0;
    int existeEstruturaAuxiliar = 0;
    int temEspaco = 0;
    int posicao_invalida = 0;

    int backup_posicao = -1;
    // testando se a posição é válida
    if(posicao < 1 || posicao > 10)
        posicao_invalida = 1;

    if (posicao_invalida)
        retorno = POSICAO_INVALIDA;
    else
    {
        // testar se existe a estrutura auxiliar
        if(vetorPrincipal[posicao-1] != NULL)
            existeEstruturaAuxiliar = 1;

        if (existeEstruturaAuxiliar)
        {
            //percorrendo toda a estrutura auxiliar em busca de uma posicao
            for(int i = 0; vetorPrincipal[posicao-1][i] != INT_MIN; i++){
                if(vetorPrincipal[posicao-1][i] == INT_MAX){
                    backup_posicao = i;
                    break;
                }
            }
            // validando se existe um espaço
            if(backup_posicao != -1)
                temEspaco = 1;

            if (temEspaco)
            {
                //insere
                vetorPrincipal[posicao-1][backup_posicao] = valor;
                retorno = SUCESSO;
            }
            else
            {
                retorno = SEM_ESPACO;
            }
        }
        else
        {
            retorno = SEM_ESTRUTURA_AUXILIAR;
        }
    }

    return retorno;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao)
{   
    int retorno = SUCESSO;

    //criei variavel para armazenar minha busca por numeros na estrutura auxiliar
    int existe = 0;
    //se existir vou armazenar a ultima ocorrência
    int posicao_apagar = -1;

    if(posicao < 1 || posicao > 10)
        return POSICAO_INVALIDA;

    else if (vetorPrincipal[posicao-1] == NULL){
        return SEM_ESTRUTURA_AUXILIAR;
    }
    
    //vou percorrer toda a estrutura auxiliar para ver ela está vazia
    for(int i = 0; vetorPrincipal[posicao-1][i] != INT_MIN; i++){
        if(vetorPrincipal[posicao-1][i] != INT_MAX && vetorPrincipal[posicao-1][i] != INT_MIN){
            existe = 1;
            posicao_apagar = i;
        }
    }
    if (existe == 0)
    {
        return ESTRUTURA_AUXILIAR_VAZIA;
    }
    
    //como toda a estrutura auxiliar é preenchida por int_max, para apagar vou sobrescrever int_max no local.
    vetorPrincipal[posicao-1][posicao_apagar] = INT_MAX;

    return retorno;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{
    int retorno = SUCESSO;


    //criei variavel para armazenar minha busca por numeros na estrutura auxiliar
    int existe = 0;
    //se existir vou armazenar a ultima ocorrência
    int posicao_apagar = -1;
    //se existe outros numeros, mas não o que estou procurando
    int existe_num = -1;

    if(posicao < 1 || posicao > 10)
        return POSICAO_INVALIDA;

    else if (vetorPrincipal[posicao-1] == NULL){
        return SEM_ESTRUTURA_AUXILIAR;
    }
    
    //vou percorrer toda a estrutura auxiliar para ver ela está vazia
    for(int i = 0; vetorPrincipal[posicao-1][i] != INT_MIN; i++){
        if(vetorPrincipal[posicao-1][i] != INT_MAX && vetorPrincipal[posicao-1][i] != INT_MIN){
            existe = 1;
        }
        if(vetorPrincipal[posicao-1][i] == valor){
            existe_num = 1;
            posicao_apagar = i;
            break;
        }
    }
    if (existe == 0)
    {
        return ESTRUTURA_AUXILIAR_VAZIA;
    }
    else if (existe_num == -1)
    {
        return NUMERO_INEXISTENTE;
    }
    
    // Move todos os elementos seguintes uma posição para trás
    int i = posicao_apagar;
    while (vetorPrincipal[posicao-1][i + 1] != INT_MIN) {
        vetorPrincipal[posicao-1][i] = vetorPrincipal[posicao-1][i + 1];
        i++;
    }

    //como toda a estrutura auxiliar é preenchida por int_max, para apagar vou sobrescrever int_max no local.
    vetorPrincipal[posicao-1][i] = INT_MAX;
    return retorno;
}

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao)
{
    int retorno = 0;
    if (posicao < 1 || posicao > 10)
    {
        retorno = POSICAO_INVALIDA;
    }
    else
        retorno = SUCESSO;

    return retorno;
}
/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    int retorno = 0;

    if(posicao < 1 || posicao > 10)
        return POSICAO_INVALIDA;
    else if (vetorPrincipal[posicao-1] == NULL){
        return SEM_ESTRUTURA_AUXILIAR;
    }
    else{
        for(int i = 0, j = 0; vetorPrincipal[posicao-1][i] != INT_MIN; i++){
            if(vetorPrincipal[posicao-1][i] != INT_MAX){
                vetorAux[j] = vetorPrincipal[posicao-1][i];
                j++;
            }
        }
        return SUCESSO;
    }
    return retorno;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    int retorno = 0;
    //contar quantos valores eu enviei para vetorAux
    int count = 0;

    //mesmo código da função anterior:
    if(posicao < 1 || posicao > 10)
        return POSICAO_INVALIDA;
    else if (vetorPrincipal[posicao-1] == NULL){
        return SEM_ESTRUTURA_AUXILIAR;
    }
    else{
        for(int i = 0, j = 0; vetorPrincipal[posicao-1][i] != INT_MIN; i++){
            if(vetorPrincipal[posicao-1][i] != INT_MAX){
                vetorAux[j] = vetorPrincipal[posicao-1][i];
                j++;
                count = j;
            }
        }   
    }

    //ordenando vetorAux
    int menor = vetorAux[0];
    int indice_j = 0;
    int backup = 0;
    for(int i = 0; i < count - 1; i++){
        menor = vetorAux[i];
        indice_j = i; 

        for(int j = i + 1; j < count; j++){
            if(menor > vetorAux[j]){
                menor = vetorAux[j];
                indice_j = j;
            }
        }
        
       
        backup = vetorAux[i];
        vetorAux[i] = vetorAux[indice_j];
        vetorAux[indice_j] = backup;
    }
    return SUCESSO;
    return retorno;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{

    int retorno = 0;
    //contar quantas estrutas auxiliaries estão vazias
    int count = 0;
    //armazenar a quantidade de numeros dentro de todas as estruturas auxiliares
    int count_num = 0;

    for(int j = 0; j < 10; j++){
        if (vetorPrincipal[j] == NULL){
            count++;
        }
        else{
        for(int i = 0; vetorPrincipal[j][i] != INT_MIN; i++){
            if(vetorPrincipal[j][i] != INT_MAX){
                vetorAux[count_num] = vetorPrincipal[j][i];
                count_num++;
               
                    }
                }   
            }   
    }

    if(count_num == 0)
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    else
        return SUCESSO;
    return retorno;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{

    int retorno = 0;
    //armazenar a quantidade de numeros dentro de todas as estruturas auxiliares
    int count_num = 0;

    for(int j = 0; j < 10; j++){
        if (vetorPrincipal[j] == NULL){
            
        }
        else{
        for(int i = 0; vetorPrincipal[j][i] != INT_MIN; i++){
            if(vetorPrincipal[j][i] != INT_MAX){
                vetorAux[count_num] = vetorPrincipal[j][i];
                count_num++;
               
                    }
                }   
            }   
    }

    if(count_num == 0)
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;

    //ordenando vetorAux
    int menor = vetorAux[0];
    int indice_j = 0;
    int backup = 0;
    for(int i = 0; i < count_num - 1; i++){
        menor = vetorAux[i];
        indice_j = i; 

        for(int j = i + 1; j < count_num; j++){
            if(menor > vetorAux[j]){
                menor = vetorAux[j];
                indice_j = j;
            }
        }
        
       
        backup = vetorAux[i];
        vetorAux[i] = vetorAux[indice_j];
        vetorAux[indice_j] = backup;
    }

    return SUCESSO;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{
    if (posicao < 1 || posicao > 10)
        return POSICAO_INVALIDA;
    else if (vetorPrincipal[posicao-1] == NULL){
        return SEM_ESTRUTURA_AUXILIAR;
    }
    
    // 1. Descobrir o tamanho antigo (x)
    int tamanhoAntigo = 0;
    while(vetorPrincipal[posicao-1][tamanhoAntigo] != INT_MIN){
        tamanhoAntigo++;
    }

    // O tamanho final resultante será o antigo (x) + o novo (n)
    int tamanhoFinal = tamanhoAntigo + novoTamanho;

    // Regra: o tamanho resultante x + n deve ser sempre >= 1
    if(tamanhoFinal < 1){
        return NOVO_TAMANHO_INVALIDO;
    }
    
    // 2. CORREÇÃO: Salvar o retorno do realloc em um ponteiro temporário
    int *novo_ponteiro = realloc(vetorPrincipal[posicao-1], sizeof(int) * (tamanhoFinal + 1));
    
    // CORREÇÃO: O teste de falta de memória deve ser feito IMEDIATAMENTE aqui
    if(novo_ponteiro == NULL){
        return SEM_ESPACO_DE_MEMORIA;
    }
    
    // Agora que sabemos que deu certo, atualizamos o vetor principal
    vetorPrincipal[posicao-1] = novo_ponteiro;

    // 3. CORREÇÃO: Preencher o espaço adicionado com INT_MAX usando limite fixo e seguro
    for(int x = tamanhoAntigo; x < tamanhoFinal; x++){
         vetorPrincipal[posicao-1][x] = INT_MAX;
    }

    // 4. Cravar o INT_MIN no novo final absoluto
    vetorPrincipal[posicao-1][tamanhoFinal] = INT_MIN;

    return SUCESSO;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{

    int retorno = 0;

    //contar elementos da estrutura auxiliar
    int count_elemento = 0;

    //criei variavel para armazenar minha busca por numeros na estrutura auxiliar
    int existe = 0;

    if(posicao < 1 || posicao > 10)
        return POSICAO_INVALIDA;

    else if (vetorPrincipal[posicao-1] == NULL){
        return SEM_ESTRUTURA_AUXILIAR;
    }
    
    //vou percorrer toda a estrutura auxiliar para ver ela está vazia
    for(int i = 0; vetorPrincipal[posicao-1][i] != INT_MIN; i++){
        if(vetorPrincipal[posicao-1][i] != INT_MAX && vetorPrincipal[posicao-1][i] != INT_MIN){
            count_elemento++;
            existe = 1;
        }
    }
    if (existe == 0)
    {
        return ESTRUTURA_AUXILIAR_VAZIA;
    }
    
    return count_elemento;

    return retorno;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote()
{
    No *lista = malloc(sizeof(No));
    lista->prox = NULL;

    
    int qtd_elementos = 0;

    for(int i = 1; i <= 10; i++){
        if(getQuantidadeElementosEstruturaAuxiliar(i) > 0)
            qtd_elementos += getQuantidadeElementosEstruturaAuxiliar(i);
    }

    int vetor[qtd_elementos];
    int situacao = getDadosDeTodasEstruturasAuxiliares(vetor);

    if(situacao == TODAS_ESTRUTURAS_AUXILIARES_VAZIAS){
        free(lista);
        return NULL;}

    for(int i = 0; i < qtd_elementos; i++){
        No *novo = malloc(sizeof(No));
        if (novo == NULL) return lista;

        novo->conteudo = vetor[i];
        No *sentinela = lista;

        while(sentinela->prox != NULL){
            sentinela = sentinela->prox;
        }
        sentinela->prox = novo;
        
    }
    return lista;
    
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
    No * atual = inicio->prox;
    int count = 0;

    while(atual){
        vetorAux[count] = atual->conteudo;
        count++;
        atual = atual->prox;
    }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio)
{
    No *atual = *inicio;
    No *proximo = *inicio;
    while(atual != NULL){
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    *inicio = NULL;
}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 

*/

void inicializar()
{
    // Percorre o vetor principal apontando cada posição para NULL
    for (int i = 0; i < TAM; i++) {
        vetorPrincipal[i] = NULL;
    }
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar()
{
    // Percorre todo o vetor principal
    for (int i = 0; i < TAM; i++) {
        // Se a estrutura auxiliar foi alocada (é diferente de NULL), libere-a
        if (vetorPrincipal[i] != NULL) {
            free(vetorPrincipal[i]);
            vetorPrincipal[i] = NULL; 
        }
    }
}
