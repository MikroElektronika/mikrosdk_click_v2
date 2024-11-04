
 

---
# R Meter Click

R Meter Click is a mikroBUS add-on board with circuitry for measuring the value of resistors. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rmeter_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/r-meter-click)

---


#### Click library 

- **Author**        : Jovan Stajkovic
- **Date**          : nov 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Rmeter Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Rmeter Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void rmeter_cfg_setup ( rmeter_cfg_t *cfg ); 
 
- Initialization function.
> RMETER_RETVAL rmeter_init ( rmeter_t *ctx, rmeter_cfg_t *cfg );

- Click Default Configuration function.
> void rmeter_default_cfg ( rmeter_t *ctx );


#### Example key functions :

- Get resistance in OHMs function
> float rmeter_get_ohms ( rmeter_t *ctx );
 
- Get average voltage function
> float rmeter_avg_volt ( rmeter_t *ctx );

- Calculations function
> float rmeter_calc ( rmeter_t *ctx, uint32_t resFilt );

## Examples Description

> Demo app measures and displays resistance of a resistor connected 
> to the R Meter Click board.

**The demo application is composed of two sections :**

### Application Init 

> Initalizes SPI, LOG and Click drivers

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    rmeter_cfg_t cfg;

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

    rmeter_cfg_setup( &cfg );
    RMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rmeter_init( &rmeter, &cfg );

    Delay_ms ( 100 );
    log_printf( &logger, "----------------------- \r\n" );
    log_printf( &logger, "    R Meter  Click      \r\n" );
    log_printf( &logger, "----------------------- \r\n" );
}
```

### Application Task

> This is an example that shows the capabilities of the R Meter Click by 
> measuring resistance.

```c
void application_task ( void )
{
    ohms = rmeter_get_ohms( &rmeter );
    
    if ( ohms == RMETER_OVER_RANGE )
    {
        log_printf( &logger, " Over range! \r\n" );
    }
    else
    {
        log_printf( &logger, "Resistance: %.2f ohm \r\n", ohms );
    }
    
    log_printf( &logger, "----------------------- \r\n" );
    Delay_ms ( 1000 );
}
```

## Note

> R Meter Click is a handy tool but it is not to be used as a precision 
> instrument! The linearity of the OpAmp impacts the measurement.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Rmeter

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
