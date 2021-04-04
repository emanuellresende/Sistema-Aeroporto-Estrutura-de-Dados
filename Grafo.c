#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Grafo.h"
#include <unistd.h>
///////////////////////////////////////////////////////////
////// Matriz

////////////////////////////////////////////////////////////////////////////// Fim Voo

GRAFO *criarGrafo_adj(int v) //  Vou passar por referencia a quantidade de vertices lidas
{
    int i;

    GRAFO *g = (GRAFO *)malloc(sizeof(GRAFO));
    g->qnt_Vertices = v;
    g->qnt_Arestas = 0;
    g->adj = (VERTICE *)malloc(v * sizeof(VERTICE));
    for (i = 0; i < v; i++)
    {
        g->adj[i].ligar = NULL; //coloco NULL em todas qnt_Arestas
    }
    return (g);
}

ADJACENCIA *criaAdj(int v, int distancia, int predecessor) // vf e variavel
{
    ADJACENCIA *temp = (ADJACENCIA *)malloc(sizeof(ADJACENCIA));
    temp->id_voo = v;
    temp->distancia = distancia;
    temp->predecessor = predecessor;
    temp->prox = NULL;
    return (temp);
}

bool criaAresta(GRAFO *gr, int de, int para, int distancia, int predecessor)
{ //vai de de a para

    ADJACENCIA *novo = criaAdj(para, distancia, predecessor);

    novo->prox = gr->adj[de].ligar;
    gr->adj[de].ligar = novo;
    gr->qnt_Arestas++;
    return (true);
}

void imprime(GRAFO *gr)
{

    printf("qnt_Vertices: %d. qnt_Arestas: %d. \n", gr->qnt_Vertices, gr->qnt_Arestas); //imprime numero de vértice e qnt_Arestas
    int i;

    for (i = 0; i < gr->qnt_Vertices; i++)
    {
        printf("Aresta: %d: ", i);
        ADJACENCIA *ad = gr->adj[i].ligar;
        while (ad)
        {
            printf(" %d(%d) - ", ad->predecessor, ad->distancia);
            ad = ad->prox;
        }
        printf("\n");
    }
}

////////////////////////////////////////////////////////////////////////
int definirNumeroVertice(TypeGraphMatriz *grafo, int numero)
{
    grafo->qntVertices = numero;
    return true;
}
TypeGraphMatriz *criarGrafo(int vertice)
{
    TypeGraphMatriz *grafo = (TypeGraphMatriz *)malloc(sizeof(TypeGraphMatriz));
    grafo->Mat = (int **)malloc(vertice * sizeof(int *));
    for (int i = 0; i < vertice; i++)
    {
        grafo->Mat[i] = (int *)malloc(vertice * sizeof(int));
        for (int j = 0; j < vertice; j++)
        {
            grafo->Mat[i][j] = 0;
        }
    }
    grafo->qntVertices = vertice;
    grafo->qntArestas = 0;
    return grafo;
}
int numero_deVERTICES(FILE *arq)
{

    char lixo[500], abreviacao[4], aeroporto[100], cidade[100];
    int vertices = 0;
    while (!feof(arq))
    {

        switch (fgetc(arq))
        {

        case '#':
            fscanf(arq, "%[^\n]s", lixo);
            fgetc(arq);

            break;

        case '$':
            while (1)
            {

                fgetc(arq);

                fscanf(arq, "%s", abreviacao);

                fgetc(arq);

                if (strcmp(abreviacao, "$") == 0)

                    break;

                fscanf(arq, "%[^(]s", cidade);

                fgetc(arq);

                fscanf(arq, "%[^)]s", aeroporto);

                vertices += 1;
            }

            return vertices;

            break;
        }
    }
}

int **gerar_matriz_minima(int vertice)
{
    int **Mat = (int **)malloc(vertice * sizeof(int *));
    for (int i = 0; i < vertice; i++)
    {
        Mat[i] = (int *)malloc(vertice * sizeof(int));
        for (int j = 0; j < vertice; j++)
        {
            Mat[i][j] = 0;
        }
    }
    return Mat;
}
