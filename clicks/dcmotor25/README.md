
---
# DC Motor 25 Click

> [DC Motor 25 Click](https://www.mikroe.com/?pid_product=MIKROE-5523) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5523&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Mar 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of DC Motor 25 Click board&trade; 
> by driving the DC motor in both directions every 3 seconds.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DCMotor25

### Example Key Functions

- `dcmotor25_cfg_setup` Config Object Initialization function.
```c
void dcmotor25_cfg_setup ( dcmotor25_cfg_t *cfg );
```

- `dcmotor25_init` Initialization function.
```c
err_t dcmotor25_init ( dcmotor25_t *ctx, dcmotor25_cfg_t *cfg );
```

- `dcmotor25_default_cfg` Click Default Configuration function.
```c
err_t dcmotor25_default_cfg ( dcmotor25_t *ctx );
```

- `dcmotor25_forward` DC Motor 25 set forward mode function.
```c
void dcmotor25_forward ( dcmotor25_t *ctx );
```

- `dcmotor25_reverse` DC Motor 25 set reverse mode function.
```c
void dcmotor25_reverse ( dcmotor25_t *ctx );
```

- `dcmotor25_brake` DC Motor 25 set brake mode function.
```c
void dcmotor25_brake ( dcmotor25_t *ctx );
```

### Application Init

> Initializes the I2C drivernd and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor25_cfg_t dcmotor25_cfg;  /**< Click config object. */

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
    dcmotor25_cfg_setup( &dcmotor25_cfg );
    DCMOTOR25_MAP_MIKROBUS( dcmotor25_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == dcmotor25_init( &dcmotor25, &dcmotor25_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DCMOTOR25_ERROR == dcmotor25_default_cfg ( &dcmotor25 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the DC Motor 25 Click board&trade;.
> Drives the motors in the forward and reverse direction 
> with a 3 seconds delay with engine braking between direction changes.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    log_printf ( &logger, " Forward\r\n" );
    dcmotor25_forward( &dcmotor25 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Brake\r\n" );
    dcmotor25_brake( &dcmotor25 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Reverse\r\n" );
    dcmotor25_reverse( &dcmotor25 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Brake\r\n" );
    dcmotor25_brake( &dcmotor25 );
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
