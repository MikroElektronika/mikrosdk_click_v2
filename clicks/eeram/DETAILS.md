 
---
# EERAM click

EERAM click is a static RAM (SRAM) memory click board™ with the unique feature - it has a backup non-volatile memory array, used to store the data from the SRAM array. Since the SRAM is not able to maintain its content after the power loss, the non-volatile EEPROM backup can be a very handy addition that can be used to preserve the data, even after the power loss event. This is a very useful feature when working with critical or sensitive applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/grupe/eeram-click-group.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/eeram-33v-click>)

[click Product page](<https://www.mikroe.com/eeram-5v-click>)
---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : maj 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Eeram Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Eeram Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void eeram_cfg_setup ( eeram_cfg_t *cfg ); 
 
- Initialization function.
> EERAM_RETVAL eeram_init ( eeram_t *ctx, eeram_cfg_t *cfg );


#### Example key functions :

- Reads the data from the selected SRAM address onwards.
> void eeram_read ( eeram_t *ctx, uint16_t address, uint8_t *data_out, uint8_t count_out );
 
- Writes the data to SRAM memory array.
> void eeram_write ( eeram_t *ctx, uint16_t address, uint8_t * data_in, uint8_t count_in );

- Returns the state of the status register.
> uint8_t eeram_status_read ( eeram_t *ctx );

## Examples Description

> This example show using EERAM click to store the data to the SRAM ( static RAM ) memory.
> The data is read and written by the I2C serial communication bus, and the memory cells 
> are organized into 2048 bytes, each 8bit wide.

**The demo application is composed of two sections :**

### Application Init 

> EERAM driver nitialization

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    eeram_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    eeram_cfg_setup( &cfg );
    EERAM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    eeram_init( &eeram, &cfg );
}
  
```

### Application Task

> Writing data to click memory and displaying the read data via UART. 

```c

void application_task ( void )
{
    log_info( &logger, "Writing MikroE to  SRAM memory, from address 0x0150:" );
    eeram_write( &eeram, 0x0150, &wr_data, 9 );
    log_info( &logger, "Reading 9 bytes of SRAM memory, from address 0x0150:" );
    eeram_read( &eeram, 0x0150, &rd_data, 9 );
    log_info( &logger, "Data read: %s", rd_data );
    Delay_ms( 1000 );
} 

```

## Note

> <pre>
> Input Voltage:	
>       5V ( on EERAM 5V Click)
>       3.3V ( on EERAM 3.3V Click)
> </pre>

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Eeram

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
