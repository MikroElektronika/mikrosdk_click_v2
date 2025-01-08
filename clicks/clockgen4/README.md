
---
# Clock Gen 4 Click

> [Clock Gen 4 Click](https://www.mikroe.com/?pid_product=MIKROE-4300) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4300&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jul 2021.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the uses of Clock Gen 4 Click which is based on CS2200-CP for changing the channel clock. The CS2200-CP is an extremely versatile system clocking 
device that utilizes a programmable phase lock loop. The CS2200-CP is based on an analog PLL architecture and this architecture allows for frequency synthesis and clock generation
from a stable reference clock. The CS2200-CP supports both I²C and SPI for full software control.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ClockGen4

### Example Key Functions

- `clockgen4_cfg_setup` Config Object Initialization function.
```c
void clockgen4_cfg_setup ( clockgen4_cfg_t *cfg );
```

- `clockgen4_init` Initialization function.
```c
err_t clockgen4_init ( clockgen4_t *ctx, clockgen4_cfg_t *cfg );
```

- `clockgen4_default_cfg` Click Default Configuration function.
```c
err_t clockgen4_default_cfg ( clockgen4_t *ctx );
```

- `clockgen4_dev_ctl` Function is used to write to device control register in order to apply settings.
```c
void clockgen4_dev_ctl ( clockgen4_t *ctx, uint8_t dev_ctl );
```

- `clockgen4_dev_cfg` Function is used to write to device configuration 1 register in order to apply settings.
```c
void clockgen4_dev_cfg ( clockgen4_t *ctx, uint8_t dev_cfg );
```

- `clockgen4_glob_cfg` Function is used to write to function configuration 2 register in order to apply settings.
```c
void clockgen4_glob_cfg ( clockgen4_t *ctx, uint8_t glob_cfg );
```

### Application Init

> Initializes I2C and SPI, sets CS pin as output and starts to write log, applies default settings and adjusted ratio to obtain a frequency.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;                     /**< Logger config object. */
    clockgen4_cfg_t clockgen4_cfg;         /**< Click config object. */

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
    
    Delay_ms ( 100 );
    log_printf( &logger, "---------------------" );
    log_printf( &logger, "  Clock Gen 4 Click  " );
    log_printf( &logger, "---------------------" );
    
    // Click initialization.
    clockgen4_cfg_setup( &clockgen4_cfg );
    CLOCKGEN4_MAP_MIKROBUS( clockgen4_cfg, MIKROBUS_1 );
    err_t init_flag  = clockgen4_init( &clockgen4, &clockgen4_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    clockgen4_default_cfg ( &clockgen4 );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> Clock Gen 4 Click is used in this example to generate and change the clock on the output channel.

```c
void application_task ( void )
{
    clockgen4_dev_ctl ( &clockgen4, CLOCKGEN4_AUX_OUT_DIS | CLOCKGEN4_CLK_OUT_EN );
    log_printf( &logger, "  PLL Clock          \r\n" );
    log_printf( &logger, "  output enabled!    \r\n" );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 1000 );
    
    clockgen4_dev_ctl ( &clockgen4, CLOCKGEN4_AUX_OUT_EN | CLOCKGEN4_CLK_OUT_DIS );
    log_printf( &logger, "  AUX Clock          \r\n" );
    log_printf( &logger, "  output enabled!    \r\n" );
    log_printf( &logger, "---------------------\r\n" );
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
