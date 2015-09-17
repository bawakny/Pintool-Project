
@ECHO off
setlocal enabledelayedexpansion
cls
@echo This is Stack Depth test > StackDepth.txt
set /a j=0
set /a i=-1  
 
set loop=abcdefghijklmnopqrstuvwxyz 

:while
if %j% lss 27 (

set lc=!loop:~%j%,1!
   pin.exe -t StackDepth.dll -- TestCheckers2.exe ab !lc!
 

 set /p texte=< StackDepth.csv

 if %j% gtr  0 (	
 
set ld=!loop:~%i%,1!
  @echo %texte% :Input %i%  >> StackDepth.txt
   
 )
set /a j+=1
set /a i+=1 
 
  goto :while
)

sort StackDepth.txt /O StackDepthSorted.txt




 



