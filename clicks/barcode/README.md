\mainpage Main Page
 
---
# Barcode Click

Barcode Click is a very fast and agile barcode scanner on a Click board™, which is compliant with a wide range of different 1D and 2D barcode protocols.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/barcode_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/barcode-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Mar 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the Barcode Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Barcode Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void barcode_cfg_setup ( barcode_cfg_t *cfg ); 
 
- Initialization function.
> BARCODE_RETVAL barcode_init ( barcode_t *ctx, barcode_cfg_t *cfg );

#### Example key functions :

- Set PWM pin state.
> void barcode_enable_scaning ( barcode_t *ctx, uint8_t state );
 
- Generic read function.
> uint16_t barcode_generic_read ( barcode_t *ctx, char *data_buf, uint16_t max_len );

## Examples Description

> This example reads and processes data from Barcode clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    barcode_cfg_t cfg;

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
    log_info( &logger, "--->  BarCode Click Init  <---" );

    //  Click initialization.

    barcode_cfg_setup( &cfg );
    BARCODE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    barcode_init( &barcode, &cfg );
    
    Delay_ms ( 500 );
}
  
```

### Application Task

> Reads the received data.

```c

void application_task ( void )
{
    barcode_enable_scaning( &barcode, BARCODE_LOGIC_ON );
    barcode_process( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    barcode_enable_scaning( &barcode, BARCODE_LOGIC_OFF );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Barcode

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
