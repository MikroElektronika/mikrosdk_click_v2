\mainpage Main Page
 
 

---
# Flash 5 click

Flash 5 Click is a perfect solution for the mass storage option in various embedded applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/flash5_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/flash-5-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Flash5 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Flash5 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void flash5_cfg_setup ( flash5_cfg_t *cfg ); 
 
- Initialization function.
> FLASH5_RETVAL flash5_init ( flash5_t *ctx, flash5_cfg_t *cfg );


#### Example key functions :

- Function for setting page read
> void flash5_page_read ( flash5_t *ctx, uint16_t page_num );
 
- Function for loading one page
> void flash5_page_load_memory ( flash5_t *ctx, uint16_t column_addr, uint8_t *data_buf, uint16_t buf_size );

- Function for writing status data
> void flash5_write_status_data ( flash5_t *ctx, uint8_t status_cmd, uint8_t status_addr, uint8_t status_data );

## Examples Description

> This application is for storing mass storage.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver, resets device, erasing one page of memory, tests communication and configures device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    flash5_cfg_t cfg;
    uint8_t device_check = 0;

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

    flash5_cfg_setup( &cfg );
    FLASH5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    flash5_init( &flash5, &cfg );

    log_printf( &logger, " - Reseting device... \r\n" );
 
    flash5_software_reset( &flash5 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " - Erasing memory... \r\n" );   
    
    flash5_send_cmd( &flash5, FLASH5_CMD_WRITE_ENABLE );
    flash5_erase_page_data( &flash5, 0x0001 );
    
    device_check = flash5_device_id_check( &flash5 );

    if ( device_check == FLASH5_DEVICE_OK )
    {
        log_printf( &logger, " - Device OK \r\n" );  
    }
    else
    {
        log_printf( &logger, " - Device Error \r\n" );  
        for( ; ; );
    }
    Delay_ms ( 100 );
    
    log_printf( &logger, " - Configuring device \r\n" );  

    flash5_write_status_data( &flash5, FLASH5_CMD_WRITE_REG_STATUS1, FLASH5_REG_STATUS_1, FLASH5_RS1_WRITE_PROTECTION_DISABLE | 
                                                                                          FLASH5_RS1_SRP1_ENABLE );
    flash5_write_status_data( &flash5, FLASH5_CMD_WRITE_REG_STATUS1, FLASH5_REG_STATUS_1, FLASH5_RS2_PAGE_READ_MODE );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "***** App init ***** \r\n" );
    log_printf( &logger, "------------------- \r\n" );
    Delay_ms ( 500 );
}
  
```

### Application Task

> Writes "MikroE" to device memory and then reads it and sends it to log.

```c

void application_task ( )
{
    char read_buf[ 6 ];
    uint8_t n_counter;

    flash5_send_cmd( &flash5, FLASH5_CMD_WRITE_ENABLE );
    flash5_page_load_memory( &flash5, 0x000A, &write_buf[ 0 ], 6 );
    flash5_page_read_memory( &flash5, 0x000A, &read_buf[ 0 ], 6 );

    for( n_counter = 0; n_counter < 6; n_counter++ )
    {
        log_printf( &logger, " %c ", &read_buf[ n_counter ] );
        Delay_ms ( 100 );
    }
    
    log_printf( &logger, " \r\n" );
    log_printf( &logger, "------------------- \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Flash5

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
