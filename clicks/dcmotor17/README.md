
---
# DC Motor 17 Click

> [DC Motor 17 Click](https://www.mikroe.com/?pid_product=MIKROE-4454) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4454&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2020.
- **Type**          : GPIO type

# Software Support

## Example Description

> The library covers all the necessary functions to control DC Motor 17 Click board.
> Library performs a standard GPIO interface communication.
> DC Motor 17 Click board is a dual H Bridge driver IC for one or two DC brushed
> motors which incorporates DMOS with low on-resistance in output transistors.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DcMotor17

### Example Key Functions

> Config Object Initialization function.
```c
void dcmotor17_cfg_setup ( dcmotor17_cfg_t *cfg );
```

> Initialization function.
```c
err_t dcmotor17_init ( dcmotor17_t *ctx, dcmotor17_cfg_t *cfg );
```

> Click Default Configuration function.
```c
void dcmotor17_default_cfg ( dcmotor17_t *ctx );
```

> DC Motor 17 stop motor function.
```c
dcmotor17_retval_t dcmotor17_stop ( dcmotor17_t *ctx, uint8_t sel_out );
```

> DC Motor 17 forward function.
```c
dcmotor17_retval_t dcmotor17_forward ( dcmotor17_t *ctx, uint8_t sel_out );
```

> DC Motor 17 reverse function.
```c
dcmotor17_retval_t dcmotor17_reverse ( dcmotor17_t *ctx, uint8_t sel_out );
```

### Application Init

> Initializes GPIO driver, set default configuration and start to write log.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    dcmotor17_cfg_t dcmotor17_cfg;  /**< Click config object. */

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
    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "      DC Motor 17 Click     \r\n" );
    log_printf( &logger, "----------------------------\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    dcmotor17_cfg_setup( &dcmotor17_cfg );
    DCMOTOR17_MAP_MIKROBUS( dcmotor17_cfg, MIKROBUS_1 );
    if ( dcmotor17_init( &dcmotor17, &dcmotor17_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    dcmotor17_default_cfg ( &dcmotor17 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This is an example that demonstrates the use of the DC Motor 17 Click board.
> This example demonstrates the use of DC Motor 17 Click,
> we first control motion A by driving it forward motion for 5 seconds,
> than applying short brakes it for 2 second, then driving it in reverse for 5 seconds
> and stop the motor for 2 seconds.
> In the second part of the example, we control motion B by the same principle.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "          Motor A           \r\n" );
    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "  Start the motor forward.  \r\n" );
    dcmotor17_forward( &dcmotor17, DCMOTOR17_SEL_OUT_A );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "       Stop the motor.      \r\n" );
    dcmotor17_stop( &dcmotor17, DCMOTOR17_SEL_OUT_A );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "  Start the motor reverse.  \r\n" );
    dcmotor17_reverse( &dcmotor17, DCMOTOR17_SEL_OUT_A );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "       Stop the motor.      \r\n" );
    dcmotor17_stop( &dcmotor17, DCMOTOR17_SEL_OUT_A );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "          Motor B           \r\n" );
    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "  Start the motor forward.  \r\n" );
    dcmotor17_forward( &dcmotor17, DCMOTOR17_SEL_OUT_B );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "       Stop the motor.      \r\n" );
    dcmotor17_stop( &dcmotor17, DCMOTOR17_SEL_OUT_B );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "  Start the motor reverse.  \r\n" );
    dcmotor17_reverse( &dcmotor17, DCMOTOR17_SEL_OUT_B );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "       Stop the motor.      \r\n" );
    dcmotor17_stop( &dcmotor17, DCMOTOR17_SEL_OUT_B );
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
