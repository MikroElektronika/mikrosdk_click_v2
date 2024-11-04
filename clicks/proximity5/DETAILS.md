 
---
# Proximity 5 Click

Proximity 5 Click is a very accurate and reliable proximity sensing (PS) and ambient light sensing (ALS) device, equipped with the state-of-the-art PS and ALS sensor. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/proximity5_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/proximity-5-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Proximity5 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Proximity5 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void proximity5_cfg_setup ( proximity5_cfg_t *cfg ); 
 
- Initialization function.
> PROXIMITY5_RETVAL proximity5_init ( proximity5_t *ctx, proximity5_cfg_t *cfg );

- Click Default Configuration function.
> void proximity5_default_cfg ( proximity5_t *ctx );


#### Example key functions :

- Starts the conversion and waits for the interrupt to finish. 
- After the interrupt finishes the proximity data from the proximity registers 
- is returned to a 3 member uint16_t array.
> void proximity5_get_values ( proximity5_t *ctx, uint16_t *prox_val );
 
- Read the ID from the ID register of the sensor.
> uint16_t proximity5_get_id ( proximity5_t *ctx );

- Generic function for reading both high and low register value 
- and returns those combined values to a 16bit variable.
> uint16_t proximity5_read_reg ( proximity5_t *ctx, uint8_t addr );

## Examples Description

> 
> <EXAMPLE_DESCRIPTION>
> 

**The demo application is composed of two sections :**

### Application Init 

> This application enables usage of the proximity and ablient light sensing

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    proximity5_cfg_t cfg;

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

    proximity5_cfg_setup( &cfg );
    PROXIMITY5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    proximity5_init( &proximity5, &cfg );

    proximity5_default_cfg( &proximity5 );
}
  
```

### Application Task

> The proximity data is read from the sensor and it is printed
> to the UART.

```c

void application_task ( void )
{
    //  Task implementation.

    uint16_t bff[ 4 ];

    proximity5_get_values( &proximity5, bff );
 
    log_printf( &logger, "PS1 %d  ", bff[ 0 ] );
    
    log_printf( &logger, "PS2 %d  ", bff[ 1 ] );
    
    log_printf( &logger, "PS3 %d \r\n\r\n", bff[ 2 ] );

    Delay_ms ( 500 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity5

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
