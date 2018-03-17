##################################################
###
### Diretivas de MAKE para o construto: TesteGrafo
### Gerado a partir de: ..\composicao\TesteGrafo.comp
###
### ----- Arquivo gerado, NÃO EDITE!!! -----
###
##################################################

### Nomes globais

NOME            = TesteGrafo


### Nomes de paths

Ph                   = ..\Fontes\TesteGrafo
Pobj                 = ..\Objetos
Perr                 = ..\Produto
PDEFAULT             = ..\Fontes\TesteGrafo
Pc                   = ..\Fontes\TesteGrafo

### Nomes de diretórios para geração

Fh                   = ..\Fontes\TesteGrafo
Fobj                 = ..\Objetos
Ferr                 = ..\Produto
FDEFAULT             = ..\Fontes\TesteGrafo
Fc                   = ..\Fontes\TesteGrafo

### Macros da plataforma


O       = /D_CRT_SECURE_NO_DEPRECATE
OD      = /Zi /Od /D_CRT_SECURE_NO_DEPRECATE
L       =
LD      = /DEBUG /DEBUGTYPE:CV

!IFDEF PRD
O       = /Ox /D_CRT_SECURE_NO_DEPRECATE
!ENDIF

OPT     = /c /J /W4 /nologo
INCLUDE = $(INCLUDE);$(PDEFAULT)


### Regras de geração

all : limpa \
   $(Fobj)\testgra.obj   $(Fobj)\grafo.obj   $(Fobj)\lista.obj \
   Construto

### Limpar arquivos

limpa :
   if exist $(Ferr)\$(NOME).err  del $(Ferr)\$(NOME).err


### Dependências de módulos objeto a compilar

$(Fobj)\testgra.obj :  {$(Pc)}\testgra.c \
    {$(Ph)}generico.h           {$(Ph)}grafo.h              {$(Ph)}lerparm.h            \
    {$(Ph)}lista.h              {$(Ph)}tst_espc.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\grafo.obj :  {$(Pc)}\grafo.c \
    {$(Ph)}grafo.h              {$(Ph)}lista.h             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\lista.obj :  {$(Pc)}\lista.c \
    {$(Ph)}lista.h             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err


### Terminação

Construto : \
   $(Fobj)\testgra.obj   $(Fobj)\grafo.obj   $(Fobj)\lista.obj
    cd $(Fobj)
    LINK $(L) @$(NOME).build >> $(Ferr)\$(NOME).err

##################################################
###
### Fim de diretivas MAKE para o construto: TesteGrafo
###
##################################################

