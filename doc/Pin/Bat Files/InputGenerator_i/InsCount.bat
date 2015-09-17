
@echo off
cls
@echo This is Instruction Counter > inscount.txt
set /a i=1
set /a j=0
set  c=a

:while
if %j% lss 121 (
  

  pin.exe -t InsCount.dll -- TestCheckers.exe %c%


 set /p texte=< InsCount.csv
 
 if %i% gtr  1 (
  @echo %texte% :Input %j%  >> inscount.txt 
   )

  set /a i+=1
  set /a j+=1
  set c=%c%a
  goto :while


)

sort InsCount.txt /O inscountSorted.txt



 



