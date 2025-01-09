
---
# Current 5 Click

> [Current 5 Click](https://www.mikroe.com/?pid_product=MIKROE-4953) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4953&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Sep 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example application showcases ability of the device
to read raw adc data and calculate the current from it.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Current5

### Example Key Functions

- `current5_cfg_setup` Config Object Initialization function.
```c
void current5_cfg_setup ( current5_cfg_t *cfg );
```

- `current5_init` Initialization function.
```c
err_t current5_init ( current5_t *ctx, current5_cfg_t *cfg );
```

- `current5_get_current` Get current.
```c
err_t current5_get_current ( current5_t *ctx, float *current )
```

- `current5_get_adc` Read raw adc value.
```c
err_t current5_get_adc ( current5_t *ctx, uint16_t *adc_data )
```

- `current5_get_alert` Get alert pin state.
```c
uint8_t current5_get_alert ( current5_t *ctx )
```

### Application Init

> Initialization of communication modules(SPI, UART) and 
additional pins for controlling device(RST, ALERT->INT).

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    current5_cfg_t current5_cfg;  /**< Click config object. */

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
    current5_cfg_setup( &current5_cfg );
    CURRENT5_MAP_MIKROBUS( current5_cfg, MIKROBUS_1 );
    err_t init_flag  = current5_init( &current5, &current5_cfg );
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Read ADC data with SPI communication and calculate input current.

```c
void application_task ( void )
{
    float current = 0;
    current5_get_current( &current5, &current );
    log_printf( &logger, " > Current[ A ]: %.2f\r\n", current );
    log_printf( &logger, "*************************************************\r\n" );
    Delay_ms ( 300 );
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
