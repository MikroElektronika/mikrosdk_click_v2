

---
# Altitude 2 click

Altitude 2 click is a high-resolution barometric pressure sensor Click board™. It provides very accurate measurements of temperature and atmospheric pressure, which can be used to calculate the altitude with a very high resolution of 20cm per step. Besides that, the device also includes features such as the ultra-low noise delta-sigma 24bit ADC, low power consumption, fast conversion times, pre-programmed unique compensation values, and more.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/altitude2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/altitude-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Altitude2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Altitude2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void altitude2_cfg_setup ( altitude2_cfg_t *cfg ); 
 
- Initialization function.
> ALTITUDE2_RETVAL altitude2_init ( altitude2_t *ctx, altitude2_cfg_t *cfg );

- Click Default Configuration function.
> void altitude2_default_cfg ( altitude2_t *ctx );


#### Example key functions :

- This function resets the device and reads calibration coefficients after reset.
> void altitude2_reset( altitude2_t *ctx );
 
- This function reads calibration data from PROM.
> uint8_t altitude2_read_prom ( altitude2_t *ctx, uint8_t select_data, uint32_t *data_out );

- This function determines oversampling ratio for temperature and pressure measurement.
> uint8_t altitude2_set_ratio( altitude2_t *ctx, uint8_t temp_ratio, uint8_t press_ratio );

## Examples Description

This example demonstrates the use of Altitude 2 Click to measure temperature, altitude and pressure.

**The demo application is composed of two sections :**

### Application Init 

> Initializes I2C driver and performs the device reset,
> after which the calibration coefficients be read.
> Determines the ratio value for temperature and pressure measurements.
> Calibration coefficients are necessary to read after the device reset.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    altitude2_cfg_t cfg;

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

    altitude2_cfg_setup( &cfg );
    ALTITUDE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    altitude2_init( &altitude2, &cfg );
    Delay_ms( 500 );
    altitude2_reset( &altitude2 );
    
    altitude2_set_ratio ( &altitude2, ALTITUDE2_RATIO_2048, ALTITUDE2_RATIO_2048 );
    log_printf( &logger, "Altitude 2 is initialized\r\n" );
    Delay_ms( 200 );
}
  
```

### Application Task

> Gets temperature data in celsius value and pressure data in mbar value.
> Gets the calculated altitude value in meters which depends on the temperature and pressure measurements.
> Logs results on USBUART and repeats operation each second.

```c

void application_task ( void )
{
    altitude2_read_data( &altitude2, &temperature, &pressure, &altitude );

    log_printf( &logger, "Temperature: %.2f Celsius\r\n", temperature );
    log_printf( &logger, "Pressure: %.2f mbar\r\n", pressure );
    log_printf( &logger, "Altitude: %.2f m\r\n", altitude );
    log_printf( &logger, "---------------------------------------\r\n\r\n" );

    Delay_ms( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Altitude2

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
