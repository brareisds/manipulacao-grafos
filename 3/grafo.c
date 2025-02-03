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
}
lista fronteira(vertice v) {
  return v->fronteira;
}
int aresta_id(aresta e) {
  return e->id;
}
vertice vertice_u(aresta e) {
  return e->u;
}
vertice vertice_v(aresta e) {
  return e->v;
}
lista vertices(grafo G) {
  return G->vertices;
}
lista arestas(grafo G) {
  return G->arestas;
}

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
    if (G == NULL) return;

    // primeiro, todas as arestas sao destruidas
    destroi_lista(arestas(G), destroi_aresta, (int_f_obj) aresta_id);

    // em seguida, todas os vertices sao destruidos
    destroi_lista(vertices(G), destroi_vertice, (int_f_obj) vertice_id);

    // destroi o grafo
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

  a->id = id;

  u = busca_chave(u_id,vertices(G),(int_f_obj) vertice_id);
  v = busca_chave(v_id,vertices(G),(int_f_obj) vertice_id);

  if(u == NULL || v == NULL) {
    printf("Um ou ambos os vertices nao existem.\n");
    free(a);
    return;
  }

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

    vertice u = vertice_u(a);
    vertice v = vertice_v(a);

    // remove a aresta das fronteiras de 'u' e 'v'
    remove_chave(id, fronteira(v), (int_f_obj) aresta_id);
    remove_chave(id, fronteira(u), (int_f_obj) aresta_id);
    remove_chave(id, arestas(G), (int_f_obj) aresta_id);
    
    // libera a memória da aresta
    free(a);
    a = NULL;

  } else {
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

//---------------------------------------------------------
// funcoes adicionadas como parte da solucao para o exercicio 3:

lista le_ids_vertices_X() {

    int id_X, *novo_id;

    lista ids_X = cria_lista();
    
    printf("\nDigite o id dos vertices de G que deseja adicionar no conjunto X ou digite 0 para terminar: \n");
    scanf("%d", &id_X);

    while (id_X) {
        // aloca memória para armazenar o valor de id_X
        novo_id = (int *)malloc(sizeof(int));
        if (!novo_id) {
            perror("Erro de alocação de memória");
            exit(1);
        }
        
        *novo_id = id_X;  
        
        empilha((void*)novo_id, ids_X);
        scanf("%d", &id_X);
    }

    return ids_X;
}

lista cria_subconjunto(grafo G, lista ids_X) {

    int id;
    lista X = cria_lista(); // cria uma nova lista para armazenar os vértices validos

    for (no n = primeiro_no(ids_X); n != NULL; n = proximo(n)) {
        id = *(int *) conteudo(n); 

        // busca o vértice com o id correspondente no grafo G
        vertice v = busca_chave(id, vertices(G), (int_f_obj) vertice_id);
        
        if (v != NULL) {
            // se o vértice foi encontrado, adiciona ao subconjunto X
            empilha(v, X);
        } else {
            // se o vértice não existe, emite um aviso
            printf("Vértice %d não encontrado no grafo original.\n", id);
        }
    }

    return X; // retorna o subconjunto de vértices válidos
}

// função para criar o subgrafo induzido G[X]
grafo grafo_induzido(grafo G, lista X) {

    // cria o novo grafo
    grafo GX = cria_grafo();

    // adiciona os vértices de X ao novo grafo GX
    for (no n = primeiro_no(X); n != NULL; n = proximo(n)) {
        vertice v = conteudo(n);
        adiciona_vertice(vertice_id(v), GX);
    }

    // adiciona as arestas entre os vértices de X
    for (no n = primeiro_no(arestas(G)); n != NULL; n = proximo(n)) {
        aresta e = conteudo(n);
        vertice u = vertice_u(e);
        vertice v = vertice_v(e);

        // verifica se ambos os vértices u e v estão em X
        if (busca_chave(vertice_id(u), X, (int_f_obj) vertice_id) != NULL &&
            busca_chave(vertice_id(v), X, (int_f_obj) vertice_id) != NULL) {

            // adiciona a aresta no novo grafo GX
            adiciona_aresta(aresta_id(e), vertice_id(u), vertice_id(v), GX);
        }
    }

    return GX;
}

void destroi_vertice(obj v) {
    vertice vert = (vertice)v; 
    if (vert == NULL) return;  // verifica se o vértice já foi destruído.

    // libera a memoria da lista de fronteira que ja esta vazia, visto que, as arestas foram destruidas primeiro
    free(fronteira(vert));
    free(vert);

    vert = NULL;
}

void destroi_aresta(obj e) {
    aresta a = (aresta)e; 
    if (a == NULL) return;  // verifica se a aresta já foi destruída.

    // remove a aresta das fronteiras dos vértices u e v
    remove_chave(aresta_id(a), fronteira(vertice_u(a)), (int_f_obj) aresta_id);
    remove_chave(aresta_id(a), fronteira(vertice_v(a)), (int_f_obj) aresta_id);
    
    // libera a memória da aresta
    free(a);
    a = NULL;
}


// destroi a lista de IDs
void destroi_int(obj o) {
    int *i = (int *)o;
    free(i);
}