
---
# 4x4 Key click

4x4 Key click carries a 16 button keypad. The design of the board — inputs are read by a pair of connected 8-bit parallel-in serial-out shift registers — allows for multiple key presses at the same time.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/4x4key_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/4x4-key-click)

---


#### Click library 

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the 4x4Key Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 4x4Key Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c4x4key_cfg_setup ( c4x4key_cfg_t *cfg ); 
 
- Initialization function.
> C4X4KEY_RETVAL c4x4key_init ( c4x4key_t *ctx, c4x4key_cfg_t *cfg );

- Click Default Configuration function.
> void c4x4key_default_cfg ( c4x4key_t *ctx );


#### Example key functions :

- Get 16-bit data function.
> uint16_t c4x4key_get_data ( c4x4key_t *ctx );
 
- Get position pressed button function.
> uint8_t c4x4key_get_btn_position ( c4x4key_t *ctx );

## Examples Description

>
> This is a example which demonstrates the use of 4x4 Key Click board. 
> Detects and logs whether any of the buttons is pressed.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Configuring clicks and log objects.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c4x4key_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_printf( &logger, "- Application Init -\r\n" );
    log_printf( &logger, "--------------------\r\n" );

    //  Click initialization.

    c4x4key_cfg_setup( &cfg );
    C4X4KEY_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c4x4key_init( &c4x4key, &cfg );
    
    btn_data_old = 0;
    
    log_printf( &logger, "   4x4 Key Click\r\n" );
    log_printf( &logger, "--------------------\r\n" );
    log_printf( &logger, "  Press any button\r\n" );
    log_printf( &logger, "--------------------\r\n" );
}
  
```

### Application Task

>
> This is a example which demonstrates the use of 4x4 Key Click board.
> Detects and logs whether any of the buttons is pressed.
> Results are being sent to the Usart Terminal
> where you can track their changes.
> All data logs on usb uart when the button is triggered.
> 

```c

void application_task ( void )
{
    uint16_t btn_data;
    
    btn_data = c4x4key_get_data( &c4x4key );

    if ( btn_data_old != btn_data )
    {
        if ( btn_data == C4X4KEY_BUTTON_0 )
        {
            log_printf( &logger, "         0\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_1 )
        {
            log_printf( &logger, "         1\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_2 )
        {
            log_printf( &logger, "         2\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_3 )
        {
            log_printf( &logger, "         3\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_4 )
        {
            log_printf( &logger, "         4\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_5 )
        {
            log_printf( &logger, "         5\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_6 )
        {
            log_printf( &logger, "         6\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_7 )
        {
            log_printf( &logger, "         7\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_8 )
        {
            log_printf( &logger, "         8\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_9 )
        {
            log_printf( &logger, "         9\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_A )
        {
            log_printf( &logger, "         A\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_B )
        {
            log_printf( &logger, "         B\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_C )
        {
            log_printf( &logger, "         C\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_D )
        {
            log_printf( &logger, "         D\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_STAR )
        {
            log_printf( &logger, "         *\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_HASH )
        {
            log_printf( &logger, "         #\r\n" );
        }

        btn_data_old = btn_data;
    }
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.4x4Key

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
