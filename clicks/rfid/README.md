
---
# RFID Click

> [RFID Click](https://www.mikroe.com/?pid_product=MIKROE-1434) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1434&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of RFID Click board by reading MIFARE ISO/IEC 14443 type A tag UID.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RFID

### Example Key Functions

- `rfid_cfg_setup` Config Object Initialization function.
```c
void rfid_cfg_setup ( rfid_cfg_t *cfg );
```

- `rfid_init` Initialization function.
```c
err_t rfid_init ( rfid_t *ctx, rfid_cfg_t *cfg );
```

- `rfid_default_cfg` Click Default Configuration function.
```c
void rfid_default_cfg ( rfid_t *ctx );
```

- `rfid_select_communication_interface` Select communication interface.
```c
err_t rfid_select_communication_interface ( rfid_t* ctx, uint8_t com_interface );
```

- `rfid_get_tag_uid` Get RFID tag uid function.
```c
err_t rfid_get_tag_uid ( rfid_t *ctx, uint8_t rfid_protocol, uint8_t *tag_uid );
```

- `rfid_get_device_id` RFID get device id function.
```c
err_t rfid_get_device_id ( rfid_t *ctx, uint8_t *device_id );
```

### Application Init

> Initializes the driver, selects the communication interface and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rfid_cfg_t rfid_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );

    // Click initialization.

    rfid_cfg_setup( &rfid_cfg );
    RFID_MAP_MIKROBUS( rfid_cfg, MIKROBUS_1 );
    err_t error_flag = rfid_init( &rfid, &rfid_cfg );
    if ( error_flag != RFID_OK ) 
    {
        log_error( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    log_printf( &logger, " Selecting communication interface... \r\n" );
    error_flag = rfid_select_communication_interface ( &rfid, RFID_SPI );
    if ( error_flag != RFID_OK ) 
    {
        log_error( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    log_printf( &logger, " Configuring the device... \r\n" );
    error_flag = rfid_default_cfg ( &rfid );
    if ( error_flag != RFID_OK ) 
    {
        log_error( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    log_printf( &logger, " The device has been configured! \r\n" );
}
```

### Application Task

> If there's a tag detected, it reads its UID and displays it on USB UART.

```c
void application_task ( void )
{
    uint8_t tag_uid[ 20 ] = { 0 };
    uint8_t tag_len = rfid_get_tag_uid( &rfid, RFID_ISO_14443A, tag_uid );
    if ( tag_len > 0 )
    {
        log_printf( &logger, " TAG UID: " );
        for ( uint8_t cnt = 0; cnt < tag_len; cnt++ )
        {
            log_printf( &logger, "0x%.2X ", ( uint16_t ) tag_uid[ cnt ] );
        }
        log_printf( &logger, "\r\n----------------------------------\r\n" );
        Delay_ms ( 1000 );
    }
}
```

### Note

> It is recommended to tie SSI_0, SSI_1 to VCC/GND at power-up, depending on 
> the communication interface selection by A and B on-board jumpers. 
> SSI_0 - UART: 0 SPI: 1
> SSI_1 - UART: 0 SPI: 0
> 
> Only tags with 4-byte or 7-byte UIDs are compatible with this example.
> We recommend MIKROE-1475 - an RFiD tag 13.56MHz compliant with ISO14443-A standard.

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
