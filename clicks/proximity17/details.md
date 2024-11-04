
---
# Proximity 17 Click

> Proximity 17 Click is a compact add-on board that contains a close-range proximity sensing solution. This board features the TMD2635, a miniature proximity sensor module from ams AG. The TMD2635 features advanced proximity measurement in a tiny and thin optical land grid array module that incorporates a 940nm infrared vertical-cavity surface-emitting laser (IR VCSEL) factory calibrated for IR proximity response. It also offers advanced crosstalk noise cancellation through a wide range of offset adjustments through a digital fast-mode I2C interface to compensate for unwanted IR energy reflection at the sensor. This Click board™ is suitable for consumer and industrial applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/proximity17_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/proximity-17-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Proximity 17 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Proximity 17 Click driver.

#### Standard key functions :

- `proximity17_cfg_setup` Config Object Initialization function.
```c
void proximity17_cfg_setup ( proximity17_cfg_t *cfg );
```

- `proximity17_init` Initialization function.
```c
err_t proximity17_init ( proximity17_t *ctx, proximity17_cfg_t *cfg );
```

- `proximity17_default_cfg` Click Default Configuration function.
```c
err_t proximity17_default_cfg ( proximity17_t *ctx );
```

#### Example key functions :

- `proximity17_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t proximity17_get_int_pin ( proximity17_t *ctx );
```

- `proximity17_read_proximity` This function reads the raw proximity data. The higher the value, the closer the detected object is.
```c
err_t proximity17_read_proximity ( proximity17_t *ctx, uint16_t *prox_data );
```

- `proximity17_soft_reset` This function executes the defice software reset command.
```c
err_t proximity17_soft_reset ( proximity17_t *ctx );
```

## Example Description

> This example demonstrates the use of Proximity 17 Click board by reading and displaying the proximity data on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger, and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity17_cfg_t proximity17_cfg;  /**< Click config object. */

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
    proximity17_cfg_setup( &proximity17_cfg );
    PROXIMITY17_MAP_MIKROBUS( proximity17_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == proximity17_init( &proximity17, &proximity17_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXIMITY17_ERROR == proximity17_default_cfg ( &proximity17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the proximity data and displays it on the USB UART approximately once per second. The higher the proximity value, the closer the detected object is.

```c
void application_task ( void )
{
    uint16_t proximity;
    if ( PROXIMITY17_OK == proximity17_read_proximity ( &proximity17, &proximity ) )
    {
        log_printf ( &logger, " Proximity: %u\r\n\n", proximity );
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity17

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
