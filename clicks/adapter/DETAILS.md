
---
# Adapter click

Adapter click™ is a breakout board which simplifies connection of add-on boards with IDC10 headers to mikroBUS™ socket. There are two ways of establishing connection: using male or female IDC10 connectors.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/adapter_click.png" height=300px>
</p>


[click Product page](<https://www.mikroe.com/adapter-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : maj 2020.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Adapter Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Adapter Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void adapter_cfg_setup ( adapter_cfg_t *cfg ); 
 
- Initialization function.
> ADAPTER_RETVAL adapter_init ( adapter_t *ctx, adapter_cfg_t *cfg );


#### Example key functions :

- This function writes data to the desired register.
> void adapter_generic_write ( adapter_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
 
- This function reads data from the desired register.
> void adapter_generic_read ( adapter_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

- Function is used to set PWM pin to 1.
> void adapter_turn_pwm_on ( adapter_t *ctx );

## Examples Description

> Adapter click is a breakout board which simplifies connection of add-on boards. 
> There are two ways of establishing connection: using male or female IDC10 connectors. 
> Male header must be soldered on the top side of Adapter Click to connect the add-on board 
> directly or via flat cable. Female header can be soldered either on the top, or the bottom 
> side, depending on which one is more convenient in given circumstances.  
> There are two jumpers for SPI/I2C selection and one for selection of power supply range.

**The demo application is composed of two sections :**

### Application Init 

> Initalizes I2C or SPI driver and makes an initial log. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    adapter_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    adapter_cfg_setup( &cfg );
    ADAPTER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adapter_init( &adapter, &cfg );
}
  
```

### Application Task

> This is an example that shows the use of the Adapter click board. 
> In I2C mode we are reading ID registrer from another device (THERMO 5 click board).
> In SPI mode example we are writing into a shift register.

```c

void application_task ( void )
{
    uint8_t wr_value;
    uint8_t rd_value;

    if ( adapter.master_sel == ADAPTER_MASTER_SPI )
    {
        adapter_turn_pwm_on( &adapter );

        wr_value = 0x79; 
        adapter_generic_write ( &adapter, 0x00, &wr_value, 1 );
    }
    else if ( adapter.master_sel == ADAPTER_MASTER_I2C )
    {
        adapter_generic_read ( &adapter, 0xFD, &rd_value, 1 );

        log_printf( &logger, " Read data :  %d\r\n", rd_value );
        log_printf( &logger, "-----------------\r\n" );
    
        Delay_ms( 2000 );
    }
} 

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Adapter

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
