//=====================================================
//  Keypad Matrix �������̽�
// 
//=====================================================

#include <avr/io.h>             
#include <util/delay.h>
#include <stdio.h>

#include "keypad.h" 


#define KEY_OUT PORTE	// keyboard ��� ��Ʈ
#define KEY_OUT_DIR DDRE	// keyboard ��� ��Ʈ ���� �������� 

#define KEY_IN  PIND	// keyboard �Է� ��Ʈ  
#define KEY_IN_PORT  PORTD	// keyboard �Է� ��Ʈ       
#define KEY_IN_DIR DDRD	// keyboard �Է� ��Ʈ ���� �������� 

static unsigned char key_scan(void);
static unsigned char last_key = NO_KEY;		// ���� Ű��

void KeyInit()
{
       KEY_OUT &= ~0xF0;	// ��� �ʱ� ������ 0�� ���
       KEY_OUT_DIR |= 0xF0;
	   
       KEY_IN_DIR &= ~0xF0;
		KEY_IN_PORT &= ~0xF0;	//
		
}        

//==============================================
//  Ű�е��� ��ĵ �ڵ� ���� �����Ѵ�.
//
//      ���� �� : 0�� �ƴ� �� : ��ĵ �ڵ� ��
//                0�� ��      : �Է� ���� ����
//==============================================   
unsigned char KeyInput(void)
{
	unsigned char in, in1;
        
	in = key_scan();	// Ű��ĵ�� �Ͽ� ���� �д´�.

	while(1)			
	{
		_delay_ms(10);  _delay_ms(10);	_delay_ms(10);
		in1 = key_scan();	// �� �� �� �д´�.
		if(in==in1) break;
		in = in1;
	}
       
	if(in == NO_KEY)        	// ������ Ű�� ����
	{
		last_key =NO_KEY;
		return NO_KEY;
	}                                     
        
	if(last_key == in)		// ���� Ű�� ��� ������ ���� 
		return NO_KEY;		// ���ο� Ű �Է��� ���� ������ ����
                        
	last_key = in;			// Ű ���� ���� ��.
        
	return in;		// �ڵ带 ��ȯ�Ѵ�.
}

//-------------------------------------------
// ��ĵ�ڵ尪�� ������
//-------------------------------------------
static unsigned char key_scan(void)
{
	unsigned char out, in, mask;
	unsigned char scancode=0;
                
	for(out = 0x10; out ; out <<= 1)
	{
		KEY_OUT = out;   	// ��� ��Ʈ�� ��ĵ����� ����.  
		
		_delay_us(10);
		
		in = KEY_IN;  		// �Էµ� ���� 

		for(mask = 0x10; mask ; mask <<=1)
		{
			if (in & mask)
			{
				return scancode;					
			}			
			scancode ++;
		}		
	}

	return NO_KEY;			// ��ĵ�ڵ� �� ����
}

