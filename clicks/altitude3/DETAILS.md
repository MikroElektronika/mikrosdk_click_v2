

---
# Altitude 3 Click

Altitude 3 Click allows high-resolution barometric pressure measurement, by utilizing the ICP-10100, an integrated barometric pressure and temperature sensor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/altitude3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/altitude-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Altitude3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Altitude3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void altitude3_cfg_setup ( altitude3_cfg_t *cfg ); 
 
- Initialization function.
> ALTITUDE3_RETVAL altitude3_init ( altitude3_t *ctx, altitude3_cfg_t *cfg );

- Click Default Configuration function.
> void altitude3_default_cfg ( altitude3_t *ctx );


#### Example key functions :

- Function sends a command to perform a SW Reset of the device.
> void altitude3_soft_reset ( altitude3_t *ctx );
 
- Function reads results of AD conversion, which consists of the 16bit temperature and 24bit
- pressure data in determined order.
> uint8_t altitude3_read_adc_results ( altitude3_t *ctx, uint8_t read_order );

- Function performs a calibration data reading, only once, and then reads a temperature and pressure
- data and calculates these values
- to standard units. Also calculates the altitude depending on the temperature and pressure data.
> uint8_t altitude3_get_data ( altitude3_t *ctx, uint8_t read_order );

## Examples Description

> This application enables high-resolution barometric pressure measurement.

**The demo application is composed of two sections :**

### Application Init 

> Initializes I2C interface and performs a SW Reset of the device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    altitude3_cfg_t cfg;

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

    altitude3_cfg_setup( &cfg );
    ALTITUDE3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    altitude3_init( &altitude3, &cfg );

    altitude3_default_cfg ( &altitude3 );

    log_printf( &logger, "** Altitude 3 Click is initialized **\r\n\r\n" );
}
  
```

### Application Task

> Selects the desired measurement mode and data reading order, and after that
> calculates the temperature, pressure and altitude data to standard units and shows results to uart
> terminal.

```c

void application_task ( void )
{
    uint8_t response;

    response = altitude3_measurement_mode( &altitude3, ALTITUDE3_NORMAL_T_FIRST );

    Delay_ms ( 100 );

    response = altitude3_get_data( &altitude3, response );
    
    if ( response != ALTITUDE3_ERROR )
    {
        log_printf( &logger, "Temperature is : %d C\r\n", ( int16_t ) altitude3.sens_data.temperature );
       
        log_printf( &logger, "Pressure is : %u  mbar[hPa]\r\n", ( uint16_t ) altitude3.sens_data.pressure );
    
        log_printf( &logger, "Altitude is : %d m\r\n\r\n", ( int16_t ) altitude3.sens_data.altitude );

        Delay_ms ( 400 );
    }
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Altitude3

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
