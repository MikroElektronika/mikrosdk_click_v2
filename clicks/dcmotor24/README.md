
---
# DC Motor 24 Click

> [DC Motor 24 Click](https://www.mikroe.com/?pid_product=MIKROE-5537) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5537&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2023.
- **Type**          : SPI/PWM type

# Software Support

## Example Description

> This example demonstrates the use of the DC Motor 24 Click board by driving the motor in both directions at different speeds.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DCMotor24

### Example Key Functions

- `dcmotor24_cfg_setup` Config Object Initialization function.
```c
void dcmotor24_cfg_setup ( dcmotor24_cfg_t *cfg );
```

- `dcmotor24_init` Initialization function.
```c
err_t dcmotor24_init ( dcmotor24_t *ctx, dcmotor24_cfg_t *cfg );
```

- `dcmotor24_default_cfg` Click Default Configuration function.
```c
err_t dcmotor24_default_cfg ( dcmotor24_t *ctx );
```

- `dcmotor24_read_diag` This function reads a diagnostics word by using SPI serial interface.
```c
err_t dcmotor24_read_diag ( dcmotor24_t *ctx, uint16_t *diag );
```

- `dcmotor24_switch_direction` This function switches the direction by toggling the DIR pin state.
```c
void dcmotor24_switch_direction ( dcmotor24_t *ctx );
```

- `dcmotor24_set_duty_cycle` This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
```c
err_t dcmotor24_set_duty_cycle ( dcmotor24_t *ctx, float duty_cycle );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor24_cfg_t dcmotor24_cfg;  /**< Click config object. */

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
    dcmotor24_cfg_setup( &dcmotor24_cfg );
    DCMOTOR24_MAP_MIKROBUS( dcmotor24_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == dcmotor24_init( &dcmotor24, &dcmotor24_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DCMOTOR24_ERROR == dcmotor24_default_cfg ( &dcmotor24 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Controls the motor speed by changing the PWM duty cycle every 500ms.
The duty cycle ranges from 0% to 100%. At the minimal speed, the motor switches direction.
It also reads and parses the diagnostics word register. Each step will be logged on
the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    static int8_t duty_pct = 10;
    static int8_t duty_step = 10;
    uint16_t diag;
    if ( DCMOTOR24_OK == dcmotor24_set_duty_cycle ( &dcmotor24, ( float ) duty_pct / 100 ) )
    {
        log_printf( &logger, "\r\n Duty: %u%%\r\n", ( uint16_t ) duty_pct );
    }
    if ( DCMOTOR24_OK == dcmotor24_read_diag ( &dcmotor24, &diag ) )
    {
        dcmotor24_display_diag ( diag );
    }
    Delay_ms ( 500 );
    if ( ( 100 == duty_pct ) || ( 0 == duty_pct ) ) 
    {
        duty_step = -duty_step;
        if ( 0 == duty_pct )
        {
            log_printf( &logger, "\r\n Switch direction\r\n" );
            dcmotor24_switch_direction ( &dcmotor24 );
            Delay_ms ( 500 );
        }
    }
    duty_pct += duty_step;
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
