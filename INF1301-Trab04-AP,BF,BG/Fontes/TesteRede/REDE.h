#if ! defined( REDE_ )
#define REDE_

  /***************************************************************************
*
*  $MCD Módulo de definição: RED Rede
*
*  Arquivo gerado:             REDE.h
*  Letras identificadoras:      RED
*
*  Projeto: T4 INF 1301 2017.2
*  Autores: ap - André Pessanha
*           bg - Bianca Gomes
*           bf - Bianca Fragoso
*
*  $HA Histórico de evolução:
*   Versão  Autor    Data       Observações
*     7        bf   20/nov/2017 mudancas para fazer algumas consultas ao usuario
*     6      ap   04/nov/2017 Implementação da funcionalidade da opção 8 e 9 do menu.
*	  5      ap   02/nov/2017 Implementação da funcionalidade da opção 6 do menu.
*	  4      ap   30/out/2017 Implementação da funcionalidade das opções 2 e 5 do menu.
*	  3      ap   28/out/2017 Implementação da funcionalidade das opções 1;3;4 e 7 do menu.
*     2      bf   28/out/2017 continuação com algumas alterações para uso do módulo usuário 
*     1      ap   26/out/2017 início desenvolvimento
*
*  $ED Descrição do módulo
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


/***** Declarações exportadas pelo módulo *****/



/***********************************************************************
*
*  $TC Tipo de dados: RED Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da rede
*
***********************************************************************/

#undef REDE_EXT

#else
#endif