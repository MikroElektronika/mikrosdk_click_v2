
---
# Ozone 2 click

Ozone 2 click is an Ozone detection (O3) sensor, based on the MQ131 gas sensor. This gas sensor has a sensitive layer made of SnO2, which changes its resistance when exposed to ozone.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ozone2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ozone-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Ozone2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Ozone2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ozone2_cfg_setup ( ozone2_cfg_t *cfg ); 
 
- Initialization function.
> OZONE2_RETVAL ozone2_init ( ozone2_t *ctx, ozone2_cfg_t *cfg );

- Click Default Configuration function.
> void ozone2_default_cfg ( ozone2_t *ctx );


#### Example key functions :

- Function reads from MCP 3351 ADC and returns 32 bit read value.
> uint32_t ozone2_read ( ozone2_t *ctx );
 
## Examples Description

> This example reads data from the MCP 3351 sensor.

**The demo application is composed of two sections :**

### Application Init 

> Driver initialization.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ozone2_cfg_t cfg;

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

    ozone2_cfg_setup( &cfg );
    OZONE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ozone2_init( &ozone2, &cfg );
}
  
```

### Application Task

> Reading ADC value and displaying it via UART.

```c

void application_task ( void )
{
    read_value = ozone2_read( &ozone2 );
    log_printf( &logger, "Read Value: %u\r\n", read_value);
    
    Delay_ms( 3000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Ozone2

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
