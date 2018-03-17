/**********************************************************************************
*  $MCI Módulo de implementação: TGRA Teste Grafo de símbolos
*
*  Arquivo gerado:              TestGRA.c
*  Letras identificadoras:      TGRA
*
*  Projeto: T2 INF 1301 2017.2
*  Autores: ap - André Pessanha
*           bg - Bianca Gomes
*           bf - Bianca Fragoso
*
*
***********************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_ESPC.H"

#include    "GENERICO.H"
#include    "LERPARM.H"

#include    "GRAFO.h"
#include    "LISTA.h"


static const char RESET_GRAFO_CMD         [ ] = "=resetteste"     ;
static const char CRIAR_GRAFO_CMD         [ ] = "=criargrafo"     ;
static const char ESVAZIAR_GRAFO_CMD      [ ] = "=esvaziargrafo"  ;
static const char DESTRUIR_GRAFO_CMD      [ ] = "=destruirgrafo"  ;
static const char INS_VERTICE_CMD         [ ] = "=insevertice"   ;
static const char INS_ARESTCORR_CMD       [ ] = "=insearestcorr" ;
static const char EXC_VERTCORR_CMD        [ ] = "=excluirvertcorr";
static const char EXC_AREST_CMD           [ ] = "=excluirarest";
static const char OBTER_VALORCORR_CMD     [ ] = "=obtervalorcorr" ;
//Novas
static const char VERIF_VERTICE_CMD       [ ] = "=verifvertice" ;  
static const char AVA_VERTCORR_CMD        [ ] = "=avancarvertcorr" ;
static const char IR_INICIO_CMD			  [ ] = "=irinicio" ;  
static const char OBTEM_ARESCORR_CMD      [ ] = "=obtemarestcorr" ;   

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_GRAFO   10
#define DIM_VT_VERTICE 30
#define DIM_VALOR     100

GRA_tppGrafo   vtGrafo[ DIM_VT_GRAFO ] ;

/***** Estrutura para Teste *****/
typedef struct Teste {
	    char id[51];
        char nome[11] ;
		char data[51] ;
		char email[51] ;
		char cidade[51] ;

} tpInfo ;

tpInfo*  vtVertice[ DIM_VT_VERTICE ] ;
char *  vtIds[ DIM_VT_VERTICE ] ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirValor( void * pValor ) ; 

   static int ValidarInxGrafo( int inxGrafo) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TGRA &Testar Grafo
*
*  $ED Descrição da função
*     Podem ser criadas até 10 grafos, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de grafos. Provoca vazamento de memória
*     =criargrafo                   inxGrafo 
*     =destruirgrafo                inxGrafo  CondRetEsp
*     =insevertice                  inxGrafo  string  string  string  string  CondRetEsp
*     =insearestcorr                inxGrafo  vert  CondRetEsp
*	  =excluirvertcorr              inxGrafo  CondRetEsp
*	  =excluirarest                 inxGrafo  vert vert CondRetEsp
*     =obtervalorcorr               inxGrafo  string  string  string  string  CondRetEsp  
*
******************************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {
	   int inxGrafo  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1 ,
		  inxVertice = -1 ,
		  inxVertice2 = -1,
		  inxIds = -1 ;

     TST_tpCondRet CondRet ;
	  char   String1[  DIM_VALOR ] ;
	  char   String2[  DIM_VALOR ];
	  char   String3[  DIM_VALOR ];
	  char   String4[  DIM_VALOR ];
	  char   id[  DIM_VALOR ];
	  char   id2[  DIM_VALOR ];
	  void *pCondRet;

     tpInfo * pDado ;
	 int i;
	 int ValEsp=-1;
	  /* Efetuar reset de teste de grafo */

         if ( strcmp( ComandoTeste , RESET_GRAFO_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_GRAFO ; i++ )
            {
               vtGrafo[i] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de grafo */
		       
		 /* Testar CriarGrafo */

          if ( strcmp( ComandoTeste , CRIAR_GRAFO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &inxGrafo ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxGrafo( inxGrafo, VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            vtGrafo[ inxGrafo ] = GRA_CriarGrafo( DestruirValor ) ;

            return TST_CompararPonteiroNulo( NAO_VAZIO , vtGrafo[ inxGrafo ] ,
               "Erro em ponteiro de novo grafo."  ) ;

         } /* fim ativa: Testar CriarGrafo */
		 
		 /* Testar inserir Vertice */

         else if ( strcmp( ComandoTeste , INS_VERTICE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isssssii" ,
                       &inxGrafo , id, String1,String2 ,String3,String4,&inxVertice, &CondRetEsp ) ;
			
			if ( ( numLidos != 8 ))
				//|| ( ValidarInxGrafo( inxGrafo, VAZIO)) )
            {
               return TST_CondRetParm ;
            } /* if */
           pDado = (tpInfo*) malloc(sizeof(tpInfo));
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */
			strcpy(pDado->id,id);
            strcpy(pDado->nome,String1);
	        strcpy(pDado->cidade,String2);
	        strcpy(pDado->data,String3);
	        strcpy(pDado->email,String4);
			vtVertice[inxVertice] = pDado;
			//vtIds[inxIds] = id;
			//CondRet = TST_CompararString( id  ,vtIds[inxIds],
                         //"teste=Valor do id errado." ) ;
			//printf("\n Teste:: %s\n",vtIds[inxIds]);
            CondRet = ( TST_tpCondRet) GRA_InserirVertice( vtGrafo[ inxGrafo ] , vtVertice[inxVertice],id ) ;
			
            if ( CondRet != GRA_CondRetOK )
            {
               free( pDado ) ;
            } /* if */

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao inserir vertice.") ;

         } /* fim ativa: Testar inserir vertice */
		 
		  /* Testar Verifica Vertice Existente */

         else if ( strcmp( ComandoTeste , VERIF_VERTICE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxGrafo ,id, &CondRetEsp ) ;
			
			if ( ( numLidos != 3 ))
              //|| ( ValidarInxGrafo( inxGrafo, VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */
			//printf("\nComparando\n TestevtIds:: %s\n",vtIds[inxIds]);
			//printf("\n TesteId:: %s\n",id);
			//CondRet = TST_CompararString( id  ,vtIds[inxIds],
              //           "teste=Valor do id errado." ) ;

			CondRet = ( TST_tpCondRet)GRA_VerificaVerticeExiste(vtGrafo[ inxGrafo ], vtIds[inxIds]);
			printf("\n TesteId:: %s\n",id);
            printf("\nComparando\n TestevtIds:: %s\n",vtIds[inxIds]);
            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao verificar vertice existe.") ;

         } /* fim ativa: Testar verificar vertice existente*/

		/* Testar obter valor de vertice corrente em Grafo */
        else if ( strcmp( ComandoTeste , OBTER_VALORCORR_CMD ) == 0 ) {

            numLidos = LER_LerParametros( "isssssi" , 
				&inxGrafo, id, String1,String2 ,String3,String4,  &ValEsp ) ;
			//printf("\n\nTESTE NUM LIDOS: %d e INXGRAFO: %d\n\n", numLidos, inxGrafo);
            if ( ( numLidos != 7 ) )
				//|| ( ValidarInxGrafo( inxGrafo, VAZIO ) ) )
            {
               return TST_CondRetParm ;
            } /* if */

			pDado = ( tpInfo *)  GRA_ObterValorCorrente( vtGrafo[ inxGrafo ]) ;
					 
		 if ( ValEsp == 0 )
            {
               return TST_CompararPonteiroNulo( 0 , pDado ,
                         "Valor não deveria existir." ) ;
            } /* if */

            if ( pDado == NULL )
            {
               return TST_CompararPonteiroNulo( 1 , pDado ,
                         "Dado tipo um deveria existir." ) ;
            } /* if */
		    
			CondRet = TST_CompararString( id , pDado->id ,
                         "Valor do id errado." ) ;

			CondRet = TST_CompararString( String1 , pDado->nome ,
                         "Valor do nome errado." ) ;
			CondRet = TST_CompararString( String2 , pDado->cidade,
                         "Valor da cidade errado." ) ;
			CondRet = TST_CompararString( String3 , pDado->data ,
                         "Valor da data errado." ) ;
			CondRet = TST_CompararString( String4 , pDado->email ,
                         "Valor do email errado." ) ;
	
			return CondRet;

        } /* fim ativa: Testar obter valor de vertice corrente em Grafo */

          else if ( strcmp( ComandoTeste ,DESTRUIR_GRAFO_CMD  ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &inxGrafo, &CondRetEsp ) ;
			
            if ( ( numLidos != 2))
              //|| ( ValidarInxGrafo( inxGrafo, VAZIO)))
            {
               return TST_CondRetParm ;
            } /* if */

            vtGrafo[ inxGrafo ] = (GRA_tppGrafo) GRA_DestruirGrafo( vtGrafo[ inxGrafo ]) ;

           return TST_CompararPonteiroNulo( CondRetEsp , vtGrafo[ inxGrafo ] ,
               "Erro grafo nao eh null."  ) ;

         } /* fim ativa: Testar destruir grafo*/

		else if ( strcmp( ComandoTeste ,ESVAZIAR_GRAFO_CMD  ) == 0 )
         {
            numLidos = LER_LerParametros( "ii" , &inxGrafo, &CondRetEsp ) ;
			
            if ( ( numLidos != 2))
              //|| ( ValidarInxGrafo( inxGrafo, VAZIO)))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = (TST_tpCondRet) GRA_EsvaziarGrafo( vtGrafo[ inxGrafo ]) ;  

           return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao esvaziar grafo.") ;

         } /* fim ativa: Testar esvaziar grafo*/
		          	
		/* Testar Insere Aresta em Vertice Corrente */  
		else if ( strcmp( ComandoTeste, INS_ARESTCORR_CMD ) == 0 ) {

			 numLidos = LER_LerParametros( "isi" ,
                       &inxGrafo ,id, &CondRetEsp ) ;
			
			 if ( ( numLidos != 3 ) )
				 //|| ( ValidarInxGrafo( inxGrafo, VAZIO) ) )
            {
               return TST_CondRetParm ;
            } /* if */
			/*
			pDado = (tpInfo*) malloc(sizeof(tpInfo));
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } 
			
			strcpy(pDado->id,id);
            strcpy(pDado->nome,String1);
	        strcpy(pDado->cidade,String2);
	        strcpy(pDado->data,String3);
	        strcpy(pDado->email,String4);
			vtVertice[inxVertice] = pDado;
			*/
			CondRet = (TST_tpCondRet) GRA_InserirArestaCorrente(vtGrafo[inxGrafo], id);

			return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao inserir aresta.") ;
		}/* Fim da Insere Aresta Corrente*/

		/* Testar Excluir Aresta */
		else if ( strcmp( ComandoTeste, EXC_AREST_CMD ) == 0 ) { 
			
			numLidos = LER_LerParametros( "issi" , &inxGrafo, id , id2 ,  &CondRetEsp) ;
			
			 if ( ( numLidos != 4 ))
				 //|| ( ValidarInxGrafo( inxGrafo, VAZIO ) ) )
            {
               return TST_CondRetParm ;
            } /* if */   

			CondRet = (TST_tpCondRet) GRA_ExcluirAresta( vtGrafo[inxGrafo], id , id2);

			return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao excluir aresta.") ;
		}/*Fim da Testar Exluir Aresta Corrente*/

		/* Testar excluir vertice corrente em Grafo */
        else if ( strcmp( ComandoTeste ,  EXC_VERTCORR_CMD   ) == 0 ) { 

            numLidos = LER_LerParametros( "ii" , &inxGrafo,  &CondRetEsp) ;

            if ( ( numLidos != 2 ))
				//|| ( ValidarInxGrafo( inxGrafo, VAZIO ) ) )
            {
               return TST_CondRetParm ;
            } /* if */
           
            CondRet = ( TST_tpCondRet) GRA_ExcluiVerticeCorrente( vtGrafo[ inxGrafo ] );

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao excluir vertice corrente."  ) ;

        } /* fim ativa: Testar excluir vertice corrente em Grafo */

		/*Testar Ir Inicio do Grafo */
		else if(  strcmp( ComandoTeste , IR_INICIO_CMD  ) == 0) {

			numLidos = LER_LerParametros( "ii" , &inxGrafo,  &CondRetEsp) ;
			if ( ( numLidos != 2 ))
				//|| ( ValidarInxGrafo( inxGrafo, VAZIO) ) )
			{
               return TST_CondRetParm ;
            } /* if */

			CondRet = ( TST_tpCondRet) GRA_IrInicio( vtGrafo[ inxGrafo ] );

			return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao ir inicio Grafo."  ) ;

        } /* fim ativa: Testar Ir Inicio Grafo */

		/*Testar Avançar Vértice Corrente */
		else if(  strcmp( ComandoTeste , AVA_VERTCORR_CMD  ) == 0) {

			numLidos = LER_LerParametros( "ii" , &inxGrafo,  &CondRetEsp) ;
			if ( ( numLidos != 2 )) 
				//|| ( ValidarInxGrafo( inxGrafo, VAZIO ) ) )
			{
               return TST_CondRetParm ;
            } /* if */

			CondRet = ( TST_tpCondRet) GRA_AvancarVerticeCorrente( vtGrafo[ inxGrafo ] );

			return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao avancar vertice corrente."  ) ;

        } /* fim ativa: Testar Avançar Vértice Corrente */

		/*Testar Obter Aresta Vértice Corrente */
		else if(  strcmp( ComandoTeste , OBTEM_ARESCORR_CMD  ) == 0) {

			numLidos = LER_LerParametros( "ii" , &inxGrafo,  &CondRetEsp) ;
			
			if ( ( numLidos != 2 ) )
				//|| ( ValidarInxGrafo( inxGrafo, VAZIO ) ) )
			{
               return TST_CondRetParm ;
            } /* if */

			pCondRet = GRA_ObtemArestasVerticeCorrente( vtGrafo[ inxGrafo ] );

			return TST_CompararPonteiroNulo( CondRetEsp , pCondRet ,
               "Condicao de retorno errada ao obter aresta corrente."  ) ;

        } /* fim ativa: Testar Obter Aresta Vértice Corrente*/
		 
      return TST_CondRetOK;
   }


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TGRA -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {

      free( pValor ) ;

   } /* Fim função: TGRA-Destruir valor */


/***********************************************************************
*
*  $FC Função: TGRA -Validar indice de grafo
*
***********************************************************************/

   int ValidarInxGrafo( int inxGrafo, int Modo)
   {

      if ( ( inxGrafo <  0 ) || ( inxGrafo >= DIM_VT_GRAFO )){
         return FALSE ;
      } 
	   if ( Modo == VAZIO )
      {
         if ( vtGrafo[ inxGrafo ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtGrafo[ inxGrafo ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */

      return TRUE ;

   } /* Fim função: TGRA -Validar indice de grafo */

/********** Fim do módulo de implementação: TGRA Teste grafo de símbolos **********/