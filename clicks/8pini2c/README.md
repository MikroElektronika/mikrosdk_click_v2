\mainpage Main Page
 
---
# 8-pin I2C Click

8-pin I2C Click is a compact add-on board that represents a breakout board that simplifies the connection of add-on boards with 8 pin Female Connector to mikroBUS™ socket.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/8pini2c_click.png" height=300px>
</p>


[Click Product page](https://www.mikroe.com/8-pin-i2c-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the 8pinI2c Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 8pinI2c Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c8pini2c_cfg_setup ( c8pini2c_cfg_t *cfg ); 
 
- Initialization function.
> C8PINI2C_RETVAL c8pini2c_init ( c8pini2c_t *ctx, c8pini2c_cfg_t *cfg );

#### Example key functions :
 
- Generic write function.
> void c8pini2c_generic_write ( c8pini2c_t *ctx, uint8_t slave_addr, uint8_t reg, uint8_t *data_buf, uint8_t len );

- Generic read function.
> void c8pini2c_generic_read ( c8pini2c_t *ctx, uint8_t slave_addr, uint8_t reg, uint8_t *data_buf, uint8_t len );

## Examples Description

> This demo example reads temperature detected by Surface temp Click board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and configures a Surface temp Click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    c8pini2c_cfg_t cfg;

    uint8_t status;

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

    c8pini2c_cfg_setup( &cfg );
    C8PINI2C_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c8pini2c_init( &c8pini2c, &cfg );

    status = surfacetemp_setup( );
    if ( status == 0 )
    {
        log_printf( &logger, "--- INIT DONE --- \r\n" );
    }
    else
    {
        log_printf( &logger, "--- INIT ERROR --- \r\n" );
        for( ; ; );
    }
}
  
```

### Application Task

> Reads the temperature detected by Surface temp Click board and logs it on the USB UART each second.

```c

void application_task ( void )
{
    float temperature;

    temperature = surfacetemp_get_temperature( );
    log_printf( &logger, "> Temperature : %.2f Celsius\r\n", temperature );
    Delay_ms ( 1000 );
} 

```

## Note

> In order to run this example successfully, a Surface temp Click board needs to be connected properly to an 8-pin I2C Click board.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.8pinI2c

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
