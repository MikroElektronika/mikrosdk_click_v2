

---
# UV 4 click

UV 4 click is a powerful Ultra Violet (UV) sensing device and Ambient Light
Sensor (ALS) Click board, featuring a sensor with a very wide dynamic range
of detectable light intensity, across two ADC range settings.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/uv4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/uv-4-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the UV4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for UV4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void uv4_cfg_setup ( uv4_cfg_t *cfg ); 
 
- Initialization function.
> UV4_RETVAL uv4_init ( uv4_t *ctx, uv4_cfg_t *cfg );

- Click Default Configuration function.
> void uv4_default_cfg ( uv4_t *ctx );


#### Example key functions :

- This function write one byte of data to given address.
> UV4_RETVAL uv4_write_reg ( uv4_t* ctx, const uint8_t reg_address, const uint8_t transfer_data );
 
- This function reads determined number of bytes from given address.
> UV4_RETVAL uv4_read_reg ( uv4_t* ctx, uint8_t reg_address, uint8_t* data_out, uint8_t inc_en, uint8_t n_bytes );

- This function writes one byte of data in parameter table.
> UV4_RETVAL uv4_write_param_data ( uv4_t* ctx, uint8_t param_address, uint8_t transfer_data );

## Examples Description

> Reads all configured measurements from selected channels and logs results every 500ms.


**The demo application is composed of two sections :**

### Application Init 

> Initializes driver, performs reset command and enables selected channels.
 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    uv4_cfg_t cfg;

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

    uv4_cfg_setup( &cfg );
    UV4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uv4_init( &uv4, &cfg );
    uv4_default_cfg( &uv4 );
}
  
```

### Application Task

> Reads all configured measurements from selected channels and logs results every 500ms.

```c

void application_task ( void )
{
    uint8_t cnt;
    uint8_t pom = 1;
    uint32_t data_r[ 6 ];
    
    uv4_read_measurements( &uv4, &data_r[ 0 ] );
    
    for ( cnt = 0; cnt < 6; cnt++ )
    {
        if ( uv4.config_byte & pom )
        {
            switch ( uv4.optical_data[ cnt ] )
            {
                case UV4_OPT_FUNC_SMALL_IR:
                {
                    log_printf( &logger, "Small IR: " );
                    break;
                }
                case UV4_OPT_FUNC_MEDIUM_IR:
                {
                    log_printf( &logger, "Medium IR: " );
                    break;
                }
                case UV4_OPT_FUNC_LARGE_IR:
                {
                    log_printf( &logger, "Large IR: " );
                    break;
                }
                case UV4_OPT_FUNC_WHITE:
                {
                    log_printf( &logger, "White : " );
                    break;
                }
                case UV4_OPT_FUNC_LARGE_WHITE:
                {
                    log_printf( &logger, "Large White: " );
                    break;
                }
                case UV4_OPT_FUNC_UV:
                {
                    log_printf( &logger, "UV: " );
                    break;
                }
                case UV4_OPT_FUNC_UV_DEEP:
                {
                    log_printf( &logger, "UV-Deep: " );
                    break;
                }
                default:
                {
                    break;
                }
            }
            log_printf( &logger, "%d\r\n", data_r[ cnt ] );
        }
        pom <<= 1;
    }
    Delay_ms( 500 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.UV4

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
