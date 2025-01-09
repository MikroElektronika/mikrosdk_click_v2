
---
# GainAMP Click

> [GainAMP Click](https://www.mikroe.com/?pid_product=MIKROE-2555) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2555&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Sep 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This is an example that demonstrates the use of the GainAMP Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.GainAMP

### Example Key Functions

- `gainamp_cfg_setup` Config Object Initialization function.
```c
void gainamp_cfg_setup ( gainamp_cfg_t *cfg );
```

- `gainamp_init` Initialization function.
```c
err_t gainamp_init ( gainamp_t *ctx, gainamp_cfg_t *cfg );
```

- `gainamp_default_cfg` Click Default Configuration function.
```c
err_t gainamp_default_cfg ( gainamp_t *ctx );
```

- `gainamp_read_an_pin_value` GainAMP read AN pin value function.
```c
err_t gainamp_read_an_pin_value ( gainamp_t *ctx, uint16_t *data_out );
```

- `gainamp_read_an_pin_voltage` GainAMP read AN pin voltage level function.
```c
err_t gainamp_read_an_pin_voltage ( gainamp_t *ctx, float *data_out );
```

- `gainamp_set_gain` Function for sets gain of the GainAMP Click.
```c
void gainamp_set_gain ( gainamp_t *ctx, uint8_t gain );
```

### Application Init

> Initializes SPI module and set CS pin and RST pin as OUTPUT, initialization driver init and resets chip.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gainamp_cfg_t gainamp_cfg;  /**< Click config object. */

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

    gainamp_cfg_setup( &gainamp_cfg );
    GAINAMP_MAP_MIKROBUS( gainamp_cfg, MIKROBUS_1 );
    err_t init_flag  = gainamp_init( &gainamp, &gainamp_cfg );
    if ( ( SPI_MASTER_ERROR == init_flag ) || ( ADC_ERROR == init_flag ) ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    gainamp_reset( &gainamp );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Sets the gain for both channels, channel A and channel B.

```c
void application_task ( void )
{
    gainamp_set_gain( &gainamp, GAINAMP_CHANNEL_A_x1 | GAINAMP_CHANNEL_B_x5 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    gainamp_set_gain( &gainamp, GAINAMP_CHANNEL_A_x10 | GAINAMP_CHANNEL_B_x100 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
