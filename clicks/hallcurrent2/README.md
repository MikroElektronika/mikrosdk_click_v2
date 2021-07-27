\mainpage Main Page
 
 

---
# Hall Current 2 click

Hall current 2 click is a very accurate current measurement Click board™, which relies on the Hall effect.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hallcurrent2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/hall-current-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the HallCurrent2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for HallCurrent2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void hallcurrent2_cfg_setup ( hallcurrent2_cfg_t *cfg ); 
 
- Initialization function.
> HALLCURRENT2_RETVAL hallcurrent2_init ( hallcurrent2_t *ctx, hallcurrent2_cfg_t *cfg );

- Click Default Configuration function.
> void hallcurrent2_default_cfg ( hallcurrent2_t *ctx );


#### Example key functions :

- This function reads data from the desired register.
> void hallcurrent2_generic_read ( hallcurrent2_t *ctx );
 
- This function changes reset chip states to reset the chip.
> void hallcurrent2_reset( hallcurrent2_t *ctx );

- Reads current's value in mV.
> int16_t hallcurrent2_get_current( hallcurrent2_t *ctx );

## Examples Description

> This application very accurately measures current using Hall effect.

**The demo application is composed of two sections :**

### Application Init 

> Initializes Driver init and reset chip

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    hallcurrent2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    hallcurrent2_cfg_setup( &cfg );
    HALLCURRENT2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hallcurrent2_init( &hallcurrent2, &cfg );

    hallcurrent2_reset( &hallcurrent2 );
}
  
```

### Application Task

> Reads current and logs on usbuart every 1 second.

```c
void application_task ( void )
{
    int16_t current_data;

    current_data = hallcurrent2_get_current( &hallcurrent2 );
    log_printf( &logger, "--- Current : %d mA\r\n", current_data );
    Delay_ms( 1000 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent2

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
