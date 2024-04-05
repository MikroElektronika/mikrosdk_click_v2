

---
# DIGI POT 3 click

DIGI POT 3 click is a versatile and feature-rich digital potentiometer click with 1024 steps and an internal non-volatile memory (EEMEM), which can be used for storing the wiper position, but also for storing various user data.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/digipot3_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/digi-pot-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the DigiPot3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for DigiPot3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void digipot3_cfg_setup ( digipot3_cfg_t *cfg ); 
 
- Initialization function.
> DIGIPOT3_RETVAL digipot3_init ( digipot3_t *ctx, digipot3_cfg_t *cfg );

- Click Default Configuration function.
> void digipot3_default_cfg ( digipot3_t *ctx );


#### Example key functions :

- This function stores 16-bit data to the desired EEMEM (non volatile) memory location.
> uint8_t digipot3_store_eemem ( digipot3_t *ctx, uint8_t location_address, uint16_t transfer_data );
 
- This function executes the desired command.
> uint8_t digipot3_send_command ( digipot3_t *ctx, uint8_t command_byte );

- This function writes 10-bit value to DAC register and determines the wiper position.
> uint8_t digipot3_write_dac ( digipot3_t *ctx, uint16_t value_dac );

## Examples Description

> This app get value from digital potentiometer and stored to the EEMEM memory.

**The demo application is composed of two sections :**

### Application Init 

> Initializes device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    digipot3_cfg_t cfg;

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

    digipot3_cfg_setup( &cfg );
    DIGIPOT3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    digipot3_init( &digipot3, &cfg );

    Delay_ms ( 200 );
    
    digipot3_read_dac(  &digipot3, &digital_value );
    digipot3_read_eemem( &digipot3, DIGIPOT3_RDAC_EEMEM_LOC, &eemem_value );
    
    if ( eemem_value != digital_value )
    {
        digipot3_send_command( &digipot3, DIGIPOT3_RESTORE_EEMEM_TO_RDAC_COMM );
    }

    log_printf( &logger, "DIGI POT 3 is initialized \r\n" );
    Delay_ms ( 200 );
}
  
```

### Application Task

> Increments the wiper position by 6dB every 2 seconds. When wiper position
> reaches the desired value (0x0200), then the wiper position be decremented by 6dB every 2 seconds, until position 
> value reaches the new desired value (0x0002). After that the new position value will be stored to the EEMEM memory,
> if that value does not already exist in the EEMEM memory.

```c

void application_task ( void )
{
    while ( digital_value < 0x0200 )
    {
        digipot3_send_command( &digipot3, DIGIPOT3_INCREMENT_RDAC_6DB_COMM );
        digipot3_read_dac( &digipot3, &digital_value );
        log_printf( &logger, "DAC value is: %u \r\n", digital_value );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }

    while ( digital_value > 0x0002 )
    {
        digipot3_send_command( &digipot3, DIGIPOT3_DECREMENT_RDAC_6DB_COMM );
        digipot3_read_dac( &digipot3, &digital_value );
        log_printf( &logger, "DAC value is: %u \r\n", digital_value );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }

    if ( eemem_value != digital_value )
    {
        digipot3_send_command( &digipot3, DIGIPOT3_STORE_RDAC_TO_EEMEM_COMM );
        eemem_value = digital_value;
    }
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.DigiPot3

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
