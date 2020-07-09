EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "ECE299 Alarm Clock Project"
Date "2020-07-08"
Rev "1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L AlarmPCB-rescue:Arduino_UNO_R3-MCU_Module A1
U 1 1 5EFF97DB
P 2150 2650
F 0 "A1" H 2150 3831 50  0000 C CNN
F 1 "Arduino_UNO_R3" H 1600 3750 50  0000 C CNN
F 2 "Module:Arduino_UNO_R3" H 2300 1600 50  0001 L CNN
F 3 "https://www.arduino.cc/en/Main/arduinoBoardUno" H 1950 3700 50  0001 C CNN
	1    2150 2650
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 5EFFE387
P 2150 3900
F 0 "#PWR03" H 2150 3650 50  0001 C CNN
F 1 "GND" H 2155 3727 50  0000 C CNN
F 2 "" H 2150 3900 50  0001 C CNN
F 3 "" H 2150 3900 50  0001 C CNN
	1    2150 3900
	-1   0    0    -1  
$EndComp
$Comp
L power:+5V #PWR04
U 1 1 5EFFECEC
P 1950 1400
F 0 "#PWR04" H 1950 1250 50  0001 C CNN
F 1 "+5V" H 1965 1573 50  0000 C CNN
F 2 "" H 1950 1400 50  0001 C CNN
F 3 "" H 1950 1400 50  0001 C CNN
	1    1950 1400
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1950 1400 1950 1650
Wire Wire Line
	2250 3750 2150 3750
Connection ~ 2150 3750
Wire Wire Line
	2150 3750 2050 3750
Wire Wire Line
	2150 3750 2150 3900
$Comp
L Display_Character:WC1602A DS1
U 1 1 5F063F5F
P 1800 6050
F 0 "DS1" H 2100 7050 50  0000 C CNN
F 1 "WC1602A" H 2200 6900 50  0000 C CNN
F 2 "Display:WC1602A" H 1800 5150 50  0001 C CIN
F 3 "http://www.wincomlcd.com/pdf/WC1602A-SFYLYHTC06.pdf" H 2500 6050 50  0001 C CNN
	1    1800 6050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 5F06DAC4
P 1800 6850
F 0 "#PWR02" H 1800 6600 50  0001 C CNN
F 1 "GND" H 1805 6677 50  0000 C CNN
F 2 "" H 1800 6850 50  0001 C CNN
F 3 "" H 1800 6850 50  0001 C CNN
	1    1800 6850
	-1   0    0    -1  
$EndComp
$Comp
L power:+5V #PWR01
U 1 1 5F06E403
P 1800 5100
F 0 "#PWR01" H 1800 4950 50  0001 C CNN
F 1 "+5V" H 1815 5273 50  0000 C CNN
F 2 "" H 1800 5100 50  0001 C CNN
F 3 "" H 1800 5100 50  0001 C CNN
	1    1800 5100
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1800 5100 1800 5250
Wire Wire Line
	1400 5450 1050 5450
Wire Wire Line
	1400 5650 1050 5650
Wire Wire Line
	1400 5550 1250 5550
Wire Wire Line
	1250 5550 1250 5800
$Comp
L power:GND #PWR05
U 1 1 5F070A81
P 1250 5800
F 0 "#PWR05" H 1250 5550 50  0001 C CNN
F 1 "GND" H 1150 5800 50  0000 C CNN
F 2 "" H 1250 5800 50  0001 C CNN
F 3 "" H 1250 5800 50  0001 C CNN
	1    1250 5800
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1400 6650 1050 6650
Wire Wire Line
	1400 6550 1050 6550
Wire Wire Line
	1400 6450 1050 6450
Wire Wire Line
	1400 6350 1050 6350
Wire Wire Line
	2200 5850 2300 5850
Wire Wire Line
	2300 5850 2300 6100
$Comp
L Device:R_Small_US R1
U 1 1 5F073E17
P 2300 6200
F 0 "R1" H 2368 6246 50  0000 L CNN
F 1 "R_Small_US" H 1800 6200 50  0000 L CNN
F 2 "" H 2300 6200 50  0001 C CNN
F 3 "~" H 2300 6200 50  0001 C CNN
	1    2300 6200
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR07
U 1 1 5F075220
P 2300 6400
F 0 "#PWR07" H 2300 6150 50  0001 C CNN
F 1 "GND" H 2305 6227 50  0000 C CNN
F 2 "" H 2300 6400 50  0001 C CNN
F 3 "" H 2300 6400 50  0001 C CNN
	1    2300 6400
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2300 6400 2300 6300
Text Label 1050 5450 0    50   ~ 0
E
Text Label 1050 5650 0    50   ~ 0
RS
Text Label 1050 6650 0    50   ~ 0
117
Text Label 1050 6550 0    50   ~ 0
118
Text Label 1050 6450 0    50   ~ 0
119
Text Label 1050 6350 0    50   ~ 0
120
Wire Wire Line
	2200 5750 2650 5750
Wire Wire Line
	2650 3250 3000 3250
Wire Wire Line
	2650 3150 3000 3150
Wire Wire Line
	2650 3050 3000 3050
Wire Wire Line
	2650 2550 3000 2550
Wire Wire Line
	2650 2450 3000 2450
Wire Wire Line
	2650 2350 3000 2350
Wire Wire Line
	2650 2250 3000 2250
Text Label 3000 3250 2    50   ~ 0
RS
Text Label 3000 3050 2    50   ~ 0
125
Text Label 3000 3150 2    50   ~ 0
E
Text Label 3000 2550 2    50   ~ 0
120
Text Label 3000 2450 2    50   ~ 0
119
Text Label 3000 2350 2    50   ~ 0
118
Text Label 3000 2250 2    50   ~ 0
117
$Comp
L Switch:SW_Push PB1
U 1 1 5F088DBE
P 5650 1500
F 0 "PB1" H 5650 1650 50  0000 C CNN
F 1 "TimeUp" H 6100 1500 50  0000 C CNN
F 2 "" H 5650 1700 50  0001 C CNN
F 3 "~" H 5650 1700 50  0001 C CNN
	1    5650 1500
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push PB2
U 1 1 5F08BB18
P 5650 1800
F 0 "PB2" H 5650 1950 50  0000 C CNN
F 1 "TimeDown" H 6150 1800 50  0000 C CNN
F 2 "" H 5650 2000 50  0001 C CNN
F 3 "~" H 5650 2000 50  0001 C CNN
	1    5650 1800
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push PB4
U 1 1 5F08C341
P 5650 2100
F 0 "PB4" H 5650 2250 50  0000 C CNN
F 1 "AlarmSet" H 6150 2100 50  0000 C CNN
F 2 "" H 5650 2300 50  0001 C CNN
F 3 "~" H 5650 2300 50  0001 C CNN
	1    5650 2100
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push PB5
U 1 1 5F08C740
P 5650 2400
F 0 "PB5" H 5650 2550 50  0000 C CNN
F 1 "CancelAlarm" H 6200 2400 50  0000 C CNN
F 2 "" H 5650 2600 50  0001 C CNN
F 3 "~" H 5650 2600 50  0001 C CNN
	1    5650 2400
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push PB6
U 1 1 5F08C9FC
P 5650 2700
F 0 "PB6" H 5650 2850 50  0000 C CNN
F 1 "Snooze" H 6100 2700 50  0000 C CNN
F 2 "" H 5650 2900 50  0001 C CNN
F 3 "~" H 5650 2900 50  0001 C CNN
	1    5650 2700
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push PB7
U 1 1 5F08CE62
P 5650 3000
F 0 "PB7" H 5650 3150 50  0000 C CNN
F 1 "Backlight" H 6150 3000 50  0000 C CNN
F 2 "" H 5650 3200 50  0001 C CNN
F 3 "~" H 5650 3200 50  0001 C CNN
	1    5650 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 1500 5900 1500
Wire Wire Line
	5850 1800 5900 1800
Wire Wire Line
	5850 2100 5900 2100
Wire Wire Line
	5850 2400 5900 2400
Wire Wire Line
	5850 2700 5900 2700
Wire Wire Line
	5850 3000 5900 3000
$Comp
L power:GND #PWR06
U 1 1 5F092395
P 5900 4500
F 0 "#PWR06" H 5900 4250 50  0001 C CNN
F 1 "GND" H 5905 4327 50  0000 C CNN
F 2 "" H 5900 4500 50  0001 C CNN
F 3 "" H 5900 4500 50  0001 C CNN
	1    5900 4500
	1    0    0    -1  
$EndComp
Text Label 4500 1500 0    50   ~ 0
121
Text Label 4500 1800 0    50   ~ 0
122
Text Label 4500 2100 0    50   ~ 0
113
Text Label 4500 2400 0    50   ~ 0
110
Text Label 4500 2700 0    50   ~ 0
111
Text Label 4500 3000 0    50   ~ 0
112
Wire Wire Line
	1650 2650 1250 2650
Text Label 1250 2650 0    50   ~ 0
109
Wire Wire Line
	2650 2650 3000 2650
Wire Wire Line
	2650 2750 3000 2750
Wire Wire Line
	2650 2950 3000 2950
Wire Wire Line
	1650 2750 1250 2750
Wire Wire Line
	1650 2850 1250 2850
Wire Wire Line
	1650 2950 1250 2950
Text Label 3000 2650 2    50   ~ 0
121
Text Label 3000 2750 2    50   ~ 0
122
Text Label 1250 2750 0    50   ~ 0
110
Text Label 1250 2850 0    50   ~ 0
111
Text Label 1250 2950 0    50   ~ 0
112
Wire Wire Line
	1650 3050 1250 3050
Text Label 1250 3050 0    50   ~ 0
113
Text Label 3000 2950 2    50   ~ 0
124
$Comp
L power:+5V #PWR011
U 1 1 5F0FF000
P 4600 3250
F 0 "#PWR011" H 4600 3100 50  0001 C CNN
F 1 "+5V" V 4700 3300 50  0000 C CNN
F 2 "" H 4600 3250 50  0001 C CNN
F 3 "" H 4600 3250 50  0001 C CNN
	1    4600 3250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5350 3250 5350 3500
$Comp
L Device:R_PHOTO R3
U 1 1 5F0F643D
P 5650 3250
F 0 "R3" V 5750 3200 50  0000 L CNN
F 1 "Photoresistor" V 5650 2400 50  0000 L CNN
F 2 "" V 5700 3000 50  0001 L CNN
F 3 "~" H 5650 3200 50  0001 C CNN
	1    5650 3250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5350 3250 5500 3250
Wire Wire Line
	5800 3250 5900 3250
$Comp
L Device:R_Small_US R2
U 1 1 5F0F87BD
P 4850 3250
F 0 "R2" V 4750 3200 50  0000 L CNN
F 1 "R_Small_US" V 4950 3050 50  0000 L CNN
F 2 "" H 4850 3250 50  0001 C CNN
F 3 "~" H 4850 3250 50  0001 C CNN
	1    4850 3250
	0    -1   1    0   
$EndComp
Wire Wire Line
	4750 3250 4600 3250
Wire Notes Line style solid
	3350 4250 3350 1100
Wire Notes Line style solid
	3350 1100 1000 1100
Wire Notes Line style solid
	1000 1100 1000 4250
Text Notes 1000 1050 0    50   ~ 10
Arduino
Wire Notes Line style solid
	1000 4250 3350 4250
Wire Notes Line style solid
	1000 7200 3400 7200
Wire Notes Line style solid
	1000 7200 1000 4800
Wire Notes Line style solid
	1000 4800 3400 4800
Wire Notes Line style solid
	3400 4800 3400 7200
Text Notes 1000 4800 0    50   ~ 10
LCD Display
Wire Wire Line
	4500 1500 5450 1500
Wire Wire Line
	4500 1800 5450 1800
Wire Wire Line
	4500 2100 5450 2100
Wire Wire Line
	4500 2400 5450 2400
Wire Wire Line
	4500 2700 5450 2700
Wire Wire Line
	4500 3000 5450 3000
Wire Wire Line
	5900 1500 5900 1800
Wire Wire Line
	5900 1800 5900 2100
Connection ~ 5900 1800
Wire Wire Line
	5900 2100 5900 2400
Connection ~ 5900 2100
Wire Wire Line
	5900 2400 5900 2700
Connection ~ 5900 2400
Wire Wire Line
	5900 2700 5900 3000
Connection ~ 5900 2700
Wire Wire Line
	5900 3000 5900 3250
Connection ~ 5900 3000
Wire Wire Line
	5350 3500 4500 3500
Wire Wire Line
	4950 3250 5350 3250
Connection ~ 5350 3250
Text Label 4500 3500 0    50   ~ 0
109
Wire Wire Line
	5900 3250 5900 3850
Connection ~ 5900 3250
$Comp
L Device:Buzzer BZ1
U 1 1 5F0DAE2B
P 5650 3750
F 0 "BZ1" V 5800 3800 50  0000 R CNN
F 1 "Buzzer" V 5550 3400 50  0000 R CNN
F 2 "" V 5625 3850 50  0001 C CNN
F 3 "~" V 5625 3850 50  0001 C CNN
	1    5650 3750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5550 3850 4500 3850
Wire Wire Line
	5750 3850 5900 3850
Connection ~ 5900 3850
Wire Wire Line
	5900 3850 5900 4100
Text Label 4500 3850 0    50   ~ 0
124
$Comp
L Device:R_POT RV1
U 1 1 5F0E8897
P 5650 4100
F 0 "RV1" V 5550 4150 50  0000 R CNN
F 1 "Contrast" V 5650 3750 50  0000 R CNN
F 2 "" H 5650 4100 50  0001 C CNN
F 3 "~" H 5650 4100 50  0001 C CNN
	1    5650 4100
	0    -1   1    0   
$EndComp
Wire Wire Line
	5800 4100 5900 4100
Connection ~ 5900 4100
Wire Wire Line
	5900 4100 5900 4500
$Comp
L power:+5V #PWR?
U 1 1 5F0F17D9
P 4600 4100
F 0 "#PWR?" H 4600 3950 50  0001 C CNN
F 1 "+5V" V 4700 4150 50  0000 C CNN
F 2 "" H 4600 4100 50  0001 C CNN
F 3 "" H 4600 4100 50  0001 C CNN
	1    4600 4100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5500 4100 4600 4100
Wire Wire Line
	5650 4250 5650 4300
Wire Wire Line
	5650 4300 4500 4300
Text Label 4500 4300 0    50   ~ 0
215
Wire Wire Line
	2200 5450 2650 5450
Text Label 2650 5750 2    50   ~ 0
125
Text Label 2650 5450 0    50   ~ 0
215
$EndSCHEMATC
