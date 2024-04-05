\mainpage Main Page
 
---
# Ambient 3 click

Ambient 3 Click is calibrated XYZ chromatic smart lighting director, providing the measurement data in digital format over the I2C interface. It utilizes the AS7225, a miniature light sensor with UART and I2C interfaces. Packed in a small casing, this sensor can provide calibrated for life nano-optic sensor providing direct CIE1931 XYZ and CIE 1976 u’v’ coordinate mapping.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ambient3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ambient-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Ambient3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Ambient3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ambient3_cfg_setup ( ambient3_cfg_t *cfg ); 
 
- Initialization function.
> AMBIENT3_RETVAL ambient3_init ( ambient3_t *ctx, ambient3_cfg_t *cfg );

- Click Default Configuration function.
> void ambient3_default_cfg ( ambient3_t *ctx );

#### Example key functions :

- This function reads device temperature.
> uint8_t ambient3_get_device_temperature( ambient3_t *ctx );

- This function reads data in LUX.
> uint16_t ambient3_get_data_in_LUX( ambient3_t *ctx );

- This function reads CCT data in K.
uint16_t ambient3_get_cct_data ( ambient3_t *ctx );

## Examples Description

> This example demonstrates the use of Ambient 3 Click board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ambient3_cfg_t cfg;

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

    ambient3_cfg_setup( &cfg );
    AMBIENT3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ambient3_init( &ambient3, &cfg );
    ambient3_default_cfg( &ambient3 );
    Delay_ms ( 100 );
}
  
```

### Application Task

> Reads the device temperature, and daylight in LUX and logs results to USB UART each second.

```c

void application_task ( )
{
    temperature = ambient3_get_device_temperature( &ambient3 );
    log_printf( &logger, " - Device temperature in Celsius : %u\r\n", ( uint16_t ) temperature );

    data_lux = ambient3_get_data_in_lux( &ambient3 );
    log_printf( &logger, " - Light in LUX : %u\r\n", data_lux );
    log_printf( &logger, " --------------------\r\n" );
    
    Delay_ms ( 1000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient3

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
