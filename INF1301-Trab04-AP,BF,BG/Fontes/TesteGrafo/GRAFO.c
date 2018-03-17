/***************************************************************************
*  $MCI Módulo de implementação: GRA  Grafo Não Dirigido Genérico com Cabeça
*
*  Arquivo gerado:              GRAFO.c
*  Letras identificadoras:      GRA
*  
*
*  Projeto: T2 INF 1301 2017.2
*  Autores: ap - André Pessanha
*           bg - Bianca Gomes
*           bf - Bianca Fragoso
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
*
***********************************************************************/
typedef struct GRA_tagVerticeGrafo{
	void * pValor;     
	LIS_tppLista arestas;
}GRA_tpVerticeGrafo;
 
/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da cabeça do grafo
*
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
  static GRA_tppVerticeGrafo GRA_PesquisaVerticeNaAresta( LIS_tppLista pAresta, void* Valor);

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
	   if(pGrafo == NULL){
		   return NULL;
	   }
	   GRA_EsvaziarGrafo(pGrafo); 
	   if(pGrafo->pListaVertices != NULL){
			LIS_DestruirLista(pGrafo->pListaVertices);
	   }
	   free(pGrafo);
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

   GRA_tpCondRet GRA_InserirVertice( GRA_tppGrafo pGrafo ,void * pValor)
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
	   vertice->arestas = NULL;
	   //

	   LIS_IrFinalLista(pGrafo->pListaVertices);
	   CondRetLis = LIS_InserirElementoApos(pGrafo->pListaVertices, (void *) vertice);

	   if(pGrafo->pVerticeCorrente == NULL) {
		   pGrafo->pVerticeCorrente = vertice;
	   }

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

		if(pGrafo->pVerticeCorrente == NULL) {
		   return GRA_CondRetVerticeNExiste;
	   }
		pVertice=GRA_PesquisaVertice(pGrafo, pValor);
		if(pVertice == NULL) {
		   return GRA_CondRetVerticeNExiste;
	   }
		if(pVertice->arestas == NULL){
			pVertice->arestas = LIS_CriarLista(NULL);
		}
	   condicao = LIS_InserirElementoApos(pVertice->arestas,pGrafo->pVerticeCorrente);
	   if(condicao==LIS_CondRetFaltouMemoria)
	   {
		   return GRA_CondRetFaltouMemoria;
	   }
	   if(pGrafo->pVerticeCorrente->arestas == NULL){
			pGrafo->pVerticeCorrente->arestas = LIS_CriarLista(NULL);
		}
	   LIS_IrFinalLista(pGrafo->pVerticeCorrente->arestas);
	   condicao = LIS_InserirElementoApos(pGrafo->pVerticeCorrente->arestas,pVertice);
	    if(condicao==LIS_CondRetFaltouMemoria)
	   {
		   return GRA_CondRetFaltouMemoria;
	   }
	    return GRA_CondRetOK ;
   } /* Fim função: GRA  &Inserir aresta em vertice corrente */


/***************************************************************************
*
*  Função: GRA  &Excluir vertice corrente
*  ****/
   GRA_tpCondRet GRA_ExcluiVerticeCorrente( GRA_tppGrafo pGrafo )
   {

	   if(pGrafo == NULL){
		   return GRA_CondRetGrafoNExiste;
	   }
	   if(pGrafo->numVert == 0){
		   return GRA_CondRetGrafoVazio;
	   }
	   if(pGrafo->pVerticeCorrente->arestas != NULL){
		   LIS_DestruirLista(pGrafo->pVerticeCorrente->arestas);
	   }
	   if(pGrafo->ExcluirValor != NULL){
		   pGrafo->ExcluirValor(pGrafo->pVerticeCorrente->pValor); 
	   }

	   LIS_ProcurarValor(pGrafo->pListaVertices, (void *) pGrafo->pVerticeCorrente);
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

	   vertice1 =GRA_PesquisaVertice(pGrafo, pValor);
	   vertice2 =GRA_PesquisaVertice(pGrafo, pValor2);

	   if(pGrafo == NULL){
		   return GRA_CondRetGrafoNExiste;
	   }
	   if(pGrafo->numVert == 0){
		   return GRA_CondRetGrafoVazio;
	   }
	   if(vertice1 == vertice2){
		   return GRA_CondRetArestaNExiste;
	   }
	   LIS_IrInicioLista( pGrafo->pListaVertices );
	   cond = LIS_ProcurarValor(pGrafo->pListaVertices, (void *) vertice1);
	   if(cond == LIS_CondRetNaoAchou){
		   return GRA_CondRetVerticeNExiste;
	   }
	   cond = LIS_ProcurarValor(vertice1->arestas, (void *) vertice2);
	   if(cond == LIS_CondRetNaoAchou){
		   return GRA_CondRetArestaNExiste;
	   }
	   LIS_ExcluirElemento(vertice1->arestas); //Removeu aresta do Vertice 1

	   cond = LIS_ProcurarValor(pGrafo->pListaVertices, (void *) vertice2);
	   if(cond == LIS_CondRetNaoAchou){
		   return GRA_CondRetVerticeNExiste;
	   }
	   cond = LIS_ProcurarValor(vertice2->arestas, (void *) vertice1);
	   if(cond == LIS_CondRetNaoAchou){
		   return GRA_CondRetArestaNExiste;
	   }
	   LIS_ExcluirElemento(vertice2->arestas); 

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
*  Função: GRA  &Ir para Vertice desejado
*  ****/

  GRA_tpCondRet GRA_IrVertice( GRA_tppGrafo pGrafo, void *pValor )
   {
	   GRA_tppVerticeGrafo vertice;
	   if (pGrafo == NULL){
		   return GRA_CondRetGrafoNExiste;
	   }

	   if (pGrafo->pVerticeCorrente == NULL){
		   return GRA_CondRetGrafoVazio;
	   }

	   vertice = GRA_PesquisaVertice( pGrafo, pValor); 
	   if(vertice == NULL) {
		   return GRA_CondRetVerticeNExiste;
	   }

	   pGrafo->pVerticeCorrente = vertice;
	   
       return GRA_CondRetOK ;

   } /* Fim função: GRA &Ir para Vertice desejado*/
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
		   if( pVerticeGrafo != NULL && pVerticeGrafo->pValor == Valor )
			   return pVerticeGrafo;

		    if( LIS_AvancarElementoCorrente( pGrafo->pListaVertices, 1 ) == LIS_CondRetFimLista )
				break;
	   }

	   return NULL;
   }/* Fim função: GRA &Pesquisar o vertice no Grafo*/
  /***************************************************************************
*
*  Função: GRA  &Pesquisar Aresta
*  ****/

 static GRA_tppVerticeGrafo GRA_PesquisaVerticeNaAresta( LIS_tppLista pAresta, void* Valor)
  {
	   LIS_IrInicioLista( pAresta );

	   while (LIS_ObterValor( pAresta)!=NULL ) {

		   if( pAresta != NULL && LIS_ObterValor(pAresta)==Valor)
			   return  (GRA_tpVerticeGrafo*) LIS_ObterValor(pAresta);

		    if( LIS_AvancarElementoCorrente( pAresta, 1 ) == LIS_CondRetFimLista )
				break;
	   }

	   return NULL;
   }
 /* Fim função: GRA &Pesquisar o vertice no Grafo*/
  

/**************************************************************************

/********** Fim do módulo de implementação: GRA Grafo Não Dirigido Genérico com Cabeça**********/