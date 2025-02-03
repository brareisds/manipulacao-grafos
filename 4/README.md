# Trabalho 1 - Exercício 4

## Descrição

Este diretório contém a solução do **Exercício 4**. Além da implementação do código da biblioteca de grafos fornecida pelo professor, foram adicionadas funções que transformam um grafo G em um grafo ponderado.

> **Nota**: O arquivo original `testa_grafos.c` não foi modificado, então nem todas as funções implementadas são testadas diretamente por ele, pois algumas não são chamadas durante a execução (como as funções de remoção de vértices e arestas).

## Características do Grafo

- **Multigrafos**: O programa permite a criação de multigrafos, onde diferentes arestas podem ter as mesmas extremidades e as extremidades de uma aresta podem coincidir, formando laços.

## Modificações

A estrutura de vértice foi mantida conforme o código original, porém, na estrutura de aresta, foi adionado o membro "peso". A solução para este exercício baseia-se na implementação do Exercício 2.

### Principais Alterações:

- **Funções Modificadas**:

  - `imprime_grafo()`: agora imprime o peso das arestas, utilizando a notação `<id>:{u,v,peso}`.
  - `imprime_aresta()`: também foi modificada para incluir a exibição do peso das arestas.

- **Funções Adicionadas**:
  - `atualiza_pesos()`: função para atualizar os pesos das arestas com base em critérios definidos.
  - `peso()`: função que retorna o peso de uma aresta específica.

> **Nota**: As adições ao código estão sinalizadas com comentários.

## Limitações

- **Tratamento de erros**:
  - O programa assume que a quantidade de vértices inicialmente fornecida pelo usuário é uma entrada válida.
