
---
# Barometer 12 Click

> [Barometer 12 Click](https://www.mikroe.com/?pid_product=MIKROE-5775) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5775&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : May 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for the Barometer 12 Click driver.
  The library initializes and defines the I2C bus drivers 
  to write and read data from registers.
  This demo application shows an example of 
  atmospheric pressure and temperature measurement.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Barometer12

### Example Key Functions

- `barometer12_cfg_setup` Config Object Initialization function.
```c
void barometer12_cfg_setup ( barometer12_cfg_t *cfg );
```

- `barometer12_init` Initialization function.
```c
err_t barometer12_init ( barometer12_t *ctx, barometer12_cfg_t *cfg );
```

- `barometer12_default_cfg` Click Default Configuration function.
```c
err_t barometer12_default_cfg ( barometer12_t *ctx );
```

- `barometer12_inv_invpres_calib` Barometer 12 inverse process data function.
```c
err_t barometer12_inv_invpres_calib ( barometer12_t *ctx, barometer12_invpres_t *cfg_data );
```

- `barometer12_get_raw_data` Barometer 12 get RAW data function.
```c
err_t barometer12_get_raw_data ( barometer12_t *ctx, uint16_t measurement_comd, uint32_t *pressure, uint16_t *temperature );
```

- `barometer12_get_press_and_temp` Barometer 12 get pressure and temperature function.
```c
err_t barometer12_get_press_and_temp ( barometer12_t *ctx,  float *pressure, float *temperature );
```

### Application Init

> The initialization of the I2C module and log UART.
  After driver initialization and default settings, 
  the app display device ID.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    barometer12_cfg_t barometer12_cfg;  /**< Click config object. */

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
    barometer12_cfg_setup( &barometer12_cfg );
    BAROMETER12_MAP_MIKROBUS( barometer12_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == barometer12_init( &barometer12, &barometer12_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BAROMETER12_ERROR == barometer12_default_cfg ( &barometer12 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    static uint16_t device_id;
    err_t err_flag = barometer12_get_device_id( &barometer12, &device_id );
    if ( BAROMETER12_ERROR == err_flag ) 
    {
        log_error( &logger, " Communication Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_printf( &logger, " Device ID   : 0x%.4X \r\n", device_id );
    log_printf( &logger, "----------------------------\r\n" );
    Delay_ms ( 1000 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This is an example that shows the use of a Barometer 12 Click board&trade;.
  Logs the atmospheric pressure [ Pa ] and temperature [ degree Celsius ] data.
  Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    float pressure;
    float temperature;
    
    barometer12_get_press_and_temp( &barometer12, &pressure, &temperature );
    log_printf( &logger, " Pressure    : %.2f Pa\r\n", pressure );
    log_printf( &logger, " Temperature : %.2f C\r\n", temperature );
    log_printf( &logger, "----------------------------\r\n" );
    Delay_ms ( 1000 );
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
