#if ! defined( USUARIO_ )
#define USUARIO_

/***************************************************************************
*
*  $MCD Módulo de definição: USU  Usuario da rede de relacionamentos
*
*  Arquivo gerado:              USUARIO.h
*  Letras identificadoras:      USU
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\USUARIO.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: AP,BF,BG
*
*  $HA Histórico de evolução:
*   Versão  Autor    Data       Observações
*     6      ap   02/dez/2017   Criação das funções ObterListaMsgs e ObterIdUsuario.
*     5      bf   20/nov/2017   mudancas para tirar consultas indevidas ao usuario
*	  4      ap   04/nov/2017   Criação da função ExibeMsgEntreUsuarios
*	  3      ap   02/nov/2017   Criação da função EnviaMsgParaUsuario
*     2		 bg   28/out/2017	continuação desenvolvimento
*     1      bf   26/out/2017   início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa usuario de uma rede de relacionamentos.
*     Podem existir n usuarios em operação simultaneamente.
*     Usuarios possuem Id, nome, data de nascimento,email e cidade de moradia..*
***************************************************************************/

#if defined(USUARIO_OWN )
   #define USUARIO_EXT
#else
   #define USUARIO_EXT extern
#endif

#include "LISTA.h"
#include "MENSAGEM.h"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

typedef struct USU_tagUsuario * USU_tppUsuario ;


/***********************************************************************
*
*  $TC Tipo de dados: USU Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do usuario
*
***********************************************************************/

   typedef enum {

         USU_CondRetOK ,
               /* Concluiu corretamente */

         USU_CondRetUsuarioNExiste ,
               /* Não encontrou o usuario procurado */

         USU_CondRetFaltouMemoria,
               /* Faltou memória ao tentar criar um elemento de lista */

		USU_CondRetInfoExcedeuTamanho,
				 /*Quando uma das infos que compõem o usuário não for valida pois excedeu o tamanho */
				
		USU_CondRetInfoInvalida,
				 /*Quando uma das infos que compõem o usuário não for valida por causa de um dos requisitos */
		
		USU_CondRetOpcaoNExiste
			    /*Quando a opcao escolhida não existe */

   } USU_tpCondRet ;


/***********************************************************************
*
*  $FC Função: USU  &Criar usuario
*
*  $ED Descrição da função
*     Cria um usuário.
*
*  $EP Parâmetros
*     id    - 	Identificador do usuário.
*    nome   -   Nome do usuário.
*   email   -	Email do usuário.
*   dtnasc  -	Data de nascimento do usuário.  
*   cidade  -	Cidade de moradia do usuário.

*  $FV Valor retornado
*     pUsuario - Se executou corretamente retorna o ponteiro para o usuario.
*     NULL     - Caso ocorra algum erro na criação do usuário.
*
***********************************************************************/

USU_tppUsuario USU_CriarUsuario(char id[],char nome[],char email[],char dtnasc[],char cidade[]);

/***********************************************************************
*
*  $FC Função: USU  &Excluir Usuario
*
*  $ED Descrição da função
*	  Exclui o ponteiro para o usuário fornecido.
*
*  $EP Parâmetros
*     pUsuario  -	Ponteiro para um usuário.
*
*  $FV Valor retornado
*	  NULL  - Usuário excluído com sucesso.
*
***********************************************************************/

void * USU_ExcluirUsuario(void * Usuario);

/***********************************************************************
*
*  $FC Função: USU  &Alterar Usuario
*
*  $ED Descrição da função
*	  Altera o valor de um dado do usuário de acordo com a opção fornecida
*	  e o novo valor fornecido no parâmetro.
*
*  $EP Parâmetros
*     pUsuario  -	Ponteiro para um usuário.
*	  opcao     -	Número correspondente a opção de alteração desejada.
*					1 - Nome
*					2 - Email
*					3 - Data de Nascimento
*					4 - Cidade de moradia
*     mudanca   -  ponteiro para a string que contém o novo valor.
*
*  $FV Valor retornado
*	 USU_CondRetOK             - Alteração realizada com sucesso.
*	 USU_CondRetUsuarioNExiste - Usuário fornecido não existe.
*
***********************************************************************/

USU_tpCondRet USU_AlterarUsuario(void * pUsuario,int opcao,char mudanca[]);

/***********************************************************************
*
*  $FC Função: USU  &Preenche Dados Usuário
*
*  $ED Descrição da função
*	  Atualiza o conteúdo dos ponteiros fornecidos com os dados de um usuário.
*
*  $EP Parâmetros
*    pUsuario  -	Ponteiro para um usuário.
*    nome      -    Nome do usuário.
*    email     -	Email do usuário.
*    dtnasc    -	Data de nascimento do usuário.  
*    cidade    - 	Cidade de moradia do usuário.
*
*  $FV Valor retornado
*	 USU_CondRetOK             - As variáveis fornecidas foram preenchidos com sucesso.
*	 USU_CondRetUsuarioNExiste - Usuário fornecido não existe.
*
***********************************************************************/

USU_tpCondRet USU_PreencheDadosUsuario(void * pUsuario,char nome[],char email[],char dtnasc[],char cidade[]);

/***********************************************************************
*
*  $FC Função: USU  &Obter Lista Msgs
*
*  $ED Descrição da função
*	  Retorna a lista de mensagens de um usuário
*	  de acordo com o tipo recebido como parâmetro.
*	  
*  $EP Parâmetros
*     pUsuario		-	Ponteiro para um usuário.
*	  tipo			-   Corresponde ao tipo da lista de mensagens
*						1 - Lista de mensagens Enviadas
*						2 - Lista de mensagens Recebidas
*
*  $FV Valor retornado
*		Ponteiro para a lista de mensagens.
*	    NULL - Tipo inválido ou pUsuario não existe.
*
***********************************************************************/

void * USU_ObterListaMsgs(void * pUsuario, int tipo);

/***********************************************************************
*
*  $FC Função: USU  &Obter Id Usuário
*
*  $ED Descrição da função
*	  Preenche a variável recebida como parâmetro com o id do usuário fornecido.
*	  
*  $EP Parâmetros
*     pUsuario		-	Ponteiro para um usuário.
*     id            -   Variável que será preenchida com o id do usuário.
*
*  $FV Valor retornado
*	  USU_CondRetOK				- Atualizou a variável id com sucesso.
*	  USU_CondRetUsuarioNExiste - O usuário não existe.
*
***********************************************************************/

USU_tpCondRet USU_ObterIdUsuario(void * pUsuario, char *id);

/***********************************************************************
*
*  $FC Função: USU  &Checar String
*
*  $ED Descrição da função
*	  Faz a validação da string fornecida.
*	  Para ser válido a string fornecida só pode conter letras
*	  A função converte a string automaticamente para maiúsculo.
*
*  $EP Parâmetros
*     Str  - Ponteiro para a string de um nome de usuário ou cidade a ser validada.
*
*  $FV Valor retornado
*	  USU_CondRetOK  -  A string foi verificada com sucesso.
*
***********************************************************************/

USU_tpCondRet USU_ChecaString(char *Str);

/***********************************************************************
*
*  $FC Função: USU  &Checar Email
*
*  $ED Descrição da função
*	  Faz a validação da string de um email fornecida.
*
*  $EP Parâmetros
*     Str  - Ponteiro para a string de um email a ser validada.
*
*  $FV Valor retornado
*	  USU_CondRetOK			  -  A string do email foi verificada com sucesso.
*	  USU_CondRetInfoInvalida - String do email é inválida.
*
***********************************************************************/

USU_tpCondRet USU_ChecaEmail(char *Str);

/***********************************************************************
*
*  $FC Função: USU  &Checar DtNasc
*
*  $ED Descrição da função
*	  Faz a validação da string fornecida.
*	  Para ser válido a string fornecida deve seguir o formato dd/mm/aaaa
*
*  $EP Parâmetros
*     Str  - Ponteiro para a string de um data de nascimento a ser validada.
*
*  $FV Valor retornado
*	  USU_CondRetOK			  -  A string foi verificada com sucesso.
*	  USU_CondRetInfoInvalida -  Formato da data de nascimento é inválida.
*
***********************************************************************/

USU_tpCondRet USU_ChecaDtNasc(char *Str);

/***********************************************************************/

#undef USUARIO_EXT

/********** Fim do módulo de definição: USU Usuário da rede de relacionamentos **********/

#else
#endif