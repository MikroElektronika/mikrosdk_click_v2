

---
# CapSense Click

CapSense Click add-on board features a capacitive sensing module CY8C201A0 which takes human body capacitance as an input and directly provides the real time sensor information via I2C output.


<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/capsense_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/capsense-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the CapSense Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for CapSense Click driver.

#### Standard key functions :

- `capsense_cfg_setup` Config Object Initialization function.
```c
void capsense_cfg_setup ( capsense_cfg_t *cfg ); 
```
 
- `capsense_init` Initialization function.
```c
err_t capsense_init ( capsense_t *ctx, capsense_cfg_t *cfg );
```

- `capsense_default_cfg` Click Default Configuration function.
```c
err_t capsense_default_cfg ( capsense_t *ctx );
```

#### Example key functions :

- `capsense_get_slider_lvl` This function gets slider level.
```c
err_t capsense_get_slider_lvl( capsense_t *ctx, uint8_t *slider_lvl );
```

- `capsense_read_data` Read one byte from register address
```c
err_t capsense_read_data( capsense_t *ctx, uint8_t reg_address, uint8_t *read_data );
```

- `capsense_write_data` Generic write data function
```c
err_t capsense_write_data( capsense_t *ctx, uint8_t reg_address, uint8_t write_command );
```

## Examples Description

> This example waits user to press top and bottom button to turn Click's LEDs ON or OFF.

**The demo application is composed of two sections :**

### Application Init 

Initialize CapSense Click and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    capsense_cfg_t cfg;

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
    capsense_cfg_setup( &cfg );
    CAPSENSE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    capsense_init( &capsense, &cfg );
    
    if ( CAPSENSE_ERROR == capsense_default_cfg ( &capsense ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> Press top and bottom button and turn it ON or OFF button LED's.

```c

void application_task ( void )
{
    static uint8_t current_led_state = 0;
    uint8_t output_lvl[ 10 ] = { 0 };
    uint8_t button_select = 0;
    uint8_t slider_lvl = 0;
    capsense_read_data( &capsense, CAPSENSE_CS_READ_STATUS0, &button_select );
    capsense_get_slider_lvl( &capsense, &slider_lvl );
    capsense_write_data( &capsense, CAPSENSE_OUTPUT_PORT0, current_led_state );
    Delay_ms ( 100 );

    if ( 8 == button_select )
    {
        current_led_state ^= 0x01;
        log_printf( &logger, "Toggle LED1\r\n");
        Delay_ms ( 100 );
    }
    if ( 16 == button_select )
    {
        current_led_state ^= 0x02;
        log_printf( &logger, "Toggle LED2\r\n");
        Delay_ms ( 100 );
    }
    if ( 24 == button_select )
    {
        current_led_state = ~current_led_state;
        log_printf( &logger, "Toggle both LEDs\r\n");
        Delay_ms ( 100 );
    }

    if ( slider_lvl )
    {
        bits_to_str( slider_lvl, output_lvl );
        log_printf( &logger, "Slider level - channels [5-1]:\t%s \r\n", &output_lvl[ 3 ] );
        Delay_ms ( 100 );
    }
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.CapSense

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
