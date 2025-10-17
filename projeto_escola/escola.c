#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "escola.h"
#include "disciplinas.h"
#include "relatorios.h"


#define TAM_ALUNO 50


int main(void)
{
    int sair = 0, sair_menu = 0;
    int opcao = 0, opcao_menu = 0; 
    pessoa alunos[TAM_ALUNO];
    pessoa professores[TAM_ALUNO];
    disciplina disciplinas[TAM_ALUNO];
    int q_alunos = 0;
    int q_professor = 0;
    int q_disciplina = 0;
    int retorno = 0;
    int atualiza = 0;

    preencher_dados_teste(alunos, &q_alunos, professores, &q_professor, disciplinas, &q_disciplina);

    while (!sair)
    {
        opcao = menugeral();
        sair_menu = 0;

        switch(opcao)
        {
            case 0:{
                sair = 1;
                break;
            }
            case 1:{
                while (!sair_menu)
                {
                    opcao_menu = menu_pessoa("Aluno");

                    switch(opcao_menu)
                    {
                        case 0:
                        {
                            sair_menu = 1;
                            break;
                        }
                        case 1:
                        {
                            cadastrar_pessoa(q_alunos, alunos);
                            q_alunos++;
                            break;
                        }
                        case 2:{
                            listar_pessoas(q_alunos, alunos);
                            break;
                        }
                        case 3:{
                            
                            atualiza = atualiza_pessoa(q_alunos, alunos);
                        
                            if (atualiza == pessoa_inexistente)
                            {
                                printf("Matricula digitada não pertence a nenhum aluno cadastrado!!\n");
                            }
                            else if(atualiza == 0)
                            {
                                printf("Aluno atualizado com sucesso\n");
                            }
                            break;
                        }
                        case 4:{
                            retorno = excluir_pessoa(q_alunos, alunos);
                            
                            if (retorno == excluido)
                            {
                                q_alunos--;
                                printf("Aluno excluido com sucesso\n");
                            }
                            else if(retorno == pessoa_inexistente)
                                printf("Aluno não existe ou a matrícula foi digida incorretamente\n");
                            break;
                        }

                    }

                } 
                break;
            }
            
            case 2:{
                 while (!sair_menu)
                {
                    opcao_menu = menu_pessoa("Professor");

                    switch(opcao_menu)
                    {
                        case 0:
                        {
                            sair_menu = 1;
                            break;
                        }
                        case 1:
                        {
                            cadastrar_pessoa(q_professor, professores);
                            q_professor++;
                            break;
                        }
                        case 2:{
                            listar_pessoas(q_professor, professores);
                            break;
                        }
                        case 3:{
                            
                            atualiza = atualiza_pessoa(q_professor, professores);
                        
                            if (atualiza == pessoa_inexistente)
                            {
                                printf("Matricula digitada não pertence a nenhum professor cadastrado!!\n");
                            }
                            else if (atualiza == 0)
                            {
                                printf("professor atualizado com sucesso\n");
                            }
                            break;
                        }
                        case 4:{
                            int retorno = excluir_pessoa(q_professor, professores);
                            
                            if (retorno == excluido)
                            {
                                q_professor--;
                                printf("professor excluido com sucesso\n");
                            }
                            else if(retorno == pessoa_inexistente)
                                printf("professor não existe ou a matrícula foi digida incorretamente\n");
                            break;
                        }

                    }

                } 
                break;

               
            }
            case 3:{
                printf("Disciplinas\n");
                while(!sair_menu)
                {
                    opcao_menu = menu_disciplina();

                    switch(opcao_menu)
                    {
                        case 0:{
                            sair_menu = 1;
                            break;
                        }
                        case 1:{
                            int dp = cadastrar_disciplina(q_disciplina, disciplinas, q_professor, professores);
                            if (dp == invalido)
                            {
                                printf("o professor não existe ou você digigou incorretamente\n");
                            }
                            else if(dp == 0)
                            {
                                q_disciplina++;
                            }
                            break;
                        }
                        case 2:{
                            int lista_dp = listar_disciplina(q_disciplina, disciplinas, q_alunos, alunos);
                            break;
                        }
                        case 3:{
                            int atualizar_dp = atualizar_disciplina(q_disciplina, disciplinas, q_professor, professores);
                            break;
                        }
                        case 4:{
                            int excluir_dp = excluir_disciplina(q_disciplina, disciplinas, q_alunos, alunos);

                            if (excluir_dp == vazio)
                            {
                                printf("nenhuma disciplina cadastrada\n");
                            }
                            else if(excluir_dp == pessoa_inexistente)
                            {
                                printf("A disciplina digitada pelo usuário não existe\n");
                            }
                            else if(excluir_dp == excluido)
                            {
                                printf("disciplina excluida com sucesso\n");
                            }
                            q_disciplina--;
                            break;
                        }
                        case 5:{
                            int incluir = incluir_aluno(q_disciplina, disciplinas, q_alunos, alunos);
                            break;
                        }
                        case 6:{
                            int excluir = excluir_aluno(q_disciplina, disciplinas, q_alunos, alunos);
                            break;
                        }
                    }
                }
                break;
            }
            case 4:{
                while (!sair_menu)
                {
                    opcao_menu = menu_relatorio();
                    switch(opcao_menu)
                    {
                        case 0:{
                            sair_menu = 1;
                            break;
                        }
                        case 1:{
                            exibir_disciplinas(q_disciplina, disciplinas);
                            break;
                        }
                        case 2:{
                            int exibir = exibir_disciplina(q_disciplina, disciplinas, q_alunos, alunos);
                            break;
                        }
                        case 3:{
                            int exibir = listar_alunos_sexo(q_alunos, alunos);
                            break;
                        }
                        case 4:{
                            ordenar_lista(q_alunos, alunos);
                            listar_pessoas(q_alunos, alunos);
                            break;
                        }
                        case 5:{
                            ordenar_data(q_alunos, alunos);
                            listar_pessoas(q_alunos, alunos);
                            break;
                        }
                        case 6:{
                            int exibir = listar_alunos_sexo(q_professor, professores);
                            break;
                        }
                        case 7:{
                            ordenar_lista(q_professor, professores);
                            listar_pessoas(q_professor, professores);
                            break;
                        }
                        case 8:{
                            ordenar_data(q_professor, professores);
                            listar_pessoas(q_professor, professores);
                            break;
                        }
                        case 9:{
                            aniversarintes_mes(q_alunos, alunos, q_professor, professores);
                            break;
                        }
                        case 10:{
                            busca_3letras(q_alunos, alunos, q_professor, professores);
                            break;
                        }
                        case 11:{
                            matriculados(q_alunos, alunos);
                            break;
                        }
                        case 12:{
                            disciplinas_cheias(q_alunos, alunos, q_disciplina, disciplinas);
                            break;
                        }

                    }
                }
                break;
            }
            default:{
                printf("opção invalida!\n");
                break;
            }    
        }
    }
}

