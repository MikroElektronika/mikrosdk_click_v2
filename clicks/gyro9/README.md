\mainpage Main Page

---
# Gyro 9 click

> Gyro 9 Click is a compact add-on board that contains a high-performance gyroscope. This board features the A3G4250D, a MEMS motion sensor from STMicroelectronics. It is a low-power 3-axes digital output gyroscope that provides unprecedented stability at zero rate level and sensitivity over temperature and time and is equipped with an embedded temperature sensor. The gyroscope has a 16-bit rate value data output with an 8-bit compensation temperature data output.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gyro9_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/gyro-9-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Aug 2023.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Gyro 9 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Gyro 9 Click driver.

#### Standard key functions :

- `gyro9_cfg_setup` Config Object Initialization function.
```c
void gyro9_cfg_setup ( gyro9_cfg_t *cfg );
```

- `gyro9_init` Initialization function.
```c
err_t gyro9_init ( gyro9_t *ctx, gyro9_cfg_t *cfg );
```

- `gyro9_default_cfg` Click Default Configuration function.
```c
err_t gyro9_default_cfg ( gyro9_t *ctx );
```

#### Example key functions :

- `gyro9_get_gyro_axis` Gyro 9 get gyro sensor axes function.
```c
err_t gyro9_get_gyro_axis ( gyro9_t *ctx, gyro9_axis_t *gyro_axis );
```

- `gyro9_get_axis_data` Gyro 9 get gyro data function.
```c
err_t gyro9_get_axis_data ( gyro9_t *ctx, gyro9_axis_data_t *gyro_axis );
```

- `gyro9_get_data_ready` Gyro 9 get data ready function.
```c
uint8_t gyro9_get_data_ready ( gyro9_t *ctx );
```

## Example Description

> This library contains API for Gyro 9 Click driver.
> The library initializes and defines the I2C and SPI bus drivers to 
> write and read data from registers, as well as the default 
> configuration for reading gyroscope data.

**The demo application is composed of two sections :**

### Application Init

> The initialization of I2C or SPI module, log UART, and additional pins.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gyro9_cfg_t gyro9_cfg;  /**< Click config object. */

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
    gyro9_cfg_setup( &gyro9_cfg );
    GYRO9_MAP_MIKROBUS( gyro9_cfg, MIKROBUS_1 );
    err_t init_flag = gyro9_init( &gyro9, &gyro9_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( GYRO9_ERROR == gyro9_default_cfg ( &gyro9 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "_________________\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the Gyro 9 Click board™.
> Measures and displays gyroscope angular rate for X-axis, Y-axis, and Z-axis.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    gyro9_axis_t gyro_axis;
    if ( gyro9_get_data_ready( &gyro9 ) )
    {
        if ( GYRO9_OK == gyro9_get_gyro_axis( &gyro9, &gyro_axis ) )
        {
            log_printf( &logger, " Gyro X: %.2f pds\r\n", gyro_axis.x );
            log_printf( &logger, " Gyro Y: %.2f pds\r\n", gyro_axis.y );
            log_printf( &logger, " Gyro Z: %.2f pds\r\n", gyro_axis.z );
            log_printf( &logger, "_________________\r\n" );
            Delay_ms ( 1000 );
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Gyro9

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
