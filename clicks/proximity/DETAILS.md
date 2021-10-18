

---
# Proximity click

Proximity Click features VCNL4010 proximity and ambient light sensor. It combines an infrared emitter and PIN photodiode for proximity measurement with a range of up to 20cm.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/proximity_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/proximity-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Proximity Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Proximity Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void proximity_cfg_setup ( proximity_cfg_t *cfg ); 
 
- Initialization function.
> PROXIMITY_RETVAL proximity_init ( proximity_t *ctx, proximity_cfg_t *cfg );

- Click Default Configuration function.
> void proximity_default_cfg ( proximity_t *ctx );


#### Example key functions :

- Functions for write data
> void proximity_write_data( proximity_t *ctx, uint8_t w_addr, uint8_t* wr_data, uint8_t n_len);
 
- Functions for reads Proximity data
> uint16_t proximity_read_prox_data( proximity_t *ctx );

- Functions for reads Ambient light
> uint16_t proximity_read_ambient_light( proximity_t *ctx );

## Examples Description

> Measures proximity data and ambient light.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver init and sets chip on the default mode 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    proximity_cfg_t cfg;

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

    proximity_cfg_setup( &cfg );
    PROXIMITY_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    proximity_init( &proximity, &cfg );
    proximity_set_default_mode( &proximity );
}
  
```

### Application Task

> Reads Proximity data and Ambient light data and logs data to USBUART every 500 ms.

```c

void application_task ( void )
{
    //  Task implementation.

    proximity_ambi_value = proximity_read_ambient_light( &proximity );
    proximity_proxi_value = proximity_read_prox_data( &proximity );

    log_printf( &logger, "Proximity:   %u\r\n", proximity_proxi_value);
    log_printf( &logger, " Ambient:   %u LUX\r\n ", proximity_ambi_value);

    Delay_ms( 500 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity

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
