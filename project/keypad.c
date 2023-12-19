//=====================================================
//  Keypad Matrix 인터페이스
// 
//=====================================================

#include <avr/io.h>             
#include <util/delay.h>
#include <stdio.h>

#include "keypad.h" 


#define KEY_OUT PORTE	// keyboard 출력 포트
#define KEY_OUT_DIR DDRE	// keyboard 출력 포트 방향 레지스터 

#define KEY_IN  PIND	// keyboard 입력 포트  
#define KEY_IN_PORT  PORTD	// keyboard 입력 포트       
#define KEY_IN_DIR DDRD	// keyboard 입력 포트 방향 레지스터 

static unsigned char key_scan(void);
static unsigned char last_key = NO_KEY;		// 이전 키값

void KeyInit()
{
       KEY_OUT &= ~0xF0;	// 출력 초기 값으로 0을 출력
       KEY_OUT_DIR |= 0xF0;
	   
       KEY_IN_DIR &= ~0xF0;
		KEY_IN_PORT &= ~0xF0;	//
		
}        

//==============================================
//  키패드의 스캔 코드 값을 리턴한다.
//
//      리턴 값 : 0이 아닐 때 : 스캔 코드 값
//                0일 때      : 입력 값이 없음
//==============================================   
unsigned char KeyInput(void)
{
	unsigned char in, in1;
        
	in = key_scan();	// 키스캔을 하여 값을 읽는다.

	while(1)			
	{
		_delay_ms(10);  _delay_ms(10);	_delay_ms(10);
		in1 = key_scan();	// 한 번 더 읽는다.
		if(in==in1) break;
		in = in1;
	}
       
	if(in == NO_KEY)        	// 눌러진 키가 없음
	{
		last_key =NO_KEY;
		return NO_KEY;
	}                                     
        
	if(last_key == in)		// 같은 키를 계속 누르고 있음 
		return NO_KEY;		// 새로운 키 입력이 없는 것으로 리턴
                        
	last_key = in;			// 키 값을 저장 함.
        
	return in;		// 코드를 반환한다.
}

//-------------------------------------------
// 스캔코드값을 리턴함
//-------------------------------------------
static unsigned char key_scan(void)
{
	unsigned char out, in, mask;
	unsigned char scancode=0;
                
	for(out = 0x10; out ; out <<= 1)
	{
		KEY_OUT = out;   	// 출력 포트에 스캔출력을 낸다.  
		
		_delay_us(10);
		
		in = KEY_IN;  		// 입력된 값의 

		for(mask = 0x10; mask ; mask <<=1)
		{
			if (in & mask)
			{
				return scancode;					
			}			
			scancode ++;
		}		
	}

	return NO_KEY;			// 스캔코드 값 리턴
}

