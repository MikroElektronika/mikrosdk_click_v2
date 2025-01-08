
---
# Buck 5 Click

> [Buck 5 Click](https://www.mikroe.com/?pid_product=MIKROE-3100) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3100&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : sep 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> Buck 5 Click is a high-efficiency buck DC/DC converter, which can provide digitally 
> adjusted step-down voltage on its output while delivering a considerable amount of current. 
> Buck 5 Click accepts a wide voltage range on its input - from 5V to 30V. The output voltage 
> may be adjusted via the SPI interface, in the range from 0.9V to approximately 5.5V.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck5

### Example Key Functions

- `buck5_cfg_setup` Config Object Initialization function. 
```c
void buck5_cfg_setup ( buck5_cfg_t *cfg );
``` 
 
- `buck5_init` Initialization function. 
```c
err_t buck5_init ( buck5_t *ctx, buck5_cfg_t *cfg );
```

- `buck5_power_on` This function wake up the chip. 
```c
void buck5_power_on ( buck5_t *ctx );
```
 
- `buck5_reset` This function reset the chip. 
```c
void buck5_reset ( buck5_t *ctx );
```

- `buck5_set_output_voltage` Maximum output voltage is 5.5V (255 set value), and minimum output voltage is 1V (0 set value). 
```c
void buck5_set_output_voltage ( buck5_t *ctx, uint8_t voltage );
```

### Application Init

> Initializes driver init, and enables the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    buck5_cfg_t cfg;

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

    buck5_cfg_setup( &cfg );
    BUCK5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck5_init( &buck5, &cfg );

    buck5_power_on( &buck5 );
    buck5_reset( &buck5 );
}
```

### Application Task

> Increases the output voltage by 500mV every 3 seconds from MIN to MAX VOUT.

```c
void application_task ( void )
{
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_MIN );
    log_printf( &logger, "VOUT: MIN\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_1000mV );
    log_printf( &logger, "VOUT: ~1V\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_1500mV );
    log_printf( &logger, "VOUT: ~1.5V\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_2000mV );
    log_printf( &logger, "VOUT: ~2V\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_2500mV );
    log_printf( &logger, "VOUT: ~2.5V\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_3000mV );
    log_printf( &logger, "VOUT: ~3V\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_3500mV );
    log_printf( &logger, "VOUT: ~3.5V\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_4000mV );
    log_printf( &logger, "VOUT: ~4V\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_4500mV );
    log_printf( &logger, "VOUT: ~4.5V\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_5000mV );
    log_printf( &logger, "VOUT: ~5V\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_MAX );
    log_printf( &logger, "VOUT: MAX\r\n" );
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
