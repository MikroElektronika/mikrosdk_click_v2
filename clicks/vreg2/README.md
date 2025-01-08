
---
# VREG 2 Click

> [VREG 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3055) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3055&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2023.
- **Type**          : PWM type

# Software Support

## Example Description

> This example demonstrates the use of the VREG 2 Click board by changing the voltage output every 5 seconds.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Vreg2

### Example Key Functions

- `vreg2_cfg_setup` Config Object Initialization function.
```c
void vreg2_cfg_setup ( vreg2_cfg_t *cfg ); 
```

- `vreg2_init` Initialization function.
```c
err_t vreg2_init ( vreg2_t *ctx, vreg2_cfg_t *cfg );
```

- `vreg2_default_cfg` Click Default Configuration function.
```c
err_t vreg2_default_cfg ( vreg2_t *ctx );
```

- `vreg2_set_duty_cycle` This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
```c
err_t vreg2_set_duty_cycle ( vreg2_t *ctx, float duty_cycle );
```

- `vreg2_pwm_start` This function starts the PWM module output.
```c
err_t vreg2_pwm_start ( vreg2_t *ctx );
```

- `vreg2_pwm_stop` This function stops the PWM module output.
```c
err_t vreg2_pwm_stop ( vreg2_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    vreg2_cfg_t vreg2_cfg;  /**< Click config object. */

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
    vreg2_cfg_setup( &vreg2_cfg );
    VREG2_MAP_MIKROBUS( vreg2_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == vreg2_init( &vreg2, &vreg2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( VREG2_ERROR == vreg2_default_cfg ( &vreg2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Controls the voltage output by changing the PWM duty cycle every 5 seconds.
The duty cycle ranges from 10% to 50%. Each step will be logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    static int8_t duty_pct = 10;
    static int8_t duty_step = 10;
    if ( VREG2_OK == vreg2_set_duty_cycle ( &vreg2, ( float ) duty_pct / 100 ) )
    {
        log_printf( &logger, "\r\n Duty: %u%%\r\n", ( uint16_t ) duty_pct );
    }
    duty_pct += duty_step;
    if ( ( duty_pct > 50 ) || ( duty_pct < 10 ) ) 
    {
        duty_step = -duty_step;
        duty_pct += ( duty_step * 2 );
    }
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
