@echo off

IF exist "P:\Namalsk_Weapon\" (
	echo Removing existing link P:\Namalsk_Weapon
	rmdir "P:\Namalsk_Weapon\"
)

echo Creating link P:\Namalsk_Weapon
mklink /J "P:\Namalsk_Weapon\" "%cd%\Namalsk_Weapon\"

echo Done