#ifndef _LEITURA
#define _LEITURA_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Grafo.h"
Tipo_Voo *ler(GRAFO *voos, TypeGraphMatriz *rotas, FILE *arq, int vertices, Aeroporto *aeroporto);
int pesquisar_id_voo(GRAFO *voos, char de[10], Aeroporto *a);
void possibilidade_voo(char de[10], char para[10], Tipo_Voo *voo);
int retornar_posicao_voo(Tipo_Voo *dados, Aeroporto *aeroporto, char de[10], GRAFO *voos);
void DFS(TypeGraphMatriz *rotas, Aeroporto *aeroporto, int origem, int destino, int paradas);
void DFS_Routh(TypeGraphMatriz *rotas, Aeroporto *aeroporto, int inicial, int origem, int destino, int paradas, int tamanho, int *guardar_rotas);
void mostrar_voo_semconaxao(TypeGraphMatriz *rotas, int id, Tipo_Voo *voo, Aeroporto *aeroporto);

int retornar_posicao_voo_id(Tipo_Voo *voo, char *de);
#endif