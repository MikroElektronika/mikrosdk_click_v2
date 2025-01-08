
---
# ISM RX 2 Click

> [ISM RX 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4230) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4230&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Feb 2023.
- **Type**          : GPIO type

# Software Support

## Example Description

> This application shows capability of ISM RX 2 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ISMRX2

### Example Key Functions

- `ismrx2_cfg_setup` Config Object Initialization function.
```c
void ismrx2_cfg_setup ( ismrx2_cfg_t *cfg );
```

- `ismrx2_init` Initialization function.
```c
err_t ismrx2_init ( ismrx2_t *ctx, ismrx2_cfg_t *cfg );
```

- `ismrx2_default_cfg` Click Default Configuration function.
```c
err_t ismrx2_default_cfg ( ismrx2_t *ctx );
```

- `ismrx2_get_data_pin_state` ISM RX 2 get state of DATA pin function.
```c
uint8_t ismrx2_get_data_pin_state ( ismrx2_t *ctx );
```

- `ismrx2_read_manchester_data` ISM RX 2 read manchester encoded data function.
```c
err_t ismrx2_read_manchester_data ( ismrx2_t *ctx, uint8_t *data_out );
```

- `ismrx2_read_rf_data` ISM RX 2 read data function.
```c
err_t ismrx2_read_rf_data ( ismrx2_t *ctx, uint8_t *data_out );
```

### Application Init

> Initialize GPIO pins and LOG module and sets default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ismrx2_cfg_t ismrx2_cfg;  /**< Click config object. */

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
    ismrx2_cfg_setup( &ismrx2_cfg );
    ISMRX2_MAP_MIKROBUS( ismrx2_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == ismrx2_init( &ismrx2, &ismrx2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ISMRX2_ERROR == ismrx2_default_cfg ( &ismrx2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Wait for the data pin to go down and start sampling and wait for sync word if it's received 
collect data to buffer till it receives 0 byte

```c
void application_task ( void ) 
{
#ifdef DEFAULT_EXAMPLE
    
    if ( ISMRX2_PIN_STATE_LOW == ismrx2_get_data_pin_state( &ismrx2 ) )
    {
        if ( ISMRX2_OK == ismrx2_read_rf_data( &ismrx2, read_data ) )
        {
            log_printf( &logger, " RX data: " );
            for ( uint8_t n_cnt = 0; n_cnt < strlen( read_data ); n_cnt++ )
            {
                if ( read_data[ n_cnt ] != '\0' )
                {
                    log_printf( &logger, "%c", read_data[ n_cnt ] );
                }
            }    
            log_printf( &logger, "\r\n*********************\r\n" );
            Delay_ms ( 10 );
        }
    }
#endif
#ifdef MANCHESTER_EXAMPLE 
    if ( ISMRX2_PIN_STATE_LOW == ismrx2_get_data_pin_state( &ismrx2 ) )
    {
        if ( ISMRX2_OK == ismrx2_read_manchester_data( &ismrx2, &read_data ) )
        {
            log_printf( &logger, " Read data: " );
            for ( uint8_t n_cnt = 1; n_cnt < strlen( read_data ); n_cnt++ )
            {
                log_printf( &logger, "%c", read_data[ n_cnt ] );
            }
            log_printf( &logger, "\r\n*********************\r\n" );
            Delay_ms ( 10 );
        }
    }
#endif
}
```

### Note

> Application task is broken down into two parts:
  DEFAULT_EXAMPLE - Collects data from the OOK TX Click board and displays it on the 
  USB UART terminal.
  MANCHESTER_EXAMPLE - Collects Manchester encoded data from the ISM TX Click board, 
  decodes it and displays it on the USB UART terminal.

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
