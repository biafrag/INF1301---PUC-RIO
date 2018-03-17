#if ! defined( REDE_ )
#define REDE_

  /***************************************************************************
*
*  $MCD M�dulo de defini��o: RED Rede
*
*  Arquivo gerado:             REDE.h
*  Letras identificadoras:      RED
*
*  Projeto: T4 INF 1301 2017.2
*  Autores: ap - Andr� Pessanha
*           bg - Bianca Gomes
*           bf - Bianca Fragoso
*
*  $HA Hist�rico de evolu��o:
*   Vers�o  Autor    Data       Observa��es
*     7        bf   20/nov/2017 mudancas para fazer algumas consultas ao usuario
*     6      ap   04/nov/2017 Implementa��o da funcionalidade da op��o 8 e 9 do menu.
*	  5      ap   02/nov/2017 Implementa��o da funcionalidade da op��o 6 do menu.
*	  4      ap   30/out/2017 Implementa��o da funcionalidade das op��es 2 e 5 do menu.
*	  3      ap   28/out/2017 Implementa��o da funcionalidade das op��es 1;3;4 e 7 do menu.
*     2      bf   28/out/2017 continua��o com algumas altera��es para uso do m�dulo usu�rio 
*     1      ap   26/out/2017 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Implementa a interface da rede de relacionamentos.
*     
*
***************************************************************************/
 
#if defined( REDE_OWN )
   #define REDE_EXT
#else
   #define REDE_EXT extern
#endif
#include "GRAFO.h"
#include "USUARIO.h"
#include "MENSAGEM.h"


/***** Declara��es exportadas pelo m�dulo *****/



/***********************************************************************
*
*  $TC Tipo de dados: RED Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da rede
*
***********************************************************************/

#undef REDE_EXT

#else
#endif