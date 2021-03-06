#ifndef INSTANCIA
#define INSTANCIA 

#include <vector> 
#include "arvore.h" 

using namespace std; 

//uma instância é o modelo de um problema diferente
//a ideia é armazenar várias instâncias que serão testadas para cada indivíduo
struct demanda
{
    double tamanho;
    double qnt; 
};


class Instancia {
    public: 
        //variaveis de problema
        vector<demanda> demandas;  
        double largura_peca; 
        //estoque máximo de peças 
        double estmax; 
        double * tamanho_por_padrao;
        double * desperdicios; 
        double total_desperdicio; 
        //vetor de vetores (matrizes) correspondente ao padrão de cortes 
        //ex: 
        /**   
        5  2.5  1.5
        {2,  0,  0}, //0
        {0,  4,  0}, //0
        {0,  0,  6}, //1
        {1,  2,  0}, //0
        {0,  3,  1}, //1
        };**/
        vector<int*> padroes_corte; 
    
        //métodos
        void adicionarPadraoCorte(int programacao[]);
        void adicionarDemanda(demanda d); 
        void printarPadroesCorte();
        void printarDemandas();
        //esses são copias dos métodos do antigo "problema.h"
        double tamanhoPorPadrao(int padraoi);
        double * desperdicio(double *total);
        double minimize(double *desperdicio, vector<int> x);
        
        //construtor
        Instancia(double largura, int est);
        ~Instancia();

};

vector<Instancia> trainingSet();
void gerarPadraoCorte(Instancia& i);
void copiarVetor(vector<int> vetor, vector<int>& destino);
void printarCortes(vector<vector<int>> cortes); 
void salvarCortes(vector<vector<int>> cortes, ofstream& arquivo);

#endif