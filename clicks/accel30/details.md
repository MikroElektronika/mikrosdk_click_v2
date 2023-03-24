
---
# Accel 30 click

> Accel 30 Click is a compact add-on board that contains an acceleration sensor. This board features the MC3635, an ultra-low power, low-noise, integrated digital output 3-axis accelerometer from MEMSIC. The MC3635 allows selectable full-scale acceleration measurements in ranges of ±2g, ±4g, ±8g, ±12g, or ±16g in three axes with a configurable host interface that supports both SPI and I2C serial communication. It also supports high-resolution, low-power operating modes and interrupt feature for various events allowing maximum flexibility to meet multiple use case needs.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/accel30_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/accel-30-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Feb 2023.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Accel 30 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Accel 30 Click driver.

#### Standard key functions :

- `accel30_cfg_setup` Config Object Initialization function.
```c
void accel30_cfg_setup ( accel30_cfg_t *cfg );
```

- `accel30_init` Initialization function.
```c
err_t accel30_init ( accel30_t *ctx, accel30_cfg_t *cfg );
```

- `accel30_default_cfg` Click Default Configuration function.
```c
err_t accel30_default_cfg ( accel30_t *ctx );
```

#### Example key functions :

- `accel30_get_axis` Accel 30 get accel data function.
```c
err_t accel30_get_axis ( accel30_t *ctx, accel30_axis_t *acc_axis );
```

- `accel30_set_resolution_ctrl` Accel 30 set resolution control function.
```c
err_t accel30_set_resolution_ctrl ( accel30_t *ctx, accel30_resolution_t resolution );
```

- `accel30_set_mode` Accel 30 set operating mode function.
```c
err_t accel30_set_mode ( accel30_t *ctx, accel30_op_mode_t mode );
```

## Example Description

> This library contains API for Accel 30 Click driver.
> The library initializes and defines the I2C or SPI bus drivers 
> to write and read data from registers. 
> The library also includes a function for reading X-axis, Y-axis, and Z-axis data.

**The demo application is composed of two sections :**

### Application Init

> The initialization of I2C or SPI module, log UART, and additional pins.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel30_cfg_t accel30_cfg;  /**< Click config object. */

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
    accel30_cfg_setup( &accel30_cfg );
    ACCEL30_MAP_MIKROBUS( accel30_cfg, MIKROBUS_1 );
    err_t init_flag = accel30_init( &accel30, &accel30_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( ACCEL30_ERROR == accel30_default_cfg ( &accel30 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    log_printf( &logger, "------------------------\r\n" );
    log_printf( &logger, "       Accel Data       \r\n" );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms( 100 ); 
}
```

### Application Task

> This example demonstrates the use of the Accel 30 Click board™.
> Measures and displays acceleration data for X-axis, Y-axis, and Z-axis.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    static accel30_axis_t axis;
    if ( ACCEL30_OK == accel30_get_axis( &accel30, &axis ) )
    {
        log_printf( &logger, "\tX : %d \r\n\tY : %d \r\n\tZ : %d \r\n", axis.x, axis.y, axis.z );
        log_printf( &logger, "------------------------\r\n" );
    }
    Delay_ms( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel30

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
