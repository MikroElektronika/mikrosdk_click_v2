
---
# Thermo 13 click

Thermo 13 Click is a Click board™ equipped with the sensor IC, which can digitize temperature measurements between -30°C and +95°C so that the temperature measurement data can be processed by the host MCU.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermo13_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/thermo-13-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Thermo13 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Thermo13 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void thermo13_cfg_setup ( thermo13_cfg_t *cfg ); 
 
- Initialization function.
> THERMO13_RETVAL thermo13_init ( thermo13_t *ctx, thermo13_cfg_t *cfg );

- Click Default Configuration function.
> void thermo13_default_cfg ( thermo13_t *ctx );


#### Example key functions :

- Set temperature limit register
> void thermo13_set_temp_limit ( thermo13_t *ctx, uint8_t temp_reg, float temp );
 
- Get temperature register
> float thermo13_get_temp_limit ( thermo13_t *ctx, uint8_t temp_reg );

- Ambient temperature data
> float thermo13_get_ambient_temperature_data ( thermo13_t *ctx, uint8_t temp_in );

## Examples Description

> The application measures temperature 

**The demo application is composed of two sections :**

### Application Init 

>Initializes the driver init, configures the module and reads the temperature Limit LOW/HIGH values that are set.


```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo13_cfg_t cfg;
    
    float temp_limit_low;
    float temp_limit_high;

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

    //  Click initialization

    thermo13_cfg_setup( &cfg );
    THERMO13_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo13_init( &thermo13, &cfg );

    // Configuration 
   
    thermo13_configuration( &thermo13, THERMO13_CFG_CONTINUOUS_MEASUREMENT |
                            THERMO13_CFG_FAULT_QUEUE_1 |
                            THERMO13_CFG_ALERT_ACTIVE_HIGH |
                            THERMO13_CFG_INTERRUPT_IS_ACTIVE |
                            THERMO13_CFG_WAIT_TIME_X16 );

        
    // Temperature Register
    log_printf( &logger, " --- Temperature register data --- \r\n \r\n" );

    temp_limit_low = thermo13_get_temp_limit ( &thermo13, THERMO13_REG_TEMPERATURE_LIMIT_LOW );
    log_printf( &logger, " --- Temp - Limit LOW : %.2f C \r\n ", temp_limit_low );

    temp_limit_high = thermo13_get_temp_limit ( &thermo13, THERMO13_REG_TEMPERATURE_LIMIT_HIGH );
    log_printf( &logger, " --- Temp - Limit HIGH :  %.2f C \r\n \r\n  ", temp_limit_high );
    
    log_printf( &logger, " --- Ambient temperature measurement --- \r\n " );

}
}
  
```

### Application Task

>Reads ambient temperature data and this data logs to USBUART every 1500ms.

```c

void application_task ( void )
{
    float temperature;

    temperature = thermo13_get_ambient_temperature_data ( &thermo13,  THERMO13_TEMP_IN_CELSIUS );

    log_printf( &logger, "** temperature %.2f ** \r\n" );

    log_printf( &logger, " ----------------------------\r\n" );

    Delay_ms ( 1000 );
    Delay_ms ( 500 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo13

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