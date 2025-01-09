
---
# ADC 11 Click

> [ADC 11 Click](https://www.mikroe.com/?pid_product=MIKROE-4593) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4593&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Feb 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This library contains API for ADC 11 Click driver.
> The library contains drivers for measuring ADC values  
> and for calculation voltage.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Adc11

### Example Key Functions

- `adc11_cfg_setup` Config Object Initialization function.
```c
void adc11_cfg_setup ( adc11_cfg_t *cfg );
```

- `adc11_init` Initialization function.
```c
err_t adc11_init ( adc11_t *ctx, adc11_cfg_t *cfg );
```

- `adc11_default_cfg` Click Default Configuration function.
```c
void adc11_default_cfg ( adc11_t *ctx );
```

- `adc11_generic_read` ADC 11 data reading function.
```c
err_t adc11_generic_read ( adc11_t *ctx, uint16_t *adc_data );
```

- `adc11_set_calibration` ADC 11 set calibration function.
```c
err_t adc11_set_calibration ( adc11_t *ctx, adc11_calibration_data_t *adc_val );
```

- `adc11_get_voltage` ADC 11 get voltage function.
```c
err_t adc11_get_voltage ( adc11_t *ctx, adc11_calibration_data_t *adc_val, float *voltage );
```

### Application Init

> Initializes SPI driver and triggers the built-in calibration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    adc11_cfg_t adc11_cfg;  /**< Click config object. */

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

    // Click initialization.

    adc11_cfg_setup( &adc11_cfg );
    ADC11_MAP_MIKROBUS( adc11_cfg, MIKROBUS_1 );
    err_t init_flag  = adc11_init( &adc11, &adc11_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_printf( &logger, "---------------------------\r\n");
    log_printf( &logger, "        Calibration        \r\n");
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n");
    log_printf( &logger, "> Turn OFF the Power unit <\r\n");
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n");
    log_printf( &logger, "  In the following 5 sec.  \r\n");
    log_printf( &logger, " turn OFF the Power Supply \r\n");
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "    Start calibration    \r\n");
    
    if ( adc11_set_calibration( &adc11, &avg_adc_data ) == ADC11_OK ) {
        log_printf( &logger, "---------------------------\r\n");
        log_printf( &logger, "    Calibration  Done    \r\n");
        Delay_ms ( 1000 );    
    }
    
    log_printf( &logger, "---------------------------\r\n");
    log_printf( &logger, "    Start measurements :   \r\n");
    log_printf( &logger, "---------------------------\r\n");
}
```

### Application Task

> This is an example that demonstrates the use of the ADC 11 Click board.
> In this example, we monitor and display voltage [ V ].
> Results are being sent to the Usart Terminal, where you can track their changes.
> All data logs write on USB UART changes every 2 sec.

```c
void application_task ( void ) 
{
    adc11_get_voltage( &adc11, &avg_adc_data, &voltage );
    log_printf( &logger, "     Volatge : %.3f V      \r\n", voltage );
    log_printf( &logger, "---------------------------\r\n");
    Delay_ms ( 1000 );
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
