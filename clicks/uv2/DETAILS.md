
---
# UV 2  click

UV 2 click is a mikroBUS™ add-on board with a VEML6075 UVA and UVB light sensor. VEML6075 is a CMOS chip that incorporates a photodiode, amplifiers, and analog/digital circuits.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/uv2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/uv2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the UV2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for UV2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void uv2_cfg_setup ( uv2_cfg_t *cfg ); 
 
- Initialization function.
> UV2_RETVAL uv2_init ( uv2_t *ctx, uv2_cfg_t *cfg );

- Click Default Configuration function.
> void uv2_default_cfg ( uv2_t *ctx );


#### Example key functions :

- This function set active force mode by write force mode UV_AF bit to config register of VEML6075 sesnor on UV 2 Click.
> void uv2_set_active_force_mode ( uv2_t *ctx, uint8_t force_mode );
 
- This function get UVA data by read UVA register value of VEML6075 sesnor on UV 2 Click.
> uint16_t uv2_get_uva ( uv2_t *ctx );

- This function get UVB data by read UVB register value of VEML6075 sesnor on UV 2 Click.
> uint16_t uv2_get_uvb ( uv2_t *ctx );

## Examples Description

> This app measurement UVA and UVB data and calculate UV index level.

**The demo application is composed of two sections :**

### Application Init 

> Initialization device and set default cinfiguration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    uv2_cfg_t cfg;

    uint8_t state_id;

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
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    uv2_cfg_setup( &cfg );
    UV2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uv2_init( &uv2, &cfg );

    Delay_ms ( 100 );

    log_printf( &logger, "------------------------\r\n" );
    log_printf( &logger, "       UV 2  Click      \r\n" );
    log_printf( &logger, "------------------------\r\n" );

    uv2_default_cfg( &uv2 );

    state_id = uv2_check_id( &uv2 );
    
    if ( state_id )
    {
        log_printf( &logger, "       Configured       \r\n" );
    }
    else
    {
        log_printf( &logger, "         ERROR          \r\n" );
    }

    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 100 );
}
  
```

### Application Task

> This is a example which demonstrates the use of UV 2 Click board.
> UV 2 Click communicates with VEML6075 sesnor via I2C by write to register and read from register.
> This example measurement UVA and UVB data, calculate UV index level and write log.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on usb uart changes for every 2 sec.

```c

void application_task ( void )
{
    uint16_t val_uva;
    uint16_t val_uvb;
    float uv_index;

    val_uva = uv2_get_uva( &uv2 );
    log_printf( &logger, " UVA data = %d \r\n", val_uva );

    val_uvb = uv2_get_uvb( &uv2 );
    log_printf( &logger, " UVB data = %d \r\n", val_uvb );

    uv_index = uv2_get_uv_index( &uv2 );
    log_printf( &logger, " UV Index = %f \r\n", uv_index );

    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.UV2

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
