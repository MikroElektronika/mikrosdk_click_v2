
---
# UVC click

UVC Click is an ultraviolet sensing board which complements UVC Light Click for a ultimate ultraviolet solution. The board is based on GUVC-T21GH ultraviolet sensor from GenUV, capable of measuring UVC spectrum in the range of 220nm up to 280nm and light intensity from 0mW/cm² up to 9.3mW/cm². With high sensitivity and good solar blindness, it can be a perfect solution for monitoring sterilization lamps used in ultraviolet germicidal irradiation (UVGI), a disinfection method that is becoming an essential tool in the battle against viruses and bacteria. UVC Click has two ways of reading UV sensor output, direct analog output value and digital output thanks to MCP3221 ADC converter.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/uvc_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/uvc-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Uvc Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Uvc Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void uvc_cfg_setup ( uvc_cfg_t *cfg ); 
 
- Initialization function.
> UVC_RETVAL uvc_init ( uvc_t *ctx, uvc_cfg_t *cfg );


#### Example key functions :

- This function reads 12bit raw data.
> uint16_t uvc_read_raw_data ( uvc_t *ctx );
 
- This function calculate voltage from raw data.
> float uvc_get_voltage ( uvc_t *ctx );

- This function calculate power from voltage.
> float uvc_calculate_power ( float voltage );

## Examples Description

> This click is capable of measuring UVC spectrum in the range of 220nm up to 280nm and light 
> intensity from 0mW/cm² up to 9.3mW/cm². With high sensitivity and good solar blindness, 
> it can be used for monitoring sterilization lamps. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    uvc_cfg_t cfg;

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

    uvc_cfg_setup( &cfg );
    UVC_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uvc_init( &uvc, &cfg );
}

  
```

### Application Task

> Reads sensor raw data and calculates voltage and power of UVC light.
> The measured values will be displayed on the USB UART every 1500 ms.

```c

void application_task ( void )
{
    uint16_t raw_data;
    float voltage;
    float power;
    
    raw_data = uvc_read_raw_data( &uvc );
    log_printf( &logger, "Raw data: %d\r\n", raw_data );
    
    voltage = uvc_get_voltage( &uvc );
    log_printf( &logger, "Voltage: %.4f mV\r\n", voltage );

    power = uvc_calculate_power( voltage );
    log_printf( &logger, "Power: %.4f mW/cm2\r\n", power );

    log_printf( &logger, "----------------------\r\n" );
    Delay_ms( 1500 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Uvc

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
