\mainpage Main Page
 
 

---
# MAC Address  click

MAC Address click provides a unique node address for your application. It also has 1Kbit of writable EEPROM memory.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/macaddress_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/mac-address-click>)

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

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "    <<  Application Init  >>    " );

    //  Click initialization.

    macaddress_cfg_setup( &cfg );
    MACADDRESS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    macaddress_init( &macaddress, &cfg );

    log_printf( &logger,"      <<   I2C Driver Init   >>      \r\n" );
    Delay_100ms( );
}
  
```

### Application Task

> This is an example which demonstrates the use of MAC Address click board.
> MAC Address click communicates with register via I2C protocol by the write to register and read from the register.
> This example shows write/read single byte and sequential write/read from EEPROM.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on USB uart changes for every 1 sec.

```c

void application_task ( void )
{
    uint8_t cnt;
    uint8_t buffer[ 12 ];
    uint8_t read_mac[ 10 ];
    uint8_t buffer_loop = 0;
    
    macaddress_get_mac( &macaddress, &read_mac );
    Delay_100ms( );

    log_printf( &logger, " MAC Address :  \r\n" );
    for ( cnt = 0; cnt < 6; cnt++ )
    {
        log_printf( &logger, "0x%x", read_mac[ cnt ] );
            
        if ( cnt != 5 )
        {
            log_printf( &logger, ": \r\n" );
        }
    }

    log_printf( &logger, "--------------------------------- \r\n" );
    log_printf( &logger, " Write Single Byte Test :  \r\n" );

    macaddress_generic_write( &macaddress, buffer_loop, &buffer_loop, 1 );

    log_printf( &logger, " Byte value [ 0x%x ] successfully written to [ 0x%x ] address \r\n" , buffer_loop + 1, buffer_loop );
    
    log_printf( &logger, "-----------------------------\r\n" );
    log_printf( &logger, "-----------------------------\r\n" );
    log_printf( &logger, " Read Single Byte Test \r\n");

    macaddress_read_byte( &macaddress, buffer_loop );
    
    log_printf( &logger, " Byte value [ 0x%x ] successfully read from  [ 0x%x ] address \r\n", buffer_loop + 1, buffer_loop );
    log_printf( &logger, "----------------------------- \r\n" );
    log_printf( &logger, "----------------------------- \r\n" );

    macaddress_generic_write( &macaddress, buffer_loop, buffer, 12 );
    Delay_100ms( );

    log_printf( &logger, " Array values : \r\n" );

    for ( cnt = 0; cnt < 12; cnt++ )
    {
        log_printf( &logger,"[ 0x%x ] \r\n", buffer[ cnt ] );
    }

    log_printf( &logger," successfully written to [ 0x%x ] address and forward \r\n", buffer_loop );
    log_printf( &logger, "-----------------------------" );
    log_printf( &logger, "-----------------------------" );

    macaddress_generic_read( &macaddress, buffer_loop, buffer, 12 );
    Delay_100ms( );

    log_printf( &logger, " Array values : \r\n" );

    for ( cnt = 0; cnt < 12; cnt++ )
    {
        log_printf( &logger,"[ 0x%x ]", buffer[ cnt ]); 
    }

    log_printf( &logger," successfully read from [ 0x%x ] address and forward \r\n", buffer_loop );
    log_printf( &logger, "-----------------------------" );
    log_printf( &logger, "-----------------------------" );

    if ( buffer_loop < MACADDRESS_END_ADDR )
    {
        buffer_loop++;
    }
    else
    {
        buffer_loop = 0;
    }

    Delay_1sec( );
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
