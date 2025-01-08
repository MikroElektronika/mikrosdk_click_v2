
---
# ISO ADC 6 Click

> [ISO ADC 6 Click](https://www.mikroe.com/?pid_product=MIKROE-5901) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5901&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Sep 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the ISO ADC 6 Click board&trade; 
> by reading and writing data by using SPI serial interface 
> and reading results of AD conversion.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ISOADC6

### Example Key Functions

- `isoadc6_cfg_setup` Config Object Initialization function.
```c
void isoadc6_cfg_setup ( isoadc6_cfg_t *cfg );
```

- `isoadc6_init` Initialization function.
```c
err_t isoadc6_init ( isoadc6_t *ctx, isoadc6_cfg_t *cfg );
```

- `isoadc6_default_cfg` Click Default Configuration function.
```c
err_t isoadc6_default_cfg ( isoadc6_t *ctx );
```

- `isoadc6_get_voltage` ISO ADC 6 get voltage level function.
```c
err_t isoadc6_get_voltage ( isoadc6_t* ctx, float *voltage );
```

- `isoadc6_get_adc_data` ISO ADC 6 get ADC data function.
```c
err_t isoadc6_get_adc_data ( isoadc6_t* ctx, uint32_t *adc_data );
```

- `isoadc6_set_adc_control` ISO ADC 6 set ADC control function.
```c
err_t isoadc6_set_adc_control ( isoadc6_t* ctx, uint16_t adc_ctrl_data );
```

### Application Init

> Initialization of SPI module and log UART.
> After driver initialization, the app executes a default configuration which enables channel 0,
> puts A0 on positive analog input and A1 on negative analog input,
> enables internal reference voltage (approximately 2.65V (AVDD = 3.3V)),
> and also enables bipolar operation mode and puts device on full power mode.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    isoadc6_cfg_t isoadc6_cfg;  /**< Click config object. */

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
    isoadc6_cfg_setup( &isoadc6_cfg );
    ISOADC6_MAP_MIKROBUS( isoadc6_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == isoadc6_init( &isoadc6, &isoadc6_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ISOADC6_ERROR == isoadc6_default_cfg ( &isoadc6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> The demo application reads the voltage levels from analog input (A0-A1) and displays the results.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    float voltage = 0;
    if ( ISOADC6_OK == isoadc6_get_voltage( &isoadc6, &voltage ) )
    {
        log_printf( &logger, " Voltage: %.3f [V]\r\n", voltage );
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
