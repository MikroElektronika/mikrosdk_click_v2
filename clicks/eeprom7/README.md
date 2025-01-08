
---
# EEPROM 7 Click

> [EEPROM 7 Click](https://www.mikroe.com/?pid_product=MIKROE-4421) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4421&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This is an example that demonstrates the use of the EEPROM 7 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.EEPROM7

### Example Key Functions

- `eeprom7_cfg_setup` Config Object Initialization function.
```c
void eeprom7_cfg_setup ( eeprom7_cfg_t *cfg );
```

- `eeprom7_init` Initialization function.
```c
err_t eeprom7_init ( eeprom7_t *ctx, eeprom7_cfg_t *cfg );
```

- `eeprom7_default_cfg` Click Default Configuration function.
```c
err_t eeprom7_default_cfg ( eeprom7_t *ctx );
```

- `eeprom7_sw_reset` Software device reset function.
```c
void eeprom7_sw_reset ( eeprom7_t *ctx );
```

- `eeprom7_write_memory` Write EEPROM memory function.
```c
void eeprom7_write_memory ( eeprom7_t *ctx, uint32_t addr, uint8_t *p_tx_data, uint8_t n_bytes );
```

- `eeprom7_read_memory` Read EEPROM memory function.
```c
void eeprom7_read_memory ( eeprom7_t *ctx, uint32_t addr, uint8_t *p_rx_data, uint8_t n_bytes);
```

### Application Init

> Initialization driver enables - SPI, also write log.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    eeprom7_cfg_t eeprom7_cfg;  /**< Click config object. */

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

    eeprom7_cfg_setup( &eeprom7_cfg );
    EEPROM7_MAP_MIKROBUS( eeprom7_cfg, MIKROBUS_1 );
    err_t init_flag  = eeprom7_init( &eeprom7, &eeprom7_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    eeprom7_default_cfg ( &eeprom7 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> In this example, we write and then read data from EEPROM memory. Results are being sent to the Usart Terminal where you can track their changes. All data logs write on USB uart changes approximately for every 3 sec.

```c
void application_task ( void ) 
{
    eeprom7_send_cmd( &eeprom7, EEPROM7_OPCODE_STATUS_WREN );
    Delay_ms ( 100 );
    
    eeprom7_write_memory( &eeprom7, 0x00001234, &demo_data[ 0 ], 9 );
    Delay_ms ( 100 );
    
    log_printf( &logger, " > Write data: %s", demo_data );

    while ( eeprom7_is_device_ready( &eeprom7 ) == EEPROM7_DEVICE_IS_READY ) {
        check_status = eeprom7_send_cmd( &eeprom7, EEPROM7_OPCODE_STATUS_WRBP );
        Delay_ms ( 1 );
    }

    eeprom7_read_memory( &eeprom7, 0x00001234, &read_data[ 0 ], 9 );
    Delay_ms ( 100 );
    log_printf( &logger, " > Read data: %s", read_data );


    log_printf( &logger, "---------------------\r\n" );
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
