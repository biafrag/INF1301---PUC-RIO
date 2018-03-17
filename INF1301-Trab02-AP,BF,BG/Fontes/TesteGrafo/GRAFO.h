#if ! defined( GRAFO_ )
#define GRAFO_
/***************************************************************************
*
*  $MCD Módulo de definição: GRA  Grafo Não Dirigido Genérico com Cabeça
*
*  Arquivo gerado:             GRAFO.h
*  Letras identificadoras:      GRA
*
*  Projeto: T2 INF 1301 2017.2
*  Autores: ap - André Pessanha
*           bg - Bianca Gomes
*           bf - Bianca Fragoso
*
*  $ED Descrição do módulo
*     Implementa grafos  não dirigidos e genéricos com cabeça.
*     Podem existir n grafos em operação simultaneamente.
*     Os grafos possuem uma cabeça encapsulando o seu estado.
*
*     Cada grafo é homogêneo quanto ao tipo dos dados que armazena.
*     Cada elemento do grafo referencia o valor que contém. //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*
*     Os ponteiros para os dados são copiados para elementos do grafo.
*        Não é copiado o valor apontado por estes ponteiros.
*
*     O controle da destruição do valor de um elemento a ser excluído
*        é realizado por uma função fornecida pelo usuário.
*
*     Cada grafo referencia uma função que determina como devem ser
*        desalocados os dados nele contidos.
*
*     A função de liberação dos valores contidos nos elementos deve
*        assegurar a liberação de todos os espaços referênciados pelo
*        valor contido em um elemento.
*        Esta função é chamada antes de se desalocar um elemento
*        de um grafo.
*        Caso não seja necessário desalocar o valor referenciado pelo
*        elemento, o ponteiro para a função de liberação poderá ser NULL .
*        Caso o elemento do grafo seja a única âncora do valor referenciado,
*        esta função deve promover a destruição (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( GRAFO_OWN )
   #define GRAFO_EXT
#else
   #define GRAFO_EXT extern
#endif
#include "LISTA.h"
/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um Grafo */

typedef struct GRA_tagGrafo* GRA_tppGrafo ;
typedef struct GRA_tagVerticeGrafo* GRA_tppVerticeGrafo; ;


/***********************************************************************
*
*  $TC Tipo de dados: GRA Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do Grafo
*
***********************************************************************/

   typedef enum {

         GRA_CondRetOK ,
               /* Concluiu corretamente */
         GRA_CondRetGrafoNExiste ,
               /* O grafo não foi criado */
         GRA_CondRetGrafoVazio ,
               /* O grafo não contém elementos */
         GRA_CondRetVerticeNExiste ,
               /* Não encontrou o vertice procurado */
        GRA_CondRetArestaNExiste ,
               /* Não encontrou a aresta procurada */
        GRA_CondRetFaltouMemoria,
               /* Faltou memória ao tentar criar um elemento do grafo */
	    GRA_CondRetArestaJaExiste
               /* Faltou memória ao tentar criar um elemento do grafo */

   } GRA_tpCondRet ;


/***********************************************************************
*
*  $FC Função: GRA  &Criar grafo
*
*  $ED Descrição da função
*     Cria um grafo não dirigido genérico com cabeça.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado ao grafo.
*
*  $EP Parâmetros
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para o grafo.
*     Este ponteiro será utilizado pelas funções que manipulem o grafo.
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
***********************************************************************/

   GRA_tppGrafo GRA_CriarGrafo(
             void   ( * ExcluirValor ) ( void * pDado ) ) ;


/***********************************************************************
*
*  $FC Função: GRA  &Destruir grafo
*
*  $ED Descrição da função
*     Destrói o grafo fornecido.
*     O parâmetro ponteiro para o grafo não é modificado.
*     Se ocorrer algum erro durante a destruição, o grafo resultará
*     estruturalmente incorreta.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  $FV Valor retornado
*     NULL: - O Grafo não existe.
*			- Grafo existe e foi destruído com sucesso.
*
***********************************************************************/

void * GRA_DestruirGrafo( GRA_tppGrafo pGrafo );


/***********************************************************************
*
*  $FC Função: GRA &Esvaziar grafo
*
*  $ED Descrição da função
*     Elimina todos os elementos, sem contudo destruir o grafo
*
*  $EP Parâmetros
*     pGrafo - ponteiro para o grafo a ser esvaziado
*
*  $FV Valor retornado
*     GRA_CondRetOK    - Esvaziou sem problemas
*	  GRA_CondRetGrafoNExiste - Grafo não foi criado.
*	  GRA_CondRetGrafoVazio - O grafo está vazio.
*
***********************************************************************/

   GRA_tpCondRet GRA_EsvaziarGrafo(GRA_tppGrafo pGrafo );


/***********************************************************************
*
*  $FC Função: GRA  &Inserir vértice
*
*  $ED Descrição da função
*     Insere novo vértice no grafo
*     Caso o grafo esteja vazio, insere o primeiro elemento do grafo.
*
*  $EP Parâmetros
*     pGrafo - ponteiro para o grafo onde deve ser inserido o elemento
*     pValor - ponteiro para o valor do novo vértice
*              Pode ser NULL
*
*  $FV Valor retornado
*     GRA_CondRetOK - Conseguiu inserir sem problemas
*	  GRA_CondRetGrafoNExiste - Grafo não foi criado.
*     GRA_CondRetFaltouMemoria - Não tinha memória para que vértice fosse inserido e o grafo continua da mesma forma
*
***********************************************************************/

   GRA_tpCondRet GRA_InserirVertice( GRA_tppGrafo pGrafo ,void * pValor);

/***********************************************************************
*
*  $FC Função: GRA  &Inserir aresta no vertice corrente
*
*  $ED Descrição da função
*     Insere nova aresta entre o vertice corrente e outro vertice dado
*
*  $EP Parâmetros
*     Parâmetros
*       pGrafo - ponteiro para o grafo onde deve ser inserido o elemento
*       Vertice - ponteiro para o vertice que se quer fazer uma aresta com o vertice corrente
*     
*  $FV Valor retornado
*        GRA_CondRetOK - conseguiu inserir aresta corretamente
*        GRA_CondRetFaltouMemoria - Faltou memória para que aresta fosse inserida e o grafo não muda
*	     GRA_CondRetVerticeNExiste - Vértice não existe, grafo não é alterado.
* 
*
***********************************************************************/
 
  GRA_tpCondRet GRA_InserirArestaCorrente( GRA_tppGrafo pGrafo ,void* pValor);

/***********************************************************************
*
*  $FC Função: GRA  &Excluir vertice corrente
*
*  $ED Descrição da função
*     Exclui o vertice corrente do grafo dado.
*     O primeiro elemento da lista de vértices será o novo corrente.
*	  Após exclusão o número de vértices do grafo será reduzida em uma unidade.
*     Se a quantidade de vértices do grafo é zero, então o grafo tornou-se vazio.
*
*  $EP Parâmetros
*     pGrafo - ponteiro para o grafo na qual deve excluir o vértice corrente.
*
*  $FV Valor retornado
*     GRA_CondRetOK - Conseguiu excluir vértice corretamente
*	  GRA_CondRetGrafoNExiste - O grafo não existe.
*     GRA_CondRetGrafoVazio - Grafo ainda estava vazio e não tinha vértices para excluir,logo, o grafo não é alterado
*
***********************************************************************/

   GRA_tpCondRet GRA_ExcluiVerticeCorrente( GRA_tppGrafo pGrafo ) ;

/***********************************************************************
*
*  $FC Função: GRA  &Excluir aresta
*
*  $ED Descrição da função
*     Exclui uma aresta entre dois vértices.
*
*  $EP Parâmetros
*     pGrafo    - ponteiro para o grafo na qual deve excluir a aresta.
*     pValor1  - ponteiro para o vértice que faz a aresta com o vertice2
*	  pValor2  - ponteiro para o vértice que faz a aresta com o vertice1
*
*  $FV Valor retornado
*     GRA_CondRetOK - conseguiu excluir aresta corretamente
*     GRA_CondRetGrafoVazio - grafo não possui arestas para excluir pois está vazio, grafo não é alterado
	  GRA_CondRetVerticeNExiste - Algum dos vértices recebidos por parâmetro não existe, grafo não é alterado
*     GRA_CondRetArestaNExiste - grafo não possui a aresta desejada para exclusão, grafo não é alterado
***********************************************************************/

   GRA_tpCondRet GRA_ExcluirAresta( GRA_tppGrafo pGrafo, void* pValor, void* pValor2 );

/***********************************************************************
*  $FC Função: GRA  &Obter referência para o valor contido no vértice 
*
*  $ED Descrição da função
*     Obtem a referência para o valor contido no vértice corrente do grafo
*
*  $EP Parâmetros
*     pGrafo - ponteiro para o grafo de onde se quer o valor
*     pValor - Endereço da Referência onde será armazenado o ponteiro para o valor contido no vértice
*
*  $FV Valor retornado
*    GRA_CondRetOK - Conseguiu obter referência para o valor contido no vértice corretamente.
*	 GRA_CondRetGrafoNExiste - Grafo não foi criado.
*	 GRA_CondRetGrafoVazio - O grafo está vazio.	
*
************************************************************************/

  void * GRA_ObterValorCorrente( GRA_tppGrafo pGrafo );

/***********************************************************************
*
*  $FC Função: GRA  &Ir para vertice desejado
*
*  $ED Descrição da função
*     Torna corrente o vertice do grafo que tem o valor recebido pela função.
*   
*  $EP Parâmetros
*     pGrafo - ponteiro para o grafo a manipular
*     pValor - valor do vertice que se quer encontrar
* 
*   $FV Valor retornado
*     GRA_CondRetOK - Vertice corrente agora aponta para vértice que possui o pValor
*     GRA_CondRetGrafoVazio - Vértice desejado não foi encontrado pois grafo está vazio
*     GRA_CondRetVerticeNExiste -  Vértice desejado não foi encontrado pois ele não foi adicionado no grafo
*
*
***********************************************************************/

	  GRA_tpCondRet GRA_IrVertice( GRA_tppGrafo pGrafo,void * pValor) ;

/***********************************************************************

#undef GRA_EXT

/********** Fim do módulo de definição: GRA  Grafo Não Dirigido Genérico com Cabeça **********/

#else
#endif