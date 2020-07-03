EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Module:Arduino_UNO_R3 A?
U 1 1 5EFF97DB
P 3100 4000
F 0 "A?" H 3100 5181 50  0000 C CNN
F 1 "Arduino_UNO_R3" H 2550 5100 50  0000 C CNN
F 2 "Module:Arduino_UNO_R3" H 3250 2950 50  0001 L CNN
F 3 "https://www.arduino.cc/en/Main/arduinoBoardUno" H 2900 5050 50  0001 C CNN
	1    3100 4000
	1    0    0    -1  
$EndComp
$Comp
L ECE:LTC-4727JR U?
U 1 1 5EFFC02F
P 6450 3950
F 0 "U?" H 6450 4587 60  0000 C CNN
F 1 "LTC-4727JR" H 6450 4481 60  0000 C CNN
F 2 "" H 5750 4350 60  0000 C CNN
F 3 "" H 5750 4350 60  0000 C CNN
	1    6450 3950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5EFFE387
P 3100 5250
F 0 "#PWR?" H 3100 5000 50  0001 C CNN
F 1 "GND" H 3105 5077 50  0000 C CNN
F 2 "" H 3100 5250 50  0001 C CNN
F 3 "" H 3100 5250 50  0001 C CNN
	1    3100 5250
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5EFFECEC
P 3300 2750
F 0 "#PWR?" H 3300 2600 50  0001 C CNN
F 1 "+5V" H 3315 2923 50  0000 C CNN
F 2 "" H 3300 2750 50  0001 C CNN
F 3 "" H 3300 2750 50  0001 C CNN
	1    3300 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 2750 3300 3000
Wire Wire Line
	3000 5100 3100 5100
Connection ~ 3100 5100
Wire Wire Line
	3100 5100 3200 5100
Wire Wire Line
	3100 5100 3100 5250
Wire Wire Line
	2600 3700 2100 3700
Wire Wire Line
	2600 3900 2100 3900
Wire Wire Line
	2600 4000 2100 4000
Wire Wire Line
	2600 4300 2100 4300
Wire Wire Line
	5950 3600 5600 3600
Wire Wire Line
	5950 3700 5600 3700
Wire Wire Line
	5950 4100 5600 4100
Wire Wire Line
	5950 4300 5600 4300
Text Label 2100 3700 0    50   ~ 0
Digit1
Text Label 2100 3900 0    50   ~ 0
Digit2
Text Label 2100 4000 0    50   ~ 0
Digit3
Text Label 2100 4300 0    50   ~ 0
Digit4
Text Label 5600 3600 0    50   ~ 0
Digit1
Text Label 5600 3700 0    50   ~ 0
Digit2
Text Label 5600 4100 0    50   ~ 0
Digit3
Text Label 5600 4300 0    50   ~ 0
Digit4
$EndSCHEMATC
