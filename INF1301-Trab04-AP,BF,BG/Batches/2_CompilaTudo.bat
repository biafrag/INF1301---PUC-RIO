@ECHO Iniciando o ambiente (environment) para compilar com o Microsoft Visual Studio ...

Call ..\ferramnt\vsvars32.bat

del ..\produto\*.err
del ..\objetos\*.obj

@ECHO Compilando todos os testes...

pushd .
 
nmake /F..\composicao\TesteLista.make
nmake /F..\composicao\TesteGrafo.make 
nmake /F..\composicao\TesteUsuario.make
nmake /F..\composicao\TesteMensagem.make 
nmake /F..\composicao\TesteRede.make
nmake /F..\composicao\TesteGrafoDebug.make 

popd

del ..\objetos\*.obj

if exist ..\produto\*.err goto faz
goto sai

:faz

copy ..\produto\*.err ..\produto\compilatudo.err
notepad ..\produto\compilatudo.err

:sai