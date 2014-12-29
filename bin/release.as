opt subtitle "Microchip Technology Omniscient Code Generator (Lite mode) build 59893"

opt pagewidth 120

	opt lm

	processor	18F26K22
porta	equ	0F80h
portb	equ	0F81h
portc	equ	0F82h
portd	equ	0F83h
porte	equ	0F84h
lata	equ	0F89h
latb	equ	0F8Ah
latc	equ	0F8Bh
latd	equ	0F8Ch
late	equ	0F8Dh
trisa	equ	0F92h
trisb	equ	0F93h
trisc	equ	0F94h
trisd	equ	0F95h
trise	equ	0F96h
pie1	equ	0F9Dh
pir1	equ	0F9Eh
ipr1	equ	0F9Fh
pie2	equ	0FA0h
pir2	equ	0FA1h
ipr2	equ	0FA2h
t3con	equ	0FB1h
tmr3l	equ	0FB2h
tmr3h	equ	0FB3h
ccp1con	equ	0FBDh
ccpr1l	equ	0FBEh
ccpr1h	equ	0FBFh
adcon1	equ	0FC1h
adcon0	equ	0FC2h
adresl	equ	0FC3h
adresh	equ	0FC4h
sspcon2	equ	0FC5h
sspcon1	equ	0FC6h
sspstat	equ	0FC7h
sspadd	equ	0FC8h
sspbuf	equ	0FC9h
t2con	equ	0FCAh
pr2	equ	0FCBh
tmr2	equ	0FCCh
t1con	equ	0FCDh
tmr1l	equ	0FCEh
tmr1h	equ	0FCFh
rcon	equ	0FD0h
wdtcon	equ	0FD1h
lvdcon	equ	0FD2h
osccon	equ	0FD3h
t0con	equ	0FD5h
tmr0l	equ	0FD6h
tmr0h	equ	0FD7h
status	equ	0FD8h
fsr2	equ	0FD9h
fsr2l	equ	0FD9h
fsr2h	equ	0FDAh
plusw2	equ	0FDBh
preinc2	equ	0FDCh
postdec2	equ	0FDDh
postinc2	equ	0FDEh
indf2	equ	0FDFh
bsr	equ	0FE0h
fsr1	equ	0FE1h
fsr1l	equ	0FE1h
fsr1h	equ	0FE2h
plusw1	equ	0FE3h
preinc1	equ	0FE4h
postdec1	equ	0FE5h
postinc1	equ	0FE6h
indf1	equ	0FE7h
wreg	equ	0FE8h
fsr0	equ	0FE9h
fsr0l	equ	0FE9h
fsr0h	equ	0FEAh
plusw0	equ	0FEBh
preinc0	equ	0FECh
postdec0	equ	0FEDh
postinc0	equ	0FEEh
indf0	equ	0FEFh
intcon3	equ	0FF0h
intcon2	equ	0FF1h
intcon	equ	0FF2h
prod	equ	0FF3h
prodl	equ	0FF3h
prodh	equ	0FF4h
tablat	equ	0FF5h
tblptr	equ	0FF6h
tblptrl	equ	0FF6h
tblptrh	equ	0FF7h
tblptru	equ	0FF8h
pcl	equ	0FF9h
pclat	equ	0FFAh
pclath	equ	0FFAh
pclatu	equ	0FFBh
stkptr	equ	0FFCh
tosl	equ	0FFDh
tosh	equ	0FFEh
tosu	equ	0FFFh
clrc   macro
	bcf	status,0
endm
setc   macro
	bsf	status,0
endm
clrz   macro
	bcf	status,2
endm
setz   macro
	bsf	status,2
endm
skipnz macro
	btfsc	status,2
endm
skipz  macro
	btfss	status,2
endm
skipnc macro
	btfsc	status,0
endm
skipc  macro
	btfss	status,0
endm
pushw macro
	movwf postinc1
endm
pushf macro arg1
	movff arg1, postinc1
endm
popw macro
	movf postdec1,w
	movf indf1,w
endm
popf macro arg1
	movf postdec1,w
	movff indf1,arg1
endm
popfc macro arg1
	movff plusw1,arg1
	decfsz fsr1,f
endm
	global	__ramtop
	global	__accesstop
# 49 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
ANSELA equ 0F38h ;# 
# 93 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
ANSELB equ 0F39h ;# 
# 142 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
ANSELC equ 0F3Ah ;# 
# 192 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PMD2 equ 0F3Dh ;# 
# 229 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PMD1 equ 0F3Eh ;# 
# 293 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PMD0 equ 0F3Fh ;# 
# 372 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
VREFCON2 equ 0F40h ;# 
# 377 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
DACCON1 equ 0F40h ;# 
# 473 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
VREFCON1 equ 0F41h ;# 
# 478 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
DACCON0 equ 0F41h ;# 
# 592 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
VREFCON0 equ 0F42h ;# 
# 597 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
FVRCON equ 0F42h ;# 
# 685 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CTMUICON equ 0F43h ;# 
# 690 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CTMUICONH equ 0F43h ;# 
# 834 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CTMUCONL equ 0F44h ;# 
# 839 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CTMUCON1 equ 0F44h ;# 
# 987 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CTMUCONH equ 0F45h ;# 
# 992 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CTMUCON0 equ 0F45h ;# 
# 1098 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
SRCON1 equ 0F46h ;# 
# 1159 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
SRCON0 equ 0F47h ;# 
# 1229 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CCPTMRS1 equ 0F48h ;# 
# 1280 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CCPTMRS0 equ 0F49h ;# 
# 1353 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
T6CON equ 0F4Ah ;# 
# 1423 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PR6 equ 0F4Bh ;# 
# 1442 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TMR6 equ 0F4Ch ;# 
# 1461 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
T5GCON equ 0F4Dh ;# 
# 1555 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
T5CON equ 0F4Eh ;# 
# 1665 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TMR5 equ 0F4Fh ;# 
# 1671 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TMR5L equ 0F4Fh ;# 
# 1690 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TMR5H equ 0F50h ;# 
# 1709 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
T4CON equ 0F51h ;# 
# 1779 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PR4 equ 0F52h ;# 
# 1798 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TMR4 equ 0F53h ;# 
# 1817 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CCP5CON equ 0F54h ;# 
# 1880 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CCPR5 equ 0F55h ;# 
# 1886 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CCPR5L equ 0F55h ;# 
# 1905 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CCPR5H equ 0F56h ;# 
# 1924 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CCP4CON equ 0F57h ;# 
# 1987 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CCPR4 equ 0F58h ;# 
# 1993 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CCPR4L equ 0F58h ;# 
# 2012 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CCPR4H equ 0F59h ;# 
# 2031 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PSTR3CON equ 0F5Ah ;# 
# 2118 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
ECCP3AS equ 0F5Bh ;# 
# 2123 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CCP3AS equ 0F5Bh ;# 
# 2359 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PWM3CON equ 0F5Ch ;# 
# 2428 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CCP3CON equ 0F5Dh ;# 
# 2509 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CCPR3 equ 0F5Eh ;# 
# 2515 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CCPR3L equ 0F5Eh ;# 
# 2534 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CCPR3H equ 0F5Fh ;# 
# 2553 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
SLRCON equ 0F60h ;# 
# 2584 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
WPUB equ 0F61h ;# 
# 2645 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
IOCB equ 0F62h ;# 
# 2683 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PSTR2CON equ 0F63h ;# 
# 2858 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
ECCP2AS equ 0F64h ;# 
# 2863 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CCP2AS equ 0F64h ;# 
# 3099 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PWM2CON equ 0F65h ;# 
# 3168 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CCP2CON equ 0F66h ;# 
# 3243 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CCPR2 equ 0F67h ;# 
# 3249 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CCPR2L equ 0F67h ;# 
# 3268 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CCPR2H equ 0F68h ;# 
# 3287 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
SSP2CON3 equ 0F69h ;# 
# 3348 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
SSP2MSK equ 0F6Ah ;# 
# 3409 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
SSP2CON2 equ 0F6Bh ;# 
# 3586 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
SSP2CON1 equ 0F6Ch ;# 
# 3726 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
SSP2STAT equ 0F6Dh ;# 
# 4118 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
SSP2ADD equ 0F6Eh ;# 
# 4208 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
SSP2BUF equ 0F6Fh ;# 
# 4227 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
BAUDCON2 equ 0F70h ;# 
# 4232 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
BAUD2CON equ 0F70h ;# 
# 4534 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
RCSTA2 equ 0F71h ;# 
# 4539 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
RC2STA equ 0F71h ;# 
# 4825 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TXSTA2 equ 0F72h ;# 
# 4830 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TX2STA equ 0F72h ;# 
# 5080 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TXREG2 equ 0F73h ;# 
# 5085 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TX2REG equ 0F73h ;# 
# 5117 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
RCREG2 equ 0F74h ;# 
# 5122 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
RC2REG equ 0F74h ;# 
# 5154 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
SPBRG2 equ 0F75h ;# 
# 5159 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
SP2BRG equ 0F75h ;# 
# 5191 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
SPBRGH2 equ 0F76h ;# 
# 5196 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
SP2BRGH equ 0F76h ;# 
# 5228 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CM2CON1 equ 0F77h ;# 
# 5233 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CM12CON equ 0F77h ;# 
# 5349 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CM2CON0 equ 0F78h ;# 
# 5354 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CM2CON equ 0F78h ;# 
# 5628 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CM1CON0 equ 0F79h ;# 
# 5633 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CM1CON equ 0F79h ;# 
# 6049 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PIE4 equ 0F7Ah ;# 
# 6080 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PIR4 equ 0F7Bh ;# 
# 6111 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
IPR4 equ 0F7Ch ;# 
# 6150 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PIE5 equ 0F7Dh ;# 
# 6181 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PIR5 equ 0F7Eh ;# 
# 6212 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
IPR5 equ 0F7Fh ;# 
# 6260 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PORTA equ 0F80h ;# 
# 6552 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PORTB equ 0F81h ;# 
# 6924 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PORTC equ 0F82h ;# 
# 7257 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PORTE equ 0F84h ;# 
# 7526 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
LATA equ 0F89h ;# 
# 7658 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
LATB equ 0F8Ah ;# 
# 7790 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
LATC equ 0F8Bh ;# 
# 7922 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TRISA equ 0F92h ;# 
# 7927 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
DDRA equ 0F92h ;# 
# 8143 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TRISB equ 0F93h ;# 
# 8148 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
DDRB equ 0F93h ;# 
# 8364 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TRISC equ 0F94h ;# 
# 8369 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
DDRC equ 0F94h ;# 
# 8585 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TRISE equ 0F96h ;# 
# 8605 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
OSCTUNE equ 0F9Bh ;# 
# 8674 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
HLVDCON equ 0F9Ch ;# 
# 8679 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
LVDCON equ 0F9Ch ;# 
# 8953 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PIE1 equ 0F9Dh ;# 
# 9029 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PIR1 equ 0F9Eh ;# 
# 9105 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
IPR1 equ 0F9Fh ;# 
# 9181 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PIE2 equ 0FA0h ;# 
# 9266 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PIR2 equ 0FA1h ;# 
# 9351 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
IPR2 equ 0FA2h ;# 
# 9436 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PIE3 equ 0FA3h ;# 
# 9559 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PIR3 equ 0FA4h ;# 
# 9638 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
IPR3 equ 0FA5h ;# 
# 9717 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
EECON1 equ 0FA6h ;# 
# 9782 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
EECON2 equ 0FA7h ;# 
# 9801 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
EEDATA equ 0FA8h ;# 
# 9820 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
EEADR equ 0FA9h ;# 
# 9889 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
EEADRH equ 0FAAh ;# 
# 9922 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
RCSTA1 equ 0FABh ;# 
# 9927 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
RCSTA equ 0FABh ;# 
# 9931 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
RC1STA equ 0FABh ;# 
# 10383 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TXSTA1 equ 0FACh ;# 
# 10388 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TXSTA equ 0FACh ;# 
# 10392 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TX1STA equ 0FACh ;# 
# 10763 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TXREG1 equ 0FADh ;# 
# 10768 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TXREG equ 0FADh ;# 
# 10772 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TX1REG equ 0FADh ;# 
# 10840 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
RCREG1 equ 0FAEh ;# 
# 10845 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
RCREG equ 0FAEh ;# 
# 10849 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
RC1REG equ 0FAEh ;# 
# 10917 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
SPBRG1 equ 0FAFh ;# 
# 10922 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
SPBRG equ 0FAFh ;# 
# 10926 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
SP1BRG equ 0FAFh ;# 
# 10994 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
SPBRGH1 equ 0FB0h ;# 
# 10999 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
SPBRGH equ 0FB0h ;# 
# 11003 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
SP1BRGH equ 0FB0h ;# 
# 11071 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
T3CON equ 0FB1h ;# 
# 11180 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TMR3 equ 0FB2h ;# 
# 11186 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TMR3L equ 0FB2h ;# 
# 11205 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TMR3H equ 0FB3h ;# 
# 11224 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
T3GCON equ 0FB4h ;# 
# 11318 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
ECCP1AS equ 0FB6h ;# 
# 11323 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
ECCPAS equ 0FB6h ;# 
# 11699 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PWM1CON equ 0FB7h ;# 
# 11704 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PWMCON equ 0FB7h ;# 
# 11952 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
BAUDCON1 equ 0FB8h ;# 
# 11957 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
BAUDCON equ 0FB8h ;# 
# 11961 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
BAUDCTL equ 0FB8h ;# 
# 11965 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
BAUD1CON equ 0FB8h ;# 
# 12741 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PSTR1CON equ 0FB9h ;# 
# 12746 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PSTRCON equ 0FB9h ;# 
# 12914 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
T2CON equ 0FBAh ;# 
# 12984 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PR2 equ 0FBBh ;# 
# 13003 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TMR2 equ 0FBCh ;# 
# 13022 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CCP1CON equ 0FBDh ;# 
# 13103 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CCPR1 equ 0FBEh ;# 
# 13109 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CCPR1L equ 0FBEh ;# 
# 13128 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
CCPR1H equ 0FBFh ;# 
# 13147 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
ADCON2 equ 0FC0h ;# 
# 13217 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
ADCON1 equ 0FC1h ;# 
# 13284 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
ADCON0 equ 0FC2h ;# 
# 13408 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
ADRES equ 0FC3h ;# 
# 13414 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
ADRESL equ 0FC3h ;# 
# 13433 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
ADRESH equ 0FC4h ;# 
# 13452 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
SSP1CON2 equ 0FC5h ;# 
# 13457 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
SSPCON2 equ 0FC5h ;# 
# 13895 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
SSP1CON1 equ 0FC6h ;# 
# 13900 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
SSPCON1 equ 0FC6h ;# 
# 14174 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
SSP1STAT equ 0FC7h ;# 
# 14179 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
SSPSTAT equ 0FC7h ;# 
# 14885 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
SSP1ADD equ 0FC8h ;# 
# 14890 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
SSPADD equ 0FC8h ;# 
# 15222 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
SSP1BUF equ 0FC9h ;# 
# 15227 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
SSPBUF equ 0FC9h ;# 
# 15275 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
SSP1MSK equ 0FCAh ;# 
# 15280 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
SSPMSK equ 0FCAh ;# 
# 15396 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
SSP1CON3 equ 0FCBh ;# 
# 15401 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
SSPCON3 equ 0FCBh ;# 
# 15517 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
T1GCON equ 0FCCh ;# 
# 15611 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
T1CON equ 0FCDh ;# 
# 15723 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TMR1 equ 0FCEh ;# 
# 15729 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TMR1L equ 0FCEh ;# 
# 15748 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TMR1H equ 0FCFh ;# 
# 15767 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
RCON equ 0FD0h ;# 
# 15899 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
WDTCON equ 0FD1h ;# 
# 15926 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
OSCCON2 equ 0FD2h ;# 
# 15982 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
OSCCON equ 0FD3h ;# 
# 16064 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
T0CON equ 0FD5h ;# 
# 16133 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TMR0 equ 0FD6h ;# 
# 16139 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TMR0L equ 0FD6h ;# 
# 16158 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TMR0H equ 0FD7h ;# 
# 16177 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
STATUS equ 0FD8h ;# 
# 16255 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
FSR2 equ 0FD9h ;# 
# 16261 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
FSR2L equ 0FD9h ;# 
# 16280 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
FSR2H equ 0FDAh ;# 
# 16286 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PLUSW2 equ 0FDBh ;# 
# 16305 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PREINC2 equ 0FDCh ;# 
# 16324 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
POSTDEC2 equ 0FDDh ;# 
# 16343 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
POSTINC2 equ 0FDEh ;# 
# 16362 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
INDF2 equ 0FDFh ;# 
# 16381 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
BSR equ 0FE0h ;# 
# 16387 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
FSR1 equ 0FE1h ;# 
# 16393 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
FSR1L equ 0FE1h ;# 
# 16412 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
FSR1H equ 0FE2h ;# 
# 16418 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PLUSW1 equ 0FE3h ;# 
# 16437 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PREINC1 equ 0FE4h ;# 
# 16456 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
POSTDEC1 equ 0FE5h ;# 
# 16475 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
POSTINC1 equ 0FE6h ;# 
# 16494 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
INDF1 equ 0FE7h ;# 
# 16513 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
WREG equ 0FE8h ;# 
# 16550 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
FSR0 equ 0FE9h ;# 
# 16556 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
FSR0L equ 0FE9h ;# 
# 16575 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
FSR0H equ 0FEAh ;# 
# 16581 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PLUSW0 equ 0FEBh ;# 
# 16600 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PREINC0 equ 0FECh ;# 
# 16619 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
POSTDEC0 equ 0FEDh ;# 
# 16638 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
POSTINC0 equ 0FEEh ;# 
# 16657 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
INDF0 equ 0FEFh ;# 
# 16676 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
INTCON3 equ 0FF0h ;# 
# 16767 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
INTCON2 equ 0FF1h ;# 
# 16836 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
INTCON equ 0FF2h ;# 
# 16967 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PROD equ 0FF3h ;# 
# 16973 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PRODL equ 0FF3h ;# 
# 16992 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PRODH equ 0FF4h ;# 
# 17011 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TABLAT equ 0FF5h ;# 
# 17032 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TBLPTR equ 0FF6h ;# 
# 17038 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TBLPTRL equ 0FF6h ;# 
# 17057 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TBLPTRH equ 0FF7h ;# 
# 17076 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TBLPTRU equ 0FF8h ;# 
# 17106 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PCLAT equ 0FF9h ;# 
# 17113 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PC equ 0FF9h ;# 
# 17119 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PCL equ 0FF9h ;# 
# 17138 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PCLATH equ 0FFAh ;# 
# 17157 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
PCLATU equ 0FFBh ;# 
# 17163 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
STKPTR equ 0FFCh ;# 
# 17268 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TOS equ 0FFDh ;# 
# 17274 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TOSL equ 0FFDh ;# 
# 17293 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TOSH equ 0FFEh ;# 
# 17312 "/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
TOSU equ 0FFFh ;# 
	FNROOT	_main
	global	_INTCONbits
_INTCONbits	set	0xFF2
psect	text0,class=CODE,space=0,reloc=2
; #config settings
	file	"/opt/microchip/xc8/v1.33/include/pic18f26k22.h"
	line	16881
global __ptext0
__ptext0:
global __CFG_PLLCFG$ON
__CFG_PLLCFG$ON equ 0x0
global __CFG_PRICLKEN$OFF
__CFG_PRICLKEN$OFF equ 0x0
global __CFG_FCMEN$ON
__CFG_FCMEN$ON equ 0x0
global __CFG_IESO$OFF
__CFG_IESO$OFF equ 0x0
global __CFG_FOSC$INTIO67
__CFG_FOSC$INTIO67 equ 0x0
global __CFG_BOREN$ON
__CFG_BOREN$ON equ 0x0
global __CFG_BORV$190
__CFG_BORV$190 equ 0x0
global __CFG_PWRTEN$ON
__CFG_PWRTEN$ON equ 0x0
global __CFG_WDTPS$16384
__CFG_WDTPS$16384 equ 0x0
global __CFG_WDTEN$SWON
__CFG_WDTEN$SWON equ 0x0
global __CFG_CCP2MX$PORTC1
__CFG_CCP2MX$PORTC1 equ 0x0
global __CFG_CCP3MX$PORTB5
__CFG_CCP3MX$PORTB5 equ 0x0
global __CFG_T3CMX$PORTC0
__CFG_T3CMX$PORTC0 equ 0x0
global __CFG_HFOFST$OFF
__CFG_HFOFST$OFF equ 0x0
global __CFG_PBADEN$ON
__CFG_PBADEN$ON equ 0x0
global __CFG_MCLRE$EXTMCLR
__CFG_MCLRE$EXTMCLR equ 0x0
global __CFG_P2BMX$PORTB5
__CFG_P2BMX$PORTB5 equ 0x0
global __CFG_STVREN$ON
__CFG_STVREN$ON equ 0x0
global __CFG_DEBUG$OFF
__CFG_DEBUG$OFF equ 0x0
global __CFG_LVP$ON
__CFG_LVP$ON equ 0x0
global __CFG_XINST$OFF
__CFG_XINST$OFF equ 0x0
global __CFG_CP0$OFF
__CFG_CP0$OFF equ 0x0
global __CFG_CP1$OFF
__CFG_CP1$OFF equ 0x0
global __CFG_CP3$OFF
__CFG_CP3$OFF equ 0x0
global __CFG_CPB$OFF
__CFG_CPB$OFF equ 0x0
global __CFG_CPD$OFF
__CFG_CPD$OFF equ 0x0
global __CFG_WRT0$OFF
__CFG_WRT0$OFF equ 0x0
global __CFG_WRT1$OFF
__CFG_WRT1$OFF equ 0x0
global __CFG_WRT2$OFF
__CFG_WRT2$OFF equ 0x0
global __CFG_WRT3$OFF
__CFG_WRT3$OFF equ 0x0
global __CFG_WRTB$OFF
__CFG_WRTB$OFF equ 0x0
global __CFG_WRTC$OFF
__CFG_WRTC$OFF equ 0x0
global __CFG_WRTD$OFF
__CFG_WRTD$OFF equ 0x0
global __CFG_EBTR0$OFF
__CFG_EBTR0$OFF equ 0x0
global __CFG_EBTR1$OFF
__CFG_EBTR1$OFF equ 0x0
global __CFG_EBTR2$OFF
__CFG_EBTR2$OFF equ 0x0
global __CFG_EBTR3$OFF
__CFG_EBTR3$OFF equ 0x0
global __CFG_EBTRB$OFF
__CFG_EBTRB$OFF equ 0x0
	file	"bin/release.as"
	line	#
psect	cinit,class=CODE,delta=1,reloc=2
global __pcinit
__pcinit:
global start_initialization
start_initialization:

global __initialization
__initialization:
psect cinit,class=CODE,delta=1
global end_of_initialization,__end_of__initialization

;End of C runtime variable initialization code

end_of_initialization:
__end_of__initialization:movlb 0
goto _main	;jump to C main() function
psect	cstackCOMRAM,class=COMRAM,space=1,noexec
global __pcstackCOMRAM
__pcstackCOMRAM:
??_main:	; 0 bytes @ 0x0
?_main:	; 2 bytes @ 0x0
;!
;!Data Sizes:
;!    Strings     0
;!    Constant    0
;!    Data        0
;!    BSS         0
;!    Persistent  0
;!    Stack       0
;!
;!Auto Spaces:
;!    Space          Size  Autos    Used
;!    COMRAM           95      0       0
;!    BANK0           160      0       0
;!    BANK1           256      0       0
;!    BANK2           256      0       0
;!    BANK3           256      0       0
;!    BANK4           256      0       0
;!    BANK5           256      0       0
;!    BANK6           256      0       0
;!    BANK7           256      0       0
;!    BANK8           256      0       0
;!    BANK9           256      0       0
;!    BANK10          256      0       0
;!    BANK11          256      0       0
;!    BANK12          256      0       0
;!    BANK13          256      0       0
;!    BANK14          256      0       0
;!    BANK15           56      0       0

;!
;!Pointer List with Targets:
;!
;!    None.


;!
;!Critical Paths under _main in COMRAM
;!
;!    None.
;!
;!Critical Paths under _main in BANK0
;!
;!    None.
;!
;!Critical Paths under _main in BANK1
;!
;!    None.
;!
;!Critical Paths under _main in BANK2
;!
;!    None.
;!
;!Critical Paths under _main in BANK3
;!
;!    None.
;!
;!Critical Paths under _main in BANK4
;!
;!    None.
;!
;!Critical Paths under _main in BANK5
;!
;!    None.
;!
;!Critical Paths under _main in BANK6
;!
;!    None.
;!
;!Critical Paths under _main in BANK7
;!
;!    None.
;!
;!Critical Paths under _main in BANK8
;!
;!    None.
;!
;!Critical Paths under _main in BANK9
;!
;!    None.
;!
;!Critical Paths under _main in BANK10
;!
;!    None.
;!
;!Critical Paths under _main in BANK11
;!
;!    None.
;!
;!Critical Paths under _main in BANK12
;!
;!    None.
;!
;!Critical Paths under _main in BANK13
;!
;!    None.
;!
;!Critical Paths under _main in BANK14
;!
;!    None.
;!
;!Critical Paths under _main in BANK15
;!
;!    None.

;;
;;Main: autosize = 0, tempsize = 0, incstack = 0, save=0
;;

;!
;!Call Graph Tables:
;!
;! ---------------------------------------------------------------------------------
;! (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;! ---------------------------------------------------------------------------------
;! (0) _main                                                 0     0      0       0
;! ---------------------------------------------------------------------------------
;! Estimated maximum stack depth 0
;! ---------------------------------------------------------------------------------
;!
;! Call Graph Graphs:
;!
;! _main (ROOT)
;!

;! Address spaces:

;!Name               Size   Autos  Total    Cost      Usage
;!BITCOMRAM           5F      0       0       0        0.0%
;!EEDATA             400      0       0       0        0.0%
;!NULL                 0      0       0       0        0.0%
;!CODE                 0      0       0       0        0.0%
;!COMRAM              5F      0       0       1        0.0%
;!STACK                0      0       0       2        0.0%
;!DATA                 0      0       0       3        0.0%
;!BITBANK0            A0      0       0       4        0.0%
;!BANK0               A0      0       0       5        0.0%
;!BITBANK1           100      0       0       6        0.0%
;!BANK1              100      0       0       7        0.0%
;!BITBANK2           100      0       0       8        0.0%
;!BANK2              100      0       0       9        0.0%
;!BITBANK3           100      0       0      10        0.0%
;!BANK3              100      0       0      11        0.0%
;!ABS                  0      0       0      12        0.0%
;!BITBANK4           100      0       0      13        0.0%
;!BANK4              100      0       0      14        0.0%
;!BITBANK5           100      0       0      15        0.0%
;!BANK5              100      0       0      16        0.0%
;!BITBANK6           100      0       0      17        0.0%
;!BANK6              100      0       0      18        0.0%
;!BITBANK7           100      0       0      19        0.0%
;!BANK7              100      0       0      20        0.0%
;!BITBANK8           100      0       0      21        0.0%
;!BANK8              100      0       0      22        0.0%
;!BITBANK9           100      0       0      23        0.0%
;!BANK9              100      0       0      24        0.0%
;!BITBANK10          100      0       0      25        0.0%
;!BANK10             100      0       0      26        0.0%
;!BITBANK11          100      0       0      27        0.0%
;!BANK11             100      0       0      28        0.0%
;!BITBANK12          100      0       0      29        0.0%
;!BANK12             100      0       0      30        0.0%
;!BITBANK13          100      0       0      31        0.0%
;!BANK13             100      0       0      32        0.0%
;!BITBANK14          100      0       0      33        0.0%
;!BANK14             100      0       0      34        0.0%
;!BITBANK15           38      0       0      35        0.0%
;!BANK15              38      0       0      36        0.0%
;!BIGRAM             F37      0       0      37        0.0%
;!BITSFR_1             0      0       0      40        0.0%
;!SFR_1                0      0       0      40        0.0%
;!BITSFR               0      0       0      40        0.0%
;!SFR                  0      0       0      40        0.0%

	global	_main

;; *************** function _main *****************
;; Defined at:
;;		line 6 in file "src/main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  2    4[COMRAM] int 
;; Registers used:
;;		None
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14  BANK15
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; This function calls:
;;		Nothing
;; This function is called by:
;;		Startup code after reset
;; This function uses a non-reentrant model
;;
psect	text0
psect	text0
	file	"src/main.c"
	line	6
	global	__size_of_main
	__size_of_main	equ	__end_of_main-_main
	
_main:
;incstack = 0
	opt	stack 31
	line	7
	
l581:
;main.c: 7: (INTCONbits.GIE = 1);
	bsf	((c:4082)),c,7	;volatile
	line	8
;main.c: 8: (INTCONbits.GIE = 0);
	bcf	((c:4082)),c,7	;volatile
	line	9
	
l5:
	global	start
	goto	start
	opt stack 0
GLOBAL	__end_of_main
	__end_of_main:
	signat	_main,90
	GLOBAL	__activetblptr
__activetblptr	EQU	0
	psect	intsave_regs,class=BIGRAM,space=1,noexec
	PSECT	rparam,class=COMRAM,space=1,noexec
	GLOBAL	__Lrparam
	FNCONF	rparam,??,?
GLOBAL	__Lparam, __Hparam
GLOBAL	__Lrparam, __Hrparam
__Lparam	EQU	__Lrparam
__Hparam	EQU	__Hrparam
	end
