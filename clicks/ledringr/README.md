\mainpage Main Page
 
---
# Led ring R  click

LED ring  R click is a mikroBUS™ add-on board with a ring of 32 red LEDs driven by four 74HC595 serial-in, parallel-out shift registers.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ledringr_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/led-ring-r-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the LedringR Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LedringR Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ledringr_cfg_setup ( ledringr_cfg_t *cfg ); 
 
- Initialization function.
> LEDRINGR_RETVAL ledringr_init ( ledringr_t *ctx, ledringr_cfg_t *cfg );

- Generic transfer function.
> void ledringr_generic_transfer ( ledringr_t *ctx, spi_master_transfer_data_t *block );


#### Example key functions :

- Generic write function.
> void ledringr_write_data ( ledringr_t *ctx, uint32_t data_to_write );
 
- Turn On LED by position.
> void ledringr_turn_on_led ( ledringr_t *ctx, uint8_t led_position );

- Set led.
> void ledringr_led_ring_set ( ledringr_t *ctx );

## Examples Description

> LED ring  R click is a mikroBUS™ add-on board with a ring of 32 red LEDs driven. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes SPI driver and performs device configuration. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ledringr_cfg_t cfg;

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

    ledringr_cfg_setup( &cfg );
    LEDRINGR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ledringr_init( &ledringr, &cfg );
}
  
```

### Application Task

> Show functionality of Led_Ring_R Click, rotating and turn on/off led's, using the SPI interface. 

```c

void application_task ( void )
{
    uint32_t ring_led_on = 0x00000001;
    uint8_t ring_led_counter;
    uint8_t number_led;

    ledringr_led_ring_set( &ledringr );

    for ( ring_led_counter = 32; ring_led_counter > 0; ring_led_counter--)
    {
        ledringr_turn_on_led( &ledringr, ring_led_counter );
        Delay_100ms( );
    }

    Delay_100ms( );

    while ( ring_led_on < 0xFFFFFFFF )
    {
        ledringr_write_data( &ledringr, ring_led_on );
        ring_led_on = ring_led_on | (ring_led_on << 1);
        Delay_100ms( );
    }
    ledringr_write_data( &ledringr, ring_led_on );

    while ( ring_led_on > 0x00000001 )
    {
        ledringr_write_data( &ledringr, ring_led_on );
        ring_led_on = ring_led_on >> 1;
        Delay_100ms( );
    }
    ledringr_write_data( &ledringr, ring_led_on );

    Delay_100ms( );

    ring_led_on = 0x11111111;
    for ( ring_led_counter = 0; ring_led_counter < 32; ring_led_counter++ )
    {
        ledringr_write_data( &ledringr, ring_led_on );

        ring_led_on *= 2;

        if ( ring_led_on == 0x88888888 )
        {
            ring_led_on = 0x11111111;
        }
            
        Delay_100ms( );
    }
    
    for ( ring_led_counter = 0; ring_led_counter < 16; ring_led_counter++ )
    {
        ledringr_write_data( &ledringr, 0xAAAAAAAA );
        Delay_100ms( );
        
        ledringr_write_data( &ledringr, 0x55555555 );
        Delay_100ms( );
    }

    ledringr_led_ring_reset( &ledringr );

    Delay_1sec( );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LedringR

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
