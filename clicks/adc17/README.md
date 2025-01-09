
---
# ADC 17 Click

> [ADC 17 Click](https://www.mikroe.com/?pid_product=MIKROE-4966) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4966&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of ADC 17 Click board by reading the voltage from the two analog input channels.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC17

### Example Key Functions

- `adc17_cfg_setup` Config Object Initialization function.
```c
void adc17_cfg_setup ( adc17_cfg_t *cfg );
```

- `adc17_init` Initialization function.
```c
err_t adc17_init ( adc17_t *ctx, adc17_cfg_t *cfg );
```

- `adc17_default_cfg` Click Default Configuration function.
```c
err_t adc17_default_cfg ( adc17_t *ctx );
```

- `adc17_set_channel` This function sets the selected channel active by modifying the config byte.
```c
err_t adc17_set_channel ( adc17_t *ctx, uint8_t channel );
```

- `adc17_get_voltage` This function reads the voltage from the previously selected channel by using I2C serial interface.
```c
err_t adc17_get_voltage ( adc17_t *ctx, float *voltage );
```

- `adc17_write_setup_byte` This function writes a setup byte to the ADC chip by using I2C serial interface.
```c
err_t adc17_write_setup_byte ( adc17_t *ctx, uint8_t setup_byte );
```

### Application Init

> Initializes the driver and performs the Click default configuration which sets the input channels to single-ended unipolar mode.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc17_cfg_t adc17_cfg;  /**< Click config object. */

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
    adc17_cfg_setup( &adc17_cfg );
    ADC17_MAP_MIKROBUS( adc17_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == adc17_init( &adc17, &adc17_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ADC17_ERROR == adc17_default_cfg ( &adc17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and displays the voltage from the two analog input channels on the USB UART approximately every 500ms.

```c
void application_task ( void )
{
    float voltage;
    if ( ADC17_OK == adc17_set_channel ( &adc17, ADC17_CHANNEL_0 ) )
    {
        if ( ADC17_OK == adc17_get_voltage ( &adc17, &voltage ) )
        {
            log_printf ( &logger, " AIN0 voltage: %.3f V \r\n\n", voltage );
        }
    }
    if ( ADC17_OK == adc17_set_channel ( &adc17, ADC17_CHANNEL_1 ) )
    {
        if ( ADC17_OK == adc17_get_voltage ( &adc17, &voltage ) )
        {
            log_printf ( &logger, " AIN1 voltage: %.3f V \r\n\n", voltage );
        }
    }
    Delay_ms ( 500 );
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
