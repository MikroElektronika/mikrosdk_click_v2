
---
# Temp-Log 5 Click

> [Temp-Log 5 Click](https://www.mikroe.com/?pid_product=MIKROE-3442) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3442&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> Measures and stores temperatures values at least 10 times in second and logs it on terminal.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TempLog5

### Example Key Functions

- `templog5_cfg_setup` Config Object Initialization function. 
```c
void templog5_cfg_setup ( templog5_cfg_t *cfg );
``` 
 
- `templog5_init` Initialization function. 
```c
err_t templog5_init ( templog5_t *ctx, templog5_cfg_t *cfg );
```

- `templog5_default_cfg` Click Default Configuration function. 
```c
void templog5_default_cfg ( templog5_t *ctx );
```

- `templog5_write_eeprom` This function write data to the EEPROM address. 
```c
void templog5_write_eeprom ( templog5_t *ctx, uint8_t start_addr, uint8_t *data_in, uint8_t n_byte );
```

- `templog5_read_eeprom` This function read data to the EEPROM address. 
```c
void templog5_read_eeprom ( templog5_t *ctx, uint8_t start_addr, uint8_t *data_out, uint8_t n_byte );
```

- `templog5_read_data` This function read from the TS register. 
```c
uint16_t templog5_read_data ( templog5_t *ctx, uint8_t reg );
```

### Application Init

> Initializes driver init, tests comunication and EEPROM read/write and sets default configuration parameters.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    templog5_cfg_t cfg;
    uint16_t tmp;
    uint8_t ee_test_write[1];
    uint8_t ee_test_read[1];

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
    log_info( &logger, "Application Init" );

    //  Click initialization.

    templog5_cfg_setup( &cfg );
    TEMPLOG5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    templog5_init( &templog5, &cfg );

    tmp = templog5_read_data( &templog5, TEMPLOG5_REG_MANUFACTURER_ID );

    if ( tmp == TEMPLOG5_MANUFACTURER_ID )
    {
        log_info( &logger, "Comunication OK!!!" );
    }
    else
    {
        log_info( &logger, "Comunication ERROR!!!" );
        while( 1 );
    }
   
    ee_test_write[ 0 ] = 0xAA;
    templog5_write_eeprom( &templog5, 0x10, &ee_test_write[ 0 ], 1);
    Delay_ms ( 200 );
    
    templog5_read_eeprom( &templog5, 0x10, &ee_test_read[ 0 ], 1);
 
    log_info( &logger," EEPROM TEST READ:  %u\r\n", ee_test_read[ 0 ] ); 

    templog5_default_cfg ( &templog5 );
}
```

### Application Task

> Reads Temperature data and logs data to the terminal every 1 sec.

```c
void application_task ( void )
{
    float temperature;

    temperature = templog5_get_temperature( &templog5 );
    log_info( &logger,"Temperature:  %.2f\r\n", temperature );
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
