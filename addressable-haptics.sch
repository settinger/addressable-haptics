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
L MCU_Microchip_ATtiny:ATtiny10-TS U1
U 1 1 5E4D283C
P 4775 2850
F 0 "U1" H 4245 2896 50  0000 R CNN
F 1 "ATtiny10-TS" H 4245 2805 50  0000 R CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6" H 4775 2850 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-8127-AVR-8-bit-Microcontroller-ATtiny4-ATtiny5-ATtiny9-ATtiny10_Datasheet.pdf" H 4775 2850 50  0001 C CNN
	1    4775 2850
	1    0    0    -1  
$EndComp
Text Label 5475 2650 0    50   ~ 0
to_mosfet
Wire Wire Line
	5475 2750 5375 2750
Text GLabel 4675 2125 0    50   Input ~ 0
3.3V
Wire Wire Line
	4675 2125 4775 2125
Wire Wire Line
	4775 2125 4775 2250
Text GLabel 4675 3550 0    50   Input ~ 0
0V
Wire Wire Line
	4675 3550 4775 3550
Wire Wire Line
	4775 3550 4775 3450
$Comp
L Connector_Generic:Conn_01x03 J3
U 1 1 5E4D319D
P 2650 2850
F 0 "J3" H 2568 3167 50  0000 C CNN
F 1 "Conn_01x03" H 2568 3076 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Horizontal" H 2650 2850 50  0001 C CNN
F 3 "~" H 2650 2850 50  0001 C CNN
	1    2650 2850
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J2
U 1 1 5E4D36EA
P 7025 2825
F 0 "J2" H 7105 2867 50  0000 L CNN
F 1 "Conn_01x03" H 7105 2776 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Horizontal" H 7025 2825 50  0001 C CNN
F 3 "~" H 7025 2825 50  0001 C CNN
	1    7025 2825
	1    0    0    -1  
$EndComp
Text GLabel 2850 2750 2    50   Input ~ 0
3.3V
Text GLabel 6825 2725 0    50   Input ~ 0
3.3V
Text GLabel 2850 2950 2    50   Input ~ 0
0V
Text GLabel 6825 2925 0    50   Input ~ 0
0V
Text Label 2850 2850 0    50   ~ 0
signal_in
Text Label 6825 2825 2    50   ~ 0
signal_out
$Comp
L Connector_Generic:Conn_02x04_Counter_Clockwise J4
U 1 1 5E4D46D6
P 4750 4325
F 0 "J4" H 4800 4642 50  0000 C CNN
F 1 "SOICBite" H 4800 4551 50  0000 C CNN
F 2 "addressable-haptics:SOIC_clipProgSmall" H 4750 4325 50  0001 C CNN
F 3 "~" H 4750 4325 50  0001 C CNN
	1    4750 4325
	1    0    0    -1  
$EndComp
Text Label 5100 1350 2    50   ~ 0
to_motor
$Comp
L Device:R R1
U 1 1 5E4DCF38
P 4550 1650
F 0 "R1" V 4343 1650 50  0000 C CNN
F 1 "1k" V 4434 1650 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4480 1650 50  0001 C CNN
F 3 "~" H 4550 1650 50  0001 C CNN
	1    4550 1650
	0    1    1    0   
$EndComp
Wire Wire Line
	4325 1650 4400 1650
Wire Wire Line
	4700 1650 4800 1650
Text GLabel 5050 1950 0    50   Input ~ 0
3.3V
Wire Wire Line
	5050 1950 5100 1950
Wire Wire Line
	5100 1950 5100 1850
Text Label 4325 1650 2    50   ~ 0
to_mosfet
Wire Wire Line
	5100 1350 5100 1450
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 5E4E8703
P 4800 900
F 0 "J1" H 4880 892 50  0000 L CNN
F 1 "Conn_01x02" H 4880 801 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical" H 4800 900 50  0001 C CNN
F 3 "~" H 4800 900 50  0001 C CNN
	1    4800 900 
	1    0    0    -1  
$EndComp
Text Label 4600 900  2    50   ~ 0
to_motor
Text GLabel 4600 1000 0    50   Input ~ 0
0V
$Comp
L Device:C C1
U 1 1 5E4F0AC0
P 3875 2425
F 0 "C1" H 3990 2471 50  0000 L CNN
F 1 ".1 uF" H 3990 2380 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3913 2275 50  0001 C CNN
F 3 "~" H 3875 2425 50  0001 C CNN
	1    3875 2425
	1    0    0    -1  
$EndComp
Text GLabel 3875 2275 1    50   Input ~ 0
3.3V
Text GLabel 3875 2575 3    50   Input ~ 0
0V
Text Label 5975 2550 0    50   ~ 0
tpi_data
Wire Wire Line
	5375 2550 5975 2550
Text Label 5975 2650 0    50   ~ 0
tpi_clk
Wire Wire Line
	5375 2650 5975 2650
Text Label 5975 2850 0    50   ~ 0
tpi_rst
Wire Wire Line
	5975 2850 5375 2850
Text GLabel 4550 4225 0    50   Input ~ 0
3.3V
Text Label 4550 4425 2    50   ~ 0
tpi_clk
Text GLabel 4550 4525 0    50   Input ~ 0
0V
Text Label 5050 4425 0    50   ~ 0
tpi_data
Text Label 5050 4325 0    50   ~ 0
tpi_rst
Text Label 5475 2750 0    50   ~ 0
signal_in
Text Label 5475 2550 0    50   ~ 0
signal_out
$Comp
L Device:Q_NMOS_GSD Q1
U 1 1 5F48D374
P 5000 1650
F 0 "Q1" H 5250 1600 50  0000 L CNN
F 1 "Q_NMOS_GSD" H 5250 1650 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 5200 1750 50  0001 C CNN
F 3 "~" H 5000 1650 50  0001 C CNN
	1    5000 1650
	1    0    0    1   
$EndComp
$EndSCHEMATC
