
---
# Altitude 5 Click

> [Altitude 5 Click](https://www.mikroe.com/?pid_product=MIKROE-4875) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4875&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Sep 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for Altitude 5 Click driver.
> The demo application reads ADC value, calculate pressure and altitude.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Altitude5

### Example Key Functions

- `altitude5_cfg_setup` Config Object Initialization function.
```c
void altitude5_cfg_setup ( altitude5_cfg_t *cfg );
```

- `altitude5_init` Initialization function.
```c
err_t altitude5_init ( altitude5_t *ctx, altitude5_cfg_t *cfg );
```

- `altitude5_default_cfg` Click Default Configuration function.
```c
err_t altitude5_default_cfg ( altitude5_t *ctx );
```

- `altitude5_get_altitude` Altitude 5 get altitude function.
```c
err_t altitude5_get_altitude ( altitude5_t *ctx, float *altitude );
```

- `altitude5_get_pressure` Altitude 5 get pressure function.
```c
err_t altitude5_get_pressure ( altitude5_t *ctx, float *pressure );
```

- `altitude5_get_adc_voltage` Altitude 5 get ADC voltage function.
```c
err_t altitude5_get_adc_voltage ( altitude5_t *ctx, float *adc_vtg );
```

### Application Init

> Initializes I2C or analog driver and log UART.
> After driver initialization the app set default settings.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    altitude5_cfg_t altitude5_cfg;  /**< Click config object. */

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
    altitude5_cfg_setup( &altitude5_cfg );
    ALTITUDE5_MAP_MIKROBUS( altitude5_cfg, MIKROBUS_1 );
    err_t init_flag = altitude5_init( &altitude5, &altitude5_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    altitude5_default_cfg ( &altitude5 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "----------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This is an example that demonstrates the use of the Altitude 5 Click board&trade;.
> In this example, we read ADC values and 
> display the Pressure ( mBar ) and Altitude ( m ) data.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    static float pressure;
    static float altitude;
    
    altitude5_get_pressure( &altitude5, &pressure );
    log_printf( &logger, " Pressure    : %.2f mBar \r\n", pressure );
    Delay_ms ( 100 );
    
    altitude5_get_altitude( &altitude5, &altitude );
    log_printf( &logger, " Altitude    : %.2f m \r\n", altitude );
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
