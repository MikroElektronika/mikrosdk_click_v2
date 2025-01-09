
---
# IR Sense 5 Click

> [IR Sense 5 Click](https://www.mikroe.com/?pid_product=MIKROE-6093) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6093&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Feb 2024.
- **Type**          : ADC/I2C type

# Software Support

## Example Description

> This library contains API for the IR Sense 5 Click driver 
> for measuring ambient and object temperature.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.IRSense5

### Example Key Functions

- `irsense5_cfg_setup` Config Object Initialization function.
```c
void irsense5_cfg_setup ( irsense5_cfg_t *cfg );
```

- `irsense5_init` Initialization function.
```c
err_t irsense5_init ( irsense5_t *ctx, irsense5_cfg_t *cfg );
```

- `irsense5_get_obj_temp` This function reads and calculate object temperature in degree Celsius [degC].
```c
err_t irsense5_get_obj_temp ( irsense5_t *ctx, float *obj_temp );
```

- `irsense5_get_amb_temp` This function reads and calculate ambient temperature in degree Celsius [degC].
```c
err_t irsense5_get_amb_temp ( irsense5_t *ctx, float *amb_temp );
```

- `irsense5_read_raw_adc_thm` This function reads the thermistor raw ADC value.
```c
err_t irsense5_read_raw_adc_thm ( irsense5_t *ctx, uint16_t *raw_adc );
```

### Application Init

> The initialization of the I2C and ADC module and log UART.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irsense5_cfg_t irsense5_cfg;  /**< Click config object. */

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
    irsense5_cfg_setup( &irsense5_cfg );
    IRSENSE5_MAP_MIKROBUS( irsense5_cfg, MIKROBUS_1 );
    err_t init_flag = irsense5_init( &irsense5, &irsense5_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> The demo application measures ambient and object temperature in degrees Celsius.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    float temperature = 0;
    if ( IRSENSE5_OK == irsense5_get_amb_temp ( &irsense5, &temperature ) )
    {
        log_printf( &logger, " Ambient Temperature: %.2f [degC]\r\n", temperature );
        Delay_ms ( 1000 );
    }

    if ( IRSENSE5_OK == irsense5_get_obj_temp ( &irsense5, &temperature ) )
    {
        log_printf( &logger, " Object Temperature:  %.2f [degC]\r\n\n", temperature );
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
