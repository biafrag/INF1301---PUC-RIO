/***************************************************************************
*  $MCI Módulo de implementação: RED  Rede
*
*  Arquivo gerado:              REDE.c
*  Letras identificadoras:      RED
*  
*
*  Projeto: T4 INF 1301 2017.2
*  Autores: ap - André Pessanha
*           bg - Bianca Gomes
*           bf - Bianca Fragoso
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data       Observações
*     8        ap   02/dez/2017 Implementação de funções relacionadas a opção 6 e 8 do menu.
*     7        bf   20/nov/2017 mudancas para fazer algumas consultas ao usuario
*     6        ap   04/nov/2017 Implementação da funcionalidade da opção 8 e 9 do menu.
*	  5        ap   02/nov/2017 Implementação da funcionalidade da opção 6 do menu.
*	  4        ap   30/out/2017 Implementação da funcionalidade das opções 2 e 5 do menu.
*	  3        ap   28/out/2017 Implementação da funcionalidade das opções 1; 3; 4 e 7 do menu.
*     2        bf   28/out/2017 continuação com algumas alterações para uso do módulo usuário 
*     1        ap   26/out/2017 início desenvolvimento
*		  
*
***************************************************************************/

#include   <stdio.h>
#include   <stdlib.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define REDE_OWN
#include "GRAFO.h"
#include "USUARIO.h"
#include "MENSAGEM.h"
#include "REDE.h"
#undef RED_OWN


/***** Protótipos das funções encapuladas no módulo *****/

static int exibeMenuPrincipal();
static int exibeMenuAlterar();
static int exibeMenuMensagem();
static char * lerID();
static char * validarNovoID(GRA_tppGrafo pGrafo, char *id);
static void exibeLogo();
static void converteIDMaiusculo (char *id);
static void ConsultaUsuarioInfo(char *nome,char *email,char *dtnasc, char *cidade);
static void ConsultaAlteracao(char *mudanca,int opcao);
static void ExibeAmigosUsuario(void * pArestas, char *id);
static void ExibeUsuario(char *id, char *nome,char *email,char *dtnasc, char *cidade);
static void ObterMensagem(char *Mensagem);
static void exibeMensagensEntreUsuarios(char *id, char *id2, void *msgsEnviadas1, void *msgsEnviadas2); 

/*****  Código das funções encapsuladas no módulo  *****/

/***************************************************************************
*
*  Função: RED  -Exibe Menu Principal
*
***************************************************************************/

static int exibeMenuPrincipal(){
	int op, testRet;

	do{
		puts("\n1. Incluir Usuario\n2. Incluir Relacionamento\n3. Alterar Usuario\n4. Remover Usuario");
		puts("5. Remover Relacionamento\n6. Enviar Mensagem\n7. Exibir Dados Usuario");
		puts("8. Exibir Mensagens\n9. Exibir Relacionamentos\n10. Sair");
		testRet = scanf("%d", &op);

		if((op < 1 || op > 10) || testRet != 1){
			exibeLogo();
			fflush(stdin);  // Caso seja digitado string
			puts("\n\nOpcao Invalida! Digite novamente: \n");
		}
	}while(op < 1 || op > 10);

	return op;

   } /* Fim função: RED -Exibe Menu Principal */

/***************************************************************************
*
*  Função: RED  -Exibe Menu Alterar
*
***************************************************************************/

static int exibeMenuAlterar(){
	int tipo, testRet;
	
	puts("\nQual opcao deseja alterar?");

	do{
		puts("\n1. Nome\n2. Email\n3. Data de Nascimento \n4. Cidade de moradia");
		puts("5. Cancelar alteracao\n\n");

		testRet = scanf("%d", &tipo);
		if((tipo < 1 || tipo > 5) || testRet != 1){
			exibeLogo();
			fflush(stdin); // Caso seja digitado string
			puts("\n\nOpcao Invalida! Digite novamente: \n");
		}
	}while(tipo < 1 || tipo > 5);

	return tipo;

   } /* Fim função: RED -Exibe Menu Alterar */


/***************************************************************************
*
*  Função: RED  -Exibe Menu Mensagem
*
***************************************************************************/

static int exibeMenuMensagem(){
	int tipo, testRet;
	
	puts("\nA mensagem sera enviada: ");

	do{
		puts("\n1. Para um\n2. Para todos\n3. Cancelar mensagem\n\n");

		testRet = scanf("%d", &tipo);
		if((tipo < 1 || tipo > 3) || testRet != 1){
			exibeLogo();
			fflush(stdin); // Caso seja digitado string
			puts("\n\nOpcao Invalida! Digite novamente: \n");
		}
	}while(tipo < 1 || tipo > 3);

	return tipo;

   } /* Fim função: RED -Exibe Menu Mensagem */

/***************************************************************************
*
*  Função: RED  -Exibe Logotipo
*
***************************************************************************/

static void exibeLogo(){

	system("cls");
	puts(" +-------------------------------------------------------------------------------------+");
	puts(" |======================= |F| |A| |N| |C| |Y| |B| |O| |O| |K| =========================|");
	puts(" +-------------------------------------------------------------------------------------+");

   } /* Fim função: RED -Exibe Logotipo */

/***************************************************************************
*
*  Função: RED  -Converte ID Maiúsculo
*
***************************************************************************/

static void converteIDMaiusculo (char *id){
	int i, tam;

	tam = strlen(id);

	for(i=0;i<tam;i++){   // Transforma em maiúsculo
		if(id[i] >= 'a' && id[i] <= 'z')
			id[i] = id[i] - 32;  
	}

} /* Fim função: RED -Converte ID Maiúsculo */

/***************************************************************************
*
*  Função: RED  -Ler ID
*
***************************************************************************/

static char * lerID(){
	char *id;

	id = (char*) malloc (51);
	if(id == NULL) return NULL;

	puts("\n\nDigite seu ID: (No Maximo 50 caracteres)\n");
	scanf(" %50s", id);
	converteIDMaiusculo(id);

	return id;
} /* Fim função: RED -Ler ID */

/***************************************************************************
*
*  Função: RED  -Valida ID
*
***************************************************************************/

static char * validarNovoID(GRA_tppGrafo pGrafo, char *id){
	GRA_tpCondRet cond;

	cond = GRA_VerificaVerticeExiste(pGrafo, id);
	
	while(cond == GRA_CondRetOK){
		if(cond == GRA_CondRetOK){
			puts("\nID ja existente! Digite novamente: \n");
		}
		scanf(" %50s", id);
		converteIDMaiusculo(id);
		cond = GRA_VerificaVerticeExiste(pGrafo, id);
	}

	return id;

   } /* Fim função: RED -Validar novo ID */

/***************************************************************************
*
*  Função: RED  -Consulta Usuario sobre Informações
*
***************************************************************************/

static void ConsultaUsuarioInfo(char *nome,char *email,char *dtnasc,char *cidade)
{
	USU_tpCondRet  cond;
	printf("\nQual o nome ? (No Maximo 50 caracteres)\n");
	scanf(" %50[^\n]s",nome);
	
	cond=USU_ChecaString(nome);
	while(cond != USU_CondRetOK) {
		printf("\nO nome deve conter somente letras! Digite novamente:  \n");
		scanf(" %50[^\n]s",nome);

		cond=USU_ChecaString(nome);
	}
	
	printf("Qual o email ? (No Maximo 50 caracteres)\n");
	scanf(" %300s",email);
	
	cond=USU_ChecaEmail(email);
	while(cond != USU_CondRetOK) 
	{
		printf("Email invalido. Digite novamente:\n");
		scanf(" %300s",email);

		cond=USU_ChecaEmail(email);
	}
	printf("Qual a data de Nascimento ? (DD/MM/AAAA)\n");
	scanf(" %s",dtnasc);

	cond=USU_ChecaDtNasc(dtnasc);
	
	while(cond != USU_CondRetOK) 
	{
		printf("Data de Nascimento invalida. Digite novamente:\n");
		scanf(" %s",dtnasc);

		cond=USU_ChecaDtNasc(dtnasc);
	} /* while */ 

	printf("Qual a cidade de moradia ? (No Maximo 50 caracteres)\n");
	scanf(" %50[^\n]s",cidade);

	cond=USU_ChecaString(cidade);

	while(cond != USU_CondRetOK) {
		printf("\nA cidade de moradia deve conter somente letras,sem acentos nem outros tipos de caracteres. Digite novamente: \n");
		scanf(" %50[^\n]s",cidade);

		cond=USU_ChecaString(cidade);
	}

}/* Fim função: RED -Consulta Usuario sobre Informações */

/***************************************************************************
*
*  Função: RED  -Consulta Alteracoes que usuario quer fazer
*
***************************************************************************/

static void ConsultaAlteracao(char *mudanca,int opcao)
{
	USU_tpCondRet cond;
	switch (opcao)
	{
		case 1:
			printf("\nQual o nome ? (No Maximo 50 caracteres)\n");
			scanf(" %50s",mudanca);
			cond=USU_ChecaString(mudanca);

			while(cond != USU_CondRetOK || strcmp(mudanca,"TODOS") == 0 ) {
				printf("\nO nome deve conter somente letras e nao pode ser 'Todos'. Digite novamente: \n");
				scanf(" %50[^\n]s",mudanca);

				cond=USU_ChecaString(mudanca);
			}
			break;

		case 2:
			printf("\nQual o email ? (No Maximo 50 caracteres)\n");
			scanf(" %300s", mudanca);
			cond=USU_ChecaEmail(mudanca);
			while(cond != USU_CondRetOK) 
			{
				printf("\nEmail invalido. Digite novamente:\n");
				scanf(" %300s",mudanca);
				cond=USU_ChecaEmail(mudanca);
			}
			break;

		case 3:
			printf("\nQual a data de nascimento ? (DD/MM/AAAA)\n");
			scanf(" %10s",mudanca);
			cond=USU_ChecaDtNasc(mudanca);
			while(cond != USU_CondRetOK) 
			{
				printf("Data de Nascimento invalida. Digite novamente:\n");
				scanf(" %s",mudanca);

				cond=USU_ChecaDtNasc(mudanca);
			} /* while */ 
			break;

	   case 4:
			printf("\nQual a cidade de moradia ? (No Maximo 50 caracteres)\n");
			scanf(" %50s",mudanca);
			cond=USU_ChecaString(mudanca);		
			while(cond != USU_CondRetOK) {
				printf("\nA cidade de moradia deve conter somente letras. Digite novamente: \n");
				scanf(" %50[^\n]s",mudanca);

				cond=USU_ChecaString(mudanca);
			}
			break;
	   default:
		   printf("Opcao invalida!\n\n");
	
	}
} /* Fim função: RED -Consulta Alteracoes que usuario quer fazer */

/***************************************************************************
*
*  Função: RED  -Exibe Amigos de Usuário
*  ****/

static void ExibeAmigosUsuario(void * pArestas, char *id){
	LIS_tppLista pAmigos;
	LIS_tpCondRet cond;
	char *idAmigo;
	int temAmigo;
	
	pAmigos = (LIS_tppLista)pArestas;
	LIS_IrInicioLista(pAmigos);
	temAmigo = 0;
	do{
		idAmigo = (char*) LIS_ObterValor (pAmigos);
		if(temAmigo == 0){
			temAmigo = 1;
			printf("\nAmigos do usuario %s:\n\n", id);
			puts("\n***************************************************************************************\n");
		}
		printf("%s ; ", idAmigo);
		cond = LIS_AvancarElementoCorrente(pAmigos, 1);
	}while(cond != LIS_CondRetFimLista);

	puts("\n\n***************************************************************************************\n");

	
}  /* Fim função: RED  -Exibe Amigos de Usuário  */

/***************************************************************************
*
*  Função: RED  -Exibir Usuário
*  ****/
static void ExibeUsuario(char *id, char *nome,char *email,char *dtnasc, char *cidade)
{
	printf("------- Usuario: %s -----------\n\n",id);
	printf("Nome: %s \n",nome);
	printf("Email: %s \n",email);
	printf("Data de Nascimento: %s \n",dtnasc);
	printf("Cidade: %s \n",cidade);
	printf("-----------------------------------------------\n");
}
/* Fim função: RED  -Exibir Usuário  */

/***************************************************************************
*
*  Função: RED  -Obter Mensagem
*  ****/

static void ObterMensagem(char *Mensagem)
{
	printf("\nQual a mensagem desejada ? (No maximo 300 caracteres) \n");
	scanf(" %301[^\n]s",Mensagem);

}
/* Fim função: RED  -Obter Mensagem */

/***************************************************************************
*
*  Função: RED  -Exibe Mensagens Entre Usuários
*  ****/

static void exibeMsgsEntreUsuarios(char *id, char *id2, void *msgsEnviadas1, void *msgsEnviadas2){
	int totalMsg, i, temMsg;
	MEN_tpCondRet cond;
	char *texto, *idDestino;

	texto = (char*) malloc (301);
	idDestino = (char*)malloc(51);

	MEN_ContaMensagens(msgsEnviadas1, &totalMsg);
	if(totalMsg == 0){
		printf("\n%s nao possui mensagens enviadas no registro!\n\n", id);
	}
	else{
		temMsg = 0;
		MEN_IrInicioRegistroMsgs(msgsEnviadas1);
		for(i=0;i<totalMsg; i++){
			cond = MEN_ObterMensagem(msgsEnviadas1, texto, idDestino);
			if(!(strcmp(idDestino, id2))){
				if(temMsg == 0){
					printf("\nMensagens enviadas de %s para %s\n\n", id, id2);
					temMsg = 1;
				}
				puts("\n***************************************************************************************\n");
				puts(texto);
				puts("\n***************************************************************************************\n");
			}
			MEN_AvancarRegistroMsgs(msgsEnviadas1);
		}
		if(temMsg == 0){
			printf("\n%s Nao possui mensagens enviadas para %s no Registro!\n\n", id, id2);
		}
	}
	 
	MEN_ContaMensagens(msgsEnviadas2, &totalMsg);

	if(totalMsg == 0){
		printf("\n%s nao possui mensagens recebidas no registro!\n\n", id);
	}
	else{
		temMsg = 0;
		MEN_IrInicioRegistroMsgs(msgsEnviadas2);
		for(i=0;i<totalMsg; i++){
			cond = MEN_ObterMensagem(msgsEnviadas2, texto, idDestino);
			if(!(strcmp(idDestino, id))){
				if(temMsg == 0){
					printf("\nMensagens enviadas de %s para %s\n\n",  id2, id);
					temMsg = 1;
				}
				puts("\n***************************************************************************************\n");
				puts(texto);
				puts("\n***************************************************************************************\n");
			}
			MEN_AvancarRegistroMsgs(msgsEnviadas2);
		}
		if(temMsg == 0){
			printf("\nNao ha mensagens enviadas de %s para %s\n\n", id2, id);
		}
	}

	free(texto);
	free(idDestino);
}


int main(void){
	int op, i, tipo, qtdUser, falha;
	GRA_tppGrafo pGrafo;
	GRA_tpCondRet cond;
	MEN_tpCondRet condMsg;
	USU_tpCondRet condUser;
	void * pUsuario, *pUsuario2, *msgs1, *msgs2;
	char * id, *id2;
	void  *pMensagem, *pArestas;
	char nome[51],email[51],cidade[51],dtnasc[11];
	char mudanca[51];
	char Mensagem[301];

	pGrafo = GRA_CriarGrafo(NULL);
	id = id2 = NULL;
	qtdUser = 0;

	exibeLogo();
	op = exibeMenuPrincipal();

	do{
	
		if(qtdUser == 0 && op != 1){
			exibeLogo();
			puts("\n\nNao ha usuarios cadastrados!");
			puts("Sugestao: Utilize a opcao (1) para incluir um novo usuario na rede.\n\n");
		}
		else if(op == 1){  // Incluir Usuário
			exibeLogo();
			id = lerID();
			id = validarNovoID(pGrafo, id);
			ConsultaUsuarioInfo(nome,email,dtnasc,cidade);
			pUsuario = USU_CriarUsuario(id,nome,email,dtnasc,cidade);  //Cria novo usuário
			if(pUsuario != NULL){
				cond = GRA_InserirVertice(pGrafo, pUsuario, id);  //Inclui usuário na rede
				if(cond == GRA_CondRetOK){
					exibeLogo();
					puts("\n\nUsuario incluso com sucesso!\n");
					qtdUser++;
				}
				else{
					exibeLogo();
					puts("\nFalha na inclusao!\n");
				}
			}
		}
		else if(op == 2){  //Incluir relacionamento
			exibeLogo();
			id = lerID();
			cond = GRA_VerificaVerticeExiste(pGrafo, id);
			if(cond != GRA_CondRetOK){
				exibeLogo();
				puts("\n\nFalha na inclusao! Usuario nao existe\n");
			}
			else{
				pUsuario = GRA_ObterValorCorrente(pGrafo);
				printf("\n\nQual o ID do usuario que deseja adicionar? ");
				id2 = lerID();
				if(strcmp(id, id2) == 0){
					exibeLogo();
					puts("\n\nFalha na inclusao! IDs Iguais!\n");
				}
				else{
					cond = GRA_VerificaVerticeExiste(pGrafo, id2);
					if(cond != GRA_CondRetOK){
						exibeLogo();
						puts("\n\nFalha na inclusao! Usuario nao existe\n");
					}
					else{
						cond = GRA_InserirArestaCorrente(pGrafo, id);  // aqui
						if(cond == GRA_CondRetOK){
							exibeLogo();
							puts("\n\nRelacionamento incluso com sucesso!\n");
						}
						else if(cond == GRA_CondRetArestaExiste){
							exibeLogo();
							puts("\n\nInclusao cancelada! Relacionamento ja existe\n");
						}
					}
				}
			}
		}
		else if(op == 3){  // Alterar usuário
			exibeLogo();
			id = lerID();
			cond = GRA_VerificaVerticeExiste(pGrafo, id);
			if(cond != GRA_CondRetOK){
				exibeLogo();
				puts("\n\nFalha na alteracao! Usuario nao existe.\n");
			}
			else{
				tipo = exibeMenuAlterar();
				if(tipo != 5){
					pUsuario = GRA_ObterValorCorrente(pGrafo);
					ConsultaAlteracao(mudanca,tipo);
					printf("Mudanca: %s\n",mudanca);
					USU_AlterarUsuario(pUsuario, tipo,mudanca);
					USU_AlterarUsuario(pUsuario, tipo,mudanca);
					exibeLogo();
					puts("\n\nAlteracao concluida com sucesso!\n");	
				}
				else{
					exibeLogo();
					puts("\nAlteracao cancelada.\n\n");
				}
			}
		}
		else if(op == 4){   // Remover usuário
			exibeLogo();
			id = lerID();
			cond = GRA_VerificaVerticeExiste(pGrafo, id);
			if(cond != GRA_CondRetOK){
				exibeLogo();
				puts("\n\nFalha na remocao! Usuario nao existe\n");
			}
			else{
				exibeLogo();
				pUsuario = GRA_ObterValorCorrente(pGrafo);
				cond = GRA_ExcluiVerticeCorrente(pGrafo);
				pUsuario = USU_ExcluirUsuario(pUsuario);
				if(cond == GRA_CondRetOK){
					exibeLogo();
					puts("\n\nRemocao concluida com sucesso!\n");
					qtdUser--;
				}
				else{
					exibeLogo();
					puts("\n\nFalha na remocao!\n");
				}
			}
		}
		else if(op == 5){ //Remover relacionamento
			exibeLogo();
			id = lerID();
			cond = GRA_VerificaVerticeExiste(pGrafo, id);
			if(cond != GRA_CondRetOK){
				exibeLogo();
				puts("\n\nFalha na remocao! Usuario nao existe\n");
			}
			else{
				pUsuario = GRA_ObterValorCorrente(pGrafo);
				printf("\n\nQual o ID do usuario que deseja desfazer amizade ? ");
				id2 = lerID();
				if(strcmp(id, id2) == 0){
					exibeLogo();
					puts("\n\nFalha na remocao! IDs Iguais!\n");
				}
				else{
					cond = GRA_VerificaVerticeExiste(pGrafo, id2);
					if(cond != GRA_CondRetOK){
						exibeLogo();
						puts("\n\nFalha na remocao! Usuario nao existe\n");
					}
					else{
						pUsuario2 = GRA_ObterValorCorrente(pGrafo);
						cond = GRA_ExcluirAresta(pGrafo, id, id2);  // aqui puser por id
						exibeLogo();
						if(cond == GRA_CondRetOK){
							exibeLogo();
							puts("\n\nRemocao concluida com sucesso!\n");
						}
						else if(cond == GRA_CondRetArestaNExiste){
							exibeLogo();
							puts("\n\nFalha na remocao! O relacionamento nao existe\n");
						}
					}
				}
			}
		}
		else if(op == 6){ //Enviar Mensagem
			falha = 0;  
			exibeLogo();
			puts("\n\nInforme o ID do remetente: ");
			id = lerID();
			cond = GRA_VerificaVerticeExiste(pGrafo, id);
			if(cond != GRA_CondRetOK){
				exibeLogo();
				puts("\n\nFalha na criacao da mensagem! Usuario Remetente nao existe\n");
			}
			else{
				pUsuario = GRA_ObterValorCorrente(pGrafo);
				tipo = exibeMenuMensagem();

				if(tipo == 3){  //Cancela e Volta pro menu
					exibeLogo();
					puts("\n\nMensagem cancelada!\n");
				}
				else{
					if(tipo == 1){  // Para um (Lê ID Destino)
						id2 = lerID();
						if(strcmp(id, id2) == 0){
							exibeLogo();
							puts("\n\nFalha na criacao da mensagem! IDs Remetente e Destino sao iguais!\n");
							falha = 1;
						}
						else{
							cond = GRA_VerificaVerticeExiste(pGrafo, id2);
							if(cond != GRA_CondRetOK){
								exibeLogo();
								puts("\n\nFalha na criacao da mensagem! Usuario Destino nao existe\n");
								falha = 1;
							}
							else{
								pUsuario2 = GRA_ObterValorCorrente(pGrafo);
							}
						}
					}
					
					if(tipo == 1 && !falha){  // Enviar para um
						ObterMensagem(Mensagem);
						pMensagem = MEN_CriarMensagem(id, id2,Mensagem);
						msgs1 = USU_ObterListaMsgs(pUsuario, 1);     // Msgs Enviadas
						msgs2 = USU_ObterListaMsgs(pUsuario2, 2);    // Msgs Recebidas
						condMsg =  MEN_EnviarMensagem(pMensagem, msgs1, msgs2);
						if(condMsg == MEN_CondRetOK){
							exibeLogo();
							puts("\n\nMensagem Enviada com sucesso!\n");
						}
						else{
							exibeLogo();
							puts("\n\nFalha no envio da mensagem!\n");
						}
					}
					else if(tipo == 2 && !falha){  // Enviar para TODOS
						id2 = (char*) malloc (51);
						ObterMensagem(Mensagem);
						GRA_IrInicio(pGrafo);                            // aqui
						pUsuario2 = GRA_ObterValorCorrente(pGrafo);
						USU_ObterIdUsuario (pUsuario2, id2);
						msgs1 = USU_ObterListaMsgs(pUsuario, 1); 
						for (i = 0; i < qtdUser ; i++){
							if(strcmp(id, id2) != 0){
								pMensagem = MEN_CriarMensagem(id, id2,Mensagem);
								msgs2 = USU_ObterListaMsgs(pUsuario2, 2);
								condMsg =  MEN_EnviarMensagem(pMensagem, msgs1, msgs2);
								if(condMsg != MEN_CondRetOK) break;	
							}
							cond = GRA_AvancarVerticeCorrente(pGrafo);
							if(cond == GRA_CondRetFimGrafo) break;	
							pUsuario2 = GRA_ObterValorCorrente(pGrafo);
							USU_ObterIdUsuario (pUsuario2, id2);
						}
						if(condMsg != MEN_CondRetOK){
							exibeLogo();
							puts("\n\nFalha! Algumas mensagens podem nao ter sido enviadas");
							puts("Sugestao: Utilize a opcao (6) para enviar novamente.\n");
						}
						else{
							exibeLogo();
							puts("\n\nMensagens Enviadas com sucesso!\n");
						}
					}
				}
			}
		}
		else if(op == 7){ // Exibir dados usuário
			exibeLogo();
			id = lerID();
			cond = GRA_VerificaVerticeExiste(pGrafo, id);
			if(cond != GRA_CondRetOK){
				exibeLogo();
				puts("\n\nUsuario nao existe!\n");
			}
			else{
				pUsuario = GRA_ObterValorCorrente(pGrafo);
				USU_PreencheDadosUsuario(pUsuario,nome,email,dtnasc,cidade);
				ExibeUsuario(id, nome, email,dtnasc, cidade);
			}
			
		}
		else if(op == 8){ // Exibir Mensagens
			exibeLogo();
			id = lerID();
			cond = GRA_VerificaVerticeExiste(pGrafo, id);
			if(cond != GRA_CondRetOK){
				exibeLogo();
				puts("\n\nFalha! Usuario nao existe\n");
			}
			else{
				pUsuario = GRA_ObterValorCorrente(pGrafo);
				printf("\n\nDeseja ver o registro de suas mensagens com qual usuario? ");
				id2 = lerID();
				if(strcmp(id, id2) == 0){
					exibeLogo();
					puts("\n\nFalha! IDs Iguais!\n");
				}
				else{
					cond = GRA_VerificaVerticeExiste(pGrafo, id2);
					if(cond != GRA_CondRetOK){
						exibeLogo();
						puts("\n\nFalha! Usuario nao existe\n");
					}
					else{
						pUsuario2 = GRA_ObterValorCorrente(pGrafo);
						exibeLogo();
						msgs1 = USU_ObterListaMsgs(pUsuario, 1);     // Msgs enviadas
						msgs2 = USU_ObterListaMsgs(pUsuario2, 1);    // Msgs enviadas
						exibeMsgsEntreUsuarios(id,id2, msgs1, msgs2);
					}
				}
			}
		}
		else if(op == 9){  //Exibe Amigos
			exibeLogo();
			id = lerID();
			cond = GRA_VerificaVerticeExiste(pGrafo, id);
			if(cond != GRA_CondRetOK){
				exibeLogo();
				puts("\n\nUsuario nao existe!\n");
			}
			else{
				pArestas = GRA_ObtemArestasVerticeCorrente(pGrafo);
				if(pArestas != NULL){
					exibeLogo();
					ExibeAmigosUsuario(pArestas, id);
				}
				else{
					exibeLogo();
					printf("\n\nO usuario %s nao possui amigos\n", id);
					puts("Sugestao: Utilize a opcao (2) para adicionar amigos\n");
				}
			}
		}

		if(op != 10){ 
			op = exibeMenuPrincipal();
		}

	}while(op != 10);

	exibeLogo();
	puts("\n\nEncerrando..."); 
	if(id) free(id);
	if(id2) free(id2);
    pGrafo = (GRA_tppGrafo) GRA_DestruirGrafo(pGrafo);
	return 0;
}


/********** Fim do módulo de implementação: RED Rede **********/