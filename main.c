#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "leitura.h"
#include "Grafo.h"

int main()
{
    char de[10], para[10];
    int menu = 0, opcao = 0, xi = 0, xy = 0;
    FILE *arq = fopen("voo.txt", "r");
    if (arq == NULL)
    {
        printf("ERRO NO ARQUIVO");
        exit(1);
    }

    int vertice = numero_deVERTICES(arq);
    ///////////////////////////////////////////////////////
    TypeGraphMatriz *rotas = criarGrafo(vertice);
    GRAFO *voo = criarGrafo_adj(vertice);
    Aeroporto aeroporto[vertice];
    Tipo_Voo *dados_voo = (ler(voo, rotas, arq, vertice, aeroporto));
    ////////////////////////////////////////////////////
    rotas->qntVertices = voo->qnt_Vertices;
    int visited[rotas->qntVertices];
    ///////////////////////////////////////////////////
    printf("\n\t\t\t\t SISTEMA DE VOOS \t\t\t\t \n");
    while (menu != 7)
    {
        printf("\n\t [1] - Mostrar a possibilidade de voos dados dois aeroportos\n");
        printf("\n\t [2] - Dado um voo e mostrar a rota possível para o mesmo\n");
        printf("\n\t [3] - Mostrar, a partir de um aeroporto definido, quais os voos direto\n");
        printf("\n\t [4] - Dados uma origem e um destino, determinar a viagem com menor custo\n");
        printf("\n\t [5] - A partir de um aeroporto qualquer atingir qualquer outro\n");
        printf("\n\t [6] - Partindo de um aeroporto selecionado definir uma rota que consiga passar por todos os aeroportos com um tempo de voo mínimo.\n");
        printf("\n\t [7]-Sair \n");
        printf("\n\t Opcao: ");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            system("clear");
            printf("Digite o aeroporto de Origem: ");
            scanf("%s", de);
            xi = pesquisar_id_voo(voo, de, aeroporto);
            if (xi == -1)
            {
                printf("\n\t\t\tAeroporto nao encontrado\t\t\t\n");
                break;
            }
            printf("\n");
            printf("Digite o aeroporto de destino: ");
            scanf("%s", para);
            xy = pesquisar_id_voo(voo, para, aeroporto);
            printf("\n");
            if (xy == -1)
            {
                printf("\n\t\t\tAeroporto nao encontrado\t\t\t\n");
                break;
            }
            if (xi == xy)
            {
                printf("\n\t\t\tNao e possivel ir pra onde ja esta\t\t\t\n");
                break;
            }

            possibilidade_voo(de, para, dados_voo);
            break;

        case 2:
            system("clear");
            printf("Digite o voo para descobrir a rota\n");
            printf("Voo:");
            scanf("%s", de);
            printf("\n");
            xi = retornar_posicao_voo(dados_voo, aeroporto, de, voo);
            int paradas = 0;
            if (xi == -1)
            {
                printf("\n\t\t\t - Nao achou - \t\t\t\n");
                break;
            }
            strcpy(de, dados_voo[xi].de);
            strcpy(para, dados_voo[xi].para);
            xi = pesquisar_id_voo(voo, de, aeroporto);
            xy = pesquisar_id_voo(voo, para, aeroporto);
            for (int i = 0; i < rotas->qntVertices; i++)
            {
                if (rotas->Mat[xi][i] > 0)
                    paradas += 1;
            }
            DFS(rotas, aeroporto, xi, xy, paradas);
            ///DFS(xi, rotas, aeroporto, visited);
            break; // fecha o case 2

        default:
            printf("\n\t [WARNING] - Opcao Invalida \t\n");
            break;
        case 3:
            system("clear");
            printf("Digite o Aeroporto para ver a rota sem conexao:\n");
            printf("Voo: ");
            scanf("%s", de);
            printf("\n");
            xi = pesquisar_id_voo(voo, de, aeroporto);
            mostrar_voo_semconaxao(rotas, xi, dados_voo, aeroporto);

            break; // fecha o case 3

        case 4:
            system("clear");
            printf("Digite o aeroporto de Origem: ");
            scanf("%s", de);
            xi = pesquisar_id_voo(voo, de, aeroporto);
            if (xi == -1)
            {
                printf("\n\t\t\tAeroporto nao encontrado\t\t\t\n");
                break;
            }
            printf("\n");
            printf("Digite o aeroporto de destino: ");
            scanf("%s", para);
            xy = pesquisar_id_voo(voo, para, aeroporto);
            printf("\n");
            if (xy == -1)
            {
                printf("\n\t\t\tAeroporto nao encontrado\t\t\t\n");
                break;
            }
            if (xi == xy)
            {
                printf("\n\t\t\tNao e possivel ir pra onde ja esta\t\t\t\n");
                break;
            }

            break; // fecha o case 4
        case 7:
            system("clear");
            printf("Encerrando .....\n");
            sleep(2);
            menu = 7;
            break; // Fecha o break do case 7
        }
    }
}