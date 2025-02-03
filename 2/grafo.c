/*******************************************
 * Implementação de biblioteca para grafos.
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>

//---------------------------------------------------------
// getters:

int vertice_id(vertice v) {
  return v->id;
};
lista fronteira(vertice v) {
  return v->fronteira;
};
int aresta_id(aresta e) {
  return e->id;
};
vertice vertice_u(aresta e) {
  return e->u;
};
vertice vertice_v(aresta e) {
  return e->v;
};
lista vertices(grafo G) {
  return G->vertices;
};
lista arestas(grafo G) {
  return G->arestas;
};

//---------------------------------------------------------
// funcoes para construcao/desconstrucao do grafo:

// cria grafo vazio e o retorna
grafo cria_grafo() {
  grafo G = (grafo) malloc(sizeof(t_grafo));
  if (!G)
    exit(_ERRO_MALLOC_);
  G->vertices = cria_lista();
  G->arestas = cria_lista();

  return G;
}

void destroi_grafo(grafo G) {
   
    vertice v;
    no n, proximo_no;

    n = primeiro_no(vertices(G));
    while (n != NULL) {
        proximo_no = proximo(n);  // armazena o próximo nó antes de remover o vértice
        v = conteudo(n);
        remove_vertice(vertice_id(v), G);
        n = proximo_no;  // avança para o próximo nó
    }

    // libera listas de vértices e arestas
    free(vertices(G));
    free(arestas(G));

    free(G);
    G = NULL;
}

// cria novo vertice com id <id> e adiciona ao grafo G
void adiciona_vertice(int id, grafo G) {
  
  vertice v = (vertice) malloc(sizeof(t_vertice));

  if (!v)
    exit(_ERRO_MALLOC_);

  v->id = id;
  v->fronteira = cria_lista();

  empilha(v,vertices(G));
}

// remove vertice com id <id> do grafo G e o destroi
// [deve remover e destruir tambem as arestas incidentes]
void remove_vertice(int id, grafo G) {

    vertice v = busca_chave(id, vertices(G), (int_f_obj) vertice_id);
    if (v == NULL) {
        printf("Vertice %d não encontrado.\n", id);
        return;
    }

     while (!vazio(fronteira(v))) {
        remove_aresta(aresta_id(desempilha(fronteira(v))), G);
      }
      free(fronteira(v));
  
    // remove o vértice da lista de vértices
    remove_chave(id, vertices(G), (int_f_obj) vertice_id);
         
    free(v); // libera a memória do vértice
    v = NULL;
}


// cria aresta com id <id> incidente a vertices com
// ids <u_id> e <v_id> e adiciona ao grafo G
void adiciona_aresta(int id, int u_id, int v_id, grafo G) {

  vertice u,v;

  aresta a = (aresta) malloc(sizeof(t_aresta));

  if(!a)
    exit(_ERRO_MALLOC_);

  u = busca_chave(u_id,vertices(G),(int_f_obj) vertice_id);
  v = busca_chave(v_id,vertices(G),(int_f_obj) vertice_id);

  if(u == NULL || v == NULL) {
    printf("Um ou ambos os vertices nao existem.\n");
    free(a);
    return;
  }

  a->id = id;
  a->u = u;
  a->v = v;
  
  empilha(a,fronteira(u));
  empilha(a,fronteira(v));
  empilha(a,arestas(G));
}

// remove aresta com id <id> do grafo G e a destroi
void remove_aresta(int id, grafo G) {
  
  // primeiro, tenta encontrar a aresta
  aresta a = busca_chave(id, arestas(G), (int_f_obj) aresta_id);
  
  // verifica se a aresta foi encontrada antes de tentar acessá-la
  if (a != NULL) {
    // remove a aresta das fronteiras de 'v' e 'u'
    remove_chave(id, fronteira(vertice_v(a)), (int_f_obj) aresta_id);
    remove_chave(id, fronteira(vertice_u(a)), (int_f_obj) aresta_id);
    remove_chave(id, arestas(G), (int_f_obj) aresta_id);
    
    // libera a memória da aresta
    free(a);
    a = NULL;
  } else {
    // a aresta com o 'id' fornecido não foi encontrada
    printf("Aresta com id %d não encontrada\n", id);
  }
}

//---------------------------------------------------------
// funcoes para operacoes com o grafo pronto:

// calcula e devolve o grau do vertice v
int grau(vertice v) {
  int d_v = 0;
  for (no n = primeiro_no(fronteira(v)); n; n = proximo(n))
    ++d_v;
  return d_v;
}

// imprime o grafo G
void imprime_grafo(grafo G) {
  printf("\nVertices: <id> - [grau]( <fronteira> )");
  printf("\nVertices: ");
  imprime_lista(vertices(G), (void_f_obj) imprime_vertice);
  printf("\nArestas: <id>:{u,v}");
  printf("\nArestas: ");
  imprime_lista(arestas(G), (void_f_obj) imprime_aresta);
  printf("\n");
}

// imprime o vertice v
void imprime_vertice(vertice v) {
  printf("%d - [%d]( ", vertice_id(v), grau(v));
  imprime_lista(fronteira(v), (void_f_obj) imprime_aresta);
  printf(")");
}

// imprime a aresta e
void imprime_aresta(aresta e) {
  int u_id = vertice_id(vertice_u(e));
  int v_id = vertice_id(vertice_v(e));
  printf("%d:{%d,%d}", aresta_id(e), u_id, v_id);
}

