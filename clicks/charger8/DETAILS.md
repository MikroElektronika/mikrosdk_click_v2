
---
# Angle 4 click

Angle 4 click is an angular magnetic rotary sensor, which can be used as a rotary encoder.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/charger8_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/angle-4-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Angle4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Angle4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void angle4_cfg_setup ( angle4_cfg_t *cfg ); 
 
- Initialization function.
> ANGLE4_RETVAL angle4_init ( angle4_t *ctx, angle4_cfg_t *cfg );

- Click Default Configuration function.
> void angle4_default_cfg ( angle4_t *ctx );


#### Example key functions :

- Functions for read Angle
> uint8_t angle4_get_new_angle ( angle4_t *ctx, uint16_t *data_out );
 
- Functions for chip calibration
> void angle4_calibration ( angle4_t *ctx, uint8_t dir, uint8_t data_resolution );

- Custom function for reading multiple bytes of data
> void angle4_multi_read ( angle4_t *ctx, uint8_t addr, uint8_t *read_data, uint8_t len );

## Examples Description

> This app uses angular magnetic rotary sensor and can be used for a rotary encoder.

**The demo application is composed of two sections :**

### Application Init 

> Driver intialization, standard configurations and start measurement 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    angle4_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    angle4_cfg_setup( &cfg );
    ANGLE4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    angle4_init( &angle4, &cfg );

    angle4_custom_write( &angle4, ANGLE4_REG_CUSTOMER_CFG_0, ANGLE4_CCFG0_SELECT_UVW_MODE |
                                                 ANGLE4_CCFG0_PWM_PERIOD_1025us |
                                                 ANGLE4_CCFG0_ABI_270edeg |
                                                 ANGLE4_CCFG0_UVW_POLE_PAIRS_8 );
                                                 
    angle4_custom_write( &angle4, ANGLE4_REG_CUSTOMER_CFG_1, ANGLE4_CCFG1_ABI_CPR_4096 |
                                                 ANGLE4_CCFG1_HYSTERESIS_1_4mdeg );

    angle4_custom_write( &angle4, ANGLE4_REG_OPERATING_VOLTAGE, ANGLE4_OPERATING_VOLTAGE_5000mV );
    
    angle4_calibration( &angle4, ANGLE4_CCFG2_DIR_COUNTER_CLOCKWISE_ROTATION, ANGLE4_CCFG2_ABS_RESOLUTION_14bit);
    
    log_printf( &logger, " --- Start measurement --- \r\n" );

    angle4_start_mesuremenet( &angle4 );
}
```

### Application Task

> Reads Angle in degreeses and logs data to USBUART every 200 ms.

```c
void application_task ( void )
{
    angle4_get_new_angle( &angle4, &angle );
    
    log_printf( &logger, " Angle : %d deg \r\n", angle );
    Delay_ms( 200 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Angle4

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
