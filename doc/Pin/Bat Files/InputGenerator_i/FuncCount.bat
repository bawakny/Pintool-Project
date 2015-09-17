
@echo off

cls
@echo This is Functions Counter > FunctionsCount.txt
set /a i=1
set /a j=0
set  c=a

:while
if %j% lss 121 (
  

  pin.exe -t FunctionsCount.dll -- TestCheckers.exe %c%
  
 
 set /p texte=< FunctionsCount.csv
 
 if %i% gtr  1 (
  @echo %texte% :Input %j%  >> FunctionsCount.txt

)
   



  set /a i+=1
  set /a j+=1
  set c=%c%a
  goto :while
 )

sort FunctionsCount.txt /O FunctionsCountSorted.txt


 



