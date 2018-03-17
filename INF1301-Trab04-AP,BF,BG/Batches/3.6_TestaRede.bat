@ECHO OFF

if exist ..\scripts\estatisticas_rede.estat        del ..\scripts\estatisticas_rede.estat
if exist ..\produto\TesteRede.log  del ..\produto\TesteRede.log

..\produto\TRAB4-6.EXE           /s..\scripts\TesteRede       /l..\produto\TesteRede        /a..\scripts\estatisticas_rede
if errorlevel 4 goto sai

if exist ..\produto\TesteRede.log goto faz
goto sai

:faz

notepad ..\produto\TesteRede.log

:sai