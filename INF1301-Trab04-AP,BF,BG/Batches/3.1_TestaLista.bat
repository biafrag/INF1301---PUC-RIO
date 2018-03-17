@ECHO OFF

if exist ..\scripts\estatisticas_lista.estat        del ..\scripts\estatisticas_lista.estat
if exist ..\produto\TesteLista.log  del ..\produto\TesteLista.log

..\produto\TRAB4-1.EXE           /s..\scripts\TesteLista         /l..\produto\TesteLista         /a..\scripts\estatisticas_lista
if errorlevel 4 goto sai

if exist ..\produto\TesteLista.log goto faz
goto sai

:faz

notepad ..\produto\TesteLista.log

:sai