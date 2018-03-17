#if ! defined( MENSAGEM_ )
#define MENSAGEM_

/***************************************************************************
*
*  $MCD Módulo de definição: MEN  Mensagem entre usuarios
*
*  Arquivo gerado:              MENSAGEM.h
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
*     Versão  Autor      Data        Observações
*     4        ap    02/dez/2017  Implementação de novas funções e correções.
*     3        ap    03/nov/2017  Implementação da função exibe mensagens.
*     2        ap    02/nov/2017  Implementação da função criar e enviar mensagem.
*     1        bf    28/out/2017  Início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa mensagens entre usuarios na rede de relacionamentos
*     Podem existir n mensagens em operação simultaneamente.
*     mensagens possuem dois ids de usuario e o texto que compõe a mensagem.
*
***************************************************************************/
 
#if defined( MENSAGEM_OWN )
   #define MENSAGEM_EXT
#else
   #define MENSAGEM_EXT extern
#endif

#include "LISTA.h"
#include "USUARIO.h"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma mensagem */

typedef struct MEN_tagMensagem * MEN_tppMensagem ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
*
***********************************************************************/

   typedef enum {

         MEN_CondRetOK ,
               /* Concluiu corretamente */
        MEN_CondRetFaltouMemoria,
               /* Faltou memória ao criar a mensagem */
		MEN_CondRetSemMensagens,
				/*Não há mensagens */
		MEN_CondRetMsgNExiste,
		        /*A lista de mensagem não foi criada */
		MEN_CondRetFimRegistro
		       /*Chegou ao fim do registro de mensagens*/
   } MEN_tpCondRet;


/***********************************************************************
*
*  $FC Função: MEN  &Criar Mensagem
*
*  $ED Descrição da função
*     Cria uma mensagem. Faz a leitura da mensagem.
*
*  $EP Parâmetros
*     idRemetente  -	Identificador do usuário Remetente.
*	  idDestino    -	Identificador do usuário Destino.
*	  texto		   -    String contendo o texto da mensagem.
*
*  $FV Valor retornado
*     pMensagem - Se executou corretamente retorna o ponteiro para a mensagem.
*     NULL      - Caso ocorra algum erro na criação da mensagem.
*
***********************************************************************/

 MEN_tppMensagem MEN_CriarMensagem (char idRemetente[], char idDestino[],char texto[]);

/***********************************************************************
*
*  $FC Função: MEN  &Enviar Mensagem
*
*  $ED Descrição da função
*	  Envia uma mensagem contendo texto, remetente e destino.
*
*  $EP Parâmetros
*	  pMensagem      -	Ponteiro para a mensagem.
*     msgsEnviadas   -	Ponteiro para a lista de mensagens enviadas pelo usuário remetente.
*	  msgsRecebidas  -	Ponteiro para a lista de mensagens recebidas pelo usuário destino.
*
*  $FV Valor retornado
*		MEN_CondRetOK         - A mensagem foi enviada com sucesso.
*		MEN_CondRetMsgNExiste - A lista de mensagens não existe.
*
***********************************************************************/

MEN_tpCondRet MEN_EnviarMensagem (void *pMensagem, void * msgsEnviadas, void * msgsRecebidas);

/***********************************************************************
*
*  $FC Função: MEN  &Obter Mensagem
*
*  $ED Descrição da função
*	  Atualiza as variáveis recebidas no parâmetro
*     com os dados da mensagem atual.
*
*  $EP Parâmetros
*		msgs    - Ponteiro que contém a lista de mensagens de um usuário.
*		texto   - Ponteiro que será atualizado com o texto da mensagem.
*		idDest  - Ponteiro que será atualizado com o id do destino da mensagem. 
*
*  $FV Valor retornado
*		MEN_CondRetOK - As variáveis texto e idDest foram atualizadas com sucesso.
*	    MEN_CondRetMsgNExiste  - A lista de mensagens não foi criada.
*
***********************************************************************/
  
 MEN_tpCondRet MEN_ObterMensagem(void * msgs, char *texto, char *idDest);

/***********************************************************************
*
*  $FC Função: MEN  &Conta Mensagens
*
*  $ED Descrição da função
*		Atualiza a variável qtd com a quantidade total de mensagens
*		contida na lista recebida no parâmetro.
*
*  $EP Parâmetros
*		msgs - Ponteiro que contém a lista de mensagens de um usuário.
*		qtd  - Ponteiro que será atualizado com a quantidade total de mensagens.
*
*  $FV Valor retornado
*		MEN_CondRetOK		    - A variável qtd foi atualizada com sucesso.
*	    MEN_CondRetMsgNExiste   - A lista de mensagens não foi criada.
*		MEN_CondRetSemMensagens - Nenhuma mensagem no registro. 
*
***********************************************************************/
  
MEN_tpCondRet MEN_ContaMensagens (void * msgs, int *qtd);

/***********************************************************************
*
*  $FC Função: MEN  &Ir Inicio Registro Mensagens
*
*  $ED Descrição da função
*		Retorna para o inicio do registro de mensagens.
*
*  $EP Parâmetros
*		msgs - Ponteiro que contém a lista de mensagens de um usuário.
*
*  $FV Valor retornado
*		MEN_CondRetOK          - Voltou para o inicio do registro com sucesso.
*	    MEN_CondRetMsgNExiste  - A lista de mensagens não foi criada.
*
***********************************************************************/

MEN_tpCondRet MEN_IrInicioRegistroMsgs (void *msgs);

/***********************************************************************
*
*  $FC Função: MEN  &Avançar Registro Mensagens
*
*  $ED Descrição da função
*		Avança para a próxima mensagem contida no registro.	
*
*  $EP Parâmetros
*		msgs - Ponteiro que contém a lista de mensagens de um usuário.
*
*  $FV Valor retornado
*		MEN_CondRetOK		   - Avançou o registro de mensagens com sucesso.
*		MEN_CondRetFimRegistro - Não tem mais mensagens no registro.
*	    MEN_CondRetMsgNExiste  - A lista de mensagens não foi criada.
*
***********************************************************************/

MEN_tpCondRet MEN_AvancarRegistroMsgs (void *msgs);

/***********************************************************************/

#undef MENSAGEM_EXT

/********** Fim do módulo de definição: MEN Mensagem entre usuarios **********/

#else
#endif