\mainpage Main Page
 
---
# I2C 1 Wire click

I2C 1-Wire click carries DS2482-800, a “bridge device” that performs bidirectional conversions between I2C masters and 1-Wire slave devices. These can be EEPROM chips, temperature sensors and similar devices that have momentary high source current modes.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/i2c1wire_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/i2c-1-wire-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the I2C1Wire Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for I2C1Wire Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void i2c1wire_cfg_setup ( i2c1wire_cfg_t *cfg ); 
 
- Initialization function.
> I2C1WIRE_RETVAL i2c1wire_init ( i2c1wire_t *ctx, i2c1wire_cfg_t *cfg );

- Click Default Configuration function.
> void i2c1wire_default_cfg ( i2c1wire_t *ctx );


#### Example key functions :

- This function writes one byte to the click module.
> void i2c1wire_write_byte_one_wire ( i2c1wire_t *ctx, uint8_t input );
 
- This function reads one byte from the click module.
> i2c1wire_read_byte_one_wire ( i2c1wire_t *ctx );

- This function does a hardware reset of the click module.
> void i2c1wire_one_wire_reset ( i2c1wire_t *ctx );

## Examples Description

> This example showcases how to initialize, confiure and use the I2C 1-Wire click. The click
  is a I2C (host) to 1-Wire interface (slave). In order for the example to work one or more 
  1-Wire (GPIO) click modules are required. Gnd goes to gnd, power goes to power and the cha-
  nnels are there to read data from connected modules.

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the logger and click modules.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    i2c1wire_cfg_t cfg;

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

    i2c1wire_cfg_setup( &cfg );
    I2C1WIRE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    i2c1wire_init( &i2c1wire, &cfg );
    Delay_1sec( );
}
  
```

### Application Task

> This function reads all of the channels on the click module and displays any data it acqu-
  ires from them with a 100 millisecond delay. 

```c

void application_task ( void )
{
    uint8_t chan_state;
    uint8_t cnt_chan;
    uint8_t cnt_val;
    uint8_t id_code[ 9 ];

    chan_state = 1;

    i2c1wire_soft_reset( &i2c1wire );
    Delay_10ms( );
    i2c1wire_set_config( &i2c1wire, I2CONEWIRE_CONFIG_1WS_HIGH |
                                    I2CONEWIRE_CONFIG_SPU_HIGH |
                                    I2CONEWIRE_CONFIG_APU_LOW );
    Delay_10ms( );

    for( cnt_chan = 0; cnt_chan < 8; cnt_chan++ )
    {
        i2c1wire_set_channel( &i2c1wire, cnt_chan );
        i2c1wire_one_wire_reset( &i2c1wire );
        Delay_10ms( );

        i2c1wire_write_byte_one_wire( &i2c1wire, I2CONEWIRE_WIRE_COMMAND_READ_ROM );
        Delay_10ms();

        for( cnt_val = 8; cnt_val > 0; cnt_val-- )
        {
            id_code[ cnt_val ] = i2c1wire_read_byte_one_wire( &i2c1wire );

            if ( id_code[ cnt_val ] == I2CONEWIRE_WIRE_RESULT_OK )
            {
                log_printf( &logger, "\r\n Channel %d : No device on the channel\r\n", cnt_chan );
                Delay_100ms( );
                break;
            }
            else if ( chan_state )
            {
                log_printf( &logger, " Channel %d : ID = 0x", cnt_chan );
                chan_state = 0;
            }

            log_printf( &logger, "%d", id_code[ cnt_val ] );
            Delay_100ms( );
        }

        log_printf( &logger, "\r\n---------------------------------------\r\n" );
    }

    log_printf( &logger, "***\r\n" );
} 

```

## Note

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.I2C1Wire

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
