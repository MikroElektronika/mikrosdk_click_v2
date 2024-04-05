
---
# MAC Address  click

MAC Address click provides a unique node address for your application. It also has 1Kbit of writable EEPROM memory.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/macaddress_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/mac-address-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the MacAddress Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for MacAddress Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void macaddress_cfg_setup ( macaddress_cfg_t *cfg ); 
 
- Initialization function.
> MACADDRESS_RETVAL macaddress_init ( macaddress_t *ctx, macaddress_cfg_t *cfg );

#### Example key functions :

- Generic read mac address function
> void macaddress_get_mac ( macaddress_t *ctx, uint8_t *read_mac );

- Generic read the byte of data function
> uint8_t macaddress_read_byte ( macaddress_t *ctx, uint8_t reg_address );

## Examples Description

> This application provides a unique node address for your application.

**The demo application is composed of two sections :**

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

> This is an example which demonstrates the use of MAC Address click board.
> MAC Address click communicates with register via I2C protocol by the write to register and read from the register.
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



The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.MacAddress

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
