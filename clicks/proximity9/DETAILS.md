
---
# Proximity 9 click

Proximity 9 click is a very accurate and reliable proximity sensing (PS) and ambient light sensing (ALS) device, equipped with the VCNL4040, an integrated PS and ALS sensor which features the Filtron™ technology.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/proximity9_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/proximity-9-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Proximity9 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Proximity9 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void proximity9_cfg_setup ( proximity9_cfg_t *cfg ); 
 
- Initialization function.
> PROXIMITY9_RETVAL proximity9_init ( proximity9_t *ctx, proximity9_cfg_t *cfg );

- Click Default Configuration function.
> void proximity9_default_cfg ( proximity9_t *ctx );


#### Example key functions :

- INT Pin Check function
> uint8_t proximity9_check_int_pin ( proximity9_t *ctx );
 
- INT Flag Check function
> uint8_t proximity9_check_int_flag ( proximity9_t *ctx, uint8_t bit_mask );

- ALS Get function
> float proximity9_get_als_lux ( proximity9_t *ctx );

## Examples Description
 
> This application is proximity sensing (PS) and ambient light sensing (ALS) device.

**The demo application is composed of two sections :**

### Application Init 

> Initializes I2C interface and performs a device configurations.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    proximity9_cfg_t cfg;

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

    proximity9_cfg_setup( &cfg );
    PROXIMITY9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    proximity9_init( &proximity9, &cfg );

    proximity9_default_cfg( &proximity9 );

    log_printf( &logger, "** Proximity 9 is initialized ** \r\n" );
    log_printf( &logger, "************************************ \r\n" );
    Delay_ms ( 300 );
}
  
```

### Application Task

> Performs a data reading and interrupt flag checking.
> Allows data and interrupt flags messages to be showed on the uart terminal.

```c

void application_task ( )
{
    uint8_t int_check;
    uint16_t prox_data;
    float als_data;
    uint8_t temp;

    als_data = proximity9_get_als_lux( &proximity9 );
    proximity9_read_register( &proximity9, PROXIMITY9_PS_DATA_REG, &prox_data );
    temp = PROXIMITY9_PS_IF_CLOSE_FLAG | PROXIMITY9_PS_IF_AWAY_FLAG;
    int_check = proximity9_check_int_flag( &proximity9, temp );
    
    log_printf( &logger, "** ALS: %.2f lux \r\n", als_data );
    log_printf( &logger, "** PROXIMITY: %d \r\n", prox_data );
    
    if ( int_check == PROXIMITY9_PS_IF_CLOSE_FLAG )
    {
        log_printf( &logger, "** Object is close! \r\n" );
        log_printf( &logger, "************************************ \r\n" );
        Delay_ms ( 200 );
    }
    if ( int_check == PROXIMITY9_PS_IF_AWAY_FLAG )
    {
        log_printf( &logger, "** Object is away!\r\n" );
        log_printf( &logger, "************************************ \r\n" );
        Delay_ms ( 200 );
    }
    if ( int_check == PROXIMITY9_INT_CLEARED )
    {
        log_printf( &logger, "************************************ \r\n" );
        Delay_ms ( 200 );
    }
}  

```

## Note

> The ALS sensitivity depends on the ALS integration time setting.
> The longer integration time has higher sensitivity.
> The Proximity (PS) output data can be set to 12-bit or 16-bit resolution.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity9

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
