\mainpage Main Page
 
---
# Hz to V click

HZ to V click is a device that can converts input frequency of the signal with virtually any wave shape to a DC voltage output, with a level proportional to the input frequency. It has a linear response, and by applying a signal with the frequency between 1kHz to 10kHz on its input, the Click board™ will generate a DC voltage, ranging from 0.33V to 3.3V.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hztov_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/hz-to-v-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : PWM type


# Software Support

We provide a library for the HzToV Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for HzToV Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void hztov_cfg_setup ( hztov_cfg_t *cfg ); 
 
- Initialization function.
> HZTOV_RETVAL hztov_init ( hztov_t *ctx, hztov_cfg_t *cfg );

- Set enable pin state.
> void hztov_set_enable ( hztov_t *ctx, uint8_t state );


#### Example key functions :

- Read voltage function.
> float hztov_read_voltage ( hztov_t *ctx );
 
- Changing the output voltage function.
> void hztov_set_input_frequency ( hztov_t *ctx, uint16_t freq );

## Examples Description

> This example demonstrates the use of Hz to V click board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and enables the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    hztov_cfg_t cfg;

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

    hztov_cfg_setup( &cfg );
    HZTOV_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hztov_init( &hztov, &cfg );
    
    hztov_set_enable ( &hztov, HZTOV_ENABLE );
    
    fin = HZTOV_MIN_FREQ;
    
    Delay_ms ( 100 );
}
  
```

### Application Task

> Sets the PWM frequency then reads the voltage from VO pin and logs all data on USB UART.

```c

void application_task ( void )
{
    if ( fin > HZTOV_MAX_FREQ )
        fin = HZTOV_MIN_FREQ;
    hztov_set_input_frequency( &hztov, fin );
    Delay_ms ( 1000 );
    log_printf( &logger, "Frequency: %u Hz \r\n", fin );
    voltage = 0;
    for ( uint8_t cnt = 0; cnt < 100; cnt++ )
    {
        voltage += hztov_read_voltage( &hztov );
    }
    log_printf( &logger, "Voltage: %.2f V \r\n", voltage / 100.0 );
    log_printf( &logger, "-------------------\r\n" );
    
    fin += 1000;
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}  

```

## Note

> In order to set PWM frequency down to 1 kHz, the user will probably need to lower the main MCU clock frequency.
> The output voltage may vary, depending on the offset potentiometer setting on the click.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.HzToV

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
