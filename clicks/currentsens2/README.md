
---
# Current Sens 2 Click

> [Current Sens 2 Click](https://www.mikroe.com/?pid_product=MIKROE-6018) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6018&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Nov 2023.
- **Type**          : ADC type

# Software Support

## Example Description

> This example demonstrates the use of Current Sens 2 Click board by reading and
  displaying the input current measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CurrentSens2

### Example Key Functions

- `currentsens2_cfg_setup` Config Object Initialization function.
```c
void currentsens2_cfg_setup ( currentsens2_cfg_t *cfg );
```

- `currentsens2_init` Initialization function.
```c
err_t currentsens2_init ( currentsens2_t *ctx, currentsens2_cfg_t *cfg );
```

- `currentsens2_get_int_pin` Current Sens 2 get int pin state function.
```c
uint8_t currentsens2_get_int_pin ( currentsens2_t *ctx );
```

- `currentsens2_tare` Current Sens 2 tare function.
```c
err_t currentsens2_tare ( currentsens2_t *ctx );
```

- `currentsens2_get_current` Current Sens 2 read current function.
```c
err_t currentsens2_get_current ( currentsens2_t *ctx, float *current );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    currentsens2_cfg_t currentsens2_cfg;  /**< Click config object. */

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
    currentsens2_cfg_setup( &currentsens2_cfg );
    CURRENTSENS2_MAP_MIKROBUS( currentsens2_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == currentsens2_init( &currentsens2, &currentsens2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, " Remove Click from the electrical circuit \r\n" );
    Delay_ms ( 1000 );
    if ( CURRENTSENS2_ERROR == currentsens2_tare ( &currentsens2 ) )
    {
        log_error( &logger, " Click tare error." );
        for ( ; ; );
    }

    currentsens2_set_prim_turn_no( &currentsens2, CURRENTSENS2_NUM_OF_PASSES_1 );

    log_printf( &logger, " Connect Click to the electrical circuit \r\n" );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the input current measurements and displays the results on the USB UART
  approximately once per second.

```c
void application_task ( void ) 
{
    float current = 0;
    if ( CURRENTSENS2_OK == currentsens2_get_current ( &currentsens2, &current ) ) 
    {
        log_printf( &logger, " Current : %.2f[A]\r\n\n", current );
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
