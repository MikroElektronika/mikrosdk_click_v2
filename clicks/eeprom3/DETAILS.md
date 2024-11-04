

---
# EEPROM 3 Click

EEPROM 3 Click provides 2 Mbit (2,097,152 bits) of Electrically Erasable Programmable Read Only Memory, organized in bytes. In other words, this Click board™ is an EEPROM memory medium with the capacity of 256 KB. The used EEPROM module has outstanding endurance, with 1,000,000 write cycles and data retention period of over 100 years.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/eeprom3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/eeprom-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Eeprom3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Eeprom3 Click driver.

#### Standard key functions :

- `eeprom3_cfg_setup` Config Object Initialization function.
```c
void eeprom3_cfg_setup ( eeprom3_cfg_t *cfg ); 
```

- `eeprom3_init` Initialization function.
```c
err_t eeprom3_init ( eeprom3_t *ctx, eeprom3_cfg_t *cfg );
```

#### Example key functions :

- `eeprom3_write_byte` This function writes data to the desired register.
```c
void eeprom3_write_byte ( eeprom3_t *ctx, uint16_t reg_address, uint8_t data_in );
```
 
- `eeprom3_write_page` This function writes given number of data to the desired register.
```c
void eeprom3_write_page( eeprom3_t *ctx, uint16_t reg_address, uint8_t* data_in, uint8_t count );
```

- `eeprom3_read` This function reads data from the desired register.
```c
void eeprom3_read ( eeprom3_t *ctx, uint16_t reg_address, uint8_t *data_out, uint16_t count );
```

## Examples Description

> This example demonstrates the process of reading and writing to the EEPROM.

**The demo application is composed of two sections :**

### Application Init 

> Initializes EEPROM 3 driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    eeprom3_cfg_t cfg;

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
    eeprom3_cfg_setup( &cfg );
    EEPROM3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    eeprom3_init( &eeprom3, &cfg );
}
  
```

### Application Task

> Writing data to EEPROM, reading that data and displaying it via UART

```c

void application_task ( void )
{
    eeprom3_write_page( &eeprom3, 0x100, text, 6 );
    log_printf( &logger, "Writing Mikroe to EEPROM 3 Click\r\n" );
    Delay_ms ( 1000 );
    
    eeprom3_read( &eeprom3, 0x100, mem_value, 6 );
    log_printf( &logger, "Data read: %s\r\n", mem_value );
    Delay_ms ( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Eeprom3

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
