/***************************************************************************
*  $MCI M�dulo de implementa��o: USU  Usu�rio da rede de relacinamentos
*
*  Arquivo gerado:              USUARIO.c
*  Letras identificadoras:      USU
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\USUARIO.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: AP,BF,BG.
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     6      ap   02/dez/2017   Cria��o das fun��es ObterListaMsgs e ObterIdUsuario.
*     5      bf   20/nov/2017   mudancas para tirar consultas indevidas ao usuario
*	  4      ap   04/nov/2017   Cria��o da fun��o ExibeMsgEntreUsuarios
*	  3      ap   02/nov/2017   Cria��o da fun��o EnviaMsgParaUsuario
*     2		 bg   28/out/2017	continua��o desenvolvimento
*     1      bf   26/out/2017   in�cio desenvolvimento
*
***************************************************************************/


#include   <stdio.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>
#include   <conio.h>
#include   <stdlib.h>
#include   <string.h>

#define USUARIO_OWN
#include "USUARIO.h" 
#undef USUARIO_OWN


/***********************************************************************
*
*  $TC Tipo de dados: USU Informa��es do usu�rio
*
*
***********************************************************************/

   typedef struct USU_tagUsuario {
	   char id[51];
	   /* string com o identificador (nickname) do usuario */

	   char nome[51];
	   /* string com o nome do usuario */

	   char email[51];
	   /* string com o email do usuario */

	   char cidade[51];
	   /*string com a cidade natal do usuario*/

	   char dtNasc[11];
	   /* string com a data de nascimento do usuario, no formato DD/MM/AAAA */

	   LIS_tppLista msgsRecebidas;
	   LIS_tppLista msgsEnviadas;

   } USU_tpUsuario ;


/***** Prot�tipos das fun��es encapuladas no m�dulo *****/



/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: USU  &Criar Usu�rio
*  ****/

USU_tppUsuario USU_CriarUsuario(char id[],char nome[],char email[],char dtnasc[],char cidade[])
{
   USU_tppUsuario pUsuario;

   pUsuario = ( USU_tpUsuario * ) malloc( sizeof( USU_tpUsuario )) ;
   if ( pUsuario == NULL )
   {
	  return NULL;
   } /* if */
    strcpy(pUsuario->id,id);
    strcpy(pUsuario->nome,nome);
	strcpy(pUsuario->email,email);
	strcpy(pUsuario->cidade,cidade);
	strcpy(pUsuario->dtNasc,dtnasc);
	pUsuario->msgsRecebidas=LIS_CriarLista(NULL); 
	pUsuario->msgsEnviadas=LIS_CriarLista(NULL); 

	return pUsuario;
}
/* Fim fun��o: USU &Criar Usu�rio */

/***************************************************************************
*
*  Fun��o: USU  &Destruir Usu�rio
*  ****/

void * USU_ExcluirUsuario(void * Usuario)
{
	
	if(Usuario != NULL){
		free(Usuario);
	}
	return NULL;
}

/* Fim fun��o: USU &Destruir Usu�rio */

/***************************************************************************
*
*  Fun��o: USU  &Alterar Usu�rio
*  ****/

USU_tpCondRet USU_AlterarUsuario(void * pUsuario,int opcao,char mudanca[])
{
	//Conferir strings
	
	USU_tppUsuario pUser;
	if(pUsuario == NULL){
		return USU_CondRetUsuarioNExiste;
	}
	pUser = (USU_tppUsuario)pUsuario;

	switch (opcao)
	{
		case 1:
			strcpy(pUser->nome,mudanca);
			break;

		case 2:
			strcpy(pUser->email,mudanca);
			break;

		case 3:
			strcpy(pUser->dtNasc,mudanca);
			break;

	   case 4:
			strcpy(pUser->cidade,mudanca);
			break;
	   default:
		   return USU_CondRetOpcaoNExiste;
	}
	return USU_CondRetOK;
}
/* Fim fun��o: USU  &Alterar Usu�rio */

/***************************************************************************
*
*  Fun��o: USU  &Preenche Dados Usu�rio
*  ****/
USU_tpCondRet USU_PreencheDadosUsuario(void * pUsuario,char nome[],char email[],char dtnasc[],char cidade[])
{
	USU_tppUsuario pUser;
	if(pUsuario == NULL){
		return USU_CondRetUsuarioNExiste;
	}
	pUser = (USU_tppUsuario)pUsuario;
	strcpy(nome,pUser->nome);
	strcpy(email,pUser->email);
	strcpy(dtnasc,pUser->dtNasc);
	strcpy(cidade,pUser->cidade);

	return USU_CondRetOK;
	
}
/* Fim fun��o: USU  &Preenche Dados Usu�rio  */

/***************************************************************************
*
*  Fun��o: USU  &Obter Lista Msgs
*  ****/

void * USU_ObterListaMsgs(void * pUsuario, int tipo){
	USU_tppUsuario pUser;

	if(pUsuario == NULL){
		return NULL;
	}

	pUser = (USU_tppUsuario) pUsuario;

	if(tipo == 1){  // Mensagens Enviadas
		return pUser->msgsEnviadas;
	}
	else if(tipo == 2){ //Mensagens recebidas
		return pUser->msgsRecebidas;
	}

	return NULL;
	
}  /* Fim fun��o: USU  &Obter Lista Msgs  */

/***************************************************************************
*
*  Fun��o: USU  &Obter ID Usu�rio
*  ****/

USU_tpCondRet USU_ObterIdUsuario(void * pUsuario, char *id){
	USU_tppUsuario pUser;

	if(pUsuario == NULL){
		return USU_CondRetUsuarioNExiste;
	}

	pUser = (USU_tppUsuario) pUsuario;

	strcpy(id, pUser->id);
	
	return USU_CondRetOK;
	
}  /* Fim fun��o: USU  &Obter ID Usu�rio */


/***************************************************************************
*
*  Fun��o: USU  &Checar String
*  ****/
 USU_tpCondRet USU_ChecaString(char *Str)
 {
	int i, tam;
	//Verifica se s� tem letras e tranforma string em maiuscula
	tam = strlen(Str);

	for(i=0;i<tam;i++){   
		if( !(Str[i] >= 'a' && Str[i] <= 'z') && !(Str[i] >= 'A' && Str[i] <= 'Z') && !(Str[i] ==' ') )
			return USU_CondRetInfoInvalida;
		else if(Str[i] >= 'a' && Str[i] <= 'z')
			Str[i] = Str[i] - 32;
	}

	return USU_CondRetOK;
 }
  /*  Fim fun��o: USU  &Checar String */

/***************************************************************************
*
*  Fun��o: USU  &Checar Email
*  ****/  
 
 USU_tpCondRet USU_ChecaEmail(char *Str)
 {
	 int i,confere=0,conferePt=0;
	 char conf[51];
   /*
   O ideal seria fazer uma valida�ao atrav�s da express�o regular usando a biblioteca "regex.h". Entretanto como n�o � poss�vel 
   utilizar essa biblioteca no visual studio, faremos uma valida��o mais simpl�ria e n�o eficiente para todos os casos 
   */
	if (Str[0] == '@' || Str[0] == '.')
	{
		return USU_CondRetInfoInvalida;
	} /* if */

	for(i=0; i< (strlen(Str)+1); i++) 
	{
		if (Str[i] == '@')
			confere+=1;
		if (Str[i] == '.')
			conferePt+=1;
		if (Str[i] == '@' && Str[i+1] == '.')
			return USU_CondRetInfoInvalida;
		if (Str[i] == '.' && Str[i+1] == '@')
			return USU_CondRetInfoInvalida;
		if (Str[i] == '.' && Str[i+1] == '.')
			return USU_CondRetInfoInvalida;
		if (Str[i] == '@' && Str[i+1] == '\0')
			return USU_CondRetInfoInvalida;
		if (Str[i] == '.' && Str[i+1] == '\0')
			return USU_CondRetInfoInvalida;
	} /* for */

	if (confere != 1) return USU_CondRetInfoInvalida;
	if (conferePt < 1 || conferePt > 2)  return USU_CondRetInfoInvalida;

	strcpy(conf,Str);
	strtok(conf,"@"); //tira a parte antes do @
	if (strlen(conf) < 6 || strlen(conf)>30)  return USU_CondRetInfoInvalida; //considerando o crit�rio do gmail
	
	return USU_CondRetOK; 
 }
  /*  Fim fun��o: USU  &Checar Email */


  /***************************************************************************
*
*  Fun��o: USU  &Checar DtNasc
*  ****/
  USU_tpCondRet USU_ChecaDtNasc(char *Str)
 {
	int i,dia,mes,ano;
	char conf[11];

	if (strlen(Str)!=10) 
	{
		return USU_CondRetInfoExcedeuTamanho;
	} /* if */
	//Confere formato da data
	
	if(Str[2] != '/' || Str[5]!='/')
		return USU_CondRetInfoInvalida;
	
	//Confere se a data � constituida apenas de numeros 
	for(i=0;i<10;i++)
	{
		if ( i==2 || i==5)
		{
			i++;
		} /* if */
		if(Str[i]< '0' || Str[i]>'9')
		{
			return USU_CondRetInfoInvalida;
		} /* if */
	} /* for */

	strcpy(conf,Str);

	dia = atoi(strtok (conf,"/"));
    mes = atoi(strtok (NULL, "/"));
	ano = atoi(strtok (NULL, "\0"));
	
	if ((dia >= 1 && dia <= 31) && (mes >= 1 && mes <= 12) && (ano >= 1900 && ano <= 2100))
	{
		if ((dia == 29 && mes == 2) && ( ((ano % 400) == 0)  || ( ((ano % 4) == 0) && ((ano % 100) != 0)) ) ) /* verifica se o ano � bissexto - um ano � bisssexto se ele for divis�vel por 400 ou se for divis�vel por 4 e n�o por 100 */
      	{
			return USU_CondRetOK;
		} 
        if (dia <= 28 && mes == 2) //verifica o mes de feveireiro 
		{
            return USU_CondRetOK;
		} 
        if ((dia <= 30) && (mes == 4 || mes == 6 || mes == 9 || mes == 11)) //verifica os meses de 30 dias
		{
			return USU_CondRetOK;
		} 
        if ((dia <=31) && (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes ==8 || mes == 10 || mes == 12)) //verifica os meses de 31 dias
        {
			return USU_CondRetOK;
		}
        else {
            return USU_CondRetInfoInvalida;
		} /* if */
   }
   else {
	   return USU_CondRetInfoInvalida;
   } /* if */
}
/*  Fim fun��o: USU  &Checar DtNasc */

/********** Fim do m�dulo de implementa��o: USU  Usuario da rede de relacionamentos **********/