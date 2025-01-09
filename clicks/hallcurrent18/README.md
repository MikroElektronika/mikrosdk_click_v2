
---
# Hall Current 18 Click

> [Hall Current 18 Click](https://www.mikroe.com/?pid_product=MIKROE-5832) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5832&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Aug 2023.
- **Type**          : ADC/I2C type

# Software Support

## Example Description

> This example demonstrates the use of Hall Current 18 Click board&trade; 
> by reading and displaying the current measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent18

### Example Key Functions

- `hallcurrent18_cfg_setup` Config Object Initialization function.
```c
void hallcurrent18_cfg_setup ( hallcurrent18_cfg_t *cfg );
```

- `hallcurrent18_init` Initialization function.
```c
err_t hallcurrent18_init ( hallcurrent18_t *ctx, hallcurrent18_cfg_t *cfg );
```

- `hallcurrent18_default_cfg` Click Default Configuration function.
```c
err_t hallcurrent18_default_cfg ( hallcurrent18_t *ctx );
```

- `hallcurrent18_read_current` Hall Current 18 read current function.
```c
err_t hallcurrent18_read_current ( hallcurrent18_t *ctx, float *current );
```

- `hallcurrent18_read_voltage` Hall Current 18 read voltage level function.
```c
err_t hallcurrent18_read_voltage ( hallcurrent18_t *ctx, float *voltage );
```

- `hallcurrent18_read_raw_adc` Hall Current 18 read raw ADC value function.
```c
err_t hallcurrent18_read_raw_adc ( hallcurrent18_t *ctx, uint16_t *raw_adc );
```

### Application Init

> The initialization of SPI module and log UART.
> After driver initialization, the app sets the default configuration
> and set the zero voltage reference.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hallcurrent18_cfg_t hallcurrent18_cfg;  /**< Click config object. */

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
    hallcurrent18_cfg_setup( &hallcurrent18_cfg );
    HALLCURRENT18_MAP_MIKROBUS( hallcurrent18_cfg, MIKROBUS_1 );
    err_t init_flag = hallcurrent18_init( &hallcurrent18, &hallcurrent18_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HALLCURRENT18_ERROR == hallcurrent18_default_cfg ( &hallcurrent18 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    log_printf( &logger, " Turn off the load current in the following 5 sec.\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( HALLCURRENT18_OK == hallcurrent18_set_zero_ref( &hallcurrent18 ) )
    {
        log_printf( &logger, " Process complete!\r\n");
    }
    else
    {
        log_error( &logger, " Zero reference." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application reads the current measurements [A] and displays the results.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    float current = 0;
    if ( HALLCURRENT18_OK == hallcurrent18_read_current ( &hallcurrent18, &current ) ) 
    {
        log_printf( &logger, " Current : %.2f [A]\r\n\n", current );
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
