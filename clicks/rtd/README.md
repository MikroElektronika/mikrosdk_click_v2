\mainpage Main Page
 
---
# RTD click

> RTD click is based on MAX31865 resistance to digital converter from Maxim Integrated, optimized for platinum resistance temperature detectors, or RTD.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rtd_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/rtd-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Rtd Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Rtd Click driver.

#### Standard key functions :

- `rtd_cfg_setup` Config Object Initialization function.
```c
void rtd_cfg_setup ( rtd_cfg_t *cfg ); 
```

- `rtd_init` Initialization function.
```c
err_t rtd_init ( rtd_t *ctx, rtd_cfg_t *cfg );
```

#### Example key functions :

- `rtd_read_register` This function reads data from the chosen register.
```c
uint8_t rtd_read_register ( rtd_t *ctx, uint8_t reg_address );
```

- `rtd_read_temperature` This function reads data from temperature registers.
```c
uint16_t rtd_read_temperature ( rtd_t *ctx );
```

- `rtd_convert_temperature` This function convert data from temperature registers.
```c
float rtd_convert_temperature ( rtd_t *ctx, uint16_t input_data, uint16_t referent_resistance );
```

## Examples Description

> This app measures temperature and converts the data to celsius degrees.

**The demo application is composed of two sections :**

### Application Init 

> Initializes RTD click driver, and sets the
> proper configuration mode for three wire RTD.

```c
 
void application_init ( void )
{
    log_cfg_t log_cfg;
    rtd_cfg_t cfg;

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
    rtd_cfg_setup( &cfg );
    RTD_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtd_init( &rtd, &cfg );
    
    RTD_SET_DATA_SAMPLE_EDGE;

    rtd_write_register( &rtd, RTD_CONFIGURATION, 0xD0 );
    Delay_ms ( 100 );
    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> Measures temperature, converts the data to celsius degrees,
> and displays it on the USB UART.

```c

void application_task ( void )
{
    uint16_t read_value = 0;
    float converted_value = 0;

    read_value = rtd_read_temperature( &rtd );
    converted_value = rtd_convert_temperature( &rtd, read_value, RTD_REF_RESISTANCE_470 );

    log_printf( &logger, " Current temperature: %.2f \r\n", converted_value );

    Delay_ms( 300 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Rtd

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
