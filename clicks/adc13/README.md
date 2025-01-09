
---
# ADC 13 Click

> [ADC 13 Click](https://www.mikroe.com/?pid_product=MIKROE-4743) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4743&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of ADC 13 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC13

### Example Key Functions

- `adc13_cfg_setup` Config Object Initialization function.
```c
void adc13_cfg_setup ( adc13_cfg_t *cfg );
```

- `adc13_init` Initialization function.
```c
err_t adc13_init ( adc13_t *ctx, adc13_cfg_t *cfg );
```

- `adc13_default_cfg` Click Default Configuration function.
```c
err_t adc13_default_cfg ( adc13_t *ctx );
```

- `adc13_measure_voltage` This function starts ADC conversation, reads RAW ADC data then calculates the voltage using the input vref for calculations.
```c
err_t adc13_measure_voltage ( adc13_t *ctx, float vref, float *voltage );
```

- `adc13_measure_temperature` This function measures the internal temperature in Celsius.
```c
err_t adc13_measure_temperature ( adc13_t *ctx, float *temperature );
```

- `adc13_set_input_channel` This function sets the ADC input positive and negative channels.
```c
err_t adc13_set_input_channel ( adc13_t *ctx, uint8_t pos, uint8_t neg );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    adc13_cfg_t adc13_cfg;  /**< Click config object. */

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

    adc13_cfg_setup( &adc13_cfg );
    ADC13_MAP_MIKROBUS( adc13_cfg, MIKROBUS_1 );
    err_t init_flag  = adc13_init( &adc13, &adc13_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    adc13_default_cfg ( &adc13 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the voltage between AIN0 and AIN1 channels, and the module internal temperature as well. 
> All values are being displayed on the USB UART where you can track their changes.

```c
void application_task ( void )
{
    float voltage = 0;
    float temperature = 0;
    
    adc13_measure_voltage ( &adc13, ADC13_VREF_INTERNAL, &voltage );
    log_printf( &logger, " Voltage: %.3f V\r\n", voltage );
    adc13_measure_temperature ( &adc13, &temperature );
    log_printf( &logger, " Temperature: %.2f C\r\n", temperature );
    log_printf( &logger, " ---------------------------\r\n" );
    
    Delay_ms ( 500 );
}
```

### Note

> An internal 2.5V reference is set by default. 
> If you want, you can change it using the adc13_set_voltage_reference function.

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
