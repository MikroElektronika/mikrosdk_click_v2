\mainpage Main Page
 
 

---
# MIC23099 click

MIC23099 click represent single AA/AAA cell step-down/step-up regulator with battery monitoring.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mic23099_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/mic23099-click>)

---


#### Click library 

- **Author**        : Mihajlo Djordjevic
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the Mic23099 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Mic23099 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void mic23099_cfg_setup ( mic23099_cfg_t *cfg ); 
 
- Initialization function.
> MIC23099_RETVAL mic23099_init ( mic23099_t *ctx, mic23099_cfg_t *cfg );

- Click Default Configuration function.
> void mic23099_default_cfg ( mic23099_t *ctx );


#### Example key functions :

- This function executes default configuration for MIC23099 click.
> void mic23099_default_cfg ( mic23099_t *ctx );
 
- This function checks the state of Power Good output pin.
> uint8_t mic23099_check_power_good ( mic23099_t *ctx );

## Examples Description

> 
> This example shows usage of MIC23099 Click as step-down/step-up voltage regulator.
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
    mic23099_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "     Application  Init\r\n" );
    Delay_ms ( 1000 );

    //  Click initialization.

    mic23099_cfg_setup( &cfg );
    MIC23099_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mic23099_init( &mic23099, &cfg );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " ---- MIC23099 Click ---- \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
    
    mic23099_default_cfg( &mic23099 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " -- Initialization done --\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
}
  
```

### Application Task

>
> This example demonstrates the use of MIC23099 Click board by checking 
> the state of power good pin and sends note via UART Terminal 
> if the state is low.
> 

```c

void application_task ( void )
{
    uint8_t new_stat = 0;
    uint8_t old_stat = 1;
    
    new_stat = mic23099_check_power_good( &mic23099 );

    if ( new_stat == 1 && old_stat == 0 )
    {
        old_stat = 1;
    }

    if ( new_stat == 0 && old_stat == 1 )
    {
        log_printf( &logger, " Change  battery  and  reset. \r\n" );
        log_printf( &logger, "------------------------------\r\n" );
        old_stat = 0;
    }
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Mic23099

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
