
---
# Analog MUX Click

> [Analog MUX Click](https://www.mikroe.com/?pid_product=MIKROE-4111) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4111&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : ADC type

# Software Support

## Example Description

> This example showcases how to initialize, configure and use the Analog MUX Click module. 
> The Click switches one of the 16 inputs to output so the adc value of that input 
> can be read on the COM (AN) pin. The RST, PWM, CS and INT are used as control output pins. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AnalogMUX

### Example Key Functions

- `analogmux_cfg_setup` Config Object Initialization function. 
```c
void analogmux_cfg_setup ( analogmux_cfg_t *cfg );
``` 
 
- `analogmux_init` Initialization function. 
```c
err_t analogmux_init ( analogmux_t *ctx, analogmux_cfg_t *cfg );
```

- `analogmux_get_voltage` Generic read voltage function. 
```c
float analogmux_get_voltage ( float adc_val, uint16_t vref, uint16_t rez );
```
 
- `analogmux_set_channel` This function sets the active channel on the MUX. 
```c
void analogmux_set_channel ( analogmux_t *ctx, uint8_t cfg );
```

### Application Init

> This function initializes and configures the logger and Click modules.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    analogmux_cfg_t cfg;

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
    Delay_100ms( );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    analogmux_cfg_setup( &cfg );
    ANALOGMUX_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    analogmux_init( &analogmux, &cfg );

    analogmux_set_channel( &analogmux, ANALOGMUX_CHANNEL_0 );
    log_printf( &logger, " Channel 0 enabled\r\n" );
    log_printf( &logger, " -------------------\r\n" );
}
```

### Application Task

> This function reads ADC value and voltage from channel 0 (AN0) and shows the results 
> on the USB UART every 2 seconds.

```c
void application_task ( void )
{
    uint16_t tmp;
    float val;

    tmp = analogmux_generic_read( &analogmux );
    
    log_printf( &logger, " ADC value : %u\r\n", tmp );

    val = analogmux_generic_read_voltage( &analogmux );

    log_printf( &logger, " Voltage: %.3f mV\r\n", val );
    log_printf( &logger, " -------------------\r\n" );

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
