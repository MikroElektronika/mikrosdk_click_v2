
---
# Analog MUX 5 Click

> [Analog MUX 5 Click](https://www.mikroe.com/?pid_product=MIKROE-5120) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5120&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nikola Peric
- **Date**          : Apr 2022.
- **Type**          : ADC type

# Software Support

## Example Description

> This example showcases how to initialize, configure and use the Analog MUX 5 Click module.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AnalogMUX5

### Example Key Functions

- `analogmux5_cfg_setup` Config Object Initialization function.
```c
void analogmux5_cfg_setup ( analogmux5_cfg_t *cfg );
```

- `analogmux5_init` Initialization function.
```c
err_t analogmux5_init ( analogmux5_t *ctx, analogmux5_cfg_t *cfg );
```

- `analogmux5_default_cfg` Click Default Configuration function.
```c
err_t analogmux5_default_cfg ( analogmux5_t *ctx );
```

- `analogmux5_enable` Analog MUX 5 enable function.
```c
void analogmux5_enable ( analogmux5_t *ctx );
```

- `analogmux5_select_ch` Analog MUX 5 set channel function.
```c
err_t analogmux5_select_ch ( analogmux5_t *ctx, uint8_t ch_select );
```

- `analogmux5_read_an_pin_voltage` Analog MUX 5 read AN pin voltage level function.
```c
err_t analogmux5_read_an_pin_voltage ( analogmux5_t *ctx, float *data_out );
```

### Application Init

> Initializes the driver and enables the analog inputs.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    analogmux5_cfg_t analogmux5_cfg;  /**< Click config object. */

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
    analogmux5_cfg_setup( &analogmux5_cfg );
    ANALOGMUX5_MAP_MIKROBUS( analogmux5_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == analogmux5_init( &analogmux5, &analogmux5_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ANALOGMUX5_ERROR == analogmux5_default_cfg ( &analogmux5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This is an example that shows the use of a Analog MUX 5 Click board
> In this example, we switch from channel AN1 to channel AN4, 
> read and display the analog value and voltage on the active channel.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    float analogmux5_an_voltage = 0;

    analogmux5_select_ch( &analogmux5, ANALOGMUX5_SEL_CH_1 );
    Delay_ms ( 100 );
        
    if ( ADC_ERROR != analogmux5_read_an_pin_voltage ( &analogmux5, &analogmux5_an_voltage ) ) 
    {
        log_printf( &logger, " Channel [ 1 ] ---> AN Voltage : %.3f[V]\r\n\n", analogmux5_an_voltage );
    }
    
    analogmux5_select_ch( &analogmux5, ANALOGMUX5_SEL_CH_2 );
    Delay_ms ( 100 );
        
    if ( ADC_ERROR != analogmux5_read_an_pin_voltage ( &analogmux5, &analogmux5_an_voltage ) ) 
    {
        log_printf( &logger, " Channel [ 2 ] ---> AN Voltage : %.3f[V]\r\n\n", analogmux5_an_voltage );
    }
    
    analogmux5_select_ch( &analogmux5, ANALOGMUX5_SEL_CH_3 );
    Delay_ms ( 100 );
        
    if ( ADC_ERROR != analogmux5_read_an_pin_voltage ( &analogmux5, &analogmux5_an_voltage ) ) 
    {
        log_printf( &logger, " Channel [ 3 ] ---> AN Voltage : %.3f[V]\r\n\n", analogmux5_an_voltage );
    }
    
    analogmux5_select_ch( &analogmux5, ANALOGMUX5_SEL_CH_4 );
    Delay_ms ( 100 );
        
    if ( ADC_ERROR != analogmux5_read_an_pin_voltage ( &analogmux5, &analogmux5_an_voltage ) ) 
    {
        log_printf( &logger, " Channel [ 4 ] ---> AN Voltage : %.3f[V]\r\n\n", analogmux5_an_voltage );
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
