
---
# Accel 21 click

> Accel 21 Click is a compact add-on board that contains an acceleration sensor. 
> This board features the MIS2DH, a high-performance three-axis accelerometer from STMicroelectronics. 
> The MIS2DH allows selectable full-scale acceleration measurements in ranges of ±2g, ±4g, ±8g, or ±16g 
> in three axes with a configurable host interface that supports both SPI and I2C serial communication. 
> It also supports high-resolution and low-power operating modes, 
> allowing maximum flexibility to meet various use case needs.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/accel21_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/accel-21-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2022.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Accel 21 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Accel 21 Click driver.

#### Standard key functions :

- `accel21_cfg_setup` Config Object Initialization function.
```c
void accel21_cfg_setup ( accel21_cfg_t *cfg );
```

- `accel21_init` Initialization function.
```c
err_t accel21_init ( accel21_t *ctx, accel21_cfg_t *cfg );
```

- `accel21_default_cfg` Click Default Configuration function.
```c
err_t accel21_default_cfg ( accel21_t *ctx );
```

#### Example key functions :

- `accel21_set_config` Accel 21 set config function.
```c
err_t accel21_set_config ( accel21_t *ctx, accel21_config_t config );
```

- `accel21_get_axis` Accel 21 get accel data function.
```c
err_t accel21_get_axis ( accel21_t *ctx, accel21_axis_t *acc_axis );
```

- `accel21_get_temperature` Accel 21 get temperature function.
```c
err_t accel21_get_temperature ( accel21_t *ctx, float *temperature );
```

## Example Description

> This library contains API for Accel 21 Click driver.
> The library initializes and defines the I2C or SPI bus drivers 
> to write and read data from registers. 
> The library also includes a function for reading X-axis, Y-axis, and Z-axis data.

**The demo application is composed of two sections :**

### Application Init

> The initialization of I2C or SPI module, log UART, and additional pins. 
> After the driver init, the app executes a default configuration,
> checks communication and device ID. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    accel21_cfg_t accel21_cfg;  /**< Click config object. */

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
    accel21_cfg_setup( &accel21_cfg );
    ACCEL21_MAP_MIKROBUS( accel21_cfg, MIKROBUS_1 );
    err_t init_flag = accel21_init( &accel21, &accel21_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ACCEL21_ERROR == accel21_default_cfg ( &accel21 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    if ( ACCEL21_ERROR == accel21_check_id ( &accel21 ) )
    {
        log_printf( &logger, " Communication ERROR \r\n" );
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

> This example demonstrates the use of the Accel 21 Click board™.
> Measures and displays acceleration data for X-axis, Y-axis, and Z-axis. 
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    static accel21_axis_t axis;
    accel21_get_axis( &accel21, &axis );
    log_printf( &logger, "\tX : %d \r\n\tY : %d \r\n\tZ : %d \r\n", axis.x, axis.y, axis.z );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel21

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
