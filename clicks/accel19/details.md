
---
# Accel 19 Click

> Accel 19 Click is a compact add-on board that contains an acceleration sensor. This board features the LIS2DTW12, an ultra-low-power high-performance three-axis accelerometer from STMicroelectronics. It allows selectable full-scale acceleration measurements in ranges of ±2g, ±4g, ±8g, or ±16g in three axes with a configurable host interface that supports both SPI and I2C serial communication. Alongside an embedded 0.8°C accuracy temperature sensor with ODRs ranging from 50 to 1.6Hz and resolution from 8 to 12 bits, it has a dedicated internal engine to process motion and acceleration detection.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/accel19_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/accel-19-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2021.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Accel 19 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Accel 19 Click driver.

#### Standard key functions :

- `accel19_cfg_setup` Config Object Initialization function.
```c
void accel19_cfg_setup ( accel19_cfg_t *cfg );
```

- `accel19_init` Initialization function.
```c
err_t accel19_init ( accel19_t *ctx, accel19_cfg_t *cfg );
```

- `accel19_default_cfg` Click Default Configuration function.
```c
err_t accel19_default_cfg ( accel19_t *ctx );
```

#### Example key functions :

- `accel19_get_axis_data` Accel 19 get accelerometer axis function.
```c
err_t accel19_get_axis_data ( accel19_t *ctx, accel19_axis_t *axis );
```

- `accel19_data_ready` Accel 19 data ready function.
```c
uint8_t accel19_data_ready (accel19_t *ctx );
```

- `accel19_set_control` Accel 19 set control function.
```c
err_t accel19_set_control ( accel19_t *ctx, uint8_t odr, uint8_t op_mode, uint8_t lp_mode );
```

## Example Description

> This library contains API for Accel 19 Click driver.
> The library initializes and defines the I2C or SPI bus drivers 
> to write and read data from registers. 
> The library also includes a function for reading X-axis, Y-axis, and Z-axis data.

**The demo application is composed of two sections :**

### Application Init

> The initialization of I2C or SPI module, log UART, and additional pins. 
> After the driver init, the app executes a default configuration
> and checks communication and device ID.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    accel19_cfg_t accel19_cfg;  /**< Click config object. */

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
    accel19_cfg_setup( &accel19_cfg );
    ACCEL19_MAP_MIKROBUS( accel19_cfg, MIKROBUS_1 );
    err_t init_flag  = accel19_init( &accel19, &accel19_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 1000 );
    
    if ( ACCEL19_ERROR == accel19_default_cfg ( &accel19 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    if ( ACCEL19_ERROR == accel19_check_device_id( &accel19 ) ) 
    {
        log_printf( &logger, "   Communication ERROR   \r\n" );
        log_printf( &logger, "     Reset the device    \r\n" );
        log_printf( &logger, "-------------------------\r\n" );

        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms ( 1000 ); 
}

```

### Application Task

> This is an example that demonstrates the use of the Accel 19 Click board™.
> Measures and displays acceleration data for X-axis, Y-axis, and Z-axis. 
> Results are being sent to the USART terminal where the user can track their changes. 
> This task repeats every 1 sec.

```c

void application_task ( void )
{
    static accel19_axis_t axis;
    
    if ( ACCEL19_STATUS_DRDY == accel19_data_ready( &accel19 ) )
    {
        accel19_get_axis_data( &accel19, &axis );
        log_printf( &logger, "\tX : %5d \r\n\tY : %5d \r\n\tZ : %5d \r\n", axis.x, axis.y, axis.z );
        log_printf( &logger, "-------------------------\r\n" );
        Delay_ms ( 1000 );     
    }
    Delay_ms ( 1 );  
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel19

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
