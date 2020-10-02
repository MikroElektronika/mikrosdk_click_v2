\mainpage Main Page
 
 

---
# MIC24045 click

MIC24045 click carries MIC24045 I2C-programmable, high-efficiency, wide input range, 5A synchronous step-down regulator from Microchip.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mic24045_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/mic24045-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Mic24045 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Mic24045 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void mic24045_cfg_setup ( mic24045_cfg_t *cfg ); 
 
- Initialization function.
> MIC24045_RETVAL mic24045_init ( mic24045_t *ctx, mic24045_cfg_t *cfg );

- Click Default Configuration function.
> void mic24045_default_cfg ( mic24045_t *ctx );


#### Example key functions :

- Get status function.
> uint8_t mic24045_get_status ( mic24045_t *ctx );
 
- Get voltage.
> float mic24045_get_vout ( mic24045_t *ctx );

- Set voltage.
> void mic24045_set_vout ( mic24045_t *ctx, float v_out );

## Examples Description

> Initializes GPIO, I2C and LOG structures
> sets RST pin as output and INT pin as input and start write log.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables - I2C, also write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    mic24045_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_printf( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    mic24045_cfg_setup( &cfg );
    MIC24045_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mic24045_init( &mic24045, &cfg );
    mic24045_default_cfg ( &mic24045 );
    
    log_printf( &logger, "------------------------\r\n" );
    log_printf( &logger, "     MIC24045 Click     \r\n" );
    log_printf( &logger, "------------------------\r\n" );
}
  
```

### Application Task

> This is a example which demonstrates the use of MIC24045 Click board.
> System will slowly decrement vOut in 0.25 V steps.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on usb uart changes for every 3 sec.

```c

void application_task ( void )
{
    //  Task implementation.

    for ( cnt = 21; cnt > 2; cnt-- )
    {
        v_out = cnt * 0.25;
        
        mic24045_set_vout( &mic24045, v_out );
        mic24045_enable ( &mic24045 );
        current_voltage = mic24045_get_vout( &mic24045 );
    
        log_printf( &logger, " Current voltage: %.2f V\r\n", current_voltage );
        log_printf( &logger, "------------------------\r\n" );
        Delay_ms( 1000 );
        mic24045_disable ( &mic24045 );
        Delay_ms( 1000 );
    }
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Mic24045

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
