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
    int qntArestas;  // Variavel para armazenas a quatantidade de arestas
    int qntVertices; // Variavel para armazenas a quatantidade de vertices
    int Digrafo;     // Verifica se e digrafo
} TypeGraphMatriz;
/////////////////////////////////////////////////////////// Fim Matriz

TypeGraphMatriz *criarGrafo(int vertice);                     // Funcao responsavel por criar o grafo de matriz
int definirNumeroVertice(TypeGraphMatriz *grafo, int numero); // Funcao responsavel por armazenas a quantidade de vertices

//////////////////////////////////////////////////////////////////////
//Lista Adjacencia
typedef struct Tipo_Voo
{
    int id;                     // Guarda o id do Voo
    int duracao;                // Guarda a duracao do Voo
    char identificador_voo[10]; // Guarda a sigla do Voo exemplo ABQ-1
    int quantidade_voo;         // Guarda a quantidade de Voo para aquele aeroporto
    char duracao_horario[6];    // Armazena a Hora
    char de[4];                 // Vo de Origem
    char para[4];               // Voo de destino
    int paradas;                // Quantidade de Paradas
} Tipo_Voo;

typedef struct Aeroporto
{
    char sigla[4];      // Guarda a abreviacao do aeroporto
    char cidade[50];    // guarda a cidade
    char aeroporto[50]; // guarda o estado
    int x;              // guarda o eixo x do mapa
    int y;              // guarda o eixo y do mapa
    int id;             // guarda o id do aeroporto

} Aeroporto;
typedef struct adjacencia
{
    int id_voo;      // guarda o ID do Voo
    int predecessor; // guarda para onde o voo ira
    int distancia;   // guarda a distancia ate o local do voo
    struct adjacencia *prox;
} ADJACENCIA;

typedef struct vertice
{
    ADJACENCIA *ligar; // realiza a ligacao
} VERTICE;

typedef struct grafo
{
    int qnt_Vertices; // armazena a quantidade de vertices
    int qnt_Arestas;  // armazena a quantidade de arestas
    VERTICE *adj;
} GRAFO;

////////////////////////////////////////////////////////////////////// Fim Lista

/////////////////////////////////////////////////////////////////////////////
/// Voo

////////////////////////////////////////////////////////////////////////////// Fim Voo
int numero_deVERTICES(FILE *arq); // Funcao responsavel por buscar no arquivo a quantidade de vertices
GRAFO *criarGrafo_adj(int v);     //  Vou passar por referencia a quantidade de vertices lidas

ADJACENCIA *criaAdj(int v, int distancia, int predecessor); //Cria a lista de adjacencia

bool criaAresta(GRAFO *gr, int de, int para, int distancia, int predecessor); // Cria aresta na lista
int **gerar_matriz_minima(int vertice);
void imprime(GRAFO *gr);

#endif