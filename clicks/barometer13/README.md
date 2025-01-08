
---
# Barometer 13 Click

> [Barometer 13 Click](https://www.mikroe.com/?pid_product=MIKROE-5921) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5921&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Sep 2023.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of  Barometer 13  Click board&trade; 
> by reading and displaying the pressure and temperature measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Barometer13

### Example Key Functions

- `barometer13_cfg_setup` Config Object Initialization function.
```c
void barometer13_cfg_setup ( barometer13_cfg_t *cfg );
```

- `barometer13_init` Initialization function.
```c
err_t barometer13_init ( barometer13_t *ctx, barometer13_cfg_t *cfg );
```

- `barometer13_default_cfg` Click Default Configuration function.
```c
err_t barometer13_default_cfg ( barometer13_t *ctx );
```

- `barometer13_get_measurement` Barometer 13 get the measurement data function.
```c
err_t barometer13_get_measurement ( barometer13_t *ctx, float *pressure, float *temperature );
```

- `barometer13_set_odr` Barometer 13 set the output data rate function.
```c
err_t barometer13_set_odr ( barometer13_t *ctx, uint8_t odr );
```

- `barometer13_set_int_cfg` Barometer 13 set the interrupt config function.
```c
err_t barometer13_set_int_cfg ( barometer13_t *ctx, uint8_t int_en, uint8_t int_od, 
                                                    uint8_t int_pol, uint8_t int_mode );
```

### Application Init

> The initialization of I2C or SPI module and log UART.
> After driver initialization, the app sets the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    barometer13_cfg_t barometer13_cfg;  /**< Click config object. */

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
    barometer13_cfg_setup( &barometer13_cfg );
    BAROMETER13_MAP_MIKROBUS( barometer13_cfg, MIKROBUS_1 );
    err_t init_flag = barometer13_init( &barometer13, &barometer13_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BAROMETER13_ERROR == barometer13_default_cfg ( &barometer13 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ______________________ \r\n" );
}
```

### Application Task

> The demo application reads and displays the Pressure [mBar] and Temperature [degree Celsius] data.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{   
    float pressure = 0, temperature = 0;
    if ( ( BAROMETER13_OK == barometer13_get_measurement( &barometer13, &pressure, &temperature ) ) &&
         barometer13_get_interrupt( &barometer13 ) )
    {
        log_printf( &logger, " Pressure    : %.2f mBar \r\n", pressure );
        log_printf( &logger, " Temperature : %.2f degC \r\n", temperature );
        log_printf( &logger, " ______________________ \r\n" );
        Delay_ms ( 1000 );
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
