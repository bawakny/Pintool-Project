
@echo off
cls
@echo This is a test of StackDepth> stackdepth.txt
set /a i=1
set /a j=0
set  c=a


:while
if %j% lss 121 (
  

  pin.exe -t StackDepth.dll -- TestCheckers.exe %c%


 set /p texte=< stackdepth.csv
 
 if %i% gtr  1 (
  @echo %texte% :Input %j%  >> stackdepth.txt 
   )

  set /a i+=1
  set /a j+=1
  set c=%c%a
  goto :while

)


sort StackDepth.txt /O StackDepthSorted.txt
 



