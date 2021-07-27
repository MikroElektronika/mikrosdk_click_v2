\mainpage Main Page

 

---
# EEPROM click

EEPROM Click is an accessory board in mikroBUS form factor. It features 24C08WP - a highly reliable, high performance CMOS technology serial 8K EEPROM in DIP packaging.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/eeprom_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/eeprom-click)

---


#### Click library 

- **Author**        : Nemanja Medakovic
- **Date**          : Oct 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Eeprom Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers).
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Eeprom Click driver.

#### Standard key functions :

- Config Structure Setup function.
> void eeprom_cfg_setup( eeprom_cfg_t *cfg );
 
- Click Initialization function.
> eeprom_retval_t eeprom_init( eeprom_t *context, eeprom_cfg_t *cfg );


#### Example key functions :

- Page Write function.
> void eeprom_write_page( eeprom_t *context, uint8_t reg_addr, eeprom_i2c_data_t *data_in );
 
- Sequential Read function.
> eeprom_retval_t eeprom_read_sequential( eeprom_t *context, uint8_t reg_addr, uint16_t n_bytes, eeprom_i2c_data_t *data_out );

- Write Protect function.
> void eeprom_write_protect( eeprom_t *context );

## Examples Description

>
> This is a example which demonstrates the use of EEPROM Click board.
>

**The demo application is composed of two sections :**

### Application Init 

>
> Initializes peripherals and pins used by EEPROM Click.
> Initializes SPI serial interface and puts a device to the initial state.
>

```c

void application_init( void )
{
    eeprom_cfg_t eeprom_cfg;
    log_cfg_t log_cfg;

    //  Click initialization.
    eeprom_cfg_setup( &eeprom_cfg );
    EEPROM_MAP_MIKROBUS( eeprom_cfg, MIKROBUS_1 );
    eeprom_init( &eeprom, &eeprom_cfg );

    //  Logger initialization.
    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "----  Application Init Done  ----\r\n" );
}

```

### Application Task

>
> First page of memory block 1 will be written with data values starting from
> 1 to 16. This memory page will be read by the user, to verify successfully
> data writing. Data writing to memory will be protected upon memory writing,
> and before memory reading.
>

```c

void application_task( void )
{
    eeprom_i2c_data_t transfer_data[ EEPROM_NBYTES_PAGE ];
    uint8_t cnt;

    transfer_data[ EEPROM_BLOCK_ADDR_START ] = 1;

    for (cnt = EEPROM_BLOCK_ADDR_START + 1; cnt < EEPROM_NBYTES_PAGE; cnt++)
    {
        transfer_data[ cnt ] = transfer_data[ cnt - 1 ] + 1;
    }

    eeprom_write_enable( &eeprom );
    eeprom_write_page( &eeprom, EEPROM_BLOCK_ADDR_START, transfer_data );
    eeprom_write_protect( &eeprom );

    Delay_ms( 1000 );
    memset( transfer_data, 0, sizeof(transfer_data) );

    eeprom_read_sequential( &eeprom, EEPROM_BLOCK_ADDR_START, EEPROM_NBYTES_PAGE, transfer_data );

    for (cnt = EEPROM_BLOCK_ADDR_START; cnt < EEPROM_NBYTES_PAGE; cnt++)
    {
        log_printf( &logger, " %d", transfer_data[ cnt ] );
        Delay_ms( 300 );
    }
    log_printf( &logger, "\r\n" );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Eeprom

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
