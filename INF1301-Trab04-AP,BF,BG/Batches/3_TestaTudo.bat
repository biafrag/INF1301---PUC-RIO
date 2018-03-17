if exist ..\scripts\estatisticas_lista.estat        del ..\scripts\estatisticas_lista.estat
if exist ..\scripts\estatisticas_grafo.estat   del ..\scripts\estatisticas_grafo.estat
if exist ..\scripts\estatisticas_usuario.estat   del ..\scripts\estatisticas_usuario.estat
if exist ..\scripts\estatisticas_mensagem.estat   del ..\scripts\estatisticas_mensagem.estat
if exist ..\scripts\estatisticas_grafodebug.estat   del ..\scripts\estatisticas_grafodebug.estat
if exist ..\scripts\estatisticas_rede.estat   del ..\scripts\estatisticas_rede.estat

del ..\produto\*.log

..\produto\TRAB4-1.EXE          /s..\scripts\TesteLista         /l..\produto\TesteLista           /a..\scripts\estatisticas_lista
if errorlevel 4 goto sai

..\produto\TRAB4-2.EXE          /s..\scripts\TesteGrafo    /l..\produto\TesteGrafo      /a..\scripts\estatisticas_grafo
if errorlevel 4 goto sai

..\produto\TRAB4-3.EXE           /s..\scripts\TesteUsuario        /l..\produto\TesteUsuario         /a..\scripts\estatisticas_usuario
if errorlevel 4 goto sai

..\produto\TRAB4-4.EXE          /s..\scripts\TesteMensagem        /l..\produto\TesteMensagem         /a..\scripts\estatisticas_mensagem
if errorlevel 4 goto sai

..\produto\TRAB4-5.EXE   		/s..\scripts\TesteContador           /l..\produto\TesteGrafoDebug        /a..\scripts\estatisticas_grafodebug
if errorlevel 4 goto sai


if exist ..\produto\*.log goto faz
goto sai

:faz

copy ..\produto\*.log ..\produto\TestaTudo.log
notepad ..\produto\TestaTudo.log

:sai

