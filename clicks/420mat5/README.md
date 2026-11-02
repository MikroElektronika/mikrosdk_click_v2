
---
# 4-20mA T 5 Click

> [4-20mA T 5 Click](https://www.mikroe.com/?pid_product=MIKROE-7100) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7100&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Aug 2026.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of 4-20mA T 5 Click board by setting the
analog output current of an industry standard 4-20mA current loop.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.420mAT5

### Example Key Functions

- `c420mat5_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void c420mat5_cfg_setup ( c420mat5_cfg_t *cfg );
```

- `c420mat5_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t c420mat5_init ( c420mat5_t *ctx, c420mat5_cfg_t *cfg );
```

- `c420mat5_default_cfg` This function executes a default configuration of 4-20mA T 5 Click board.
```c
err_t c420mat5_default_cfg ( c420mat5_t *ctx );
```

- `c420mat5_set_output_current` This function sets the analog output current of the current loop.
```c
err_t c420mat5_set_output_current ( c420mat5_t *ctx, float current_ma );
```

- `c420mat5_enable_output` This function enables the loop output by setting the OD pin to the low logic level.
```c
void c420mat5_enable_output ( c420mat5_t *ctx );
```

- `c420mat5_disable_output` This function disables the loop output by setting the OD pin to the high logic level.
```c
void c420mat5_disable_output ( c420mat5_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c420mat5_cfg_t c420mat5_cfg;  /**< Click config object. */

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
    c420mat5_cfg_setup( &c420mat5_cfg );
    C420MAT5_MAP_MIKROBUS( c420mat5_cfg, MIKROBUS_POSITION_C420MAT5 );
    if ( SPI_MASTER_ERROR == c420mat5_init( &c420mat5, &c420mat5_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C420MAT5_ERROR == c420mat5_default_cfg ( &c420mat5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Sweeps the loop output current from 4mA to 20mA in 4mA steps
and displays the selected current and the error flag state on the USB UART.

```c
void application_task ( void )
{
    for ( uint8_t cnt = 0; C420MAT5_DEMO_STEPS > cnt; cnt++ )
    {
        if ( C420MAT5_OK == c420mat5_set_output_current( &c420mat5, demo_current[ cnt ] ) )
        {
            log_printf( &logger, " Loop current: %.2f mA\r\n", demo_current[ cnt ] );
        }
        else
        {
            log_error( &logger, " Failed to set output current." );
        }
        if ( C420MAT5_ERR_FLAG_ACTIVE == c420mat5_get_err_pin( &c420mat5 ) )
        {
            log_printf( &logger, " Error flag is active\r\n" );
        }
        log_printf( &logger, " --------------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
}
```

### Note

> The JP2 jumper must be in the VCC position in order to select the current
output mode. An external power supply from 8V to 60V must be connected to
the TB3 terminal and the current loop to the TB2 terminal.

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
