
---
# ISM TX Click

> [ISM TX Click](https://www.mikroe.com/?pid_product=MIKROE-4242) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4242&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Jan 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This application shows capability of ISM TX Click board. 
It sets default configuration, and transmits data in 
manchester encoding with FSK or ASK signal modulation.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ISMTX

### Example Key Functions

- `ismtx_cfg_setup` Config Object Initialization function.
```c
void ismtx_cfg_setup ( ismtx_cfg_t *cfg );
```

- `ismtx_init` Initialization function.
```c
err_t ismtx_init ( ismtx_t *ctx, ismtx_cfg_t *cfg );
```

- `ismtx_default_cfg` Click Default Configuration function.
```c
err_t ismtx_default_cfg ( ismtx_t *ctx );
```

- `ismtx_set_cfg` ISM TX writing configuration.
```c
err_t ismtx_set_cfg ( ismtx_t *ctx, uint8_t cfg_macro, uint8_t cfg_value )
```

- `ismtx_set_frequency` Setting specific frequency for transmission.
```c
err_t ismtx_set_frequency ( ismtx_t *ctx, uint32_t freq )
```

- `ismtx_transmit_data` Function for transmitting data with preamble byte and lenght.
```c
err_t ismtx_transmit_data ( ismtx_t *ctx, uint8_t preamble_byte, uint8_t *tx_data, uint8_t tx_data_len );
```

### Application Init

> Initialization of log and communication, set's signal modulation, 
 resets device, and set's default configuration for selected modulation.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    ismtx_cfg_t ismtx_cfg;  /**< Click config object. */

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
    ismtx_cfg_setup( &ismtx_cfg );
    ISMTX_MAP_MIKROBUS( ismtx_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == ismtx_init( &ismtx, &ismtx_cfg ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    ismtx.modulation = ISM_TX_MODULATION_FSK;

    ismtx_soft_reset( &ismtx );
    
    if ( ismtx_default_cfg ( &ismtx ) < 0 )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, select correct signal modulation... " );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Transmits data via external antenna in span of 100ms.

```c
void application_task ( void ) 
{
    log_info( &logger, " Data sent: %s", tx_data_buf );
    ismtx_transmit_data( &ismtx, PREAMBLE_BYTE, tx_data_buf, sizeof( tx_data_buf ) );
    Delay_ms ( 100 );
}
```

### Note

> Default configuration configures device and set's transmission frequency to 433.92 MHz.
 If selected modulation is FSK frequency deviation is set to 40kHz.

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
