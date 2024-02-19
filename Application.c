/* 
 * File:   Application.c
 * Author: Alielden
 *
 * Created on September 9, 2023, 6:23 PM
 */

#include "Application.h"

Std_ReturnType ret = 0 ;


lcd_4bit_t lcd1 = 
{
  .lcd_rs.port      = GPIO_PORTC ,
  .lcd_rs.pin       = GPIO_PIN0 ,
  .lcd_rs.logic     = GPIO_LOW ,
  .lcd_rs.direction = GPIO_OUTPUT ,
  
  .lcd_en.port      = GPIO_PORTC ,
  .lcd_en.pin       = GPIO_PIN1 ,
  .lcd_en.logic     = GPIO_LOW ,
  .lcd_en.direction = GPIO_OUTPUT ,
  
  .lcd_data[0].port      = GPIO_PORTC ,
  .lcd_data[0].pin       = GPIO_PIN2 ,
  .lcd_data[0].logic     = GPIO_LOW ,
  .lcd_data[0].direction = GPIO_OUTPUT ,
  
  .lcd_data[1].port      = GPIO_PORTC ,
  .lcd_data[1].pin       = GPIO_PIN3 ,
  .lcd_data[1].logic     = GPIO_LOW ,
  .lcd_data[1].direction = GPIO_OUTPUT ,
  
  .lcd_data[2].port      = GPIO_PORTC ,
  .lcd_data[2].pin       = GPIO_PIN4 ,
  .lcd_data[2].logic     = GPIO_LOW ,
  .lcd_data[2].direction = GPIO_OUTPUT ,
  
  .lcd_data[3].port      = GPIO_PORTC ,
  .lcd_data[3].pin       = GPIO_PIN5 ,
  .lcd_data[3].logic     = GPIO_LOW ,
  .lcd_data[3].direction = GPIO_OUTPUT ,
  
  
};

keypad_t keypad1 =
{
  .rows_pins[0].port      = GPIO_PORTD  ,
  .rows_pins[0].pin       = GPIO_PIN0   ,
  .rows_pins[0].logic     = GPIO_LOW    ,
  .rows_pins[0].direction = GPIO_OUTPUT ,
  .rows_pins[1].port      = GPIO_PORTD  ,
  .rows_pins[1].pin       = GPIO_PIN1   ,
  .rows_pins[1].logic     = GPIO_LOW    ,
  .rows_pins[1].direction = GPIO_OUTPUT ,
  .rows_pins[2].port      = GPIO_PORTD  ,
  .rows_pins[2].pin       = GPIO_PIN2   ,
  .rows_pins[2].logic     = GPIO_LOW    ,
  .rows_pins[2].direction = GPIO_OUTPUT ,
  .rows_pins[3].port      = GPIO_PORTD  ,
  .rows_pins[3].pin       = GPIO_PIN3   ,
  .rows_pins[3].logic     = GPIO_LOW    ,
  .rows_pins[3].direction = GPIO_OUTPUT ,
  
  .columns_pins[0].port      = GPIO_PORTD  ,
  .columns_pins[0].pin       = GPIO_PIN4   ,
  .columns_pins[0].logic     = GPIO_LOW    ,
  .columns_pins[0].direction = GPIO_INPUT ,
  .columns_pins[1].port      = GPIO_PORTD  ,
  .columns_pins[1].pin       = GPIO_PIN5   ,
  .columns_pins[1].logic     = GPIO_LOW    ,
  .columns_pins[1].direction = GPIO_INPUT ,
  .columns_pins[2].port      = GPIO_PORTD  ,
  .columns_pins[2].pin       = GPIO_PIN6   ,
  .columns_pins[2].logic     = GPIO_LOW    ,
  .columns_pins[2].direction = GPIO_INPUT ,
  .columns_pins[3].port      = GPIO_PORTD  ,
  .columns_pins[3].pin       = GPIO_PIN7   ,
  .columns_pins[3].logic     = GPIO_LOW    ,
  .columns_pins[3].direction = GPIO_INPUT ,
};

dc_motor_t motor1 =
{
  .dc_motor[0].pin = GPIO_PIN6 ,
  .dc_motor[0].port = GPIO_PORTC ,
  .dc_motor[0].direction = GPIO_OUTPUT ,
  .dc_motor[0].logic = GPIO_LOW ,
  
  .dc_motor[1].pin = GPIO_PIN7 ,
  .dc_motor[1].port = GPIO_PORTC ,
  .dc_motor[1].direction = GPIO_OUTPUT ,
  .dc_motor[1].logic = GPIO_LOW ,    
};


led_t green_led =
{
  .port =  GPIO_PORTA ,
  .pin =   GPIO_PIN0 ,
  .led_status = led_OFF
};

led_t red_led =
{
  .port =  GPIO_PORTA ,
  .pin =   GPIO_PIN1 ,
  .led_status = led_OFF
};



led_t buzzer =
{
  .port =  GPIO_PORTA ,
  .pin =   GPIO_PIN2 ,
  .led_status = led_OFF
};


uint8 function_done = 0 , correct_password = 0 , wrong_flag = 0 ;  
uint32 confirm_value = 0  ;

int main() {
    APPLICATION_INTIALIZE();
    ret = EEPROM_ReadData(0x00 , &correct_password );
    welcome_lcd();
    main_lcd() ;
    
    while(1){
      function_done = 0 ; 
      function_done =  keypad_lcd() ;

      if( function_done == 1 )
      {
          switch(confirm_value )
          {
              case ENTER_PASSWORD :
                 enter_password();
                 __delay_ms(100);
                 confirm_value = 0 ; 
                 check_password();
                  break ;
                 
                 
                  
              case CHANGE_PASSWORD :
                  change_password();
                  __delay_ms(100);
                 confirm_value = 0 ;
                 check_change_password() ;
                  break ;
          }
      }

    }
    
    return (EXIT_SUCCESS);
}



void APPLICATION_INTIALIZE(void){
    Std_ReturnType ret = 0 ;
    ret = lcd_4bit_intialize(&lcd1) ;
    ret = keypad_intialize(&keypad1) ;
    ret = dc_motor_intialize(&motor1) ;
    ret = led_intialize(&green_led);
    ret = led_intialize(&red_led);
    ret = led_intialize(&buzzer);
}


void Motor_move_forward(void)
{
    ret = dc_motor_move_forward(&motor1) ;
}

void Motor_stop(void)
{
    ret = dc_motor_stop(&motor1) ;
}


void green_led_turn_on(void)
{
    ret = led_turn_on(&green_led);
}

void green_led_turn_off(void)
{
    ret = led_turn_off(&green_led);
}

void red_led_turn_on(void)
{
    ret = led_turn_on(&red_led);
}

void red_led_turn_off(void)
{
    ret = led_turn_off(&red_led);
}

void buzzer_turn_on(void)
{
    ret = led_turn_on(&buzzer);
}

void buzzer_turn_off(void)
{
    ret = led_turn_off(&buzzer);
}

uint8 keypad_lcd(void)
{
    uint8 value = 0 , done = 0 , conv = 0 ;
    ret = keypad_get_value(&keypad1 , &value ) ;
    if( (value != 0) && (value != '#') )
    {
        conv = atoi(&value);
        ret = lcd_4bit_send_char_data(&lcd1  , value ) ;
         __delay_ms(100);
         value = 0 ;
         confirm_value = (confirm_value * 10 ) + conv ;
    }
    else if( value == '#')
    {
        ret = lcd_4bit_send_command(&lcd1 , _LCD_CLEAR );
        done = 1 ;
        return done ;        
    }
}

void welcome_lcd(void)
{
    ret = lcd_4bit_send_string_data(&lcd1 , "Welcome");
    ret = lcd_4bit_send_char_data(&lcd1 , '.' ) ;
    __delay_ms(250) ;
    ret = lcd_4bit_send_char_data(&lcd1 , '.' ) ;
    __delay_ms(250) ;
    ret = lcd_4bit_send_char_data(&lcd1 , '.' ) ;
    __delay_ms(250) ;
    ret = lcd_4bit_send_char_data_pos(&lcd1 , 1 , 8 , ' ' );
    ret = lcd_4bit_send_char_data_pos(&lcd1 , 1 , 9 , ' ' );
    ret = lcd_4bit_send_char_data_pos(&lcd1 , 1 , 10 , ' ' );
     __delay_ms(250) ;
     ret = lcd_4bit_send_char_data_pos(&lcd1 , 1 , 8 , '.' ) ;
    __delay_ms(250) ;
     ret = lcd_4bit_send_char_data_pos(&lcd1 , 1 ,9 , '.' ) ;
    __delay_ms(250) ;
     ret = lcd_4bit_send_char_data_pos(&lcd1 , 1 , 10 , '.' ) ;
    __delay_ms(250) ;
    ret = lcd_4bit_send_command(&lcd1 , _LCD_CLEAR );
    
}

void main_lcd(void)
{
    ret = lcd_4bit_send_string_data_pos(&lcd1 , 1 , 1 , "Enter Mode : ");
    ret = lcd_4bit_send_string_data_pos(&lcd1 , 2 , 1 , "1.Enter Password ");
    ret = lcd_4bit_send_string_data_pos(&lcd1 , 3 , 1 , "2.Change Password ");
    ret = lcd_4bit_send_char_data_pos(&lcd1 , 4 , 1 , ' ');
    ret = lcd_4bit_send_command(&lcd1 , _LCD_CURSOR_MOVE_LEFT );
}

void enter_password(void)
{
    ret = lcd_4bit_send_string_data(&lcd1 , "Enter Passward : ") ;
    ret = lcd_4bit_send_char_data_pos(&lcd1 , 3 , 1 , ' ');
    ret = lcd_4bit_send_command(&lcd1 , _LCD_CURSOR_MOVE_LEFT );
}


void check_password(void)
{
            while(1)
                 {
                     function_done =  keypad_lcd() ;
                     __delay_ms(100);
                    if( (function_done == 1) && (confirm_value == correct_password ) )
                    {
                         ret = lcd_4bit_send_string_data(&lcd1 , "Correct Password");
                         Motor_move_forward();
                         green_led_turn_on();
                         __delay_ms(3000);
                         Motor_stop();
                         break ;
                    }
                    else if( (function_done == 1) && (confirm_value != correct_password ) )
                    {
                        wrong_flag++ ;
                        switch(wrong_flag)
                        {
                            case 1 :
                                ret = lcd_4bit_send_string_data(&lcd1 , "Wrong Password"); 
                                ret = lcd_4bit_send_string_data_pos(&lcd1 , 2 , 1 , " Try again(1/3) : ");
                                break;
                            case 2 :
                                ret = lcd_4bit_send_string_data(&lcd1 , "Wrong Password"); 
                                ret = lcd_4bit_send_string_data_pos(&lcd1 , 2 , 1 , " Try again(2/3) : ");
                                break;
                            case 3 :
                                ret = lcd_4bit_send_string_data(&lcd1 , "Wrong Password"); 
                                ret = lcd_4bit_send_string_data_pos(&lcd1 , 2 , 1 , " Try again(3/3) : ");
                                break;    
                        }
                       
                       if( wrong_flag==3 )
                       {
                           red_led_turn_on();
                           buzzer_turn_on();
                       }
                       else
                       {
                           __delay_ms(1000);
                             ret = lcd_4bit_send_command(&lcd1 , _LCD_CLEAR ); 
                            main_lcd() ;
                            confirm_value = 0 ;
                           
                       }
                       break ;
                    }
                 } 
}

void change_password(void)
{
    ret = lcd_4bit_send_string_data(&lcd1 , "Enter old Passward : ") ;
    ret = lcd_4bit_send_char_data_pos(&lcd1 , 3 , 1 , ' ');
    ret = lcd_4bit_send_command(&lcd1 , _LCD_CURSOR_MOVE_LEFT );
}

void check_change_password(void)
{
            while(1)
                 {
                     function_done =  keypad_lcd() ;
                     __delay_ms(100);
                    if( (function_done == 1) && (confirm_value == correct_password ) )
                    {
                        enter_password();
                        confirm_value=0 ;
                        while(1)
                        {
                            function_done =  keypad_lcd() ;
                            if( function_done== 1 )
                            {
                                ret = EEPROM_WriteData(0x00 , confirm_value ) ;
                                __delay_ms(100);
                                ret = lcd_4bit_send_string_data(&lcd1 , "Password Updated "); 
                                break ;
                             }
                            
                        }
                        
                        
                         break ;
                    }
                    else if( (function_done == 1) && (confirm_value != correct_password ) )
                    {
                        wrong_flag++ ;
                        switch(wrong_flag)
                        {
                            case 1 :
                                ret = lcd_4bit_send_string_data(&lcd1 , "Wrong Password"); 
                                ret = lcd_4bit_send_string_data_pos(&lcd1 , 2 , 1 , " Try again(1/3) : ");
                                break;
                            case 2 :
                                ret = lcd_4bit_send_string_data(&lcd1 , "Wrong Password"); 
                                ret = lcd_4bit_send_string_data_pos(&lcd1 , 2 , 1 , " Try again(2/3) : ");
                                break;
                            case 3 :
                                ret = lcd_4bit_send_string_data(&lcd1 , "Wrong Password"); 
                                ret = lcd_4bit_send_string_data_pos(&lcd1 , 2 , 1 , " Try again(3/3) : ");
                                break;    
                        }
                       
                       if( wrong_flag==3 )
                       {
                           red_led_turn_on();
                           buzzer_turn_on();
                       }
                       else
                       {
                           __delay_ms(1000);
                            ret = lcd_4bit_send_command(&lcd1 , _LCD_CLEAR ); 
                            main_lcd() ;
                            confirm_value = 0 ;
                       }
                       break ;
                    }
                 } 
}
