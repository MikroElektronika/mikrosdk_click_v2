

---
# Magnetic linear click

Magnetic linear click is a very accurate position sensing Click board™ which utilizes the HMC1501, a magnetic field displacement sensor IC.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/magneticlinear_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/magnetic-linear-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Magneticlinear Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Magneticlinear Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void magneticlinear_cfg_setup ( magneticlinear_cfg_t *cfg ); 
 
- Initialization function.
> MAGNETICLINEAR_RETVAL magneticlinear_init ( magneticlinear_t *ctx, magneticlinear_cfg_t *cfg );

- Click Default Configuration function.
> void magneticlinear_default_cfg ( magneticlinear_t *ctx );


#### Example key functions :

- This function reads Magnetics Linear data.
> uint16_t magneticlinear_read_data ( magneticlinear_t *ctx );

## Examples Description

> This application reads magnetics linear data.

**The demo application is composed of two sections :**

### Application Init 

> Device initialization.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    magneticlinear_cfg_t cfg;

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

    magneticlinear_cfg_setup( &cfg );
    MAGNETICLINEAR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    magneticlinear_init( &magneticlinear, &cfg );
}
  
```

### Application Task

> Reads magnetic linear data and logs it to USB UART every 500ms.

```c

void application_task ( void )
{
    uint16_t magnetic_data;
    
    magnetic_data = magneticlinear_read_data( &magneticlinear );

    log_printf( &logger, " Magnetic Linear data : %u\r\n", magnetic_data );
    Delay_ms ( 500 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Magneticlinear

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
