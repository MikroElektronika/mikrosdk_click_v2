\mainpage Main Page
 
 

---
# Thermo 11 click

Thermo 11 Click is a Click board™ equipped with the sensor IC, which can digitize temperature measurements between -55°C and +150°C so that the temperature measurement data can be processed by the host MCU.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermo11_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/thermo-11-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Thermo11 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Thermo11 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void thermo11_cfg_setup ( thermo11_cfg_t *cfg ); 
 
- Initialization function.
> THERMO11_RETVAL thermo11_init ( thermo11_t *ctx, thermo11_cfg_t *cfg );

- Click Default Configuration function.
> void thermo11_default_cfg ( thermo11_t *ctx );

#### Example key functions :

- Temperature Get function
> float thermo11_get_temp ( thermo11_t *ctx, uint8_t temp_addr );
 
- Software Reset Command
> void thermo11_sw_reset ( thermo11_t *ctx );

- Temperature Set function
> THERMO11_RETVAL thermo11_set_temp ( thermo11_t *ctx, uint8_t temp_addr, float temp_value );

## Examples Description

> The application measures temperature 

**The demo application is composed of two sections :**

### Application Init 

> Initializes I2C serial interface and performs a software reset command

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo11_cfg_t cfg;

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

    thermo11_cfg_setup( &cfg );
    THERMO11_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo11_init( &thermo11, &cfg );

    thermo11_sw_reset( &thermo11 );

    thermo11_default_cfg( &thermo11 );
    
    log_printf( &logger, "** Thermo 11 is initialized ** \r\n" );
    log_printf( &logger, "************************************************ \r\n \r\n" );
    
    Delay_ms( 500 );
}
  
```

### Application Task

> Waits until data was ready and conversion cycle was done, and then reads 

```c

void application_task ( void )
{
    uint8_t response_check;
    float temperature;
    
    response_check = thermo11_get_int(  &thermo11 );
    while ( response_check == THERMO11_FLAG_IS_CLEARED )
    {
        response_check = thermo11_get_int( &thermo11 );
    }

    temperature = thermo11_get_temp(  &thermo11, THERMO11_TEMPERATURE_REG );
    response_check = thermo11_check_status( &thermo11 );
    
    log_printf( &logger, "*Temperature is: %.2f \r\n", temperature );

    
    if ( ( response_check & THERMO11_HIGH_ALERT_FLAG ) != THERMO11_FLAG_IS_CLEARED )
    {
        log_printf( &logger, "*HIGH limit detection! \r\n" );
    }
    if ( ( response_check & THERMO11_LOW_ALERT_FLAG ) != THERMO11_FLAG_IS_CLEARED )
    {
         log_printf( &logger, "*LOW limit detection! \r\n" );
    }
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo11

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
