EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 1 1
Title "ECE299 Alarm Clock Project"
Date "2020-07-08"
Rev "1"
Comp "Ben Kellman and Adam Carloni"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L AlarmPCB-rescue:Arduino_UNO_R3-MCU_Module A1
U 1 1 5EFF97DB
P 5250 3850
F 0 "A1" H 5250 5031 50  0000 C CNN
F 1 "Arduino_UNO_R3" H 4700 4950 50  0000 C CNN
F 2 "Module:Arduino_UNO_R3" H 5400 2800 50  0001 L CNN
F 3 "https://www.arduino.cc/en/Main/arduinoBoardUno" H 5050 4900 50  0001 C CNN
	1    5250 3850
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR05
U 1 1 5EFFE387
P 5250 5100
F 0 "#PWR05" H 5250 4850 50  0001 C CNN
F 1 "GND" H 5255 4927 50  0000 C CNN
F 2 "" H 5250 5100 50  0001 C CNN
F 3 "" H 5250 5100 50  0001 C CNN
	1    5250 5100
	-1   0    0    -1  
$EndComp
$Comp
L power:+5V #PWR04
U 1 1 5EFFECEC
P 5050 2600
F 0 "#PWR04" H 5050 2450 50  0001 C CNN
F 1 "+5V" H 5065 2773 50  0000 C CNN
F 2 "" H 5050 2600 50  0001 C CNN
F 3 "" H 5050 2600 50  0001 C CNN
	1    5050 2600
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5050 2600 5050 2850
Wire Wire Line
	5350 4950 5250 4950
Connection ~ 5250 4950
Wire Wire Line
	5250 4950 5150 4950
Wire Wire Line
	5250 4950 5250 5100
$Comp
L Display_Character:WC1602A DS1
U 1 1 5F063F5F
P 8400 4000
F 0 "DS1" H 8700 5000 50  0000 C CNN
F 1 "WC1602A" H 8800 4850 50  0000 C CNN
F 2 "Display:WC1602A" H 8400 3100 50  0001 C CIN
F 3 "http://www.wincomlcd.com/pdf/WC1602A-SFYLYHTC06.pdf" H 9100 4000 50  0001 C CNN
	1    8400 4000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 5F06DAC4
P 8400 4800
F 0 "#PWR09" H 8400 4550 50  0001 C CNN
F 1 "GND" H 8405 4627 50  0000 C CNN
F 2 "" H 8400 4800 50  0001 C CNN
F 3 "" H 8400 4800 50  0001 C CNN
	1    8400 4800
	-1   0    0    -1  
$EndComp
$Comp
L power:+5V #PWR08
U 1 1 5F06E403
P 8400 3050
F 0 "#PWR08" H 8400 2900 50  0001 C CNN
F 1 "+5V" H 8415 3223 50  0000 C CNN
F 2 "" H 8400 3050 50  0001 C CNN
F 3 "" H 8400 3050 50  0001 C CNN
	1    8400 3050
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8400 3050 8400 3200
Wire Wire Line
	8000 3400 7650 3400
Wire Wire Line
	8000 3600 7650 3600
Wire Wire Line
	8000 3500 7850 3500
Wire Wire Line
	7850 3500 7850 3750
$Comp
L power:GND #PWR07
U 1 1 5F070A81
P 7850 3750
F 0 "#PWR07" H 7850 3500 50  0001 C CNN
F 1 "GND" H 7750 3750 50  0000 C CNN
F 2 "" H 7850 3750 50  0001 C CNN
F 3 "" H 7850 3750 50  0001 C CNN
	1    7850 3750
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8000 4600 7650 4600
Wire Wire Line
	8000 4500 7650 4500
Wire Wire Line
	8000 4400 7650 4400
Wire Wire Line
	8000 4300 7650 4300
Wire Wire Line
	8800 3800 8900 3800
Wire Wire Line
	8900 3800 8900 4050
$Comp
L Device:R_Small_US R3
U 1 1 5F073E17
P 8900 4150
F 0 "R3" H 8968 4196 50  0000 L CNN
F 1 "220R" H 8600 4150 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" H 8900 4150 50  0001 C CNN
F 3 "~" H 8900 4150 50  0001 C CNN
	1    8900 4150
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5F075220
P 8900 4350
F 0 "#PWR010" H 8900 4100 50  0001 C CNN
F 1 "GND" H 8905 4177 50  0000 C CNN
F 2 "" H 8900 4350 50  0001 C CNN
F 3 "" H 8900 4350 50  0001 C CNN
	1    8900 4350
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8900 4350 8900 4250
Text Label 7650 3400 0    50   ~ 0
D11
Text Label 7650 3600 0    50   ~ 0
D12
Text Label 7650 4600 0    50   ~ 0
D2
Text Label 7650 4500 0    50   ~ 0
D3
Text Label 7650 4400 0    50   ~ 0
D4
Text Label 7650 4300 0    50   ~ 0
D5
Wire Wire Line
	5750 4450 6100 4450
Wire Wire Line
	5750 4350 6100 4350
Wire Wire Line
	5750 4250 6100 4250
Wire Wire Line
	5750 3750 6100 3750
Wire Wire Line
	5750 3650 6100 3650
Wire Wire Line
	5750 3550 6100 3550
Wire Wire Line
	5750 3450 6100 3450
Text Label 6100 4450 2    50   ~ 0
D12
Text Label 6100 4250 2    50   ~ 0
D10
Text Label 6100 4350 2    50   ~ 0
D11
Text Label 6100 3750 2    50   ~ 0
D5
Text Label 6100 3650 2    50   ~ 0
D4
Text Label 6100 3550 2    50   ~ 0
D3
Text Label 6100 3450 2    50   ~ 0
D2
$Comp
L Switch:SW_Push PB6
U 1 1 5F088DBE
P 2950 3750
F 0 "PB6" V 3100 3900 50  0000 C CNN
F 1 "Time+" H 2800 3850 50  0000 C CNN
F 2 "Button_Switch_THT:SW_TH_Tactile_Omron_B3F-10xx" H 2950 3950 50  0001 C CNN
F 3 "~" H 2950 3950 50  0001 C CNN
	1    2950 3750
	0    -1   1    0   
$EndComp
$Comp
L Switch:SW_Push PB5
U 1 1 5F08BB18
P 2550 3750
F 0 "PB5" V 2700 3900 50  0000 C CNN
F 1 "Time-" H 2400 3850 50  0000 C CNN
F 2 "Button_Switch_THT:SW_TH_Tactile_Omron_B3F-10xx" H 2550 3950 50  0001 C CNN
F 3 "~" H 2550 3950 50  0001 C CNN
	1    2550 3750
	0    -1   1    0   
$EndComp
$Comp
L Switch:SW_Push PB3
U 1 1 5F08C740
P 1750 3750
F 0 "PB3" V 1900 3900 50  0000 C CNN
F 1 "CancelAlarm" H 1500 3850 50  0000 C CNN
F 2 "Button_Switch_THT:SW_TH_Tactile_Omron_B3F-10xx" H 1750 3950 50  0001 C CNN
F 3 "~" H 1750 3950 50  0001 C CNN
	1    1750 3750
	0    -1   1    0   
$EndComp
$Comp
L Switch:SW_Push PB2
U 1 1 5F08C9FC
P 1350 3750
F 0 "PB2" V 1500 3850 50  0000 C CNN
F 1 "Snooze" H 1200 3850 50  0000 C CNN
F 2 "Button_Switch_THT:SW_TH_Tactile_Omron_B3F-10xx" H 1350 3950 50  0001 C CNN
F 3 "~" H 1350 3950 50  0001 C CNN
	1    1350 3750
	0    -1   1    0   
$EndComp
$Comp
L Switch:SW_Push PB1
U 1 1 5F08CE62
P 1000 3750
F 0 "PB1" V 1150 3850 50  0000 C CNN
F 1 "Backlight" H 800 3850 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH-12mm_Wuerth-430476085716" H 1000 3950 50  0001 C CNN
F 3 "~" H 1000 3950 50  0001 C CNN
	1    1000 3750
	0    -1   1    0   
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5F092395
P 6650 4500
F 0 "#PWR06" H 6650 4250 50  0001 C CNN
F 1 "GND" H 6655 4327 50  0000 C CNN
F 2 "" H 6650 4500 50  0001 C CNN
F 3 "" H 6650 4500 50  0001 C CNN
	1    6650 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 3850 6100 3850
Wire Wire Line
	5750 3950 6100 3950
Text Label 6100 3850 2    50   ~ 0
D6
Text Label 6100 3950 2    50   ~ 0
D7
Wire Notes Line style solid
	7600 5150 10000 5150
Wire Notes Line style solid
	7600 5150 7600 2750
Wire Notes Line style solid
	7600 2750 10000 2750
Wire Notes Line style solid
	10000 2750 10000 5150
Text Notes 7600 2750 0    50   ~ 10
LCD Display
$Comp
L Device:Buzzer BZ1
U 1 1 5F0DAE2B
P 6850 4250
F 0 "BZ1" V 7000 4300 50  0000 R CNN
F 1 "Buzzer" H 6950 4500 50  0000 R CNN
F 2 "Buzzer_Beeper:Buzzer_D14mm_H7mm_P10mm" V 6825 4350 50  0001 C CNN
F 3 "~" V 6825 4350 50  0001 C CNN
	1    6850 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT RV1
U 1 1 5F0E8897
P 9400 3400
F 0 "RV1" V 9300 3450 50  0000 R CNN
F 1 "Contrast" H 9350 3550 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_ACP_CA6-H2,5_Horizontal" H 9400 3400 50  0001 C CNN
F 3 "~" H 9400 3400 50  0001 C CNN
	1    9400 3400
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8800 3400 9250 3400
Text Label 9000 3700 2    50   ~ 0
D10
Text Label 1200 3450 2    50   ~ 0
A3
Text Label 1550 3450 2    50   ~ 0
A2
Text Label 1950 3450 2    50   ~ 0
A1
Text Label 2350 3450 2    50   ~ 0
A4
Text Label 2750 3450 2    50   ~ 0
D7
Wire Wire Line
	9000 3700 8800 3700
$Comp
L power:GND #PWR012
U 1 1 5F0AF103
P 9400 3700
F 0 "#PWR012" H 9400 3450 50  0001 C CNN
F 1 "GND" H 9405 3527 50  0000 C CNN
F 2 "" H 9400 3700 50  0001 C CNN
F 3 "" H 9400 3700 50  0001 C CNN
	1    9400 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 3700 9400 3550
$Comp
L power:+5V #PWR011
U 1 1 5F0B0F52
P 9400 3100
F 0 "#PWR011" H 9400 2950 50  0001 C CNN
F 1 "+5V" H 9415 3273 50  0000 C CNN
F 2 "" H 9400 3100 50  0001 C CNN
F 3 "" H 9400 3100 50  0001 C CNN
	1    9400 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 3100 9400 3250
$Comp
L Device:R_Small_US R2
U 1 1 5F0F87BD
P 4050 3450
F 0 "R2" V 3950 3400 50  0000 L CNN
F 1 "1K9" H 4150 3450 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" H 4050 3450 50  0001 C CNN
F 3 "~" H 4050 3450 50  0001 C CNN
	1    4050 3450
	1    0    0    1   
$EndComp
Wire Wire Line
	4050 3550 4050 3650
$Comp
L Device:R_PHOTO R1
U 1 1 5F0F643D
P 4050 3000
F 0 "R1" V 4150 2950 50  0000 L CNN
F 1 "PhotoResistor" V 4250 2800 50  0000 L CNN
F 2 "OptoDevice:R_LDR_4.9x4.2mm_P2.54mm_Vertical" V 4100 2750 50  0001 L CNN
F 3 "~" H 4050 2950 50  0001 C CNN
	1    4050 3000
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR02
U 1 1 5F0FF000
P 4050 2700
F 0 "#PWR02" H 4050 2550 50  0001 C CNN
F 1 "+5V" V 4150 2750 50  0000 C CNN
F 2 "" H 4050 2700 50  0001 C CNN
F 3 "" H 4050 2700 50  0001 C CNN
	1    4050 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 2700 4050 2850
$Comp
L power:GND #PWR03
U 1 1 5F0D1E03
P 4050 3650
F 0 "#PWR03" H 4050 3400 50  0001 C CNN
F 1 "GND" H 4055 3477 50  0000 C CNN
F 2 "" H 4050 3650 50  0001 C CNN
F 3 "" H 4050 3650 50  0001 C CNN
	1    4050 3650
	1    0    0    -1  
$EndComp
Text Label 4500 4250 0    50   ~ 0
A4
Text Label 4500 4150 0    50   ~ 0
A3
Text Label 4500 4050 0    50   ~ 0
A2
Text Label 4500 3950 0    50   ~ 0
A1
Wire Wire Line
	4500 3950 4750 3950
Wire Wire Line
	4750 4050 4500 4050
Wire Wire Line
	4500 4150 4750 4150
Wire Wire Line
	4750 4250 4500 4250
Wire Wire Line
	4500 3850 4750 3850
$Comp
L Switch:SW_Push PB4
U 1 1 5F08C341
P 2150 3750
F 0 "PB4" V 2300 3900 50  0000 C CNN
F 1 "AlarmSet" H 1900 3850 50  0000 C CNN
F 2 "Button_Switch_THT:SW_TH_Tactile_Omron_B3F-10xx" H 2150 3950 50  0001 C CNN
F 3 "~" H 2150 3950 50  0001 C CNN
	1    2150 3750
	0    -1   1    0   
$EndComp
Text Label 3150 3450 2    50   ~ 0
D6
Wire Wire Line
	2350 3450 2150 3450
Wire Wire Line
	2150 3450 2150 3550
Wire Wire Line
	2750 3450 2550 3450
Wire Wire Line
	2550 3450 2550 3550
Wire Wire Line
	2950 3450 2950 3550
Wire Wire Line
	2950 3450 3150 3450
Wire Wire Line
	1950 3450 1750 3450
Wire Wire Line
	1750 3450 1750 3550
Wire Wire Line
	1550 3450 1350 3450
Wire Wire Line
	1350 3550 1350 3450
Wire Wire Line
	1000 3450 1000 3550
Wire Wire Line
	1200 3450 1000 3450
Wire Wire Line
	1000 3950 1350 3950
Connection ~ 2550 3950
Wire Wire Line
	2550 3950 2950 3950
Connection ~ 2150 3950
Wire Wire Line
	2150 3950 2550 3950
Connection ~ 1750 3950
Wire Wire Line
	1750 3950 1950 3950
Connection ~ 1350 3950
Wire Wire Line
	1350 3950 1750 3950
Wire Wire Line
	1950 3950 1950 4150
Connection ~ 1950 3950
Wire Wire Line
	1950 3950 2150 3950
$Comp
L power:GND #PWR01
U 1 1 5F1394E5
P 1950 4150
F 0 "#PWR01" H 1950 3900 50  0001 C CNN
F 1 "GND" H 1955 3977 50  0000 C CNN
F 2 "" H 1950 4150 50  0001 C CNN
F 3 "" H 1950 4150 50  0001 C CNN
	1    1950 4150
	-1   0    0    -1  
$EndComp
Wire Notes Line
	3250 4450 750  4450
Wire Notes Line style solid
	750  4450 750  3250
Wire Notes Line style solid
	750  3250 3250 3250
Wire Notes Line style solid
	3250 3250 3250 4450
Wire Notes Line style solid
	3250 4450 750  4450
Text Notes 3250 3250 2    50   ~ 10
User Buttons
Text Notes 6100 4350 0    50   Italic 0
LCD_Enable
Wire Wire Line
	6650 4500 6650 4350
Wire Wire Line
	6650 4350 6750 4350
Wire Wire Line
	5750 4150 6750 4150
Text Notes 6100 4450 0    50   Italic 0
LCD_Select
Text Notes 6100 3450 0    50   Italic 0
LCD_D7
Text Notes 6100 3550 0    50   Italic 0
LCD_D6
Text Notes 6100 3650 0    50   Italic 0
LCD_D5
Text Notes 6100 3750 0    50   Italic 0
LCD_D4
Text Notes 6100 4250 0    50   Italic 0
LCD_Backlight
Text Notes 6100 3850 0    50   Italic 0
Time+_Button
Text Notes 6100 3950 0    50   Italic 0
Time-_Button
Text Notes 4500 3950 2    50   Italic 0
Cancel_Button
Text Notes 4500 4050 2    50   Italic 0
Snooze_Button
Text Notes 4500 4150 2    50   Italic 0
Backlight_Button
Text Notes 4500 4250 2    50   Italic 0
Set_Button
Wire Wire Line
	4050 3350 4050 3250
Wire Wire Line
	4050 3250 4500 3250
Connection ~ 4050 3250
Wire Wire Line
	4050 3250 4050 3150
Wire Wire Line
	4500 3250 4500 3850
NoConn ~ 5150 2850
NoConn ~ 5350 2850
NoConn ~ 4750 3250
NoConn ~ 4750 3450
NoConn ~ 4750 3650
NoConn ~ 4750 4350
NoConn ~ 4750 4550
NoConn ~ 4750 4650
NoConn ~ 5750 4550
NoConn ~ 5750 4050
NoConn ~ 5750 3350
NoConn ~ 5750 3250
NoConn ~ 8000 3900
NoConn ~ 8000 4000
NoConn ~ 8000 4100
NoConn ~ 8000 4200
$Comp
L Mechanical:MountingHole H1
U 1 1 5F1B765B
P 6400 5750
F 0 "H1" H 6500 5796 50  0000 L CNN
F 1 "MountingHole" H 6500 5705 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 6400 5750 50  0001 C CNN
F 3 "~" H 6400 5750 50  0001 C CNN
	1    6400 5750
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 5F1B83F1
P 7150 5750
F 0 "H2" H 7250 5796 50  0000 L CNN
F 1 "MountingHole" H 7250 5705 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 7150 5750 50  0001 C CNN
F 3 "~" H 7150 5750 50  0001 C CNN
	1    7150 5750
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 5F1BA130
P 7900 5750
F 0 "H3" H 8000 5796 50  0000 L CNN
F 1 "MountingHole" H 8000 5705 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 7900 5750 50  0001 C CNN
F 3 "~" H 7900 5750 50  0001 C CNN
	1    7900 5750
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 5F1BA136
P 8650 5750
F 0 "H4" H 8750 5796 50  0000 L CNN
F 1 "MountingHole" H 8750 5705 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 8650 5750 50  0001 C CNN
F 3 "~" H 8650 5750 50  0001 C CNN
	1    8650 5750
	1    0    0    -1  
$EndComp
$EndSCHEMATC
