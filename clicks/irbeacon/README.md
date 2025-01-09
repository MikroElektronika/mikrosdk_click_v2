
---
# IR Beacon Click

> [IR Beacon Click](https://www.mikroe.com/?pid_product=MIKROE-1939) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1939&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nikola Peric
- **Date**          : Feb 2022.
- **Type**          : PWM type

# Software Support

## Example Description

>  This library contains an API for the IrBeacon Click driver.
>  This application is suitable for high pulse current operation.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.IrBeacon

### Example Key Functions

- `irbeacon_cfg_setup` Config Object Initialization function. 
```c
void irbeacon_cfg_setup ( irbeacon_cfg_t *cfg );
``` 
 
- `irbeacon_init` Initialization function. 
```c
err_t irbeacon_init ( irbeacon_t *ctx, irbeacon_cfg_t *cfg );
```

- `irbeacon_enable_mod` Enable MOD function. 
```c
void irbeacon_enable_mod ( irbeacon_t *ctx );
```
 
- `irbeacon_disable_mod` Disable MOD function. 
```c
void irbeacon_disable_mod ( irbeacon_t *ctx );
```

- `irbeacon_reset_mod` Reset MOD function. 
```c
void irbeacon_reset_mod ( irbeacon_t *ctx );
```

### Application Init

> Enables GPIO and PWM, sets the frequency and duty cycle and enables PWM.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    irbeacon_cfg_t cfg;

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

    irbeacon_cfg_setup( &cfg );
    IRBEACON_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    irbeacon_init( &irbeacon, &cfg );
    irbeacon_pwm_start( &irbeacon );
    
    log_info( &logger, "---- Application Task ----" );
    Delay_ms ( 1000 );
}
```

### Application Task

>  This is a example which demonstrates the use of IR Beacon Click board.
>  It shows how to enable the device and gradualy increase the duty cycle.
>  Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    irbeacon_set_duty_cycle ( &irbeacon, duty );
    irbeacon_enable_mod( &irbeacon );
    log_printf( &logger, "Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    Delay_ms ( 500 );
    
    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        irbeacon_disable_mod( &irbeacon );
        duty_inc = 1;
    }
    duty_cnt += duty_inc;
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
