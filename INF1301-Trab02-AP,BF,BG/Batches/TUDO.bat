@ECHO Limpar tudo que sera regerado
Call 0_LimpaTudo

@ECHO Gerar todos os scripts de make
Call 1_GeraTudo

@ECHO Compilar todos os programas modulo
Call 2_CompilaTudo

@ECHO Testar todos os scripts
Call 3_TestaTudo

pause