/*******************************************
 * Leitura e impressao de grafos.
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  
  // cria grafo vazio
  grafo G = cria_grafo();
  
  // le n e adiciona vertices 1..n
  int n;
  scanf("%d", &n); // qtd vertices
  
  for (int i = 1; i <= n; ++i)
    adiciona_vertice(i, G);
  
  // le pares u v e adiciona arestas {u,v}
  // termina quando digitar 0 0
  int id = 1;
  int u, v;
  scanf("%d %d", &u, &v);
  while (u && v) {
    adiciona_aresta(id, u, v, G);
    ++id;
    scanf("%d %d", &u, &v);
  }
  
  // imprime informacoes do grafo 
  printf("\nGrafo G: ");
  imprime_grafo(G);

//--------------------------------------------------------------------------------------
// codigo adicionado como parte da solucao para o exercicio 3:

  // lista que armazena os ids fornecidos pelo usuário
  lista ids_X = le_ids_vertices_X();
  // Cria o subconjunto de vértices validos
  lista X = cria_subconjunto(G, ids_X);
  // Cria um subgrafo induzido com a lista X de vértices
  grafo GX = grafo_induzido(G, X);

  printf("\n");
  printf("Grafo GX: ");
  imprime_grafo(GX);
  printf("\n");

  // Libera a lista de IDs
  destroi_lista(ids_X, destroi_int, NULL);
  // Libera a lista de vértices no subconjunto X
  destroi_lista(X, NULL, NULL);
  // Destroi os grafos
  destroi_grafo(G);
  destroi_grafo(GX);
  
  return 0;
}
