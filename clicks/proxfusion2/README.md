\mainpage Main Page
 
---
# ProxFusion 2 click

> ProxFusion 2 Click is an ambient lighting, capacitive, Hall-effect, and inductive sensing Click board™ which features a single multifunctional sensor IC. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/proxfusion2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/proxfusion-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the ProxFusion2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for ProxFusion2 Click driver.

#### Standard key functions :

- `proxfusion2_cfg_setup` Config Object Initialization function.
```c
void proxfusion2_cfg_setup ( proxfusion2_cfg_t *cfg ); 
```

- `proxfusion2_init` Initialization function.
```c
err_t proxfusion2_init ( proxfusion2_t *ctx, proxfusion2_cfg_t *cfg );
```

- `proxfusion2_default_cfg` Click Default Configuration function.
```c
err_t proxfusion2_default_cfg ( proxfusion2_t *ctx );
```

#### Example key functions :

- `proxfusion2_detect_touch` Function for detect Touch
```c
uint8_t proxfusion2_detect_touch ( proxfusion2_t *ctx );
```

- `proxfusion2_detect_dark_light` Function for read ambient light
```c
uint8_t proxfusion2_detect_dark_light ( proxfusion2_t *ctx, uint8_t *als_range );
```

- `proxfusion2_detect_hall` Function for read Hall-effect 
```c
uint8_t proxfusion2_detect_hall ( proxfusion2_t *ctx );
```

## Examples Description

> This example demontrates the use of ProxFusion 2 Click board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proxfusion2_cfg_t proxfusion2_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    proxfusion2_cfg_setup( &proxfusion2_cfg );
    PROXFUSION2_MAP_MIKROBUS( proxfusion2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == proxfusion2_init( &proxfusion2, &proxfusion2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXFUSION2_ERROR == proxfusion2_default_cfg ( &proxfusion2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> - Checks whether Touch is detected and measures the output detection.
> - Measures Ambient lighting - whether it's Light or Dark, ALS range and ALS output.
> - Checks the orientation of the magnet and measures the HALL output.

```c

void application_task ( void )
{
    uint8_t als_range = 0;
    uint8_t hall_detect = 0;
    uint16_t read_data = 0;
    if ( PROXFUSION2_TOUCH_DETECTED == proxfusion2_detect_touch( &proxfusion2 ) )
    {
        log_printf( &logger, " TOUCH: YES\r\n" );
    }
    else
    {
        log_printf( &logger, " TOUCH: NO\r\n" );
    }
    read_data = proxfusion2_read_data( &proxfusion2 , PROXFUSION2_HYSTERESIS_UI_OUTPUT );
    log_printf( &logger, " LEVEL: %u\r\n\n", read_data );
 
    if ( PROXFUSION2_AMBIENT_DARK == proxfusion2_detect_dark_light( &proxfusion2, &als_range ) )
    {
        log_printf( &logger, " AMBIENT: DARK\r\n" );
    }
    else
    {
        log_printf( &logger, " AMBIENT: LIGHT\r\n" );
    }
    log_printf( &logger, " RANGE: %u\r\n", ( uint16_t ) als_range );
 
    read_data = proxfusion2_read_data( &proxfusion2, PROXFUSION2_ALS_UI_OUTPUT );

    log_printf( &logger, " LEVEL: %u\r\n\n", read_data );
 
    hall_detect = proxfusion2_detect_hall( &proxfusion2 );
    if ( PROXFUSION2_HALL_NORTH == hall_detect )
    {
        log_printf( &logger, " HALL: NORTH\r\n" );
    }
    else if ( PROXFUSION2_HALL_SOUTH == hall_detect )
    {
        log_printf( &logger, " HALL: SOUTH\r\n" );
    }
    else
    {
        log_printf( &logger, " HALL: UNKNOWN\r\n" );
    }
    read_data = proxfusion2_read_data( &proxfusion2, PROXFUSION2_HALL_EFFECT_UI_OUTPUT );
    log_printf( &logger, " LEVEL: %u\r\n", read_data );
    
    log_printf( &logger, " --------------\r\n" );
    Delay_ms ( 1000 );
}

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.ProxFusion2

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
