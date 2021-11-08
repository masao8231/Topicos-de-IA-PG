#include "includes/arvore.h"
#include "includes/funcoes.h"
#include "includes/instancia.h"
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <vector>

#define POPMAX 1000
#define DEPTH_I 10
#define GEN_MAX 100

using namespace std;
Funcoes f;
int prof = DEPTH_I;

//gerações
int geracoes = 0;

//funções prototipadas
void fitness(arvoregenes individuo, float *nota, float *fitness_demanda, float *fitness_desp, vector<Instancia> problemas);
void limparPopulacao(vector<arvoregenes> &pop);

//Reproduz os genes da população seguinte
arvoregenes reproducao(arvoregenes programa)
{
	//simplesmente copia a árvore
	arvoregenes novo_individuo = copiaArvore(programa);
	return novo_individuo;
}

//Cria uma subárvore aleatória com base no ponto de crossover
arvoregenes mutacao(arvoregenes programa)
{

	arvoregenes genes;
	char *chave;

	//criar a chave
	chave = (char *)malloc(strlen(programa->chave) + 1);
	strcpy(chave, programa->chave);

	//mutante criado
	arvoregenes mutante;

	//raiz baseada no pai
	mutante = criaArvore(chave);
	//gera uma ramificação aleatória
	arvoregenes alteracao = gerarPopulacao(DEPTH_I, alteracao);

	if (geraNum(0, 1) == 0)
	{
		//copia a subarvore esquerda
		genes = copiaArvore(programa->filhoesquerdo);
		mutante->filhoesquerdo = genes;
		mutante->filhodireito = alteracao;
	}
	else
	{
		//copia a subarvore direita
		genes = copiaArvore(programa->filhodireito);
		mutante->filhodireito = genes;
		mutante->filhoesquerdo = alteracao;
	}

	return mutante;
}

//Essa função faz com que a subárvore alvo herde os atributos do gene transferido
void herdarGenes(arvoregenes *genes, arvoregenes heranca)
{
	//aloca o tamanho da nova chave na memória
	char *nova_chave;
	nova_chave = (char *)malloc(strlen(heranca->chave) + 1);
	//e copia o conteúdo da chave nova.
	strcpy(nova_chave, heranca->chave);

	//apaga os nodos laterais
	apagaNodo((&(*genes)->filhodireito));
	apagaNodo((&(*genes)->filhoesquerdo));
	//insere a nova chave
	free((*genes)->chave);
	(*genes)->chave = nova_chave;
	//e então copia os genes para as subárvores
	(*genes)->filhodireito = copiaArvore(heranca->filhodireito);
	(*genes)->filhoesquerdo = copiaArvore(heranca->filhoesquerdo);
}

//A função que irá cruzar um indivíduo com outro
void crossover(arvoregenes pai, arvoregenes mae, arvoregenes *prole_1, arvoregenes *prole_2)
{
	//copia os genes dos parentes
	arvoregenes genes_pai = copiaArvore(pai);
	arvoregenes genes_mae = copiaArvore(mae);

	//pega os pontos de crossover
	arvoregenes cp_1 = crossoverPoint(genes_pai->filhodireito);
	arvoregenes cp_2 = crossoverPoint(genes_mae->filhoesquerdo);

	//copia as heranças
	arvoregenes heranca_1 = copiaArvore(cp_1);
	arvoregenes heranca_2 = copiaArvore(cp_2);

	//herda os genes
	herdarGenes(&cp_1, heranca_2);
	herdarGenes(&cp_2, heranca_1);

	ordem(cp_1);

	//libere a memória
	apagaNodo(&heranca_1);
	apagaNodo(&heranca_2);

	*prole_1 = genes_pai;
	*prole_2 = genes_mae;
}

void PG(vector<arvoregenes> &individuos, vector<Instancia> problemas)
{
	//variaveis de fitness
	float fitness_demanda = 0; 
	float fitness_desp = 0;
	float nota = 0; 

	//variaveis de controle 
	float melhor_demanda = 0; 
	float melhor_desp = 9999;
	float melhor_nota = 0; 

	//itera pelo vetor de indivíduos 
	for (int i = 0; i<individuos.size(); i++){
		//avalia o indivíduo
		fitness(individuos[i], &nota, &fitness_demanda, &fitness_desp, problemas);
		
	}

}

//a função que vai lidar com o problema em si
//a ideia será fazer o programa gerado pela GP definir o número de cortes em função da largura e demanda definida
//fitness(programa, nota, solução, desperdício)
void fitness(arvoregenes individuo, float *nota, float *fitness_demanda, float *fitness_desp, vector<Instancia> problemas)
{

	//testa o indivíduo para todas as instâncias
	for (int pr = 0; pr < problemas.size(); pr++)
	{
		//variáveis de decisão
		Instancia problema = problemas[pr];
		int *cortes;
		//variáveis de demanda
		//demandas totais (em quantidade)
		float max_demandas = problema.demandas.size();

		//demandas atendidas
		float demandas_atendidas = 0; 
		//criar o vetor de cortes
		cortes = (int *)malloc(problema.padroes_corte.size() * sizeof(int));

		//calcular os desperdícios
		float *desp;
		float total_desperdicios = 0;
		//desp(i) sendo i itens de cada padrão de corte
		desp = problema.desperdicio(&total_desperdicios);

		//para cada padrão de corte testar o programa
		for (int j = 0; j < problema.padroes_corte.size(); j++)
		{
			//essa variável é criada por conta do C não dar um valor 0 para um vetor inicializado
			//assim o resultado não mostra algum número gigante sem lógica alguma ao invés de um simples zero
			int temp_cortes = 0;
			for (int i = 0; i < problema.demandas.size(); i++)
			{
				//peças cortadas para cada padrão de corte
				float peca_tam = problema.tamanhoPorPadrao(i);
				//testa o programa com base no tamanho da peça e da demanda
				saida out = f.eval(individuo, peca_tam, (problema.demandas[j].tamanho));
				//se a equação for verdadeira
				//aloca como se fosse um corte para esse padrão
				if (out.binario)
				{
					temp_cortes += (int)out.numerico;
					cortes[j] = temp_cortes;
					//caso contrário, não altera
				}
				else
				{
					cortes[j] = temp_cortes;
				}
			}
		}

		//pega o total de desperdício
		float desp_solucao = problema.minimize(desp, cortes);
		//cout << total_desperdicios;
		//isso contudo, deve ser executado em várias instâncias ou seja, será acumulado valores proporcionais
		//o objetivo é minimizar os desperdícios, então a meta é a porcentagem desses desperdícios sempre serem menores
		*fitness_desp += (desp_solucao / total_desperdicios);

		for (int i = 0; i<problema.demandas.size(); i++){
			for (int j = 0; j<problema.padroes_corte.size(); j++){
				
				float qnt = 0;
				float total_cortes = 0;
				float media_demanda = 0;
				float media_cortes = 0;

				qnt += cortes[j] * (problema.demandas[i].qnt * problema.demandas[i].tamanho);
				total_cortes += cortes[j];
				//primeira condição: se a demanda está sendo atendida
				//verificar se a quantidade produzida das peças de demanda(i) atende ou supera as demandas
				if (qnt >= (problema.demandas[i].qnt * problema.demandas[i].tamanho)){
					demandas_atendidas += 1; 
					media_demanda += 1; 
				} else {
					media_demanda -= 1; 
				}

				//segunda condição: se os cortes estão ultrapassando o estoque
				if (total_cortes > problema.estmax){
					media_cortes -= 1; 
				} else {
					media_cortes += 1; 
				}
				//gera a média das demandas
				media_demanda = media_demanda/problema.demandas.size();
				media_cortes = media_cortes/problema.padroes_corte.size();

				*nota += (media_demanda + media_cortes)/2;
			}
		}

		//calcular o fitness da demanda
		*fitness_demanda += (demandas_atendidas/max_demandas);


		
		// //[DEBUG] printar a solução gerada
		//  for (int i = 0; i < problema.padroes_corte.size(); i++)
		//  {
		//  	cout << cortes[i] << "\n";
		//  }

		//garbage colector 
		free(cortes);
		free(desp);
	}

	*fitness_demanda = *fitness_demanda/problemas.size();
	*fitness_desp = *fitness_desp/problemas.size();
    *nota = (*nota/problemas.size()) * 100;
	cout << *nota;
}

//cria a população inicial com base em programas aleatórios
vector<arvoregenes> populacaoInicial(int q, int maxlv)
{
	//insere as árvores randomicamente geradas de níveis aleatórios (que não passem da profundidade máxima)
	vector<arvoregenes> individuos;
	for (int i = 0; i < q; i++)
	{
		//individuos[i] = gerarPopulacao(geraNum(maxlv), individuos[i]);
		//a raiz consistirá nos operadores de >= e <=
		arvoregenes programa = criaArvore((char *)logic_set[geraNum(0, LOGIC_LINE - 1)]);
		programa->filhoesquerdo = gerarPopulacao(geraNum(1, maxlv), programa->filhoesquerdo);
		programa->filhodireito = gerarPopulacao(geraNum(1, maxlv), programa->filhodireito);
		individuos.push_back(programa);
	}
	return individuos;
}

//Limpa a população de programas
void limparPopulacao(vector<arvoregenes> &pop)
{
	if (pop.size() > 0)
	{
		for (int i = 0; i < pop.size(); i++)
			//deleta o nodo da memória para evitar memory leak
			apagaNodo(&pop[i]);
		//limpa todos os elementos do vetor
		pop.clear();
	}
}

int main()
{
	//população inicial
	vector<arvoregenes> programas = populacaoInicial(POPMAX, DEPTH_I);
	float nota = 0;
	float demandas = 0;
	float desperdicio = 0;

	vector<Instancia> problemas = trainingSet();

	fitness(programas[0], &nota, &demandas, &desperdicio, problemas);

	//i.printarPadroesCorte();

	// while (geracoes < GEN_MAX)
	// {
	// 	PG(programas);
	// }

	// cout << "Problemas Resolvidos: " << problema_resolvido;

	return 0;
}
