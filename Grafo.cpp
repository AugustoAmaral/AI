/* 
NESSE ALGORITMO, ESTOU CONSIDERANDO QUE O NÓ NÃO TEM DIREÇÃO, CASO QUEIRA QUE SEJA DIRECIONADO, VERIFIQUE AONDE TEM COMENTARIO SOBRE ISSO.

AS FUNÇÕES QUE PERCORREM A ESTRUTURA DE NÓS E DE CAMINHOS NÃO ALTERAM A VARIAVEL ORIGINAL POIS ELAS SÃO RECURSIVAS, OU SEJA,
SE PRECISAREM IR PARA O PROXIMO NÓ, ELAS VÃO SE CHAMAR PASSANDO O PROXIMO NÓ.


*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>


typedef struct path{
	struct path* prox;
	int a,b,id;
}Path;

typedef struct node{
	struct node* prox;
	int id;
	char nome[40];
}Node;

int getNodeId(Node* N, char nome[40]){ //RETORNA O ID DO NÓ CUJO NOME FOI PASSADO
	if (N == NULL){
		printf("No recebido e nulo.\n");
		return 0;
	}
	if (strcmp(nome,N->nome) == 0)
		return N->id;
	else
		getNodeId(N->prox,nome);
}

void printNode (Node* N){ //PRINTA O NÓ PASSADO
	printf("No: %s, Id: %d\n",N->nome,N->id);
}

char* getNodeName (Node* N, int id){ // RETORNA O NOME DO NÓ COM O ID PASSADO
	if (N == NULL){
		printf("No recebido e nulo.\n");
		return 0;
	}
	if (N->id == id)
		return N->nome;
	else
		getNodeName(N->prox,id);	
}

void printPath (Node* N, Path* P){ //PRINTA TO CAMINHO QUE FOI PASSADO E SEU ID
	printf("Path: %s <-> %s, ID: %d\n",getNodeName(N,P->a),getNodeName(N,P->b),P->id);
}

void printAllPath (Node* N, Path* P){ //MOSTRA TODOS OS CAMINHOS DISPONIVEIS
	if (P == NULL){
		printf("Caminho recebido e nulo.\n");
		exit(0);
	}
	printPath(N,P);
	if (P->prox != NULL)
		printAllPath(N, P->prox);
}

void printAllNode (Node* N){ //MOSTRA TODOS OS NÓS EXISTENTES
	if (N == NULL){
		printf("No recebido e nulo.\n");
		exit(0);
	}
	printNode(N);
	if (N->prox != NULL)
		printAllNode(N->prox);
}

Node* f_node (){ //INICIA O PRIMEIRO NÓ
	Node* N = (Node*) malloc (sizeof(Node));
	N->id = 0;
	strcpy(N->nome,"Nenhum no");
	N->prox = NULL;
	return N;
}

Path* f_path(){ //INICIA O PRIMEIRO CAMINHO
	Path* P = (Path*) malloc (sizeof(Path));
	P->a=0;
	P->b=0;
	P->prox=NULL;
	P->id=0;
	return P;
}

void createPath (Path* P, int a, int b){ //CRIA O CAMINHO DE A ATÉ B
	int temp=0;	
	if (P == NULL){
		printf("No recebido e nulo.\n");
		exit(0);
	}
	if (P->a == 0){
		P->a = a;
		P->b = b;
		P->prox = NULL;
		P->id=0;
	}
	else{
		temp=1;
		while (P->prox != NULL){
			P = P->prox;
			temp++;
		}
		P->prox = (Path*) malloc (sizeof(Path));
		P->prox->a = a;
		P->prox->b = b;
		P->prox->prox = NULL;
		P->prox->id=temp;
	}
}

void createNode (Node* N, char nome[40]){ //CRIA O NÓ COM O NOME PASSADO
	if (N == NULL){
		printf("No recebido e nulo.\n");
		exit(0);
	}
	if (N->id == 0){
		N->prox = NULL;
		strcpy(N->nome,nome);
		N->id = (N->id+1);		
	}
	else{
		while (N->prox != NULL)
			N = N->prox;
		N->prox = (Node*) malloc (sizeof(Node));
		N->prox->prox = NULL;
		strcpy(N->prox->nome,nome);
		N->prox->id = (N->id+1);
	}
}

int gotoNode (int my_node, int dest_node, Path* P){ //CAMINHA DO NÓ A ATÉ O B
	while (P != NULL){
		if (P->a == my_node)
			if (P->b == dest_node){
				printf("O caminho e possivel, movendo para %d\n",dest_node);
				return dest_node;
			}
		if (P->b == my_node) //CASO O NÓ SEJA DIRECIONAL, REMOVER ESSA CONDIÇÃO
			if (P->a == dest_node){
				printf("O caminho e possivel, movendo para %d\n",dest_node);
				return dest_node;
			}
		if ((P->a != my_node) or (P->b != my_node))
			return (gotoNode(my_node,dest_node,P->prox));
	}
		printf("O caminho nao foi possivel.\n");
		return my_node;
}

void loadPreSet(Node* N,Path* P){
	createNode(N,"Piscina");
	createNode(N,"Sala de Jogos");
	createNode(N,"Quarto de Hospedes");
	createNode(N,"Bar");
	createNode(N,"Dormitorio");
	createNode(N,"Dependencia de empregada");
	createNode(N,"Adega");
	createNode(N,"Cozinha");
	createNode(N,"Dispensa");
	createNode(N,"Saida");
	createPath(P,1,10);
	createPath(P,1,10);
	createPath(P,1,9);
	createPath(P,1,8);
	createPath(P,1,3);
	createPath(P,2,3);
	createPath(P,2,3);
	createPath(P,3,4);
	createPath(P,4,5);
	createPath(P,5,6);
	createPath(P,5,6);
	createPath(P,7,8);
	createPath(P,7,8);
	createPath(P,8,9);
	printf("Estrutura carregada.\n");
}

int main() {
	Node* N = f_node();
	Path* P = f_path();
	int me=10; //ID DO NÓ AONDE COMEÇO.
	int opt;
	printf("Voce deseja precarregar a estrutura de nos do trabalho?\n1- Sim\n");
	scanf("%d",&opt);
	printf("\n");
	switch (opt){
		case 1:
			loadPreSet(N,P);
			break;
		default:
			printf("Opcao invalida, iniciando programa com estrutura de nos zerada.\n");
	}
	system("pause");
	system("cls");

	
	while (true){
		printf("O que voce quer fazer?\n1- Aonde eu estou?\n2- Ir para.\n3- Mostrar todos os nos\n4- Mostrar todos os caminhos\nDigite a opcao: ");
		scanf("%d",&opt);
		printf("\n");
		switch (opt){
			case 1:
				printf("Eu estou em %s\n",getNodeName(N,me));
				break;
			case 2:
				printf("digite o caminho que voce quer ir: ");
				scanf("%d",&opt);
				me = gotoNode(me,opt,P);
				printf("\n");
				break;
			case 3:
				printAllNode(N);
				break;
			case 4:
				printAllPath(N,P);
				break;
			default:
				printf("Opcao invalida.\n");
				break;
		}
		system("pause");
		system("cls");
		
	}
		return 0;
}
