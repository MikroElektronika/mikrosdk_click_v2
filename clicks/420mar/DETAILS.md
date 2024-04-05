
---
# 4-20 mA R click

4-20mA R Click is an add-on board in mikroBUS form factor which serves as a receiver in a 4-20mA current loop standard. It features INA196 current shunt monitor, MCP3201 12-bit ADC as well as TPS61041 DC/DC boost converter.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/420mar_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/4-20ma-r-click)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type

# Software Support

We provide a library for the 420MaR Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 420MaR Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c420mar_cfg_setup ( c420mar_cfg_t *cfg ); 
 
- Initialization function.
> c420MAR_RETVAL c420mar_init ( c420mar_t *ctx, c420mar_cfg_t *cfg );

- Click Default Configuration function.
> void c420mar_default_cfg ( c420mar_t *ctx );


#### Example key functions :

- This function reads the 16-bit current value from the SPI data register, and then normalizes and converts it to float.
> float c420mar_read_data( c420mar_t *ctx );

## Examples Description

> This example showcases how to initialize, configure and use the 4-20 mA R click. It is a
  simple SPI communication module that acts as a receiver in a 4-20 current loop. The click
  reads current data and converts the analog signal to a digital 12-bit format. 

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the logger and click modules. 

```c

void application_init ( )
{
    log_cfg_t log_cfg;
    c420mar_cfg_t cfg;

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

    c420mar_cfg_setup( &cfg );
    c420MAR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c420mar_init( &c420mar, &cfg );
}
  
```

### Application Task

> This function reads and displays current data every half a second. 

```c

void application_task ( )
{
    float current;

    current = c420mar_read_data( &c420mar );

    log_printf( &logger, "-----------------------------\r\n" );
    log_printf( &logger, " * Current: %.3f mA * \r\n", current );

    Delay_ms ( 500 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.420MaR

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
