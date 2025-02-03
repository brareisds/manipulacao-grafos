# Trabalho 1 - Exercício 2

## Descrição

Este diretório contém a solução do **Exercício 2**, onde foi implementado o código da biblioteca de grafos fornecida pelo professor. O código foi testado utilizando o programa `testa_grafos.c`, também disponibilizado.

> **Nota**: O arquivo `testa_grafos.c` não foi modificado, então nem todas as funções implementadas são testadas diretamente por ele, pois algumas não são chamadas durante a execução (como as funções de remoção de vértices e arestas).

## Características do Grafo

- **Multigrafos**: O programa permite a criação de multigrafos, onde diferentes arestas podem ter as mesmas extremidades e as extremidades de uma aresta podem coincidir, formando laços.

## Modificações

As estruturas de vértices, arestas e grafo foram mantidas conforme o código original fornecido. As únicas modificações foram feitas no arquivo `grafo.c`, onde somente as funções indicadas foram implementadas (`destroi_grafo()`, `adiciona_aresta()`, `remove_vertice()`, `remove_aresta()`).

## Limitações

- **Tratamento de erros**:  
  O programa assume que a quantidade de vértices inicialmente fornecida pelo usuário é uma entrada válida.
