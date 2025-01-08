
---
# LLC I2C Click

> [LLC I2C Click](https://www.mikroe.com/?pid_product=MIKROE-3276) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3276&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : maj 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This Click can be utilized as the level converter for logic signals. The topology of this 
> logic level conversion (LLC) circuit is perfectly suited for the bi-directional I2C communication.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LlcI2c

### Example Key Functions

- `llci2c_cfg_setup` Config Object Initialization function. 
```c
void llci2c_cfg_setup ( llci2c_cfg_t *cfg );
``` 
 
- `llci2c_init` Initialization function. 
```c
err_t llci2c_init ( llci2c_t *ctx, llci2c_cfg_t *cfg );
```

- `llci2c_generic_write` This function writes data to the desired register. 
```c
void llci2c_generic_write ( llci2c_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
```
 
- `llci2c_generic_read` This function reads data from the desired register. 
```c
void llci2c_generic_read ( llci2c_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
```

### Application Init

> Initialization driver init

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    llci2c_cfg_t cfg;

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

    llci2c_cfg_setup( &cfg );
    LLCI2C_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    llci2c_init( &llci2c, &cfg );
}
```

### Application Task

> Reads the temperature from the Thermo 7 Click board and logs data to UART.

```c
void application_task ( void )
{
    // Thermo 7 measurement Temperature
    uint8_t write_reg = 0x00;
    uint8_t read_reg[ 2 ] = { 0 };
    
    float temp_msb;
    uint8_t temp_lsb;

    llci2c_generic_read ( &llci2c, write_reg, read_reg, 2 );
    
    temp_msb = read_reg[ 0 ];
    temp_lsb = read_reg[ 1 ] & 0xF0;

    if ( temp_lsb & 0x80 ) temp_msb += 0.50;
    if ( temp_lsb & 0x40 ) temp_msb += 0.25;
    if ( temp_lsb & 0x20 ) temp_msb += 0.125;
    if ( temp_lsb & 0x10 ) temp_msb += 0.0625;

    log_info( &logger, " Ambient temperature : %2.f C", temp_msb );
    Delay_ms ( 1000 );
}
```

### Note

> <pre>
> Connection between Thermo 7 and I2C-LLC is made through I2C interface.
> You can connect a Thermo 7 Click and I2C-LLC Click with the wires to make connection between Click boards.
> We use the Thermo 7 Click to demonstrate the functions of the I2C-LLC Click.
> </pre> 

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
