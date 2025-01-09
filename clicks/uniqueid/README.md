
---
# UNIQUE ID Click

> [UNIQUE ID Click](https://www.mikroe.com/?pid_product=MIKROE-1819) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1819&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Aleksandra Cvjeticanin
- **Date**          : Feb 2022.
- **Type**          : One Wire type

# Software Support

## Example Description

> This example demonstrates the use of UNIQUE ID Click board by reading and displaying Family Code and Serial Number on the UART Terminal.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.UNIQUEID

### Example Key Functions

- `uniqueid_cfg_setup` Config Object Initialization function.
```c
void uniqueid_cfg_setup ( uniqueid_cfg_t *cfg );
```

- `uniqueid_init` Initialization function.
```c
err_t uniqueid_init ( uniqueid_t *ctx, uniqueid_cfg_t *cfg );
```

- `uniqueid_read_id` This function reads Family Code and Serial Number of device's ROM memory.
```c
err_t uniqueid_read_id ( uniqueid_t *ctx, uint8_t *family, uint8_t *serial_num ); 
```

### Application Init

> Initionalizes both logger config object and Click config object. 

```c
void application_init ( void )
{
	log_cfg_t log_cfg;  /**< Logger config object. */
    uniqueid_cfg_t uniqueid_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization
    uniqueid_cfg_setup( &uniqueid_cfg );
    UNIQUEID_MAP_MIKROBUS( uniqueid_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == uniqueid_init( &uniqueid, &uniqueid_cfg ) ) 
    {
        log_error( &logger, " Initialization error." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Demonstrates the usage of uniqueid_read_id function,
which stores the Family Code and Serial Number of the Click in 
family_code and serial_num variables. Both values will be displayed 
on the UART Terminal.

```c
void application_task ( void )
{
	uint8_t family_code;
    uint8_t serial_num[ 6 ];
    
    if ( UNIQUEID_OK == uniqueid_read_id( &uniqueid, &family_code, &serial_num[ 0 ] ) )
    {
        log_printf( &logger, "Family Code = 0x%.2X\r\n", ( uint16_t ) family_code ); 
        log_printf( &logger, "Serial Number = 0x%.2X%.2X%.2X%.2X%.2X%.2X\r\n", 
                    ( uint16_t ) serial_num[ 0 ], ( uint16_t ) serial_num[ 1 ], 
                    ( uint16_t ) serial_num[ 2 ], ( uint16_t ) serial_num[ 3 ], 
                    ( uint16_t ) serial_num[ 4 ], ( uint16_t ) serial_num[ 5 ] ); 
    }      
    
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
