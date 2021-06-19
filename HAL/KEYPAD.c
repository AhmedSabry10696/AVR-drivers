/**
 * @file Keypad.c
 * @author Ahmed Sabry (ahmed.sabry10696@gmail.com)
 * @brief Keypad driver implementation
 * @version 0.1
 * @date 17-06-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Keypad.h"

static u8 KeysArray[ROW][COL] ={{'7','8','9','A'},
                                {'4','5','6','B'},
                                {'1','2','3','E'},
                                {'C','0','=','F'}};

u8 KEYPAD_GeyKey(void)
{
    u8 key = NO_KEY;
    DIO_WritePin(FIRST_OUTPUT,HIGH);
    DIO_WritePin(FIRST_OUTPUT+1,HIGH);
    DIO_WritePin(FIRST_OUTPUT+2,HIGH);
    DIO_WritePin(FIRST_OUTPUT+3,HIGH);
    
    /* loop for rows */
    for (u8 r = 0; r < ROW; r++)
    {
        DIO_WritePin(FIRST_OUTPUT+r,LOW);

        /* loop for cols */
        for (u8 c = 0; c < COL; c++)
        {
            if(LOW == DIO_ReadPin(FIRST_INPUT+c))
            {
                key = KeysArray[r][c];

                /* wait till the user let the button */
                while(LOW == DIO_ReadPin(FIRST_INPUT+c));
            }
        }
        DIO_WritePin(FIRST_OUTPUT+r,HIGH);
    }
    
    /* if no key pressed */
    return key;
}