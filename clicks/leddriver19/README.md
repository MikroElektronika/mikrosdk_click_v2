
---
# LED Driver 19 Click

> [LED Driver 19 Click](https://www.mikroe.com/?pid_product=MIKROE-5639) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5639&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Apr 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for LED Driver 19 Click driver. 
  The library initializes and defines the I2C bus drivers to 
  write the default configuration for a PWM output value 
  of the out pins.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LEDDriver19

### Example Key Functions

- `leddriver19_cfg_setup` Config Object Initialization function.
```c
void leddriver19_cfg_setup ( leddriver19_cfg_t *cfg );
```

- `leddriver19_init` Initialization function.
```c
err_t leddriver19_init ( leddriver19_t *ctx, leddriver19_cfg_t *cfg );
```

- `leddriver19_default_cfg` Click Default Configuration function.
```c
err_t leddriver19_default_cfg ( leddriver19_t *ctx );
```

- `leddriver19_sw_reset` LED Driver 19 software reset function.
```c
err_t leddriver19_sw_reset ( leddriver19_t *ctx );
```

- `leddriver19_enable_channels` LED Driver 19 enables channels function.
```c
err_t leddriver19_enable_channels ( leddriver19_t *ctx, uint16_t channels_en );
```

- `leddriver19_set_pattern_pwm` LED Driver 19 set pattern PWM value function.
```c
err_t leddriver19_set_pattern_pwm ( leddriver19_t *ctx, uint8_t pattern_sel, uint8_t channel_sel, float pwm_value );
```

### Application Init

> Initializes the driver and performs default configuration, sets the device
  in output enabled mode and checks communication by reading device ID.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    leddriver19_cfg_t leddriver19_cfg;  /**< Click config object. */

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
    leddriver19_cfg_setup( &leddriver19_cfg );
    LEDDRIVER19_MAP_MIKROBUS( leddriver19_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == leddriver19_init( &leddriver19, &leddriver19_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    uint8_t device_id;
    
    leddriver19_read_reg( &leddriver19, LEDDRIVER19_REG_DEVICE_ID, &device_id );
    if ( LEDDRIVER19_DEVICE_ID != device_id )
    {
        log_error( &logger, " Communication error." );
        for ( ; ; );
    }
    
    if ( LEDDRIVER19_ERROR == leddriver19_default_cfg ( &leddriver19 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This example demonstrates the use of the LED Driver 19 Click board by 
  changing PWM values of all channels from maximum to minimum turning 
  LEDs on and off in the process.

```c
void application_task ( void ) 
{
    for ( uint8_t n_cnt = LEDDRIVER19_CH_SEL_0; n_cnt <= LEDDRIVER19_CH_SEL_11; n_cnt++ )
    {
        leddriver19_set_pattern_pwm( &leddriver19, LEDDRIVER19_PATSEL_0, n_cnt, 100  );
        Delay_ms ( 100 );
    }
    Delay_ms ( 1000 );
    
    for ( uint8_t n_cnt = LEDDRIVER19_CH_SEL_0; n_cnt <= LEDDRIVER19_CH_SEL_11; n_cnt++ )
    {
        leddriver19_set_pattern_pwm( &leddriver19, LEDDRIVER19_PATSEL_0, n_cnt, 0  );
        Delay_ms ( 100 );
    }
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
