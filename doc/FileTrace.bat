@echo off

cls
@echo This is CreateFile tracer > FileTrace.txt
set /a i=1
set /a j=0
set  c=a

:while
if %j% lss 121 (
  

  pin.exe -t fileTrace.dll -- TestCheckers.exe %c%
  
 
 set /p texte=< fileTrace.csv
 
 if %i% gtr  1 (
  @echo %texte% :Input %j%  >> FileTrace.txt 

)
   


  set /a i+=1
  set /a j+=1
  set c=%c%a
  goto :while
 )

sort FileTrace.txt /O FileTraceSorted.txt


 



