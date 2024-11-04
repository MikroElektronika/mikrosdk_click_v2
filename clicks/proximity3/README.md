\mainpage Main Page
 
---
# Proximity 3 Click

> Proximity 3 Click is an intelligent proximity and light sensing device, which features the VCNL4200 sensor from Vishay - high sensitivity long distance proximity sensor (PS), ambient light sensor (ALS) and 940 nm IRED, all in one small package.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/proximity3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/proximity-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Proximity3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Proximity3 Click driver.

#### Standard key functions :

- `proximity3_cfg_setup` Config Object Initialization function.
```c
void proximity3_cfg_setup ( proximity3_cfg_t *cfg ); 
```

- `proximity3_init` Initialization function.
```c
err_t proximity3_init ( proximity3_t *ctx, proximity3_cfg_t *cfg );
```

- `proximity3_default_cfg` Click Default Configuration function.
```c
err_t proximity3_default_cfg ( proximity3_t *ctx );
```

#### Example key functions :

- `proximity3_write_16` This function writes data to the desired register.
```c
err_t proximity3_write_16 ( proximity3_t *ctx, uint8_t reg_address, uint16_t data_in );
```

- `proximity3_read_als` This function gets the data returned by the ambient light sensor.
```c
uint16_t proximity3_read_als ( proximity3_t *ctx );
```

- `proximity3_read_proximity` This function returns the proximity.
```c
uint16_t proximity3_read_proximity ( proximity3_t *ctx );
```

## Examples Description

> This application reads the raw ALS and proximity data from Proximity 3 Click board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity3_cfg_t proximity3_cfg;  /**< Click config object. */

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
    proximity3_cfg_setup( &proximity3_cfg );
    PROXIMITY3_MAP_MIKROBUS( proximity3_cfg, MIKROBUS_1 );
    if ( PROXIMITY3_ERROR == proximity3_init( &proximity3, &proximity3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXIMITY3_ERROR == proximity3_default_cfg ( &proximity3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> Reads the raw ALS and proximity data and displays the results on the USB UART every 500ms.

```c

void application_task ( void )
{
    uint16_t proximity = 0;
    uint16_t als = 0;
    
    proximity = proximity3_read_proximity( &proximity3 );
    log_printf( &logger, " Proximity: %u\r\n", proximity );

    als = proximity3_read_als( &proximity3 );
    log_printf( &logger, " ALS: %u\r\n", als );

    log_printf( &logger, "-----------------\r\n" );
    Delay_ms ( 500 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity3

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
