
---
# THERMO 5 click

THERMO 5 click measures temperature in default range of 0°C to 127°C and extended range of -64°C to 191°C with ±1°C accuracy.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermo5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/thermo-5-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the THERMO5 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for THERMO5 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void thermo5_cfg_setup ( thermo5_cfg_t *cfg ); 
 
- Initialization function.
> THERMO5_RETVAL thermo5_init ( thermo5_t *ctx, thermo5_cfg_t *cfg );

- Click Default Configuration function.
> void thermo5_default_cfg ( thermo5_t *ctx );


#### Example key functions :
 
- This function reads measurements made by internal diode.
> float thermo5_read_inter_temp ( thermo5_t *ctx );

- This function reads measurements made by external 1 diode.
> float thermo5_read_extern_1_temp ( thermo5_t *ctx );

- This function reads the High Limit Status register which utilises its lower nibble to represents which diodes have exceed their programmed high limit.
> uint8_t thermo5_read_high_limit_stat ( thermo5_t *ctx );

## Examples Description

> This app measures internal and external temperature.

**The demo application is composed of two sections :**

### Application Init 

> Initalizes device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo5_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    thermo5_cfg_setup( &cfg );
    THERMO5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo5_init( &thermo5, &cfg );
    Delay_ms( 500 );
    log_printf( &logger, " Thermo 5 click ready! \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms( 100 );
}
  
```

### Application Task

> This is an example that shows the most important functions that Thermo 5 click has.

```c

void application_task ( void )
{
    float inter_temp;
    float exter_temp_1;
    float exter_temp_2;
    float exter_temp_3;

    inter_temp = thermo5_read_inter_temp( &thermo5 );
    log_printf( &logger, " Internal temperature :   %.2f \r\n", inter_temp );
    exter_temp_1 = thermo5_read_extern_1_temp( &thermo5 );
    log_printf( &logger, " External temperature 1 : %.2f \r\n", exter_temp_1 );
    exter_temp_2 = thermo5_read_extern_2_temp( &thermo5 );
    log_printf( &logger, " External temperature 2 : %.2f \r\n", exter_temp_2 );
    exter_temp_3 = thermo5_read_extern_3_temp( &thermo5 );
    log_printf( &logger, " External temperature 3 : %.2f \r\n", exter_temp_2 );
    log_printf( &logger, "---------------------------------\r\n" );
    Delay_ms( 5000 );
}


```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.THERMO5

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
