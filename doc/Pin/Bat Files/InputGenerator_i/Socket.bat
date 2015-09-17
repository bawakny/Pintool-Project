
@echo off
cls
@echo This is Socket Check > socket.txt
set /a i=1
set /a j=0
set  c=a


:while
if %j% lss 121 (
  

  pin.exe -t Socket.dll -- TestCheckers.exe %c%
 

 set /p texte=< socketcheck.csv
 
 if %i% gtr  1 (
  @echo %texte% :Input %j%  >> socket.txt 
  ) 

  set /a i+=1
    set /a j+=1
  set c=%c%a
  goto :while

)

 
sort Socket.txt /O socketSorted.txt



