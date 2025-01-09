
---
# Current Limit 7 Click

> [Current Limit 7 Click](https://www.mikroe.com/?pid_product=MIKROE-4972) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4972&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for the Current Limit 7 Click driver.
> This driver provides the functions to set the current limiting conditions 
> in order to provide the threshold of the fault conditions.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CurrentLimit7

### Example Key Functions

- `currentlimit7_cfg_setup` Config Object Initialization function.
```c
void currentlimit7_cfg_setup ( currentlimit7_cfg_t *cfg );
```

- `currentlimit7_init` Initialization function.
```c
err_t currentlimit7_init ( currentlimit7_t *ctx, currentlimit7_cfg_t *cfg );
```

- `currentlimit7_default_cfg` Click Default Configuration function.
```c
err_t currentlimit7_default_cfg ( currentlimit7_t *ctx );
```

- `currentlimit7_set_current_limit` Current Limit 7 set current limit function.
```c
err_t currentlimit7_set_current_limit ( currentlimit7_t *ctx, uint8_t op_mode, uint16_t current_limit_ma );
```

- `currentlimit7_set_resistance` Current Limit 7 set resistance function.
```c
err_t currentlimit7_set_resistance ( currentlimit7_t *ctx, uint32_t res_ohm );
```

- `currentlimit7_get_fault` Current Limit 7 get fault function.
```c
uint8_t currentlimit7_get_fault ( currentlimit7_t *ctx );
```

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization, default settings turn on the device.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    currentlimit7_cfg_t currentlimit7_cfg;  /**< Click config object. */

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
    currentlimit7_cfg_setup( &currentlimit7_cfg );
    CURRENTLIMIT7_MAP_MIKROBUS( currentlimit7_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == currentlimit7_init( &currentlimit7, &currentlimit7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CURRENTLIMIT7_ERROR == currentlimit7_default_cfg ( &currentlimit7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------------\r\n" );
    log_printf( &logger, "   Current Limit 7 Click   \r\n" );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms ( 100 );
    
#ifdef CURRENTLIMIT_MODE_250_mA_500_mA
    currentlimit7_set_current_limit ( &currentlimit7, CURRENTLIMIT7_OP_MODE_250_mA_500_mA, limit_value_op[ 10 ] );
    log_printf( &logger, "  >>> Selected mode %d     \r\n", 0 );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    log_printf( &logger, " Current limit is %d mA    \r\n", limit_value_op[ 10 ] );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms ( 100 );
#else
    currentlimit7_set_current_limit ( &currentlimit7, CURRENTLIMIT7_OP_MODE_500_mA_2500_mA, limit_value_op[ 0 ] );
    log_printf( &logger, "  >>> Selected mode %d     \r\n", 0 );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    log_printf( &logger, " Current limit is %d mA    \r\n", limit_value_op[ 0 ] );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms ( 100 );
#endif
    
    display_selection( );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the Current Limit 7 Click board&trade;.
> Reading user's input from Usart Terminal and using it as an index 
> for an array of pre-calculated values that define the current limit level.
> Results are being sent to the Usart Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    static char index;
    
    if ( CURRENTLIMIT7_ERROR != log_read( &logger, &index, 1 ) ) 
    {
    #ifdef CURRENTLIMIT_MODE_250_mA_500_mA
        if ( ( index >= '0' ) && ( index <= '3' ) )
        {
            currentlimit7_set_current_limit ( &currentlimit7, CURRENTLIMIT7_OP_MODE_250_mA_500_mA, limit_value_op[ index - 38 ] );
            log_printf( &logger, "  >>> Selected mode %d     \r\n", index - 48 );
            log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
            log_printf( &logger, "  Current limit is %d mA   \r\n", limit_value_op[ index - 38 ] );
            log_printf( &logger, "---------------------------\r\n" );
            Delay_ms ( 100 );
        }
    #else
        if ( ( index >= '0' ) && ( index <= '9' ) ) 
        {
            currentlimit7_set_current_limit ( &currentlimit7, CURRENTLIMIT7_OP_MODE_500_mA_2500_mA, limit_value_op[ index - 48 ] );
            log_printf( &logger, "  >>> Selected mode %d     \r\n", index - 48 );
            log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
            log_printf( &logger, "  Current limit is %d mA   \r\n", limit_value_op[ index - 48 ] );
            log_printf( &logger, "---------------------------\r\n" );
            Delay_ms ( 100 );
        }
    #endif
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
