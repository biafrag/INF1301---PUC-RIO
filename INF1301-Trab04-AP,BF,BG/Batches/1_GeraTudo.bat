@ECHO Gerando todos os arquivos necessarios para compilação dos projetos...

pushd  .

..\ferramnt\Gmake  /b..\composicao  /c..\composicao\TesteLista
..\ferramnt\Gmake  /b..\composicao  /c..\composicao\TesteGrafo
..\ferramnt\Gmake  /b..\composicao  /c..\composicao\TesteUsuario
..\ferramnt\Gmake  /b..\composicao  /c..\composicao\TesteMensagem
..\ferramnt\Gmake  /b..\composicao  /c..\composicao\TesteRede
..\ferramnt\Gmake  /b..\composicao  /c..\composicao\TesteGrafoDebug

popd
 