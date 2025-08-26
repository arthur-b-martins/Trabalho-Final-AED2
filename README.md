### Trabalho-Final-AED2

## Arthur:

Vou comentar aqui coisas que não podemos nos esquecer!!!


# Coisas a fazer:

 - Generalizar muitas coisas kkkk
 - trocar o jeito de limpar o buffer para o do trabalho passado 

# Caso a professora pergunte sobre a minha parte:

 - As árvores são estruturas recursivas, ou seja, 
 geralmente você recebe o nó raíz, faz alguma coisa (tipo alguma verificação)
 e chama a mesma função para o nó da esquerda, e ou nó da direita 


 - no caso da inserção na Bst, a gente faz assim:
 "inserir_bst(&((*raiz)->esq), info);"

 ou seja, a gente passa o ENDEREÇO DO PONTEIRO, em outras palavras, um ponteiro duplo

 porque? 
 porque quando chegarmos em raiz == NULL, precisamos fazer 
 raiz = novo_ponteiro
 MAAAS se 'raiz' é um valor passado como parâmetro por valor, 
 fazer "raiz = novo_ponteiro" DENTRO da função não altera 
 nada FORA da função... Portanto nós devemos passar como ponteiro duplo,
 ou seja, passar o ponteiro como REFERENCIA, assim da para modificar
 dentro da função e a mudança permanecer!!!! 

  - Caso a função retorne algo, tipo se ela retorna -1 em caso de erro,
  nós devemos chama-la recursivamente dando um return, tipo:
  return inserir_bst(&((*raiz)->dir), info);
  porque ai se der merda em alguma recursão, vai retornando, até retornar
  para a main o -1 que deu merda laa em baixo

 - Estou retornando na busca o ponteiro, para ser mais eficiente do que 
 retornar por valor uma strcut q tem uma estrofe inteira, etc.