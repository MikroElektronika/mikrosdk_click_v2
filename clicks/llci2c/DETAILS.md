
---
# LLC I2C click

LLC I2C click can be utilized as the level converter for logic signals, which makes it a very useful Click board™. The topology of this logic level conversion (LLC) circuit is perfectly suited for the bi-directional I2C communication. Although there are some specialized integrated circuits on the market, sometimes it is more convenient to have a simple solution made of just a few passive elements and four MOSFETs.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/llci2c_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/llc-i2c-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : maj 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the LlcI2c Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LlcI2c Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void llci2c_cfg_setup ( llci2c_cfg_t *cfg ); 
 
- Initialization function.
> LLCI2C_RETVAL llci2c_init ( llci2c_t *ctx, llci2c_cfg_t *cfg );


#### Example key functions :

- This function writes data to the desired register.
> void llci2c_generic_write ( llci2c_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
 
- This function reads data from the desired register.
> void llci2c_generic_read ( llci2c_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );


## Examples Description

> This click can be utilized as the level converter for logic signals. The topology of this 
> logic level conversion (LLC) circuit is perfectly suited for the bi-directional I2C communication.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver init

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    llci2c_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    llci2c_cfg_setup( &cfg );
    LLCI2C_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    llci2c_init( &llci2c, &cfg );
}
  
```

### Application Task

> Reads the temperature from the Thermo 7 click board and logs data to UART.

```c

void application_task ( void )
{
    // Thermo 7 measurement Temperature
    uint8_t write_reg = 0x00;
    uint8_t read_reg[ 2 ] = { 0 };
    
    float temp_msb;
    uint8_t temp_lsb;

    llci2c_generic_read ( &llci2c, write_reg, read_reg, 2 );
    
    temp_msb = read_reg[ 0 ];
    temp_lsb = read_reg[ 1 ] & 0xF0;

    if ( temp_lsb & 0x80 ) temp_msb += 0.50;
    if ( temp_lsb & 0x40 ) temp_msb += 0.25;
    if ( temp_lsb & 0x20 ) temp_msb += 0.125;
    if ( temp_lsb & 0x10 ) temp_msb += 0.0625;

    log_info( &logger, " Ambient temperature : %2.f C", temp_msb );
    Delay_ms( 1000 );
}

```

## Note

> <pre>
> Connection between Thermo 7 and I2C-LLC is made through I2C interface.
> You can connect a Thermo 7 click and I2C-LLC click with the wires to make connection between click boards.
> We use the Thermo 7 click to demonstrate the functions of the I2C-LLC click.
> </pre> 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LlcI2c

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
