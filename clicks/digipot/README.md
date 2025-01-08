
---
# DIGI POT Click

> [DIGI POT Click](https://www.mikroe.com/?pid_product=MIKROE-923) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-923&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> The demo application changes the resistance using DIGIPOT Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DigiPot

### Example Key Functions

- `digipot_cfg_setup` Config Object Initialization function.
```c
void digipot_cfg_setup ( digipot_cfg_t *cfg );
```

- `digipot_init` Initialization function.
```c
err_t digipot_init ( digipot_t *ctx, digipot_cfg_t *cfg );
```

- `digipot_set_wiper_positions` The function sets 8-bit wiper positions data.
```c
void digipot_set_wiper_positions ( digipot_t *ctx, uint8_t wiper_pos );
```

- `digipot_convert_output` The function convert 10-bit ADC value to volatage reference.
```c
float digipot_convert_output ( uint16_t adc_val, float v_ref );
```

### Application Init

> Initializes SPI and LOG modules.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digipot_cfg_t digipot_cfg;  /**< Click config object. */

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

    digipot_cfg_setup( &digipot_cfg );
    DIGIPOT_MAP_MIKROBUS( digipot_cfg, MIKROBUS_1 );
    err_t init_flag  = digipot_init( &digipot, &digipot_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_printf( &logger, "----------------\r\n" );
    log_printf( &logger, " DIGI POT Click\r\n" );
    log_printf( &logger, "----------------\r\n" );
}
```

### Application Task

> This is an example which demonstrates the use of DIGI POT Click board. Increments the wiper position by 10 positions every 5 seconds.

```c
void application_task ( void ) 
{
    for ( uint16_t n_cnt = 127; n_cnt < 255; n_cnt += 10 ) {
        wiper_pos = ( uint8_t ) n_cnt;
        digipot_set_wiper_positions( &digipot, wiper_pos );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
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
