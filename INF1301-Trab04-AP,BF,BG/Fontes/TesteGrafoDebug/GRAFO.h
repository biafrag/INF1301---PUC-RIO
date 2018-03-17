#if ! defined( GRAFO_ )
#define GRAFO_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: GRA  Grafo N�o Dirigido Gen�rico com Cabe�a
*
*  Arquivo gerado:             GRAFO.h
*  Letras identificadoras:      GRA
*
*  Projeto: T4 INF 1301 2017.2
*  Autores: ap - Andr� Pessanha
*           bg - Bianca Gomes
*           bf - Bianca Fragoso
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data       Observa��es
*     7       ap      04/nov/2017 Cria��o de novas fun��es
*     6       ap      29/out/2017 altera��o no m�dulo para que grafo tivesse um identificador
*     5       bg      16/out/2017 continua��o e altera��o de script de testes e de m�dulo testador
*     4      bg,bf    01/fev/2006 criar linguagem script simb�lica
*     3     ap,bg,bf  08/dez/2004 revis�o do c�digo
*     2       bf      07/out/2017 continua��o do desenvolvimento e documenta��o
*     1       ap      13/out/2017 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Implementa grafos  n�o dirigidos e gen�ricos com cabe�a.
*     Podem existir n grafos em opera��o simultaneamente.
*     Os grafos possuem uma cabe�a encapsulando o seu estado.
*
*     Cada grafo � homog�neo quanto ao tipo dos dados que armazena.
*     Cada elemento do grafo referencia o valor que cont�m. //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*
*     Os ponteiros para os dados s�o copiados para elementos do grafo.
*        N�o � copiado o valor apontado por estes ponteiros.
*
*     O controle da destrui��o do valor de um elemento a ser exclu�do
*        � realizado por uma fun��o fornecida pelo usu�rio.
*
*     Cada grafo referencia uma fun��o que determina como devem ser
*        desalocados os dados nele contidos.
*
*     A fun��o de libera��o dos valores contidos nos elementos deve
*        assegurar a libera��o de todos os espa�os refer�nciados pelo
*        valor contido em um elemento.
*        Esta fun��o � chamada antes de se desalocar um elemento
*        de um grafo.
*        Caso n�o seja necess�rio desalocar o valor referenciado pelo
*        elemento, o ponteiro para a fun��o de libera��o poder� ser NULL .
*        Caso o elemento do grafo seja a �nica �ncora do valor referenciado,
*        esta fun��o deve promover a destrui��o (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( GRAFO_OWN )
   #define GRAFO_EXT
#else
   #define GRAFO_EXT extern
#endif
#include "LISTA.h"
/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para um Grafo */

typedef struct GRA_tagGrafo* GRA_tppGrafo ;
typedef struct GRA_tagVerticeGrafo* GRA_tppVerticeGrafo ;


/***********************************************************************
*
*  $TC Tipo de dados: GRA Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es do Grafo
*
***********************************************************************/

   typedef enum {

         GRA_CondRetOK ,
               /* Concluiu corretamente */
         GRA_CondRetGrafoNExiste ,
               /* O grafo n�o foi criado */
         GRA_CondRetGrafoVazio ,
               /* O grafo n�o cont�m elementos */
         GRA_CondRetVerticeNExiste ,
               /* N�o encontrou o vertice procurado */
        GRA_CondRetArestaNExiste ,
               /* N�o encontrou a aresta procurada */
		GRA_CondRetArestaExiste ,   
			   /* A aresta j� existe */
        GRA_CondRetFaltouMemoria,
               /* Faltou mem�ria ao tentar criar um elemento do grafo */
	    GRA_CondRetFimGrafo,
			  /* Foi atingido o fim do Grafo */
		GRA_CondRetErroEstrutura 
			 /* Estrutura do Grafo est� errada */
   } GRA_tpCondRet ;


/***********************************************************************
*
*  $TC Tipo de dados: GRA Modos de deturpar
*
***********************************************************************/

#ifdef _DEBUG

   typedef enum {

         DeturpaQtdVert					  =  1 ,
               /* Alterar a quantidade total de v�rtices. */

         DeturpaVertCorrenteNulo          =  2 ,
               /* Torna ponteiro v�rtice corrente nulo */

         DeturpaLisVertNulo               =  3 ,
               /*  Torna ponteiro lista vertices nulo */

         DeturpaCabecaNulo                 =  4 ,
               /* Torna ponteiro da cabe�a do Grafo nulo */

         DeturpaValorVertCorrenteNulo      =  5 ,
               /* Torna ponteiro valor do v�rtice corrente nulo */

         DeturpaEspacoCabeca               =  6 ,
               /*  Modifica o tipo cabe�a do Grafo */

         DeturpaEspacoVerticeCorrente      =  7 ,
               /* Modifica o tipo do v�rtice corrente */

         DeturpaTamCabeca				   =  8 ,
               /*  Altera o tamanho da cabe�a do Grafo */

         DeturpaTamVerticeCorrente         =  9 ,
               /*Altera o tamanho do v�rtice corrente */

         DeturpaPtCabecaNulo               = 10
               /* Anula ponteiro cabe�a */


   } GRA_tpModosDeturpacao ;

#endif


/***********************************************************************
*
*  $FC Fun��o: GRA  &Criar grafo
*
*  $ED Descri��o da fun��o
*     Cria um grafo n�o dirigido gen�rico com cabe�a.
*     Os poss�veis tipos s�o desconhecidos a priori.
*     A tipagem � implicita.
*     N�o existe identificador de tipo associado ao grafo.
*
*  $EP Par�metros
*     ExcluirValor  - ponteiro para a fun��o que processa a
*                     exclus�o do valor referenciado pelo elemento
*                     a ser exclu�do.
*                     Ver descri��o do m�dulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para o grafo.
*     Este ponteiro ser� utilizado pelas fun��es que manipulem o grafo.
*     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*     a fun��o retornar� NULL.
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
***********************************************************************/

   GRA_tppGrafo GRA_CriarGrafo(
             void   ( * ExcluirValor ) ( void * pDado ) ) ;


/***********************************************************************
*
*  $FC Fun��o: GRA  &Destruir grafo
*
*  $ED Descri��o da fun��o
*     Destr�i o grafo fornecido.
*     O par�metro ponteiro para o grafo n�o � modificado.
*     Se ocorrer algum erro durante a destrui��o, o grafo resultar�
*     estruturalmente incorreta.
*     OBS: N�o existe previs�o para poss�veis falhas de execu��o.
*
*  $FV Valor retornado
*     NULL  - O Grafo n�o existe.
*			- Grafo existe e foi destru�do com sucesso.
*
***********************************************************************/

void * GRA_DestruirGrafo( GRA_tppGrafo pGrafo );


/***********************************************************************
*
*  $FC Fun��o: GRA &Esvaziar grafo
*
*  $ED Descri��o da fun��o
*     Elimina todos os elementos, sem contudo destruir o grafo
*
*  $EP Par�metros
*     pGrafo - ponteiro para o grafo a ser esvaziado
*
*  $FV Valor retornado
*     GRA_CondRetOK           - O Grafo foi esvaziado com sucesso.
*	  GRA_CondRetGrafoNExiste - O Grafo n�o foi criado.
*	  GRA_CondRetGrafoVazio   - O Grafo est� vazio.
*
***********************************************************************/

   GRA_tpCondRet GRA_EsvaziarGrafo(GRA_tppGrafo pGrafo );


/***********************************************************************
*
*  $FC Fun��o: GRA  &Inserir v�rtice
*
*  $ED Descri��o da fun��o
*     Insere novo v�rtice no grafo
*     Caso o grafo esteja vazio, insere o primeiro elemento do grafo.
*
*  $EP Par�metros
*     pGrafo - ponteiro para o grafo onde deve ser inserido o elemento
*     pValor - ponteiro para o valor do novo v�rtice
*              Pode ser NULL
*	  id     - Ponteiro para o valor corresponde ao ID do v�rtice a ser inserido.
*
*  $FV Valor retornado
*     GRA_CondRetOK            - Novo v�rtice inserido no Grafo com sucesso.
*	  GRA_CondRetGrafoNExiste  - Grafo n�o foi criado.
*     GRA_CondRetFaltouMemoria - N�o tinha mem�ria para que v�rtice fosse inserido e o grafo continua da mesma forma
*
***********************************************************************/

   GRA_tpCondRet GRA_InserirVertice( GRA_tppGrafo pGrafo ,void * pValor, void *id);

/***********************************************************************
*
*  $FC Fun��o: GRA  &Inserir aresta no vertice corrente
*
*  $ED Descri��o da fun��o
*     Insere nova aresta entre o vertice corrente e outro vertice dado
*
*  $EP Par�metros
*     Par�metros
*       pGrafo - ponteiro para o grafo onde deve ser inserido o elemento
*       Vertice - ponteiro para o vertice que se quer fazer uma aresta com o vertice corrente
*     
*  $FV Valor retornado
*        GRA_CondRetOK - conseguiu inserir aresta corretamente
*        GRA_CondRetFaltouMemoria - Faltou mem�ria para que aresta fosse inserida e o grafo n�o muda
*	     GRA_CondRetVerticeNExiste - V�rtice n�o existe, grafo n�o � alterado.
*	     GRA_CondRetArestaExiste   - Aresta j� existe, grafo n�o � alterado.
*
***********************************************************************/
 
  GRA_tpCondRet GRA_InserirArestaCorrente( GRA_tppGrafo pGrafo ,void* pValor);

/***********************************************************************
*
*  $FC Fun��o: GRA  &Excluir vertice corrente
*
*  $ED Descri��o da fun��o
*     Exclui o vertice corrente do grafo dado.
*     O primeiro elemento da lista de v�rtices ser� o novo corrente.
*	  Ap�s exclus�o o n�mero de v�rtices do grafo ser� reduzida em uma unidade.
*     Se a quantidade de v�rtices do grafo � zero, ent�o o grafo tornou-se vazio.
*
*  $EP Par�metros
*     pGrafo - ponteiro para o grafo na qual deve excluir o v�rtice corrente.
*
*  $FV Valor retornado
*     GRA_CondRetOK - Conseguiu excluir v�rtice corretamente
*	  GRA_CondRetGrafoNExiste - O grafo n�o existe.
*     GRA_CondRetGrafoVazio - Grafo ainda estava vazio e n�o tinha v�rtices para excluir,logo, o grafo n�o � alterado
*
***********************************************************************/

   GRA_tpCondRet GRA_ExcluiVerticeCorrente( GRA_tppGrafo pGrafo ) ;

/***********************************************************************
*
*  $FC Fun��o: GRA  &Excluir aresta
*
*  $ED Descri��o da fun��o
*     Exclui uma aresta entre dois v�rtices.
*
*  $EP Par�metros
*     pGrafo    - ponteiro para o grafo na qual deve excluir a aresta.
*     pValor1  - ponteiro para o v�rtice que faz a aresta com o vertice2
*	  pValor2  - ponteiro para o v�rtice que faz a aresta com o vertice1
*
*  $FV Valor retornado
*     GRA_CondRetOK - conseguiu excluir aresta corretamente
*     GRA_CondRetGrafoVazio - grafo n�o possui arestas para excluir pois est� vazio, grafo n�o � alterado
*	  GRA_CondRetVerticeNExiste - Algum dos v�rtices recebidos por par�metro n�o existe, grafo n�o � alterado
*     GRA_CondRetArestaNExiste - grafo n�o possui a aresta desejada para exclus�o, grafo n�o � alterado
*
***********************************************************************/

   GRA_tpCondRet GRA_ExcluirAresta( GRA_tppGrafo pGrafo, void* pValor, void* pValor2 );

/***********************************************************************
*  $FC Fun��o: GRA  &Obter refer�ncia para o valor contido no v�rtice 
*
*  $ED Descri��o da fun��o
*     Obtem a refer�ncia para o valor contido no v�rtice corrente do grafo
*
*  $EP Par�metros
*     pGrafo - ponteiro para o grafo de onde se quer o valor
*
*  $FV Valor retornado
*    pValor - Ponteiro para o valor contido no v�rtice corrente do Grafo.
*	 NULL - O grafo n�o foi criado ou est� vazio.	
*
************************************************************************/

  void * GRA_ObterValorCorrente( GRA_tppGrafo pGrafo );

/***********************************************************************
*  $FC Fun��o: GRA  &Obtem Arestas do v�rtice Corrente 
*
*  $ED Descri��o da fun��o
*     Obtem a refer�ncia para as arestas do v�rtice corrente.
*
*  $EP Par�metros
*     pGrafo - ponteiro para o grafo de onde se quer o valor
*
*  $FV Valor retornado
*    pValor - Ponteiro para as arestas do v�rtice corrente do Grafo.
*	 NULL - O grafo n�o foi criado ou est� vazio.	
*
************************************************************************/

  void * GRA_ObtemArestasVerticeCorrente( GRA_tppGrafo pGrafo );

/***********************************************************************
*  $FC Fun��o: GRA  &Verifica Vertice Existe
*
*  $ED Descri��o da fun��o
*     Verifica se um v�rtice existe no grafo a partir de seu ID
*
*  $EP Par�metros
*     id - Ponteiro para o valor do ID do v�rtice.
*     
*  $FV Valor retornado
*    GRA_CondRetOK - O v�rtice correspondente ao ID recebido no par�metro existe.
*	 GRA_CondRetGrafoNExiste - Grafo n�o foi criado.
*	 GRA_CondRetVerticeNExiste - O v�rtice correspondente ao ID recebido no par�metro n�o existe.
*
************************************************************************/

  GRA_tpCondRet GRA_VerificaVerticeExiste( GRA_tppGrafo pGrafo, void *id);

/***********************************************************************
*  $FC Fun��o: GRA  &Avan�ar V�rtice Corrente
*
*  $ED Descri��o da fun��o
*     Avan�a o v�rtice corrente em uma unidade.
*
*  $EP Par�metros
*     pGrafo - Ponteiro para o grafo.
*     
*  $FV Valor retornado
*    GRA_CondRetOK - Avan�ou para o pr�ximo v�rtice com sucesso.
*	 GRA_CondRetGrafoVazio - Grafo n�o possui v�rtices.
*	 GRA_CondRetFimGrafo -  O Grafo n�o possui mais v�rtices.
*
************************************************************************/

  GRA_tpCondRet GRA_AvancarVerticeCorrente( GRA_tppGrafo pGrafo);

/***********************************************************************
*  $FC Fun��o: GRA  &Ir Inicio
*
*  $ED Descri��o da fun��o
*     Torna corrente o primeiro v�rtice do grafo.
*   
*  $EP Par�metros
*     pGrafo - ponteiro para o grafo a manipular
* 
*   $FV Valor retornado
*     GRA_CondRetOK - Vertice corrente agora aponta para o primeiro v�rtice do Grafo
*	  GRA_CondRetGrafoNExiste - O Grafo n�o foi criado.
*     GRA_CondRetGrafoVazio - O Grafo est� vazio. N�o possui v�rtices.
*
***********************************************************************/

	 GRA_tpCondRet GRA_IrInicio (GRA_tppGrafo pGrafo) ;

/***********************************************************************
*
*  $FC Fun��o: GRA Verificar Grafo
*
*  $ED Descri��o da fun��o
*		Verifica a estrutura Grafo, contabilizando o total de erros encontrados.
*
*  $EP Par�metros
*     $P pGrafo - ponteiro para o grafo a ser verificado.
*     $P qtdErros - ponteiro para inteiro que ser� atualizado com a quantidade total de erros.
*
*  $FV Valor retornado
*     GRA_CondRetOK - Executou corretamente e atualizou o contador de erros.
*     GRA_CondRetErroEstrutura - Detectou erros na estrutura do v�rtice do Grafo.
*
***********************************************************************/

#ifdef _DEBUG
   GRA_tpCondRet GRA_VerificarGrafo( GRA_tppGrafo pGrafo, int * qtdErros );
#endif

/***********************************************************************
*
*  $FC Fun��o: GRA  &Verificar um v�rtice do Grafo
*
*  $ED Descri��o da fun��o
*     Fun��o da interface de teste.
*     Verifica a integridade de um v�rtice estrutural do Grafo.
*
*  $EP Par�metros
*     $P pVerticeParm - ponteiro para espa�o que deveria ser um V�rtice estrutural.
*     $P qtdErros - ponteiro para inteiro que ser� atualizado com a quantidade total de erros.
*	  $P tamValor - Ponteiro a ser atualizado com o tamanho em bytes do v�rtice.
*
*  $FV Valor retornado
*     GRA_CondRetOK - Executou corretamente e atualizou o contador de erros.
*     GRA_CondRetErroEstrutura - Detectou erros na estrutura do v�rtice do Grafo.
*
***********************************************************************/

#ifdef _DEBUG
   GRA_tpCondRet GRA_VerificarVertice( void * pVerticeParm, int *qtdErros, int *tamValor );
#endif

/***********************************************************************
*
*  $FC Fun��o: GRA  &Verificar Cabe�a do Grafo
*
*  $ED Descri��o da fun��o
*     Fun��o da interface de teste.
*     Verifica a integridade da cabe�a do Grafo.
*
*  $EP Par�metros
*     $P pCabecaParm - ponteiro para um espa�o que deveria ser uma cabe�a
*                      de Grafo.
*	  $P qtdErros - ponteiro para inteiro que ser� atualizado com a quantidade total de erros.
*
*  $FV Valor retornado
*     Condi��o de retorno de teste
*
***********************************************************************/

#ifdef _DEBUG
   GRA_tpCondRet GRA_VerificarCabecaGrafo( void * pCabecaParm, int * qtdErros );
#endif

/***********************************************************************
*
*  $FC Fun��o: GRA &Deturpar Grafo
*
*  $ED Descri��o da fun��o
*		Fun��o da interface de teste. Corrompe elementos espec�ficos da estrutura do Grafo
*		de acordo com o tipo fornecido.
*		Essa fun��o destina-se a preparar os cen�rios de teste dos
*		casos de teste utilizados ao testar os verificadores estruturais
*		do Grafo.
*
*  $EP Par�metros
*     $P pGrafo -  Ponteiro para o grafo a ser deturpado.
*     $P tipo   -  Indica o tipo de deturpacao a ser realizado:
*			1  - Altera a quantidade total de v�rtices.
*			2  - Torna ponteiro v�rtice corrente nulo
*			3  - Altera o tipo cabe�a do Grafo
*			4  - Altera o tipo do v�rtice corrente
*
***********************************************************************/

#ifdef _DEBUG
   void GRA_Deturpar( GRA_tppGrafo pGrafo, GRA_tpModosDeturpacao tipo);
#endif

/***********************************************************************
*
*  $FC Fun��o: GRA &Corrige Quantidade de v�rtices
*
*  $ED Descri��o da fun��o
*		Fun��o de recupera��o de estado inconsitente do Grafo.
*	    Corrige a quantidade total de v�rtices do Grafo.
*
*  $EP Par�metros
*     $P pGrafo -  Ponteiro para o grafo a ser corrigido.
* 
*  $FV Valor retornado
*     GRA_CondRetOK - Executou corretamente e corrigiu a exce��o.
*
***********************************************************************/

#ifdef _DEBUG
   GRA_tpCondRet GRA_CorrigeQuantidadeVertices( GRA_tppGrafo pGrafo) ;
#endif

/***********************************************************************/

#undef GRAFO_EXT

#undef GRA_EXT

/********** Fim do m�dulo de defini��o: GRA  Grafo N�o Dirigido Gen�rico com Cabe�a **********/

#else
#endif