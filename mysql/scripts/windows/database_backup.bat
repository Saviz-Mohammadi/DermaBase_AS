@echo off

REM (Script must be executed in administrative mode)

REM (MySQL bin directory):
set "MYSQL_BIN_DIR=C:\Program Files\MySQL\MySQL Server 8.0\bin"
cd /d "%MYSQL_BIN_DIR%"

REM (Base folder where backups will be stored):
set BACKUP_PATH=C:\Backups

REM (Database credentials):
set "USERNAME=UFO_Dermatologist"
set "PASSWORD=1345750"
set "DATABASE=ufo_dermatologist"

REM (Create backup folder with numeric suffix):
set "FOLDER_NAME=%DATABASE%"
set "COUNTER=0"
set "BACKUP_DIR=%BACKUP_PATH%\%FOLDER_NAME%"

:CHECK_FOLDER
if exist "%BACKUP_DIR%" (
    set /a COUNTER+=1
    set "BACKUP_DIR=%BACKUP_PATH%\%FOLDER_NAME%_%COUNTER%"
    goto CHECK_FOLDER
)
mkdir "%BACKUP_DIR%"


REM (Initialize log file):
set "LOGFILE=%BACKUP_DIR%\log.txt"
echo Backup started at %DATE% %TIME% > "%LOGFILE%"

REM (Get the list of tables from the target database. The "skip=1" option avoids the header row in the output):
for /f "skip=1 delims=" %%i in ('mysql -u %USERNAME% -p%PASSWORD% -e "SHOW TABLES FROM %DATABASE%;"') do (
    if not "%%i"=="" (
        echo Backing up table: %%i
        echo Backing up table: %%i >> "%LOGFILE%"
        mysqldump -u %USERNAME% -p%PASSWORD% %DATABASE% %%i > "%BACKUP_DIR%\%%i.sql" 2>> "%LOGFILE%"
        if errorlevel 1 (
            echo Error backing up table %%i >> "%LOGFILE%"
        ) else (
            echo Successfully backed up table %%i >> "%LOGFILE%"
        )
    )
)

echo Backup completed at %DATE% %TIME% >> "%LOGFILE%"
