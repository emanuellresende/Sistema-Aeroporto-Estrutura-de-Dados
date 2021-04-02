#ifndef _GRAFO_
#define _GRAFO_
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
///////////////////////////////////////////////////////////
////// Matriz
typedef struct TypeGraphMatriz
{
    int **Mat;
    int qntArestas;  // Liga X e Y
    int qntVertices; // Marcador
    int Digrafo;
} TypeGraphMatriz;
/////////////////////////////////////////////////////////// Fim Matriz

TypeGraphMatriz *criarGrafo(int vertice);
int definirNumeroVertice(TypeGraphMatriz *grafo, int numero);

//////////////////////////////////////////////////////////////////////
//Lista Adjacencia
typedef struct Tipo_Voo
{
    int id;
    /* variavel para armazenar a duracao de um determinado voo. */
    int duracao;
    /* variavel para armazenar o identificador de um determinado voo. */
    char identificador_voo[10];
    int quantidade_voo;
    /* variavel para armazenar a duracao em um formato diferente. */
    char duracao_horario[6];
    char de[4];
    char para[4];
    int paradas;
} Tipo_Voo;

typedef struct Aeroporto
{
    char sigla[4];
    char cidade[50];
    char aeroporto[50];
    int id;

} Aeroporto;
typedef struct adjacencia
{
    int id_voo;
 
    struct adjacencia *prox;
} ADJACENCIA;

typedef struct vertice
{
    ADJACENCIA *ligar;
} VERTICE;

typedef struct grafo
{
    int qnt_Vertices;
    int qnt_Arestas;
    VERTICE *adj;
} GRAFO;

////////////////////////////////////////////////////////////////////// Fim Lista

/////////////////////////////////////////////////////////////////////////////
/// Voo

////////////////////////////////////////////////////////////////////////////// Fim Voo
int numero_deVERTICES(FILE *arq);
GRAFO *criarGrafo_adj(int v); //  Vou passar por referencia a quantidade de vertices lidas

void criaAdj_aux(GRAFO *grafo, int i, ADJACENCIA *aux); // vf e variavel
ADJACENCIA *criaAdj(int v);                             // Passar por referencia

bool criaAresta(GRAFO *gr, int de, int para);

void imprime(GRAFO *gr);

#endif