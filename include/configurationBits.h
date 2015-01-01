#ifndef CONFIGURATIONBITS_H
#define CONFIGURATIONBITS_H

/*
 * PLLCFG =	4X PLL Enable
 * OFF	Oscillator used directly
 * ON	Oscillator multiplied by 4
 */
#pragma config PLLCFG = ON

/*
 * PRICLKEN =	Primary clock enable bit
 * OFF	Primary clock can be disabled by software
 * ON	Primary clock enabled
 */
#pragma config PRICLKEN = OFF

/*
 * FCMEN =	Fail-Safe Clock Monitor Enable bit
 * OFF	Fail-Safe Clock Monitor disabled
 * ON	Fail-Safe Clock Monitor enabled
 */
#pragma config FCMEN = ON

/*
 * IESO =	Internal/External Oscillator Switchover bit
 * OFF	Oscillator Switchover mode disabled
 * ON	Oscillator Switchover mode enabled
 */
#pragma config IESO = OFF

/*
 * FOSC =	Oscillator Selection bits
 * ECLP	EC oscillator, CLKOUT function on OSC2 (low power, <500 kHz)
 * RC	External RC oscillator, CLKOUT function on OSC2
 * ECMPIO6	EC oscillator (medium power, 500 kHz-16 MHz)
 * ECHP	EC oscillator, CLKOUT function on OSC2 (high power, >16 MHz)
 * HSMP	HS oscillator (medium power 4-16 MHz)
 * INTIO67	Internal oscillator block
 * LP	LP oscillator
 * ECMP	EC oscillator, CLKOUT function on OSC2 (medium power, 500 kHz-16 MHz)
 * INTIO7	Internal oscillator block, CLKOUT function on OSC2
 * ECHPIO6	EC oscillator (high power, >16 MHz)
 * XT	XT oscillator
 * ECLPIO6	EC oscillator (low power, <500 kHz)
 * RCIO6	External RC oscillator
 * HSHP	HS oscillator (high power > 16 MHz)
 */
#pragma config FOSC = INTIO67

/*
 * BOREN =	Brown-out Reset Enable bits
 * NOSLP	Brown-out Reset enabled in hardware only and disabled in Sleep mode (SBOREN is disabled)
 * ON	Brown-out Reset enabled and controlled by software (SBOREN is enabled)
 * OFF	Brown-out Reset disabled in hardware and software
 * SBORDIS	Brown-out Reset enabled in hardware only (SBOREN is disabled)
 */
#pragma config BOREN = ON

/*
 * BORV =	Brown Out Reset Voltage bits
 * 220	VBOR set to 2.20 V nominal
 * 285	VBOR set to 2.85 V nominal
 * 250	VBOR set to 2.50 V nominal
 * 190	VBOR set to 1.90 V nominal
 */
#pragma config BORV = 190

/*
 * PWRTEN =	Power-up Timer Enable bit
 * OFF	Power up timer disabled
 * ON	Power up timer enabled
 */
#pragma config PWRTEN = ON

/*
 * WDTPS =	Watchdog Timer Postscale Select bits
 * 16384	1:16384
 * 128	1:128
 * 4	1:4
 * 4096	1:4096
 * 2048	1:2048
 * 1024	1:1024
 * 256	1:256
 * 32	1:32
 * 32768	1:32768
 * 16	1:16
 * 8	1:8
 * 1	1:1
 * 8192	1:8192
 * 512	1:512
 * 2	1:2
 * 64	1:64
 */
#pragma config WDTPS = 16384

/*
 * WDTEN =	Watchdog Timer Enable bits
 * SWON	WDT is controlled by SWDTEN bit of the WDTCON register
 * NOSLP	WDT is disabled in sleep, otherwise enabled. SWDTEN bit has no effect
 * ON	WDT is always enabled. SWDTEN bit has no effect
 * OFF	Watch dog timer is always disabled. SWDTEN has no effect.
 */
#pragma config WDTEN = SWON

/*
 * CCP2MX =	CCP2 MUX bit
 * PORTC1	CCP2 input/output is multiplexed with RC1
 * PORTB3	CCP2 input/output is multiplexed with RB3
 */
#pragma config CCP2MX = PORTC1

/*
 * CCP3MX =	P3A/CCP3 Mux bit
 * PORTB5	P3A/CCP3 input/output is multiplexed with RB5
 * PORTC6	P3A/CCP3 input/output is mulitplexed with RC6
 */
#pragma config CCP3MX = PORTB5

/*
 * T3CMX =	Timer3 Clock input mux bit
 * PORTC0	T3CKI is on RC0
 * PORTB5	T3CKI is on RB5
 */
#pragma config T3CMX = PORTC0

/*
 * HFOFST =	HFINTOSC Fast Start-up
 * ON	HFINTOSC output and ready status are not delayed by the oscillator stable status
 * OFF	HFINTOSC output and ready status are delayed by the oscillator stable status
 */
#pragma config HFOFST = OFF

/*
 * PBADEN =	PORTB A/D Enable bit
 * ON	PORTB<5:0> pins are configured as analog input channels on Reset
 * OFF	PORTB<5:0> pins are configured as digital I/O on Reset
 */
#pragma config PBADEN = ON

/*
 * MCLRE =	MCLR Pin Enable bit
 * EXTMCLR	MCLR pin enabled, RE3 input pin disabled
 * INTMCLR	RE3 input pin enabled; MCLR disabled
 */
#pragma config MCLRE = EXTMCLR

/*
 * P2BMX =	ECCP2 B output mux bit
 * PORTB5	P2B is on RB5
 * PORTC0	P2B is on RC0
 */
#pragma config P2BMX = PORTB5

/*
 * STVREN =	Stack Full/Underflow Reset Enable bit
 * ON	Stack full/underflow will cause Reset
 * OFF	Stack full/underflow will not cause Reset
 */
#pragma config STVREN = ON

/*
 * DEBUG =	Background Debug
 * OFF	Disabled
 * ON	Enabled
 */
#pragma config DEBUG = OFF

/*
 * LVP =	Single-Supply ICSP Enable bit
 * ON	Single-Supply ICSP enabled if MCLRE is also 1
 * OFF	Single-Supply ICSP disabled
 */
#pragma config LVP = ON

/*
 * XINST =	Extended Instruction Set Enable bit
 * ON	Instruction set extension and Indexed Addressing mode enabled
 * OFF	Instruction set extension and Indexed Addressing mode disabled (Legacy mode)
 */
#pragma config XINST = OFF

/*
 * CP0 =	Code Protection Block 0
 * OFF	Block 0 (000800-003FFFh) not code-protected
 * ON	Block 0 (000800-003FFFh) code-protected
 */
#pragma config CP0 = OFF

/*
 * CP1 =	Code Protection Block 1
 * OFF	Block 1 (004000-007FFFh) not code-protected
 * ON	Block 1 (004000-007FFFh) code-protected
 */
#pragma config CP1 = OFF

/*
 * CP2 =	Code Protection Block 2
 * OFF	Block 2 (008000-00BFFFh) not code-protected
 * ON	Block 2 (008000-00BFFFh) code-protected
 */
#pragma config CP1 = OFF

/*
 * CP3 =	Code Protection Block 3
 * OFF	Block 3 (00C000-00FFFFh) not code-protected
 * ON	Block 3 (00C000-00FFFFh) code-protected
 */
#pragma config CP3 = OFF

/*
 * CPB =	Boot Block Code Protection bit
 * OFF	Boot block (000000-0007FFh) not code-protected
 * ON	Boot block (000000-0007FFh) code-protected
 */
#pragma config CPB = OFF

/*
 * CPD =	Data EEPROM Code Protection bit
 * OFF	Data EEPROM not code-protected
 * ON	Data EEPROM code-protected
 */
#pragma config CPD = OFF

/*
 * WRT0 =	Write Protection Block 0
 * OFF	Block 0 (000800-003FFFh) not write-protected
 * ON	Block 0 (000800-003FFFh) write-protected
 */
#pragma config WRT0 = OFF

/*
 * WRT1 =	Write Protection Block 1
 * OFF	Block 1 (004000-007FFFh) not write-protected
 * ON	Block 1 (004000-007FFFh) write-protected
 */
#pragma config WRT1 = OFF

/*
 * WRT2 =	Write Protection Block 2
 * OFF	Block 2 (008000-00BFFFh) not write-protected
 * ON	Block 2 (008000-00BFFFh) write-protected
 */
#pragma config WRT2 = OFF

/*
 * WRT3 =	Write Protection Block 3
 * OFF	Block 3 (00C000-00FFFFh) not write-protected
 * ON	Block 3 (00C000-00FFFFh) write-protected
 */
#pragma config WRT3 = OFF

/*
 * WRTB =	Boot Block Write Protection bit
 * OFF	Boot Block (000000-0007FFh) not write-protected
 * ON	Boot Block (000000-0007FFh) write-protected
 */
#pragma config WRTB = OFF

/*
 * WRTC =	Configuration Register Write Protection bit
 * OFF	Configuration registers (300000-3000FFh) not write-protected
 * ON	Configuration registers (300000-3000FFh) write-protected
 */
#pragma config WRTC = OFF

/*
 * WRTD =	Data EEPROM Write Protection bit
 * OFF	Data EEPROM not write-protected
 * ON	Data EEPROM write-protected
 */
#pragma config WRTD = OFF

/*
 * EBTR0 =	Table Read Protection Block 0
 * OFF	Block 0 (000800-003FFFh) not protected from table reads executed in other blocks
 * ON	Block 0 (000800-003FFFh) protected from table reads executed in other blocks
 */
#pragma config EBTR0 = OFF

/*
 * EBTR1 =	Table Read Protection Block 1
 * OFF	Block 1 (004000-007FFFh) not protected from table reads executed in other blocks
 * ON	Block 1 (004000-007FFFh) protected from table reads executed in other blocks
 */
#pragma config EBTR1 = OFF

/*
 * EBTR2 =	Table Read Protection Block 2
 * OFF	Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks
 * ON	Block 2 (008000-00BFFFh) protected from table reads executed in other blocks
 */
#pragma config EBTR2 = OFF

/*
 * EBTR3 =	Table Read Protection Block 3
 * OFF	Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks
 * ON	Block 3 (00C000-00FFFFh) protected from table reads executed in other blocks
 */
#pragma config EBTR3 = OFF

/*
 * EBTRB =	Boot Block Table Read Protection bit
 * OFF	Boot Block (000000-0007FFh) not protected from table reads executed in other blocks
 * ON	Boot Block (000000-0007FFh) protected from table reads executed in other blocks
 */
#pragma config EBTRB = OFF

#endif
