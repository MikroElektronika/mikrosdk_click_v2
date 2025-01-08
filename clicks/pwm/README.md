
---
# PWM Click

> [PWM Click](https://www.mikroe.com/?pid_product=MIKROE-1898) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1898&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This is an example that shows some of the functions that PWM Click has.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pwm

### Example Key Functions

- `pwm_cfg_setup` Config Object Initialization function. 
```c
void pwm_cfg_setup ( pwm_cfg_t *cfg );
``` 
 
- `pwm_init` Initialization function. 
```c
err_t pwm_init ( pwm_t *ctx, pwm_cfg_t *cfg );
```

- `pwm_dev_config` Device configuration function. 
```c
void pwm_dev_config ( pwm_t *ctx, uint8_t chann_id, uint8_t state );
```
 
- `pwm_set_channel_raw` Set channel raw function. 
```c
void pwm_set_channel_raw ( pwm_t *ctx, uint8_t chann_id, uint16_t raw_off_set, uint16_t raw_dc );
```

- `pwm_set_all_raw` Set all channels raw function. 
```c
void pwm_set_all_raw ( pwm_t *ctx, uint16_t raw_dc );
```

### Application Init

> Initalizes I2C driver, enables output, configures device, sets prescaling,
> configures output and makes an initial log. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    pwm_cfg_t cfg;

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

    pwm_cfg_setup( &cfg );
    PWM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pwm_init( &pwm, &cfg );
    Delay_ms ( 100 );
    
    pwm_set_output( &pwm, PWM_ENABLE );
    pwm_dev_config( &pwm, &config0 );
    pwm_set_pre_scale( &pwm, 0x04 );
    pwm_dev_config( &pwm, &config1 );
    pwm_output_config( &pwm,  &config2 );
    Delay_ms ( 100 );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " PWM  Click \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
}
```

### Application Task

> Changes the duty cycle of all channels every 10 seconds.
> All data are being logged on USB UART where you can track their changes.

```c
void application_task ( void )
{
    uint8_t chann_id;
    
    pwm_set_all_raw( &pwm, PWM_MAX_RESOLUTION / 2 );
    log_printf( &logger, "All Channels set to 50%% duty cycle \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
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
    
    for ( chann_id = 0; chann_id < 8; chann_id++ )
    {
        pwm_set_channel_raw( &pwm, chann_id, 0, PWM_MAX_RESOLUTION / 4 );
    }
    log_printf( &logger, "Channels 0-7 set to 25%% duty cycle \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
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
    
    for ( chann_id = 0; chann_id < 8; chann_id++ )
    {
        pwm_set_channel_raw( &pwm, chann_id, 0, ( PWM_MAX_RESOLUTION / 4 ) * 3 );
    }
    log_printf( &logger, "Channels 0-7 set to 75%% duty cycle \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
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
    
    pwm_all_chann_state( &pwm, 0 );
    log_printf( &logger, "All Channels disabled \r\n " );
    log_printf( &logger, "--------------------------\r\n" );
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
