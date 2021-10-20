
---
# Barcode 2 click

Barcode 2 Click is an adapter add-on board that contains a computerized image recognition system that is compliant with a wide range of different 1D and 2D barcode protocols.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/barcode2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/barcode-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the Barcode2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Barcode2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void barcode2_cfg_setup ( barcode2_cfg_t *cfg ); 
 
- Initialization function.
> BARCODE2_RETVAL barcode2_init ( barcode2_t *ctx, barcode2_cfg_t *cfg );


#### Example key functions :

- The function enables or disables barcode scaning depending on state parametar value.
> void barcode2_enable_scaning ( barcode2_t *ctx, uint8_t en_state )
 
- The general process of collecting data the module sends.
> static void barcode2_process ( void )

## Examples Description

> This example reads and processes data from Barcode 2 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the UART driver used for communication and another UART bus used for data logging.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    barcode2_cfg_t cfg;

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

    barcode2_cfg_setup( &cfg );
    BARCODE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    barcode2_init( &barcode2, &cfg );
    Delay_ms ( 100 );
}
  
```

### Application Task

> This is an example that demonstrates the use of the Barcode 2 Click board.
> First, it enables scanning and waits up to 10 seconds for the barcode to be detected.
> If the barcode or QR Code is detected, it displays its content to the USB UART.
> After that, disables scanning for 3 seconds.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void )
{
    log_printf( &logger, "   Scanning enabled   \r\n" );
    log_printf( &logger, "------------------------\r\n" );
    barcode2_enable_scaning( &barcode2, BARCODE2_ENABLE );
    barcode2_process(  );

    barcode2_enable_scaning( &barcode2, BARCODE2_DISABLE );
    log_printf( &logger, "   Scanning disabled   \r\n" );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms( 3000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Barcode2

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
