
 

---
# Thermo 15 Click

Thermo 15 Click is a Click board™ equipped with the sensor IC, which can digitize temperature measurements between -55°C and +125°C so that the temperature measurement data can be processed by the host MCU.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermo15_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/thermo-15-click)

---


#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : nov 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Thermo15 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Thermo15 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void thermo15_cfg_setup ( thermo15_cfg_t *cfg ); 
 
- Initialization function.
> THERMO15_RETVAL thermo15_init ( thermo15_t *ctx, thermo15_cfg_t *cfg );

- Click Default Configuration function.
> void thermo15_default_cfg ( thermo15_t *ctx );


#### Example key functions :

- Ambient temperature data
> float thermo15_get_temperature_data ( thermo15_t *ctx,  uint8_t temp_format );
 
- Set temperature register
> void thermo15_set_temp_register ( thermo15_t *ctx, uint8_t temp_reg, float temp_data );

- Interrupt state
> uint8_t thermo15_get_interrupt_state ( thermo15_t *ctx );

## Examples Description

> This demo-app shows the temperature measurement procedure using Thermo 15 Click.

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects. 
> Setting the Click in the default configuration to start the measurement.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo15_cfg_t cfg;

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

    thermo15_cfg_setup( &cfg );
    THERMO15_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo15_init( &thermo15, &cfg );

    thermo15_default_cfg ( &thermo15 );
    log_info( &logger, "---- Start measurement ----" );
}
```

### Application Task

> Reads ambient temperature data and this data logs to USBUART every 1500ms.

```c
void application_task ( void )
{
    float temperature;

    temperature = thermo15_get_temperature_data( &thermo15, THERMO15_TEMP_IN_CELSIUS );
    log_printf( &logger, "** Temperature: %.2f C \r\n", temperature );

    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo15

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
