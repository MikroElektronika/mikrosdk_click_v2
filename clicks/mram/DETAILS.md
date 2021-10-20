

---
# MRAM click

MRAM click features MRAM module which contains 262,144 magnetoresistive memory cells, organized into 32,768 bytes of memory. It means that MRAM click is a memory storage device with 32KB of memory space. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mram_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/mram-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the MRAM Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for MRAM Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void mram_cfg_setup ( mram_cfg_t *cfg ); 
 
- Initialization function.
> MRAM_RETVAL mram_init ( mram_t *ctx, mram_cfg_t *cfg );

- Click Default Configuration function.
> void mram_default_cfg ( mram_t *ctx );


#### Example key functions :

- Function writes n bytes of data from the buffer.
> void mram_write_data_bytes ( mram_t *ctx, const uint16_t address, uint8_t *buffer, const uint16_t nBytes);
 
- Function reads n bytes of data and saves it in buffer.
> void mram_read_data_bytes ( mram_t *ctx, const uint16_t address, uint8_t *buffer, const uint16_t n_bytes);

- Function enables or disables write protect.
> void mram_enable_write_protect ( mram_t *ctx, uint8_t state);

## Examples Description

> This example writes and reads from the Mram Click and displays it on the terminal.

**The demo application is composed of two sections :**

### Application Init 

> Initializes click driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    mram_cfg_t cfg;

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

    mram_cfg_setup( &cfg );
    MRAM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mram_init( &mram, &cfg );
}
  
```

### Application Task

> Writes 6 bytes of buffer data in memory with start address 0x0000. 
> Then reads 3 bytes from memory with start address 0x0002 and shows result on USB UART.

```c

void application_task ( void )
{
    uint8_t number_bytes_write;
    uint8_t number_bytes_read;
    uint16_t i;
    uint8_t data_write[ 10 ] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    uint8_t data_read[ 20 ] = {0};
    
    number_bytes_write = 10;
    number_bytes_read = 10;

    log_printf( &logger, " Data written!\r\n" );
    mram_write_data_bytes ( &mram, 0x0000, data_write, number_bytes_write );
    
    log_printf( &logger, " Read data:\r\n" );
    mram_read_data_bytes ( &mram, 0x0000, data_read, number_bytes_read );
    
    for(i = 0; i < number_bytes_read; i++)
    {
        log_printf( &logger, "%d ", data_read[i] );
    }
    
    log_printf(&logger, "\n");

    Delay_ms(3000);
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.MRAM

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
