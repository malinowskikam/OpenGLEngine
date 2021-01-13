g++ *.cpp -lopengl32 -lglew32 -lglfw3dll -lfreetype -m64 -pipe
if($LASTEXITCODE -eq 0)
{
    ./a
}
else
{
    write-host("Nie skompilowalo sie")
}