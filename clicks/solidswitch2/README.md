
---
# SolidSwitch 2 Click

> [SolidSwitch 2 Click](https://www.mikroe.com/?pid_product=MIKROE-5313) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5313&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2022.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of SolidSwitch 2 Click board by controlling the output state.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SolidSwitch2

### Example Key Functions

- `solidswitch2_cfg_setup` Config Object Initialization function.
```c
void solidswitch2_cfg_setup ( solidswitch2_cfg_t *cfg );
```

- `solidswitch2_init` Initialization function.
```c
err_t solidswitch2_init ( solidswitch2_t *ctx, solidswitch2_cfg_t *cfg );
```

- `solidswitch2_default_cfg` Click Default Configuration function.
```c
err_t solidswitch2_default_cfg ( solidswitch2_t *ctx );
```

- `solidswitch2_write_register` This function writes a desired data to the selected register by using SPI serial interface.
```c
err_t solidswitch2_write_register ( solidswitch2_t *ctx, uint8_t reg, uint8_t data_in );
```

- `solidswitch2_toggle_in0_pin` This function toggles the IN0 pin logic state.
```c
void solidswitch2_toggle_in0_pin ( solidswitch2_t *ctx );
```

- `solidswitch2_toggle_in1_pin` This function toggles the IN1 pin logic state.
```c
void solidswitch2_toggle_in1_pin ( solidswitch2_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration which maps outputs as follows:
> - OUT2   - IN0,
> - OUT3   - IN1,
> - OUT4-5 - PWM GEN,
> - OUT6-7 - PWM LED.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    solidswitch2_cfg_t solidswitch2_cfg;  /**< Click config object. */

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
    solidswitch2_cfg_setup( &solidswitch2_cfg );
    SOLIDSWITCH2_MAP_MIKROBUS( solidswitch2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == solidswitch2_init( &solidswitch2, &solidswitch2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SOLIDSWITCH2_ERROR == solidswitch2_default_cfg ( &solidswitch2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Changes the PWM GEN (max to min) and PWM LED (min to max) duty cycle and toggles the IN0 and IN1
pins every 250ms. The duty cycle values and INx toggle messages will be displayed on the USB UART.

```c
void application_task ( void )
{
    for ( uint16_t duty_cycle = SOLIDSWITCH2_MIN_DUTY_CYCLE; duty_cycle <= SOLIDSWITCH2_MAX_DUTY_CYCLE; duty_cycle += 5 )
    {
        if ( SOLIDSWITCH2_OK == solidswitch2_write_register ( &solidswitch2, SOLIDSWITCH2_REG_PWM_GEN_DC, 
                                                              ( uint8_t ) ( SOLIDSWITCH2_MAX_DUTY_CYCLE - duty_cycle ) ) )
        {
            log_printf ( &logger, " PWM GEN DC: %u\r\n", ( SOLIDSWITCH2_MAX_DUTY_CYCLE - duty_cycle ) );
        }
        if ( SOLIDSWITCH2_OK == solidswitch2_write_register ( &solidswitch2, SOLIDSWITCH2_REG_PWM_LED_DC, ( uint8_t ) duty_cycle ) )
        {
            log_printf ( &logger, " PWM LED DC: %u\r\n", duty_cycle );
        }
        solidswitch2_toggle_in0_pin ( &solidswitch2 );
        log_printf ( &logger, " Toggle IN0 pin\r\n" );
        solidswitch2_toggle_in1_pin ( &solidswitch2 );
        log_printf ( &logger, " Toggle IN1 pin\r\n\n" );
        Delay_ms ( 250 );
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
