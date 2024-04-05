
---
# ISM RX 2 click

> ISM RX 2 Click is a compact add-on board that contains a pin configurable, low current, sub-GHz EZRadio® receiver. This board features the Si4356, a standalone Sub-GHz RF receiver IC, from Silicon Labs, which provides a true plug-and-play receive option.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ismrx2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ism-rx-2-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Feb 2023.
- **Type**          : GPIO type


# Software Support

We provide a library for the ISM RX 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ISM RX 2 Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This application shows capability of ISM RX 2 Click board.

**The demo application is composed of two sections :**

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

## Note

> Application task is broken down into two parts:
  DEFAULT_EXAMPLE - Collects data from the OOK TX Click board and displays it on the 
  USB UART terminal.
  MANCHESTER_EXAMPLE - Collects Manchester encoded data from the ISM TX Click board, 
  decodes it and displays it on the USB UART terminal.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ISMRX2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
