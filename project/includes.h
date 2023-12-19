/*
*********************************************************************************************************
*                                               uC/OS-II
*                                        The Real-Time Kernel
*
*                                          AVR Specific code
*
* File         : INCLUDES.H
* By           : Ole Saether
* Port Version : V1.01
*
* Modifications by Julius Luukko 07-21-2003 (Julius.Luukko@lut.fi) to get this compiled with 
* uC/OS-II 2.52 and 2.70.
*
*********************************************************************************************************
*/

#ifndef	 INCLUDES_H
#define  INCLUDES_H

#include <string.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/signal.h>
#include <avr/interrupt.h>

#include  "os_cpu.h" 
#include  "os_cfg.h" 
#include  ".\source\ucos_ii.h"
#include  "KEY.h"

/* ISR support macros */
#include "avr_isr.h"


#define  COLOR_BLACK     0                       /* VT102 Color Codes                                  */
#define  COLOR_RED       1
#define  COLOR_GREEN     2
#define  COLOR_BROWN     3
#define  COLOR_BLUE      4
#define  COLOR_MAGENTA   5
#define  COLOR_CYAN      6
#define  COLOR_WHITE     7

#endif
