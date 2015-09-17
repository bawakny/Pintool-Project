
@echo off
cls
@echo This is Memory Tracer > memoryTrace.txt
set /a i=1
set /a j=0
set  c=a


:while
if %j% lss 121 (
  

  pin.exe -t MemoryTrace.dll -- TestCheckers.exe %c%
 

 set /p texte=< MemTrace.csv
 
 if %i% gtr  1 (
  @echo %texte% :Input %j%  >> memoryTrace.txt 
   )

  set /a i+=1
    set /a j+=1
  set c=%c%a
  goto :while
 )
 
sort MemoryTrace.txt /O MemoryTraceSorted.txt

 



