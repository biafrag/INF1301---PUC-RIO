@ECHO OFF

if exist ..\scripts\estatisticas_grafodebug.estat        del ..\scripts\estatisticas_grafodebug.estat
if exist ..\produto\TesteGrafoDebug.log  del ..\produto\TesteGrafoDebug.log

..\produto\TRAB4-5.EXE   /s..\scripts\TesteContador           /l..\produto\TesteGrafoDebug        /a..\scripts\estatisticas_grafodebug
if errorlevel 4 goto sai

if exist ..\produto\TesteGrafoDebug.log goto faz
goto sai

:faz

notepad ..\produto\TesteGrafoDebug.log

:sai