
---
# Brushless 12 Click

> [Brushless 12 Click](https://www.mikroe.com/?pid_product=MIKROE-4357) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4357&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2021.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of Brushless 12 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless12

### Example Key Functions

- `brushless12_cfg_setup` Config Object Initialization function.
```c
void brushless12_cfg_setup ( brushless12_cfg_t *cfg );
```

- `brushless12_init` Initialization function.
```c
err_t brushless12_init ( brushless12_t *ctx, brushless12_cfg_t *cfg );
```

- `brushless12_default_cfg` Click Default Configuration function.
```c
void brushless12_default_cfg ( brushless12_t *ctx );
```

- `brushless12_set_brake` This function sets the BRK pin to the desired state.
```c
void brushless12_set_brake ( brushless12_t *ctx, uint8_t state );
```

- `brushless12_set_direction` This function sets the F/R pin to the desired state.
```c
void brushless12_set_direction ( brushless12_t *ctx, uint8_t state );
```

- `brushless12_set_enable` This function sets the EN pin to the desired state.
```c
void brushless12_set_enable ( brushless12_t *ctx, uint8_t state );
```

### Application Init

> Initializes the driver and sets the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    brushless12_cfg_t brushless12_cfg;  /**< Click config object. */

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

    brushless12_cfg_setup( &brushless12_cfg );
    BRUSHLESS12_MAP_MIKROBUS( brushless12_cfg, MIKROBUS_1 );
    
    if ( brushless12_init( &brushless12, &brushless12_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    brushless12_default_cfg( &brushless12 );
    Delay_ms ( 100 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Drives the motor in the forward direction for 5 seconds, then pulls brake for 2 seconds, 
> and after that drives it in the reverse direction for 5 seconds, and pulls brake for 2 seconds.
> Each step will be logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    log_printf( &logger, "The motor turns forward! \r\n" );
    brushless12_set_direction ( &brushless12, BRUSHLESS12_DIR_FORWARD );
    brushless12_set_brake ( &brushless12, BRUSHLESS12_START );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "Pull brake! \r\n" );
    brushless12_set_brake ( &brushless12, BRUSHLESS12_BRAKE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "The motor turns in reverse! \r\n" );
    brushless12_set_direction ( &brushless12, BRUSHLESS12_DIR_REVERSE );
    brushless12_set_brake ( &brushless12, BRUSHLESS12_START );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "Pull brake! \r\n" );
    brushless12_set_brake ( &brushless12, BRUSHLESS12_BRAKE );
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
