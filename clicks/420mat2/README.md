
---
# 4-20mA T 2 Click

> [4-20mA T 2 Click](https://www.mikroe.com/?pid_product=MIKROE-5540) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5540&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of 4-20mA T 2 Click board&trade;.
> This driver provides functions to configure 
> analog output current transfer over an industry standard 4-20mA current loop.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.c420mAT2

### Example Key Functions

- `c420mat2_cfg_setup` Config Object Initialization function.
```c
void c420mat2_cfg_setup ( c420mat2_cfg_t *cfg );
```

- `c420mat2_init` Initialization function.
```c
err_t c420mat2_init ( c420mat2_t *ctx, c420mat2_cfg_t *cfg );
```

- `c420mat2_default_cfg` Click Default Configuration function.
```c
err_t c420mat2_default_cfg ( c420mat2_t *ctx );
```

- `c420mat2_set_output_current` 4-20mA T 2 set output current function.
```c
err_t c420mat2_set_output_current ( c420mat2_t *ctx, float current_ma );
```

- `c420mat2_get_status` 4-20mA T 2 set status function.
```c
err_t c420mat2_get_status ( c420mat2_t *ctx, c420mat2_status_t *status );
```

- `c420mat2_set_lower_limit` 4-20mA T 2 set lower limit function.
```c
err_t c420mat2_set_lower_limit ( c420mat2_t *ctx, float lower_limit_ma );
```

### Application Init

> Initialization of SPI module and log UART.
> After driver initialization, default settings turn on the device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c420mat2_cfg_t c420mat2_cfg;  /**< Click config object. */

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
    c420mat2_cfg_setup( &c420mat2_cfg );
    C420MAT2_MAP_MIKROBUS( c420mat2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == c420mat2_init( &c420mat2, &c420mat2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( C420MAT2_ERROR == c420mat2_default_cfg ( &c420mat2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    log_printf( &logger, " -----------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the 4-20mA T 2 Click board&trade;.
> This example periodically changes the analog output current transfer 
> from 4mA to 20mA and display status every 5 seconds.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    if ( C420MAT2_OK == c420mat2_set_output_current( &c420mat2, 4.0 ) )
    {
        log_printf( &logger, " Loop Current:  4.0 mA \r\n" );
        log_printf( &logger, " - - - - - - - - - - - - - - -\r\n" );
        if ( C420MAT2_OK == c420mat2_get_status ( &c420mat2, &status ) )
        {
            display_status( );    
        }
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }

    if ( C420MAT2_OK == c420mat2_set_output_current( &c420mat2, 10.0 ) )
    {
        log_printf( &logger, " Loop Current: 10.0 mA \r\n" );
        log_printf( &logger, " - - - - - - - - - - - - - - -\r\n" );
        if ( C420MAT2_OK == c420mat2_get_status ( &c420mat2, &status ) )
        {
            display_status( );    
        }
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }

    if ( C420MAT2_OK == c420mat2_set_output_current( &c420mat2, 15.0 ) )
    {
        log_printf( &logger, " Loop Current: 15.0 mA \r\n" );
        log_printf( &logger, " - - - - - - - - - - - - - - -\r\n" );
        if ( C420MAT2_OK == c420mat2_get_status ( &c420mat2, &status ) )
        {
            display_status( );    
        }
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }

    if ( C420MAT2_OK == c420mat2_set_output_current( &c420mat2, 20.0 ) )
    {
        log_printf( &logger, " Loop Current: 20.0 mA \r\n" );
        log_printf( &logger, " - - - - - - - - - - - - - - -\r\n" );
        if ( C420MAT2_OK == c420mat2_get_status ( &c420mat2, &status ) )
        {
            display_status( );    
        }
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
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
