/***************************************************************************
*  $MCI Módulo de implementação: MEN  Mensagem entre usuarios
*
*  Arquivo gerado:              MENSAGEM.c
*  Letras identificadoras:      MEN
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\MENSAGEM.BSW
*
*  Projeto: T4 INF 1301 2017.2
*  Autores: ap - André Pessanha
*           bg - Bianca Gomes
*           bf - Bianca Fragoso
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data       Observações
*     4        ap    02/dez/2017  Implementação de novas funções e correções.
*     3        ap    03/nov/2017  Implementação da função exibe mensagens.
*     2        ap    02/nov/2017  Implementação da função criar e enviar mensagem.
*     1        bf    28/out/2017 início desenvolvimento
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
*  $TC Tipo de dados: MEN Informações da mensagem
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


/***** Protótipos das funções encapuladas no módulo *****/
  

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: MEN  &Criar Mensagem
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

} /* Fim função: MEN &Criar Mensagem */

/***************************************************************************
*
*  Função: MEN  &Enviar Mensagem
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

}  /* Fim função: MEN &Enviar Mensagem */

/***************************************************************************
*
*  Função: MEN  &Conta Mensagens
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

} /* Fim função: MEN &Conta Mensagens */

/***************************************************************************
*
*  Função: MEN  &Ir Inicio Registro Mensagens
*  ****/

MEN_tpCondRet MEN_IrInicioRegistroMsgs (void *msgs){
	LIS_tppLista Lmsgs;

	if(msgs == NULL){
		return MEN_CondRetMsgNExiste;
	}
	Lmsgs = (LIS_tppLista) msgs;

	LIS_IrInicioLista(Lmsgs);

	return MEN_CondRetOK;

} /* Fim função: MEN &Ir Inicio Registro Mensagens */

/***************************************************************************
*
*  Função: MEN  &Avançar Registro Mensagens
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

} /* Fim função: MEN &Avançar Registro Mensagens */

/***************************************************************************
*
*  Função: MEN  &Obter Mensagem
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

} /* Fim função: MEN &Obter Mensagem */
	

   /********** Fim do módulo de implementação: MEN Mensagem entre usuarios**********/