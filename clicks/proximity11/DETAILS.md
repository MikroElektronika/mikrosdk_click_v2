 
---
# Proximity 11 click

Proximity 11 Click is a close-range proximity sensing Click board™, equipped with the RPR-0521RS, a very accurate and power-efficient proximity and ambient Light Sensor with IrLED.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/proximity11_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/proximity-11-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Proximity11 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Proximity11 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void proximity11_cfg_setup ( proximity11_cfg_t *cfg ); 
 
- Initialization function.
> PROXIMITY11_RETVAL proximity11_init ( proximity11_t *ctx, proximity11_cfg_t *cfg );

- Click Default Configuration function.
> void proximity11_default_cfg ( proximity11_t *ctx );


#### Example key functions :

- This function reads proximity values from the desired registers.
> uint8_t proximity11_get ( proximity11_t *ctx, uint8_t register_address, uint8_t *output_buffer, uint8_t n_bytes );
 
- This function updates data used to calculate Lux. This function should be called if changing als measurement time and als gain.
> void proximity11_update ( proximity11_t *ctx );

- This function sets High ALS threshold value
> void proximity11_set_als_threshold_high ( proximity11_t *ctx, uint16_t threshold_value );

## Examples Description

> This appication enables usage of the proximity and ambient light sensors

**The demo application is composed of two sections :**

### Application Init 

> Initializes I2C driver and performs device initialization

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    proximity11_cfg_t cfg;
    uint8_t init_status;

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

    proximity11_cfg_setup( &cfg );
    PROXIMITY11_MAP_MIKROBUS( cfg, MIKROBUS_4 );
    proximity11_init( &proximity11, &cfg );

    Delay_ms ( 500 );

    init_status = proximity11_default_cfg( &proximity11 );

    if ( init_status == 1 )
    {
        log_printf( &logger, "> app init fail\r\n" );
		while( 1 );
    }
    else if ( init_status == 0 )
    {
        log_printf( &logger, "> app init done\r\n" );
    }
}
  
```

### Application Task

> Gets ALS and PS values and logs those values

```c

void application_task ( void )
{
    //  Task implementation

    uint16_t ps_value;
    float als_value;

    proximity11_get_ps_als_values( &proximity11, &ps_value, &als_value );

    log_printf( &logger, "PS  : %ld [count]\r\n", ps_value );
    log_printf( &logger, "ALS : %.2f [Lx]\r\n\r\n", als_value );

    Delay_ms ( 500 );

}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity11

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
