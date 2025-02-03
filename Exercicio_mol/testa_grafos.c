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

#include <string.h>

// Função para ignorar o cabeçalho
void pula_linhas(FILE *file, int lines) {
    char buffer[256];
    for (int i = 0; i < lines; i++) {
        fgets(buffer, sizeof(buffer), file);
    }
}

// Função para ler o número de átomos e ligações
int contagem_atomos_ligacoes(FILE *file, int *n, int *m) {
    if (fscanf(file, "%d %d", n, m) != 2) {
        fprintf(stderr, "Erro ao ler o número de átomos e ligações\n");
        return 1;
    }
    char buffer[256];
    fgets(buffer, sizeof(buffer), file); // Pula o restante da linha
    return 0;
}


int main() {
  
  FILE *file = fopen("HMDB0000034(Adenine).mol", "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

  pula_linhas(file, 3); // Ignora o cabeçalho

  int n, m, u, v, multiplicidade;
    char buffer[256], elemento;

  if (contagem_atomos_ligacoes(file, &n, &m)) { // Lendo o número de átomos e ligações
      fclose(file);
      return 1;
  }

  // cria grafo vazio
  grafo G = cria_grafo();
  
  for (int i = 1; i <= n; ++i) {
      fgets(buffer, sizeof(buffer), file);
      sscanf(buffer + 31, "%c", &elemento); // Extraindo o elementoo
      adiciona_vertice(i, elemento, G);
  }

  int id = 1;

  for (int i = 0; i < m; i++) {
      fscanf(file, "%d %d %d", &u, &v, &multiplicidade);
      //printf("u,v,multiplicidade: %d,%d,%d\n", u,v,multiplicidade);
      for (int j = 0; j < multiplicidade; j++){
       // printf("adicionando aresta: {%d,%d}", u, v);
        adiciona_aresta(id, u, v, G);
        ++id;
      }
      fgets(buffer, sizeof(buffer), file); // Pula o restante da linha
  }

// imprime informacoes do grafo e o destroi junto com o arquivo
imprime_grafo(G);
destroi_grafo(G);
fclose(file);

return 0;
}
