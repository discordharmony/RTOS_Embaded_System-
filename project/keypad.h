#ifndef __KEYPAD_H__
#define __KEYPAD_H__

// Ű�е� ����ġ �ڵ� ��
#define SW0     0    // 0-��° ��
#define SW1     1
#define SW2     2
#define SW3     3
#define SW4     4    // 1-��° ��
#define SW5     5
#define SW6     6
#define SW7     7
#define SW8     8    // 2-��° ��
#define SW9     9
#define SW10    10
#define SW11    11
#define SW12    12    // 3-��° ��
#define SW13    13
#define SW14    14
#define SW15    15

#define NO_KEY	 0xFF
                   
//
// �Լ� ����
//                                    
void KeyInit(void);
unsigned char KeyInput(void);
#endif

