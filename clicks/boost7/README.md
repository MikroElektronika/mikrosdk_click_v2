\mainpage Main Page

---
# Boost 7 Click

> Boost 7 Click is a compact add-on board that steps up the voltage from its input (supply) to its output (load). This board features the BD8316GWL, a dual DC/DC converter from Rohm Semiconductor. Each converter inside the BD8316GWL is designed with up to 200mA current limit generating well-regulated positive and negative outputs of ±3.3V or ±5V, making the BD8316GWL ideal for various applications. In addition to the possibility of working with both mikroBUS™ power rails, it also provides the opportunity of using an external power supply with a very low voltage of 2.5V.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/boost7_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/boost-7-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2022.
- **Type**          : GPIO type


# Software Support

We provide a library for the Boost 7 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Boost 7 Click driver.

#### Standard key functions :

- `boost7_cfg_setup` Config Object Initialization function.
```c
void boost7_cfg_setup ( boost7_cfg_t *cfg );
```

- `boost7_init` Initialization function.
```c
err_t boost7_init ( boost7_t *ctx, boost7_cfg_t *cfg );
```

#### Example key functions :

- `boost7_enable_out1` This function enables the OUT1 (V-) by setting the STB1 pin to high logic state.
```c
void boost7_enable_out1 ( boost7_t *ctx );
```

- `boost7_disable_out1` This function disables the OUT1 (V-) by setting the STB1 pin to low logic state.
```c
void boost7_disable_out1 ( boost7_t *ctx );
```

- `boost7_enable_out2` This function enables the OUT2 (V+) by setting the STB2 pin to high logic state.
```c
void boost7_enable_out2 ( boost7_t *ctx );
```

## Example Description

> This example demonstrates the use of Boost 7 Click board by controlling the V- and V+ outputs state.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    boost7_cfg_t boost7_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    boost7_cfg_setup( &boost7_cfg );
    BOOST7_MAP_MIKROBUS( boost7_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == boost7_init( &boost7, &boost7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Toggles the V- and V+ outputs state every 5 seconds and displays their state on the USB UART.

```c
void application_task ( void )
{
    log_printf( &logger, " OUT1 (V-) : ENABLED\r\n" );
    log_printf( &logger, " OUT2 (V+) : DISABLED\r\n\n" );
    boost7_enable_out1 ( &boost7 );
    boost7_disable_out2 ( &boost7 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " OUT1 (V-) : DISABLED\r\n" );
    log_printf( &logger, " OUT2 (V+) : ENABLED\r\n\n" );
    boost7_disable_out1 ( &boost7 );
    boost7_enable_out2 ( &boost7 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Boost7

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
