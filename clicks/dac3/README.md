
---
# DAC 3 Click

> [DAC 3 Click](https://www.mikroe.com/?pid_product=MIKROE-2038) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2038&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This example showcases how to initialize, configure and use the DAC 3 Click module. The Click
  performs digital to analog conversion and the output voltage can be read on the output termi-
  nal using a multimeter. An oscilloscope is required to read the analog signal. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DAC3

### Example Key Functions

- `dac3_cfg_setup` Config Object Initialization function. 
```c
void dac3_cfg_setup ( dac3_cfg_t *cfg );
``` 
 
- `dac3_init` Initialization function. 
```c
err_t dac3_init ( dac3_t *ctx, dac3_cfg_t *cfg );
```

- `dac3_default_cfg` Click Default Configuration function. 
```c
void dac3_default_cfg ( dac3_t *ctx );
```

- `dac3_write_all_mem` This function configures the Click module. 
```c
void dac3_write_all_mem ( dac3_t *ctx, uint16_t value );
```
 
- `dac3_send_command` This function sends a command to the Click module using SPI communication. 
```c
void dac3_send_command ( dac3_t *ctx, uint8_t cmd );
```

- `dac3_set_out_voltage` This function sets the output voltage on the Click module terminal. 
```c
void dac3_set_out_voltage ( dac3_t *ctx, uint16_t output );
```

### Application Init

> This function configures and initializes the Click and logger modules. The write_all_mem(...)
  function configures DAC settings. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    dac3_cfg_t cfg;

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

    dac3_cfg_setup( &cfg );
    DAC3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dac3_init( &dac3, &cfg );

    dac3.dac_cfg.vrl = 0;
    dac3.dac_cfg.power = 0;
    dac3.dac_cfg.gain = 0;

    dac3_write_all_mem( &dac3, 0 );
    Delay_100ms( );
}
```

### Application Task

> This function resets and wakes up the Click module and then changes the output voltage on the
  output terminal a few times in a loop with a 5 second delay. It does so every 1 second. 

```c
void application_task ( void )
{
    uint8_t cnt;
    uint32_t output_value;

    output_value = 500;

    dac3_send_command( &dac3, DAC3_RESET );
    Delay_100ms( );

    dac3_send_command( &dac3, DAC3_WAKE_UP );
    Delay_100ms( );

    for ( cnt = 1; cnt < 9; cnt ++ )
    {
        dac3_set_out_voltage( &dac3, output_value * cnt );

        log_printf( &logger, " .current DAC value: %d\r\n", output_value * cnt );
        log_printf( &logger, " .output voltage: %d mV\r\n", ( ( output_value * cnt ) * 79 ) / 64 );
        log_printf( &logger, "-------------------------------\r\n" );

        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }

    log_printf( &logger, "###############################\r\n" );
    Delay_1sec( );
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
