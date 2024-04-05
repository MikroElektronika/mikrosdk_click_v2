
---
# Alcohol 2 click

Alcohol 2 click is a very accurate ethanol gas (alcohol) sensor Click board™, equipped with the SPEC amperometric gas sensor which electrochemically reacts with the ethanol.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/alcohol2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/alcohol-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Alcohol2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Alcohol2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void alcohol2_cfg_setup ( alcohol2_cfg_t *cfg ); 
 
- Initialization function.
> ALCOHOL2_RETVAL alcohol2_init ( alcohol2_t *ctx, alcohol2_cfg_t *cfg );

- Click Default Configuration function.
> void alcohol2_default_cfg ( alcohol2_t *ctx );


#### Example key functions :

- This function writes one byte to the register.
> void alcohol2_write_byte ( alcohol2_t *ctx, uint8_t reg, uint8_t w_data );
 
- This function reads one byte from the register.
> uint8_t alcohol2_read_byte ( alcohol2_t *ctx, uint8_t reg );

- This function reads Alcohol data.
> uint16_t alcohol2_read_alcohol ( alcohol2_t *ctx );

## Examples Description

> The demo application gets Alcohol data and logs data to USBUART.

**The demo application is composed of two sections :**

### Application Init 

> Initializes device configuration.

```c

oid application_init ( void )
{
    log_cfg_t log_cfg;
    alcohol2_cfg_t cfg;

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

    ALCOHOL2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    alcohol2_init( &alcohol2, &cfg );

    alcohol2_write_byte( &alcohol2, ALCOHOL2_MODECN_REG, ALCOHOL2_DEEP_SLEEP_MODE );
    alcohol2_write_byte( &alcohol2, ALCOHOL2_LOCK_REG,   ALCOHOL2_WRITE_MODE );
    alcohol2_write_byte( &alcohol2, ALCOHOL2_TIACN_REG, ALCOHOL2_EXT_TIA_RES | ALCOHOL2_100_OHM_LOAD_RES );
    alcohol2_write_byte( &alcohol2, ALCOHOL2_REFCN_REG, ALCOHOL2_VREF_INT | ALCOHOL2_50_PERCENTS_INT_ZERO | ALCOHOL2_BIAS_POL_NEGATIVE | ALCOHOL2_0_PERCENTS_BIAS );

    log_printf( &logger, "Alcohol 2 is initialized\r\n");
    Delay_ms ( 300 );
}
  
```

### Application Task

> Gets Alcohol (C2H5OH) data and logs data to USBUART every 500ms. 

```c

void application_task ( void )
{
    alcohol_value = alcohol2_read_alcohol( &alcohol2 );
    log_printf( &logger, "Alcohol value : %f \r\n",alcohol_value );
    Delay_ms ( 500 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Alcohol2

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