\mainpage Main Page
 
 

---
# LEM Click

LEM Click carries the LTS 6-NP current transducer and MCP3201 ADC converter. The Click can measure AC and DC current with exceptional speed, up to 200 KHz.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lem__click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/lem-click)

---


#### Click library 

- **Author**        : Jovan Stajkovic
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Lem Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Lem Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void lem_cfg_setup ( lem_cfg_t *cfg ); 
 
- Initialization function.
> LEM_RETVAL lem_init ( lem_t *ctx, lem_cfg_t *cfg );


#### Example key functions :

- Function is used to read current in amperes or milliamperes.
> float lem_get_current ( lem_t *ctx, float coef );

## Examples Description

> 
> Demo app measures and displays current by using LEM Click board.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Initalizes SPI, LOG and Click drivers.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    lem_cfg_t cfg;

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

    lem_cfg_setup( &cfg );
    LEM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lem_init( &lem, &cfg );
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "      LEM Click      \r\n" );
    log_printf( &logger, "---------------------\r\n" );
}
  
```

### Application Task

>
> This is an example that shows the capabilities of the LEM Click by measuring 
> current passing through the conductor placed through the hole on the sensor.
> 

```c

void application_task ( void )
{
    current = lem_get_current( &lem, LEM_MILIAMP_COEF );
    
    log_printf( &logger, " Current : %.2f mA \r\n", current );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Lem

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
