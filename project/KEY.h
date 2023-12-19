/*
*********************************************************************************************************
*                                   Embedded Systems Building Blocks
*                                Complete and Ready-to-Use Modules in C
*
*                                         Matrix Keyboard Driver
*
*                            (c) Copyright 1999, Jean J. Labrosse, Weston, FL
*                                           All Rights Reserved
*
* Filename   : KEY.H
* Programmer : Jean J. Labrosse
*********************************************************************************************************
*                                            ����� ���� ���
*
* ��Ʈ: �̵� #define ������� ����� ȯ�濡 �µ��� ����Ǿ�� �Ѵ�
*********************************************************************************************************
*/

#ifndef  CFG_H
#define  KEY_BUF_SIZE               10      /* Ű���� ������ ũ��                                      */

#define  KEY_PORT_ROW           0x0312      /* Ű���� ��Ʈ������ �࿡ �ش��ϴ� ��Ʈ�� ��巹��         */
#define  KEY_PORT_COL           0x0311      /* Ű���� ��Ʈ������ ���� �ش��ϴ� ��Ʈ�� ��巹��         */
#define  KEY_PORT_CW            0x0313      /* Ű���� I/O��Ʈ ����� ������ ��巹��                   */

#define  KEY_MAX_ROWS                4      /* Ű������ �ִ� ��(row) ��                                */
#define  KEY_MAX_COLS                4      /* Ű������ �ִ� ��(column) ��                             */

#define  KEY_RPT_DLY                 2      /* �ڵ� �ݺ������ �ٽ� ����Ǳ� ���� ��ĵŸ�� ��          */
#define  KEY_RPT_START_DLY          10      /* �ڵ� �ݺ������ ����Ǳ������ ��ĵŸ�� ��              */

#define  KEY_SCAN_TASK_DLY          40      /* Ű�� ��ĵ�ϴ� �ð� ����                                 */
#define  KEY_SCAN_TASK_PRIO         50      /* Ű���� ��ĳ�� �½�ũ�� �켱����                         */
#define  KEY_SCAN_TASK_STK_SIZE   1024      /* Ű���� ��ĳ�� �½�ũ�� ���� ũ��                        */

//#define  KEY_SHIFT1_MSK           0x80      /* SHIFT1Ű�� ���Է� ��Ʈ�� ��Ʈ7�� ��ġ��                 */  
#define  KEY_SHIFT1_MSK           0x00      /* SHIFT1Ű�� ���Է� ��Ʈ�� ��Ʈ7�� ��ġ��                 */
                                            /*     (0x00�� SHIFT1Ű�� ������ ���Ѵ�)                   */
#define  KEY_SHIFT1_OFFSET          24      /* SHIFT1Ű�� �������� �� ������ ������ ��                 */

//#define  KEY_SHIFT2_MSK           0x80      /* SHIFT2Ű�� ���Է� ��Ʈ�� ��Ʈ6�� ��ġ��                 */ 
#define  KEY_SHIFT2_MSK           0x00      /* SHIFT2Ű�� ���Է� ��Ʈ�� ��Ʈ6�� ��ġ��                 */
                                            /*     (0x00�� SHIFT2Ű�� ������ ���Ѵ�)                   */
#define  KEY_SHIFT2_OFFSET          48      /* SHIFT2Ű�� �������� �� ������ ������ ��                 */

#define  KEY_SHIFT3_MSK           0x00      /* SHIFT3Ű�� ���Է� ��Ʈ�� ��Ʈ5�� ��ġ��                 */
                                            /*     (0x00�� SHIFT3Ű�� ������ ���Ѵ�)                   */
#define  KEY_SHIFT3_OFFSET           0      /* SHIFT3Ű�� �������� �� ������ ������ ��                 */
#endif

#define  KEY_ALL_ROWS             0xFF      /* ��� ���� ���� (��, ��� ���� 0���� ���)               */

/*
*********************************************************************************************************
*                                                �Լ�����
*********************************************************************************************************
*/

void    KeyFlush(void);                /* Ű���� ���۸� Ŭ���� �Ѵ�                                    */
INT8U   KeyGetKey(INT16U to);          /* Ű���� ����̹��κ��� ��ĵ�ڵ带 �о�´�. ������ -1�� ����  */
INT32U  KeyGetKeyDownTime(void);       /* Ű�� ������ �ִ� �ð��� �����Ѵ� (�и���, milliseconds)      */
BOOLEAN KeyHit(void);                  /* Ű�� ������ �ִ� ���� Ȯ��(�������� TRUE, �׷��� ������FALSE)*/
void    KeyInit(void);                 /* Ű���� ����̹��� �ʱ�ȭ                                     */


void    KeyInitPort(void);             /* I/O��Ʈ�� �ʱ�ȭ                                             */
INT8U   KeyGetCol(void);               /* ���� �д´�                                                  */
void    KeySelRow(INT8U row);          /* ���� �����Ѵ�                                                */
