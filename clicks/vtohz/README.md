
---
# V to Hz Click

> [V to Hz Click](https://www.mikroe.com/?pid_product=MIKROE-2889) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2889&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jan 2020.
- **Type**          : PWM type

# Software Support

## Example Description

> This application converts an analog voltage input signal into a pulse wave signal of a certain frequency. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.VtoHz

### Example Key Functions

- `vtohz_cfg_setup` Config Object Initialization function. 
```c
void vtohz_cfg_setup ( vtohz_cfg_t *cfg );
``` 
 
- `vtohz_init` Initialization function. 
```c
err_t vtohz_init ( vtohz_t *ctx, vtohz_cfg_t *cfg );
```

- `vtohz_set_duty_cycle` Generic sets PWM duty cycle. 
```c
void vtohz_set_duty_cycle ( vtohz_t *ctx, pwm_data_t duty_cycle );
```
 
- `vtohz_pwm_stop` Stop PWM module. 
```c
void vtohz_pwm_stop ( vtohz_t *ctx );
```

- `vtohz_pwm_start` Start PWM module. 
```c
void vtohz_pwm_start ( vtohz_t *ctx );
```

### Application Init

> Initializes driver and enables the Click board. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    vtohz_cfg_t cfg;

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

    vtohz_cfg_setup( &cfg );
    VTOHZ_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    vtohz_init( &vtohz, &cfg );
    
    vtohz_enable ( &vtohz );
}
```

### Application Task

> Alternates between different output frequencies.

```c
void application_task ( void )
{
    set_output_frequency( 1000 );        //1000 Hz output
    log_printf( &logger, "Output frequency: \t 1000 Hz\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    set_output_frequency( 2000 );        //2000 Hz output
    log_printf( &logger, "Output frequency: \t 2000 Hz\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    set_output_frequency( 5000 );        //5000 Hz output
    log_printf( &logger, "Output frequency: \t 5000 Hz\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    set_output_frequency( 10000 );       //10000 Hz output
    log_printf( &logger, "Output frequency: \t 10000 Hz\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> Output frequency may vary depending on the offset and gain potentiometers on board the Click.

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
