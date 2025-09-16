
---
# ClickID

> [ClickID](https://www.mikroe.com/clickid) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/clickid.png" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2023.
- **Type**          : One Wire type

# Software Support

## Example Description

> This example reads the information from ClickID permanent memory.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ClickID

### Example Key Functions

- `clickid_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void clickid_cfg_setup ( clickid_cfg_t *cfg );
```

- `clickid_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t clickid_init ( clickid_t *ctx, clickid_cfg_t *cfg );
```

- `clickid_check_communication` This function checks the communication by reading the ROM address as well as verifying family code and CRC 8.
```c
err_t clickid_check_communication ( clickid_t *ctx );
```

- `clickid_read_memory` This function reads a desired number of data bytes starting from the selected address of the EEPROM memory using One Wire communication protocol.
```c
err_t clickid_read_memory ( clickid_t *ctx, uint16_t address, uint8_t *data_out, uint16_t len );
```

- `clickid_read_information` This function reads the Click board information from the permanent data memory.
```c
err_t clickid_read_information ( clickid_t *ctx, clickid_information_t *info );
```

### Application Init

> Initializes the driver and checks the communication with the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    clickid_cfg_t clickid_cfg;  /**< ClickID config object. */

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

    // ClickID initialization.
    clickid_cfg_setup( &clickid_cfg );
    CLICKID_MAP_MIKROBUS( clickid_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == clickid_init( &clickid, &clickid_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CLICKID_ERROR == clickid_check_communication ( &clickid ) )
    {
        log_error( &logger, " Communication fail." );
        log_printf( &logger, "Check if the Click is attached to the correct " );
        log_printf( &logger, "MIKROBUS socket, and try again.\r\n" );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the information from ClickID permanent manifest every 5 seconds.

```c
void application_task ( void )
{
    clickid_information_t info;
    if ( CLICKID_OK == clickid_read_information ( &clickid, &info ) )
    {
        log_printf ( &logger, "\r\n --- Click info ---\r\n" );
        log_printf ( &logger, " Name: %s\r\n", info.name );
        log_printf ( &logger, " PID: MIKROE-%u\r\n", info.serial );
        log_printf ( &logger, " HW REV.: %u.%.2u\r\n", 
                     ( uint16_t ) info.hw_rev.major, ( uint16_t ) info.hw_rev.minor );
        log_printf ( &logger, " Type: 0x%.4X\r\n", info.type );
        log_printf ( &logger, " Custom: 0x%.2X\r\n", ( uint16_t ) info.custom );
    }
    
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
