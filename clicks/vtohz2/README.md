
---
# V to Hz 2 Click

> [V to Hz 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3131) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3131&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jan 2020.
- **Type**          : PWM type

# Software Support

## Example Description

> This appliaction enables usage of a converter for analog voltage input signal into 
> a pulse wave signal of a certain frequency.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.VToHz2

### Example Key Functions

- `vtohz2_cfg_setup` Config Object Initialization function. 
```c
void vtohz2_cfg_setup ( vtohz2_cfg_t *cfg );
``` 
 
- `vtohz2_init` Initialization function. 
```c
err_t vtohz2_init ( vtohz2_t *ctx, vtohz2_cfg_t *cfg );
```

- `vtohz2_get_freq_out` Function gets the out frequency on mikrobus INT pin. 
```c
uint8_t vtohz2_get_freq_out ( vtohz2_t *ctx );
```
 
- `vtohz2_enable` Function performs enabling and disabling of the device. 
```c
void vtohz2_enable ( vtohz2_t *ctx, uint8_t state );
```

- `vtohz2_pwm_start` This function starts PWM module. 
```c
void vtohz2_pwm_start ( vtohz2_t *ctx );
```

### Application Init

> Initializes driver and enables the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    vtohz2_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    vtohz2_cfg_setup( &cfg );
    VTOHZ2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    vtohz2_init( &vtohz2, &cfg );

    vtohz2_enable( &vtohz2, VTOHZ2_ENABLE );
    vtohz2_pwm_start( &vtohz2 );
}

  
```

### Application Task

> Sets the output frequency by incrementing the pwm duty cycle from 0 to 100% in an infinite loop.
> Results are being sent to USB UART terminal.

```c
void application_task ( void )
{
    for ( duty_cycle = 0; duty_cycle <= 1.0; duty_cycle += 0.01 )
    {
        vtohz2_set_duty_cycle ( &vtohz2, duty_cycle );
        log_printf( &logger," PWM Duty: %.2f%%\r\n", duty_cycle * 100 );
        Delay_ms ( 100 );
    }
    log_printf( &logger, "------------------------------\r\n" );
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
