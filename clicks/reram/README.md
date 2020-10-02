\mainpage Main Page

 

---
# ReRAM click

ReRAM Click features ReRAM (Resistive Random Access Memory) module which contains the cell array made of 524.288 words x 8 bits, which totals 4 Mbits of data.
The used memory module can withstand a large number of write cycles, it has data retention period greater than 10 years and it can read and write to random addresses with no delay.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/reram_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/reram-click>)

---


#### Click library

- **Author**        : Nemanja Medakovic
- **Date**          : Oct 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Reram Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers).
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account.

## Library Description

> This library contains API for Reram Click driver.

#### Standard key functions :

- Configuration Object Setup function.
> void reram_cfg_setup( reram_cfg_t *cfg );

- Click Initialization function.
> reram_err_t reram_init( reram_t *ctx, reram_cfg_t *cfg );

- Click Default Configuration function.
> void reram_default_cfg ( reram_t *ctx );


#### Example key functions :

- Command Send function.
> reram_err_t reram_send_cmd( reram_t *ctx, reram_spi_data_t cmd_code );
 
- Status Read function.
> reram_spi_data_t reram_read_status( reram_t *ctx );

- Memory Write function.
> reram_err_t reram_write_memory( reram_t *ctx, uint32_t mem_addr, reram_spi_data_t *data_in, uint16_t n_bytes );

## Examples Description

>
> This example demonstrates the use of the ReRAM Click board.
>

**The demo application is composed of two sections :**

### Application Init

>
> Initializes SPI serial interface and puts a device to the initial state.
> Data from 0 to 255 will be written in memory block from address 0x0 to address 0xFF.
>

```c

void application_init( void )
{
    reram_cfg_t reram_cfg;
    log_cfg_t logger_cfg;
    reram_spi_data_t data_in[ RERAM_TRANSFER_BYTES_MAX ];
    uint16_t cnt;

    //  Click object initialization.
    reram_cfg_setup( &reram_cfg );
    RERAM_MAP_MIKROBUS( reram_cfg, MIKROBUS_1 );
    reram_init( &reram, &reram_cfg );

    //  Click start configuration.
    reram_default_cfg( &reram );

    //  Logger initialization.
    LOG_MAP_USB_UART( logger_cfg );
    logger_cfg.baud = 57600;
    log_init( &logger, &logger_cfg );
    log_write( &logger, "***  ReRAM Initialization Done  ***", LOG_FORMAT_LINE );
    log_write( &logger, "***********************************", LOG_FORMAT_LINE );

    //  Memory writing.
    data_in[ RERAM_MEM_ADDR_START ] = 0;

    for (cnt = 0x1; cnt < RERAM_TRANSFER_BYTES_MAX; cnt++)
    {
        data_in[ cnt ] = data_in[ cnt - 1 ] + 1;
    }

    reram_send_cmd( &reram, RERAM_CMD_WREN );
    reram_write_memory( &reram, RERAM_MEM_ADDR_START, data_in,
                        RERAM_TRANSFER_BYTES_MAX );
    Delay_ms( 1000 );
}

```

### Application Task

>
> Reads same memory block starting from address 0x0 to address 0xFF and
> sends memory content to USB UART, to verify memory write operation.
>

```c

void application_task( void )
{
    reram_spi_data_t data_out;
    static uint16_t mem_addr = RERAM_MEM_ADDR_START;

    reram_read_memory( &reram, mem_addr, &data_out, 1 );

    log_printf( &logger, "* Memory Address [0x%X] : %u", mem_addr, data_out );
    log_write( &logger, "", LOG_FORMAT_LINE );

    if (mem_addr < 0xFF)
    {
        mem_addr++;
    }
    else
    {
        mem_addr = RERAM_MEM_ADDR_START;
    }

    Delay_ms( 500 );
}

```

## Note

>
> Write Enable Latch is reset after the following operations:
>  - After 'Write Disable'command recognition.
>  - The end of writing process after 'Write Status' command recognition.
>  - The end of writing process after 'Write Memory' command recognition.
>
> Data will not be written in the protected blocks of the ReRAM array.
>  - Upper 1/4 goes from address 0x60000 to 0x7FFFF.
>  - Upper 1/2 goes from address 0x40000 to 0x7FFFF.
>  - The entire ReRAM array goes from address 0x00000 to 0x7FFFF.
>

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Reram

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
