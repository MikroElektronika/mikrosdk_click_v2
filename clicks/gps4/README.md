\mainpage Main Page
 
---
# GPS4 click

GPS 4 click carries the L70 compact GPS module from Quectel. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gps4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/gps-4-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : apr 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the Gps4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Gps4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void gps4_cfg_setup ( gps4_cfg_t *cfg ); 
 
- Initialization function.
> GPS4_RETVAL gps4_init ( gps4_t *ctx, gps4_cfg_t *cfg );

#### Example key functions :

- Generic parser function.
> gps4_error_t gps4_generic_parser ( char *rsp,  uint8_t command, uint8_t element, char *parser_buf );
 
- Generic read function.
> int32_t gps4_generic_read ( gps4_t *ctx, char *data_buf, uint16_t max_len );

- Wake-up module.
> void gps4_module_wakeup ( gps4_t *ctx );

## Examples Description

> This example reads and processes data from GPS4 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and wake-up module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    gps4_cfg_t cfg;

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

    gps4_cfg_setup( &cfg );
    GPS4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gps4_init( &gps4, &cfg );

    gps4_module_wakeup( &gps4 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
  
```

### Application Task

> Reads the received data and parses it.

```c

void application_task ( void )
{
    gps4_process(  );
    parser_application( current_parser_buf );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Gps4

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
