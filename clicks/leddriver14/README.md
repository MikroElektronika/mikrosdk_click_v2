
---
# LED Driver 14 Click

> [LED Driver 14 Click](https://www.mikroe.com/?pid_product=MIKROE-4996) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4996&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of LED Driver 14 Click board by controlling the brightness of LEDs by changing the PWM Duty Cycle.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LEDDriver14

### Example Key Functions

- `leddriver14_cfg_setup` Config Object Initialization function.
```c
void leddriver14_cfg_setup ( leddriver14_cfg_t *cfg );
```

- `leddriver14_init` Initialization function.
```c
err_t leddriver14_init ( leddriver14_t *ctx, leddriver14_cfg_t *cfg );
```

- `leddriver14_default_cfg` Click Default Configuration function.
```c
err_t leddriver14_default_cfg ( leddriver14_t *ctx );
```

- `leddriver14_set_rset` This function sets the resistance of the selected rset channel.
```c
err_t leddriver14_set_rset ( leddriver14_t *ctx, uint8_t rset, uint16_t res_ohm );
```

- `leddriver14_get_int_pin` This function returns the int pin logic state.
```c
uint8_t leddriver14_get_int_pin ( leddriver14_t *ctx );
```

- `leddriver14_set_duty_cycle` This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
```c
err_t leddriver14_set_duty_cycle ( leddriver14_t *ctx, float duty_cycle );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    leddriver14_cfg_t leddriver14_cfg;  /**< Click config object. */

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
    leddriver14_cfg_setup( &leddriver14_cfg );
    LEDDRIVER14_MAP_MIKROBUS( leddriver14_cfg, MIKROBUS_1 );
    err_t init_flag = leddriver14_init( &leddriver14, &leddriver14_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( PWM_ERROR == init_flag ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LEDDRIVER14_ERROR == leddriver14_default_cfg ( &leddriver14 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Adjusts the LEDs' brightness by changing the PWM duty cycle every 500ms. A duty cycle value is being displayed on the USB UART.

```c
void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    leddriver14_set_duty_cycle ( &leddriver14, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
    }
    duty_cnt += duty_inc;
    
    if ( !leddriver14_get_int_pin ( &leddriver14 ) )
    {
        log_info ( &logger, " Abnormality such as LED Open or the OUTx pin short circuit occured " );
    }
    
    Delay_ms ( 500 );
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
