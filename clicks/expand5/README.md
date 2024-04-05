\mainpage Main Page
 
---
# Expand 5 click

EXPAND 5 Click features a low-voltage 24-bit I2C and SMBus I/O expander. This 24-bit I/O expander is designed to provide general-purpose remote I/O expansion for most microcontroller families via the I2C serial interface. This Click board™ features the TCA6424A from Texas Instruments, and it operates over a power supply voltage range of 1.65V to 5.5V. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/expand5_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/expand-5-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jul 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Expand5 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Expand5 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void expand5_cfg_setup ( expand5_cfg_t *cfg ); 
 
- Initialization function.
> EXPAND5_RETVAL expand5_init ( expand5_t *ctx, expand5_cfg_t *cfg );

#### Example key functions :

- Set all OUTPUT pins' logic levels in all banks function
> void expand5_write_all_banks ( expand5_t *ctx, uint8_t bank0, uint8_t bank1, uint8_t bank2 );
 
- Get all pin polarity ( normal/inverted ) settings from one bank function
> uint8_t expand5_get_bank_pol ( expand5_t *ctx, uint8_t bank );

- Get a single pin's direction ( I/O ) setting function
> uint8_t expand5_get_pin_dir ( expand5_t *ctx, uint16_t pin );

## Examples Description

> This example demonstrates the use of Expand 5 Click board.

**The demo application is composed of two sections :**

### Application Init 

> Initalizes I2C driver, resets the device, configures all pins as output and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    expand5_cfg_t cfg;

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

    expand5_cfg_setup( &cfg );
    EXPAND5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    expand5_init( &expand5, &cfg );

    Delay_ms ( 100 );

    log_printf( &logger, "------------------- \r\n" );
    log_printf( &logger, "   EXPAND 5 click   \r\n" );
    log_printf( &logger, "------------------- \r\n" );
    expand5_reset( &expand5 );
    expand5_set_all_dir( &expand5, bank_out, bank_out, bank_out );
    Delay_ms ( 100 );
    log_printf( &logger, "  Pins configured   \r\n" );
    log_printf( &logger, "     as output      \r\n" );
    log_printf( &logger, "------------------- \r\n" );
}
  
```

### Application Task

> This example shows the capabilities of the EXPAND 5 click by toggling each of the 24 available pins.

```c

void application_task ( void )
{
    for ( pin_num = EXPAND5_P00; pin_num <= EXPAND5_P27; pin_num++ )
    {
        expand5_write_all_banks ( &expand5, bank_low, bank_low, bank_low );
        expand5_write_pin ( &expand5, pin_num, EXPAND5_HIGH );
        log_printf( &logger, "Pin %u is high \r\n", ( uint16_t ) pin_num );

        Delay_ms ( 200 );
        expand5_write_all_banks ( &expand5, bank_low, bank_low, bank_low );
    }
    log_printf( &logger, "------------------- \r\n" );
    Delay_ms ( 1000 );
}

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand5

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
