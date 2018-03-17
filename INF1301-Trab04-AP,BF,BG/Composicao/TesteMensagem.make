##################################################
###
### Diretivas de MAKE para o construto: TesteMensagem
### Gerado a partir de: ..\composicao\TesteMensagem.comp
###
### ----- Arquivo gerado, NÃO EDITE!!! -----
###
##################################################

### Nomes globais

NOME            = TesteMensagem


### Nomes de paths

Ph                   = ..\Fontes\TesteMensagem
Pobj                 = ..\Objetos
Perr                 = ..\Produto
PDEFAULT             = ..\Fontes\TesteMensagem
Pc                   = ..\Fontes\TesteMensagem

### Nomes de diretórios para geração

Fh                   = ..\Fontes\TesteMensagem
Fobj                 = ..\Objetos
Ferr                 = ..\Produto
FDEFAULT             = ..\Fontes\TesteMensagem
Fc                   = ..\Fontes\TesteMensagem

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
   $(Fobj)\testmen.obj   $(Fobj)\mensagem.obj   $(Fobj)\lista.obj \
   Construto

### Limpar arquivos

limpa :
   if exist $(Ferr)\$(NOME).err  del $(Ferr)\$(NOME).err


### Dependências de módulos objeto a compilar

$(Fobj)\testmen.obj :  {$(Pc)}\testmen.c \
    {$(Ph)}generico.h           {$(Ph)}lerparm.h            {$(Ph)}lista.h              \
    {$(Ph)}mensagem.h           {$(Ph)}tst_espc.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\mensagem.obj :  {$(Pc)}\mensagem.c \
    {$(Ph)}lista.h              {$(Ph)}mensagem.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\lista.obj :  {$(Pc)}\lista.c \
    {$(Ph)}lista.h             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err


### Terminação

Construto : \
   $(Fobj)\testmen.obj   $(Fobj)\mensagem.obj   $(Fobj)\lista.obj
    cd $(Fobj)
    LINK $(L) @$(NOME).build >> $(Ferr)\$(NOME).err

##################################################
###
### Fim de diretivas MAKE para o construto: TesteMensagem
###
##################################################

