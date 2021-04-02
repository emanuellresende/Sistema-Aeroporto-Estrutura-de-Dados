
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "leitura.h"
#include "Grafo.h"

Tipo_Voo *ler(GRAFO *voos, TypeGraphMatriz *rotas, FILE *arq, int vertices, Aeroporto *aeroporto)
{
    rewind(arq); // VOlta o arquivo pro inicio
    char lixo[500];
    char de[10];
    char para[10];
    char identificador[10];
    int duracao;
    char horario[10];
    char abreviacao_cidade[4];
    char nome_cidade[30];
    char nome_aeroporto[30];
    int i = 0;
    int bb = 0;
    char hora_duracao[10];
    Aeroporto aux_adj;
    int xi = 0, xy = 0;
    Tipo_Voo *dados_voo = malloc(sizeof(Tipo_Voo));
    while (!feof(arq))
    {

        switch (fgetc(arq))
        {

        case '#': // Se achar esse caractere vai simplismente ignorar por ser comentario

            fscanf(arq, "%[^\n]s", lixo);
            fgetc(arq);

            break;

        case '$': // Caracter generico usado para controle

            for (i = 0; i < vertices; i++)
            {

                fgetc(arq); // Le o \n depois do caracter $

                fscanf(arq, "%s", aeroporto[i].sigla); // Pega o nome da abreviacao

                fgetc(arq); // Pega o espaco

                fscanf(arq, "%[^(]s", aeroporto[i].cidade); // Le o nome da cidade

                fgetc(arq); // Pega o espaco

                fscanf(arq, "%[^)]s", aeroporto[i].aeroporto); // Le o nome do aeroporto
            }
            fgetc(arq); // Removeo )
            //Remove os ultimos \n
            fgetc(arq);
            fgetc(arq);
            fgetc(arq);

            break;

        case '!': // Caracter generico de controle
            while (1)
            {
                int aux_conexao1 = 0, aux_conexao2 = 0; // Variaveis para auxiliar para setar as conexoes
                fgetc(arq);                             // Le o \n depois do !

                fscanf(arq, "%s", de); // Pega a conexao

                if (strcmp(de, "!") == 0) // Caso a conexao seja o caracter de pause
                    break;

                fgetc(arq); // Pega o espaco

                fscanf(arq, "%s", para); // Le o para

                fgetc(arq); // Le o \n

                /*Procurando a conexao DE*/

                ///
                xi = pesquisar_id_voo(voos, de, aeroporto); // Retorna o ID do Aeroporto
                xy = pesquisar_id_voo(voos, para, aeroporto);

                rotas->Mat[xi][xy] = 1;
                rotas->qntArestas += 1;

              
            }
            break;

        case '%':
            i = 0;
            while (1)
            {
                xi = 0;
                xy = 0;
                fgetc(arq); // Le o \n depois do caracter %

                fscanf(arq, "%s", identificador);

                //Se encontrar o caracter final ira parar
                if (strcmp(identificador, "%") == 0)
                    break;

                fgetc(arq); // Le o espaco

                fscanf(arq, "%s", de); // Le a origem

                fgetc(arq); // Le o espaco

                fscanf(arq, "%s", para); // Le o destino

                fgetc(arq); // Le o espaco

                fscanf(arq, "%d", &duracao); // Le a duracao

                fgetc(arq); // Le o espaco

                fscanf(arq, "%d", &bb);

                fgetc(arq);

                fscanf(arq, "%[^,]s", hora_duracao); // Le a duracao em forma de horas

                xi = pesquisar_id_voo(voos, de, aeroporto);
                xy = pesquisar_id_voo(voos, para, aeroporto);
                if (criaAresta(voos, xi, xy) == true)
                {

                    strcpy(dados_voo[i].de, de);
                    strcpy(dados_voo[i].para, para);
                    strcpy(dados_voo[i].identificador_voo, identificador);
                    strcpy(dados_voo[i].duracao_horario, hora_duracao);
                    dados_voo[i].duracao = duracao;
                    dados_voo[i].paradas = bb;
                    dados_voo->quantidade_voo += 1;
                    i += 1;
                    dados_voo = (Tipo_Voo *)realloc(dados_voo, (i + 1) * sizeof(Tipo_Voo));
                }
            }
            printf("\nFora main%s\n", dados_voo[0].identificador_voo);
            break;
        }
    }

    /*Fecha o arquivo*/
    fclose(arq);

    return dados_voo;
}

int retornar_posicao_voo_id_cadastro(Tipo_Voo *voo, char *de, GRAFO *grafo)
{
    int vertice = voo->quantidade_voo;
    for (int i = 0; i < vertice; i++)
    {
        if (strcmp(de, voo[i].identificador_voo) == 0){
            return i;
        }
    }
    return -1;
}

int retornar_posicao_voo_id(Tipo_Voo *voo, char *de)
{
    int vertice = voo->quantidade_voo;
    for (int i = 0; i < vertice; i++)
    {
        if (strcmp(de, voo[i].identificador_voo) == 0)
            return i;
    }
    return -1;
}

int pesquisar_id_voo(GRAFO *voos, char de[10], Aeroporto *a)
{
    int i, vertice = 0;
    vertice = voos->qnt_Vertices;
    for (i = 0; i < vertice; i++)
    {
        if (strcmp(a[i].sigla, de) == 0)
        {
            return i;
        }
    }
    return -1;
}

void possibilidade_voo(char de[10], char para[10], Tipo_Voo *voo)
{
    int duracao = voo->quantidade_voo;
    for (int i = 0; i < duracao; i++)
    {
        if (strcmp(voo[i].de, de) == 0 && strcmp(voo[i].para, para) == 0)
        {
            printf("|Voo: %s\t|De: %s\t|Para: %s\t|Duracao: %d|\tTempo: %s\t\n", voo[i].identificador_voo, voo[i].de, voo[i].para, voo[i].duracao, voo[i].duracao_horario);
        }
    }
}

int retornar_posicao_voo(Tipo_Voo *dados, Aeroporto *aeroporto, char de[10], GRAFO *voos)
{

    int i, j;
    for (i = 0; i < dados->quantidade_voo; i++)
    {
        if (strcmp(dados[i].identificador_voo, de) == 0)
        {
            for (j = 0; j < voos->qnt_Vertices; j++)
            {
                if (strcmp(dados[i].de, aeroporto[j].sigla) == 0)
                {
                    return j;
                }
            }
        }
    }
    return -1;
}

void DFS(TypeGraphMatriz *rotas, Aeroporto *aeroporto, int origem, int destino, int paradas)
{
    int *guardar_rotas = malloc(sizeof(int) * rotas->qntVertices);
    int tamanho = 0;
    for (int i = 0; i < rotas->qntVertices; i++)
        guardar_rotas[i] = -1;
    DFS_Routh(rotas, aeroporto, origem, origem, destino, paradas, tamanho, guardar_rotas);
}

void DFS_Routh(TypeGraphMatriz *rotas, Aeroporto *aeroporto, int inicial, int origem, int destino, int paradas, int tamanho, int *guardar_rotas)
{
    int vertice = rotas->qntVertices;

    for (int i = 0; i < vertice; i++)
    {
        int teste = 0;
        for (int j = 0; j < tamanho; j++)
        {
            if (i == guardar_rotas[j])
            {
                teste = 1;
            }
        }

        if (teste == 0 && i != inicial && rotas->Mat[inicial][i] == 1 && i != destino && i != origem)
        {
            guardar_rotas[tamanho] = i;
            tamanho += 1;
            DFS_Routh(rotas, aeroporto, i, origem, destino, paradas, tamanho, guardar_rotas);
        }

        else if (teste == 0 && i != inicial && rotas->Mat[inicial][i] == 1 && i == destino && tamanho >= paradas)
        {
            printf("%s -> ", aeroporto[origem].sigla);
            for (int j = 0; j < tamanho; j++)
            {
                printf("%s -> ", aeroporto[guardar_rotas[j]].sigla);
            }
            printf("%s\n\n", aeroporto[destino].sigla);
        }
    }
}

void mostrar_voo_semconaxao(TypeGraphMatriz *rotas, int id, Tipo_Voo *voo, Aeroporto *aeroporto)
{
    int vertice = rotas->qntVertices;
    for (int i = 0; i < vertice; i++)
    {
        if (rotas->Mat[id][i] == 0)
        {
            for (int j = 0; j < voo->quantidade_voo; j++)
            {
                if (strcmp(voo[j].de, aeroporto[id].sigla) == 0 && strcmp(voo[j].para, aeroporto[i].sigla) == 0)
                {
                    printf("Voo: %s|\tDe: %s|\tPara: %s|\tDuracao: %d|\tTempo: %s|\t", voo[j].identificador_voo, voo[j].de, voo[j].para, voo[j].duracao, voo[j].duracao_horario);
                    printf("\n");
                }
            }
        }
    }
}
