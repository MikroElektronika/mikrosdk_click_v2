
---
# Dot-Matrix R click

Dot Matrix R Click is a display device Click board™ based on a four-digit dot matrix display module, labeled as HCMS-3906 from a company Avago (Broadcom Inc).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dotmatrixr_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/dot-matrix-r-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jul 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the DotMatrixR Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for DotMatrixR Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void dotmatrixr_cfg_setup ( dotmatrixr_cfg_t *cfg ); 
 
- Initialization function.
> DOTMATRIXR_RETVAL dotmatrixr_init ( dotmatrixr_t *ctx, dotmatrixr_cfg_t *cfg );

#### Example key functions :

- Sets BL pin to high or low state
> void dotmatrixr_set_bl_pin_state ( dotmatrixr_t *ctx, uint8_t state );
 
- Restart device 
> void dotmatrixr_restart ( dotmatrixr_t *ctx );

- Sets display to written value
> void dotmatrixr_write_ascii ( dotmatrixr_t *ctx, char *ascii_data );

## Examples Description

> This demo application show data on display.

**The demo application is composed of two sections :**

### Application Init 

> Configuration device

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    dotmatrixr_cfg_t cfg;

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

    dotmatrixr_cfg_setup( &cfg );
    DOTMATRIXR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dotmatrixr_init( &dotmatrixr, &cfg );

    Delay_ms( 100 );
    dotmatrixr_restart( &dotmatrixr );
    Delay_ms( 500 );
    
    dotmatrixr_set_bl_pin_state( &dotmatrixr, 0 );
    dotmatrixr_set_rs_pin_state( &dotmatrixr, 0 );

    dotmatrixr_ctrl_1( &dotmatrixr, DOTMATRIXR_CTRL_BYTE_1_OSC_PRESCALER_1 |
                       DOTMATRIXR_CTRL_BYTE_1_DOUT_DIN );
    dotmatrixr_ctrl_0( &dotmatrixr, DOTMATRIXR_CTRL_BYTE_0_BRIGHTNESS_30 |
                       DOTMATRIXR_CTRL_BYTE_0_PIXEL_PEAK_CURRENT_9p3mA |
                       DOTMATRIXR_CTRL_BYTE_0_MODE_NORMAL );
}
  
```

### Application Task

> Display shows 3 different data in span of 1 second

```c

void application_task ( void )
{
    dotmatrixr_write_ascii( &dotmatrixr, &demo_t1[ 0 ] );
    Delay_ms( 1000 );
    dotmatrixr_write_ascii( &dotmatrixr, &demo_t2[ 0 ] );
    Delay_ms( 1000 );
    dotmatrixr_write_ascii( &dotmatrixr, &demo_t3[ 0 ] );
    Delay_ms( 1000 );
}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.DotMatrixR

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
