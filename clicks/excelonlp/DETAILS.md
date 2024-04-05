
---
# Excelon LP click

Excelon LP click carries a ferroelectric RAM module. Ferroelectric RAM, also known as FRAM, is a non-volatile memory type, with characteristics comparable to much faster DRAM memory modules.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/excelonlp_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/excelon-lp-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the ExcelonLP Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for ExcelonLP Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void excelonlp_cfg_setup ( excelonlp_cfg_t *cfg ); 
 
- Initialization function.
> EXCELONLP_RETVAL excelonlp_init ( excelonlp_t *ctx, excelonlp_cfg_t *cfg );

#### Example key functions :

- Functions for send opcode command
> void excelonlp_send_command ( excelonlp_t *ctx, uint8_t opcode );
 
- Functions for read data
> void excelonlp_read_data ( excelonlp_t *ctx, uint8_t opcode, uint8_t *out_buf, uint8_t n_data);

- Functions for write data to memory
> void excelonlp_write_memory_data ( excelonlp_t *ctx, uint8_t opcode, uint32_t addr, uint8_t c_data);

## Examples Description

> This application writes in RAM memory and read from RAM memory.

**The demo application is composed of two sections :**

### Application Init 

> Initializes Device init

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    excelonlp_cfg_t cfg;

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

    excelonlp_cfg_setup( &cfg );
    EXCELONLP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    excelonlp_init( &excelonlp, &cfg );
}
  
```

### Application Task

> Reads device ID, writes 6-bytes (MikroE) to memory and reads 6-bytes from memory

```c

void application_task ( )
{
    uint8_t out_buf[ 20 ] = { 0 };
    uint8_t cnt;
    char memory_data[ 3 ];
    uint8_t send_buffer[ 7 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 0 };
    uint32_t memory_address = 0x00000055;

    log_printf( &logger, "Read Device ID: " );
    excelonlp_send_command( &excelonlp, EXCELONLP_OPCODE_SET_WRITE_ENABLE_LATCH );
    excelonlp_read_data( &excelonlp, EXCELONLP_OPCODE_READ_DEVICE_ID, &out_buf[ 0 ], 9 );
    for( cnt = 0; cnt < 9; cnt++ )
    {
        log_printf( &logger, " 0x", out_buf );
        Delay_100ms();
    }
    log_printf( &logger, "\r\n" );

   log_printf( &logger, "Write MikroE data." );
   excelonlp_send_command( &excelonlp, EXCELONLP_OPCODE_SET_WRITE_ENABLE_LATCH );
   for ( cnt = 0; cnt < 6; cnt++ )
   {
        excelonlp_send_command( &excelonlp, EXCELONLP_OPCODE_SET_WRITE_ENABLE_LATCH );
        excelonlp_write_memory_data( &excelonlp, EXCELONLP_OPCODE_WRITE_MEMORY_DATA, memory_address++, send_buffer[ cnt ] );
        Delay_100ms();
   }
   memory_address = 0x00000055;
   log_printf( &logger, "Read memory data: " );
   for ( cnt = 0; cnt < 6; cnt++ )
   {
       memory_data[ 0 ] = excelonlp_read_memory_data( &excelonlp, EXCELONLP_OPCODE_READ_MEMORY_DATA, memory_address++ );
       log_printf( &logger, " %d", memory_address );
       Delay_100ms();
   }
   Delay_ms ( 1000 );
   Delay_ms ( 1000 );
   Delay_ms ( 1000 );
   Delay_ms ( 1000 );
   Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.ExcelonLP

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
