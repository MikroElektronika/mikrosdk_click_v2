\mainpage Main Page
 
 

---
# Power Reset click

Power/Reset Click is equipped with two capacitive touch pads on a single click board™.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/powerreset_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/power-reset-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the PowerReset Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for PowerReset Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void powerreset_cfg_setup ( powerreset_cfg_t *cfg ); 
 
- Initialization function.
> POWERRESET_RETVAL powerreset_init ( powerreset_t *ctx, powerreset_cfg_t *cfg );

#### Example key functions :

- Power Check function.
> powerreset_state_t powerreset_get_pwr( powerreset_t *ctx );
 
- Reset Check function.
> powerreset_state_t powerreset_get_rst( powerreset_t *ctx );

## Examples Description

> Reads PWR and RST pin states and performs a control of the timer counter depending on the pressed button.

**The demo application is composed of two sections :**

### Application Init 

> Initializes device and logger module, prints Initialization done message.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    powerreset_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    powerreset_cfg_setup( &cfg );
    POWERRESET_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    powerreset_init( &powerreset, &cfg );

    Delay_ms( 100 );
    
    log_printf( &logger, "** Touch Button initialization done **\r\n");
    log_printf( &logger, "**************************************\r\n");
}

```

### Application Task

> Checks the states of the PWR and RST pins and logs every change.

```c

void application_task ( void )
{
    new_pwr_state = powerreset_get_pwr( &powerreset );
    new_rst_state = powerreset_get_rst( &powerreset );
    
    if ( new_pwr_state != pwr_state )
    {
        if ( new_pwr_state == POWERRESET_ACTIVE )
        {
            log_printf( &logger, "POWER ON\r\n" );
            Delay_ms( 100 );
        }
        else if ( new_pwr_state == POWERRESET_INACTIVE )
        {
            log_printf( &logger, "POWER OFF\r\n" );
            Delay_ms( 100 );
        }
        pwr_state = new_pwr_state;
    }

    if ( new_rst_state != rst_state )
    {
        if ( new_rst_state == POWERRESET_ACTIVE )
        {
            log_printf( &logger, "Reset occured!\r\n" );
            Delay_ms( 100 );
        }
        rst_state = new_rst_state;
    }
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.PowerReset

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
