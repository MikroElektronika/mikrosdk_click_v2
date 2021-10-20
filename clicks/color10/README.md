\mainpage Main Page
 
---
# Color 10 click

Color 10 Click is carrying VEML3328 sensor for RGB and IR light sensing as well as the RGB diode incorporated on the board which makes it good color detection device when its combined with a white LED. The VEML3328 sensor senses red, green, blue, clear and IR light by incorporating photodiodes, amplifiers, and analog / digital circuits into a single CMOS chip. With this sensor, the brightness and color temperature of a display backlight can be adjusted based on the ambient light source, and it can differentiate indoor from outdoor lighting environments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/color10_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/color-10-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Color10 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https:///shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https:///shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Color10 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void color10_cfg_setup ( color10_cfg_t *cfg ); 
 
- Initialization function.
> COLOR10_RETVAL color10_init ( color10_t *ctx, color10_cfg_t *cfg );


#### Example key functions :

- This function reads data from the desired register.
> uint16_t color10_generic_read ( color10_t *ctx, uint8_t cmd_addr );

- This function calculates the color value.
> float color10_get_color_value ( color10_t *ctx );

- This function identifies the color using the color value.
> uint8_t color10_get_color ( float color_value );

## Examples Description

> Color 10 Click is carrying a sensor for RGB and IR light sensing as well as 
> the RGB diode incorporated on the board which makes it good color detection 
> device when its combined with a white LED. 

**The demo application is composed of two sections :**

### Application Init 

> Initialize I2C driver

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    color10_cfg_t cfg;
    uint8_t id_data;

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

    color10_cfg_setup( &cfg );
    COLOR10_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    color10_init( &color10, &cfg );
    Delay_ms( 500 );

    if ( color10_get_id( &color10 ) == COLOR10_DEVICE_ID )
    {
         log_printf( &logger, " -DEVICE ID OK\r\n" );
    }
    else
    {
        log_printf( &logger, " -DEVICE ID ERROR\r\n" );
        for( ; ; );
    }

    color10_config( &color10, COLOR10_CFG_HIGH_DYNAMIC_RANGE_1 |
                    COLOR10_CFG_INTEGRATION_TIME_SETT_50_MS |
                    COLOR10_CFG_AUTO_MODE |
                    COLOR10_CFG_TRIGGER_NO |
                    COLOR10_CFG_POWER_ON |
                    COLOR10_CFG_GAIN_1_X1 |
                    COLOR10_CFG_GAIN_2_X1 );
    log_printf( &logger, "-----Init done------\r\n" );
    Delay_ms( 500 );
}
  
```

### Application Task

> This example senses orange, red, pink, purple, blue, cyan, green or yellow color
> and IR light and print it via UART terminal. 

```c

void application_task ( void )
{
    uint16_t read_data;
    float color_data;

    read_data = color10_generic_read ( &color10, COLOR10_CMD_REG_IR );
    log_printf( &logger, " -IR value: %d\r\n", read_data );
    log_printf( &logger, " -Color: " );
    write_color( void );

    log_printf( &logger, " ********************** \r\n" );
    Delay_ms( 1000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Color10

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https:///shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https:///shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https:///shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https:///shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
