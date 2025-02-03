# Trabalho 1 - Exercício 3

## Descrição

Este diretório contém a solução do **Exercício 3**. Além da implementação do código da biblioteca de grafos fornecida pelo professor, foram adicionadas funções que transformam um grafo G em um grafo induzido G[X], a partir de um conjunto de vértices X.

O código foi testado utilizando o programa `testa_grafos.c`, que foi modificado para permitir a geração do grafo induzido. Porém, nem todas as funções implementadas são testadas diretamente por ele, pois algumas não são chamadas durante a execução (como as funções de remoção de vértices e arestas).

## Características do Grafo

- **Multigrafos**: O programa permite a criação de multigrafos, onde diferentes arestas podem ter as mesmas extremidades e as extremidades de uma aresta podem coincidir, formando laços.

## Modificações

As estruturas de vértices, arestas e grafo foram mantidas conforme o código original. A solução para este exercício baseia-se na implementação do Exercício 2.

- **Funções Modificadas**:

  - No arquivo grafo.c: A função `destroi_grafo()`foi adaptada para ser compatível com as novas funções de destruição criadas.

- **Funções Adicionadas**:
  - No arquivo grafo.c: `le_ids_vertices_X()`, `cria_subconjunto()`, `grafo_induzido()`, `destroi_vertice()`, `destroi_aresta()`. `destroi_int()`.
  - No arquivo lista.c: `destroi_lista()` foi criada para permitir a destruição adequada de objetos usados como parâmetros.

> **Nota**: As adições ao código estão sinalizadas com comentários.

## Limitações

- **Tratamento de erros**:
  - O programa assume que a quantidade de vértices inicialmente fornecida pelo usuário é uma entrada válida.
  - As funções `destroi_vertice()` e `destroi_aresta()` foram implementadas para serem usadas em conjunto com `destroi_lista()` apenas para liberar a memória alocada dentro da função `destroi_grafo()`.
