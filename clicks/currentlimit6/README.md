
---
# Current Limit 6 Click

> [Current Limit 6 Click](https://www.mikroe.com/?pid_product=MIKROE-4915) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4915&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Oct 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This library contains API for the Current Limit 6 Click driver.
> This driver provides the functions to set the current limiting conditions 
> in order to provide the threshold of the fault conditions.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CurrentLimit6

### Example Key Functions

- `currentlimit6_cfg_setup` Config Object Initialization function.
```c
void currentlimit6_cfg_setup ( currentlimit6_cfg_t *cfg );
```

- `currentlimit6_init` Initialization function.
```c
err_t currentlimit6_init ( currentlimit6_t *ctx, currentlimit6_cfg_t *cfg );
```

- `currentlimit6_default_cfg` Click Default Configuration function.
```c
err_t currentlimit6_default_cfg ( currentlimit6_t *ctx );
```

- `currentlimit6_set_current_limit` Current Limit 6 set current limit function.
```c
err_t currentlimit6_set_current_limit ( currentlimit6_t *ctx, float current_limit );
```

- `currentlimit6_power_mode` Current Limit 6 power mode function.
```c
err_t currentlimit6_power_mode ( currentlimit6_t *ctx, currentlimit6_pwr_mode_value_t pwr_mode );
```

- `currentlimit6_check_limit_exceeded` Current Limit 6 check limit exceeded function.
```c
uint8_t currentlimit6_check_limit_exceeded ( currentlimit6_t *ctx );
```

### Application Init

> Initialization of SPI module and log UART.
> After driver initialization, default settings turn on the device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    currentlimit6_cfg_t currentlimit6_cfg;  /**< Click config object. */

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
    currentlimit6_cfg_setup( &currentlimit6_cfg );
    CURRENTLIMIT6_MAP_MIKROBUS( currentlimit6_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == currentlimit6_init( &currentlimit6, &currentlimit6_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CURRENTLIMIT6_ERROR == currentlimit6_default_cfg ( &currentlimit6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "  Current Limit 6 Click  \r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    Delay_ms ( 100 );
    
    display_selection( );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the Current Limit 6 Click board&trade;.
> Reading user's input from Usart Terminal and using it as an index 
> for an array of pre-calculated values that define the current limit level.
> Results are being sent to the Usart Terminal, where you can track their changes.

```c
void application_task ( void )
{ 
    static char index;
    
    if ( log_read( &logger, &index, 1 ) != CURRENTLIMIT6_ERROR ) 
    {
        if ( ( index >= '1' ) && ( index <= '9' ) ) 
        {
            currentlimit6_set_current_limit ( &currentlimit6, limit_value[ index - 49 ] );
            log_printf( &logger, "  >>> Selected mode %d     \r\n", index - 48 );
            log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
            log_printf( &logger, " Current limit is %.3f A \r\n", limit_value[ index - 49 ] );
            log_printf( &logger, "--------------------------\r\n" );
            Delay_ms ( 100 );
        } 
        else 
        { 
            log_printf( &logger, "    Data not in range!    \r\n" );
            log_printf( &logger, "--------------------------\r\n" );
            display_selection( );
            Delay_ms ( 100 );
        }
    }
}
```

## Additional Function
- `display_selection` This function displays selection messages.
```c
static void display_selection ( void );
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
