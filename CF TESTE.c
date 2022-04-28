#include "stdio.h"
#include "locale.h"
#include "string.h"
#define TAMANHO 50
#define True 1
#define False 0
float total;

struct produto{
	int id;
	char prod[40];
	float valor;
}produtos[TAMANHO];

struct end{
	char rua[100];
	int num;
};
struct client{
	int id;
	char nome[40]; 
	char cpf[15];
	float total;
	struct end cobranca;
	struct end entrega;
	struct end residencial;
	struct end matriz;
}cliente[TAMANHO];

struct compra{
	int id;
	int qtd;
	int prod;
	float valor;
	float total;
}carrinho[TAMANHO];


//CLIENTES - ENTRADA
int entrada(int posicao){
	setlocale(LC_ALL, "Portuguese");
	int resp = False;
	int num, quant;
	Flistar();
	carrinho[posicao].id = posicao;
	printf("\nID do produto que deseja adicionar: ");
	scanf("%d", &num);
	printf("quantidade de produtos: ");
 	scanf("%d", &quant);
	if(produtos[num].id != -1){
 		   carrinho[posicao].valor = produtos[num].valor;
 		   carrinho[posicao].prod = num;
 		   carrinho[posicao].qtd = quant;
 		   total += quant * produtos[num].valor;
 		   resp = True;
 	}
 	else{
 		carrinho[posicao].id = -1;
 	}
 	return resp;
}


//FORNECEDOR - ENTRADA
int Fentrada(int posicao){
	setlocale(LC_ALL, "Portuguese");
	int resp = False;
	produtos[posicao].id = posicao;
	printf("\nDigite o nome do produto: ");
	scanf("%s", produtos[posicao].prod);
	printf("Digite o preço do produto: ");
	scanf("%f", &produtos[posicao].valor);
}



//CLIENTES - INICIALIZAR
int inicializar(){
	int resp = False, i;
	for(i=0; i<TAMANHO; i++){
		carrinho[i].id = -1;
		cliente[i].id = -1;
	}
	resp = True;
	return resp;
}

//FORNECEDOR - INICIALIZAR
int Finicializar(){
	int resp = False, i;
	for(i=0; i<TAMANHO; i++){
		produtos[i].id = -1;
	}
	resp = True;
	return resp;
}



//CLIENTES - INCLUIR
int incluir(){
	int resp = False, i, posicao=-1;
	for(i=0; i<TAMANHO; i++){
		if(carrinho[i].id==-1){
			posicao = i;
			break;
		}
	}
	if(posicao != -1){
		if(entrada(posicao)){
			resp = True;
		}
	}else{
		resp = False;
	}
	return resp;
}


//FORNECEDOR - INCLUIR
int Fincluir(){
	int resp = False, i, posicao=-1;
	for(i=0; i<TAMANHO; i++){
		if(produtos[i].id==-1){
			posicao = i;
			break;
		}
	}
	if(posicao != -1){
		if(Fentrada(posicao)){
			resp = True;
		}
	}else{
		resp = False;
	}
	return resp;
}



//CLIENTES - LISTAR
int listar(){
	int resp = False, i;
	for(i=0; i<TAMANHO; i++){
		if(carrinho[i].id != -1){
			printf("\n\n**********************************");
			printf("\nID                   : %d", carrinho[i].id);
			printf("\nProduto                : %s", produtos[carrinho[i].prod].prod);
			printf("\npreço do produto       : %.2f", carrinho[i].valor);
			printf("\nquantidade de produtos : %d", carrinho[i].qtd);
			printf("\n\n**********************************");
		}
	}
	printf("\nO valor adicionado foi de: %.2f", total);
	resp = True;
	return resp;
}



//FORNECEDOR - LISTAR
int Flistar(){
	int resp = False, i;
	for(i=0; i<TAMANHO; i++){
		if(produtos[i].id != -1){
			printf("\n\n******************************");
			printf("\nID                  : %d", produtos[i].id);
			printf("\nProduto             : %s", produtos[i].prod);
			printf("\npreço do produto    : R$ %.2f", produtos[i].valor);
			printf("\n\n******************************");
		}
	}
	resp = True;
	return resp;
}



//CLIENTES - ALTERAÇÃO          vou ter q devolver a quantidade de produtos
int alteracao(){
	int resp = False, posicao = -1;
	int i;
	char confirma;
	listar();
	printf("\nQual é o ID do Registro? : ");
	scanf("%d", &posicao);
	fflush(stdin);
	if(carrinho[posicao].id != -1){
		printf("\nConfirma a Alteração? [S/N]: ");
		scanf("%c", &confirma);
		if(confirma == 'S'|| confirma =='s'){
			total -= (carrinho[posicao].qtd * carrinho[posicao].valor);
			entrada(posicao);
			resp = True;
		}
	}
	return resp;
}

//FORNECEDOR - ALTERAÇÃO
int Falteracao(){
	int resp = False, posicao = -1;
	char confirma;
	Flistar();
	printf("\nQual é o ID do Registro? : ");
	scanf("%d", &posicao);
	fflush(stdin);
	if(produtos[posicao].id != -1){
		printf("\nConfirma a Alteração? [S/N]: ");
		scanf("%c", &confirma);
		if(confirma == 'S'|| confirma =='s'){
			Fentrada(posicao);
			resp = True;
		}
	}
	return resp;
}

//CLIENTES - EXCLUSAO        vou ter q devolver a quantidade de produtos
int excluir(){
	int resp = False, posicao = -1;
	int i;
	char confirma;
	listar();
	printf("\nQual é o ID da compra? : ");
	scanf("%d", &posicao);
	fflush(stdin);
	if(carrinho[posicao].id != -1){
		printf("\nConfirma a exclusao? [S/N]: ");
		scanf("%c", &confirma);
		if(confirma == 'S'|| confirma =='s'){
			carrinho[posicao].id = -1;
			total -= carrinho[posicao].qtd * carrinho[posicao].valor;
			resp = True;
		}
	}
	return resp;
}

//FORNECEDOR - EXCLUSAO
int Fexcluir(){
	int resp = False, posicao = -1;
	char confirma;
	Flistar();
	printf("\nQual é o ID do Registro? : ");
	scanf("%d", &posicao);
	fflush(stdin);
	if(produtos[posicao].id != -1){
		printf("\nConfirma a exclusao? [S/N]: ");
		scanf("%c", &confirma);
		if(confirma == 'S'|| confirma =='s'){
			produtos[posicao].id = -1;
			resp = True;
		}
	}
	return resp;
}

//CLIENTES - FINALIZAR COMPRA
int finalizar(){
	int resp = False;
	int i, posicao =-1;
	
	for(i=0; i<TAMANHO; i++){
		if(cliente[i].id==-1){
			posicao = i;
			break;
		}
	}
	if(posicao != -1){
		listar();
		char confirma;
		cliente[posicao].id = posicao;
		printf("\nPrimeiro nome: ");
		scanf("%s", cliente[posicao].nome);
		printf("CPF: ");
		scanf("%s", cliente[posicao].cpf);
		printf("*endereço de cobrança*");
		printf("\nRua (nome simples ou número): ");
		scanf("%s", cliente[posicao].cobranca.rua);
		printf("Número: ");
		scanf("%d", &cliente[posicao].cobranca.num);
		printf("*endereço de entrega*");
		printf("\nRua (nome simples ou número): ");
		scanf("%s", cliente[posicao].entrega.rua);
		printf("Número: ");
		scanf("%d", &cliente[posicao].entrega.num);
		printf("*endereço residencial* (se não tiver = 0)");
		printf("\nRua (nome simples ou número): ");
		scanf("%s", cliente[posicao].residencial.rua);
		printf("Número: ");
		scanf("%d", &cliente[posicao].residencial.num);
		printf("*endereço da Matriz* (se não tiver = 0)");
		printf("\nRua (nome simples ou número): ");
		scanf("%s", cliente[posicao].matriz.rua);
		printf("Número: ");
		scanf("%d", &cliente[posicao].matriz.num);
		fflush(stdin);
		printf("\nfinalizar compra?[S/N] ");
		scanf("%c", &confirma);
		if(confirma == 'S'|| confirma =='s'){
			listar();
			printf("\nCliente que efetuou a compra: %s", cliente[posicao].nome);
			printf("\nCPF: %s", cliente[posicao].cpf);
			printf("\nendereço de cobrança: %s, Número: %d", cliente[posicao].cobranca.rua, cliente[posicao].cobranca.num);
			printf("\nendereço de entrega: %s, Número: %d", cliente[posicao].entrega.rua, cliente[posicao].entrega.num);
			if(cliente[posicao].residencial.num != 0){
				printf("\nendereço residencial: %s, Número: %d", cliente[posicao].residencial.rua, cliente[posicao].residencial.num);
			}
			if(cliente[posicao].matriz.num != 0){
				printf("\nendereço da Matriz: %s, Número: %d", cliente[posicao].matriz.rua, cliente[posicao].matriz.num);
			}
			if (cliente[posicao].total == 0){
				cliente[posicao].total = total;
			}
			printf("\nTotal : R$ %.2f", cliente[posicao].total);
			resp = True;
			for(i=0; i<TAMANHO; i++){
				carrinho[i].id = -1;
				total = 0;
			}
		}
		else {
			cliente[posicao].id = -1;
		}
	}
	return resp;
}

//DADOS DO CLIENTE
int dados(){
	int cont=0;
	int id;
	int pergunta;
	int opcao;
	int resp = False;
	int posicao;
	for(posicao=0; posicao<TAMANHO; posicao++){
		if(cliente[posicao].id != -1){
			printf("\n\n**************************************************");
			printf("\nID                                : %d", cliente[posicao].id);
			printf("\n\nCliente que efetuou a compra      : %s", cliente[posicao].nome);
			printf("\nCPF                               : %s", cliente[posicao].cpf);
			printf("\nendereço de cobrança              : %s, Número %d", cliente[posicao].cobranca.rua, cliente[posicao].cobranca.num);
			printf("\nendereço de entrega               : %s, Número %d", cliente[posicao].entrega.rua, cliente[posicao].entrega.num);
			if(cliente[posicao].residencial.num != 0){
				printf("\nendereço residencial              : %s, Número %d", cliente[posicao].residencial.rua, cliente[posicao].residencial.num);
			}
			if(cliente[posicao].matriz.num != 0){
				printf("\nendereço da Matriz                : %s, Número %d", cliente[posicao].matriz.rua, cliente[posicao].matriz.num);
			}
			printf("\nTotal a pagar                     : R$ %.2f", cliente[posicao].total);
			printf("\n\n**************************************************");
			cont++;
			resp = True;
		}
	}
	if (cont > 0){
		printf("\n[1] - para alterar / excluir dados do usuário ");
		printf("\n[0] - para sair");
		printf("\ndigite aqui: ");
		scanf("%d", &pergunta);
		if (pergunta == 1){
			printf("\ndigite o ID do usuário: ");
			scanf("%d", &id);
			printf("\n[0] - cancelar");
			printf("\n[1] - excluir dados do usuário");
			printf("\n[2] - alterar dados do usuário");
			printf("\ndigite aqui: ");
			scanf("%d", &opcao);
			if (opcao == 1 && cliente[id].id != -1){
				cliente[id].total = 0;
				cliente[id].id = -1;
			}
			else if(opcao == 2 && cliente[id].id != -1){
				cliente[id].id = -1;
				finalizar();
			}
		}
	}
	return resp;
}

//PRINCIPAL
int main(){
	setlocale(LC_ALL, "Portuguese");
	int continua = True;
	if(inicializar() && Finicializar()){
		printf("\n\nInicializado\n\n");
	}else{
		printf("\n\nNão inicializado\n\n");
	}
	int opcaoc, opcaof;
	char menu;
	do{
		printf("\nEscolha o Tipo de Menu:");
		printf("\n[C] - Cliente");
		printf("\n[F] - Fornecedor");
		printf("\n[S] - Sair");
		printf("\nEscreva Aqui: ");
		scanf("%c", &menu);
		switch(menu){
			case 'c':
			case 'C': system("CLS");
				 	  do{
					 	   	printf("\n**********Menu de Cliente**********");
   							printf("\n[0] - Voltar para o Menu Inicial");
   							printf("\n[1] - Finalizar Compra");
					 	  	printf("\n[2] - Adicionar nova Compra ao Carrinho");
							printf("\n[3] - Alterar Compra");
							printf("\n[4] - Remover Item do Carrinho");
							printf("\n[5] - Listar compras");
							printf("\nEscolha sua opção: ");
							scanf("%d", &opcaoc);
							switch(opcaoc){
						  		case 0: system("CLS");
								  	 	continua = False;
					  	  			 	printf("\nVoltando para o Menu\n");
					  	  			 	break;
					  	  			 	
								case 1: system("CLS");
									 	printf("\n**************FINALIZAR COMPRA**********************");
									 	if(finalizar()){
											printf("\nCompra finalizada\n\n");
											continua = False;
										}else{
											printf("\n[ERRO] ao finalizar compra\n\n");
										}
									 	break;
										
								case 2: system("CLS");
									 	printf("\n**********ADICIONAR NOVA COMPRA********");
						  			 	if(incluir()){
										   	printf("\nItem Adicionado ao Carrinho\n\n");
										   	continua = True;
										}else{
											printf("\n[ERRO] ao Adicionar Item\n\n");
											continua = True;
					 			  		}
							 	  		break;
														 	
								case 3: system("CLS");
									 	printf("\n**************ALTERAÇÃO DE COMPRA*********************");
										if(alteracao()){
											printf("\nAlteração Concluída\n\n");
											continua = True;
										}else{
											printf("\n[ERRO] na Alteração\n\n");
											continua = True;
										}
										break;
														 	
								case 4: system("CLS");
									 	printf("\n**************REMOVER ITEM DO CARRINHO**********************");
										if(excluir()){
											printf("\nItem Removido\n\n");
											continua = True;
										}else{
											printf("\n[ERRO] na Remoção\n\n");
											continua = True;
										}
										break;
														 	
								case 5: system("CLS");
									 	printf("\n**************Listar COMPRAS**********************");
										if(listar()){
											printf("\nListado\n\n");
											continua = True;
										}else{
											printf("\n[ERRO] ao listar Compras\n\n");
											continua = True;
										}
										break;
														 	
								default: system("CLS");
		 								 printf("\n[ERRO] Tente Novamente!\n\n");
		 								 continua = True;
										 break;
											 				
							}
							fflush(stdin);
		 			  } while(continua);
		 			  break;
		 			  
  			case 'f':
			case 'F': system("CLS");
				 	  do{
					 	   	printf("\n**********Menu de Fornecedor**********");
   							printf("\n[0] - Voltar para o Menu Inicial");
					 	  	printf("\n[1] - Adicionar novo Produto no Mercado");
							printf("\n[2] - Alterar Produto");
							printf("\n[3] - Remover Produto do Mercado");
							printf("\n[4] - Listar Produtos do Mercado");
							printf("\n[5] - Ver clientes cadastrados");
							printf("\nEscolha sua opção: ");
							scanf("%d", &opcaof);
							switch(opcaof){
						  		case 0: system("CLS");
								  	 	continua = False;
					  	  			 	printf("\nVoltando para o Menu\n");
					  	  			 	break;
					  	  			 	
								case 1: system("CLS");
									 	printf("\n**********ADICIONAR NOVO PRODUTO********");
						  			 	if(Fincluir()){
										   	printf("\nProduto Adicionado\n\n");
										   	continua = True;
										}else{
											printf("\n[ERRO] ao Adicionar Item\n\n");
											continua = True;
					 			  		}
							 	  		break;
														 	
								case 2: system("CLS");
									 	printf("\n**************ALTERAÇÃO DE PRODUTO*********************");
										if(Falteracao()){
											printf("\nAlteração Concluída\n\n");
											continua = True;
										}else{
											printf("\n[ERRO] na Alteração\n\n");
											continua = True;
										}
										break;
														 	
								case 3: system("CLS");
									 	printf("\n**************REMOVER PRODUTO DO MERCADO**********************");
										if(Fexcluir()){
											printf("\nItem Removido\n\n");
											continua = True;
										}else{
											printf("\n[ERRO] na Remoção\n\n");
											continua = True;
										}
										break;
														 	
								case 4: system("CLS");
									 	printf("\n**************LISTAR PRODUTOS ADICIONADOS**********************");
										if(Flistar()){
											printf("\nProdutos Listados\n\n");
											continua = True;
										}else{
											printf("\n[ERRO] ao Listar Produtos\n\n");
											continua = True;
										}
										break;
								case 5: system("CLS");
									 	printf("\n**************CLIENTES CADASTRADOS**********************");
										if(dados()){
											printf("\nListados\n\n");
											continua = True;
										}else{
											printf("\n[ERRO] ao Listar clientes cadastrados\n\n");
											continua = True;
										}
									 	break;
														 	
								default: system("CLS");
										 printf("\n[ERRO] Tente Novamente!\n\n");
										 continua = True;
										 break;
											 				
							}
							fflush(stdin);
		 			  } while(continua);
		 			  break;
				 	  
	  		case 's':
  			case 'S': printf("\nSaindo...");
					  return 0;//tava dando problema sem esse return
			  	 	  break;
			  	 	  
	 	  	default: printf("\n[ERRO] Tente Novamente!");
				  	 break;
		}
		fflush(stdin);
	} while(menu != 's'|| menu != 'S');
	return 0;
}
