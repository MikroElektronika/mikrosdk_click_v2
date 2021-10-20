
 

---
# Thermo K click

THERMO K click carries the MCP9600 IC from Microchip. Depending on the type of probe it uses the click can measure temperatures from −200 °C to +1372 °C.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermok_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/thermo-k-click)

---


#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : nov 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the ThermoK Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for ThermoK Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void thermok_cfg_setup ( thermok_cfg_t *cfg ); 
 
- Initialization function.
> THERMOK_RETVAL thermok_init ( thermok_t *ctx, thermok_cfg_t *cfg );


#### Example key functions :

- Temperature data
> float thermok_get_temperature ( thermok_t *ctx, uint8_t reg, uint8_t temp_format );
 
- Get status
> void thermok_get_status ( thermok_t *ctx, thermok_alert_t *status );

- Functions for read device info
> uint16_t thermok_get_device_info ( thermok_t *ctx );

## Examples Description

> Demo application shows basic temperature reading using Thermo K click.

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects.
> Reads the device ID and also checks the click and MCU communication.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    thermok_cfg_t cfg;

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

    thermok_cfg_setup( &cfg );
    THERMOK_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermok_init( &thermok, &cfg );

    // Check communication and reads device ID

    device_info = thermok_get_device_info( &thermok );

    if ( ( device_info >> 8 ) == THERMOK_DEVICE_ID )
    {
        log_info(&logger, "---- Communication OK!!! ----" );
    }
    else
    {
        log_info(&logger, "---- Communication ERROR!!! ----" );
        for ( ; ; );
    }
    Delay_1sec( );
}
```

### Application Task

> Reads Temperature data(Type K probe) and this data logs to USBUART every 500ms.

```c
void application_task ( void )
{
    float temperature;

    //  Task implementation.

    temperature = thermok_get_temperature( &thermok, 
                                           THERMOK_REG_HOT_JUNCTION_TEMP_THR, 
                                           THERMOK_TEMP_IN_CELSIUS );
    log_printf( &logger, ">> Temperature is %.2f C\r\n", temperature );

    Delay_ms( 1500 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.ThermoK

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
