/***************************************************************************
*  $MCI Módulo de implementação: GRA  Grafo Não Dirigido Genérico com Cabeça
*
*  Arquivo gerado:              GRAFO.c
*  Letras identificadoras:      GRA
*  
*
*  Projeto: T4 INF 1301 2017.2
*  Autores: ap - André Pessanha
*           bg - Bianca Gomes
*           bf - Bianca Fragoso
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data       Observações
*     7       ap      04/nov/2017 Criação de novas funções
*     6       ap      29/out/2017 Alteração no módulo para que grafo tivesse um identificador
*     5       bg      16/out/2017 Continuação e alteração de script de testes e de módulo testador
*     4      bg,bf    01/fev/2006 Criar linguagem script simbólica
*     3     ap,bg,bf  08/dez/2004 Revisão do código
*     2       bf      07/out/2017 Continuação do desenvolvimento e documentação
*     1       ap      13/out/2017 Início desenvolvimento
*		  
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define GRAFO_OWN
#include "GRAFO.h"
#undef GRAFO_OWN

/***********************************************************************
*
*  $TC Tipo de dados: GRA Elemento do grafo
*
***********************************************************************/
typedef struct GRA_tagVerticeGrafo{
	void * pValor;   
	void * id;   // ID de cada usuário
	LIS_tppLista arestas;
}GRA_tpVerticeGrafo;
 
/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da cabeça do grafo
*
***********************************************************************/

  typedef struct GRA_tagGrafo {
	LIS_tppLista  pListaVertices;
	GRA_tpVerticeGrafo * pVerticeCorrente;
	int numVert;
	void ( * ExcluirValor ) ( void * pValor );
} GRA_tpGrafo;
   

/*****  Código das funções encapsuladas pelo módulo  *****/

  static GRA_tppVerticeGrafo GRA_PesquisaVertice(GRA_tppGrafo pGrafo, void* Valor);

/***************************************************************************
*
*  Função: GRA  &Criar grafo
*  ****/
   GRA_tppGrafo GRA_CriarGrafo(
             void   ( * ExcluirValor ) ( void * pDado ) )
   {
	   GRA_tpGrafo * pGrafo = NULL ;

      pGrafo = ( GRA_tpGrafo * ) malloc( sizeof( GRA_tpGrafo )) ;
      if ( pGrafo == NULL )
      {
         return NULL ;
      } 
	  pGrafo->ExcluirValor=ExcluirValor;
	  pGrafo->numVert=0;
	  pGrafo->pListaVertices=LIS_CriarLista(NULL); 
	  pGrafo->pVerticeCorrente=NULL;

	  return pGrafo;
      
   } /* Fim função: LIS  &Criar grafo */
/***********************************************************************
*
*  $FC Função: GRA  -Destruir o grafo
*
*  ****/

void * GRA_DestruirGrafo( GRA_tppGrafo pGrafo )
   {
	   if(pGrafo != NULL){
		   GRA_EsvaziarGrafo(pGrafo); 
		   if(pGrafo->pListaVertices != NULL){
			   LIS_DestruirLista(pGrafo->pListaVertices);
		   }
		   free(pGrafo);
	   }
	   
	   return NULL;

   } /* Fim função: GRA -Destruir o grafo */

/***********************************************************************
*
*  $FC Função: GRA  -Esvaziar o grafo
*
*  ****/

   GRA_tpCondRet GRA_EsvaziarGrafo(GRA_tppGrafo pGrafo )
   {
	   if(pGrafo == NULL){
		   return GRA_CondRetGrafoNExiste;
	   }
	   LIS_IrInicioLista(pGrafo->pListaVertices);
	   if(pGrafo->pVerticeCorrente == NULL || pGrafo->numVert == 0){
		   return GRA_CondRetGrafoVazio;
	   }
	   do{
		   pGrafo->pVerticeCorrente->id = NULL;
		     //Remover arestas do vértice corrente
		   if(pGrafo->pVerticeCorrente->arestas != NULL){
			   LIS_EsvaziarLista(pGrafo->pVerticeCorrente->arestas);
		   }
		   if(pGrafo->ExcluirValor != NULL){ //Excluir o Valor
			   pGrafo->ExcluirValor(pGrafo->pVerticeCorrente->pValor); 
		   }
		}while(LIS_AvancarElementoCorrente(pGrafo->pListaVertices,1) != LIS_CondRetFimLista);
	  
	   LIS_EsvaziarLista(pGrafo->pListaVertices);
	   pGrafo->numVert = 0;
	   pGrafo->pVerticeCorrente = NULL;

	   return GRA_CondRetOK;

   } /* Fim função: GRA -Esvaziar o grafo */


/***************************************************************************
*
*  Função: GRA &Inserir vertice 
*  ****/

   GRA_tpCondRet GRA_InserirVertice( GRA_tppGrafo pGrafo ,void * pValor, void *id)
   {
	   GRA_tppVerticeGrafo vertice;
	   LIS_tpCondRet CondRetLis;
	   //Não foi possivel criar vertice pois o ponteiro para o grafo não existe
	   if (pGrafo == NULL){
		   return GRA_CondRetGrafoNExiste;
	   }
	   vertice = (GRA_tppVerticeGrafo) malloc(sizeof(GRA_tpVerticeGrafo));
	   if(vertice==NULL)
	   {
		   return GRA_CondRetFaltouMemoria;
	   }
	   vertice->pValor = pValor;
	   vertice->id = id;    // Atualiza o ID
	   vertice->arestas = NULL;
	 
	   LIS_IrFinalLista(pGrafo->pListaVertices);
	   CondRetLis = LIS_InserirElementoApos(pGrafo->pListaVertices, (void *) vertice);
	 
	   pGrafo->pVerticeCorrente = vertice;

	   if (CondRetLis != LIS_CondRetOK){
		   return GRA_CondRetFaltouMemoria;
	   }
	   pGrafo->numVert++;
	   
	   return GRA_CondRetOK;
   } /* Fim função: GRA  &Inserir vertice */

/***************************************************************************
*
*  Função: GRA  &Inserir Aresta em vertice corrente
*  ****/

   GRA_tpCondRet GRA_InserirArestaCorrente( GRA_tppGrafo pGrafo ,void* pValor)   
   {
	    GRA_tppVerticeGrafo pVertice;
		LIS_tpCondRet condicao;
		  if (pGrafo == NULL){
		   return GRA_CondRetGrafoNExiste;
	   }

	   if (pGrafo->pVerticeCorrente == NULL){
		   return GRA_CondRetGrafoVazio;
	   }
	   
		pVertice=GRA_PesquisaVertice(pGrafo, pValor);
		if(pVertice == NULL) {
		   return GRA_CondRetVerticeNExiste;
	   }
		if(pVertice->arestas == NULL){
			pVertice->arestas = LIS_CriarLista(NULL);
		}
		
		condicao = LIS_ProcurarValor(pVertice->arestas, pGrafo->pVerticeCorrente->id);
		if(condicao == LIS_CondRetOK){
			return GRA_CondRetArestaExiste;
		}
		else if(condicao == LIS_CondRetNaoAchou || condicao == LIS_CondRetListaVazia){
			condicao = LIS_InserirElementoApos(pVertice->arestas,pGrafo->pVerticeCorrente->id);
			if(condicao==LIS_CondRetFaltouMemoria)
			{
				return GRA_CondRetFaltouMemoria;
			}
			if(pGrafo->pVerticeCorrente->arestas == NULL){
				pGrafo->pVerticeCorrente->arestas = LIS_CriarLista(NULL);
			}
			condicao = LIS_InserirElementoApos(pGrafo->pVerticeCorrente->arestas,pVertice->id);
			if(condicao==LIS_CondRetFaltouMemoria)
			{
				return GRA_CondRetFaltouMemoria;
			}
		}
		return GRA_CondRetOK ;
   } /* Fim função: GRA  &Inserir aresta em vertice corrente */

/***************************************************************************
*
*  Função: GRA  &Excluir vertice corrente
*  ****/
   GRA_tpCondRet GRA_ExcluiVerticeCorrente( GRA_tppGrafo pGrafo )
   {
	   LIS_tpCondRet cond;
	   GRA_tpCondRet condGra;
	   GRA_tppVerticeGrafo pUser;
	   void * idAmigo, * pAmigo;

	   if(pGrafo == NULL){
		   return GRA_CondRetGrafoNExiste;
	   }
	   if(pGrafo->numVert == 0){
		   return GRA_CondRetGrafoVazio;
	   }

	   pUser = pGrafo->pVerticeCorrente;

	   if(pGrafo->pVerticeCorrente->arestas != NULL){
		   LIS_IrInicioLista(pUser->arestas);
		   
		   do{
			   idAmigo = LIS_ObterValor(pUser->arestas);
			   condGra = GRA_VerificaVerticeExiste(pGrafo, idAmigo);
			   if(condGra == GRA_CondRetOK){
				   pAmigo = GRA_ObterValorCorrente(pGrafo);
				   GRA_ExcluirAresta(pGrafo, pUser->pValor, pAmigo);
			   }
			    
		   }while(pUser->arestas != NULL);

		   if(pUser->arestas != NULL){
			   LIS_DestruirLista(pUser->arestas);
		   }
	   }
	   pUser->id = NULL;  //Apaga o ID

	   if(pGrafo->ExcluirValor != NULL){
		   pGrafo->ExcluirValor(pGrafo->pVerticeCorrente->pValor); 
	   }

	   LIS_ProcurarValor(pGrafo->pListaVertices, (void *) pUser);
	   LIS_ExcluirElemento(pGrafo->pListaVertices);
	   
	   pGrafo->numVert--;

	   if(pGrafo->numVert == 0){
		   pGrafo->pVerticeCorrente = NULL;
	   }
	   else{
		    LIS_IrInicioLista(pGrafo->pListaVertices);
			pGrafo->pVerticeCorrente = (GRA_tpVerticeGrafo*) LIS_ObterValor( pGrafo->pListaVertices);
	   }

	    return GRA_CondRetOK;
   } /* Fim função: GRA  &Excluir vertice corrente */

/***************************************************************************
*
*  Função: GRA  &Excluir aresta
*  ****/
   GRA_tpCondRet GRA_ExcluirAresta( GRA_tppGrafo pGrafo, void* pValor, void* pValor2 ) 
   {
	   LIS_tpCondRet cond;
	   GRA_tppVerticeGrafo vertice1, vertice2;
	   int qtd;
	   
	   if(pGrafo == NULL){
		   return GRA_CondRetGrafoNExiste;
	   }
	   if(pGrafo->numVert == 0){
		   return GRA_CondRetGrafoVazio;
	   }

	   vertice1 =GRA_PesquisaVertice(pGrafo, pValor);
	   vertice2 =GRA_PesquisaVertice(pGrafo, pValor2);

	   if(vertice1 == vertice2){
		   return GRA_CondRetArestaNExiste;
	   }
	   LIS_IrInicioLista( pGrafo->pListaVertices );
	   cond = LIS_ProcurarValor(pGrafo->pListaVertices, (void *) vertice1);
	   if(cond == LIS_CondRetNaoAchou){
		   return GRA_CondRetVerticeNExiste;
	   }
	   cond = LIS_ProcurarValor(vertice1->arestas, (void *) vertice2->id);
	   if(cond == LIS_CondRetNaoAchou || cond == LIS_CondRetListaNExiste || cond == LIS_CondRetListaVazia ){
		   return GRA_CondRetArestaNExiste;
	   }
	   LIS_ExcluirElemento(vertice1->arestas); //Removeu aresta do Vertice 1
	   qtd = LIS_ContaElementos(vertice1->arestas);
	   if(qtd == 0){
		   LIS_DestruirLista(vertice1->arestas);
		   vertice1->arestas = NULL;
	   }

	   cond = LIS_ProcurarValor(pGrafo->pListaVertices, (void *) vertice2);
	   if(cond == LIS_CondRetNaoAchou){
		   return GRA_CondRetVerticeNExiste;
	   }
	   cond = LIS_ProcurarValor(vertice2->arestas, (void *) vertice1->id);
	   if(cond == LIS_CondRetNaoAchou || cond == LIS_CondRetListaNExiste ){
		   return GRA_CondRetArestaNExiste;
	   }
	   LIS_ExcluirElemento(vertice2->arestas);  //Removeu aresta do Vertice 2
	   qtd = LIS_ContaElementos(vertice2->arestas);
	   if(qtd == 0){
		   LIS_DestruirLista(vertice2->arestas);
		   vertice2->arestas = NULL;
	   }

	   return GRA_CondRetOK ;
   } /* Fim função: GRA  &Excluir aresta */

/***************************************************************************
*
*  Função: GRA  &Obter referência para o valor contido no vértice corrente
*  ****/

 void* GRA_ObterValorCorrente( GRA_tppGrafo pGrafo)
   {
	   if (pGrafo == NULL || pGrafo->pVerticeCorrente == NULL){
		   return NULL;
	   }
	   	   
	   return   pGrafo->pVerticeCorrente->pValor;
   } /* Fim função: GRA &Obter referência para o valor contido no vértice corrente*/

/***************************************************************************
*
*  Função: GRA  &Obtem Arestas Vértice Corrente
*  ****/

  void * GRA_ObtemArestasVerticeCorrente( GRA_tppGrafo pGrafo)
   {

	  if (pGrafo == NULL || pGrafo->pVerticeCorrente == NULL){
		   return NULL;
	   }
	   
	   return pGrafo->pVerticeCorrente->arestas;

   } /* Fim função: GRA &Obtem Arestas Vértice Corrente */

/***************************************************************************
*
*  Função: GRA  &Verifica Vertice Existe
*  ****/

  GRA_tpCondRet GRA_VerificaVerticeExiste( GRA_tppGrafo pGrafo, void *id)
   {
	   GRA_tppVerticeGrafo pVerticeGrafo;

	   if (pGrafo == NULL){
		   return GRA_CondRetGrafoNExiste;
	   }
	   if(pGrafo->pVerticeCorrente == NULL){
		   return GRA_CondRetVerticeNExiste;
	   }

	   LIS_IrInicioLista(pGrafo->pListaVertices);

	   while (LIS_ObterValor( pGrafo->pListaVertices ) != NULL )
	   {
		   pVerticeGrafo = (GRA_tppVerticeGrafo) LIS_ObterValor( pGrafo->pListaVertices );
	       if(strcmp((char*)pVerticeGrafo->id, (char*) id) == 0){
			   pGrafo->pVerticeCorrente = pVerticeGrafo;
			   return GRA_CondRetOK;
		   }
			
		   if( LIS_AvancarElementoCorrente( pGrafo->pListaVertices, 1 ) == LIS_CondRetFimLista )
				break;
	   }
	   	   
	   return GRA_CondRetVerticeNExiste;

   } /* Fim função: GRA &Verifica Vertice Existe*/
/***************************************************************************
*
*  Função: GRA  &Avançar Vértice Corrente
*  ****/

  GRA_tpCondRet GRA_AvancarVerticeCorrente( GRA_tppGrafo pGrafo)
   {
	   LIS_tpCondRet cond;

	   if (pGrafo == NULL){
		   return GRA_CondRetGrafoNExiste;
	   }
	   if(pGrafo->pVerticeCorrente == NULL){
		   return GRA_CondRetGrafoVazio;
	   }
	   
	   cond = LIS_AvancarElementoCorrente(pGrafo->pListaVertices, 1);
	   if(cond == LIS_CondRetFimLista){
			return GRA_CondRetFimGrafo;
	   }
	   pGrafo->pVerticeCorrente = (GRA_tppVerticeGrafo) LIS_ObterValor(pGrafo->pListaVertices);
	   
	   return GRA_CondRetOK;

   } /* Fim função: GRA &Avançar Vértice Corrente */
/***************************************************************************
*
*  Função: GRA  &Ir Inicio
*  ****/

  GRA_tpCondRet GRA_IrInicio( GRA_tppGrafo pGrafo)
   {

	   if (pGrafo == NULL){
		   return GRA_CondRetGrafoNExiste;
	   }
	   if(pGrafo->pVerticeCorrente == NULL){
		   return GRA_CondRetGrafoVazio;
	   }
	   
	   LIS_IrInicioLista(pGrafo->pListaVertices);
	   
	   return GRA_CondRetOK;

   } /* Fim função: GRA &Ir Inicio */

/***************************************************************************
*
*  Função: GRA  &Pesquisar Vertice no Grafo
*  ****/

static GRA_tppVerticeGrafo GRA_PesquisaVertice(GRA_tppGrafo pGrafo, void* Valor)
  {
	   GRA_tppVerticeGrafo pVerticeGrafo;
	   LIS_IrInicioLista(pGrafo->pListaVertices);

	   while (LIS_ObterValor( pGrafo->pListaVertices ) != NULL )
	   {
		   pVerticeGrafo = (GRA_tppVerticeGrafo) LIS_ObterValor( pGrafo->pListaVertices );
		   if( pVerticeGrafo != NULL && (strcmp((char*)pVerticeGrafo->id, (char*) Valor) == 0))
			   return pVerticeGrafo;

		    if( LIS_AvancarElementoCorrente( pGrafo->pListaVertices, 1 ) == LIS_CondRetFimLista )
				break;
	   }

	   return NULL;
   }/* Fim função: GRA &Pesquisar o vertice no Grafo*/

/**************************************************************************

/********** Fim do módulo de implementação: GRA Grafo Não Dirigido Genérico com Cabeça**********/