
---
# Force 3 click

Force 3 Click is a compact add-on board with circuitry for implementing Force Sensing Resistor into your projects whose resistance changes when a force, pressure, or mechanical stress is applied.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/force3_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/force-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jul 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Force3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Force3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void force3_cfg_setup ( force3_cfg_t *cfg ); 
 
- Initialization function.
> FORCE3_RETVAL force3_init ( force3_t *ctx, force3_cfg_t *cfg );

#### Example key functions :

- Read 12bit raw data.
> uint16_t force3_read_raw_data ( force3_t *ctx );

## Examples Description

> This application demonstrates the use of Force 3 click board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    force3_cfg_t cfg;

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

    force3_cfg_setup( &cfg );
    FORCE3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    force3_init( &force3, &cfg );
}
  
```

### Application Task

> Reads the sensor raw data and displays it on the USB UART.

```c

void application_task ( void )
{
    uint16_t raw_data;

    raw_data = force3_read_raw_data( &force3 );
    log_printf( &logger, "Raw data: %d \r\n", raw_data );

    if ( ( raw_data > 5 ) && ( raw_data <= 200 ) )
    {
       log_printf( &logger, ">> Light touch \r\n" );
    }
    else if ( ( raw_data > 200 ) && ( raw_data <= 500 ) )
    {
       log_printf( &logger, ">> Light squeeze \r\n" );
    }
    else if ( ( raw_data > 500 ) && ( raw_data <= 800 ) )
    {
       log_printf( &logger, ">> Medium squeeze \r\n" );
    }
    else if ( raw_data > 800 )
    {
       log_printf( &logger, ">> Big squeeze \r\n" );
    }
    
    log_printf( &logger, "----------------------\r\n" );
    Delay_ms( 1000 );
}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Force3

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
