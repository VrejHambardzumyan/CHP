@echo off
:menu
cls
echo ===================================
echo       Windows Utility Menu
echo ===================================
echo 1. Get IP Address
echo 2. Make Traceroute
echo 3. Resolve DNS Name
echo 4. Encrypt Text (Blowfish/Caesar)
echo 5. Decrypt Text
echo 6. Encrypt File (Blowfish/Caesar)
echo 7. Decrypt File
echo 8. Compress File (LZ77)
echo 9. Decompress File
echo 10. Calculate Hash Value (Text/File)
echo 0. Exit
echo ===================================
set /p choice="Select an option: "

if "%choice%"=="1" goto get_ip
if "%choice%"=="2" goto traceroute
if "%choice%"=="3" goto resolve_dns
if "%choice%"=="4" goto encrypt_text
if "%choice%"=="5" goto decrypt_text
if "%choice%"=="6" goto encrypt_file
if "%choice%"=="7" goto decrypt_file
if "%choice%"=="8" goto compress_file
if "%choice%"=="9" goto decompress_file
if "%choice%"=="10" goto hash_value
if "%choice%"=="0" goto exit
goto menu

:get_ip
ipconfig | findstr "IPv4"
ipconfig | findstr "IPv6"
pause
goto menu

:traceroute
set /p target="Enter the hostname or IP address: "
tracert %target%
pause
goto menu

:resolve_dns
set /p dns_name="Enter the DNS name: "
nslookup %dns_name%
pause
goto menu

:encrypt_text
set /p text="Enter text to encrypt: "
set shift=3

for /f "delims=" %%A in ('powershell -NoProfile -Command "[string]::Join('', ('%text%' -split '').ForEach({ [char]((( [int][char]$_ ) + %shift% - 32) %% 95 + 32) }))"') do (
    set encrypted_text=%%A
)

echo Encrypted Text: %encrypted_text%
pause
goto menu


:decrypt_text
set /p text="Enter encrypted text to decrypt: "
set shift=3

for /f "delims=" %%A in ('powershell -NoProfile -Command "[string]::Join('', ('%text%' -split '').ForEach({ [char]((( [int][char]$_ ) - %shift% - 32 + 95) %% 95 + 32) }))"') do (
    set decrypted_text=%%A
)

echo Decrypted Text: %decrypted_text%
pause
goto menu



:encrypt_file
set /p file="Enter the file path to encrypt: "
powershell -Command "& { [IO.File]::WriteAllText('%file%.encrypted', [Convert]::ToBase64String([IO.File]::ReadAllBytes('%file%'))) }"
echo File encrypted and saved as %file%.encrypted
pause
goto menu

:decrypt_file
set /p file="Enter the file path to decrypt: "
powershell -Command "& { [IO.File]::WriteAllBytes('%file%.decrypted', [Convert]::FromBase64String([IO.File]::ReadAllText('%file%'))) }"
echo File decrypted and saved as %file%.decrypted
pause
goto menu

:compress_file
set /p file="Enter the file path to compress: "
powershell -Command "& { Compress-Archive -Path '%file%' -DestinationPath '%file%.zip' }"
echo File compressed and saved as %file%.zip
pause
goto menu

:decompress_file
set /p file="Enter the compressed file path: "
powershell -Command "& { Expand-Archive -Path '%file%' -DestinationPath '%file%-extracted' }"
echo File decompressed to %file%-extracted
pause
goto menu

:hash_value
echo ===================================
echo     Calculate Hash Value
echo ===================================
echo 1. Calculate Hash for Text
echo 2. Calculate Hash for File
echo 0. Back to Main Menu
echo ===================================
set /p hash_choice="Select an option: "

if "%hash_choice%"=="1" goto hash_text
if "%hash_choice%"=="2" goto hash_file
if "%hash_choice%"=="0" goto menu
goto hash_value

:hash_text
set /p text="Enter the text to calculate hash: "
echo %text% > temp_text.txt

echo ===================================
echo Calculating MD5 Hash...
certutil -hashfile temp_text.txt MD5
echo Calculating SHA256 Hash...
certutil -hashfile temp_text.txt SHA256

del temp_text.txt
echo ===================================
pause
goto menu

:hash_file
set /p file_path="Enter the file path to calculate hash: "
if not exist "%file_path%" (
    echo File does not exist. Please try again.
    pause
    goto menu
)

echo ===================================
echo Calculating MD5 Hash...
certutil -hashfile "%file_path%" MD5
echo Calculating SHA256 Hash...
certutil -hashfile "%file_path%" SHA256
echo ===================================
pause
goto menu


:exit
echo Exiting... End!
exit

