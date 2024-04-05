
---
# Presence click

> Presence click is an infrared sensing Click board™ which can be used for presence sensing, motion detection, and a remote overtemperature protection. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/presence_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/presence-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Presence Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Presence Click driver.

#### Standard key functions :

- `presence_cfg_setup` Config Object Initialization function.
```c
void presence_cfg_setup ( presence_cfg_t *cfg ); 
```

- `presence_init` Initialization function.
```c
err_t presence_init ( presence_t *ctx, presence_cfg_t *cfg );
```

- `presence_default_cfg` Click Default Configuration function.
```c
err_t presence_default_cfg ( presence_t *ctx );
```

#### Example key functions :

- `presence_ambient_temperature` This function returns ambient temperature in degrees Celsius.
```c
err_t presence_ambient_temperature( presence_t *ctx, float *temperature )
```

- `presence_object_temperature` This function returns object temperature.
```c
err_t presence_object_temperature( presence_t *ctx, float *temperature );
```

## Examples Description

> This application enables usage of sensor for motion and presence sensing and measuring of object's and ambient temperature.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    presence_cfg_t cfg;

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
    presence_cfg_setup( &cfg );
    PRESENCE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    presence_init( &presence, &cfg );

    if ( PRESENCE_ERROR == presence_default_cfg ( &presence ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> Checks whether a new event (motion, presence or over-temperature) is detected. 
If there's no event detected it reads the ambient and object temperature and displays the results on the USB UART.

```c

void application_task ( void )
{
    uint8_t int_status = 0;
    uint8_t tp_presence = 0;
    uint8_t tp_motion = 0;
    float t_amb = 0;
    float t_obj = 0;
    
    if ( PRESENCE_OK == presence_generic_read( &presence, PRESENCE_REG_INTERRUPT_STATUS, &int_status, 1 ) )
    {
        if ( int_status & PRESENCE_INT_MASK1_PRESENCE )
        {
            if ( PRESENCE_OK == presence_generic_read( &presence, PRESENCE_REG_TP_PRESENCE, &tp_presence, 1 ) )
            {
                log_info( &logger, "Presence detected! Level: %u", ( uint16_t ) tp_presence );
            }
        }
        else if ( int_status & PRESENCE_INT_MASK1_MOTION )
        {
            if ( PRESENCE_OK == presence_generic_read( &presence, PRESENCE_REG_TP_MOTION, &tp_motion, 1 ) )
            {
                log_info( &logger, "Motion detected! Level: %u", ( uint16_t ) tp_motion );
            }
        }
        else if ( int_status & PRESENCE_INT_MASK1_TP_OT )
        {
            log_info( &logger, "Temp threshold exceeded!" );
        }
        else
        {
            if ( PRESENCE_OK == presence_ambient_temperature( &presence, &t_amb ) )
            {
                log_printf( &logger, "Ambient temperature: %.2f degC\r\n", t_amb );
            }
            if ( PRESENCE_OK == presence_object_temperature( &presence, &t_obj ) )
            {
                log_printf( &logger, "Object temperature: %.2f degC\r\n\n", t_obj );
            }
        }
    }
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Presence

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