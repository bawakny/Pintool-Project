
@ECHO off
setlocal enabledelayedexpansion
cls
@echo  This is Double Free detection > DoubleFree.txt
set /a j=0
set /a i=-1 
set /a m=0   
set loop=abcdefghijklmnopqrstuvwxyz 

:while
if %j% lss 27 (

set lc=!loop:~%j%,1!
   pin.exe -t DoubleFree.dll -- TestCheckers2.exe ab !lc!
 

 set /p texte=< DoubleFree.csv

 if %j% gtr  0 (	
 
set ld=!loop:~%i%,1!
  @echo %texte% :Input !ld!  >> DoubleFree.txt
   
 )
set /a j+=1
set /a i+=1  
set /a m+=1 
  goto :while
)

sort DoubleFree.txt /O DoubleFreeSorted.txt

DoubleFreeSorted.txt




 



