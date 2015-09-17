
@ECHO off
setlocal enabledelayedexpansion
cls
@echo This is File Tracer > FileTrace.txt
set /a j=0
set /a i=-1  
set /a m=0  
set loop=abcdefghijklmnopqrstuvwxyz 

:while
if %j% lss 27 (

set lc=!loop:~%j%,1!
   pin.exe -t FileTrace.dll -- TestCheckers2.exe ab !lc!
 

 set /p texte=< FileTrace.csv

 if %j% gtr  0 (	
 
set ld=!loop:~%i%,1!
  @echo %texte% :Input %m%  >> FileTrace.txt
   
 )
set /a j+=1
set /a i+=1
set /a m+=1   
  goto :while
)

sort FileTrace.txt /O FileTraceSorted.txt
 





 



