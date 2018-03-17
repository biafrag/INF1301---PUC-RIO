@ECHO OFF

if exist ..\scripts\estatisticas_usuario.estat        del ..\scripts\estatisticas_usuario.estat
if exist ..\produto\TesteUsuario.log  del ..\produto\TesteUsuario.log

..\produto\TRAB4-3.EXE          /s..\scripts\TesteUsuario        /l..\produto\TesteUsuario         /a..\scripts\estatisticas_usuario
if errorlevel 4 goto sai

if exist ..\produto\TesteUsuario.log goto faz
goto sai

:faz

notepad ..\produto\TesteUsuario.log

:sai