
---
# OPTO 4 Click

Opto 4 Click is a galvanically isolated power switch, which uses a power MOSFET in combination with an optocoupler.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/opto4_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/opto-4-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the OPTO4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for OPTO4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void opto4_cfg_setup ( opto4_cfg_t *cfg ); 
 
- Initialization function.
> OPTO4_RETVAL opto4_init ( opto4_t *ctx, opto4_cfg_t *cfg );

- Click Default Configuration function.
> void opto4_default_cfg ( opto4_t *ctx );


#### Example key functions :

- Function for output enable or disable
> void opto4_output_enable( opto4_t *ctx, uint8_t enable );

## Examples Description

> Opto 4 Click is a galvanically isolated power switch, which uses a power MOSFET in combination with an optocoupler.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver init.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    opto4_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    opto4_cfg_setup( &cfg );
    OPTO4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    opto4_init( &opto4, &cfg );
}
  
```

### Application Task

> The Output voltage enable and disable every 3 sec.

```c
void application_task ( )
{
    opto4_output_enable( &opto4, OPTO4_OUTPUT_ENABLE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    opto4_output_enable( &opto4, OPTO4_OUTPUT_DISABLE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.OPTO4

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
