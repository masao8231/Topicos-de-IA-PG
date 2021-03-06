## Listas de coisas a fazer
1. Testar se o interpretador está funcionando. ✔️

2. Antes de implementar totalmente o mesmo, reestruturar a árvore para suportar strings (assim é possível implementar expressões mais complexas, como estruturas condicionais, etc). ✔️

3. Por enquanto ainda será usada uma arvore binária, entretanto, é melhor já pensar em uma implementação de uma estrutura de arvore mais robusta. ✔️ 

    * 3.1 - Na verdade, acredito que árvore binária tem plena capacidade de resolver o problema do corte. ✔️

4. Na stack, adaptar o vetor para a classe std::Vector, considerando que ele já lida com memória alocada dinamicamente e não tem necessidade de usar espaço desnecessário na memória. (a struct stack foi deletada aliás, a ideia era usar a própria como interpretador mas dá pra fazer isso recursivamente sem a necessidade de usar outra estrutura de dados). ✔️

5. Pensar em uma maneira de gerar uma população inicial ✔️ . Que atenda as restrições do problema do corte unidimensional. ✔️

6. Fazer o interpretador reconhecer os terminais (as variáveis no caso). ✔️ 

7. A seleção natural funciona corretamente, entretanto é necessário fazer um polimento adequado aos métodos de crossover e mutação principalmente, de maneira que a árvore de expressões aumente até o seu limite imposto. Assim, é possível criar uma variabilidade consistente e que permita a uma tendência próxima à solução do problema. ✔️

    * 7.1 Ajustei os parâmetros da seleção natural, o que permite tolerar mais indivíduos, segundo os testes, alguns se aproximam da solução do problema, mas não conseguem resolver inteiramente, talvez seja mesmo necessário ajustar o crossover e mutação que possam melhorar o resultado ✔️

8. Caso os programas finalmente evoluam de maneira que sejam capazes de resolver o problema, testar várias configurações de problemas diferentes para verificar se a inteligência artificial consegue resolver qualquer tipo de problema.   ✔️

    * 8.1 Reprogramar o fitness com o novo método de bio-heurística ✔️

    * 8.2 Alterar o problema.h e problema.cpp, de modo que eles coletem qualquer instância de problema, assim, viabilizando o uso da PG ✔️

9 - Com o fitness funcionando, apenas é necessário coletar os melhores resultados, inserir mais instâncias de testes e assim permitindo o levantamento de dados. ✔️

10 - Nota de atualização: alterei o fitness e corrigi o bug do corte negativo, também mexi na função objetico (fo). Baseando-se em criar um fitness para capacidades de estoques mantidas: ``fo = ((fitness_demanda * 0.5) + (fitness_capacidades_mantidas * 0.5)) - fitness_desperdicio.`` O que ainda permite uma fo normalizada e com soluções que respeitem o limite de estoque para cada instância. 
    

