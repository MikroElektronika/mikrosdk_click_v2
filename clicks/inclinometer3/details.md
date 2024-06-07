
---
# Inclinometer 3 click

> Inclinometer 3 Click is a compact add-on board for precise tilt and leveling measurement applications. This board features the SCL3400-D01, a two-axis inclinometer sensor from Murata, leveraging advanced capacitive 3D-MEMS technology. It features a high-performance mixed-signal ASIC with a flexible SPI digital interface housed in a robust 12-pin pre-molded casing, ensuring long-term reliability and performance.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/inclinometer3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/inclinometer-3-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the Inclinometer 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Inclinometer 3 Click driver.

#### Standard key functions :

- `inclinometer3_cfg_setup` Config Object Initialization function.
```c
void inclinometer3_cfg_setup ( inclinometer3_cfg_t *cfg );
```

- `inclinometer3_init` Initialization function.
```c
err_t inclinometer3_init ( inclinometer3_t *ctx, inclinometer3_cfg_t *cfg );
```

- `inclinometer3_default_cfg` Click Default Configuration function.
```c
err_t inclinometer3_default_cfg ( inclinometer3_t *ctx );
```

#### Example key functions :

- `inclinometer3_get_axes` This function reads the accelerometer sensor axes data by using SPI serial interface.
```c
err_t inclinometer3_get_axes ( inclinometer3_t *ctx, float *x_axes, float *y_axes );
```

- `inclinometer3_get_temperature` This function reads the temperature measurement data by using SPI serial interface.
```c
err_t inclinometer3_get_temperature ( inclinometer3_t *ctx, float *temperature );
```

## Example Description

> This library contains API for the Inclinometer 3 Click driver.
> The library initializes and defines the SPI drivers to 
> write and read data from registers, as well as the default configuration 
> for the reading accelerator and temperature data.

**The demo application is composed of two sections :**

### Application Init

> The initialization of the SPI module, log UART, and additional pins.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    inclinometer3_cfg_t inclinometer3_cfg;  /**< Click config object. */

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
    inclinometer3_cfg_setup( &inclinometer3_cfg );
    INCLINOMETER3_MAP_MIKROBUS( inclinometer3_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == inclinometer3_init( &inclinometer3, &inclinometer3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( INCLINOMETER3_ERROR == inclinometer3_default_cfg ( &inclinometer3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ________________________ \r\n" );
}
```

### Application Task

> This example demonstrates the use of the Inclinometer 3 Click board.
> Measures and displays acceleration data for the XY-axis [mg] 
> and temperature [degree Celsius] data.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    float temperature = 0, x_axes = 0, y_axes = 0;
    if ( ( INCLINOMETER3_OK == inclinometer3_get_temperature( &inclinometer3, &temperature ) ) && 
         ( INCLINOMETER3_OK == inclinometer3_get_axes( &inclinometer3, &x_axes, &y_axes ) ) )
    {
        log_printf( &logger, " Accel X: %.2f mg\r\n", x_axes );
        log_printf( &logger, " Accel Y: %.2f mg\r\n\r\n", y_axes );
        log_printf( &logger, " Temperature : %.2f degC\r\n", temperature );
        log_printf( &logger, " ________________________ \r\n" );
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Inclinometer3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
