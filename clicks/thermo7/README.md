\mainpage Main Page
 
 

---
# Thermo 7 Click

Thermo 7 Click is a Click board™ equipped with the sensor IC, which can digitize temperature measurements between -55°C and +125°C so that the temperature measurement data can be processed by the host MCU.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermo7_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/thermo-7-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Thermo7 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Thermo7 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void thermo7_cfg_setup ( thermo7_cfg_t *cfg ); 
 
- Initialization function.
> THERMO7_RETVAL thermo7_init ( thermo7_t *ctx, thermo7_cfg_t *cfg );

- Click Default Configuration function.
> void thermo7_default_cfg ( thermo7_t *ctx );


#### Example key functions :

- This fuction gets Hysteresis Temperature.
> int16_t thermo7_get_hysteresis_temperature ( thermo7_t *ctx );
 
- This fuction sets limit temperature.
> void thermo7_set_limit_temperature ( thermo7_t *ctx, int16_t temperature );

- This fuction reads state of interrupt pins.
> uint8_t thermo7_get_interrupt ( thermo7_t *ctx );

## Examples Description

> This application reads ambient temperature.

**The demo application is composed of two sections :**

### Application Init 

> Initializes device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo7_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    thermo7_cfg_setup( &cfg );
    THERMO7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo7_init( &thermo7, &cfg );

    thermo7_set_configuration( &thermo7, THERMO7_CONFIG_COMPARATOR_MODE | THERMO7_CONFIG_ALERT_POLARITY_ACTIVE_HIGH );
    thermo7_set_resolution( &thermo7, THERMO7_CONFIG_ADC_RESOLUTION_12bit );
}
  
```

### Application Task

> Reads ambient temperature and logs to USBUART every 1 seconds.

```c

void application_task ( void )
{
    float ambient_temperature;

    ambient_temperature = thermo7_read_ambient_temperature( &thermo7 );
    log_printf( &logger, " Ambient temperature : %f �C\r\n", ambient_temperature );

    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo7

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
