
---
# Proximity 6 click

Proximity 6 click is a versatile proximity detection device on a Click board™.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/proximity6_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/proximity-6-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Proximity6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Proximity6 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void proximity6_cfg_setup ( proximity6_cfg_t *cfg ); 
 
- Initialization function.
> PROXIMITY6_RETVAL proximity6_init ( proximity6_t *ctx, proximity6_cfg_t *cfg );

- Click Default Configuration function.
> void proximity6_default_cfg ( proximity6_t *ctx );


#### Example key functions :

- Function reads proximity data when one or more data register is updated.
> uint8_t proximity6_read_data ( proximity6_t *ctx, uint16_t *axis_out );
 
- Function reads proximity data and checks from which side the object affects on the sensor.
> proximity6_get_position( proximity6_t *ctx, uint8_t *position );

- Function shows proximity data values in determined resolution as graphic view.
> uint8_t proximity6_display_data( proximity6_t *ctx, uint8_t *data_value, uint8_t set_resolution );

## Examples Description
 
> This application can detect the proximity of an object via sensor and can show the results
> of proximity as a graphic view, or show the position of the object.

**The demo application is composed of two sections :**

### Application Init 

> Sets the registers in default state and configures the device to work in
> proper operating mode (Proximity Mode).  

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    proximity6_cfg_t cfg;

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
    log_info( &logger, "-|--|- Application Init -|--|-" );

    //  Click initialization.

    proximity6_cfg_setup( &cfg );
    PROXIMITY6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    proximity6_init( &proximity6, &cfg );

    Delay_ms( 300 );

    proximity6_default_cfg( &proximity6 );
    proximity6_load_settings( &proximity6 );
    proximity6_set_mode( &proximity6, PROXIMITY6_PROXIMITY_MODE );

    log_printf( &logger, "Proximity 6 is initialized\r\n\r\n");
    Delay_ms( 300 );
}
  
```

### Application Task

> Example can show the data register values as graphic view in desired resolution.
> Also can determine from which side the object (body) affects on the sensor and logs results on USB 
> UART.
> Results will be shown only when one or more data registers are updated with the new value (sensor 
> detects the change).
 

```c

void application_task ( void )
{
    //  Task implementation.
    proximity6_log_position_res( &proximity6 );
} 

```

## Note

> void proximity6_logGraphicRes() - Function loggs on USB UART results from the data proximity 
> registers as graphic view.
> void proximity6_logPositionRes() - Function loggs on USB UART the position of the object which 
> affects of the sensor.
 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity6

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
