
---
# Buck 16 Click

> [Buck 16 Click](https://www.mikroe.com/?pid_product=MIKROE-4846) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4846&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Sep 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example showcases ability of the device to
control voltage output of device. Output voltage 
can range from 800 to 5500 depending of VIN. By default
it will go from 800 to 3300 VIN==VCC.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck16

### Example Key Functions

- `buck16_cfg_setup` Config Object Initialization function.
```c
void buck16_cfg_setup ( buck16_cfg_t *cfg );
```

- `buck16_init` Initialization function.
```c
err_t buck16_init ( buck16_t *ctx, buck16_cfg_t *cfg );
```

- `buck16_enable_output` Enable/Disable voltage output.
```c
void buck16_enable_output ( buck16_t *ctx, uint8_t enable );
```

- `buck16_set_potentiometer` Set potentiometer resistivity.
```c
err_t buck16_set_potentiometer ( buck16_t *ctx, uint16_t rwb );
```

- `buck16_set_output` Set output voltage.
```c
err_t buck16_set_output ( buck16_t *ctx, uint16_t vout );
```

### Application Init

> Initialization of communication modules (SPI, UART) 
and additional pin for enabling output and sets it to
high.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    buck16_cfg_t buck16_cfg;    /**< Click config object. */

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
    log_printf( &logger, "\r> Application Init <\r\n" );

    // Click initialization.
    buck16_cfg_setup( &buck16_cfg );
    BUCK16_MAP_MIKROBUS( buck16_cfg, MIKROBUS_1 );
    err_t init_flag  = buck16_init( &buck16, &buck16_cfg );
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    buck16_enable_output( &buck16, 1 );
    log_printf( &logger, "> Application Task <\r\n" );
}
```

### Application Task

> Sets voltage output first to 900mV then to 2500 mV.
Then disables and enables output by toggling pin.
In the end sets output value to 1500mV.

```c
void application_task ( void )
{
    log_printf( &logger, " > Setting output to 0.9V\r\n" );
    buck16_set_output( &buck16, 900 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " > Setting output to 2.5V\r\n" );
    buck16_set_output( &buck16, 2500 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " > Disable output\r\n" );
    buck16_enable_output( &buck16, 0 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " > Enable output\r\n" );
    buck16_enable_output( &buck16, 1 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " > Setting output to 1.5V\r\n" );
    buck16_set_output( &buck16, 1500 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
