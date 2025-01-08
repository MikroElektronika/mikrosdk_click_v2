
---
# MAC Address  Click

> [MAC Address Click](https://www.mikroe.com/?pid_product=MIKROE-2733) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2733&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application provides a unique node address for your application.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.MacAddress

### Example Key Functions

- `macaddress_cfg_setup` Config Object Initialization function. 
```c
void macaddress_cfg_setup ( macaddress_cfg_t *cfg );
``` 
 
- `macaddress_init` Initialization function. 
```c
err_t macaddress_init ( macaddress_t *ctx, macaddress_cfg_t *cfg );
```

- `macaddress_get_mac` Generic read mac address function. 
```c
void macaddress_get_mac ( macaddress_t *ctx, uint8_t *read_mac );
```

- `macaddress_read_byte` Generic read the byte of data function. 
```c
uint8_t macaddress_read_byte ( macaddress_t *ctx, uint8_t reg_address );
```

### Application Init

> Initialization driver enables - I2C, also write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    macaddress_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    macaddress_cfg_setup( &cfg );
    MACADDRESS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    macaddress_init( &macaddress, &cfg );
    
    macaddress_get_mac( &macaddress, mac_addr );
    
    log_printf( &logger, " > MAC Address: 0x" );
    for ( uint8_t cnt = 0; cnt < 8; cnt++ )
    {
        log_printf( &logger, "%02X", (uint16_t)mac_addr[ cnt ] );
    }
    log_printf( &logger, "\r\n" );

    Delay_ms ( 1000 );
    log_info( &logger, "---- Application Task ----" );
    data_cnt = 0;
}
```

### Application Task

> This is an example which demonstrates the use of MAC Address Click board.
> MAC Address Click communicates with register via I2C protocol by the write to register and read from the register.
> This example shows write/read sequential write/read from EEPROM.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void )
{
    log_printf( &logger, " > Writing data to memory...\r\n" );
    Delay_ms ( 100 );
    macaddress_generic_write( &macaddress, address, write_data[ data_cnt ], data_len[ data_cnt ] );
    log_printf( &logger, " > Writing done.\r\n" );
    Delay_ms ( 1000 );
    
    
    log_printf( &logger, " > Reading data from memory...\r\n" );
    macaddress_generic_read( &macaddress, address, read_buff, data_len[ data_cnt ] );
    Delay_ms ( 100 );
    log_printf( &logger, " > Read data: " );
    for( uint8_t cnt = 0; cnt < data_len[ data_cnt ]; cnt++ )
    {
        log_printf( &logger, "%c", read_buff[ cnt ] );
    }
    log_printf( &logger, "\r\n" );
    Delay_ms ( 100 );
    log_printf( &logger, " > Reading done.\r\n" );
    log_printf( &logger, "---------------------------------\r\n" );
    data_cnt++;
    if ( data_cnt >= 3 )
        data_cnt = 0;
    
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
