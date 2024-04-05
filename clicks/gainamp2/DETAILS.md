

---
# GainAMP 2 click

GainAMP 2 click is a 6-channel programmable gain amplifier, used to amplify signals on any of the 6 non-inverting input channels up to 32x, in eight discrete steps.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gainapm2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/gainamp-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the GainAmp2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for GainAmp2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void gainamp2_cfg_setup ( gainamp2_cfg_t *cfg ); 
 
- Initialization function.
> GAINAMP2_RETVAL gainamp2_init ( gainamp2_t *ctx, gainamp2_cfg_t *cfg );


#### Example key functions :

- Set the channel gain.
> void gainamp2_set_channel_gain ( gainamp2_t *ctx, uint8_t channel, uint8_t gain );
 
- Return voltage measured from VOUT pin.
> float gainamp2_get_voltage ( gainamp2_t *ctx );

- Send Command
> void gainamp2_write_Command( gainamp2_t *ctx, uint8_t instruction, uint8_t input )

## Examples Description

> This application is programmable gain amplifier

**The demo application is composed of two sections :**

### Application Init 

> Initializes and sets GainAMP 2 click channel 0 to amplify the signal 2 times

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    gainamp2_cfg_t cfg;

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

    gainamp2_cfg_setup( &cfg );
    GAINAMP2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gainamp2_init( &gainamp2, &cfg );
    
    gainamp2_set_channel_gain ( &gainamp2, GAINAMP2_CH0, GAINAMP2_GAIN_2X );
    log_printf( &logger,"Channel 0 - aplified 2x \r\n" ); 
}
  
```

### Application Task

> Displays the voltage measured from VOUT pin

```c

void application_task ( void )
{
    log_printf( &logger,"Voltage at VOUT: %f \r\n", gainamp2_get_voltage( &gainamp2 ) );
    log_printf( &logger,"------------------------------- \r\n " );
    Delay_ms ( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.GainAmp2

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
