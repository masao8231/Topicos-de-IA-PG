#include "funcoes.h"
#include <stdlib.h>
#include <iostream>
#include <stdbool.h>
#include <string.h>
#include <random>
#include <cmath>

using namespace std; 


//construtor
Funcoes::~Funcoes(){}

Funcoes::Funcoes(){
    l = 0;
    d = 0; 
}


//operação de soma 
double Funcoes::soma(double x1, double x2){
    return fabs(x1 + x2);
}

//operação de subtração
double Funcoes::subtracao(double x1, double x2){
    return fabs(x1 - x2);
}

//operação de multiplicação
double Funcoes::multiplicacao(double x1, double x2){
    return fabs(x1 * x2);
}

//operação de divisão
double Funcoes::divisao(double x1, double x2){
    if (x2 == 0)
        return fabs(x1);
    return fabs(x1/x2);
}

//operação de resto
double Funcoes::resto(double x1, double x2){
    if (x2 == 0)
        return x1;
    return (int)x1%(int)x2;
}

double Funcoes::sen(double x1, double x2){ 
    return fabs(x1 * sin(x2));
}

//verifica se x1 é menor que x2 
bool Funcoes::menorique(double x1, double x2){
    return x1 <= x2;
}

//verifica se x1 é maior que x2 
bool Funcoes::maiorique(double x1, double x2){
    return x1 >= x2;
}

//verifica se x1 E x2 é uma verdade  
bool Funcoes::AND(bool x1, bool x2){
    return x1 && x2;
}

//verifica se x1 OU x2 é uma verdade 
bool Funcoes::OR(bool x1, bool x2){
    return x1 || x2;
}

//Carrega e valida as expressões na árvore 
saida Funcoes::eval(arvoregenes programa, double l, double d){
    saida s; 
    s.binario = false; 
    s.numerico = 0;
    //se for uma árvore vazia, apenas retorne zero
    if (!programa){
        return s; 
    }

    //depois, verifica se os nós são folhas da árvore 
    //pois são as folhas da árvore que são os números, e variáveis, em outras palavras, terminais
    if (!programa->filhodireito && !programa->filhoesquerdo){
        if (strcmp(programa->chave, "l") == 0){
            s.numerico = l;
        } else if(strcmp(programa->chave, "d") == 0){
            s.numerico = d;
        } else {
            s.numerico = atoi(programa->chave);
        }
    }

    //lendo a subárvore da esquerda 
    saida valor_e = eval(programa->filhoesquerdo, l, d);

    //lendo a subárvore da direita 
    saida valor_d = eval(programa->filhodireito, l, d);

    if (strcmp(programa->chave, "+") == 0){
        s.numerico = soma(valor_e.numerico, valor_d.numerico);
    }

    else if (strcmp(programa->chave, "-") == 0){
        s.numerico = subtracao(valor_e.numerico, valor_d.numerico);
    }

    else if (strcmp(programa->chave, "*") == 0){
        s.numerico = multiplicacao(valor_e.numerico, valor_d.numerico);
    }

    else if (strcmp(programa->chave, "/") == 0){
        s.numerico = divisao(valor_e.numerico, valor_d.numerico);
    }

    else if (strcmp(programa->chave, "MOD") == 0){
        s.numerico = resto(valor_e.numerico, valor_d.numerico);
    }

    else if (strcmp(programa->chave, "SIN") == 0){
        s.numerico = sen(valor_e.numerico, valor_d.numerico);
    }

    else if (strcmp(programa->chave, ">=") == 0) {
        s.binario = maiorique(valor_e.numerico, valor_d.numerico);
        if (s.binario){
            s.numerico = valor_d.numerico;
        } else {
            s.numerico = valor_e.numerico;
        }
    }
    else if (strcmp(programa->chave, "<=") == 0) {
        s.binario = menorique(valor_e.numerico, valor_d.numerico);
        if (s.binario){
            s.numerico = valor_e.numerico;
        } else {
            s.numerico = valor_d.numerico;
        }
    }

    else if (strcmp(programa->chave, "AND") == 0){
        s.binario = AND(valor_e.binario, valor_d.binario);
    }

    else if (strcmp(programa->chave, "OR") == 0){
        s.binario = OR(valor_e.binario, valor_d.binario);
    }

    return s; 

    /**
    É possível agora fazer essa função retornar dois valores consecutivos. 
    Usando o registro Saída
    
    saida registro:
        real numerico,
        logico binario
    fim_registro
     **/
}

//gera um número aleatório 
int geraNum(int min, int max){
    std::random_device rd; // obtém um numero aleatorio pelo hardware 
    std::mt19937 gen(rd()); // semea o gerador 
    std::uniform_int_distribution<> distr(min, max); // define o alcance 

    return distr(gen);  // gera os números e retorna :) 
}

//gera um número real aleatório
double randomdouble(double min, double max){
	std::random_device rd; 
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<> distr(min, max);
	return distr(eng);
}