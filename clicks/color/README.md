\mainpage Main Page
 
 

---
# Color click

Color click is a color light sensing Click board™, featuring the popular TSC3471 integrated color sensor. It is capable of sensing red, green, and blue light components, as well as the clear light.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/color_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/color-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Color Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https:///shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https:///shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Color Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void color_cfg_setup ( color_cfg_t *cfg ); 
 
- Initialization function.
> COLOR_RETVAL color_init ( color_t *ctx, color_cfg_t *cfg );

- Click Default Configuration function.
> void color_default_cfg ( color_t *ctx );


#### Example key functions :

- This function reads desired color ratio from register.
> float color_read_color_ratio ( color_t *ctx, uint8_t color );

 
- This function reads 3 color filters and clear filters and converts the resulting color from RGBC to HSL.
> float color_get_color_value ( color_t *ctx );


- This function determines which color is read by click sensor function has been invoked previously.
> uint8_t color_get_color ( float color_value );


## Examples Description

The following code demonstrates color detection/recognition functionality of the click.

**The demo application is composed of two sections :**

### Application Init 

Initializes device and driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    color_cfg_t cfg;

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

    color_cfg_setup( &cfg );
    COLOR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    color_init( &color, &cfg );
    color_default_cfg( &color );
    is_color = 0;
}
  
```

### Application Task

Checks which color is detected by the sensor.
The name of the detected color is logged on the USBUART.

```c

void application_task ( void )
{
    color_value = color_get_color_value( &color );
    is_color = color_get_color( color_value );

    switch( is_color )
    {
        case ORANGE_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: ORANGE\r\n" );
            break;
        }
        case RED_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: RED\r\n" );
            break;
        }
        case PINK_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: PINK\r\n" );
            break;
        }
        case PURPLE_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: PURPLE\r\n" );
            break;
        }
        case BLUE_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: BLUE\r\n" );
            break;
        }
        case CYAN_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: CYAN\r\n" );
            break;
        }
        case GREEN_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: GREEN\r\n" );
            break;
        }
        case YELLOW_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: YELLOW\r\n" );
            break;
        }
        default:
        {
            break;
        }
    }

    Delay_ms ( 300 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Color

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https:///shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https:///shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https:///shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https:///shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
