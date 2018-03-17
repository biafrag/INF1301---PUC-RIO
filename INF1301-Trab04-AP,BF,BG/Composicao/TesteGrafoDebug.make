##################################################
###
### Diretivas de MAKE para o construto: TesteGrafoDebug
### Gerado a partir de: ..\composicao\TesteGrafoDebug.comp
###
### ----- Arquivo gerado, NÃO EDITE!!! -----
###
##################################################

### Nomes globais

NOME            = TesteGrafoDebug


### Nomes de paths

Pdef                 = ..\Tabelas
Ph                   = ..\Fontes\TesteGrafoDebug
Pobj                 = ..\Objetos
Perr                 = ..\Produto
PDEFAULT             = ..\Fontes\TesteGrafoDebug
Pc                   = ..\Fontes\TesteGrafoDebug

### Nomes de diretórios para geração

Fdef                 = ..\Tabelas
Fh                   = ..\Fontes\TesteGrafoDebug
Fobj                 = ..\Objetos
Ferr                 = ..\Produto
FDEFAULT             = ..\Fontes\TesteGrafoDebug
Fc                   = ..\Fontes\TesteGrafoDebug

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
    ..\\tabelas\\idtiposespaco.def {$(Ph)}cespdin.h            {$(Ph)}conta.h              \
    {$(Ph)}generico.h           {$(Ph)}grafo.h              {$(Ph)}lista.h              \
    {$(Pdef)}tiposespacosgrafo.def {$(Ph)}tst_espc.h          
   cl /D_DEBUG $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

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
### Fim de diretivas MAKE para o construto: TesteGrafoDebug
###
##################################################

