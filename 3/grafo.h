/*******************************************
 * Implementação de biblioteca para grafos.
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#ifndef _GRAFO_
#define _GRAFO_

#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct t_vertice *vertice;
typedef struct t_aresta *aresta;
typedef struct t_grafo *grafo;

typedef struct t_vertice {
	int id;
	lista fronteira;
} t_vertice;

typedef struct t_aresta {
	int id;
	vertice u, v;
} t_aresta;

typedef struct t_grafo {
  lista vertices;
  lista arestas;
} t_grafo ;

//---------------------------------------------------------
// getters:

int vertice_id(vertice v);
lista fronteira(vertice v);
int aresta_id(aresta e);
vertice vertice_u(aresta e);
vertice vertice_v(aresta e);
lista vertices(grafo G);
lista arestas(grafo G);

//---------------------------------------------------------
// funcoes para construcao/desconstrucao do grafo:

// cria grafo vazio e o retorna
grafo cria_grafo();

// destroi grafo G (desaloca toda a memoria)
void destroi_grafo(grafo G);

// cria novo vertice com id <id> e adiciona ao grafo G
void adiciona_vertice(int id, grafo G);

// remove vertice com id <id> do grafo G e o destroi
// [deve remover e destruir tambem as arestas incidentes]
void remove_vertice(int id, grafo G);

// cria aresta com id <id> incidente a vertices com
// ids <u_id> e <v_id> e adiciona ao grafo G
void adiciona_aresta(int id, int u_id, int v_id, grafo G);

// remove aresta com id <id> do grafo G e a destroi
void remove_aresta(int id, grafo G);

//---------------------------------------------------------
// funcoes para operacoes com o grafo pronto:

// calcula e devolve o grau do vertice v
int grau(vertice v);

// imprime o grafo G
void imprime_grafo(grafo G);

// imprime o vertice v
void imprime_vertice(vertice v);

// imprime a aresta e
void imprime_aresta(aresta e);

//---------------------------------------------------------
// funcoes adicionadas no exercicio 3:

// cria uma lista com os ids fornecidos pelo usuario
lista le_ids_vertices_X();

// cria o subconjunto de vertices X validado
lista cria_subconjunto(grafo G, lista ids_X);

// cria um subgrafo induzido a partir do subconjunto X
grafo grafo_induzido(grafo G, lista X);

// Funções auxiliares para destruir objetos específicos (vértices, arestas e inteiros).
// Estas funções devem ser utilizadas dentro da 'destroi_grafo(G)' para garantir que 
// todos os objetos alocados dentro do grafo sejam corretamente liberados. 
// Elas são passadas como parâmetro para 'destroi_lista', dependendo dos tipos 
// de dados presentes na lista que está sendo liberada.

void destroi_vertice(obj v);  
void destroi_aresta(obj e);   
void destroi_int(obj o);    // Função que destrói inteiros da lista de IDs.


#endif
