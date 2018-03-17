/**********************************************************************************
*  $MCI M�dulo de implementa��o: TGRA Teste Grafo de s�mbolos
*
*  Arquivo gerado:              TestGRA.c
*  Letras identificadoras:      TGRA
*
*  Projeto: T4 INF 1301 2017.2
*  Autores: ap - Andr� Pessanha
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

static const char START_TEST_CMD         [ ] = "=startteste"     ;

TST_tpCondRet TST_EfetuarComando(char * ComandoTeste)
   {
      if(strcmp(ComandoTeste, START_TEST_CMD)==0)
          return TST_CondRetOK ;

      return TST_CondRetNaoConhec ;
   } /* Fim fun��o: TCAR &Testar Partida*/


