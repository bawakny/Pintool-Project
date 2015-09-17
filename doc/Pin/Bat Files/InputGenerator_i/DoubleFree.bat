
@echo off


cls
@echo This is Double Free detection > DoubleFree.txt
set /a i=1
set /a j=0
set  c=a
set t=0
set /a avg =0

:while
if %j% lss 121 (
  

  pin.exe -t DoubleFree.dll -- TestCheckers.exe %c%
  
 
 set /p texte=< DoubleFree.csv
 
 if %i% gtr  1 (
  @echo %texte% :Input %j%  >> DoubleFree.txt

)
   


 
  set /a i+=1
  set /a j+=1
  set c=%c%a
  goto :while
  )
  
  
 sort DoubleFree.txt /O DoubleFreeSorted.txt




 



