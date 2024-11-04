\mainpage Main Page
  # Ambient 7 Click

> Ambient 7 Click is a light intensity-sensing and measuring Click board™, which features an accurate light-intensity sensor labeled as SFH 5701 A01, made by Osram Opto Semiconductors.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ambient7_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ambient-7-click)

---


#### Click library 

- **Author**        : Luka Filipovic
- **Date**          : Nov 2019.
- **Type**          : ADC type


# Software Support

We provide a library for the Ambient7 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Ambient7 Click driver.

#### Standard key functions :

- `ambient7_cfg_setup` Config Object Initialization function.
```c
void ambient7_cfg_setup ( ambient7_cfg_t *cfg ); 
```

- `ambient7_init` Initialization function.
```c
err_t ambient7_init ( ambient7_t *ctx, ambient7_cfg_t *cfg );
```

#### Example key functions :

- `ambient7_read_an_pin_value` This function reads results of AD conversion of the AN pin.
```c
err_t ambient7_read_an_pin_value ( ambient7_t *ctx, uint16_t *data_out );
```

- `ambient7_read_an_pin_voltage` This function reads results of AD conversion of the AN pin and converts them to proportional voltage level.
```c
err_t ambient7_read_an_pin_voltage ( ambient7_t *ctx, float *data_out );
```

## Examples Description

> Reads the AN pin voltage.

**The demo application is composed of two sections :**

### Application Init 

> Initializes ADC and LOG for logging data.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ambient7_cfg_t cfg;

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
    ambient7_cfg_setup( &cfg );
    AMBIENT7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ambient7_init( &ambient7, &cfg );
    
    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> Reads the AN pin voltage and displays the results on the USB UART once per second.

```c

void application_task ( void )
{
    float voltage = 0;
    if ( AMBIENT7_OK == ambient7_read_an_pin_voltage ( &ambient7, &voltage ) ) 
    {
        log_printf( &logger, " AN Voltage : %.3f[V]\r\n\n", voltage );
        Delay_ms ( 1000 );
    }
}  

```

## Note

> Illuminance range [ EV ] - from 0.01 [ lx ] to 10k [ lx ]

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient7

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
