
---
# Nano GPS click

Nano GPS click carries the Nano Hornet module from OriginGPS. It’s the smallest GPS module with an integrated patch antenna (measuring just 10x10x3.8mm).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/nanogps_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/nano-gps-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : apr 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the Nanogps Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Nanogps Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void nanogps_cfg_setup ( nanogps_cfg_t *cfg ); 
 
- Initialization function.
> NANOGPS_RETVAL nanogps_init ( nanogps_t *ctx, nanogps_cfg_t *cfg );


#### Example key functions :

- Generic parser function.
> nanogps_error_t nanogps_generic_parser ( char *rsp,  uint8_t command, uint8_t element, char *parser_buf );

- Generic read function.
> int32_t nanogps_generic_read ( nanogps_t *ctx, char *data_buf, uint16_t max_len );

- Wake-up module.
> void nanogps_module_wakeup ( nanogps_t *ctx );

## Examples Description

> This example reads and processes data from Nano GPS clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and wake-up module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    nanogps_cfg_t cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    nanogps_cfg_setup( &cfg );
    NANOGPS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    nanogps_init( &nanogps, &cfg );

    nanogps_module_wakeup( &nanogps );
}
  
```

### Application Task

> Reads the received data and parses it.

```c

void application_task ( void )
{
    nanogps_process(  );
    parser_application( current_parser_buf );
}

```

## Note

> Depending on the environmental conditions and the satellites availability
> it may take some time for the module to receive the position fix.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Nanogps

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
