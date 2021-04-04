#ifndef _LEITURA
#define _LEITURA_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Grafo.h"
#include <math.h>
Tipo_Voo *ler(GRAFO *voos, TypeGraphMatriz *rotas, FILE *arq, int vertices, Aeroporto *aeroporto, GRAFO *voo_rotas);                              // Le o arquivo e armazena na estrutura
int pesquisar_id_voo(GRAFO *voos, char de[10], Aeroporto *a);                                                                                     // retorna o id do voo procurado pela Sigla dele
void possibilidade_voo(char de[10], char para[10], Tipo_Voo *voo);                                                                                // printa as possibilidades de voo
int retornar_posicao_voo(Tipo_Voo *dados, Aeroporto *aeroporto, char de[10], GRAFO *voos);                                                        // retorna a posicao do voo
void DFS(TypeGraphMatriz *rotas, Aeroporto *aeroporto, int origem, int destino, int paradas);                                                     // Realiza a busca DFS
void DFS_Routh(TypeGraphMatriz *rotas, Aeroporto *aeroporto, int inicial, int origem, int destino, int paradas, int tamanho, int *guardar_rotas); // Realiza a rotas do dfs
void mostrar_voo_semconaxao(int id, Tipo_Voo *voo, GRAFO *gr);                                                                                    // mostra todos os voos sem conexoes
int retornar_posicao_voo_id(Tipo_Voo *voo, char *de);                                                                                             // Passa por parametro a origem ele te retorna todos os voos com aquela origem
int retornar_voo_viaDEPARA(Tipo_Voo *voo, char de[10], char para[10]);                                                                            // busca qual voo tem a origem e destino passados pelo usuario
bool existeAberto(GRAFO *g, bool *aberto);                                                                                                        // funcao auxiliar da dijskra que pesquisa se ainda existe variavel auxiliar aberta
void *dijskra(GRAFO *g, int s, int destino,Aeroporto*aeroporto);                                                                                                      // funcao dijkra utilizada na letra D, para calcular o menor caminho
void relaxa(GRAFO *g, int *d, int *p, int u, int v);                                                                                              // funcao auxiliar da dijskra usada para o menor caminho
int menorDist(GRAFO *g, bool *aberto, int *d);                                                                                                    // funcao auxiliar da dijkra para devolver a vertice de menor distancia
void inicializaD(GRAFO *gr, int *d, int *p, int s);                                                                                               // funcao auxiliar da dijkra para iniciar os vetores
int calcula_distancia(int x1, int x2, int y1, int y2);                                                                                            // funcao utilizada para calcular a distancia atraves do eixo X e Y
//int **GeraMatrizMinima(TypeGraphMatriz *rotas, GRAFO *gr, Tipo_Voo *voo);
//void FloydWarshall(TypeGraphMatriz *rotas, int **MatrizMinima);
#endif