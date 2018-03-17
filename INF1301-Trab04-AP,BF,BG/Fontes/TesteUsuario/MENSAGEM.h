#if ! defined( MENSAGEM_ )
#define MENSAGEM_

/***************************************************************************
*
*  $MCD M�dulo de defini��o: MEN  Mensagem entre usuarios
*
*  Arquivo gerado:              MENSAGEM.h
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
*     Vers�o  Autor      Data        Observa��es
*     4        ap    02/dez/2017  Implementa��o de novas fun��es e corre��es.
*     3        ap    03/nov/2017  Implementa��o da fun��o exibe mensagens.
*     2        ap    02/nov/2017  Implementa��o da fun��o criar e enviar mensagem.
*     1        bf    28/out/2017  In�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Implementa mensagens entre usuarios na rede de relacionamentos
*     Podem existir n mensagens em opera��o simultaneamente.
*     mensagens possuem dois ids de usuario e o texto que comp�e a mensagem.
*
***************************************************************************/
 
#if defined( MENSAGEM_OWN )
   #define MENSAGEM_EXT
#else
   #define MENSAGEM_EXT extern
#endif

#include "LISTA.h"
#include "USUARIO.h"

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma mensagem */

typedef struct MEN_tagMensagem * MEN_tppMensagem ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da lista
*
***********************************************************************/

   typedef enum {

         MEN_CondRetOK ,
               /* Concluiu corretamente */
        MEN_CondRetFaltouMemoria,
               /* Faltou mem�ria ao criar a mensagem */
		MEN_CondRetSemMensagens,
				/*N�o h� mensagens */
		MEN_CondRetMsgNExiste,
		        /*A lista de mensagem n�o foi criada */
		MEN_CondRetFimRegistro
		       /*Chegou ao fim do registro de mensagens*/
   } MEN_tpCondRet;


/***********************************************************************
*
*  $FC Fun��o: MEN  &Criar Mensagem
*
*  $ED Descri��o da fun��o
*     Cria uma mensagem. Faz a leitura da mensagem.
*
*  $EP Par�metros
*     idRemetente  -	Identificador do usu�rio Remetente.
*	  idDestino    -	Identificador do usu�rio Destino.
*	  texto		   -    String contendo o texto da mensagem.
*
*  $FV Valor retornado
*     pMensagem - Se executou corretamente retorna o ponteiro para a mensagem.
*     NULL      - Caso ocorra algum erro na cria��o da mensagem.
*
***********************************************************************/

 MEN_tppMensagem MEN_CriarMensagem (char idRemetente[], char idDestino[],char texto[]);

/***********************************************************************
*
*  $FC Fun��o: MEN  &Enviar Mensagem
*
*  $ED Descri��o da fun��o
*	  Envia uma mensagem contendo texto, remetente e destino.
*
*  $EP Par�metros
*	  pMensagem      -	Ponteiro para a mensagem.
*     msgsEnviadas   -	Ponteiro para a lista de mensagens enviadas pelo usu�rio remetente.
*	  msgsRecebidas  -	Ponteiro para a lista de mensagens recebidas pelo usu�rio destino.
*
*  $FV Valor retornado
*		MEN_CondRetOK         - A mensagem foi enviada com sucesso.
*		MEN_CondRetMsgNExiste - A lista de mensagens n�o existe.
*
***********************************************************************/

MEN_tpCondRet MEN_EnviarMensagem (void *pMensagem, void * msgsEnviadas, void * msgsRecebidas);

/***********************************************************************
*
*  $FC Fun��o: MEN  &Obter Mensagem
*
*  $ED Descri��o da fun��o
*	  Atualiza as vari�veis recebidas no par�metro
*     com os dados da mensagem atual.
*
*  $EP Par�metros
*		msgs    - Ponteiro que cont�m a lista de mensagens de um usu�rio.
*		texto   - Ponteiro que ser� atualizado com o texto da mensagem.
*		idDest  - Ponteiro que ser� atualizado com o id do destino da mensagem. 
*
*  $FV Valor retornado
*		MEN_CondRetOK - As vari�veis texto e idDest foram atualizadas com sucesso.
*	    MEN_CondRetMsgNExiste  - A lista de mensagens n�o foi criada.
*
***********************************************************************/
  
 MEN_tpCondRet MEN_ObterMensagem(void * msgs, char *texto, char *idDest);

/***********************************************************************
*
*  $FC Fun��o: MEN  &Conta Mensagens
*
*  $ED Descri��o da fun��o
*		Atualiza a vari�vel qtd com a quantidade total de mensagens
*		contida na lista recebida no par�metro.
*
*  $EP Par�metros
*		msgs - Ponteiro que cont�m a lista de mensagens de um usu�rio.
*		qtd  - Ponteiro que ser� atualizado com a quantidade total de mensagens.
*
*  $FV Valor retornado
*		MEN_CondRetOK		    - A vari�vel qtd foi atualizada com sucesso.
*	    MEN_CondRetMsgNExiste   - A lista de mensagens n�o foi criada.
*		MEN_CondRetSemMensagens - Nenhuma mensagem no registro. 
*
***********************************************************************/
  
MEN_tpCondRet MEN_ContaMensagens (void * msgs, int *qtd);

/***********************************************************************
*
*  $FC Fun��o: MEN  &Ir Inicio Registro Mensagens
*
*  $ED Descri��o da fun��o
*		Retorna para o inicio do registro de mensagens.
*
*  $EP Par�metros
*		msgs - Ponteiro que cont�m a lista de mensagens de um usu�rio.
*
*  $FV Valor retornado
*		MEN_CondRetOK          - Voltou para o inicio do registro com sucesso.
*	    MEN_CondRetMsgNExiste  - A lista de mensagens n�o foi criada.
*
***********************************************************************/

MEN_tpCondRet MEN_IrInicioRegistroMsgs (void *msgs);

/***********************************************************************
*
*  $FC Fun��o: MEN  &Avan�ar Registro Mensagens
*
*  $ED Descri��o da fun��o
*		Avan�a para a pr�xima mensagem contida no registro.	
*
*  $EP Par�metros
*		msgs - Ponteiro que cont�m a lista de mensagens de um usu�rio.
*
*  $FV Valor retornado
*		MEN_CondRetOK		   - Avan�ou o registro de mensagens com sucesso.
*		MEN_CondRetFimRegistro - N�o tem mais mensagens no registro.
*	    MEN_CondRetMsgNExiste  - A lista de mensagens n�o foi criada.
*
***********************************************************************/

MEN_tpCondRet MEN_AvancarRegistroMsgs (void *msgs);

/***********************************************************************/

#undef MENSAGEM_EXT

/********** Fim do m�dulo de defini��o: MEN Mensagem entre usuarios **********/

#else
#endif