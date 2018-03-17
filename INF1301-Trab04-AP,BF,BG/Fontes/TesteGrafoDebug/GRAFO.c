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

#ifdef _DEBUG
#include "CONTA.H"
#include "CESPDIN.H"
#include "GENERICO.h"
#include   "..\\tabelas\\IdTiposEspaco.def"  
#endif

/***********************************************************************
*
*  $TC Tipo de dados: GRA Elemento do grafo
*
***********************************************************************/
typedef struct GRA_tagVerticeGrafo{
	void * pValor;   
	void * id;   // ID de cada usuário
	LIS_tppLista arestas;
#ifdef _DEBUG
	int idTipo;
	GRA_tppGrafo pCabeca;
	int tamValor;
#endif
}GRA_tpVerticeGrafo;

/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da cabeça do grafo
*
***********************************************************************/

typedef struct GRA_tagGrafo {
	LIS_tppLista  pListaVertices;
	GRA_tpVerticeGrafo * pVerticeCorrente;
	void ( * ExcluirValor ) ( void * pValor );
#ifdef _DEBUG
	int numVert;
	int tamTotal;
	int idTipo;
#endif
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

	#ifdef _DEBUG
		CNT_CONTAR( "GRA_CriarGrafo" ) ;
	#endif

	pGrafo = ( GRA_tpGrafo * ) malloc( sizeof( GRA_tpGrafo )) ;
	if ( pGrafo == NULL )
	{
		return NULL ;
	}

	#ifdef _DEBUG
		CNT_CONTAR( "GRA_CriarGrafo-pr0" ) ;
	#endif

	pGrafo->ExcluirValor=ExcluirValor;

	#ifdef _DEBUG
	CED_MarcarEspacoAtivo(pGrafo);
	pGrafo->numVert=0;
	pGrafo->tamTotal = 0;
	#endif

	pGrafo->pListaVertices=LIS_CriarLista(NULL); 
	pGrafo->pVerticeCorrente=NULL;

	#ifdef _DEBUG
		CED_DefinirTipoEspaco( pGrafo , GRA_TipoEspacoCabeca ) ; 
	#endif  

	return pGrafo;

} /* Fim função: LIS  &Criar grafo */
/***********************************************************************
*
*  $FC Função: GRA  -Destruir o grafo
*
*  ****/

void * GRA_DestruirGrafo( GRA_tppGrafo pGrafo )
{
	#ifdef _DEBUG
		CNT_CONTAR( "GRA_DestruirGrafo" ) ;
	#endif

	if(pGrafo == NULL){
		#ifdef _DEBUG
			   CNT_CONTAR( "GRA_DestruirGrafo-if0" ) ;
		#endif
		return NULL;
	}

	#ifdef _DEBUG
	      CNT_CONTAR( "GRA_DestruirGrafo-pr0" ) ;
	#endif

	GRA_EsvaziarGrafo(pGrafo); 
	if(pGrafo->pListaVertices != NULL){
		#ifdef _DEBUG
			   CNT_CONTAR( "GRA_DestruirGrafo-if1" ) ;
		#endif
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
	#ifdef _DEBUG
		CNT_CONTAR( "GRA_EsvaziarGrafo" ) ;
	#endif

	if(pGrafo == NULL){
		#ifdef _DEBUG
			   CNT_CONTAR( "GRA_EsvaziarGrafo-if0" ) ;
		#endif
		return GRA_CondRetGrafoNExiste;
	}

	#ifdef _DEBUG
		 CNT_CONTAR( "GRA_EsvaziarGrafo-pr0" ) ;
	#endif  

	LIS_IrInicioLista(pGrafo->pListaVertices);
	if(pGrafo->pVerticeCorrente == NULL){
		#ifdef _DEBUG
			   CNT_CONTAR( "GRA_EsvaziarGrafo-if1" ) ;
		#endif
		return GRA_CondRetGrafoVazio;
	}
	#ifdef _DEBUG
		 CNT_CONTAR( "GRA_EsvaziarGrafo-pr1" ) ;
	#endif 

	do{
		#ifdef _DEBUG
			   CNT_CONTAR( "GRA_EsvaziarGrafo-dowhile0" ) ;
		#endif

		pGrafo->pVerticeCorrente->id = NULL;
		//Remover arestas do vértice corrente
		if(pGrafo->pVerticeCorrente->arestas != NULL){
			#ifdef _DEBUG
			  // CNT_CONTAR( "GRA_EsvaziarGrafo-dowhile-if0" ) ;
			#endif
			LIS_EsvaziarLista(pGrafo->pVerticeCorrente->arestas);
		}

		if(pGrafo->ExcluirValor != NULL){ //Excluir o Valor
			pGrafo->ExcluirValor(pGrafo->pVerticeCorrente->pValor); 
		}
	}while(LIS_AvancarElementoCorrente(pGrafo->pListaVertices,1) != LIS_CondRetFimLista);


	LIS_EsvaziarLista(pGrafo->pListaVertices);
	#ifdef _DEBUG
		pGrafo->numVert = 0;
	#endif
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

	#ifdef _DEBUG
		CNT_CONTAR( "GRA_InserirVertice" ) ;
	#endif

	//Não foi possivel criar vertice pois o ponteiro para o grafo não existe
	if (pGrafo == NULL){
		#ifdef _DEBUG
			   CNT_CONTAR( "GRA_InserirVertice-if0" ) ;
		#endif
		return GRA_CondRetGrafoNExiste;
	}
	#ifdef _DEBUG
		 CNT_CONTAR( "GRA_InserirVertice-pr0" ) ;
	#endif

	vertice = (GRA_tppVerticeGrafo) malloc(sizeof(GRA_tpVerticeGrafo));
	if(vertice==NULL){
		return GRA_CondRetFaltouMemoria;
	}

	#ifdef _DEBUG
		 CNT_CONTAR( "GRA_InserirVertice-pr1" ) ;
	#endif

	vertice->pValor = pValor;
	vertice->id = id;    // Atualiza o ID
	vertice->arestas = NULL;

	#ifdef _DEBUG
	vertice->tamValor = 0;
	vertice->pCabeca = pGrafo;
	vertice->idTipo = CED_ObterTipoEspaco(pValor);
	if(pValor != NULL){
		CNT_CONTAR( "GRA_InserirVertice-if2" ) ;
		vertice->tamValor = CED_ObterTamanhoValor(pValor);
	}
	else{
		vertice->tamValor = 0;
	}
	pGrafo->tamTotal += vertice->tamValor;
	#endif 

	LIS_IrFinalLista(pGrafo->pListaVertices);
	CondRetLis = LIS_InserirElementoApos(pGrafo->pListaVertices, (void *) vertice);

	pGrafo->pVerticeCorrente = vertice;

	if (CondRetLis != LIS_CondRetOK){
		return GRA_CondRetFaltouMemoria;
	}

	#ifdef _DEBUG
	    CNT_CONTAR( "GRA_InserirVertice-pr2" ) ;
	#endif

	#ifdef _DEBUG
		pGrafo->numVert++;
		CED_DefinirTipoEspaco( pGrafo->pVerticeCorrente , GRA_TipoEspacoVertice ) ; 
	#endif 

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

	#ifdef _DEBUG
		CNT_CONTAR( "GRA_InserirArestaCorrente" ) ;
	#endif

	if (pGrafo == NULL){
		#ifdef _DEBUG
			   CNT_CONTAR( "GRA_InserirArestaCorrente-if0" ) ;
		#endif
		return GRA_CondRetGrafoNExiste;
	}

	#ifdef _DEBUG
		CNT_CONTAR( "GRA_InserirArestaCorrente-pr0" ) ;
	#endif

	if (pGrafo->pVerticeCorrente == NULL){
		#ifdef _DEBUG
			   CNT_CONTAR( "GRA_InserirArestaCorrente-if1" ) ;
		#endif
		return GRA_CondRetGrafoVazio;
	}

	#ifdef _DEBUG
		CNT_CONTAR( "GRA_InserirArestaCorrente-pr1" ) ;
	#endif

	pVertice=GRA_PesquisaVertice(pGrafo, pValor);  
	if(pVertice == NULL) {
		#ifdef _DEBUG
			   CNT_CONTAR( "GRA_InserirArestaCorrente-if3" ) ;
		#endif
		return GRA_CondRetVerticeNExiste;
	}
	#ifdef _DEBUG
		CNT_CONTAR( "GRA_InserirArestaCorrente-pr3" ) ;
	#endif

	if(pVertice->arestas == NULL){
		#ifdef _DEBUG
			   CNT_CONTAR( "GRA_InserirArestaCorrente-if4" ) ;
		#endif
		pVertice->arestas = LIS_CriarLista(NULL);
	}

	condicao = LIS_ProcurarValor(pVertice->arestas, pGrafo->pVerticeCorrente->id);
	if(condicao == LIS_CondRetOK){
		#ifdef _DEBUG
			CNT_CONTAR( "GRA_InserirArestaCorrente-if5" ) ;
		#endif
		return GRA_CondRetArestaExiste;
	}
	else if(condicao == LIS_CondRetNaoAchou || condicao == LIS_CondRetListaVazia){
		condicao = LIS_InserirElementoApos(pVertice->arestas,pGrafo->pVerticeCorrente->id);
		if(condicao==LIS_CondRetFaltouMemoria)
		{
			#ifdef _DEBUG
				CNT_CONTAR( "GRA_InserirArestaCorrente-pr4" ) ;
				CNT_CONTAR( "GRA_InserirArestaCorrente-if6" ) ;
			#endif
			return GRA_CondRetFaltouMemoria;
		}
		#ifdef _DEBUG
			 CNT_CONTAR( "GRA_InserirArestaCorrente-pr5" ) ;	
		#endif

		if(pGrafo->pVerticeCorrente->arestas == NULL){
			#ifdef _DEBUG
				CNT_CONTAR( "GRA_InserirArestaCorrente-if7" ) ;
			#endif
			pGrafo->pVerticeCorrente->arestas = LIS_CriarLista(NULL);
		}
		condicao = LIS_InserirElementoApos(pGrafo->pVerticeCorrente->arestas,pVertice->id);
		if(condicao==LIS_CondRetFaltouMemoria)
		{
			#ifdef _DEBUG
				CNT_CONTAR( "GRA_InserirArestaCorrente-if8" ) ;
			#endif
			return GRA_CondRetFaltouMemoria;
		}
		#ifdef _DEBUG
			  CNT_CONTAR( "GRA_InserirArestaCorrente-pr6" ) ;
		#endif
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

	   #ifdef _DEBUG
			CNT_CONTAR( "GRA_ExcluiVerticeCorrente" ) ;
	   #endif

	   if(pGrafo == NULL){
		   #ifdef _DEBUG
			   CNT_CONTAR( "GRA_ExcluiVerticeCorrente-if0" ) ;
		   #endif
		   return GRA_CondRetGrafoNExiste;
	   }
	   #ifdef _DEBUG
			CNT_CONTAR( "GRA_ExcluiVerticeCorrente-pr0" ) ;
	   #endif

	   if(pGrafo->numVert == 0){
		   #ifdef _DEBUG
			   CNT_CONTAR( "GRA_ExcluiVerticeCorrente-if1" ) ;
		   #endif
		   return GRA_CondRetGrafoVazio;
	   }
	   #ifdef _DEBUG
			CNT_CONTAR( "GRA_ExcluiVerticeCorrente-pr1" ) ;
	   #endif
	   pUser = pGrafo->pVerticeCorrente;

	   if(pGrafo->pVerticeCorrente->arestas != NULL){
		   #ifdef _DEBUG
			   CNT_CONTAR( "GRA_ExcluiVerticeCorrente-if2" ) ;
		   #endif
		   LIS_IrInicioLista(pUser->arestas);
		   
		   do{
			   #ifdef _DEBUG
				 CNT_CONTAR( "GRA_ExcluiVerticeCorrente-dowhile0" ) ;
			   #endif
			   idAmigo = LIS_ObterValor(pUser->arestas);
			   condGra = GRA_VerificaVerticeExiste(pGrafo, idAmigo);
			   if(condGra == GRA_CondRetOK){
				   #ifdef _DEBUG
					  CNT_CONTAR( "GRA_ExcluiVerticeCorrente-dowhile-if0" ) ;
				   #endif
				   pAmigo = GRA_ObterValorCorrente(pGrafo);
				   GRA_ExcluirAresta(pGrafo, pUser->pValor, pAmigo);
			   }
			    
		   }while(pUser->arestas != NULL);

		   if(pUser->arestas != NULL){
			   #ifdef _DEBUG
					//CNT_CONTAR( "GRA_ExcluiVerticeCorrente-if3" ) ;
			   #endif
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
		   #ifdef _DEBUG
				  CNT_CONTAR( "GRA_ExcluiVerticeCorrente-if4" ) ;
		   #endif
		   pGrafo->pVerticeCorrente = NULL;
	   }
	   else{
		    #ifdef _DEBUG
				  CNT_CONTAR( "GRA_ExcluiVerticeCorrente-else0" ) ;
		    #endif
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

	   #ifdef _DEBUG
			CNT_CONTAR( "GRA_ExcluirAresta" ) ;
	   #endif

		if(pGrafo == NULL){
		   #ifdef _DEBUG
			   CNT_CONTAR( "GRA_ExcluirAresta-if0" ) ;
		   #endif
		   return GRA_CondRetGrafoNExiste;
	   }
	    #ifdef _DEBUG
			   CNT_CONTAR( "GRA_ExcluirAresta-pr0" ) ;
		#endif

	   vertice1 =GRA_PesquisaVertice(pGrafo, pValor);
	   vertice2 =GRA_PesquisaVertice(pGrafo, pValor2);

	   if(pGrafo->numVert == 0){
		   #ifdef _DEBUG
			   CNT_CONTAR( "GRA_ExcluirAresta-if1" ) ;
		   #endif
		   return GRA_CondRetGrafoVazio;
	   }
	   #ifdef _DEBUG
			   CNT_CONTAR( "GRA_ExcluirAresta-pr1" ) ;
	   #endif
	   if(vertice1 == vertice2){
		   #ifdef _DEBUG
			   CNT_CONTAR( "GRA_ExcluirAresta-if2" ) ;
		   #endif
		   return GRA_CondRetArestaNExiste;
	   }
	    #ifdef _DEBUG
			   CNT_CONTAR( "GRA_ExcluirAresta-pr2" ) ;
	   #endif

	   LIS_IrInicioLista( pGrafo->pListaVertices );
	   cond = LIS_ProcurarValor(pGrafo->pListaVertices, (void *) vertice1);
	   if(cond == LIS_CondRetNaoAchou){
		   #ifdef _DEBUG
			   CNT_CONTAR( "GRA_ExcluirAresta-if3" ) ;
		   #endif
		   return GRA_CondRetVerticeNExiste;
	   }
	   #ifdef _DEBUG
			   CNT_CONTAR( "GRA_ExcluirAresta-pr3" ) ;
	   #endif
	   cond = LIS_ProcurarValor(vertice1->arestas, (void *) vertice2->id);
	   if(cond == LIS_CondRetNaoAchou || cond == LIS_CondRetListaNExiste || cond == LIS_CondRetListaVazia ){
		   #ifdef _DEBUG
			   CNT_CONTAR( "GRA_ExcluirAresta-if4" ) ;
		   #endif
		   return GRA_CondRetArestaNExiste;
	   }
	   #ifdef _DEBUG
			   CNT_CONTAR( "GRA_ExcluirAresta-pr4" ) ;
	   #endif
	   LIS_ExcluirElemento(vertice1->arestas); //Removeu aresta do Vertice 1
	   qtd = LIS_ContaElementos(vertice1->arestas);
	   if(qtd == 0){
		   #ifdef _DEBUG
			   CNT_CONTAR( "GRA_ExcluirAresta-if5" ) ;
		   #endif
		   LIS_DestruirLista(vertice1->arestas);
		   vertice1->arestas = NULL;
	   }

	   cond = LIS_ProcurarValor(pGrafo->pListaVertices, (void *) vertice2);
	   if(cond == LIS_CondRetNaoAchou){
		   #ifdef _DEBUG
			   CNT_CONTAR( "GRA_ExcluirAresta-if6" ) ;
		   #endif
		   return GRA_CondRetVerticeNExiste;
	   }
	    #ifdef _DEBUG
			   CNT_CONTAR( "GRA_ExcluirAresta-pr5" ) ;
	    #endif
	   cond = LIS_ProcurarValor(vertice2->arestas, (void *) vertice1->id);
	   if(cond == LIS_CondRetNaoAchou || cond == LIS_CondRetListaNExiste ){
		   #ifdef _DEBUG
			   CNT_CONTAR( "GRA_ExcluirAresta-if7" ) ;
		   #endif
		   return GRA_CondRetArestaNExiste;
	   }
	   #ifdef _DEBUG
			   CNT_CONTAR( "GRA_ExcluirAresta-pr6" ) ;
	    #endif
	   LIS_ExcluirElemento(vertice2->arestas);  //Removeu aresta do Vertice 2
	   qtd = LIS_ContaElementos(vertice2->arestas);
	   if(qtd == 0){
		   #ifdef _DEBUG
			   CNT_CONTAR( "GRA_ExcluirAresta-if8" ) ;
		   #endif
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
	#ifdef _DEBUG
		CNT_CONTAR( "GRA_ObterValorCorrente" ) ;
	#endif

	if (pGrafo == NULL || pGrafo->pVerticeCorrente == NULL){
		#ifdef _DEBUG
			   CNT_CONTAR( "GRA_ObterValorCorrente-if0" ) ;
		#endif
		return NULL;
	}
	#ifdef _DEBUG
			CNT_CONTAR( "GRA_ObterValorCorrente-pr0" ) ;
    #endif

	return   pGrafo->pVerticeCorrente->pValor;
} /* Fim função: GRA &Obter referência para o valor contido no vértice corrente*/

/***************************************************************************
*
*  Função: GRA  &Obtem Arestas Vértice Corrente
*  ****/

void * GRA_ObtemArestasVerticeCorrente( GRA_tppGrafo pGrafo)
{

	#ifdef _DEBUG
		CNT_CONTAR( "GRA_ObtemArestasVerticeCorrente" ) ;
	#endif

	if (pGrafo == NULL || pGrafo->pVerticeCorrente == NULL){
		#ifdef _DEBUG
			   CNT_CONTAR( "GRA_ObtemArestasVerticeCorrente-if0" ) ;
		#endif
		return NULL;
	}
	#ifdef _DEBUG
		CNT_CONTAR( "GRA_ObtemArestasVerticeCorrente-pr0" ) ;
	#endif

	return pGrafo->pVerticeCorrente->arestas;

} /* Fim função: GRA &Obtem Arestas Vértice Corrente */

/***************************************************************************
*
*  Função: GRA  &Verifica Vertice Existe
*  ****/

  GRA_tpCondRet GRA_VerificaVerticeExiste( GRA_tppGrafo pGrafo, void *id)
   {
	   GRA_tppVerticeGrafo pVerticeGrafo;

	   #ifdef _DEBUG
		   CNT_CONTAR( "GRA_VerificaVerticeExiste" ) ;
	   #endif

	   if (pGrafo == NULL){
		   #ifdef _DEBUG
			   CNT_CONTAR( "GRA_VerificaVerticeExiste-if0" ) ;
		   #endif
		   return GRA_CondRetGrafoNExiste;
	   }
	   #ifdef _DEBUG
			   CNT_CONTAR( "GRA_VerificaVerticeExiste-pr0" ) ;
	   #endif
	   if(pGrafo->pVerticeCorrente == NULL){
		   #ifdef _DEBUG
			   CNT_CONTAR( "GRA_VerificaVerticeExiste-if1" ) ;
		   #endif
		   return GRA_CondRetVerticeNExiste;
	   }
	   #ifdef _DEBUG
			   CNT_CONTAR( "GRA_VerificaVerticeExiste-pr1" ) ;
	   #endif
	   
		LIS_IrInicioLista(pGrafo->pListaVertices);
	   
	   while (LIS_ObterValor( pGrafo->pListaVertices ) != NULL )
	   {
		   #ifdef _DEBUG
			   CNT_CONTAR( "GRA_VerificaVerticeExiste-while0" ) ;
		   #endif
		   pVerticeGrafo = (GRA_tppVerticeGrafo) LIS_ObterValor( pGrafo->pListaVertices );
	       if(strcmp((char*)pVerticeGrafo->id, (char*) id) == 0){
			   #ifdef _DEBUG
					CNT_CONTAR( "GRA_VerificaVerticeExiste-while-if0" ) ;
			   #endif
			   pGrafo->pVerticeCorrente = pVerticeGrafo;
			   return GRA_CondRetOK;
		   }
		   #ifdef _DEBUG
					CNT_CONTAR( "GRA_VerificaVerticeExiste-while-pr0" ) ;
		   #endif
			
		   if( LIS_AvancarElementoCorrente( pGrafo->pListaVertices, 1 ) == LIS_CondRetFimLista )
			   #ifdef _DEBUG
					CNT_CONTAR( "GRA_VerificaVerticeExiste-while-if1" ) ;
			   #endif
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

	   #ifdef _DEBUG
		   CNT_CONTAR( "GRA_AvancarVerticeCorrente" ) ;
	   #endif

	   if (pGrafo == NULL){
		   #ifdef _DEBUG
			   CNT_CONTAR( "GRA_AvancarVerticeCorrente-if0" ) ;
		   #endif
		   return GRA_CondRetGrafoNExiste;
	   }
	   #ifdef _DEBUG
			   CNT_CONTAR( "GRA_AvancarVerticeCorrente-pr0" ) ;
	   #endif
	   if(pGrafo->pVerticeCorrente == NULL){
		   #ifdef _DEBUG
			   CNT_CONTAR( "GRA_AvancarVerticeCorrente-if1" ) ;
		   #endif
		   return GRA_CondRetGrafoVazio;
	   }
	   #ifdef _DEBUG
			   CNT_CONTAR( "GRA_AvancarVerticeCorrente-pr1" ) ;
	   #endif
	   
	   cond = LIS_AvancarElementoCorrente(pGrafo->pListaVertices, 1);
	   if(cond == LIS_CondRetFimLista){
		   #ifdef _DEBUG
			   CNT_CONTAR( "GRA_AvancarVerticeCorrente-if2" ) ;
		   #endif
		   return GRA_CondRetFimGrafo;
	   }
	   #ifdef _DEBUG
			   CNT_CONTAR( "GRA_AvancarVerticeCorrente-pr2" ) ;
	   #endif
	   pGrafo->pVerticeCorrente = (GRA_tppVerticeGrafo) LIS_ObterValor(pGrafo->pListaVertices);
	   
	   return GRA_CondRetOK;

   } /* Fim função: GRA &Avançar Vértice Corrente */
/***************************************************************************
*
*  Função: GRA  &Ir Inicio
*  ****/

GRA_tpCondRet GRA_IrInicio( GRA_tppGrafo pGrafo)
{

	#ifdef _DEBUG
		CNT_CONTAR( "GRA_IrInicio" ) ;
	#endif

	if (pGrafo == NULL){
		#ifdef _DEBUG
			   CNT_CONTAR( "GRA_IrInicio-if0" ) ;
		#endif
		return GRA_CondRetGrafoNExiste;
	}
	#ifdef _DEBUG
			   CNT_CONTAR( "GRA_IrInicio-pr0" ) ;
	#endif
	if(pGrafo->pVerticeCorrente == NULL){
		#ifdef _DEBUG
			   CNT_CONTAR( "GRA_IrInicio-if1" ) ;
		#endif
		return GRA_CondRetGrafoVazio;
	}
	#ifdef _DEBUG
			CNT_CONTAR( "GRA_IrInicio-pr1" ) ;
	#endif

	LIS_IrInicioLista(pGrafo->pListaVertices);

	return GRA_CondRetOK;

} /* Fim função: GRA &Ir Inicio */

/***************************************************************************
*
*  Função: GRA  -Pesquisar Vertice no Grafo
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
  

/**************************************************************************/


  /*Inicio das funções de verificação do Grafo */

/***************************************************************************
*
*  Função: GRA  &Verificar Grafo
*  ****/

#ifdef _DEBUG 

GRA_tpCondRet GRA_VerificarGrafo( GRA_tppGrafo pGrafo, int * qtdErros )
{	

	int tamTotal, numVert, tamValor;
	*qtdErros = 0;

	tamTotal = numVert = 0;

	#ifdef _DEBUG
		CNT_CONTAR( "GRA_VerificarGrafo" ) ;
	#endif

	if ( GRA_VerificarCabecaGrafo( pGrafo, qtdErros ) != GRA_CondRetOK ){
		return GRA_CondRetErroEstrutura ;
	} 

	CED_MarcarEspacoAtivo( pGrafo ) ;

	GRA_IrInicio(pGrafo);

	do{
		numVert++;
		if ( GRA_VerificarVertice(pGrafo->pVerticeCorrente, qtdErros, &tamValor) != GRA_CondRetOK ){
			return GRA_CondRetErroEstrutura ;
		}
		tamTotal += tamValor;

	}while(GRA_AvancarVerticeCorrente(pGrafo) != GRA_CondRetFimGrafo);

	if(numVert != pGrafo->numVert){
		TST_NotificarFalha( "Quantidade incorreta de vertices." ) ;
		(*qtdErros)++;
		return GRA_CondRetErroEstrutura ;
	}

	if(tamTotal != pGrafo->tamTotal){
		TST_NotificarFalha( "Tamanho total incorreto." ) ;
		(*qtdErros)++;
		return GRA_CondRetErroEstrutura ;
	}

	return GRA_CondRetOK ;

} /* Fim função: GRA  &Verificar Grafo */

/***************************************************************************
*
*  Função: GRA  &Verificar Cabeça Grafo
*  ****/

GRA_tpCondRet GRA_VerificarCabecaGrafo( void * pCabecaParm, int *qtdErros )
{
	GRA_tppGrafo pGrafo = NULL ;
	GRA_tpCondRet cond = GRA_CondRetOK;

	#ifdef _DEBUG
		CNT_CONTAR( "GRA_VerificarCabecaGrafo" ) ;
	#endif

	/* Verifica o tipo do espaço */

	if ( pCabecaParm == NULL )
	{
		TST_NotificarFalha( "Tentou verificar cabeca inexistente." ) ;
		(*qtdErros)++;
		cond = GRA_CondRetErroEstrutura ;
	} 

	if ( ! CED_VerificarEspaco( pCabecaParm , NULL ))
	{
		TST_NotificarFalha( "Controle do espaco acusou erro." ) ;
		(*qtdErros)++;
		cond = GRA_CondRetErroEstrutura ;
	} 

	if ( TST_CompararInt( GRA_TipoEspacoCabeca ,
		CED_ObterTipoEspaco( pCabecaParm ) ,
		"Tipo do espaço de dados nao eh cabeca de Grafo." ) != TST_CondRetOK )
	{
		(*qtdErros)++;
		cond = GRA_CondRetErroEstrutura ;
	} 

	pGrafo = ( GRA_tppGrafo )( pCabecaParm ) ;

	/* Verifica corrente */

	if(pGrafo->pVerticeCorrente == NULL && pGrafo->numVert > 0){
		TST_NotificarFalha( "Grafo com elementos e vertice corrente nulo." ) ;
		(*qtdErros)++;
		cond =  GRA_CondRetErroEstrutura ;
	}

	if(pGrafo->pListaVertices == NULL && pGrafo->numVert > 0){
		TST_NotificarFalha( "Grafo com elementos e lista vertices nula." ) ;
		(*qtdErros)++;
		cond = GRA_CondRetErroEstrutura ;
	}

	if ( pGrafo->pVerticeCorrente != NULL )
	{
		if ( TST_CompararPonteiro( pCabecaParm , pGrafo->pVerticeCorrente->pCabeca ,
			"Vertice corrente nao aponta para cabeca." ) != TST_CondRetOK )
		{
			(*qtdErros)++;
			cond =  GRA_CondRetErroEstrutura ;
		} 
	} 
	else if ( TST_CompararPonteiro( NULL , pGrafo->pVerticeCorrente ,
		"Grafo nao vazio tem vertice corrente NULL." ) != TST_CondRetOK )
	{
		(*qtdErros)++;
		cond = GRA_CondRetErroEstrutura ;
	} 

	return cond ;

} /* Fim função: GRA  &Verificar Cabeça Grafo */


/***************************************************************************
*
*  Função: GRA  &Verificar um Vértice do Grafo
*  ****/

GRA_tpCondRet GRA_VerificarVertice( void * pVerticeParm, int *qtdErros, int *tamValor )
{
	GRA_tpCondRet cond = GRA_CondRetOK;
	GRA_tppVerticeGrafo pVertice = NULL ;
	GRA_tppGrafo        pGrafo   = NULL ;

	#ifdef _DEBUG
		CNT_CONTAR( "GRA_VerificarVertice" ) ;
	#endif

	/* Verificar se é nó estrutural */

	if ( pVerticeParm == NULL )
	{
		TST_NotificarFalha( "Tentou verificar vertice inexistente." ) ;
		(*qtdErros)++;
		cond = GRA_CondRetErroEstrutura ;
	}

	if ( ! CED_VerificarEspaco( pVerticeParm , NULL ))
	{
		TST_NotificarFalha( "Controle do espaço acusou erro." ) ;
		(*qtdErros)++;
		cond =  GRA_CondRetErroEstrutura ;
	} 

	if ( TST_CompararInt( GRA_TipoEspacoVertice ,
		CED_ObterTipoEspaco( pVerticeParm ) ,
		"Tipo do espaco de dados nao eh vertice do Grafo." ) != TST_CondRetOK )
	{
		(*qtdErros)++;
		cond = GRA_CondRetErroEstrutura ;
	} 

	pVertice  = ( GRA_tppVerticeGrafo )( pVerticeParm ) ;
	pGrafo    = pVertice->pCabeca ;

	if(CED_ObterTamanhoValor(pVertice) != pVertice->tamValor){
		TST_NotificarFalha( "Tamanho do vertice incorreto" ) ;
		(*qtdErros)++;
		cond = GRA_CondRetErroEstrutura ;
	}

	*tamValor = pVertice->tamValor;

	/* Verificar cabeça */

	if ( pGrafo->pVerticeCorrente != NULL  )
	{
		if ( TST_CompararPonteiro( pGrafo , pGrafo->pVerticeCorrente->pCabeca ,
			"Vertice não pertence ao Grafo." ) != TST_CondRetOK )
		{
			(*qtdErros)++;
			cond = GRA_CondRetErroEstrutura ;
		} 
	} 
	else{

		TST_NotificarFalha( "Vertice pertence a Grafo vazio." ) ;
		(*qtdErros)++;
		cond = GRA_CondRetErroEstrutura ;
	} 

	/* Verificar pai */

	if ( pVertice->pCabeca != NULL )
	{
		if ( ( pVertice->pCabeca->pVerticeCorrente != pVertice ))
		{
			(*qtdErros)++;
			cond = GRA_CondRetErroEstrutura ;
		} 
	} 
	else if ( TST_CompararPonteiro( pVertice , pGrafo->pVerticeCorrente ,
		"Vertice nao eh apontado por cabeça do Grafo." ) != TST_CondRetOK )
	{
		(*qtdErros)++;
		cond = GRA_CondRetErroEstrutura ;
	}

	return cond ;

} /* Fim função: GRA  &Verificar um Vértice do Grafo */


/***************************************************************************
*
*  Função: GRA  &Deturpar Grafo
*  ****/

void GRA_Deturpar( GRA_tppGrafo pGrafo, GRA_tpModosDeturpacao tipo)
{
	GRA_tppVerticeGrafo pVertice;
	void *id;

	#ifdef _DEBUG
		CNT_CONTAR( "GRA_Deturpar" ) ;
	#endif

	if(pGrafo == NULL)
		return ;

	if(tipo == DeturpaQtdVert){  // Tipo 1
		pGrafo->numVert = -1;
	}
	else if(tipo == DeturpaVertCorrenteNulo){  //Tipo 2
		if(pGrafo->pVerticeCorrente != NULL)
			pGrafo->pVerticeCorrente = NULL;
	}
	else if(tipo == DeturpaLisVertNulo){  // Tipo 3
		if(pGrafo->pListaVertices != NULL)
			pGrafo->pListaVertices = NULL;
	}
	else if(tipo == DeturpaCabecaNulo){  // Tipo 4
		pGrafo = NULL;
	}
	else if(tipo == DeturpaValorVertCorrenteNulo){  // Tipo 5: 
		if(pGrafo->pVerticeCorrente->pValor != NULL)
			pGrafo->pVerticeCorrente->pValor = NULL;
	}
	else if(tipo == DeturpaEspacoCabeca){ // Tipo 6
		CED_DefinirTipoEspaco( pGrafo , CED_ID_TIPO_VALOR_NULO ) ;
	}
	else if(tipo == DeturpaEspacoVerticeCorrente){  // Tipo 7
		if(pGrafo->pVerticeCorrente != NULL)
			CED_DefinirTipoEspaco( pGrafo->pVerticeCorrente, CED_ID_TIPO_VALOR_NULO );
	}
	else if(tipo == DeturpaTamCabeca){  // Tipo 8
		pGrafo->tamTotal = -1;
	}
	else if(tipo == DeturpaTamVerticeCorrente ){  // Tipo 9
		if(pGrafo->pVerticeCorrente != NULL)
			pGrafo->pVerticeCorrente->tamValor = -1;
	}
	else if(tipo == DeturpaPtCabecaNulo){ // Tipo 10
		if(pGrafo->pVerticeCorrente != NULL)
			pGrafo->pVerticeCorrente->pCabeca = NULL;
	}


} /* Fim função: GRA &Deturpar Grafo */

/***************************************************************************
*
*  Função: GRA  &Corrige Quantidade de vértices
*  ****/

GRA_tpCondRet GRA_CorrigeQuantidadeVertices( GRA_tppGrafo pGrafo)
{
	int qtdVert = 0;
	void * pAux;
	GRA_tpCondRet cond;
	GRA_tppVerticeGrafo pVertice;

	#ifdef _DEBUG
		CNT_CONTAR( "GRA_CorrigeQuantidadeVertices" ) ;
	#endif

	CED_InicializarIteradorEspacos();

	do{
		pAux = CED_ObterPonteiroEspacoCorrente();
		if ( TST_CompararInt( GRA_TipoEspacoVertice, 
			CED_ObterTipoEspaco( pAux ), "Corrigindo Grafo") == TST_CondRetOK){

				cond = GRA_VerificaVerticeExiste(pGrafo, pAux);
				if(cond == GRA_CondRetVerticeNExiste){  // Inserir Vértice Perdido
					pVertice = (GRA_tppVerticeGrafo) pAux;
					if(pVertice->pCabeca == pGrafo){   // Vértice pertence ao Grafo
						qtdVert ++;  //Mais um vértice encontrado
						GRA_InserirVertice(pGrafo, pAux, pVertice->id );
					}
				}
		}

	}while(CED_AvancarProximoEspaco() == 0);

	pGrafo->numVert = qtdVert;

	return GRA_CondRetOK;

} /* Fim função: GRA &Corrige Quantidade de vértices */

#endif  /*Fim das funções de verificação do Grafo */

/********** Fim do módulo de implementação: GRA Grafo Não Dirigido Genérico com Cabeça**********/