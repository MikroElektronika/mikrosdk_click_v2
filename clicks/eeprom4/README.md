\mainpage Main Page
 
 

---
# EEPROM 4 Click

<EEPROM 4 Click is 2,097,152 bits on a Click board™, organized into 262,144 bytes. In other words, this Click board™ is an EEPROM memory medium with the capacity of 256 KB.>

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/eeprom4_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/eeprom-4-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : nov 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Eeprom4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Eeprom4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void eeprom4_cfg_setup ( eeprom4_cfg_t *cfg ); 
 
- Initialization function.
> EEPROM4_RETVAL eeprom4_init ( eeprom4_t *ctx, eeprom4_cfg_t *cfg );

- Click Default Configuration function.
> void eeprom4_default_cfg ( eeprom4_t *ctx );


#### Example key functions :

- Status register write function
> void eeprom4_write_status_reg ( eeprom4_t *ctx, uint8_t data_value );
 
- Memory array write function
> void eeprom4_write_memory ( eeprom4_t *ctx, uint32_t memory_address, uint8_t *data_input, uint8_t n_bytes );

- Memory array read function
> void eeprom4_read_memory ( eeprom4_t *ctx, uint32_t memory_address, uint8_t *data_output, uint8_t n_bytes );

## Examples Description

> This Click is a memmory.

**The demo application is composed of two sections :**

### Application Init 

>
> Initializes Click driver and configures Click that all memory block > is unprotected.
> Also configures that HOLD operation is disabled, and the memory and > status register are writable.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    eeprom4_cfg_t cfg;

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

    eeprom4_cfg_setup( &cfg );
    EEPROM4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    eeprom4_init( &eeprom4, &cfg );
}
  
```

### Application Task

>
> Enables writting to memory array, writes data from buffer to memory,
> checks if the part is in a write cycle, and if is not reads data >  > from memory array and stores data to buffer.
> Storaged data shows on USB UART.
> 

```c
void application_task (  )
{
    uint8_t data_write[ 13 ] = { 'M', 'i', 'K', 'r', 'O', 'e', 0 };
    uint8_t data_read[ 255 ] = { 0 };
    uint8_t cnt;
    uint8_t check_state;

    eeprom4_send_command( &eeprom4, EEPROM4_SET_WRITE_ENABLE_LATCH_COMMAND );
    eeprom4_write_memory( &eeprom4, EEPROM4_FIRST_MEMORY_LOCATION, data_write, 
6 );

    cnt = eeprom4_check_status_reg( &eeprom4, EEPROM4_READY_BIT );
    check_state = eeprom4_send_command( &eeprom4, EEPROM4_LOW_POWER_WRITE_POLL_COMMAND );
    
    while ( cnt | check_state )
    {
        cnt = eeprom4_check_status_reg( &eeprom4, EEPROM4_READY_BIT );
        check_state = eeprom4_send_command( &eeprom4, EEPROM4_LOW_POWER_WRITE_POLL_COMMAND );
    }
    
    eeprom4_read_memory( &eeprom4, 0x00000000, data_read, 6 );

    for ( cnt = 0; cnt < 6; cnt++ )
    {
        log_printf( &logger, " %c ", data_read[cnt] );
    }
    log_printf( &logger, "-----   \r\n" );
    
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Eeprom4

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
