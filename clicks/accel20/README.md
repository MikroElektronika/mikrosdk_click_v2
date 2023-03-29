\mainpage Main Page

---
# Accel 20 click

> Accel 20 Click is a compact add-on board that contains an acceleration sensor. This board features the KX134-1211, a digital output 3-axis accelerometer optimized for machine condition monitoring from Rohm Semiconductor. It allows selectable full-scale acceleration measurements in ranges of ±8g, ±16g, ±32g, or ±64g in three axes with a configurable host interface that supports both SPI and I2C serial communication. It also features an Advanced Data Path (ADP) technology which allows noise filtering and sensor signal processing, usually carried out by the MCU, to be performed by the accelerometer. They contribute to reducing MCU load and power consumption together with improved application performance.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/accel20_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/accel-20-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Sep 2021.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Accel20 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Accel20 Click driver.

#### Standard key functions :

- `accel20_cfg_setup` Config Object Initialization function.
```c
void accel20_cfg_setup ( accel20_cfg_t *cfg );
```

- `accel20_init` Initialization function.
```c
err_t accel20_init ( accel20_t *ctx, accel20_cfg_t *cfg );
```

- `accel20_default_cfg` Click Default Configuration function.
```c
err_t accel20_default_cfg ( accel20_t *ctx );
```

#### Example key functions :

- `accel20_get_axis_data` Accel 20 get accelerometer axis function.
```c
err_t accel20_get_axis_data ( accel20_t *ctx, accel20_axis_t *axis );
```

- `accel20_set_output_data_rate` Accel 20 set output data rate function.
```c
err_t accel20_set_output_data_rate ( accel20_t *ctx, uint8_t odr );
```

- `accel20_set_accel_range` Accel 20 set accel range function.
```c
err_t accel20_set_accel_range ( accel20_t *ctx, uint8_t range );
```

## Example Description

> This library contains API for Accel 20 Click driver.
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
    accel20_cfg_t accel20_cfg;  /**< Click config object. */

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
    accel20_cfg_setup( &accel20_cfg );
    ACCEL20_MAP_MIKROBUS( accel20_cfg, MIKROBUS_1 );
    err_t init_flag  = accel20_init( &accel20, &accel20_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    accel20_default_cfg ( &accel20 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "      Accel 20 Click     \r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms( 100 ); 
    
    if ( accel20_check_id( &accel20 ) == ACCEL20_OK ) 
    {
        log_printf( &logger, "     Communication OK    \r\n" );
        log_printf( &logger, "-------------------------\r\n" );
    }
    else 
    {
        log_printf( &logger, "   Communication ERROR   \r\n" );
        log_printf( &logger, "     Reset the device    \r\n" );
        log_printf( &logger, "-------------------------\r\n" );

        for ( ; ; );
    }
    
    log_printf( &logger, "       Accel Data:       \r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms( 100 ); 
}

```

### Application Task

> This is an example that demonstrates the use of the Accel 20 Click board™.
> Measures and displays acceleration data for X-axis, Y-axis, and Z-axis. 
> Results are being sent to the USART terminal where the user can track their changes. 
> This task repeats every 1 sec.

```c

void application_task ( void )
{
    static accel20_axis_t axis;
    
    if ( accel20_get_int_1( &accel20 ) == ACCEL20_INT1_DATA_READY )
    {
        accel20_get_axis_data( &accel20, &axis );
        log_printf( &logger, "\tX : %d \r\n\tY : %d \r\n\tZ : %d \r\n", axis.x, axis.y, axis.z );
        log_printf( &logger, "-------------------------\r\n" );
        Delay_ms( 1000 );     
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel20

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
