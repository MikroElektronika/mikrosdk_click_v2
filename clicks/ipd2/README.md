
---
# IPD 2 Click

> [IPD 2 Click](https://www.mikroe.com/?pid_product=MIKROE-6314) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6314&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2024.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of IPD 2 Click by toggling the output state.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.IPD2

### Example Key Functions

- `ipd2_cfg_setup` Config Object Initialization function.
```c
void ipd2_cfg_setup ( ipd2_cfg_t *cfg );
```

- `ipd2_init` Initialization function.
```c
err_t ipd2_init ( ipd2_t *ctx, ipd2_cfg_t *cfg );
```

- `ipd2_enable_out1` This function enables OUT1 by setting the IN1 pin to high logic state.
```c
void ipd2_enable_out1 ( ipd2_t *ctx );
```

- `ipd2_disable_out1` This function disables OUT1 by setting the IN1 pin to low logic state.
```c
void ipd2_disable_out1 ( ipd2_t *ctx );
```

- `ipd2_get_st1_pin` This function returns the ST1 pin logic state.
```c
uint8_t ipd2_get_st1_pin ( ipd2_t *ctx );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ipd2_cfg_t ipd2_cfg;  /**< Click config object. */

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
    ipd2_cfg_setup( &ipd2_cfg );
    IPD2_MAP_MIKROBUS( ipd2_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == ipd2_init( &ipd2, &ipd2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Toggles OUT1 and OUT2 state every 3 seconds and displays both outputs state and
status diagnostics pin state. If the status pin is HIGH it indicates that the fault
condition on this output has occurred and the output is disabled.

```c
void application_task ( void )
{
    ipd2_enable_out1 ( &ipd2 );
    ipd2_disable_out2 ( &ipd2 );
    Delay_ms ( 100 );
    log_printf( &logger, " OUT1: enabled\r\n" );
    log_printf( &logger, " OUT2: disabled\r\n" );
    log_printf( &logger, " ST1: %s\r\n", ( char * ) ( ipd2_get_st1_pin ( &ipd2 ) ? "high" : "low" ) );
    log_printf( &logger, " ST2: %s\r\n\n", ( char * ) ( ipd2_get_st2_pin ( &ipd2 ) ? "high" : "low" ) );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    ipd2_disable_out1 ( &ipd2 );
    ipd2_enable_out2 ( &ipd2 );
    Delay_ms ( 100 );
    log_printf( &logger, " OUT1: disabled\r\n" );
    log_printf( &logger, " OUT2: enabled\r\n" );
    log_printf( &logger, " ST1: %s\r\n", ( char * ) ( ipd2_get_st1_pin ( &ipd2 ) ? "high" : "low" ) );
    log_printf( &logger, " ST2: %s\r\n\n", ( char * ) ( ipd2_get_st2_pin ( &ipd2 ) ? "high" : "low" ) );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
