\mainpage Main Page
 
---
# HZ to V 2 click

HZ to V 2 click is a device that can convert input frequency of the signal with virtually any wave shape to a DC voltage output, with a level proportional to the input frequency.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hztov2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/hz-to-v-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : ADC type


# Software Support

We provide a library for the HzToV2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for HzToV2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void hztov2_cfg_setup ( hztov2_cfg_t *cfg ); 
 
- Initialization function.
> HZTOV2_RETVAL hztov2_init ( hztov2_t *ctx, hztov2_cfg_t *cfg );


#### Example key functions :

- This function enable the click board.
> void hztov2_en_pin ( hztov2_t *ctx, uint8_t pin_state );

- This function read ADC data and converts it to voltage.
> float hztov2_read_voltage ( hztov2_t *ctx );
 
- This function sets PWM clock frequency at FIN pin.
> HZTOV2_RETVAL hztov2_fin_set ( hztov2_t *ctx, uint32_t fin );

## Examples Description

> This app converts input frequency to a DC voltage output.

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the logger and the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    hztov2_cfg_t cfg;

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

    hztov2_cfg_setup( &cfg );
    HZTOV2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hztov2_init( &hztov2, &cfg );
    hztov2_en_pin( &hztov2, 1 );
    
    fin = 10000;
    
    Delay_ms( 100 );
}
  
```

### Application Task

> Sets the PWM frequency then reads the voltage from VO pin and logs all data on USB UART.

```c

void application_task ( void )
{
    if ( fin > 120000 )
        fin = 10000;
    hztov2_fin_set( &hztov2, fin );
    log_printf( &logger, "Frequency: %lu Hz \r\n", fin );
    Delay_ms( 100 );
    
    voltage = hztov2_read_voltage( &hztov2 );
    log_printf( &logger, "Voltage: %.2f V \r\n", voltage );
    
    fin += 10000;
    Delay_ms( 2000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.HzToV2

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
