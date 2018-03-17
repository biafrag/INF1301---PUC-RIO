#if ! defined( GRAFO_ )
#define GRAFO_
/***************************************************************************
*
*  $MCD Módulo de definição: GRA  Grafo Não Dirigido Genérico com Cabeça
*
*  Arquivo gerado:             GRAFO.h
*  Letras identificadoras:      GRA
*
*  Projeto: T4 INF 1301 2017.2
*  Autores: ap - André Pessanha
*           bg - Bianca Gomes
*           bf - Bianca Fragoso
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data       Observações
*     7       ap      04/nov/2017 Criação de novas funções
*     6       ap      29/out/2017 alteração no módulo para que grafo tivesse um identificador
*     5       bg      16/out/2017 continuação e alteração de script de testes e de módulo testador
*     4      bg,bf    01/fev/2006 criar linguagem script simbólica
*     3     ap,bg,bf  08/dez/2004 revisão do código
*     2       bf      07/out/2017 continuação do desenvolvimento e documentação
*     1       ap      13/out/2017 início desenvolvimento
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
typedef struct GRA_tagVerticeGrafo* GRA_tppVerticeGrafo ;


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
		GRA_CondRetArestaExiste ,   
			   /* A aresta já existe */
        GRA_CondRetFaltouMemoria,
               /* Faltou memória ao tentar criar um elemento do grafo */
	    GRA_CondRetFimGrafo,
			  /* Foi atingido o fim do Grafo */
		GRA_CondRetErroEstrutura 
			 /* Estrutura do Grafo está errada */
   } GRA_tpCondRet ;


/***********************************************************************
*
*  $TC Tipo de dados: GRA Modos de deturpar
*
***********************************************************************/

#ifdef _DEBUG

   typedef enum {

         DeturpaQtdVert					  =  1 ,
               /* Alterar a quantidade total de vértices. */

         DeturpaVertCorrenteNulo          =  2 ,
               /* Torna ponteiro vértice corrente nulo */

         DeturpaLisVertNulo               =  3 ,
               /*  Torna ponteiro lista vertices nulo */

         DeturpaCabecaNulo                 =  4 ,
               /* Torna ponteiro da cabeça do Grafo nulo */

         DeturpaValorVertCorrenteNulo      =  5 ,
               /* Torna ponteiro valor do vértice corrente nulo */

         DeturpaEspacoCabeca               =  6 ,
               /*  Modifica o tipo cabeça do Grafo */

         DeturpaEspacoVerticeCorrente      =  7 ,
               /* Modifica o tipo do vértice corrente */

         DeturpaTamCabeca				   =  8 ,
               /*  Altera o tamanho da cabeça do Grafo */

         DeturpaTamVerticeCorrente         =  9 ,
               /*Altera o tamanho do vértice corrente */

         DeturpaPtCabecaNulo               = 10
               /* Anula ponteiro cabeça */


   } GRA_tpModosDeturpacao ;

#endif


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
*
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
*     OBS: Não existe previsão para possíveis falhas de execução.
*
*  $FV Valor retornado
*     NULL  - O Grafo não existe.
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
*     GRA_CondRetOK           - O Grafo foi esvaziado com sucesso.
*	  GRA_CondRetGrafoNExiste - O Grafo não foi criado.
*	  GRA_CondRetGrafoVazio   - O Grafo está vazio.
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
*	  id     - Ponteiro para o valor corresponde ao ID do vértice a ser inserido.
*
*  $FV Valor retornado
*     GRA_CondRetOK            - Novo vértice inserido no Grafo com sucesso.
*	  GRA_CondRetGrafoNExiste  - Grafo não foi criado.
*     GRA_CondRetFaltouMemoria - Não tinha memória para que vértice fosse inserido e o grafo continua da mesma forma
*
***********************************************************************/

   GRA_tpCondRet GRA_InserirVertice( GRA_tppGrafo pGrafo ,void * pValor, void *id);

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
*	     GRA_CondRetArestaExiste   - Aresta já existe, grafo não é alterado.
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
*	  GRA_CondRetVerticeNExiste - Algum dos vértices recebidos por parâmetro não existe, grafo não é alterado
*     GRA_CondRetArestaNExiste - grafo não possui a aresta desejada para exclusão, grafo não é alterado
*
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
*
*  $FV Valor retornado
*    pValor - Ponteiro para o valor contido no vértice corrente do Grafo.
*	 NULL - O grafo não foi criado ou está vazio.	
*
************************************************************************/

  void * GRA_ObterValorCorrente( GRA_tppGrafo pGrafo );

/***********************************************************************
*  $FC Função: GRA  &Obtem Arestas do vértice Corrente 
*
*  $ED Descrição da função
*     Obtem a referência para as arestas do vértice corrente.
*
*  $EP Parâmetros
*     pGrafo - ponteiro para o grafo de onde se quer o valor
*
*  $FV Valor retornado
*    pValor - Ponteiro para as arestas do vértice corrente do Grafo.
*	 NULL - O grafo não foi criado ou está vazio.	
*
************************************************************************/

  void * GRA_ObtemArestasVerticeCorrente( GRA_tppGrafo pGrafo );

/***********************************************************************
*  $FC Função: GRA  &Verifica Vertice Existe
*
*  $ED Descrição da função
*     Verifica se um vértice existe no grafo a partir de seu ID
*
*  $EP Parâmetros
*     id - Ponteiro para o valor do ID do vértice.
*     
*  $FV Valor retornado
*    GRA_CondRetOK - O vértice correspondente ao ID recebido no parâmetro existe.
*	 GRA_CondRetGrafoNExiste - Grafo não foi criado.
*	 GRA_CondRetVerticeNExiste - O vértice correspondente ao ID recebido no parâmetro não existe.
*
************************************************************************/

  GRA_tpCondRet GRA_VerificaVerticeExiste( GRA_tppGrafo pGrafo, void *id);

/***********************************************************************
*  $FC Função: GRA  &Avançar Vértice Corrente
*
*  $ED Descrição da função
*     Avança o vértice corrente em uma unidade.
*
*  $EP Parâmetros
*     pGrafo - Ponteiro para o grafo.
*     
*  $FV Valor retornado
*    GRA_CondRetOK - Avançou para o próximo vértice com sucesso.
*	 GRA_CondRetGrafoVazio - Grafo não possui vértices.
*	 GRA_CondRetFimGrafo -  O Grafo não possui mais vértices.
*
************************************************************************/

  GRA_tpCondRet GRA_AvancarVerticeCorrente( GRA_tppGrafo pGrafo);

/***********************************************************************
*  $FC Função: GRA  &Ir Inicio
*
*  $ED Descrição da função
*     Torna corrente o primeiro vértice do grafo.
*   
*  $EP Parâmetros
*     pGrafo - ponteiro para o grafo a manipular
* 
*   $FV Valor retornado
*     GRA_CondRetOK - Vertice corrente agora aponta para o primeiro vértice do Grafo
*	  GRA_CondRetGrafoNExiste - O Grafo não foi criado.
*     GRA_CondRetGrafoVazio - O Grafo está vazio. Não possui vértices.
*
***********************************************************************/

	 GRA_tpCondRet GRA_IrInicio (GRA_tppGrafo pGrafo) ;

/***********************************************************************
*
*  $FC Função: GRA Verificar Grafo
*
*  $ED Descrição da função
*		Verifica a estrutura Grafo, contabilizando o total de erros encontrados.
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para o grafo a ser verificado.
*     $P qtdErros - ponteiro para inteiro que será atualizado com a quantidade total de erros.
*
*  $FV Valor retornado
*     GRA_CondRetOK - Executou corretamente e atualizou o contador de erros.
*     GRA_CondRetErroEstrutura - Detectou erros na estrutura do vértice do Grafo.
*
***********************************************************************/

#ifdef _DEBUG
   GRA_tpCondRet GRA_VerificarGrafo( GRA_tppGrafo pGrafo, int * qtdErros );
#endif

/***********************************************************************
*
*  $FC Função: GRA  &Verificar um vértice do Grafo
*
*  $ED Descrição da função
*     Função da interface de teste.
*     Verifica a integridade de um vértice estrutural do Grafo.
*
*  $EP Parâmetros
*     $P pVerticeParm - ponteiro para espaço que deveria ser um Vértice estrutural.
*     $P qtdErros - ponteiro para inteiro que será atualizado com a quantidade total de erros.
*	  $P tamValor - Ponteiro a ser atualizado com o tamanho em bytes do vértice.
*
*  $FV Valor retornado
*     GRA_CondRetOK - Executou corretamente e atualizou o contador de erros.
*     GRA_CondRetErroEstrutura - Detectou erros na estrutura do vértice do Grafo.
*
***********************************************************************/

#ifdef _DEBUG
   GRA_tpCondRet GRA_VerificarVertice( void * pVerticeParm, int *qtdErros, int *tamValor );
#endif

/***********************************************************************
*
*  $FC Função: GRA  &Verificar Cabeça do Grafo
*
*  $ED Descrição da função
*     Função da interface de teste.
*     Verifica a integridade da cabeça do Grafo.
*
*  $EP Parâmetros
*     $P pCabecaParm - ponteiro para um espaço que deveria ser uma cabeça
*                      de Grafo.
*	  $P qtdErros - ponteiro para inteiro que será atualizado com a quantidade total de erros.
*
*  $FV Valor retornado
*     Condição de retorno de teste
*
***********************************************************************/

#ifdef _DEBUG
   GRA_tpCondRet GRA_VerificarCabecaGrafo( void * pCabecaParm, int * qtdErros );
#endif

/***********************************************************************
*
*  $FC Função: GRA &Deturpar Grafo
*
*  $ED Descrição da função
*		Função da interface de teste. Corrompe elementos específicos da estrutura do Grafo
*		de acordo com o tipo fornecido.
*		Essa função destina-se a preparar os cenários de teste dos
*		casos de teste utilizados ao testar os verificadores estruturais
*		do Grafo.
*
*  $EP Parâmetros
*     $P pGrafo -  Ponteiro para o grafo a ser deturpado.
*     $P tipo   -  Indica o tipo de deturpacao a ser realizado:
*			1  - Altera a quantidade total de vértices.
*			2  - Torna ponteiro vértice corrente nulo
*			3  - Altera o tipo cabeça do Grafo
*			4  - Altera o tipo do vértice corrente
*
***********************************************************************/

#ifdef _DEBUG
   void GRA_Deturpar( GRA_tppGrafo pGrafo, GRA_tpModosDeturpacao tipo);
#endif

/***********************************************************************
*
*  $FC Função: GRA &Corrige Quantidade de vértices
*
*  $ED Descrição da função
*		Função de recuperação de estado inconsitente do Grafo.
*	    Corrige a quantidade total de vértices do Grafo.
*
*  $EP Parâmetros
*     $P pGrafo -  Ponteiro para o grafo a ser corrigido.
* 
*  $FV Valor retornado
*     GRA_CondRetOK - Executou corretamente e corrigiu a exceção.
*
***********************************************************************/

#ifdef _DEBUG
   GRA_tpCondRet GRA_CorrigeQuantidadeVertices( GRA_tppGrafo pGrafo) ;
#endif

/***********************************************************************/

#undef GRAFO_EXT

#undef GRA_EXT

/********** Fim do módulo de definição: GRA  Grafo Não Dirigido Genérico com Cabeça **********/

#else
#endif