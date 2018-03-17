##################################################
###
### Diretivas de MAKE para o construto: TesteRede
### Gerado a partir de: ..\composicao\TesteRede.comp
###
### ----- Arquivo gerado, NÃO EDITE!!! -----
###
##################################################

### Nomes globais

NOME            = TesteRede


### Nomes de paths

Ph                   = ..\Fontes\TesteRede
Pobj                 = ..\Objetos
Perr                 = ..\Produto
PDEFAULT             = ..\Fontes\TesteRede
Pc                   = ..\Fontes\TesteRede

### Nomes de diretórios para geração

Fh                   = ..\Fontes\TesteRede
Fobj                 = ..\Objetos
Ferr                 = ..\Produto
FDEFAULT             = ..\Fontes\TesteRede
Fc                   = ..\Fontes\TesteRede

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
   $(Fobj)\testerede.obj   $(Fobj)\rede.obj   $(Fobj)\lista.obj \
   $(Fobj)\usuario.obj   $(Fobj)\lista.obj   $(Fobj)\mensagem.obj \
   $(Fobj)\grafo.obj \
   Construto

### Limpar arquivos

limpa :
   if exist $(Ferr)\$(NOME).err  del $(Ferr)\$(NOME).err


### Dependências de módulos objeto a compilar

$(Fobj)\testerede.obj :  {$(Pc)}\testerede.c \
    {$(Ph)}generico.h           {$(Ph)}grafo.h              {$(Ph)}lerparm.h            \
    {$(Ph)}lista.h              {$(Ph)}tst_espc.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\rede.obj :  {$(Pc)}\rede.c \
    {$(Ph)}grafo.h              {$(Ph)}lista.h              {$(Ph)}mensagem.h           \
    {$(Ph)}rede.h               {$(Ph)}usuario.h           
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\lista.obj :  {$(Pc)}\lista.c \
    {$(Ph)}lista.h             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\usuario.obj :  {$(Pc)}\usuario.c \
    {$(Ph)}lista.h              {$(Ph)}mensagem.h           {$(Ph)}usuario.h           
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\lista.obj :  {$(Pc)}\lista.c
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\mensagem.obj :  {$(Pc)}\mensagem.c \
    {$(Ph)}lista.h              {$(Ph)}mensagem.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\grafo.obj :  {$(Pc)}\grafo.c \
    {$(Ph)}grafo.h              {$(Ph)}lista.h             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err


### Terminação

Construto : \
   $(Fobj)\testerede.obj   $(Fobj)\rede.obj   $(Fobj)\lista.obj \
   $(Fobj)\usuario.obj   $(Fobj)\lista.obj   $(Fobj)\mensagem.obj \
   $(Fobj)\grafo.obj
    cd $(Fobj)
    LINK $(L) @$(NOME).build >> $(Ferr)\$(NOME).err

##################################################
###
### Fim de diretivas MAKE para o construto: TesteRede
###
##################################################

