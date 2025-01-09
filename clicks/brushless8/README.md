
---
# Brushless 8  Click

> [Brushless 8 Click](https://www.mikroe.com/?pid_product=MIKROE-4275) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4275&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nikola Peric
- **Date**          : Mar 2022.
- **Type**          : PWM type

# Software Support

## Example Description

>  This example showcases how to initialize and use the Brushless 8 Click. 
>  This application is a schowcase of controlling speed 
>  and direction of brushless motor with hall sesnor.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless8

### Example Key Functions

- `brushless8_cfg_setup` Config Object Initialization function. 
```c
void brushless8_cfg_setup ( brushless8_cfg_t *cfg );
```

- `brushless8_init` Initialization function. 
```c
err_t brushless8_init ( brushless8_t *ctx, brushless8_cfg_t *cfg );
```

- `brushless8_default_cfg` Click Default Configuration function. 
```c
void brushless8_default_cfg ( brushless8_t *ctx );
```

- `brushless8_cfg_setup` function initializes Click configuration structure to initial values.
```c
brushless8_cfg_setup( &brushless8_cfg );
```

- `brushless8_init` function initializes all necessary pins and peripherals used for this Click board.
```c
err_t init_flag = brushless8_init( &brushless8, &brushless8_cfg );
```

- `brushless8_default_cfg` function executes a default configuration of Brushless 8 Click board.
```c
brushless8_default_cfg ( &brushless8 );
```

### Application Init

> Initializes the Click board to appropriate settings based on selected mode.
> Initialization settings are sent through I2C bus and the motor itself is
> controlled via PWM or DAC over I2C.
> * Modes:
>     - BRUSHLESS8_PWM
>     - BRUSHLESS8_DAC

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless8_cfg_t brushless8_cfg;  /**< Click config object. */

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
    log_info( &logger, "Application Init" );

    // Click initialization.

    brushless8_cfg_setup( &brushless8_cfg );
    // Select desired mode.
    brushless8_cfg.ctrl_mod = BRUSHLESS8_MODE;
    BRUSHLESS8_MAP_MIKROBUS( brushless8_cfg, MIKROBUS_1 );

err_t init_flag = brushless8_init( &brushless8, &brushless8_cfg );
    if ( BRUSHLESS8_OK != init_flag )
    {
        log_error( &logger, "Application Init Error" );
        log_info( &logger, "Please, run program again..." );

        for ( ; ; );
    }

    brushless8_default_cfg ( &brushless8 );

    if ( BRUSHLESS8_PWM == brushless8.ctrl_mod )
    {
        brushless8_set_dac_vout( &brushless8, BRUSHLESS8_DAC_REG_CHN_A_DVSP, 0 );
        brushless8_set_duty_cycle( &brushless8, 0 );
        brushless8_pwm_start( &brushless8 );

        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }

    log_info( &logger, "Application Task" );
    log_printf( &logger, "------------------------------\r\n" );
}
```

### Application Task

>  This example demonstrates the use of Brushless 8 Click board.
>  Brushless 8 Click communicates with the device via I2C driver in order to 
>  set adequate voltage level for connected motor.
>  Current PWM/DAC settings being output are sent via logger.
>  Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void )
{    
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    brushless8_set_duty_cycle ( &brushless8, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms ( 500 );
    
    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
    }
    duty_cnt += duty_inc;
}
```

### Note

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
