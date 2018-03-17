@ECHO OFF

if exist ..\scripts\estatisticas_mensagem.estat        del ..\scripts\estatisticas_mensagem.estat
if exist ..\produto\TesteMensagem.log  del ..\produto\TesteMensagem.log

..\produto\TRAB4-4.EXE          /s..\scripts\TesteMensagem        /l..\produto\TesteMensagem         /a..\scripts\estatisticas_mensagem
if errorlevel 4 goto sai

if exist ..\produto\TesteMensagem.log goto faz
goto sai

:faz

notepad ..\produto\TesteMensagem.log

:sai