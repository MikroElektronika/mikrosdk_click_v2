
---
# Button G Click

> [Button G Click](https://www.mikroe.com/?pid_product=MIKROE-2040) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2040&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nikola Peric
- **Date**          : Feb 2022.
- **Type**          : GPIO type

# Software Support

## Example Description

>  This library contains API for Button G Click driver. 
>  One library is used for every single one of them.
>  They are simple touch detectors that send a pressed/released 
>  signal and receive a PWM output which controls the backlight on the button.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ButtonG

### Example Key Functions

- `buttong_cfg_setup` Config Object Initialization function.
```c
void buttong_cfg_setup ( buttong_cfg_t *cfg );
```

- `buttong_init` Initialization function.
```c
err_t buttong_init ( buttong_t *ctx, buttong_cfg_t *cfg );
```

- `buttong_pwm_stop` This function stops the PWM moudle output.
```c
err_t buttong_pwm_stop ( buttong_t *ctx );
```

- `buttong_pwm_start` This function starts the PWM moudle output.
```c
err_t buttong_pwm_start ( buttong_t *ctx );
```

- `buttong_get_button_state` This function reads the digital signal from the INT pin which tells us whether the button has been pressed or not.
```c
uint8_t buttong_get_button_state ( buttong_t *ctx );
```

### Application Init

> This function initializes and configures the logger and Click modules. 

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    buttong_cfg_t buttong_cfg;  /**< Click config object. */

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

    buttong_cfg_setup( &buttong_cfg );
    BUTTONG_MAP_MIKROBUS( buttong_cfg, MIKROBUS_1 );
    err_t init_flag  = buttong_init( &buttong, &buttong_cfg );
    if ( PWM_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms ( 500 );
    
    buttong_set_duty_cycle ( &buttong, 0.0 );
    buttong_pwm_start( &buttong );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This example first increases the backlight on the button and then decreases the intensity of the
> backlight. When the button is pressed,  
> reports the event in the console using UART communication.

```c
void application_task ( void ) 
{
    static float duty_cycle;
    static uint8_t button_state;
    static uint8_t button_state_old;

    button_state = buttong_get_button_state( &buttong );
    
    if ( button_state && ( button_state != button_state_old ) ) 
    {
        log_printf( &logger, " <-- Button pressed --> \r\n" );
        for ( uint8_t n_cnt = 1; n_cnt <= 100; n_cnt++  )
        {
            duty_cycle = ( float ) n_cnt ;
            duty_cycle /= 100;
            buttong_set_duty_cycle( &buttong, duty_cycle );
            Delay_ms ( 10 );
        }
        button_state_old = button_state;
    } 
    else if ( !button_state && ( button_state != button_state_old ) ) 
    {
        for ( uint8_t n_cnt = 100; n_cnt > 0; n_cnt-- )
        {
            duty_cycle = ( float ) n_cnt ;
            duty_cycle /= 100;
            buttong_set_duty_cycle( &buttong,  duty_cycle );
            Delay_ms ( 10 );
        }
        button_state_old = button_state;
    }
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
