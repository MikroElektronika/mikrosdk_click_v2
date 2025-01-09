
---
# Pressure 15 Click

> [Pressure 15 Click](https://www.mikroe.com/?pid_product=MIKROE-4747) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4747&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Jun 2021.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This application example showcases the ability of the device to
read temperature and pressure data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure15

### Example Key Functions

- `pressure15_cfg_setup` Config Object Initialization function.
```c
void pressure15_cfg_setup ( pressure15_cfg_t *cfg );
```

- `pressure15_init` Initialization function.
```c
err_t pressure15_init ( pressure15_t *ctx, pressure15_cfg_t *cfg );
```

- `pressure15_default_cfg` Click Default Configuration function.
```c
err_t pressure15_default_cfg ( pressure15_t *ctx );
```

- `pressure15_get_int` Get interrupt pin state.
```c
uint8_t pressure15_get_int ( pressure15_t *ctx );
```

- `pressure15_get_pressure` Get pressure data.
```c
err_t pressure15_get_pressure ( pressure15_t *ctx, float *pressure );
```

- `pressure15_get_temperature` Get temperature data.
```c
err_t pressure15_get_temperature ( pressure15_t *ctx, float *temperature );
```

### Application Init

> Initialization of hosts communication modules (UART, SPI/I2C) 
and interrupt pin. Checks device ID and sets the default configuration
that enables interrupt on new data.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pressure15_cfg_t pressure15_cfg;  /**< Click config object. */

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
    pressure15_cfg_setup( &pressure15_cfg );
    PRESSURE15_MAP_MIKROBUS( pressure15_cfg, MIKROBUS_1 );
    err_t init_flag = pressure15_init( &pressure15, &pressure15_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    uint8_t whoami = 0;
    init_flag = pressure15_generic_read( &pressure15, PRESSURE15_REG_WHO_AM_I, &whoami, 1 );
    if ( !init_flag && ( PRESSURE15_ID == whoami ) )
    {
        log_printf( &logger, " > ID: 0x%.2X\r\n", ( uint16_t )whoami );
    }
    else
    {
        log_error( &logger, " ID\r\n");
    }
    
    pressure15_default_cfg ( &pressure15 );
    Delay_ms ( 1000 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Checks if an interrupt occurred. If occurred reads new pressure and temperature
data in hPa and degC respectively.

```c
void application_task ( void ) 
{
    if ( pressure15_get_int( &pressure15 ) )
    {
        float temperature, pressure;
        
        pressure15_get_pressure( &pressure15, &pressure );
        log_printf( &logger, " > Pressure[hPa]: %.2f\r\n", pressure );
        
        pressure15_get_temperature( &pressure15, &temperature );
        log_printf( &logger, " > Temperature[degC]: %.2f\r\n", temperature );
        log_printf( &logger, "***************************************\r\n" );
        Delay_ms ( 200 );
    }
}
```

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
