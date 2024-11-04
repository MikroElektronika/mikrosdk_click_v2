
---
# NDIR CO2 Click

NDIR CO2 Click is an advanced integrated CO2 gas sensor system, which is able to measure an absolute CO2 concentration, by utilizing the CDM7160 integrated sensor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ndirco2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ndir-co2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the NDIRCO2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for NDIRCO2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ndirco2_cfg_setup ( ndirco2_cfg_t *cfg ); 
 
- Initialization function.
> NDIRCO2_RETVAL ndirco2_init ( ndirco2_t *ctx, ndirco2_cfg_t *cfg );


#### Example key functions :

- CO2 Concentration Read function
> void ndirco2_read_co2 ( ndirco2_t *ctx, uint8_t set_check_mode, uint16_t *output_data );
 
- Average Complete Check function
> uint8_t ndirco2_check_average_complete ( ndirco2_t *ctx );

- Mode Set function
> void ndirco2_set_mode ( ndirco2_t *ctx, uint8_t select_mode );

## Examples Description

> This application measures absolute CO2 concetration.

**The demo application is composed of two sections :**

### Application Init 

> Initializes I2C driver and performs driver reset and determines
> number of averaging measurements.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ndirco2_cfg_t cfg;

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

    ndirco2_cfg_setup( &cfg );
    NDIRCO2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ndirco2_init( &ndirco2, &cfg );

    Delay_ms ( 300 );

    ndirco2_reset( &ndirco2 );
    ndirco2_write_register( &ndirco2, NDIRCO2_AVERAGING_COUNT_REG, 0x03 );
    ndirco2_set_mode( &ndirco2, NDIRCO2_CONTINUOUS_OP_MODE );
    log_printf( &logger, "NDIR CO2 is initialized \r\n" );
    Delay_ms ( 200 );
}
  
```

### Application Task

> Reads CO2 concentration data in ppm unit after each completed measurement.
> One measurement is finished after 300 ms, and period between two measurements is 2 seconds.
> Results of measurements logs on USBUART.

```c

void application_task ( )
{
    uint16_t co2_data;

    ndirco2_read_co2( &ndirco2, NDIRCO2_CHECK_EACH_MEASURE, &co2_data );
    log_printf( &logger, "CO2 concentration is: %d ppm \r\n", co2_data );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.NDIRCO2

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
