
---
# Pressure 2 click

> Pressure 2 click carries MS5803, a high resolution MEMS pressure sensor that is both precise and robust.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pressure-2-click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pressure-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Pressure2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Pressure2 Click driver.

#### Standard key functions :

- `pressure2_cfg_setup` Config Object Initialization function.
```c
void pressure2_cfg_setup ( pressure2_cfg_t *cfg ); 
```

- `pressure2_init` Initialization function.
```c
err_t pressure2_init ( pressure2_t *ctx, pressure2_cfg_t *cfg );
```

- `pressure2_default_cfg` Click Default Configuration function.
```c
err_t pressure2_default_cfg ( pressure2_t *ctx );
```

#### Example key functions :

- `pressure2_read_coefficient` This function read calibration coefficients and return coefficient.
```c
uint16_t pressure2_read_coefficient ( pressure2_t *ctx, uint8_t index );
```

- `pressure2_send_cmd_adc` This function preforms ADC conversion and return 24bit result.
```c
uint32_t pressure2_send_cmd_adc ( pressure2_t *ctx, uint8_t cmd );
```

- `pressure2_read_sensor` Functions for readding sensor.
```c
void pressure2_read_sensor ( pressure2_t *ctx, float *press, float *temp );
```

## Examples Description

> This application measures pressure in range from 0 to 14 bars (with a resolution of up to 0.2 mbars),
but because of the stainless steel cap enclosure, the sensor can withstand up to 30 bars of pressure.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver init and chip init.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    pressure2_cfg_t pressure2_cfg;

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
    pressure2_cfg_setup( &pressure2_cfg );
    PRESSURE2_MAP_MIKROBUS( pressure2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == pressure2_init( &pressure2, &pressure2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PRESSURE2_ERROR == pressure2_default_cfg ( &pressure2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> Reads sensor and logs to USB UART pressure and temperature every second. 

```c

void application_task ( void )
{
    pressure2_read_sensor( &pressure2, &pressure, &temperature );
    
    log_printf( &logger," Pressure: %.2f mBar\r\n", pressure );
    log_printf( &logger," Temperature: %.2f degC\r\n\n", temperature );

    Delay_ms( 1000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure2

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
