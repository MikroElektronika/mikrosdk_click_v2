
---
# eFuse 7 Click

> [eFuse 7 Click](https://www.mikroe.com/?pid_product=MIKROE-5738) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5738&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : May 2023.
- **Type**          : GPIO type

# Software Support

## Example Description

> This library contains API for the eFuse 7 Click driver.
  This driver provides the functions to set the current limiting conditions 
  in order to provide the threshold of the fault conditions.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.eFuse7

### Example Key Functions

- `efuse7_cfg_setup` Config Object Initialization function.
```c
void efuse7_cfg_setup ( efuse7_cfg_t *cfg );
```

- `efuse7_init` Initialization function.
```c
err_t efuse7_init ( efuse7_t *ctx, efuse7_cfg_t *cfg );
```

- `efuse7_default_cfg` Click Default Configuration function.
```c
err_t efuse7_default_cfg ( efuse7_t *ctx );
```

- `efuse7_enable_output` eFuse 7 output enable function.
```c
void efuse7_enable_output ( efuse7_t *ctx );
```

- `efuse7_wiper_inc` eFuse 7 wiper position increase function.
```c
void efuse7_wiper_inc ( efuse7_t *ctx, uint8_t inc_num );
```

- `efuse7_set_limit` eFuse 7 set current limit function.
```c
err_t efuse7_set_limit ( efuse7_t *ctx, uint8_t set_current );
```

### Application Init

> Initialization of Click module and UART log, then performing default 
  configuration and setting a current limit to 1A.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    efuse7_cfg_t efuse7_cfg;  /**< Click config object. */

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
    efuse7_cfg_setup( &efuse7_cfg );
    EFUSE7_MAP_MIKROBUS( efuse7_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == efuse7_init( &efuse7, &efuse7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EFUSE7_ERROR == efuse7_default_cfg ( &efuse7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    display_selection( );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the eFuse 7 Click board.
  Reading user's input from UART Terminal and using it as an index 
  for an array of pre-calculated values that define the current limit level.
  Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    static char index;
    
    if ( 1 == log_read( &logger, &index, 1 ) ) 
    {
        if ( ( index >= '0' ) && ( index <= '7' ) ) 
        {
            efuse7_set_limit ( &efuse7, limit_value_op[ index - 48 ] );
            log_printf( &logger, "  >>> Selected mode %c     \r\n", index );
            log_printf( &logger, "---------------------------\r\n" );
            Delay_ms ( 100 );
        }
        else 
        { 
            log_printf( &logger, "    Data not in range!    \r\n" );
            log_printf( &logger, "---------------------------\r\n" );
            display_selection( );
            Delay_ms ( 100 );
        }
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
