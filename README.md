# Laboratorio de Sistemas Operacionais 3 - Manipulação de threads
## Resumo
Os programas do presente repositório são destinados a resolução das problemáticas apresentadas pelo professor Rodrigo Campiolo com foco na programação de threads.

## Problemáticas
- 1. Faça um programa com N threads que localiza um valor em um vetor de inteiros. O espaço de busca no vetor deve ser distribuído para as N threads. 
    - programa proposto como solucao: search\_value.c
- 2. Implemente um programa multithread com pthreads que calcule:
    - a média aritmética de cada linha de uma matriz MxN e devolva o resultado em um vetor de tamanho M.
    - a média geométrica de cada coluna de uma matriz MxN e devolva o resultado em um vetor de tamanho N.
    - O programa deve gerar matrizes MxN com elementos aleatórios para arquivos; usar técnicas de paralelização de funções e de dados; ler matrizes MxN de arquivos no formato em anexo; gravar os resultados em um arquivo texto.
    - programa proposto como solucao: matrix\_calculator.c
## Instruções
- Utilizar comando `make` para compilar ambos os programas
- search_value.c: `./search_value <array_size> <value_to_find> <n_threads>`
- matrix\_calculator.c: `./matrix_calculator <M> <N> <output_file> [n_threads]`
