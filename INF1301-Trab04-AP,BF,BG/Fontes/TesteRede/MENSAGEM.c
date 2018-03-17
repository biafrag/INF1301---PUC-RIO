/***************************************************************************
*  $MCI M�dulo de implementa��o: MEN  Mensagem entre usuarios
*
*  Arquivo gerado:              MENSAGEM.c
*  Letras identificadoras:      MEN
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\MENSAGEM.BSW
*
*  Projeto: T4 INF 1301 2017.2
*  Autores: ap - Andr� Pessanha
*           bg - Bianca Gomes
*           bf - Bianca Fragoso
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data       Observa��es
*     4        ap    02/dez/2017  Implementa��o de novas fun��es e corre��es.
*     3        ap    03/nov/2017  Implementa��o da fun��o exibe mensagens.
*     2        ap    02/nov/2017  Implementa��o da fun��o criar e enviar mensagem.
*     1        bf    28/out/2017 in�cio desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define MENSAGEM_OWN
#include "MENSAGEM.h"
#undef MENSAGEM_OWN

/***********************************************************************
*
*  $TC Tipo de dados: MEN Informa��es da mensagem
*
***********************************************************************/

   typedef struct MEN_tagMensagem {

         char idRemetente[51];
               /*String com o Id do Remetente da mensagem */

         char idDestino[51];
               /* String com o Id do Destinatario da mensagem*/

         char Texto[301];
               /* Texto da mensagem */

   } MEN_tpMensagem ;


/***** Prot�tipos das fun��es encapuladas no m�dulo *****/
  

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: MEN  &Criar Mensagem
*  ****/
   
MEN_tppMensagem MEN_CriarMensagem (char idRemetente[], char idDestino[],char texto[]){

	MEN_tppMensagem pMensagem;

	pMensagem = (MEN_tppMensagem) malloc (sizeof(MEN_tpMensagem));
	if(pMensagem == NULL){
		return NULL;
	}

	strcpy(pMensagem->Texto, texto);
	strcpy(pMensagem->idRemetente, idRemetente);
	strcpy(pMensagem->idDestino, idDestino);

	return pMensagem;

} /* Fim fun��o: MEN &Criar Mensagem */

/***************************************************************************
*
*  Fun��o: MEN  &Enviar Mensagem
*  ****/

MEN_tpCondRet MEN_EnviarMensagem (void *pMensagem, void * msgsEnviadas, void * msgsRecebidas)
{
	LIS_tpCondRet cond;
	MEN_tppMensagem pMsg;
	LIS_tppLista msgs1, msgs2;

	if(pMensagem == NULL || msgsEnviadas == NULL || msgsRecebidas == NULL){
		return MEN_CondRetMsgNExiste;
	}

	pMsg = (MEN_tppMensagem) pMensagem;
	msgs1 = (LIS_tppLista) msgsEnviadas;
	msgs2 = (LIS_tppLista) msgsRecebidas;

	cond = LIS_InserirElementoApos(msgs1, pMsg);
	if(cond == LIS_CondRetFaltouMemoria){
		return MEN_CondRetFaltouMemoria;
	}
	cond = LIS_InserirElementoApos(msgs2, pMsg);
	if(cond == LIS_CondRetFaltouMemoria){
		return MEN_CondRetFaltouMemoria;
	}

	return MEN_CondRetOK;

}  /* Fim fun��o: MEN &Enviar Mensagem */

/***************************************************************************
*
*  Fun��o: MEN  &Conta Mensagens
*  ****/

MEN_tpCondRet MEN_ContaMensagens (void * msgs, int *qtd){
	LIS_tppLista Lmsgs;

	if(msgs == NULL){
		return MEN_CondRetMsgNExiste;
	}
	Lmsgs = (LIS_tppLista) msgs;

	*qtd = LIS_ContaElementos(Lmsgs);
	if(*qtd == 0){
		return MEN_CondRetSemMensagens;
	}

	return MEN_CondRetOK;

} /* Fim fun��o: MEN &Conta Mensagens */

/***************************************************************************
*
*  Fun��o: MEN  &Ir Inicio Registro Mensagens
*  ****/

MEN_tpCondRet MEN_IrInicioRegistroMsgs (void *msgs){
	LIS_tppLista Lmsgs;

	if(msgs == NULL){
		return MEN_CondRetMsgNExiste;
	}
	Lmsgs = (LIS_tppLista) msgs;

	LIS_IrInicioLista(Lmsgs);

	return MEN_CondRetOK;

} /* Fim fun��o: MEN &Ir Inicio Registro Mensagens */

/***************************************************************************
*
*  Fun��o: MEN  &Avan�ar Registro Mensagens
*  ****/

MEN_tpCondRet MEN_AvancarRegistroMsgs (void *msgs){
	LIS_tppLista Lmsgs;
	LIS_tpCondRet cond;

	if(msgs == NULL){
		return MEN_CondRetMsgNExiste;
	}
	Lmsgs = (LIS_tppLista) msgs;

	cond = LIS_AvancarElementoCorrente(Lmsgs, 1);
	if(cond == LIS_CondRetFimLista){
		return MEN_CondRetFimRegistro;
	}

	return MEN_CondRetOK;

} /* Fim fun��o: MEN &Avan�ar Registro Mensagens */

/***************************************************************************
*
*  Fun��o: MEN  &Obter Mensagem
*  ****/

MEN_tpCondRet MEN_ObterMensagem(void * msgs, char *texto, char *destino){
	MEN_tppMensagem pMensagem;
	LIS_tppLista Lmsgs;

	if(msgs == NULL){
		return MEN_CondRetMsgNExiste;
	}

	Lmsgs = (LIS_tppLista) msgs;
	
	pMensagem = (MEN_tppMensagem) LIS_ObterValor(Lmsgs);
	if(pMensagem == NULL){
		return MEN_CondRetMsgNExiste;
	}
	strcpy(texto, pMensagem->Texto);
	strcpy(destino, pMensagem->idDestino);

	return MEN_CondRetOK;

} /* Fim fun��o: MEN &Obter Mensagem */
	

   /********** Fim do m�dulo de implementa��o: MEN Mensagem entre usuarios**********/