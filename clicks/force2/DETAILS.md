
---
# Force 2 click

Force 2 Click is a mikroBUS™ add-on board with circuitry for implementing Honeywell’s FSS1500NGT Series force sensors into your projects (with a single zone force sensing resistor included with the click).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/force2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/force-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : ADC type


# Software Support

We provide a library for the Force2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Force2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void force2_cfg_setup ( force2_cfg_t *cfg ); 
 
- Initialization function.
> FORCE2_RETVAL force2_init ( force2_t *ctx, force2_cfg_t *cfg );


#### Example key functions :

- Generic read function.
> force2_data_t force2_generic_read ( force2_t *ctx );

## Examples Description

> This application is used to measure the pressure force.

**The demo application is composed of two sections :**

### Application Init 

> Initalizes ADC driver, sets ADC channel and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    force2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    force2_cfg_setup( &cfg );
    FORCE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    force2_init( &force2, &cfg );


    log_printf( &logger, "--------------------\r\n" );
    log_printf( &logger, "    Force 2 click   \r\n" );
    log_printf( &logger, "--------------------\r\n" );

    Delay_ms( 100 );
}
  
```

### Application Task

> This is an example that shows the capabilities of the Force 2 click by taking measurements from the device and displaying it via USART terminal.

```c

void application_task ( void )
{
    uint32_t disp_val;
    force2_data_t tmp;
    
    //  Task implementation.
    
    tmp = force2_generic_read ( &force2 );
    disp_val = force2_val_conv( tmp, 4095, 15, 0 );

    log_printf( &logger, "Force: %d N\r\n", disp_val );
    Delay_ms( 500 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Force2

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
