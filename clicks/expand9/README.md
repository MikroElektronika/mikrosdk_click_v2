
---
# Expand 9 Click

> [Expand 9 Click](https://www.mikroe.com/?pid_product=MIKROE-4853) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4853&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Aug 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This is an example that demonstrates the use of the Expand 9 Click board&trade;.
> The library initializes and defines the I2C bus drivers 
> to write and read data from registers. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand9

### Example Key Functions

- `expand9_cfg_setup` Config Object Initialization function.
```c
void expand9_cfg_setup ( expand9_cfg_t *cfg );
```

- `expand9_init` Initialization function.
```c
err_t expand9_init ( expand9_t *ctx, expand9_cfg_t *cfg );
```

- `expand9_default_cfg` Click Default Configuration function.
```c
err_t expand9_default_cfg ( expand9_t *ctx );
```

- `expand9_set_ch_output_state` Expand 9 set channel output state function.
```c
err_t expand9_set_ch_output_state ( expand9_t *ctx, uint8_t ch_pos, expand9_ch_state_value_t ch_state );
```

- `expand9_led_driver_config` Expand 9 LED driver configuration function.
```c
err_t expand9_led_driver_config ( expand9_t *ctx, uint8_t ch_pos, uint8_t freq_div, uint8_t lin_log );
```

- `expand9_soft_reset` Expand 9 software reset function.
```c
err_t expand9_soft_reset ( expand9_t *ctx );
```

### Application Init

> The initialization of I2C  module, log UART, and additional pins. 
> After driver initialization the app set default settings.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    expand9_cfg_t expand9_cfg;  /**< Click config object. */

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
    expand9_cfg_setup( &expand9_cfg );
    EXPAND9_MAP_MIKROBUS( expand9_cfg, MIKROBUS_1 );
    err_t init_flag = expand9_init( &expand9, &expand9_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    expand9_default_cfg ( &expand9 );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> his is an example that demonstrates the use of the Expand 9 Click board&trade;.
> This example shows the capabilities of the Expand 9 Click by toggling each of 16 available channels.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{   
    expand9_soft_reset( &expand9 );
    Delay_ms ( 100 );
    
    for ( uint8_t cnt = 0; cnt < 16; cnt++ )
    {
        expand9_set_ch_output_state( &expand9, cnt, CH_OUTPUT_ON );
        Delay_ms ( 100 );
        expand9_set_ch_output_state( &expand9, cnt, CH_OUTPUT_OFF );
        Delay_ms ( 100 );
    }
    
    for ( uint8_t cnt = 15; cnt > 0; cnt-- )
    {
        expand9_set_ch_output_state( &expand9, cnt, CH_OUTPUT_ON );
        Delay_ms ( 100 );
        expand9_set_ch_output_state( &expand9, cnt, CH_OUTPUT_OFF );
        Delay_ms ( 100 );
    }
    
    expand9_soft_reset( &expand9 );
    Delay_ms ( 100 );
    
    for ( uint8_t cnt = 0; cnt < 16; cnt++ )
    {
        expand9_led_driver_config( &expand9, cnt, EXPAND9_FREQ_DIV_1, EXPAND9_LED_MODE_LINEAR );
        expand9_set_intensity( &expand9, cnt, 10 );
        Delay_ms ( 100 );
        expand9_led_driver_config( &expand9, cnt, EXPAND9_FREQ_DIV_1, EXPAND9_LED_MODE_LINEAR );
        expand9_set_intensity( &expand9, cnt, 200 );
        Delay_ms ( 100 );
    }
    
    for ( uint8_t cnt = 15; cnt > 0; cnt-- )
    {
        expand9_led_driver_config( &expand9, cnt, EXPAND9_FREQ_DIV_1, EXPAND9_LED_MODE_LINEAR );
        expand9_set_intensity( &expand9, cnt, 200 );
        Delay_ms ( 100 );
        expand9_led_driver_config( &expand9, cnt, EXPAND9_FREQ_DIV_1, EXPAND9_LED_MODE_LINEAR );
        expand9_set_intensity( &expand9, cnt, 10 );
        Delay_ms ( 100 );
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
