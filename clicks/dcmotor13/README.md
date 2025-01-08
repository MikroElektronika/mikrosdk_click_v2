
---
# DC Motor 13 Click

> [DC Motor 13 Click](https://www.mikroe.com/?pid_product=MIKROE-5101) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5101&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of DC Motor 13 Click board by driving the motors in both direction in the span of 9 seconds.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DCMotor13

### Example Key Functions

- `dcmotor13_cfg_setup` Config Object Initialization function.
```c
void dcmotor13_cfg_setup ( dcmotor13_cfg_t *cfg );
```

- `dcmotor13_init` Initialization function.
```c
err_t dcmotor13_init ( dcmotor13_t *ctx, dcmotor13_cfg_t *cfg );
```

- `dcmotor13_default_cfg` Click Default Configuration function.
```c
err_t dcmotor13_default_cfg ( dcmotor13_t *ctx );
```

- `dcmotor13_set_outa_mode` This function sets the OUTA mode.
```c
err_t dcmotor13_set_outa_mode ( dcmotor13_t *ctx, uint8_t mode );
```

- `dcmotor13_set_outb_mode` This function sets the OUTB mode.
```c
err_t dcmotor13_set_outb_mode ( dcmotor13_t *ctx, uint8_t mode );
```

- `dcmotor13_set_outa_torque` This function sets the OUTA torque.
```c
err_t dcmotor13_set_outa_torque ( dcmotor13_t *ctx, uint8_t torque );
```

### Application Init

> Initializes the driver and performs the Click default configuration which sets the output torque to 100%.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor13_cfg_t dcmotor13_cfg;  /**< Click config object. */

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
    dcmotor13_cfg_setup( &dcmotor13_cfg );
    DCMOTOR13_MAP_MIKROBUS( dcmotor13_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == dcmotor13_init( &dcmotor13, &dcmotor13_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DCMOTOR13_ERROR == dcmotor13_default_cfg ( &dcmotor13 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Drives the motors in the clockwise direction, then switches to the counter-clockwise direction, and after that pulls the motors brake with a 3 seconds delay after each change.
Each step will be logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    if ( DCMOTOR13_OK == dcmotor13_set_outa_mode ( &dcmotor13, DCMOTOR13_MODE_CW ) )
    {
        log_printf ( &logger, " OUTA: Clockwise\r\n" );
    }
    if ( DCMOTOR13_OK == dcmotor13_set_outb_mode ( &dcmotor13, DCMOTOR13_MODE_CW ) )
    {
        log_printf ( &logger, " OUTB: Clockwise\r\n\n" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( DCMOTOR13_OK == dcmotor13_set_outa_mode ( &dcmotor13, DCMOTOR13_MODE_CCW ) )
    {
        log_printf ( &logger, " OUTA: Counter-Clockwise\r\n" );
    }
    if ( DCMOTOR13_OK == dcmotor13_set_outb_mode ( &dcmotor13, DCMOTOR13_MODE_CCW ) )
    {
        log_printf ( &logger, " OUTB: Counter-Clockwise\r\n\n" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( DCMOTOR13_OK == dcmotor13_set_outa_mode ( &dcmotor13, DCMOTOR13_MODE_SHORT_BRAKE ) )
    {
        log_printf ( &logger, " OUTA: Short brake\r\n" );
    }
    if ( DCMOTOR13_OK == dcmotor13_set_outb_mode ( &dcmotor13, DCMOTOR13_MODE_SHORT_BRAKE ) )
    {
        log_printf ( &logger, " OUTB: Short brake\r\n\n" );
    }
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
