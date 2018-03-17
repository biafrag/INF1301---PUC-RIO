@ECHO OFF

if exist ..\scripts\estatisticas_grafo.estat        del ..\scripts\estatisticas_grafo.estat
if exist ..\produto\TesteGrafo.log  del ..\produto\TesteGrafo.log

..\produto\TRAB1-2           /s..\scripts\TesteGrafo         /l..\produto\TesteGrafo         /a..\scripts\estatisticas_grafo
if errorlevel 4 goto sai

if exist ..\produto\TesteGrafo.log goto faz
goto sai

:faz

notepad ..\produto\TesteGrafo.log

:sai