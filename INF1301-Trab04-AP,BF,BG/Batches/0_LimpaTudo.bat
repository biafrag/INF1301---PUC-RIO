@ECHO Removendo todos os arquivos criados após os ultimos testes...

pushd .

cd ..\Batches
del *.bak

cd ..\Composicao
del *.bak
del *.list
del *.make

cd ..\Fontes
del *.bak
del *.err

cd ..\Objetos
del *.bak
del *.obj
del *.build

cd ..\Produto
del *.bak
del *.log
del *.exe
del *.err

cd ..\Projeto
del *.bak

cd ..\Tabelas
del *.bak

cd ..\Scripts
del *.bak
del *.estat

cd ..\..\Documentos
del *.bak

cd ..\Ferramnt
del *.bak
del *.err
del *.obj

popd