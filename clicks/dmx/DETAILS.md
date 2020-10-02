
---
# DMX click

DMX Click is a device used to establish communication between the MCU and equipment that uses the DMX512-A communication protocol.

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>

[click Product page](https://www.mikroe.com/dmx-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the Dmx Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Dmx Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void dmx_cfg_setup ( dmx_cfg_t *cfg ); 
 
- Initialization function.
> DMX_RETVAL dmx_init ( dmx_t *ctx, dmx_cfg_t *cfg );

- Click Default Configuration function.
> void dmx_default_cfg ( dmx_t *ctx );


#### Example key functions :

- Auto Baud Rate Setting function
> void dmx_auto_baud_rate ( dmx_t *ctx );
 
- This function checks the interrupt state.
> uint8_t dmx_check_int ( dmx_t *ctx );

- This function allows user to put device in config or run mode.
> void dmx_run ( dmx_t *ctx, uint8_t run_mode );

## Examples Description

> This example reads and processes data from DMX clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and wake-up module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    dmx_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    dmx_cfg_setup( &cfg );
    DMX_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dmx_init( &dmx, &cfg );

    dmx_auto_baud_rate( &dmx );
    Delay_ms( 100 );

/** 
 * This is the only place where user needs to set the device mode,
 * master or slave.
 */

    device_mode = DMX_MASTER;
    master_mode = DMX_MASTER_DEMO_CTRL;

    dmx_reset( &dmx, device_mode );
    dmx_process( );
    dmx_run( &dmx, DMX_CONFIG_MODE );
    Delay_ms( 100 );

    if ( device_mode == DMX_SLAVE )
    {
        dmx_generic_write( &dmx, &sadr_cmd[ 0 ], 9 );
        dmx_process( );
        dmx_generic_write( &dmx, &flen_slave_cmd[ 0 ], 9 );
        dmx_process( );
        dmx_generic_write( &dmx, &itmr_cmd[ 0 ], 9 );
        dmx_process( );
    }
    else
    {
        dmx_generic_write( &dmx, &purgebfr_cmd[ 0 ], 9 );
        dmx_process( );
        dmx_generic_write( &dmx, &sadr_cmd[ 0 ], 9 );
        dmx_process( );
        dmx_generic_write( &dmx, &blen_cmd[ 0 ], 9 );
        dmx_process( );
        dmx_generic_write( &dmx, &flen_master_cmd[ 0 ], 9 );
        dmx_process( );
        dmx_generic_write( &dmx, &itmr_cmd[ 0 ], 9 );
        dmx_process( );
        dmx_generic_write( &dmx, &ftmr_cmd[ 0 ], 9 );
        dmx_process( );
    }

    dmx_run( &dmx, DMX_RUN_MODE );

    log_printf( &logger, "************************************\r\n" );
    log_printf( &logger, "***   SmartDMX is ready now...   ***\r\n" );
    log_printf( &logger, "************************************\r\n" );

    Delay_ms( 500 );
}
  
```

### Application Task

> Reads the received data and parses it.

```c

void application_task ( void )
{
    uint8_t test[ 6 ] = { 0 };

    if ( device_mode == DMX_SLAVE )
    {
        dmx_process(  );
    }
    else
    {
        application_demo( &dmx );
    }
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Dmx

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
