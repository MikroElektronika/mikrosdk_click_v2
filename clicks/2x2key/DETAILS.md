
---
# 2x2 key click

2x2 Key click has a 4 button keypad and allows multiple key presses.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/2x2key_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/2x2-key-click)

---


#### Click library 

- **Author**        : Mihajlo Djordjevic
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the 2x2key Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 2x2key Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c2x2key_cfg_setup ( c2x2key_cfg_t *cfg ); 
 
- Initialization function.
> C2X2KEY_RETVAL c2x2key_init ( c2x2key_t *ctx, c2x2key_cfg_t *cfg );

- Click Default Configuration function.
> void c2x2key_default_cfg ( c2x2key_t *ctx );


#### Example key functions :

- This function gets state of AN pin on 2X2_Key Click board.
> uint8_t c2x2key_t1_state ( c2x2key_t *ctx );
 
- This function gets state of RST pin on 2X2_Key Click board.
> uint8_t c2x2key_t2_state ( c2x2key_t *ctx );

- This function gets state of CS pin on 2X2_Key Click board.
> uint8_t c2x2key_t3_state ( c2x2key_t *ctx );

- This function gets state of PWM pin on 2X2_Key Click board.
> uint8_t c2x2key_t4_state ( c2x2key_t *ctx );

## Examples Description

> 
> This example code demonstrates the usage of 2X2 Key Click board.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Application Init performs Logger and Click initialization.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c2x2key_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_printf( &logger, "-- Application  Init --\r\n" );
    Delay_ms ( 1000 );

    //  Click initialization.

    c2x2key_cfg_setup( &cfg );
    C2X2KEY_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c2x2key_init( &c2x2key, &cfg );
    
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "     2X2 key Click     \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "    System is ready    \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms ( 1000 );
}
  
```

### Application Task

>
> Application Task detects whether any of the keys is pressed,
> and results are being sent to the UART Terminal where you can track changes.
> 

```c

void application_task ( void )
{
   t1_state = c2x2key_t1_state( &c2x2key );
   
   if ( t1_state == 1 && t1_state_old == 0 )
    {
        log_printf( &logger, "-----------------------\r\n" );
        log_printf( &logger, "     Key 1 pressed     \r\n" );
        log_printf( &logger, "-----------------------\r\n" );
        t1_state_old = 1;
    }
    
    if ( t1_state == 0 && t1_state_old == 1 )
    {
        t1_state_old = 0;
    }
    
    t2_state = c2x2key_t2_state( &c2x2key );
   
   if ( t2_state == 1 && t2_state_old == 0 )
    {
        log_printf( &logger, "-----------------------\r\n" );
        log_printf( &logger, "     Key 2 pressed     \r\n" );
        log_printf( &logger, "-----------------------\r\n" );
        t2_state_old = 1;
    }
    
    if ( t2_state == 0 && t2_state_old == 1 )
    {
        t2_state_old = 0;
    }
    
    t3_state = c2x2key_t3_state( &c2x2key );
   
   if ( t3_state == 1 && t3_state_old == 0 )
    {
        log_printf( &logger, "-----------------------\r\n" );
        log_printf( &logger, "     Key 3 pressed     \r\n" );
        log_printf( &logger, "-----------------------\r\n" );
        t3_state_old = 1;
    }
    
    if ( t3_state == 0 && t3_state_old == 1 )
    {
        t3_state_old = 0;
    }
    
    t4_state = c2x2key_t4_state( &c2x2key );
   
   if ( t4_state == 1 && t4_state_old == 0 )
    {
        log_printf( &logger, "-----------------------\r\n" );
        log_printf( &logger, "     Key 4 pressed     \r\n" );
        log_printf( &logger, "-----------------------\r\n" );
        t4_state_old = 1;
    }
    
    if ( t4_state == 0 && t4_state_old == 1 )
    {
        t4_state_old = 0;
    }
} 

``` 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.2x2key

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
