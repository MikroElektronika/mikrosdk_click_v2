
---
# Hall Current 19 Click

> [Hall Current 19 Click](https://www.mikroe.com/?pid_product=MIKROE-6097) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6097&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Feb 2024.
- **Type**          : ADC type

# Software Support

## Example Description

> This example demonstrates the use of Hall Current 19 Click board
  by reading and displaying the current measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent19

### Example Key Functions

- `hallcurrent19_cfg_setup` Config Object Initialization function.
```c
void hallcurrent19_cfg_setup ( hallcurrent19_cfg_t *cfg );
```

- `hallcurrent19_init` Initialization function.
```c
err_t hallcurrent19_init ( hallcurrent19_t *ctx, hallcurrent19_cfg_t *cfg );
```

- `hallcurrent19_get_oc2` This function is used to get state of the overcurrent 2 detection of the Hall Current 19 Click board.
```c
uint8_t hallcurrent19_get_oc2 ( hallcurrent19_t *ctx );
```

- `hallcurrent19_set_zero_ref` This function sets the zero voltage reference of the Hall Current 19 Click board.
```c
err_t hallcurrent19_set_zero_ref ( hallcurrent19_t *ctx );
```

- `hallcurrent19_get_current` This function reads and calculate input current value of the Hall Current 19 Click board.
```c
err_t hallcurrent19_get_current ( hallcurrent19_t *ctx, float *current );
```

### Application Init

> Initializes the driver and logger, and set the zero voltage reference.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hallcurrent19_cfg_t hallcurrent19_cfg;  /**< Click config object. */

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
    hallcurrent19_cfg_setup( &hallcurrent19_cfg );
    HALLCURRENT19_MAP_MIKROBUS( hallcurrent19_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == hallcurrent19_init( &hallcurrent19, &hallcurrent19_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_printf( &logger, " Turn off the load current in the following 5 sec.\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( HALLCURRENT19_OK == hallcurrent19_set_zero_ref( &hallcurrent19 ) )
    {
        log_printf( &logger, " Process complete!\r\n");
    }
    else
    {
        log_error( &logger, " Zero reference." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> The demo application reads the current measurements [A] and displays the results.
  Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    float voltage = 0;
    if ( HALLCURRENT19_OK == hallcurrent19_get_current ( &hallcurrent19, &voltage ) ) 
    {
        log_printf( &logger, " Current : %.3f[A]\r\n\n", voltage );
        Delay_ms ( 1000 );
    }
    if ( HALLCURRENT19_OCD_ACTIVE == hallcurrent19_get_oc1( &hallcurrent19 ) )
    {
        log_printf( &logger, " Current over 7A \r\n" );
    }
    if ( HALLCURRENT19_OCD_ACTIVE == hallcurrent19_get_oc2( &hallcurrent19 ) )
    {
        log_printf( &logger, " Current over 17.5A \r\n" );
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
