/* 
NESSE ALGORITMO, ESTOU CONSIDERANDO QUE O NÓ NÃO TEM DIREÇÃO, CASO QUEIRA QUE SEJA DIRECIONADO, VERIFIQUE AONDE TEM COMENTARIO SOBRE ISSO.

AS FUNÇÕES QUE PERCORREM A ESTRUTURA DE NÓS E DE CAMINHOS NÃO ALTERAM A VARIAVEL ORIGINAL POIS ELAS SÃO RECURSIVAS, OU SEJA,
SE PRECISAREM IR PARA O PROXIMO NÓ, ELAS VÃO SE CHAMAR PASSANDO O PROXIMO NÓ.


*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

int global_graph = 0;

void printGraphModel (int x){
	switch (x){
		case 1:
			printf (" _____1_____\n");
			printf ("|     A     |\n");
			printf ("|    / \\    |\n");
			printf ("|   B---C   |\n");
			printf ("|  //       |\n");
			printf ("|  D=====E  |\n");
			printf ("|___________|\n");
			break;
		case 2:	
			printf (" _____2_____\n");
			printf ("| D---A     |\n");
			printf ("|  \\// \\    |\n");
			printf ("|   B---C   |\n");
			printf ("|___________|\n");
			break;
		case 3:
			printf (" _____3_____\n");
			printf ("|     A     |\n");
			printf ("|    //\\    |\n");
			printf ("|   B---C   |\n");
			printf ("|___________|\n");
			break;
		case 4:
			printf (" _____4_____\n");
			printf ("|     A     |\n");
			printf ("|    / \\    |\n");
			printf ("|   B---C   |\n");
			printf ("|  /        |\n");
			printf ("|  D=====E  |\n");
			printf ("|___________|\n");
			break;
		default:
			printf("");
			break;
	}
}

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
	printf("(Flag: %d)Path: %s <-> %s, ID: %d\n",P->flag,getNodeName(N,P->a),getNodeName(N,P->b),P->id);
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

void createNode (Node* N, char* nome){ //CRIA O NÓ COM O NOME PASSADO
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

void loadPreSetUm(Node* N,Path* P){
	createNode(N,"A");
	createNode(N,"B");
	createNode(N,"C");
	createNode(N,"D");
	createNode(N,"E");
	createPath(P,1,2);
	createPath(P,1,3);
	createPath(P,2,3);
	createPath(P,2,4);
	createPath(P,2,4);
	createPath(P,4,5);
	createPath(P,4,5);
	
	printf("Estrutura carregada: Exemplo um.\n");
}

void loadPreSetDois(Node* N,Path* P){
	createNode(N,"A");
	createNode(N,"B");
	createNode(N,"C");
	createNode(N,"D");
	createPath(P,1,2);
	createPath(P,1,2);
	createPath(P,1,4);
	createPath(P,1,3);
	createPath(P,3,2);
	createPath(P,2,4);
	
	printf("Estrutura carregada: Exemplo Dois.\n");
}

void loadPreSetTres  (Node* N,Path* P){
	createNode(N,"A");
	createNode(N,"B");
	createNode(N,"C");
	createPath(P,1,2);
	createPath(P,1,2);
	createPath(P,1,3);
	createPath(P,2,3);
	
	printf("Estrutura carregada: Exemplo tres.\n");
}

void loadPreSetQuatro(Node* N,Path* P){
	createNode(N,"A");
	createNode(N,"B");
	createNode(N,"C");
	createNode(N,"D");
	createNode(N,"E");
	createPath(P,1,2);
	createPath(P,1,3);
	createPath(P,2,3);
	createPath(P,2,4);
	createPath(P,4,5);
	createPath(P,4,5);
	
	printf("Estrutura carregada: Exemplo um.\n");
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
			printf("Todos Paths percorridos.\n");
			return 1;
		}
	else{
		printf("Path vazio encontrado.\n");
		return 0;
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
	if (P == NULL){
		printf("No recebido e nulo (PP)\n");
	}
	if (((P->a == me) || (P->b == me)) && P->flag == 0) //AQUI EU TO CONSIDERANDO IDA E VOLTA, OU SEJA, NO SEM DIREÇÃO
		if (P->prox == NULL)
			return 1;
		else
			return (1+possiblePaths(P->prox,me));
	else
		if (P->prox == NULL)
			return 0;
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

void isEulerian (Path* P, Node* N, int me, int *answer){ //ANSWER precisa ser passado como referencia
	int paths = possiblePaths(P,me);
	Path* p_tmp;
	int next_node = 1;
	if (paths > 1){
		while (paths > 0){
			if (me != gotoNode(me,next_node,P,N)){
				p_tmp = copyAllPaths(P);
				isEulerian(p_tmp,N,gotoNode(me,next_node,p_tmp,N,1),answer);
				paths = possiblePaths(P,next_node);
				next_node++;
			}
			else{
				next_node++;
				paths = possiblePaths(P,next_node);
			}
		}
	}
	else if (paths == 1){
		while (paths == 1){
			if (me != gotoNode(me,next_node,P,N)){
				me = gotoNode(me,next_node,P,N,1);
				next_node = 1;
				paths = possiblePaths(P,me);
			}
			else
			next_node++;
		}
		isEulerian(P,N,me,answer);
	}
	else if (paths == 0){
		*answer = *answer + checkAllFlags(P);
		printf("\n\n(DEBUG)Answer: %d.\n\n",*answer);
	}
}

int main() {
	Node* N = f_node();
	Path* P = f_path();
	int me; //ID DO NÓ AONDE COMEÇO.
	int opt,opt_aux,opt_aux_duo,opt_loop; //OPCOES QUE SERÃO LIDAS COMO INTEIRO
	char opt_char[40]; //OPCOES QUE SERAO LIDAS COMO CHAR
	int confirm = 0;
	opt_aux=opt_aux_duo = 0;
	while (confirm != 1){
		printf("Voce deseja precarregar alguma estrutura de nos?\n");
		printf("Exemplos: (1),(2),(3),(4),(5 - Trabalho)\n");
		scanf("%d",&opt);
		system("cls");
		printf("Voce selecionou a opcao %d, deseja carregar essa estrutura? (1- Sim)\n",opt);
		printGraphModel(opt);
		scanf("%d",&confirm);
	}
	printf("\n");
	switch (opt){
		case 5:
			loadPreSet(N,P);
			me=10;
			break;
		case 1:
			loadPreSetUm(N,P);
			global_graph=1;
			me=1;
			break;
		case 2:
			loadPreSetDois(N,P);
			global_graph=2;
			me=1;
			break;
		case 3:
			loadPreSetTres(N,P);
			global_graph=3;
			me=1;
			break;
		case 4:
			loadPreSetQuatro(N,P);
			global_graph=4;
			me=1;
			break;
		default:
			printf("Opcao invalida, iniciando programa com estrutura de nos zerada.\n");
	}
	system("pause");
	system("cls");

	
	while (true){
		printGraphModel (global_graph);
		printf("\nEu estou em %s\n\n",getNodeName(N,me));
		printf("O que voce quer fazer?\n1- Adicionar um no(vertice)\n2- Adicionar um caminho(aresta)\n3- Ir para no.\n4- Ir para (flag).\n5- Mostrar todos os nos\n6- Mostrar todos os caminhos\n7- Resetar Flags\n8- Checar: todos os camihos estao com flag?\n9- Copiar todos os caminhos e os mostrar.\n10- Quantos caminhos tem o no X\n11- Esse grafo tem quantos camihos eulerianos?\n100- Sair.\nDigite a opcao: ");
		scanf("%d",&opt);
		printf("\n");
		switch (opt){
			case 1:
				opt_loop=2;
				while (opt_loop !=1){
					printf("Digite o nome do no (recomendo ser uma letra): ");
					scanf("%s",&opt_char);
					printf("\nConfirmar: %s? (1- Sim)\n",opt_char);
					scanf("%d",&opt_loop);
				}
					me = 1;
					createNode(N,opt_char);
				break;
			case 2:	
				opt_loop=2;
				while (opt_loop !=1){
					printf("Digite o nome da primeira ponta da aresta: ");
					scanf("%s",&opt_char);
					opt_aux= getNodeId(N,opt_char);
					printf("Digite o nome da segunda ponta da aresta: ");
					scanf("%s",&opt_char);
					opt_aux_duo= getNodeId(N,opt_char);
					printf("\nConfirmar (ID) %s - %s? (1- Sim)\n",getNodeName(N,opt_aux),getNodeName(N,opt_aux_duo));
					scanf("%d",&opt_loop);
				}
					createPath(P,opt_aux,opt_aux_duo);
				break;
			case 3:
				printf("digite o nome do no que voce quer ir: ");
				scanf("%s",&opt_char);
				me = gotoNode(me,getNodeId(N,opt_char),P,N);
				printf("\n");
				break;
			case 4:
				printf("digite o nome do nome que voce quer ir: ");
				scanf("%s",&opt_char);
				me = gotoNode(me,getNodeId(N,opt_char),P,N,1);
				printf("\n");
				break;
			case 5:
				printAllNode(N);
				break;
			case 6:
				printAllPath(N,P);
				break;
			case 7:
				resetFlag(P);
				break;
			case 8:
				checkAllFlags(P);
				break;
			case 9:
				printAllPath(N,P);
				printf("\n\n");
				printAllPath(N,copyAllPaths(P));
				break;
			case 10:
				printf("digite o id do comodo que voce quer checar: ");
				scanf("%d",&opt_loop);
				printf("\nForam encontrado %d caminhos possiveis",possiblePaths(P,opt_loop));
				printf("\n");
				break;
			case 11:
				opt_loop = 0;
				isEulerian(P,N,me,&opt_loop);
				if (opt_loop>0)
					printf("\n\n\nForam encontrados %d caminhos eulerianos.\n",opt_loop);
				else
					printf("\n\n\nNao foram encontrados caminhos eulerianos.\n",opt_loop);
				break;
			case 100:
				system("cls");
				printf("saindo do programa.");
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
