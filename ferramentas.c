
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "ferramentas.h"
#include "Grafo.h"
#include <limits.h>
#include <math.h>
Tipo_Voo *ler(GRAFO *voos, TypeGraphMatriz *rotas, FILE *arq, int vertices, Aeroporto *aeroporto, GRAFO *voo_rotas)
{
    rewind(arq);               // VOlta o arquivo pro inicio
    char lixo[500];            // Variavel utilizada para remover quando for comentario
    char de[10];               // Variavel para armazenar a origem do voo
    char para[10];             // variavel para armazenas o destino do voo
    char identificador[10];    // armazena o voo Exemplo ABQ-1
    int duracao;               // armazena duracao do voo
    char horario[10];          // armazena o horario do voo em char
    char abreviacao_cidade[4]; // armazena a abreviacao da cidade exemplo ABQ
    char nome_cidade[30];      // armazena o nome da cidade
    char nome_aeroporto[30];   // armazena o nome do aeroporto
    char hora_duracao[10];     // Armazena a duracao do voo

    int i = 0;       // variavel contadora
    int paradas = 0; // armazena a quantidade de paradas

    int xi = 0, xy = 0; // Variaveis para controlar no xi a origem e no xy o destino
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

                fscanf(arq, "%d", &aeroporto[i].x); // Pega o nome da abreviacao

                fgetc(arq); // Pega o espaco

                fscanf(arq, "%d", &aeroporto[i].y); // Pega o nome da abreviacao

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
                int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
                int soma = 0;
                int aux_conexao1 = 0, aux_conexao2 = 0; // Variaveis para auxiliar para setar as conexoes
                fgetc(arq);                             // Le o \n depois do !

                fscanf(arq, "%s", de); // Pega a conexao

                if (strcmp(de, "!") == 0) // Caso a conexao seauxa o caracter de pause
                    break;

                fgetc(arq); // Pega o espaco

                fscanf(arq, "%s", para); // Le o para

                fgetc(arq); // Le o \n

                /*Procurando a conexao DE*/

                ///
                xi = pesquisar_id_voo(voos, de, aeroporto); // Retorna o ID do Aeroporto
                xy = pesquisar_id_voo(voos, para, aeroporto);

                rotas->Mat[xi][xy] = 1;
                rotas->Mat[xy][xi] = 1;
                rotas->qntArestas += 1;

                int distancia = calcula_distancia(aeroporto[xi].x, aeroporto[xy].x, aeroporto[xi].y, aeroporto[xi].y);
                if (criaAresta(voo_rotas, xi, xy, distancia, xy) == true)
                {
                }
                if (criaAresta(voo_rotas, xy, xi, distancia, xi) == true)
                {
                }
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

                fscanf(arq, "%d", &paradas);

                fgetc(arq);

                fscanf(arq, "%[^,]s", hora_duracao); // Le a duracao em forma de horas

                xi = pesquisar_id_voo(voos, de, aeroporto);
                xy = pesquisar_id_voo(voos, para, aeroporto);
                int distancia = calcula_distancia(aeroporto[xi].x, aeroporto[xy].x, aeroporto[xi].y, aeroporto[xi].y);

                if (criaAresta(voos, xi, i, distancia, xy) == true)
                {

                    strcpy(dados_voo[i].de, de);
                    strcpy(dados_voo[i].para, para);
                    strcpy(dados_voo[i].identificador_voo, identificador);
                    strcpy(dados_voo[i].duracao_horario, hora_duracao);
                    dados_voo[i].duracao = duracao;
                    dados_voo[i].paradas = paradas;
                    dados_voo[i].id = i;
                    dados_voo->quantidade_voo += 1;
                    i += 1;
                    dados_voo = (Tipo_Voo *)realloc(dados_voo, (i + 1) * sizeof(Tipo_Voo));
                }
                else
                    printf("ELS");
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
        if (strcmp(de, voo[i].identificador_voo) == 0)
        {
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

    int i, aux;
    for (i = 0; i < dados->quantidade_voo; i++)
    {
        if (strcmp(dados[i].identificador_voo, de) == 0)
        {
            for (aux = 0; aux < voos->qnt_Vertices; aux++)
            {
                if (strcmp(dados[i].de, aeroporto[aux].sigla) == 0)
                {
                    return aux;
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
    {
        guardar_rotas[i] = -1;
    }
    DFS_Routh(rotas, aeroporto, origem, origem, destino, paradas, tamanho, guardar_rotas);
}

void DFS_Routh(TypeGraphMatriz *rotas, Aeroporto *aeroporto, int inicial, int origem, int destino, int paradas, int tamanho, int *guardar_rotas)
{
    int vertice = rotas->qntVertices;
    int teste = 0;
    for (int i = 0; i < vertice; i++)
    {
        teste = 0;
        for (int aux = 0; aux < tamanho; aux++)
        {
            if (i == guardar_rotas[aux])
            {
                teste = 1;
                break;
            }
        }

        if (teste == 0 && i != inicial && rotas->Mat[inicial][i] > 0 && i != destino && i != origem)
        {

            guardar_rotas[tamanho] = i;
            DFS_Routh(rotas, aeroporto, i, origem, destino, paradas, tamanho + 1, guardar_rotas);
        }

        else if (teste == 0 && i != inicial && rotas->Mat[inicial][i] > 0 && i == destino && tamanho >= paradas)
        {
            printf("%s -> ", aeroporto[origem].sigla);
            for (int aux = 0; aux < tamanho; aux++)
            {
                printf("%s -> ", aeroporto[guardar_rotas[aux]].sigla);
            }
            printf("%s\n\n", aeroporto[destino].sigla);
        }
    }
}

void mostrar_voo_semconaxao(int id, Tipo_Voo *voo, GRAFO *gr)
{

    ADJACENCIA *ad = gr->adj[id].ligar;
    while (ad)
    {
        if (voo[ad->id_voo].paradas == 0)
        {
            int j = ad->id_voo;
            printf("Voo: %s|\tDe: %s|\tPara: %s|\tDuracao: %d|\tTempo: %s|\t", voo[j].identificador_voo, voo[j].de, voo[j].para, voo[j].duracao, voo[j].duracao_horario);
            printf("\n");
        }
        ad = ad->prox;
    }
    printf("\n");
}

//int **GeraMatrizMinima(TypeGraphMatriz *rotas, GRAFO *gr, Tipo_Voo *voo)
//{

//}

/*void FloydWarshall(TypeGraphMatriz *rotas, int **MatrizMinima)
{ //Função que procura o caminho mínimo entre todos os vértices que possuem conexão
    int numAero = rotas->qntVertices;
    for (int x = 0; x < numAero; x++)
    {
        for (int y = 0; y < numAero; y++)
        {
            for (int z = 0; z < numAero; z++)
            {
                if (MatrizMinima[y][z] > (MatrizMinima[y][x] + MatrizMinima[x][z]))
                {
                    MatrizMinima[y][z] = MatrizMinima[y][x] + MatrizMinima[x][z];
                }
            }
        }
    }
}
*/

void inicializaD(GRAFO *gr, int *d, int *p, int s)
{
    for (int i = 0; i < gr->qnt_Vertices; i++)
    {
        d[i] = INT_MAX / 2;
        p[i] = -1;
    }
    d[s] = 0;
}

void relaxa(GRAFO *g, int *d, int *p, int u, int v)
{
    ADJACENCIA *ad = g->adj[u].ligar;
    while (ad && ad->predecessor != v)
        ad = ad->prox;
    if (ad)
    {
        if (d[v] > (d[u] + ad->distancia))
        {
            d[v] = d[u] + ad->distancia;
            p[v] = u;
        }
    }
}

void *dijskra(GRAFO *g, int s, int destino, Aeroporto *aeroporto)
{
    int *d = (int *)malloc(g->qnt_Vertices * sizeof(int));
    int destino_2;
    int soma = 0;
    int p[g->qnt_Vertices];
    bool aberto[g->qnt_Vertices];
    inicializaD(g, d, p, s);

    int i;
    for (i = 0; i < g->qnt_Vertices; i++)
        aberto[i] = true;

    while (existeAberto(g, aberto))
    {
        int u = menorDist(g, aberto, d);
        aberto[u] = false;

        ADJACENCIA *ad = g->adj[u].ligar;
        while (ad)
        {
            relaxa(g, d, p, u, ad->predecessor);
            ad = ad->prox;
        }
    }

    for (i = 0; i < g->qnt_Vertices; i++)
    {
        if (p[i] == destino)
        {
            destino_2 = i;
        }
    }

    for (i = 0; i <= destino_2; i++)
    {
        printf("%s ->", aeroporto[p[i]].sigla);
        soma = soma + d[i];
    }
    printf("\nDistancia Total %d", soma);
}

bool existeAberto(GRAFO *g, bool *aberto)
{
    int i;
    for (i = 0; i < g->qnt_Vertices; i++)
    {
        if (aberto[i])
        {
            return true;
        }
    }
    return false;
}

int menorDist(GRAFO *g, bool *aberto, int *d)
{
    int i;
    for (i = 0; i < g->qnt_Vertices; i++)
    {
        if (aberto[i])
        {
            break;
        }
    }
    if (i == g->qnt_Vertices)
        return (-1);

    int menor = i;
    for (i = menor + 1; i < g->qnt_Vertices; i++)
    {
        if (aberto[i] && (d[menor] > d[i]))
        {
            menor = i;
        }
    }
    return menor;
}

int retornar_voo_viaDEPARA(Tipo_Voo *voo, char de[10], char para[10])
{
    for (int i = 0; i < voo->quantidade_voo; i++)
    {

        if (strcmp(voo[i].de, de) == 0 && strcmp(voo[i].para, para) == 0)
        {
            return i;
        }
    }
}

int calcula_distancia(int x1, int x2, int y1, int y2)
{
    int soma;
    int soma_x = x2 - x1;
    soma_x = pow(soma_x, 2);

    int soma_y = y2 - y1;
    soma_y = pow(soma_y, 2);

    soma = sqrt((soma_x + soma_y));
    return soma;
}