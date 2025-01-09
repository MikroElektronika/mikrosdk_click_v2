
---
# EERAM 5V Click

> [EERAM 5V Click](https://www.mikroe.com/?pid_product=MIKROE-2729) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2729&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jun 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example show using EERAM Click to store the data to the SRAM ( static RAM ) memory.
The data is read and written by the I2C serial communication bus, and the memory cells 
are organized into 2048 bytes, each 8bit wide.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.EERAM5V

### Example Key Functions

- `eeram5v_cfg_setup` Config Object Initialization function.
```c
void eeram5v_cfg_setup ( eeram5v_cfg_t *cfg );
```

- `eeram5v_init` Initialization function.
```c
err_t eeram5v_init ( eeram5v_t *ctx, eeram5v_cfg_t *cfg );
```

- `eeram5v_generic_read` This function reads a desired number of data bytes starting from the selected register by using I2C serial interface.
```c
void eeram5v_generic_read ( eeram5v_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );
```

- `eeram5v_status_write` Status register contains settings for write protection and auto-store function. Use this function to configure them.
```c
void eeram5v_status_write ( eeram5v_t *ctx, uint8_t command );
```

- `eeram5v_status_read` Returns the state of the status register.
```c
uint8_t eeram5v_status_read ( eeram5v_t *ctx );
```

### Application Init

> EERAM driver initialization.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;            /**< Logger config object. */
    eeram5v_cfg_t eeram5v_cfg;    /**< Click config object. */

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

    // Click initialization.
    
    eeram5v_cfg_setup( &eeram5v_cfg );
    EERAM5V_MAP_MIKROBUS( eeram5v_cfg, MIKROBUS_1 );
    err_t init_flag = eeram5v_init( &eeram5v, &eeram5v_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Writing data to Click memory and displaying the read data via UART. 

```c
void application_task ( void ) 
{
    log_info( &logger, "Writing MikroE to  SRAM memory, from address 0x0150:" );
    eeram5v_write( &eeram5v, 0x0150, &wr_data, 9 );
    log_info( &logger, "Reading 9 bytes of SRAM memory, from address 0x0150:" );
    eeram5v_read( &eeram5v, 0x0150, &rd_data, 9 );
    log_info( &logger, "Data read: %s", rd_data );
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
