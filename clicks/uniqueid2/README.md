
---
# UNIQUE ID 2 Click

> [UNIQUE ID 2 Click](https://www.mikroe.com/?pid_product=MIKROE-7077) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7077&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Jun 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of UNIQUE ID 2 Click board by reading and
displaying the unique identifier, and by writing data to the memory and
reading it back.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.UNIQUEID2

### Example Key Functions

- `uniqueid2_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void uniqueid2_cfg_setup ( uniqueid2_cfg_t *cfg );
```

- `uniqueid2_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t uniqueid2_init ( uniqueid2_t *ctx, uniqueid2_cfg_t *cfg );
```

- `uniqueid2_default_cfg` This function executes a default configuration of UNIQUE ID 2 Click board.
```c
err_t uniqueid2_default_cfg ( uniqueid2_t *ctx );
```

- `uniqueid2_write_memory` This function writes a desired number of data bytes to the EEPROM memory starting from the selected address.
```c
err_t uniqueid2_write_memory ( uniqueid2_t *ctx, uint32_t address, uint8_t *data_in, uint16_t len );
```

- `uniqueid2_read_memory` This function reads a desired number of data bytes from the EEPROM memory starting from the selected address.
```c
err_t uniqueid2_read_memory ( uniqueid2_t *ctx, uint32_t address, uint8_t *data_out, uint32_t len );
```

- `uniqueid2_read_id_page` This function reads a desired number of data bytes from the identification page.
```c
err_t uniqueid2_read_id_page ( uniqueid2_t *ctx, uint8_t offset, uint8_t *data_out, uint16_t len );
```

### Application Init

> Initializes the driver and logger, performs the default configuration and 
then reads and displays the UID.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    uniqueid2_cfg_t uniqueid2_cfg;  /**< Click config object. */

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
    uniqueid2_cfg_setup( &uniqueid2_cfg );
    UNIQUEID2_MAP_MIKROBUS( uniqueid2_cfg, MIKROBUS_POSITION_UNIQUEID2 );
    if ( I2C_MASTER_ERROR == uniqueid2_init( &uniqueid2, &uniqueid2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( UNIQUEID2_ERROR == uniqueid2_default_cfg ( &uniqueid2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    uint8_t uid[ UNIQUEID2_UID_LEN ] = { 0 };
    uint8_t cnt = 0;

    if ( UNIQUEID2_OK == uniqueid2_read_uid( &uniqueid2, uid ) )
    {
        log_printf( &logger, " UID: " );
        for ( cnt = 0; cnt < UNIQUEID2_UID_LEN; cnt++ )
        {
            log_printf( &logger, "%.2X ", ( uint16_t ) uid[ cnt ] );
        }
        log_printf( &logger, "\r\n" );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Writes a desired number of bytes to the memory and then verifies if it is
written correctly by reading from the same memory location and displaying the
memory content on the USB UART.

```c
void application_task ( void ) 
{
    uint8_t data_buf[ UNIQUEID2_PAGE_SIZE ] = { 0 };

    log_printf( &logger, "\r\n Memory address: 0x%.5lX\r\n", ( uint32_t ) STARTING_ADDRESS );

    /* Write first DEMO message */
    if ( strlen ( DEMO_TEXT_MESSAGE_1 ) > UNIQUEID2_PAGE_SIZE )
    {
        memcpy( data_buf, DEMO_TEXT_MESSAGE_1, UNIQUEID2_PAGE_SIZE );
    }
    else
    {
        memcpy( data_buf, DEMO_TEXT_MESSAGE_1, strlen ( DEMO_TEXT_MESSAGE_1 ) );
    }
    if ( UNIQUEID2_OK == uniqueid2_write_memory( &uniqueid2, STARTING_ADDRESS, data_buf, strlen ( DEMO_TEXT_MESSAGE_1 ) ) )
    {
        log_printf( &logger, " Write data: %s\r\n", data_buf );
    }
    Delay_ms ( 100 );

    /* Read first DEMO message */
    memset( data_buf, 0, sizeof ( data_buf ) );
    if ( UNIQUEID2_OK == uniqueid2_read_memory( &uniqueid2, STARTING_ADDRESS, data_buf, strlen ( DEMO_TEXT_MESSAGE_1 ) ) )
    {
        log_printf( &logger, " Read data: %s\r\n", data_buf );
    }
    Delay_ms ( 1000 );

    /* Write second DEMO message */
    if ( strlen ( DEMO_TEXT_MESSAGE_2 ) > UNIQUEID2_PAGE_SIZE )
    {
        memcpy( data_buf, DEMO_TEXT_MESSAGE_2, UNIQUEID2_PAGE_SIZE );
    }
    else
    {
        memcpy( data_buf, DEMO_TEXT_MESSAGE_2, strlen ( DEMO_TEXT_MESSAGE_2 ) );
    }
    if ( UNIQUEID2_OK == uniqueid2_write_memory( &uniqueid2, STARTING_ADDRESS, data_buf, strlen ( DEMO_TEXT_MESSAGE_2 ) ) )
    {
        log_printf( &logger, " Write data: %s\r\n", data_buf );
    }
    Delay_ms ( 100 );

    /* Read second DEMO message */
    memset( data_buf, 0, sizeof ( data_buf ) );
    if ( UNIQUEID2_OK == uniqueid2_read_memory( &uniqueid2, STARTING_ADDRESS, data_buf, strlen ( DEMO_TEXT_MESSAGE_2 ) ) )
    {
        log_printf( &logger, " Read data: %s\r\n", data_buf );
    }

    Delay_ms ( 1000 );
}

```

### Note

> When using uniqueid2_write_register() note that setting the DAL bit (CDA) or the WPL bit (SWP)
from 0 to 1 is a permanent, irreversible action that freezes the respective register in read-only mode.

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
