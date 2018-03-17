@ECHO Gerando todos os arquivos necessarios para compilação dos projetos...

pushd  .

..\ferramnt\Gmake  /b..\composicao  /c..\composicao\TesteLista
..\ferramnt\Gmake  /b..\composicao  /c..\composicao\TesteGrafo

popd
 