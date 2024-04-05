
---
# Scanner click

Scanner Click as his name said, is an optical scanner expansion board for building optical cost-sensitive scanners and printers.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/scanner_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/scanner-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the Scanner Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Scanner Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void scanner_cfg_setup ( scanner_cfg_t *cfg ); 
 
- Initialization function.
> SCANNER_RETVAL scanner_init ( scanner_t *ctx, scanner_cfg_t *cfg );

#### Example key functions :

- Pulse function.
> void scanner_clock ( scanner_t *ctx );
 
- Write function.
> void scanner_serial_write_reg ( scanner_t *ctx, uint8_t reg_adr, uint8_t write_data );

- Read pixels.
> void scanner_read_pixel ( scanner_t *ctx, uint8_t *pixel_data );

## Examples Description

> This example reads data from Scanner clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and starts up the module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    scanner_cfg_t cfg;

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
    log_info( &logger, "--->>> APP INIT <<<---\r\n" );

    //  Click initialization.

    scanner_cfg_setup( &cfg );
    SCANNER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    scanner_init( &scanner, &cfg );

    Delay_ms ( 300 );

    scanner_startup( &scanner );
    Delay_ms ( 100 );
    
    scanner_serial_write_reg( &scanner, SCANNER_REG_MODE, SCANNER_DATA_NORMAL_MODE );
    
    for ( uint8_t data_cnt = 0; data_cnt < 3; )
    {
        scanner_serial_write_reg( &scanner, SCANNER_REG_OFFSET_LEFT + ( 2 * data_cnt ), 25 );
        data_cnt++;
        scanner_serial_write_reg( &scanner, SCANNER_REG_GAIN_LEFT + ( 2 * data_cnt ), 25 );
        data_cnt++;
    }
    log_printf( &logger, "--->>> APP TASK <<<--- \r\n" );
}
  
```

### Application Task

> Reads the array of 102 pixels and displays the results on the USB UART as frequently as possible.

```c

void application_task ( void )
{
    uint8_t pixels[ 102 ];
    scanner_read_pixel( &scanner, pixels );
    
    log_printf( &logger, "left center right\r\n" );
    for ( uint8_t cnt = 0; cnt < 34; cnt++ )
    {
        log_printf( &logger, " %u   %u   %u \r\n", ( uint16_t ) pixels[ cnt ], 
                                                   ( uint16_t ) pixels[ cnt + 34 ], 
                                                   ( uint16_t ) pixels[ cnt + 68 ] );
    }
    log_printf( &logger, "----------------\r\n" );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Scanner

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
