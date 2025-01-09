
---
# ADC 19 Click

> [ADC 19 Click](https://www.mikroe.com/?pid_product=MIKROE-4997) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4997&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2022.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of ADC 19 Click board by reading the voltage from the two analog input channels.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC19

### Example Key Functions

- `adc19_cfg_setup` Config Object Initialization function.
```c
void adc19_cfg_setup ( adc19_cfg_t *cfg );
```

- `adc19_init` Initialization function.
```c
err_t adc19_init ( adc19_t *ctx, adc19_cfg_t *cfg );
```

- `adc19_set_vref` This function sets the voltage reference value that will be used for voltage calculation.
```c
void adc19_set_vref ( adc19_t *ctx, float vref );
```

- `adc19_set_input_channel` This function sets the selected input channel active by modifying the control register.
```c
err_t adc19_set_input_channel ( adc19_t *ctx, uint8_t input_ch );
```

- `adc19_get_voltage` This function reads the voltage from the previously selected channel by using SPI serial interface.
```c
err_t adc19_get_voltage ( adc19_t *ctx, float *voltage );
```

### Application Init

> Initializes the driver and logger and sets the ADC voltage reference.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc19_cfg_t adc19_cfg;  /**< Click config object. */

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
    adc19_cfg_setup( &adc19_cfg );
    ADC19_MAP_MIKROBUS( adc19_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == adc19_init( &adc19, &adc19_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    adc19_set_vref ( &adc19, ADC19_VREF_3V3 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and displays the voltage from the two analog input channels on the USB UART approximately every 500ms.

```c
void application_task ( void )
{
    float voltage;
    if ( ADC19_OK == adc19_set_input_channel ( &adc19, ADC19_INPUT_CHANNEL_1 ) )
    {
        if ( ADC19_OK == adc19_get_voltage ( &adc19, &voltage ) )
        {
            log_printf ( &logger, " IN1 : %.3f V \r\n", voltage );
        }
    }
    if ( ADC19_OK == adc19_set_input_channel ( &adc19, ADC19_INPUT_CHANNEL_2 ) )
    {
        if ( ADC19_OK == adc19_get_voltage ( &adc19, &voltage ) )
        {
            log_printf ( &logger, " IN2 : %.3f V \r\n\n", voltage );
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
