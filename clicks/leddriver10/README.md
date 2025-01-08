
---
# LED Driver 10 Click

> [LED Driver 10 Click](https://www.mikroe.com/?pid_product=MIKROE-4787) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4787&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of LED Driver 10 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LEDDriver10

### Example Key Functions

- `leddriver10_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void leddriver10_cfg_setup ( leddriver10_cfg_t *cfg );
```

- `leddriver10_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t leddriver10_init ( leddriver10_t *ctx, leddriver10_cfg_t *cfg );
```

- `leddriver10_pwm_start` This function starts the PWM module output.
```c
err_t leddriver10_pwm_start ( leddriver10_t *ctx );
```

- `leddriver10_set_channels` This function sets all channels to desired value by using SPI serial interface.
```c
err_t leddriver10_set_channels ( leddriver10_t *ctx, uint16_t ch_mask );
```

- `leddriver10_read_channels` This function reads the current state of all channels by using SPI serial interface.
```c
err_t leddriver10_read_channels ( leddriver10_t *ctx, uint16_t *ch_mask );
```

- `leddriver10_set_duty_cycle` This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
```c
err_t leddriver10_set_duty_cycle ( leddriver10_t *ctx, float duty_cycle );
```

### Application Init

> Initializes the driver, starts the PWM module and enables all channels.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    leddriver10_cfg_t leddriver10_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.

    leddriver10_cfg_setup( &leddriver10_cfg );
    LEDDRIVER10_MAP_MIKROBUS( leddriver10_cfg, MIKROBUS_1 );
    err_t init_flag  = leddriver10_init( &leddriver10, &leddriver10_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    leddriver10_pwm_start( &leddriver10 );    
    leddriver10_set_channels ( &leddriver10, LEDDRIVER10_ENABLE_ALL_CH );
    log_printf( &logger, " All channels enabled!\r\n" );
    log_printf( &logger, " Dimming the LEDs light...\r\n" );
}
```

### Application Task

> Controls the LEDs brightness by changing the PWM duty cycle.
> The PWM duty cycle percentage will be logged on the USB UART.

```c
void application_task ( void )
{
    static int16_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    leddriver10_set_duty_cycle ( &leddriver10, duty );
    log_printf( &logger, "> Duty: %u%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
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
