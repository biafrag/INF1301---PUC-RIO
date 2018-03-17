#if ! defined( USUARIO_ )
#define USUARIO_

/***************************************************************************
*
*  $MCD M�dulo de defini��o: USU  Usuario da rede de relacionamentos
*
*  Arquivo gerado:              USUARIO.h
*  Letras identificadoras:      USU
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\USUARIO.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: AP,BF,BG
*
*  $HA Hist�rico de evolu��o:
*   Vers�o  Autor    Data       Observa��es
*     6      ap   02/dez/2017   Cria��o das fun��es ObterListaMsgs e ObterIdUsuario.
*     5      bf   20/nov/2017   mudancas para tirar consultas indevidas ao usuario
*	  4      ap   04/nov/2017   Cria��o da fun��o ExibeMsgEntreUsuarios
*	  3      ap   02/nov/2017   Cria��o da fun��o EnviaMsgParaUsuario
*     2		 bg   28/out/2017	continua��o desenvolvimento
*     1      bf   26/out/2017   in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Implementa usuario de uma rede de relacionamentos.
*     Podem existir n usuarios em opera��o simultaneamente.
*     Usuarios possuem Id, nome, data de nascimento,email e cidade de moradia..*
***************************************************************************/

#if defined(USUARIO_OWN )
   #define USUARIO_EXT
#else
   #define USUARIO_EXT extern
#endif

#include "LISTA.h"
#include "MENSAGEM.h"

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma lista */

typedef struct USU_tagUsuario * USU_tppUsuario ;


/***********************************************************************
*
*  $TC Tipo de dados: USU Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es do usuario
*
***********************************************************************/

   typedef enum {

         USU_CondRetOK ,
               /* Concluiu corretamente */

         USU_CondRetUsuarioNExiste ,
               /* N�o encontrou o usuario procurado */

         USU_CondRetFaltouMemoria,
               /* Faltou mem�ria ao tentar criar um elemento de lista */

		USU_CondRetInfoExcedeuTamanho,
				 /*Quando uma das infos que comp�em o usu�rio n�o for valida pois excedeu o tamanho */
				
		USU_CondRetInfoInvalida,
				 /*Quando uma das infos que comp�em o usu�rio n�o for valida por causa de um dos requisitos */
		
		USU_CondRetOpcaoNExiste
			    /*Quando a opcao escolhida n�o existe */

   } USU_tpCondRet ;


/***********************************************************************
*
*  $FC Fun��o: USU  &Criar usuario
*
*  $ED Descri��o da fun��o
*     Cria um usu�rio.
*
*  $EP Par�metros
*     id    - 	Identificador do usu�rio.
*    nome   -   Nome do usu�rio.
*   email   -	Email do usu�rio.
*   dtnasc  -	Data de nascimento do usu�rio.  
*   cidade  -	Cidade de moradia do usu�rio.

*  $FV Valor retornado
*     pUsuario - Se executou corretamente retorna o ponteiro para o usuario.
*     NULL     - Caso ocorra algum erro na cria��o do usu�rio.
*
***********************************************************************/

USU_tppUsuario USU_CriarUsuario(char id[],char nome[],char email[],char dtnasc[],char cidade[]);

/***********************************************************************
*
*  $FC Fun��o: USU  &Excluir Usuario
*
*  $ED Descri��o da fun��o
*	  Exclui o ponteiro para o usu�rio fornecido.
*
*  $EP Par�metros
*     pUsuario  -	Ponteiro para um usu�rio.
*
*  $FV Valor retornado
*	  NULL  - Usu�rio exclu�do com sucesso.
*
***********************************************************************/

void * USU_ExcluirUsuario(void * Usuario);

/***********************************************************************
*
*  $FC Fun��o: USU  &Alterar Usuario
*
*  $ED Descri��o da fun��o
*	  Altera o valor de um dado do usu�rio de acordo com a op��o fornecida
*	  e o novo valor fornecido no par�metro.
*
*  $EP Par�metros
*     pUsuario  -	Ponteiro para um usu�rio.
*	  opcao     -	N�mero correspondente a op��o de altera��o desejada.
*					1 - Nome
*					2 - Email
*					3 - Data de Nascimento
*					4 - Cidade de moradia
*     mudanca   -  ponteiro para a string que cont�m o novo valor.
*
*  $FV Valor retornado
*	 USU_CondRetOK             - Altera��o realizada com sucesso.
*	 USU_CondRetUsuarioNExiste - Usu�rio fornecido n�o existe.
*
***********************************************************************/

USU_tpCondRet USU_AlterarUsuario(void * pUsuario,int opcao,char mudanca[]);

/***********************************************************************
*
*  $FC Fun��o: USU  &Preenche Dados Usu�rio
*
*  $ED Descri��o da fun��o
*	  Atualiza o conte�do dos ponteiros fornecidos com os dados de um usu�rio.
*
*  $EP Par�metros
*    pUsuario  -	Ponteiro para um usu�rio.
*    nome      -    Nome do usu�rio.
*    email     -	Email do usu�rio.
*    dtnasc    -	Data de nascimento do usu�rio.  
*    cidade    - 	Cidade de moradia do usu�rio.
*
*  $FV Valor retornado
*	 USU_CondRetOK             - As vari�veis fornecidas foram preenchidos com sucesso.
*	 USU_CondRetUsuarioNExiste - Usu�rio fornecido n�o existe.
*
***********************************************************************/

USU_tpCondRet USU_PreencheDadosUsuario(void * pUsuario,char nome[],char email[],char dtnasc[],char cidade[]);

/***********************************************************************
*
*  $FC Fun��o: USU  &Obter Lista Msgs
*
*  $ED Descri��o da fun��o
*	  Retorna a lista de mensagens de um usu�rio
*	  de acordo com o tipo recebido como par�metro.
*	  
*  $EP Par�metros
*     pUsuario		-	Ponteiro para um usu�rio.
*	  tipo			-   Corresponde ao tipo da lista de mensagens
*						1 - Lista de mensagens Enviadas
*						2 - Lista de mensagens Recebidas
*
*  $FV Valor retornado
*		Ponteiro para a lista de mensagens.
*	    NULL - Tipo inv�lido ou pUsuario n�o existe.
*
***********************************************************************/

void * USU_ObterListaMsgs(void * pUsuario, int tipo);

/***********************************************************************
*
*  $FC Fun��o: USU  &Obter Id Usu�rio
*
*  $ED Descri��o da fun��o
*	  Preenche a vari�vel recebida como par�metro com o id do usu�rio fornecido.
*	  
*  $EP Par�metros
*     pUsuario		-	Ponteiro para um usu�rio.
*     id            -   Vari�vel que ser� preenchida com o id do usu�rio.
*
*  $FV Valor retornado
*	  USU_CondRetOK				- Atualizou a vari�vel id com sucesso.
*	  USU_CondRetUsuarioNExiste - O usu�rio n�o existe.
*
***********************************************************************/

USU_tpCondRet USU_ObterIdUsuario(void * pUsuario, char *id);

/***********************************************************************
*
*  $FC Fun��o: USU  &Checar String
*
*  $ED Descri��o da fun��o
*	  Faz a valida��o da string fornecida.
*	  Para ser v�lido a string fornecida s� pode conter letras
*	  A fun��o converte a string automaticamente para mai�sculo.
*
*  $EP Par�metros
*     Str  - Ponteiro para a string de um nome de usu�rio ou cidade a ser validada.
*
*  $FV Valor retornado
*	  USU_CondRetOK  -  A string foi verificada com sucesso.
*
***********************************************************************/

USU_tpCondRet USU_ChecaString(char *Str);

/***********************************************************************
*
*  $FC Fun��o: USU  &Checar Email
*
*  $ED Descri��o da fun��o
*	  Faz a valida��o da string de um email fornecida.
*
*  $EP Par�metros
*     Str  - Ponteiro para a string de um email a ser validada.
*
*  $FV Valor retornado
*	  USU_CondRetOK			  -  A string do email foi verificada com sucesso.
*	  USU_CondRetInfoInvalida - String do email � inv�lida.
*
***********************************************************************/

USU_tpCondRet USU_ChecaEmail(char *Str);

/***********************************************************************
*
*  $FC Fun��o: USU  &Checar DtNasc
*
*  $ED Descri��o da fun��o
*	  Faz a valida��o da string fornecida.
*	  Para ser v�lido a string fornecida deve seguir o formato dd/mm/aaaa
*
*  $EP Par�metros
*     Str  - Ponteiro para a string de um data de nascimento a ser validada.
*
*  $FV Valor retornado
*	  USU_CondRetOK			  -  A string foi verificada com sucesso.
*	  USU_CondRetInfoInvalida -  Formato da data de nascimento � inv�lida.
*
***********************************************************************/

USU_tpCondRet USU_ChecaDtNasc(char *Str);

/***********************************************************************/

#undef USUARIO_EXT

/********** Fim do m�dulo de defini��o: USU Usu�rio da rede de relacionamentos **********/

#else
#endif