\mainpage Main Page
 
---
# Heart rate 4 click

Heart rate 4 click carries the MAX30101 high-sensitivity pulse oximeter and heart-rate sensor from Maxim Integrated. The click is designed to run on either 3.3V or 5V power supply. It communicates with the target MCU over I2C interface, with additional functionality provided by INT pin on the mikroBUS™ line.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/heartrate4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/heart-rate-4-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the HeartRate4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for HeartRate4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void heartrate4_cfg_setup ( heartrate4_cfg_t *cfg ); 
 
- Initialization function.
> HEARTRATE4_RETVAL heartrate4_init ( heartrate4_t *ctx, heartrate4_cfg_t *cfg );

- Click Default Configuration function.
> void heartrate4_default_cfg ( heartrate4_t *ctx );


#### Example key functions :

- Function is used to read desired interrupt specified by flag.
> uint8_t heartrate4_get_intrrupt ( heartrate4_t *ctx, uint8_t flag );
 
- Function is used to read the oldest RED value.
> uint32_t heartrate4_get_red_val ( heartrate4_t *ctx );

- Function is used to determine which LED is active in each time slot.
> void heartrate4_enable_slot ( heartrate4_t *ctx, uint8_t slot_num, uint8_t dev );

## Examples Description

> This example demonstrates the use of Heart rate 4 click board.

**The demo application is composed of two sections :**

### Application Init 

> Initalizes I2C driver, applies default settings, and makes an initial log.

```c


void application_init ( void )
{
    log_cfg_t log_cfg;
    heartrate4_cfg_t cfg;

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

    heartrate4_cfg_setup( &cfg );
    HEARTRATE4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    heartrate4_init( &heartrate4, &cfg );

    Delay_ms( 100 );
    heartrate4_default_cfg( &heartrate4 );
    Delay_ms( 100 );
}
  
```

### Application Task

> Reads data from Red diode and displays the results on USB UART if the measured data
> is above defined threshold, otherwise, it displays desired message on the terminal.

```c


void application_task ( void )
{
    if ( heartrate4_get_intrrupt( &heartrate4, 1 ) & 0x40 )
    {
        red_samp = heartrate4_get_red_val( &heartrate4 );
        counter++;
        
        // If sample pulse amplitude is not under threshold value 0x8000
        if ( red_samp > 0x8000 )
        {
            log_printf( &logger, "%lu\r\n", red_samp );
            Delay_ms( 1 );
            counter = 200;
        }
        else if ( counter > 200 )
        {
            log_printf( &logger, "Place Finger On Sensor\r\n" );
            Delay_ms( 100 );
            counter = 0;
        }
    }
}

```

## Note
> <pre>
>     MCU              : STM32F107VCT6
>     Dev. Board       : Fusion for ARM v8
> </pre> 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.HeartRate4

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
