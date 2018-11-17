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
	int a,b,id,flag;
}Path;

typedef struct node{
	struct node* prox;
	int id;
	char nome[40];
}Node;

int gotoNode (int, int, Path*, Node*,int = 0); //FLAG VAI COMO PADRÃO OCULTO 0
void createPath (Path*, int, int, int = 0);

int getNodeId(Node* N, char nome[40]){ //RETORNA O ID DO NÓ CUJO NOME FOI PASSADO
	if (N == NULL){
		printf("No recebido e nulo(GNI).\n");
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
		printf("No recebido e nulo(GNN).\n");
		return 0;
	}
	if (N->id == id)
		return N->nome;
	else
		getNodeName(N->prox,id);	
}

void printPath (Node* N, Path* P){ //PRINTA TO CAMINHO QUE FOI PASSADO E SEU ID
	printf("(%d)Path: %s <-> %s, ID: %d\n",P->flag,getNodeName(N,P->a),getNodeName(N,P->b),P->id);
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
		printf("No recebido e nulo.(PAN)\n");
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
	P->flag=0;
	return P;
}

void createPath (Path* P, int a, int b,int flag){ //CRIA O CAMINHO DE A ATÉ B
	int temp=0;	
	if (P == NULL){
		printf("No recebido e nulo(CP).\n");
		exit(0);
	}
	if (P->a == 0){
		P->a = a;
		P->b = b;
		P->prox = NULL;
		P->id=0;
		P->flag=flag;
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
		P->prox->flag=flag;
	}
}

void createNode (Node* N, char nome[40]){ //CRIA O NÓ COM O NOME PASSADO
	if (N == NULL){
		printf("No recebido e nulo(CN).\n");
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

int gotoNode (int my_node, int dest_node, Path* P,Node* N,int flag){ //CAMINHA DO NÓ A ATÉ O B
	while (P != NULL){ //Acho que fiz meio zuado, trocar isso por if também funciona.
		if (P->a == my_node)
			if (P->b == dest_node){
				if(P->flag==0){
					P->flag=flag;
					if (flag == 0)
						printf("TESTE: O caminho de %s ate %s e possivel\n",getNodeName(N,my_node),getNodeName(N,dest_node));
					else
						printf("movendo de %s para %s\n",getNodeName(N,my_node),getNodeName(N,dest_node));
					return dest_node;
				}
				//else
					//printf("Caminho encontrado, porem o mesmo esta marcado, procurando outro caminho.\n");
			}
		if (P->b == my_node) //CASO O NÓ SEJA DIRECIONAL, REMOVER ESSA CONDIÇÃO
			if (P->a == dest_node){
				if (P->flag==0){
					P->flag=flag;
					if (flag == 0)
						printf("TESTE: O caminho de %s ate %s e possivel\n",getNodeName(N,my_node),getNodeName(N,dest_node));
					else
						printf("movendo de %s para %s\n",getNodeName(N,my_node),getNodeName(N,dest_node));
					return dest_node;
				}
				//else
					//printf("Caminho de %s para %s encontrado, porem o mesmo esta marcado, procurando outro caminho.\n",getNodeName(N,my_node),getNodeName(N,dest_node));
			}
		if ((P->a != my_node) or (P->b != my_node))
			return (gotoNode(my_node,dest_node,P->prox,N,flag));
	}
		printf("O caminho de %s ate %s nao foi possivel.\n",getNodeName(N,my_node),getNodeName(N,dest_node));
		return my_node;
}

void loadPreSet(Node* N,Path* P){
	createNode(N,"piscina");
	createNode(N,"sala de Jogos");
	createNode(N,"quarto de hospedes");
	createNode(N,"bar");
	createNode(N,"dormitorio");
	createNode(N,"dependencia de empregada");
	createNode(N,"adega");
	createNode(N,"cozinha");
	createNode(N,"dispensa");
	createNode(N,"jardim");
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
	printf("Estrutura carregada: trabalho.\n");
}

void loadPreSetEuler(Node* N,Path* P){
	/*createNode(N,"Um");
	createNode(N,"Dois");
	createNode(N,"Tres");
	createNode(N,"Quatro");
	createNode(N,"Cinco");
	createPath(P,1,2);
	createPath(P,1,3);
	createPath(P,2,3);
	createPath(P,2,4);
	createPath(P,2,4);
	createPath(P,4,5);
	createPath(P,4,5);*/
	createNode(N,"Um");
	createNode(N,"Dois");
	createNode(N,"Tres");
	createNode(N,"Quatro");
	createPath(P,1,2);
	createPath(P,1,2);
	createPath(P,1,4);
	createPath(P,1,3);
	createPath(P,3,2);
	createPath(P,2,4);
	
	printf("Estrutura carregada: Exemplo euleriano.\n");
}

void resetFlag (Path* P){
	P->flag=0;
	if (P->prox != NULL)
		resetFlag(P->prox);	
}

int checkAllFlags (Path* P){
	if (P->flag == 1)
		if (P->prox != NULL)
			checkAllFlags(P->prox);
		else{
			printf("\n\n\nTodos Paths percorridos.\n\n");
			return 0;
		}
	else{
		printf("\n\n\nPath vazio encontrado.\n\n");
		return 1;
	}
}

Path* copyAllPaths(Path* P){
	Path* P_cp = f_path();
	Path* P_tmp = P;
	
	while (P_tmp->prox != NULL){
		createPath (P_cp,P_tmp->a,P_tmp->b,P_tmp->flag);
		P_tmp = P_tmp->prox;
	}
	createPath (P_cp,P_tmp->a,P_tmp->b,P_tmp->flag);
	return P_cp;
}

int possiblePaths(Path* P, int me){
	if (P == NULL)
		return 0;
	if (((P->a == me) || (P->b == me)) && P->flag == 0) //AQUI EU TO CONSIDERANDO IDA E VOLTA, OU SEJA, NO SEM DIREÇÃO
		return (1+possiblePaths(P->prox,me));
	else
		return (0+possiblePaths(P->prox,me));
}

void freePath(Path* P){
	path* P_TMP=P->prox;
	while (P->prox != NULL){
		free (P);
		P = P_TMP;
		P_TMP = P_TMP->prox;
	}
	free(P);
}

void isEulerian (Path* P, Node* N, int me){
	int paths=possiblePaths(P,me);
	Path* P_tmp = P;
	int test=1;
	if (paths>0)
		while (paths>0){
			P_tmp=P;
			if (me != gotoNode(me,test,P,N)){ //SE ISSO FOR DIFERENTE, EU POSSO AVANCAR
				if (paths > 1)
					P_tmp = copyAllPaths(P); //COPIO UM CAMINHO
				//printf("\n\nBranch em me: %d e path: %d\n\n",me,test);
				isEulerian(P_tmp,N,gotoNode(me,test,P_tmp,N,1)); //TESTO SE É EULERIANO AGORA TENDO UM NOVO EU
				//freePath(P_tmp);
				//printf("\n\nFECHEI UM EULERIANO %d %d\n\n",me,test);
				test++;
				paths--;
			}
			else{
				test++;
			}
		}
	else{
		checkAllFlags(P);
	}
}

int main() {
	Node* N = f_node();
	Path* P = f_path();
	int me; //ID DO NÓ AONDE COMEÇO.
	int opt; //OPCOES QUE SERÃO LIDAS COMO INTEIRO
	char opt_char[40]; //OPCOES QUE SERAO LIDAS COMO CHAR
	printf("Voce deseja precarregar alguma estrutura de nos?\n1- Trabalho\n2- Euleriano\n");
	scanf("%d",&opt);
	printf("\n");
	switch (opt){
		case 1:
			loadPreSet(N,P);
			me=10;
			break;
		case 2:
			loadPreSetEuler(N,P);
			me=1;
			break;
		default:
			printf("Opcao invalida, iniciando programa com estrutura de nos zerada.\n");
	}
	system("pause");
	system("cls");

	
	while (true){
		printf("O que voce quer fazer?\n1- Aonde eu estou?\n2- Ir para (ID).\n3- Ir para (flag).\n4- Mostrar todos os nos\n5- Mostrar todos os caminhos\n6- Resetar Flags\n7- Check All Paths\n8- Copy all path, print original and copy\n9- Quantos caminhos tem o comodo X\n10- Is eulerian?\nDigite a opcao: ");
		scanf("%d",&opt);
		printf("\n");
		switch (opt){
			case 1:
				printf("Eu estou em %s\n",getNodeName(N,me));
				break;
			case 2:
				printf("digite o id do lugar que voce quer ir: ");
				scanf("%d",&opt);
				me = gotoNode(me,opt,P,N);
				printf("\n");
				break;
			case 3:
				printf("digite o id do lugar que voce quer ir: ");
				scanf("%d",&opt);
				me = gotoNode(me,opt,P,N,1);
				printf("\n");
				break;
			case 4:
				printAllNode(N);
				break;
			case 5:
				printAllPath(N,P);
				break;
			case 6:
				resetFlag(P);
				break;
			case 7:
				checkAllFlags(P);
				break;
			case 8:
				printAllPath(N,P);
				printf("\n\n");
				printAllPath(N,copyAllPaths(P));
				break;
			case 9:
				printf("digite o id do comodo que voce quer checar: ");
				scanf("%d",&opt);
				printf("\nForam encontrado %d caminhos possiveis",possiblePaths(P,opt));
				printf("\n");
				break;
			case 10:
				isEulerian(P,N,me);
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
