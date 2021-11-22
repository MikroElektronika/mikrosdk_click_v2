\mainpage Main Page

---
# Thermo 21 click

> Thermo 21 Click is a compact add-on board that provides an accurate temperature measurement. This board features the ADT7301, a high-precision digital temperature sensor from Analog Devices. The ADT7301 houses an on-chip temperature sensor, a 13-bit A/D converter, a reference circuit, and serial interface logic functions in one package. Characterized by its high accuracy (up to ±0.5°C typical) and high resolution of 0.03125°C, this temperature sensor provides temperature data to the host controller with a configurable SPI interface. This Click board™ is appropriate for process control, environmental monitoring, domestic appliances, electronic test equipment, or other temperature measurement applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermo21_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/thermo-21-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Sep 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the Thermo21 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Thermo21 Click driver.

#### Standard key functions :

- `thermo21_cfg_setup` Config Object Initialization function.
```c
void thermo21_cfg_setup ( thermo21_cfg_t *cfg );
```

- `thermo21_init` Initialization function.
```c
err_t thermo21_init ( thermo21_t *ctx, thermo21_cfg_t *cfg );
```

#### Example key functions :

- `thermo21_temperature_read` Temperature reading function.
```c
err_t thermo21_temperature_read ( thermo21_t *ctx, float *data_out );
```

- `thermo21_generic_read` Data reading function.
```c
err_t thermo21_generic_read ( thermo21_t *ctx, uint8_t *data_out, uint8_t len );
```

## Example Description

> This example application showcases ability of the click board to read temperature data.

**The demo application is composed of two sections :**

### Application Init

> Initialization of communication modules(SPI, UART).

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo21_cfg_t thermo21_cfg;  /**< Click config object. */

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
    thermo21_cfg_setup( &thermo21_cfg );
    THERMO21_MAP_MIKROBUS( thermo21_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == thermo21_init( &thermo21, &thermo21_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Read and log temperautre every half second.

```c

void application_task ( void )
{
    float temperature = 0;
    if ( !thermo21_temperature_read( &thermo21, &temperature ) )
    {
        log_printf( &logger, " > Temperature[degC]: %.2f\r\n", temperature );
    }
    Delay_ms( 500 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo21

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
