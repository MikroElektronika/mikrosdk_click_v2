
---
# Wheatstone Click

> Wheatstone Click is a measurement Click board™ which utilizes a Wheatstone bridge circuit onboard, in order to precisely measure the resistance of an external element. Besides the wheatstone bridge circuit, this Click board™ also utilizes MAX4208 – an ultra-low offset/drift, precision instrumentation amplifier, from Maxim Integrated.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/wheatstone_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/wheatstone-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Wheatstone Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Wheatstone Click driver.

#### Standard key functions :

- `wheatstone_cfg_setup` Config Object Initialization function.
```c
void wheatstone_cfg_setup ( wheatstone_cfg_t *cfg ); 
```

- `wheatstone_init` Initialization function.
```c
err_t wheatstone_init ( wheatstone_t *ctx, wheatstone_cfg_t *cfg );
```

#### Example key functions :

- `wheatstone_set_potentiometer` Set potentiometer ( 0 - 100k )
```c
void wheatstone_set_potentiometer ( wheatstone_t *ctx, uint8_t pot_value );
```

- `wheatstone_read_an_pin_voltage` This function reads results of AD conversion of the AN pin and converts them to proportional voltage level.
```c
err_t wheatstone_read_an_pin_voltage ( wheatstone_t *ctx, float *data_out );
```

## Examples Description

> This example demonstrates the use of Wheatstone Click board by measuring the input resistance.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and logger and sets the default potentiometer (gain) level.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    wheatstone_cfg_t cfg;

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
    wheatstone_cfg_setup( &cfg );
    WHEATSTONE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    wheatstone_init( &wheatstone, &cfg );

    wheatstone_set_potentiometer ( &wheatstone, WHEATSTONE_POT_MAX );

    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> Reads the AN pin voltage and calculates the input resistance from it. All data are being displayed on the USB UART where you can track their changes.

```c

void application_task ( void )
{
    float an_pin_v = 0;
    float vout = 0;
    float r_kohm = 0;
    if ( WHEATSTONE_OK == wheatstone_read_an_pin_voltage ( &wheatstone, &an_pin_v ) ) 
    {
        vout = an_pin_v / wheatstone.gain;
        if ( 0 != vout )
        {
            r_kohm = ( WHEATSTONE_VCC_5V - 2 * vout ) / ( 4 * vout );
        }
        log_printf( &logger, " VCC     : %.3f V\r\n", WHEATSTONE_VCC_5V );
        log_printf( &logger, " GAIN    : %.3f\r\n", wheatstone.gain );
        log_printf( &logger, " AN_PIN  : %.3f V\r\n", an_pin_v );
        log_printf( &logger, " VOUT    : %.3f V\r\n", vout );
        log_printf( &logger, " R_INPUT : %.3f kOhm\r\n\n", r_kohm );
        Delay_ms ( 1000 );
    }
}  

```

## Note

> The following formulas you may find useful:
> - AN_PIN(V) = ( ( 1kOhm + R_INPUT(kOhm) ) / ( 1kOhm + 2*R_INPUT(kOhm) ) - 1/2 ) * VCC(V) * GAIN
> - VOUT(V) = AN_PIN(V) / GAIN
> - R_INPUT(kOhm) = ( VCC(V) * GAIN - 2*AN_PIN(V) ) / ( 4*AN_PIN(V) )
> - R_INPUT(kOhm) = ( VCC(V) - 2*VOUT(V) ) / ( 4*VOUT(V) )

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Wheatstone

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
