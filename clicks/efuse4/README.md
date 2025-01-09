
---
# eFuse 4 Click

> [eFuse 4 Click](https://www.mikroe.com/?pid_product=MIKROE-5501) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5501&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for the eFuse 4 Click driver.
> This driver provides the functions to set the current limiting conditions 
> in order to provide the threshold of the fault conditions.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.eFuse4

### Example Key Functions

- `efuse4_cfg_setup` Config Object Initialization function.
```c
void efuse4_cfg_setup ( efuse4_cfg_t *cfg );
```

- `efuse4_init` Initialization function.
```c
err_t efuse4_init ( efuse4_t *ctx, efuse4_cfg_t *cfg );
```

- `efuse4_default_cfg` Click Default Configuration function.
```c
err_t efuse4_default_cfg ( efuse4_t *ctx );
```

- `efuse4_set_current_limit` eFuse 4 set current limit function.
```c
err_t efuse4_set_current_limit ( efuse4_t *ctx, efuse4_current_limit_t current_limit )
```

- `efuse4_set_resistance` eFuse 4 set resistance function.
```c
err_t efuse4_set_resistance ( efuse4_t *ctx, uint32_t res_ohm );
```

- `efuse4_set_digi_pot` eFuse 4 set normal mode function.
```c
void efuse4_set_normal_mode ( efuse4_t *ctx );
```

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization, default settings turn on the device.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    efuse4_cfg_t efuse4_cfg;  /**< Click config object. */

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
    efuse4_cfg_setup( &efuse4_cfg );
    EFUSE4_MAP_MIKROBUS( efuse4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == efuse4_init( &efuse4, &efuse4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EFUSE4_ERROR == efuse4_default_cfg ( &efuse4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms ( 100 );
    
    display_selection( );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the eFuse 4 Click board&trade;.
> Reading user's input from UART Terminal and using it as an index 
> for an array of pre-calculated values that define the current limit level.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{  
    static char index;
    
    if ( EFUSE4_ERROR != log_read( &logger, &index, 1 ) ) 
    {
        if ( ( index >= '0' ) && ( index <= '6' ) ) 
        {
            efuse4_set_current_limit ( &efuse4, limit_value_op[ index - 48 ] );
            log_printf( &logger, "  >>> Selected mode %d     \r\n", index - 48 );
            log_printf( &logger, "  Current limit is %d mA   \r\n", limit_value_op[ index - 48 ] );
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
