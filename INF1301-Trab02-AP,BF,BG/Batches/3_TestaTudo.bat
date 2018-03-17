if exist ..\scripts\estatisticas_lista.estat        del ..\scripts\estatisticas_lista.estat
if exist ..\scripts\estatisticas_embaralhar.estat   del ..\scripts\estatisticas_grafo.estat

del ..\produto\*.log

..\produto\TRAB1-1          /s..\scripts\TesteLista         /l..\produto\TesteLista           /a..\scripts\estatisticas_lista
if errorlevel 4 goto sai

..\produto\TRAB1-2          /s..\scripts\TesteGrafo    /l..\produto\TesteGrafo      /a..\scripts\estatisticas_grafo
if errorlevel 4 goto sai

if exist ..\produto\*.log goto faz
goto sai

:faz

copy ..\produto\*.log ..\produto\TestaTudo.log
notepad ..\produto\TestaTudo.log

:sai

