\mainpage Main Page
 
---
# Hydro Probe Click

Hydro Probe Click is a capacitive soil moisture sensor based on capacitive changes that are used to detect the volumetric water content in the soil. Water detection is achieved by using function oscillator MIC1557 and ADC converter MCP3221 from Microchip, which allow you to convert moisture presents to the digital value. Compared to resistant soil moisture sensors, its capacitive style reduces electrode erosion making it corrosion resistant and a better choice for applications such as soil moisture detection and automatic plant watering.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hydroprobe_click.png" height=300px>
</p>


[Click Product page](https://www.mikroe.com/hydro-probe-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jul 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the HydroProbe Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for HydroProbe Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void hydroprobe_cfg_setup ( hydroprobe_cfg_t *cfg ); 
 
- Initialization function.
> HYDROPROBE_RETVAL hydroprobe_init ( hydroprobe_t *ctx, hydroprobe_cfg_t *cfg );

#### Example key functions :

- Get average value function
> uint16_t hydroprobe_avg_val ( hydroprobe_t *ctx );
 
- Get minimum value function
> uint16_t hydroprobe_min_val ( hydroprobe_t *ctx );

- Get Relative humidity of the environment function
> uint8_t hydroprobe_rel_env_hum ( hydroprobe_t *ctx, uint16_t dry_val, uint16_t wet_val );

## Examples Description

> This demo application measures moisture.

**The demo application is composed of two sections :**

### Application Init 

> Initalizes I2C driver, prerforms calibration and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    hydroprobe_cfg_t cfg;

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

    hydroprobe_cfg_setup( &cfg );
    HYDROPROBE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hydroprobe_init( &hydroprobe, &cfg );
    
    Delay_ms ( 100 );

    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "  Hydro Probe Click  \r\n" );
    log_printf( &logger, "---------------------\r\n" );
    hydroprobe_calib( );
    log_printf( &logger, "     Calibrated      \r\n" );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
  
```

### Application Task

> This example shows the capabilities of the Hydro Probe Click by measuring 
> environment moisture content and displaying it in percent via USB UART.

```c

void application_task ( void )
{
    humy_val = hydroprobe_rel_env_hum( &hydroprobe, dry_val, wet_val );
    log_printf( &logger, "Environment moisture content: %d %% \r\n ", ( uint16_t ) humy_val );
    log_printf( &logger, "------------------------------\r\n" );
    Delay_ms ( 1000 );
} 

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.HydroProbe

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
