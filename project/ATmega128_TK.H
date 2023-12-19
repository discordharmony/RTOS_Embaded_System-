/* ---------------------------------------------------------------------------------- */
/*  ATmega128_TK.H     	                                                           	 */
/*  I/O Direction & LCD subroutine									  		 */
/* ---------------------------------------------------------------------------------- */
void MCU_init(void)			/* initialize ATmega128 TK */
{ 
     // -------------------------------------------------------------------------------------------
     // MCU initialize 
     // -------------------------------------------------------------------------------------------
     MCUCR = 0x00;	
   	XMCRA = 0x00; 
   	XMCRB = 0x00; 
   	
   	DDRA	 = 0xFF;			// PORTA Data Direction ( 1:out, 0:in )
   	PORTA = 0x00;             
   						// PORTA.0 (O) : LCD DATA0
     					// PORTA.1 (O) : LCD DATA1
     					// PORTA.2 (O) : LCD DATA2
     					// PORTA.3 (O) : LCD DATA3
     					// PORTA.4 (O) : LCD DATA4
     					// PORTA.5 (O) : LCD DATA5
     					// PORTA.6 (O) : LCD DATA6
     					// PORTA.7 (O) : LCD DATA7 
   	
   	DDRB  = 0x00;  		// PORTB Data Direction ( 1:out, 0:in ) 
     PORTB = 0x00;            
     					// PORTB.0 (I) : Not Used
     					// PORTB.1 (I) : SCK for ISP
     					// PORTB.2 (I) : SW DIP.0
     					// PORTB.3 (I) : SW DIP.1
     					// PORTB.4 (I) : SW DIP.2
     					// PORTB.5 (I) : SW DIP.3
     					// PORTB.6 (I) : SW DIP.4
     					// PORTB.7 (I) : SW DIP.5
     					
     DDRC  = 0xFF;  		// PORTC Data Direction ( 1:out, 0:in ) 
     PORTC = 0x00;            
     					// PORTC.0 (O) : LCD_E
     					// PORTC.1 (O) : LCD_RS
     					// PORTC.2 (O) : LED
     					// PORTC.3 (O) : LED
     					// PORTC.4 (O) : LED
     					// PORTC.5 (O) : LED
     					// PORTC.6 (O) : LED
     					// PORTC.7 (O) : LED
     										     
     DDRD	 = 0x00;			// PORTD Data Direction ( 1:out, 0:in )
   	PORTD = 0x00;            //  										     
     					// PORTD.0 (I) : Not Used
     					// PORTD.1 (I) : Not Used
     					// PORTD.2 (I) : RXD1
     					// PORTD.3 (I) : TXD1
     					// PORTD.4 (I) : KEY_DATA_0
     					// PORTD.5 (I) : KEY_DATA_1
     					// PORTD.6 (I) : KEY_DATA_2
     					// PORTD.7 (I) : KEY_DATA_3
     					
    	DDRE  = 0xF2;  		// PORTE Data Direction ( 1:out, 0:in )  
     PORTE = 0x00;            
     					// PORTE.0 (I) : RXD0
     					// PORTE.1 (O) : TXD0
     					// PORTE.2 (I) : Not Used
     					// PORTE.3 (I) : Not Used
     					// PORTE.4 (O) : KEY_SACN_0
     					// PORTE.5 (O) : KEY_SACN_1
     					// PORTE.6 (O) : KEY_SACN_2
     					// PORTE.7 (O) : KEY_SACN_3

     DDRF  = 0x00;  		// PORTF Data Direction ( 1:out, 0:in )  
     PORTF = 0x00;             
     					// PORTF.0 (I) : ADC0
     					// PORTF.1 (I) : ADC1
     					// PORTF.2 (I) : Not Used
     					// PORTF.3 (I) : Not Used
     					// PORTF.4 (I) : Not Used 
     					// PORTF.5 (I) : Not Used
     					// PORTF.6 (I) : Not Used
     					// PORTF.7 (I) : Not Used
     					
     DDRG  = 0x18;            // PORTG Data Direction ( 1:out, 0:in )   
     PORTG = 0x00;
     					// PORTG.0 (I) : Not Used
     					// PORTG.1 (I) : Not Used 					
     					// PORTG.2 (I) : Not Used
     					// PORTG.3 (O) : TEST PIN 3					     
     					// PORTG.4 (O) : TEST PIN 3
     // -------------------------------------------------------------------------------------------
}

void Delay_us(unsigned char time_us)		/* time delay for us */
{ 
     register unsigned char i;

     for(i = 0; i < time_us; i++) {     // 4 cycle +      
        asm (" PUSH  R0 ");     		// 2 cycle +       
        asm (" POP   R0 ");       		// 2 cycle +
        asm (" PUSH  R0 ");       		// 2 cycle +
        asm (" POP   R0 ");       		// 2 cycle +
        asm (" PUSH  R0 ");       		// 2 cycle +
        asm (" POP   R0 ");	     	// 2 cycle = 16 cycle = 1 us for 16MHz
     }
}

void Delay_ms(unsigned int time_ms)       	/* time delay for ms */
{ 
     register unsigned int i;

     for(i = 0; i < time_ms; i++) {
        Delay_us(250);
        Delay_us(250);
        Delay_us(250);
        Delay_us(250);
     }
}  

// LCD_E와 LCD_RS의 신호핀 할당에 주의
void LCD_command(unsigned char command)		/* write a command(instruction) to text LCD */
{
     PORTC &= ~_BV(1); 			// E = 0, Rs = 0  
     PORTC &= ~_BV(0); 
     PORTA  = command;			// output command
	PORTC |= _BV(1);  			// E = 1
     asm (" PUSH  R0 ");			// delay for about 250 ns
     asm (" POP   R0 ");
     PORTC &= ~_BV(1); 			// E = 0
     Delay_us(50);
}

void LCD_data(unsigned char data)		/* display a character on text LCD */
{
     PORTC &= ~_BV(1); 			// E = 0, Rs = 1 
     PORTC |= _BV(0); 
     PORTA = data;				// output data
	PORTC |= _BV(1); 			// E = 1
     asm (" PUSH  R0 ");			// delay for about 250 ns
     asm (" POP   R0 ");
     PORTC &= ~_BV(1); 			// E = 0
     Delay_us(50);
}


void LCD_string(char command, char *string) /* display a string on LCD */
{
     LCD_command(command);			// start position of string
     while(*string != '\0') {			// display string
        LCD_data(*string);
        string++;
     }
}

void LCD_initialize(void)			/* initialize text LCD module */
{
     PORTC |= _BV(1);				// E = 1, Rs = 1 (dummy write)    
     PORTC |= _BV(0);
     PORTC &= ~_BV(1);				// E = 0, Rs = 1
     PORTC |= _BV(0);
     Delay_ms(2);

     LCD_command(0x38);				// function set(8 bit, 2 line, 5x7 dot)
     LCD_command(0x0C);				// display control(display ON, cursor OFF)
     LCD_command(0x06);				// entry mode set(increment, not shift)
     LCD_command(0x01);				// clear display
     Delay_ms(2);
}

void LCD_1d(unsigned int number)
{
   if(number < 10) {
     LCD_data(number + '0');
   } else {
     LCD_data(' ');
   }
}

void LCD_1d2(float number)
{
	int i, j;
	j = (int)(number * 100. + 0.5);
	i = j / 100;
	LCD_data(i + '0');
	LCD_data('.');
	i = (j % 100) / 10;
	LCD_data(i + '0');
	i = j % 10;
	LCD_data(i + '0');
}
void LCD_s4f(float number) {
    int intPart = (int)number;              // 정수 부분
    int decimalPart = (int)((number - intPart) * 10);  // 소수 부분 (1자리까지)

    if (number < 0) {
        LCD_data('-');  // 음수 기호 출력
        intPart *= -1;  // 정수 부분을 양수로 변환
    } else {
        LCD_data('+');  // 양수 기호 출력
    }

    LCD_2d(intPart);  // 정수 부분 출력
    LCD_data('.');    // 소수점 출력
    LCD_data(decimalPart + '0');  // 소수 부분 출력 (1자리)
}
void LCD_2d(unsigned int number)
{
     unsigned int i;
     i = number / 10;
     if(i == 0) LCD_data(' ');
     else LCD_data(i + '0');
      
     i = number % 10;
     LCD_data(i + '0');
} 

void LCD_2d2(float number) {
  int whole_part, decimal_part;
  
  // 정수 부분 계산
  whole_part = (int)number;
  
  // 소수점 이하 부분 계산 (100을 곱한 후 반올림)
  decimal_part = (int)(number * 100.0f + 0.5f);
  
  // 정수 부분 출력
  LCD_2d(whole_part);
  
  // 소수점 출력
  LCD_data('.');
  
  // 소수점 첫째 자리 계산 및 출력
  if (decimal_part >= 10) {
    LCD_data(decimal_part / 10 + '0');
  } else {
    LCD_data('0');
  }
  
  // 소수점 둘째 자리 계산 및 출력
  decimal_part %= 10;
  LCD_data(decimal_part + '0');
}

void LCD_2hex(unsigned int number)
{
     unsigned int i;
     
	i = (number >> 4) & 0x0F;
     if(i <= 9) LCD_data(i + '0');
     else       LCD_data(i - 10 + 'A');
     
     i = number & 0x0F;
     if(i <= 9) LCD_data(i + '0');
     else       LCD_data(i - 10 + 'A');
} 

void LCD_2d1(float number)			/* display XX.X number on LCD */
{ 
     int i;

 //    number = fabs(number) + 0.05;
     i = (int)(number/10.);
     LCD_data(i + '0');

     i = (int)(number - i * 10);
     LCD_data(i + '0');

     LCD_data('.');

     i = (int)((number - (int)number) * 10.);
     LCD_data(i + '0');
}   

void LCD_3d(unsigned int number)
{
     unsigned int i,flag;
     flag = 0;
     i = number / 100;
     if(i == 0) LCD_data(' ');
     else {   LCD_data(i + '0');
              flag = 1;
          }
      
     number = number % 100;
     i = number / 10; 
     if((i == 0) && (flag == 0)) LCD_data(' ');
     else {   LCD_data(i + '0');
              flag = 1;
          }
     
     i = number % 10;
     LCD_data(i + '0');
}  

void LCD_4d(unsigned int number)
{
     unsigned int i,flag;
     flag = 0;
     i = number / 1000;
     if(i == 0) LCD_data(' ');
     else {   LCD_data(i + '0');
              flag = 1;
          }
      
     number = number % 1000;
     i = number / 100; 
     if((i == 0) && (flag == 0)) LCD_data(' ');
     else {   LCD_data(i + '0');
              flag = 1;
          }
     
     number = number % 100;
     i = number / 10;
     if((i == 0) && (flag == 0)) LCD_data(' ');
     else LCD_data(i + '0');
     
     i = number % 10;
     LCD_data(i + '0');
}    

void LCD_s4d(int number)
{
     unsigned int i, flag;
     flag = 0;      
     
     if(number < 0) {
     	number = number * (-1);
     	LCD_data('-');
     } else {
     	if(number == 0) LCD_data(' ');
     	else            LCD_data('+');
     }
     
     i = number / 1000;
     if(i == 0) LCD_data(' ');
     else {   LCD_data(i + '0');
              flag = 1;
          }
      
     number = number % 1000;
     i = number / 100; 
     if((i == 0) && (flag == 0)) LCD_data(' ');
     else {   LCD_data(i + '0');
              flag = 1;
          }
     
     number = number % 100;
     i = number / 10;
     if((i == 0) && (flag == 0)) LCD_data(' ');
     else LCD_data(i + '0');
     
     i = number % 10;
     LCD_data(i + '0');  
}  
   
void LCD_4f(float number) {
    int intPart = (int)number;              // 정수 부분
    int decimalPart = (int)((number - intPart) * 10);  // 소수 부분 (1자리까지)

    LCD_2d(intPart);  // 정수 부분 출력
    LCD_data('.');    // 소수점 출력
    LCD_data(decimalPart + '0');  // 소수 부분 출력 (1자리)
}
void LCD_4d1(float number) 	/* xxxx.x */
{
     unsigned int i,j,flag;  
     flag = 0;
     
     j = (int)(number*10. + 0.5);
     i = j/10000; 
     if(i == 0) LCD_data(' ');					/* 10^3 */
     else {   LCD_data(i + '0');     
              flag = 1;
          }
     
     j = j % 10000;				
     i = j / 1000;                       			/* 10^2 */
     if((i == 0) && (flag == 0)) LCD_data(' ');
     else {   LCD_data(i + '0');
              flag = 1;
          }       
     
     j = j % 1000;				
     i = j / 100;                       			/* 10^1 */
     if((i == 0) && (flag == 0)) LCD_data(' ');
     else {   LCD_data(i + '0');
              flag = 1;
          }
     
     j = j % 100;				
     i = j / 10;                       				/* 10^0 */
     LCD_data(i + '0');

     LCD_data('.');     
     
     i = j % 10;								/* 10^-1 */
     LCD_data(i + '0');
}   


void LCD_4hex(unsigned int number)
{
     unsigned int i;
     
     i = number >>12;
     if(i <= 9) LCD_data(i + '0');
     else       LCD_data(i - 10 + 'A');
     
     i = (number >> 8) & 0x000F;
     if(i <= 9) LCD_data(i + '0');
     else       LCD_data(i - 10 + 'A');
     
     i = (number >> 4) & 0x000F;
     if(i <= 9) LCD_data(i + '0');
     else       LCD_data(i - 10 + 'A');
     
     i = number & 0x000F;
     if(i <= 9) LCD_data(i + '0');
     else       LCD_data(i - 10 + 'A');
}  



void LCD_5d(unsigned long number)
{
  unsigned int i, flag;
  flag = 0;

  i = number / 1000000; /* 10^5 */
  if (i == 0) {
    LCD_data(' ');
  } else {
    LCD_data(i + '0');
    flag = 1;
  }

  number = number % 1000000; /* 10^4 */
  i = number / 100000;
  if ((i == 0) && (flag == 0)) {
    LCD_data(' ');
  } else {
    LCD_data(i + '0');
    flag = 1;
  }

  number = number % 100000; /* 10^3 */
  i = number / 10000;
  if ((i == 0) && (flag == 0)) {
    LCD_data(' ');
  } else {
    LCD_data(i + '0');
    flag = 1;
  }

  number = number % 10000; /* 10^2 */
  i = number / 1000;
  if ((i == 0) && (flag == 0)) {
    LCD_data(' ');
  } else {
    LCD_data(i + '0');
    flag = 1;
  }

  number = number % 1000; /* 10^1 */
  i = number / 100;
  if ((i == 0) && (flag == 0)) {
    LCD_data(' ');
  } else {
    LCD_data(i + '0');
    flag = 1;
  }

  i = number % 100; /* 10^0 */
  LCD_data(i + '0');
}


void LCD_6d(uint16_t number)
{
    uint8_t i, flag;
    flag = 0;
    
    i = number / 10000;  // 10^4
    if (i == 0)
        LCD_data(' ');
    else
    {
        LCD_data(i + '0');
        flag = 1;
    }

    number = number % 10000; // 10^4
    i = number / 1000;       // 10^3
    if ((i == 0) && (flag == 0))
        LCD_data(' ');
    else
    {
        LCD_data(i + '0');
        flag = 1;
    }

    number = number % 1000;  // 10^3
    i = number / 100;        // 10^2
    if ((i == 0) && (flag == 0))
        LCD_data(' ');
    else
    {
        LCD_data(i + '0');
        flag = 1;
    }

    number = number % 100;   // 10^2
    i = number / 10;         // 10^1
    if ((i == 0) && (flag == 0))
        LCD_data(' ');
    else
    {
        LCD_data(i + '0');
        flag = 1;
    }

    i = number % 10;  // 10^0
    LCD_data(i + '0');
}

void LCD_7d(unsigned long number) {
    unsigned int i, flag;
    flag = 0;

    i = number / 1000000; /* 10^6 */
    if (i == 0) {
        LCD_data(' ');
    } else {
        LCD_data(i + '0');
        flag = 1;
    }

    number = number % 1000000; /* 10^5 */
    i = number / 100000;
    if ((i == 0) && (flag == 0)) {
        LCD_data(' ');
    } else {
        LCD_data(i + '0');
        flag = 1;
    }

    number = number % 100000; /* 10^4 */
    i = number / 10000;
    if ((i == 0) && (flag == 0)) {
        LCD_data(' ');
    } else {
        LCD_data(i + '0');
        flag = 1;
    }

    number = number % 10000; /* 10^3 */
    i = number / 1000;
    if ((i == 0) && (flag == 0)) {
        LCD_data(' ');
    } else {
        LCD_data(i + '0');
        flag = 1;
    }

    number = number % 1000; /* 10^2 */
    i = number / 100;
    if ((i == 0) && (flag == 0)) {
        LCD_data(' ');
    } else {
        LCD_data(i + '0');
        flag = 1;
    }

    i = number % 100; /* 10^1 */
    LCD_data(i + '0');

    i = number % 10; /* 10^0 */
    LCD_data(i + '0');
}
void LCD_4f2(float number) {
    int intPart = (int)number;              // Integer part
    int decimalPart = (int)((number - intPart) * 100.0f + 0.5f);  // Decimal part (2 decimal places)

    LCD_2d(intPart);  // Display integer part
    LCD_data('.');    // Display decimal point

    // Display decimal part (2 digits)
    if (decimalPart < 10) {
        LCD_data('0');
    }
    LCD_2d(decimalPart);
}
void LCD_s4f2(float number) {
    int intPart = (int)number;              // 정수 부분
    int decimalPart = (int)((number - intPart) * 100.0f + 0.5f);  // 소수 부분 (2자리까지)

    if (number < 0) {
        LCD_data('-');  // 음수 기호 출력
        intPart *= -1;  // 정수 부분을 양수로 변환
    } else {
        LCD_data('+');  // 양수 기호 출력
    }

    LCD_2d(intPart);  // 정수 부분 출력
    LCD_data('.');    // 소수점 출력

    // 소수 부분 계산 및 출력 (2자리)
    if (decimalPart < 10) {
        LCD_data('0');
    }
    LCD_2d(decimalPart);
}
