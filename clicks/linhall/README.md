\mainpage Main Page
 
 

---
# LIN HALL click

LIN HALL click carries an MLX90242 linear Hall sensor IC (with built-in active error correction circuitry) and an MCP3201 12-bit ADC.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/linhall_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/lin-hall-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the LinHall Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LinHall Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void linhall_cfg_setup ( linhall_cfg_t *cfg ); 
 
- Initialization function.
> LINHALL_RETVAL linhall_init ( linhall_t *ctx, linhall_cfg_t *cfg );

- Click Default Configuration function.
> void linhall_default_cfg ( linhall_t *ctx );


#### Example key functions :

- Read 12-bit data function.
> uint16_t linhall_read_data ( linhall_t *ctx );
 
## Examples Description

> 
> This is a example which demonstrates the use of Lin Hall Click board.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Initializes SPI and LOG structures, initialization driver enable's 
> SPI and start write log.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    linhall_cfg_t cfg;

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
    log_printf( &logger, " Application Init \r\n" );

    //  Click initialization.

    linhall_cfg_setup( &cfg );
    LINHALL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    linhall_init( &linhall, &cfg );
    
    log_printf( &logger, "  Lin Hall click  \r\n" );
    log_printf( &logger, "------------------\r\n" );
    Delay_ms( 100 );
    
    value_adc_old = 0;
    sensitivity = 30;
}
  
```

### Application Task

>
> Read 12-bit ADC value from the MCP3201 chip.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs on usb uart for aproximetly every 100 ms when the ADC value changes.
> 

```c

void application_task ( void )
{
    value_adc = linhall_read_data( &linhall );

    if ( ( ( value_adc - value_adc_old ) > sensitivity ) && ( ( value_adc_old - value_adc ) > sensitivity ) )
    {
        log_printf( &logger, "  ADC Value : %4d \r\n", value_adc );
        log_printf( &logger, "------------------\r\n" );

        value_adc_old = value_adc;
        Delay_ms( 100 );
    }
}  

``` 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LinHall

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
