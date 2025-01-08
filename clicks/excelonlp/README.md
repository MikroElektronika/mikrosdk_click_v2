
---
# Excelon LP Click

> [Excelon LP Click](https://www.mikroe.com/?pid_product=MIKROE-3104) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3104&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This application writes in RAM memory and read from RAM memory.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ExcelonLP

### Example Key Functions

- `excelonlp_cfg_setup` Config Object Initialization function. 
```c
void excelonlp_cfg_setup ( excelonlp_cfg_t *cfg );
``` 
 
- `excelonlp_init` Initialization function. 
```c
err_t excelonlp_init ( excelonlp_t *ctx, excelonlp_cfg_t *cfg );
```

- `excelonlp_send_command` Functions for send opcode command. 
```c
void excelonlp_send_command( excelonlp_t *ctx, uint8_t opcode );
```
 
- `excelonlp_read_data` Functions for read data. 
```c
void excelonlp_read_data (  excelonlp_t *ctx, uint8_t opcode, uint8_t *out_buf, uint8_t n_data );
```

- `excelonlp_write_memory_data` Functions for write data to memory. 
```c
void excelonlp_write_memory_data (  excelonlp_t *ctx, uint8_t opcode, uint32_t addr, uint8_t c_data );
```

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

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
