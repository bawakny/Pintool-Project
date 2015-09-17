
@echo off
cls
@echo This is a test of time> timeCheck.txt
set /a j=0
set /a i=1
set  c=a


:while
if %j% lss 121 (
  

  pin.exe -t Time.dll -- TestCheckers.exe %c%

 
 set /p texte=< timeCheck.csv
 
 if %i% gtr  1 (
  @echo %texte% :Input %j%  >> timeCheck.txt

   )

  set /a i+=1
   set /a j+=1
  set c=%c%a
  goto :while
)

sort timeCheck.txt /O timeSorted.txt



 



