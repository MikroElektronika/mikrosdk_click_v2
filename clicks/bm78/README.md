
---
# BM78 Click

> [BM78 Click](https://www.mikroe.com/?pid_product=MIKROE-6114) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6114&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Feb 2024.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of BM78 Click board by processing
 the incoming data and displaying them on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BM78

### Example Key Functions

- `bm78_cfg_setup` Config Object Initialization function.
```c
void bm78_cfg_setup ( bm78_cfg_t *cfg );
```

- `bm78_init` Initialization function.
```c
err_t bm78_init ( bm78_t *ctx, bm78_cfg_t *cfg );
```

- `bm78_eeprom_send_cmd` This function is used to send specific EEPROM command by using UART serial interface.
```c
err_t bm78_eeprom_send_cmd ( bm78_t *ctx, uint16_t op_code, uint8_t *param, uint8_t len );
```

- `bm78_eeprom_write` This function is used to write data into the EEPROM location specified by the address parameter.
```c
err_t bm78_eeprom_write ( bm78_t *ctx, uint16_t address, uint8_t *data_in, uint8_t len );
```

- `bm78_flash_eeprom` This function is used write default configuration into the EEPROM.
```c
err_t bm78_flash_eeprom ( bm78_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration by writing it into the EEPROM.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    bm78_cfg_t bm78_cfg;  /**< Click config object. */

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
    bm78_cfg_setup( &bm78_cfg );
    BM78_MAP_MIKROBUS( bm78_cfg, MIKROBUS_1 );
    if ( UART_ERROR == bm78_init( &bm78, &bm78_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    uint8_t tmp_data[ 16 ];
    bm78_generic_read( &bm78, &tmp_data, 1 );  
    Delay_ms ( 100 );

    log_printf( &logger, " = = = = = = = = = = = = = = = = = \r\n" );
    log_printf( &logger, " Place Click into Write EEPROM mode \r\n" );
    log_printf( &logger, " By setting MODE SEL in the following configuration \r\n" );
    log_printf( &logger, "         | 1 | 2 | 3 |             \r\n" );
    log_printf( &logger, "         | H | L | L |             \r\n" );
    log_printf( &logger, " = = = = = = = = = = = = = = = = = \r\n" );
    log_printf( &logger, " Send YES once you placed Click into Write EEPROM mode \r\n" );
    #define WANTED_ANSWER "YES/r/n"
    log_printf( &logger, " = = = = = = = = = = = = = = = = = \r\n" );
    while ( 1 )
    {
        log_read( &logger, &tmp_data, 5 );
        
        if ( 0 == strstr ( WANTED_ANSWER, tmp_data ) )
        {
            break;
        }
        else
        {
            log_printf( &logger, " Send YES once you placed Click into Write EEPROM mode \r\n" );
        }
    }
    bm78_hw_reset( &bm78 );
    log_printf( &logger, " Writing into the EEPROM \r\n" );
    if ( BM78_ERROR == bm78_flash_eeprom ( &bm78 ) )
    {
        log_error( &logger, " EEPROM Flash failed. " );
        log_printf( &logger, " Check Selected Click mode. \r\n" );
        for ( ; ; );
    }

    log_printf( &logger, " = = = = = = = = = = = = = = = = = \r\n" );
    log_printf( &logger, " Place Click into Application mode \r\n" );
    log_printf( &logger, " By setting MODE SEL in the following configuration \r\n" );
    log_printf( &logger, "         | 1 | 2 | 3 |             \r\n" );
    log_printf( &logger, "         | L | L | L |             \r\n" );
    log_printf( &logger, " = = = = = = = = = = = = = = = = = \r\n" );
    log_printf( &logger, " Send YES once you placed Click into Application mode \r\n" );
    log_printf( &logger, " = = = = = = = = = = = = = = = = = \r\n" );
    while ( 1 )
    {
        log_read( &logger, &tmp_data, 5 );
        
        if ( 0 == strstr ( WANTED_ANSWER, tmp_data ) )
        {
            break;
        }
        else
        {
            log_printf( &logger, " Send YES once you placed Click into Application mode \r\n" );
        }
    }
    bm78_hw_reset( &bm78 );

    log_info( &logger, " Application Task " );
    log_printf( &logger, " Connect to the device using the Serial Bluetooth Terminal App \r\n\r\n" );
}
```

### Application Task

> Reads and processes all incoming data from the Serial Bluetooth Terminal smartphone application and displays them on the USB UART.

```c
void application_task ( void ) 
{
    if ( BM78_OK == bm78_process( &bm78 ) ) 
    {
        bm78_log_app_buf( );
        bm78_clear_app_buf( );
    }
}
```

### Note

> We have used the Serial Bluetooth Terminal smartphone application for the test. 
  A smartphone and the Click board must be paired in order to exchange messages with each other.

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
