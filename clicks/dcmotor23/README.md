
---
# DC Motor 23 Click

> [DC Motor 23 Click](https://www.mikroe.com/?pid_product=MIKROE-5476) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5476&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of DC Motor 23 Click board&trade;. 
> by driving the motors in both direction every 3 seconds.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DCMotor23

### Example Key Functions

- `dcmotor23_cfg_setup` Config Object Initialization function.
```c
void dcmotor23_cfg_setup ( dcmotor23_cfg_t *cfg );
```

- `dcmotor23_init` Initialization function.
```c
err_t dcmotor23_init ( dcmotor23_t *ctx, dcmotor23_cfg_t *cfg );
```

- `dcmotor23_default_cfg` Click Default Configuration function.
```c
err_t dcmotor23_default_cfg ( dcmotor23_t *ctx );
```

- `dcmotor23_set_clockwise` DC Motor 23 set clockwise function.
```c
err_t dcmotor23_set_clockwise ( dcmotor23_t *ctx, uint8_t sel_motor );
```

- `dcmotor23_set_counter_clockwise` DC Motor 23 set counter clockwise function.
```c
err_t dcmotor23_set_counter_clockwise ( dcmotor23_t *ctx, uint8_t sel_motor );
```

- `dcmotor23_set_decay` DC Motor 23 set decay function.
```c
err_t dcmotor23_set_decay ( dcmotor23_t *ctx, uint8_t sel_motor );
```

### Application Init

> Initializes the driver and performs the Click default configuration 
> which sets the output torque to 100%.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor23_cfg_t dcmotor23_cfg;  /**< Click config object. */

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
    dcmotor23_cfg_setup( &dcmotor23_cfg );
    DCMOTOR23_MAP_MIKROBUS( dcmotor23_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == dcmotor23_init( &dcmotor23, &dcmotor23_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( DCMOTOR23_ERROR == dcmotor23_default_cfg ( &dcmotor23 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    log_printf ( &logger, "--------------------------\r\n" );
}
```

### Application Task

> This example demonstrates the use of the DC Motor 23  Click board&trade;.
> Drives the motors in the clockwise direction,
> after that decay the motors with a 3 seconds delay
> then switches to the counter-clockwise direction, 
> and decay the motors with a 3 seconds delay.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{    
    if ( DCMOTOR23_OK == dcmotor23_set_clockwise( &dcmotor23, DCMOTOR23_SEL_OUT_A ) )
    {
        log_printf ( &logger, " OUTA: Clockwise\r\n" );
    }
    if ( DCMOTOR23_OK == dcmotor23_set_clockwise( &dcmotor23, DCMOTOR23_SEL_OUT_B ) )
    {
        log_printf ( &logger, " OUTB: Clockwise\r\n\n" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    if ( DCMOTOR23_OK == dcmotor23_set_decay( &dcmotor23, DCMOTOR23_SEL_OUT_A ) )
    {
        log_printf ( &logger, " OUTA: Decay\r\n" );
    }
    if ( DCMOTOR23_OK == dcmotor23_set_decay( &dcmotor23, DCMOTOR23_SEL_OUT_B ) )
    {
        log_printf ( &logger, " OUTB: Decay\r\n\n" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    if ( DCMOTOR23_OK == dcmotor23_set_counter_clockwise( &dcmotor23, DCMOTOR23_SEL_OUT_A ) )
    {
        log_printf ( &logger, " OUTA: Counter-Clockwise\r\n" );
    }
    if ( DCMOTOR23_OK == dcmotor23_set_counter_clockwise( &dcmotor23, DCMOTOR23_SEL_OUT_B ) )
    {
        log_printf ( &logger, " OUTB: Counter-Clockwise\r\n\n" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    if ( DCMOTOR23_OK == dcmotor23_set_decay( &dcmotor23, DCMOTOR23_SEL_OUT_A ) )
    {
        log_printf ( &logger, " OUTA: Decay\r\n" );
    }
    if ( DCMOTOR23_OK == dcmotor23_set_decay( &dcmotor23, DCMOTOR23_SEL_OUT_B ) )
    {
        log_printf ( &logger, " OUTB: Decay\r\n\n" );
    }
    log_printf ( &logger, "--------------------------\r\n" );
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
