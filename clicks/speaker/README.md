
---
# Speaker Click

> [Speaker Click](https://www.mikroe.com/?pid_product=MIKROE-4662) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4662&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Apr 2021.
- **Type**          : GPIO type

# Software Support

## Example Description

> This library contains API for the Speaker Click driver.
> This application controls the operating modes of the 
> Speaker Click board&trade;.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Speaker

### Example Key Functions

- `speaker_cfg_setup` Config Object Initialization function.
```c
void speaker_cfg_setup ( speaker_cfg_t *cfg );
```

- `speaker_init` Initialization function.
```c
err_t speaker_init ( speaker_t *ctx, speaker_cfg_t *cfg );
```

- `speaker_default_cfg` Click Default Configuration function.
```c
void speaker_default_cfg ( speaker_t *ctx );
```

- `speaker_shutdown` Speaker shutdown mode function.
```c
err_t speaker_shutdown ( speaker_t *ctx );
```

- `speaker_normal_operation` Speaker normal operation mode function.
```c
err_t speaker_normal_operation ( speaker_t *ctx );
```

- `speaker_enable_slave_amp` Speaker enables the slave amplifier function.
```c
err_t speaker_enable_slave_amp ( speaker_t *ctx );
```

### Application Init

> Initialization of GPIO module and log UART.
> After driver initialization, the application performs the default settings.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    speaker_cfg_t speaker_cfg;  /**< Click config object. */

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
    log_printf( &logger, "\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    speaker_cfg_setup( &speaker_cfg );
    SPEAKER_MAP_MIKROBUS( speaker_cfg, MIKROBUS_1 );
    if ( speaker_init( &speaker, &speaker_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    speaker_default_cfg ( &speaker );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> This is an example that shows the use of a Speaker Click board&trade;.
> The task of the application consists of 
> switching two modes of operation: normal and shutdown modes.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "  Normal Operation Mode \r\n" );
    speaker_normal_operation( &speaker );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "   Enter Shutdown Mode  \r\n" );
    speaker_shutdown( &speaker );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
