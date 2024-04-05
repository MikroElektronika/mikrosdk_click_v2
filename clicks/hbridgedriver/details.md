
---
# H-Bridge Driver click

> H-Bridge Driver Click is a compact add-on board that contains an H-bridge gate driver, also known as a full-bridge pre-driver. This board features the MC33883, an H-Bridge gate driver with an integrated charge pump and independent high and low side gate drive channels from NXP Semiconductors.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/h_bridge_driver_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/h-bridge-driver-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Oct 2021.
- **Type**          : GPIO type


# Software Support

We provide a library for the HBridgeDriver Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for HBridgeDriver Click driver.

#### Standard key functions :

- `hbridgedriver_cfg_setup` Config Object Initialization function.
```c
void hbridgedriver_cfg_setup ( hbridgedriver_cfg_t *cfg );
```

- `hbridgedriver_init` Initialization function.
```c
err_t hbridgedriver_init ( hbridgedriver_t *ctx, hbridgedriver_cfg_t *cfg );
```

#### Example key functions :

- `hbridgedriver_glo_enable` Global enable function.
```c
void hbridgedriver_glo_enable ( hbridgedriver_t *ctx, uint8_t state );
```

- `hbridgedriver_reverse` H-Bridge mode reverse function.
```c
void hbridgedriver_reverse ( hbridgedriver_t *ctx );
```

- `hbridgedriver_forward` H-Bridge mode forward function.
```c
void hbridgedriver_forward ( hbridgedriver_t *ctx );
```

## Example Description

> This is an example that demonstrates the use of the H-Bridge Driver Click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes GPIO and LOG structures, and sets AN, RST, CS, PWM and INT pins as output and start to write log.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridgedriver_cfg_t hbridgedriver_cfg;  /**< Click config object. */

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
    hbridgedriver_cfg_setup( &hbridgedriver_cfg );
    HBRIDGEDRIVER_MAP_MIKROBUS( hbridgedriver_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == hbridgedriver_init( &hbridgedriver, &hbridgedriver_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    hbridgedriver_glo_enable( &hbridgedriver, HBRIDGEDRIVER_PROP_EN );
    Delay_ms ( 100 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Demonstrates use of the H-Bridge Driver click board by turning connected MOSFETs 
> gates high or low in order to drive the motor forward, in reverse, brake or coast.

```c

void application_task ( void ) 
{
    log_printf( &logger, "The motor turns forward! \r\n" );
    hbridgedriver_forward( &hbridgedriver );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "The motor brakes! \r\n" );
    hbridgedriver_braking( &hbridgedriver );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "The motor turns in reverse \r\n" );
    hbridgedriver_reverse( &hbridgedriver );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "The motor coasting \r\n" );
    hbridgedriver_coasting( &hbridgedriver );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridgeDriver

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
