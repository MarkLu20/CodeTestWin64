TITLE CO UnrealPak Extract Tool
@ECHO OFF
 SET Unreal_PATH=G:\MatrixUnrealEngine4.18.3\Engine\Binaries\Win64\UnrealPak.exe
 SET KeyFile_PATH=H:\CodeTestForWindows\Doc\KeyFileBig.txt
 SET P_Value=12664b1
 SET Q_Value=1272d7b
 ECHO ---------------------------------------
 ECHO UnrealPak GenerateKey
 ECHO ---------------------------------------
 
 REM choice /C YNC /M "Verify PQ Primes(Y/N)? Verify May Take a While . C Quit"
 REM if errorlevel 3 goto Quit
 REM if errorlevel 2 goto NoVerifyPrimes
 REM if errorlevel 1 
 goto VerifyPrimes
 
 
 :VerifyPrimes
 CALL %Unreal_PATH% GenerateKeys=%KeyFile_PATH% P=%P_Value% Q=%Q_Value%
 
 :NoVerifyPrimes
CALL %Unreal_PATH% GenerateKeys=%KeyFile_PATH% P=%P_Value% Q=%Q_Value% -NoVerifyPrimes

:Quit

 ECHO ---------------------------------------
 ECHO UnrealPak GenerateKey Done
 ECHO ---------------------------------------
 
 PAUSE