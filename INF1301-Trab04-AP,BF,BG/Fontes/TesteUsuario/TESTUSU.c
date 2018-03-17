/**********************************************************************************
*  $MCI M�dulo de implementa��o: TUSU Teste Usuario 
*
*  Arquivo gerado:              TESTUSU.c
*  Letras identificadoras:      TUSU
*
*  Projeto: T4 INF 1301 2017.2 
*  Autores: ap - Andr� Pessanha
*           bg - Bianca Gomes
*           bf - Bianca Fragoso
*  $HA Hist�rico de evolu��o:
*   Vers�o  Autor    Data       Observa��es
*	  4		 bg	  05/12/2017	continua��o do desenvolvimento depois de altera��es no m�dulo Usu�rio e finaliza��o
*     3      bf   01/12/2017    continua��o do desenvolvimento depois de terem sido feitas altera��es no m�dulo Usu�rio
*     2		 bf   18/nov/2017	continua��o desenvolvimento
*     1      bf   10/nov/2017   in�cio desenvolvimento
*
*
***********************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_ESPC.H"

#include    "GENERICO.H"
#include    "LERPARM.H"

#include    "USUARIO.h"
#include    "MENSAGEM.h"
#include    "LISTA.h"


static const char RESET_USUARIO_CMD    [ ] = "=resetteste"     ;
static const char CRIAR_USUARIO_CMD    [ ] = "=criarusuario"     ;
static const char EXCLUIR_USUARIO_CMD  [ ] = "=excluirusuario"  ;
static const char ALT_USUARIO_CMD      [ ] = "=alterarusuario"   ;
static const char PREEN_DADOS_USU_CMD  [ ] = "=preenchedados" ;
static const char OBTER_MSGS_CMD       [ ] = "=obtermsgs" ;  
static const char OBTER_ID_USU_CMD     [ ] = "=obterid" ;  
static const char CHECA_STRING_CMD     [ ] = "=checastring" ;
static const char CHECA_EMAIL_CMD      [ ] = "=checaemail" ;
static const char CHECA_DATA_CMD       [ ] = "=checadata" ;  

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_USUARIO   10
#define DIM_VALOR     100

USU_tppUsuario   vtUsuario[ DIM_VT_USUARIO ] ;

MEN_tppMensagem vtMensagem[ DIM_VT_USUARIO ] ;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static int ValidarInxUsuario( int inxUsuario, int Modo ) ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TGRA &Testar Usuario
*
*  $ED Descri��o da fun��o
*     Podem ser criadas at� 10 usuarios, identificados pelos �ndices 0 a 10
*
*     Comandos dispon�veis:
*
*     =resetteste
*     - anula o vetor de usuarios. Provoca vazamento de mem�ria
*     =criarusuario                 inxUsuario 
*     =excluirusuario               inxUsuario  CondRetEsp
*     =alterarusuario               inxUsuario  op		mudanca  CondRetEsp
*	  =preenchedados				inxUsuario  nome	email	dtnasc	cidade	CondRetEsp	
*	  =obtermsgs					inxUsuario  tipo  CondRetEsp
*	  =obteriduser					inxUsuario  CondRetEsp
*
******************************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {
	   int inxUsuario  = -1,
		   numLidos   = -1,
		   CondRetEsp = -1,
		   tipo = -1,
		   op;


	   TST_tpCondRet CondRet ;
	   char   id[  DIM_VALOR ] ;
	   char   nome[  DIM_VALOR ];
	   char   email[  DIM_VALOR ];
	   char   dtnasc[  DIM_VALOR ];
	   char   cidade[  DIM_VALOR ];
	   char   mudanca[  DIM_VALOR ] ;

	   int i;
	   
	  /* Efetuar reset de teste de usuario */

         if ( strcmp( ComandoTeste , RESET_USUARIO_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_USUARIO ; i++ )
            {
               vtUsuario[i] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de usuario */
		       
		 /* Testar CriarUsuario */

          if ( strcmp( ComandoTeste , CRIAR_USUARIO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isssss" ,
                       &inxUsuario,&id,&nome,&email,&dtnasc,&cidade ) ;

            if ( ( numLidos != 6 )
              || ( ! ValidarInxUsuario( inxUsuario , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            vtUsuario[ inxUsuario ] =
                 USU_CriarUsuario(id,nome,email,dtnasc,cidade ) ;

            return TST_CompararPonteiroNulo( 1 , vtUsuario[ inxUsuario ] ,
               "Erro em ponteiro de novo usuario."  ) ;


         } /* fim ativa: Testar CriarUsuario */
		 
		 /* Testar ExcluirUsuario */

         else if ( strcmp( ComandoTeste , EXCLUIR_USUARIO_CMD) == 0 )
         {

           numLidos = LER_LerParametros( "ii" ,
                       &inxUsuario, &CondRetEsp ) ;

            if ( ( numLidos != 2)
              || ( ValidarInxUsuario( inxUsuario , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet  = (TST_tpCondRet)  USU_ExcluirUsuario( vtUsuario[ inxUsuario ]) ;

            return TST_CompararInt( CondRetEsp , CondRet ,
               "Condicao de retorno errada excluir usuario"  ) ;

         } /* fim ativa: Testar destruir usuario*/
		
		  /* Testar Altera Usu�rio */

         else if ( strcmp( ComandoTeste , ALT_USUARIO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iisi" ,
                       &inxUsuario ,&op,&mudanca,&CondRetEsp ) ;
			
			if ( ( numLidos != 4 ) )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRet = (TST_tpCondRet) USU_AlterarUsuario(vtUsuario[inxUsuario],op,mudanca);

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao alterar usuario") ;

         } /* fim ativa: Testar Altera Usuario */

		 /* Testar Preencher Dados */

         else if ( strcmp( ComandoTeste , PREEN_DADOS_USU_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "issssi" ,
                       &inxUsuario ,nome,email,dtnasc,cidade,&CondRetEsp ) ;
			
			if ( ( numLidos != 6 ))
            {
               return TST_CondRetParm ;
            } /* if */

			CondRet = (TST_tpCondRet) USU_PreencheDadosUsuario(vtUsuario[inxUsuario],nome,email,dtnasc,cidade);

           return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao preencher dados") ;
			

         } /* fim ativa: Testar Preenche Dados */

		/* Testar Obter Lista Msgs */

		 else if ( strcmp( ComandoTeste , OBTER_MSGS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
                       &inxUsuario,&tipo,&CondRetEsp ) ;
			
			if ( ( numLidos != 3 ) 
              || ( ValidarInxUsuario( inxUsuario , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

			vtMensagem[ inxUsuario ] = (MEN_tppMensagem) USU_ObterListaMsgs(vtUsuario[inxUsuario], tipo);

			return TST_CompararPonteiroNulo( 1 , vtMensagem[ inxUsuario ] ,
               "Erro em ponteiro de mensagem."  ) ;
			
         } /* fim ativa: Obter Lista Msgs */

		 /* Testar Obter Id Usu�rio*/

		 else if ( strcmp( ComandoTeste , OBTER_ID_USU_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                       &inxUsuario, &CondRetEsp ) ;
			
			if ( ( numLidos != 2 ))
            {
               return TST_CondRetParm ;
            } /* if */

			CondRet = (TST_tpCondRet) USU_ObterIdUsuario(vtUsuario[inxUsuario], id);
			
           return TST_CompararInt( CondRetEsp , CondRet ,
                    "Condicao de retorno errada ao obter Id do Usuario") ;
			

         } /* fim ativa: Obter Id Usu�rio */
		 		 
		 /* Testar Checa Strings */

         else if ( strcmp( ComandoTeste , CHECA_STRING_CMD  ) == 0 )
         {
			  
            numLidos = LER_LerParametros( "si" ,
                       nome,&CondRetEsp ) ;
			
			if ( ( numLidos != 2 ))
            {
               return TST_CondRetParm ;
            } /* if */

			CondRet = (TST_tpCondRet) USU_ChecaString(nome);

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao checar string") ;

         } /* fim ativa: Checar string */

		 /* Testar Checa Email */

         else if ( strcmp( ComandoTeste , CHECA_EMAIL_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "si" ,
                       email,&CondRetEsp ) ;
			
			if ( ( numLidos != 2 ))
            {
               return TST_CondRetParm ;
            } /* if */

			CondRet = (TST_tpCondRet) USU_ChecaEmail(email);

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao checar email") ;

         } /* fim ativa: Checar email */

		  /* Testar Checa Data de nascimento */

         else if ( strcmp( ComandoTeste , CHECA_DATA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "si" ,
                       dtnasc,&CondRetEsp ) ;
			
			if ( ( numLidos != 2 ))
            {
               return TST_CondRetParm ;
            } /* if */

			CondRet = (TST_tpCondRet) USU_ChecaDtNasc(dtnasc);

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao checar data") ;

         } /* fim ativa: Checar data */
		 return TST_CondRetOK;
   }
/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TUSU -Validar indice de usuario
*
***********************************************************************/

   int ValidarInxUsuario (int inxUsuario, int Modo )
   {

      if ( ( inxUsuario <  0 )
        || ( inxUsuario >= DIM_VT_USUARIO ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtUsuario[ inxUsuario ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtUsuario[ inxUsuario ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim fun��o: TUSU -Validar indice de usuario */
/********** Fim do m�dulo de implementa��o: TUSU Teste usu�rio de s�mbolos **********/