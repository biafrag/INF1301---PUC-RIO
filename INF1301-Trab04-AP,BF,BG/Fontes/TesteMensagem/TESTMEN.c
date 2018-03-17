 /**********************************************************************************
*  $MCI Módulo de implementação: TMEN Teste Mensagem 
*
*  Arquivo gerado:              TESTMEN.c
*  Letras identificadoras:      TMEN
*
*  Projeto: T4 INF 1301 2017.2
*  Autores: ap - André Pessanha
*           bg - Bianca Gomes
*           bf - Bianca Fragoso
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*		2	   bg	06/dez/2017	  continuãção desenvolvimento e finalização
*		1      bg   04/dez/2017   início desenvolvimento
*
***********************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_ESPC.H"

#include    "GENERICO.H"
#include    "LERPARM.H"

#include    "MENSAGEM.h"
#include    "LISTA.h"


static const char RESET_MENSAGEM_CMD         [ ] = "=resetteste"      ;
static const char CRIAR_MENSAGEM_CMD         [ ] = "=criarmensagem"   ;
static const char ENVIAR_MENSAGEM_CMD        [ ] = "=enviarmensagem"  ;
static const char CONTA_MENSAGEM_CMD         [ ] = "=contamensagem"   ;
static const char IR_IN_REG_MENSAGEM_CMD     [ ] = "=irmensagem"     ;
static const char AVANCAR_REG_MENSAGEM_CMD   [ ] = "=avancamensagem" ;
static const char OBTER_MENSAGEM_CMD         [ ] = "=obtermensagem"   ;

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_MEN   100
#define DIM_VALOR     100

MEN_tppMensagem vtMensagem[DIM_VT_MEN];
LIS_tppLista	vtMsgRec[DIM_VT_MEN];
LIS_tppLista	vtMsgEnv[DIM_VT_MEN]; 


/***** Protótipos das funções encapuladas no módulo *****/

   int ValidarInxMen( int inxMen , int Modo ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TGRA &Testar Mensagens
*
*  $ED Descrição da função
*     Podem ser criadas até 100 mensagens, identificadas pelos índices 0 a 100
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de mensagens. Provoca vazamento de memória
*     =criarmensagem                inxMen	  String1  String2  String3
*     =enviarmensagem               inxMen    CondRetEsp
*     =contamensagem                tipo  CondRetEsp
*     =irmensagem	                tipo  CondRetEsp
*	  =avancamensagem               tipo  CondRetEsp
*	  =obtermensagem                tipo  CondRetEsp
*
******************************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {
	  int inxMen = -1 ,
           numLidos   = -1 ,
		   tipo = -1 ,
           CondRetEsp = -1 ;

	  int qtd;

      TST_tpCondRet CondRet ;
	  char   String1[  DIM_VALOR ] ;
	  char   String2[  DIM_VALOR ];
	  char   String3[  DIM_VALOR ];
	  char   id[  DIM_VALOR ];

	  int i;
	  
	  /* Efetuar reset de teste de mensagem */

         if ( strcmp( ComandoTeste , RESET_MENSAGEM_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_MEN ; i++ )
            {
               vtMensagem[i] = NULL ;
            } /* for */
			 
			return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de mensagem */
		       
		 /* Testar CriarMensagem */

          if ( strcmp( ComandoTeste , CRIAR_MENSAGEM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isss" ,
                       &inxMen,String1,String2,String3 ) ;

            if ( ( numLidos != 4 )
              || ( ! ValidarInxMen( inxMen , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */
			
            vtMensagem[ inxMen ] =
                 MEN_CriarMensagem(String1, String2, String3) ;
			
			vtMsgRec[inxMen] = LIS_CriarLista(NULL);
			vtMsgEnv[inxMen] = LIS_CriarLista(NULL);

            return TST_CompararPonteiroNulo( 1 , vtMensagem[ inxMen ] ,
               "Erro em ponteiro de nova mensagem."  ) ;

         } /* fim ativa: Testar CriarMensagem */
		 
		 /* Testar enviar Mensagem */

         else if ( strcmp( ComandoTeste , ENVIAR_MENSAGEM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                       &inxMen, &CondRetEsp ) ;
			
			if ( ( numLidos != 2 ))
            {
               return TST_CondRetParm ;
            } /* if */
			
			CondRet = (TST_tpCondRet) MEN_EnviarMensagem (vtMensagem[ inxMen ], vtMsgEnv[ 0 ] , vtMsgRec[ 0 ]);
			
            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de erro ao enviar mensagem.") ;

         } /* fim ativa: Testar enviar Mensagem  */
		 
		  /* Testar Conta Mensagens */

         else if ( strcmp( ComandoTeste , CONTA_MENSAGEM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                        &tipo , &CondRetEsp ) ;
			
			if ( ( numLidos != 2 ) )
            {
               return TST_CondRetParm ;
            } /* if */

			if (tipo == 1)
				CondRet = (TST_tpCondRet) MEN_ContaMensagens (vtMsgEnv[ 0 ], &qtd);
			else if (tipo == 2)
				CondRet = (TST_tpCondRet) MEN_ContaMensagens (vtMsgRec[ 0 ], &qtd);
			else {
				printf("Tipo inválido. Escolha Enviadas ou Recebidas\n");
				CondRet = TST_CondRetNaoImplementado;
			}

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao contar mensagens.") ;

         } /* fim ativa: Testar Conta Mensagens */

		/* Testar Ir Inicio Registro Mensagens */
        else if ( strcmp( ComandoTeste , IR_IN_REG_MENSAGEM_CMD ) == 0 ) {

            numLidos = LER_LerParametros( "ii" ,
                       &tipo , &CondRetEsp ) ;

            if ( ( numLidos != 2 ) )
            {
               return TST_CondRetParm ;
            } /* if */

			if (tipo == 1)
				CondRet = (TST_tpCondRet) MEN_IrInicioRegistroMsgs (vtMsgEnv[ 0 ]);
			else if (tipo == 2)
				CondRet = (TST_tpCondRet) MEN_IrInicioRegistroMsgs (vtMsgRec[ 0 ]);
			else {
				printf("Tipo inválido. Escolha Enviadas ou Recebidas\n");
				CondRet = TST_CondRetNaoImplementado;
			}
			
			CondRet = TST_CompararString( id , id,
                         "Condicao de retorno errada para ir no inicio do registro de mensagens" ) ;

			return CondRet;

        } /* fim ativa: Testar Ir Inicio Registro Mensagens */

		/* Testar Avançar Registro Mensagens */

          else if ( strcmp( ComandoTeste , AVANCAR_REG_MENSAGEM_CMD  ) == 0 )
         {
           numLidos = LER_LerParametros( "ii" ,
                       &tipo, &CondRetEsp ) ;

            if ( ( numLidos != 2))
            {
               return TST_CondRetParm ;
            } /* if */

			if (tipo == 1)
				CondRet = (TST_tpCondRet) MEN_AvancarRegistroMsgs (vtMsgEnv[ 0 ]);
			else if (tipo == 2)
				CondRet = (TST_tpCondRet) MEN_AvancarRegistroMsgs (vtMsgRec[ 0 ]);
			else {
				printf("Tipo inválido. Escolha Enviadas ou Recebidas\n");
				CondRet = TST_CondRetNaoImplementado;
			}

            return TST_CompararInt( CondRetEsp , CondRet ,
               "Condicao de retorno errada ao avançar no registro de mensagens."  ) ;
         } /* fim ativa: Testar Avançar Registro Mensagens */
		          	
		/* Testar Obter Mensagem */  
		else if ( strcmp( ComandoTeste, OBTER_MENSAGEM_CMD ) == 0 ) {

			 numLidos = LER_LerParametros( "ii" , &tipo,  &CondRetEsp) ;

			 if ( ( numLidos != 2 ))
            {
               return TST_CondRetParm ;
            } /* if */
			
			if (tipo == 1)
				CondRet = (TST_tpCondRet) MEN_ObterMensagem (vtMsgEnv[ 0 ], String1, id);
			else if (tipo == 2)
				CondRet = (TST_tpCondRet) MEN_ObterMensagem (vtMsgRec[ 0 ], String1, id);
			else {
				printf("Tipo inválido. Escolha Enviadas ou Recebidas\n");
				CondRet = TST_CondRetNaoImplementado;
			}

			return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao obter mensagem.") ;
		}/* Fim da Obter Mensagem */

      return TST_CondRetOK;
   }


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: TGRA -Validar indice de mensagem
*
***********************************************************************/

   int ValidarInxMen( int inxMen , int Modo )
   {

      if ( ( inxMen <  0 )
        || ( inxMen >= DIM_VT_MEN ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtMensagem[ inxMen ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtMensagem[ inxMen ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim função: TGRA -Validar indice de mensagem */

/********** Fim do módulo de implementação: TGRA Teste grafo de símbolos **********/