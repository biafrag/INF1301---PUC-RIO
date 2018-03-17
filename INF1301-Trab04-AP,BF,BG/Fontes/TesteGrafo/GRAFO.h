#if ! defined( GRAFO_ )
#define GRAFO_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: GRA  Grafo N�o Dirigido Gen�rico com Cabe�a
*
*  Arquivo gerado:             GRAFO.h
*  Letras identificadoras:      GRA
*
*  Projeto: T2 INF 1301 2017.2
*  Autores: ap - Andr� Pessanha
*           bg - Bianca Gomes
*           bf - Bianca Fragoso
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
typedef struct GRA_tagVerticeGrafo* GRA_tppVerticeGrafo; ;


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
        GRA_CondRetFaltouMemoria,
               /* Faltou mem�ria ao tentar criar um elemento do grafo */
	    GRA_CondRetArestaJaExiste
               /* Faltou mem�ria ao tentar criar um elemento do grafo */

   } GRA_tpCondRet ;


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
*     OBS. n�o existe previs�o para poss�veis falhas de execu��o.
*
*  $FV Valor retornado
*     NULL: - O Grafo n�o existe.
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
*     GRA_CondRetOK    - Esvaziou sem problemas
*	  GRA_CondRetGrafoNExiste - Grafo n�o foi criado.
*	  GRA_CondRetGrafoVazio - O grafo est� vazio.
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
*
*  $FV Valor retornado
*     GRA_CondRetOK - Conseguiu inserir sem problemas
*	  GRA_CondRetGrafoNExiste - Grafo n�o foi criado.
*     GRA_CondRetFaltouMemoria - N�o tinha mem�ria para que v�rtice fosse inserido e o grafo continua da mesma forma
*
***********************************************************************/

   GRA_tpCondRet GRA_InserirVertice( GRA_tppGrafo pGrafo ,void * pValor);

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
* 
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
	  GRA_CondRetVerticeNExiste - Algum dos v�rtices recebidos por par�metro n�o existe, grafo n�o � alterado
*     GRA_CondRetArestaNExiste - grafo n�o possui a aresta desejada para exclus�o, grafo n�o � alterado
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
*     pValor - Endere�o da Refer�ncia onde ser� armazenado o ponteiro para o valor contido no v�rtice
*
*  $FV Valor retornado
*    GRA_CondRetOK - Conseguiu obter refer�ncia para o valor contido no v�rtice corretamente.
*	 GRA_CondRetGrafoNExiste - Grafo n�o foi criado.
*	 GRA_CondRetGrafoVazio - O grafo est� vazio.	
*
************************************************************************/

  void * GRA_ObterValorCorrente( GRA_tppGrafo pGrafo );

/***********************************************************************
*
*  $FC Fun��o: GRA  &Ir para vertice desejado
*
*  $ED Descri��o da fun��o
*     Torna corrente o vertice do grafo que tem o valor recebido pela fun��o.
*   
*  $EP Par�metros
*     pGrafo - ponteiro para o grafo a manipular
*     pValor - valor do vertice que se quer encontrar
* 
*   $FV Valor retornado
*     GRA_CondRetOK - Vertice corrente agora aponta para v�rtice que possui o pValor
*     GRA_CondRetGrafoVazio - V�rtice desejado n�o foi encontrado pois grafo est� vazio
*     GRA_CondRetVerticeNExiste -  V�rtice desejado n�o foi encontrado pois ele n�o foi adicionado no grafo
*
*
***********************************************************************/

	  GRA_tpCondRet GRA_IrVertice( GRA_tppGrafo pGrafo,void * pValor) ;

/***********************************************************************

#undef GRA_EXT

/********** Fim do m�dulo de defini��o: GRA  Grafo N�o Dirigido Gen�rico com Cabe�a **********/

#else
#endif