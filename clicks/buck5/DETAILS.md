
---
# Buck 5 click

Buck 5 Click is a high-efficiency buck (step-down) DC/DC converter, which can provide digitally adjusted step-down voltage on its output while delivering a considerable amount of current. Buck 5 click accepts a wide voltage range on its input - from 5V to 30V. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/buck5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/buck-5-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : sep 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Buck5 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Buck5 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void buck5_cfg_setup ( buck5_cfg_t *cfg ); 
 
- Initialization function.
> BUCK5_RETVAL buck5_init ( buck5_t *ctx, buck5_cfg_t *cfg );


#### Example key functions :

- This function wake up the chip.
> void buck5_power_on ( buck5_t *ctx );
 
- This function reset the chip.
> void buck5_reset ( buck5_t *ctx );

- Maximum output voltage is 5.5V (255 set value), and minimum output voltage is 1V (0 set value).
> void buck5_set_output_voltage ( buck5_t *ctx, uint8_t voltage );

## Examples Description

> Buck 5 Click is a high-efficiency buck DC/DC converter, which can provide digitally 
> adjusted step-down voltage on its output while delivering a considerable amount of current. 
> Buck 5 click accepts a wide voltage range on its input - from 5V to 30V. The output voltage 
> may be adjusted via the SPI interface, in the range from 0.9V to approximately 5.5V.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver init, and enables the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    buck5_cfg_t cfg;

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

    buck5_cfg_setup( &cfg );
    BUCK5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck5_init( &buck5, &cfg );

    buck5_power_on( &buck5 );
    buck5_reset( &buck5 );
}
  
```

### Application Task

> Increases the output voltage by 500mV every 3 seconds from MIN to MAX VOUT.

```c

void application_task ( void )
{
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_MIN );
    log_printf( &logger, "VOUT: MIN\r\n" );
    Delay_ms( 3000 );
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_1000mV );
    log_printf( &logger, "VOUT: ~1V\r\n" );
    Delay_ms( 3000 );
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_1500mV );
    log_printf( &logger, "VOUT: ~1.5V\r\n" );
    Delay_ms( 3000 );
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_2000mV );
    log_printf( &logger, "VOUT: ~2V\r\n" );
    Delay_ms( 3000 );
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_2500mV );
    log_printf( &logger, "VOUT: ~2.5V\r\n" );
    Delay_ms( 3000 );
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_3000mV );
    log_printf( &logger, "VOUT: ~3V\r\n" );
    Delay_ms( 3000 );
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_3500mV );
    log_printf( &logger, "VOUT: ~3.5V\r\n" );
    Delay_ms( 3000 );
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_4000mV );
    log_printf( &logger, "VOUT: ~4V\r\n" );
    Delay_ms( 3000 );
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_4500mV );
    log_printf( &logger, "VOUT: ~4.5V\r\n" );
    Delay_ms( 3000 );
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_5000mV );
    log_printf( &logger, "VOUT: ~5V\r\n" );
    Delay_ms( 3000 );
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_MAX );
    log_printf( &logger, "VOUT: MAX\r\n" );
    Delay_ms( 3000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck5

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
