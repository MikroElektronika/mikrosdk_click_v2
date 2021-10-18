 
---
# Ambient 11 click

 The Ambient 11 Click is a Click board™ equipped with the VEML6035,
 a low power, high sensitivity, I2C ambient light sensor from Vishay Semiconductors.
 Because of the possibilities its features offer,
 the Ambient 11 Click can be used as an ambient light sensor for mobile devices,
 industrial lighting operation, and as an optical switch for consumer,
 computing and industrial devices and displays.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ambient11_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ambient-11-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Ambient11 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Ambient11 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ambient11_cfg_setup ( ambient11_cfg_t *cfg ); 
 
- Initialization function.
> AMBIENT11_RETVAL ambient11_init ( ambient11_t *ctx, ambient11_cfg_t *cfg );

- Click Default Configuration function.
> void ambient11_default_cfg ( ambient11_t *ctx );


#### Example key functions :

- This function writes data to the desired register.
> void ambient11_generic_write ( ambient11_t *ctx, uint8_t wr_cmd, uint16_t wr_data );
 
- This function reads data from the desired register.
> uint16_t ambient11_generic_read ( ambient11_t *ctx, uint8_t reg_addr );

- Function is used to calculate ambiental illumination.
> float ambient11_calc_illumination ( ambient11_t *ctx, float typical_res );

- Function checks interrupt occurence.
> uint8_t ambient11_check_int ( ambient11_t *ctx );

## Examples Description


> The devices resolution depends on settings applied.
>  User should consult the datasheet and choose resolution value 
>   that corresponds to the settings applied.


**The demo application is composed of two sections :**

### Application Init 


> Initalizes I2C driver, applies low sensitiviti settings
>( GAIN = 0, DG = 0, SENS = 1 and IT = 100ms ) and makes an initial log.
 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ambient11_cfg_t cfg;

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

    ambient11_cfg_setup( &cfg );
    AMBIENT11_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ambient11_init( &ambient11, &cfg );
    ambient11_default_cfg ( &ambient11 );
}
  
```

### Application Task


> This example shows the capabilities of the Ambient 11 click by measuring
>  ambiental illumination and displaying calculated value via USART terminal in luxes.
 

```c

void application_task ( void )
{
    lx_val = ambient11_calc_illumination( &ambient11, resolution );
    log_printf( &logger, "Illumination : %.2f lx \r\n",lx_val );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms( 2000 );
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient11

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
