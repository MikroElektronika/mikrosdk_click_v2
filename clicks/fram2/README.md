\mainpage Main Page
 
 

---
# FRAM 2 click

FRAM 2 click carries a ferroelectric RAM module. Ferroelectric RAM, also known as FRAM, is a non-volatile memory type, with characteristics comparable to much faster DRAM memory modules. It offers much faster alternative to common serial FLASH and EEPROM modules, which use the conventional technologies.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/fram2_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/fram-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the FRAM2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for FRAM2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void fram2_cfg_setup ( fram2_cfg_t *cfg ); 
 
- Initialization function.
> FRAM2_RETVAL fram2_init ( fram2_t *ctx, fram2_cfg_t *cfg );

- Click Default Configuration function.
> void fram2_default_cfg ( fram2_t *ctx );


#### Example key functions :

- This function reads content from address and saves it to buffer.
> void fram2_read( fram2_t *ctx, uint32_t address, uint8_t *buffer, uint8_t count ); 

- This function writes content from buffer to address.
> void fram2_write( fram2_t *ctx, uint32_t address, uint8_t *buffer, uint8_t counter );

- This function reads content of FRAM status register.
> uint8_t fram2_read_status( fram2_t *ctx ); 

## Examples Description

> This example performs write & read operation to certain register.

**The demo application is composed of two sections :**

### Application Init 

> Initiazlize device and enable write operation.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    fram2_cfg_t cfg;

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

    fram2_cfg_setup( &cfg );
    FRAM2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    fram2_init( &fram2, &cfg );
    fram2_default_cfg ( &fram2 );

}
  
```

### Application Task

> Write value 42 to register 0x10 and check if operation was done properly.

```c

void application_task ( void )
{
    log_info( &logger, "Writing value 42 into register 0x10..." );  
    test_addr = 0x0010;  
    fram2_write( &fram2, test_addr, data_to_write, 3 );
    Delay_ms( 200 );

    log_info( &logger, "Reading from register 0x10..." );
    memset( read_buf, 0, 32 );
    Delay_ms( 500 );
    
    fram2_read( &fram2, test_addr, read_buf, 3 );
    log_printf ( &logger, "Read value: %s\r\n\n", read_buf );
    Delay_ms( 500 );
} 

```

### Note

> If user doesn't see declarations of some variables in application_init() and application_task(),
they are declared as global in main.c file.

> The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.FRAM2

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
