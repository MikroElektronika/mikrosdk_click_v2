
---
# IR SENSE Click

> [IR SENSE Click](https://www.mikroe.com/?pid_product=MIKROE-2677) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2677&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application return the temperature of object.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.IrSense

### Example Key Functions

- `irsense_cfg_setup` Config Object Initialization function. 
```c
void irsense_cfg_setup ( irsense_cfg_t *cfg );
``` 
 
- `irsense_init` Initialization function. 
```c
err_t irsense_init ( irsense_t *ctx, irsense_cfg_t *cfg );
```

- `irsense_write_byte` Function write the 8-bit data to the target 8-bit register address of AK9750 sensor on IR Sense Click board. 
```c
void irsense_write_byte ( irsense_t *ctx, uint8_t reg_address, uint8_t write_data );
```
 
- `irsense_read_byte` Function read the 8-bit data from the target 8-bit register address of AK9750 sensor on IR Sense Click board. 
```c
uint8_t irsense_read_byte ( irsense_t *ctx, uint8_t reg_address );
```

- `irsense_read_data` Function read the 16-bit data from the two target 8-bit register address of AK9750 sensor on IR Sense Click board. 
```c
uint16_t irsense_read_data ( irsense_t *ctx, uint8_t reg_address_low );
```

### Application Init

> Initialization driver enables - I2C, enable sensor, set soft reset, set Continuous Mode 0,  also write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    irsense_cfg_t cfg;

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

    irsense_cfg_setup( &cfg );
    IRSENSE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    irsense_init( &irsense, &cfg );

    log_printf( &logger, "     I2C Driver Init       \r\n"  );
    Delay_ms ( 100 );
    log_printf( &logger, "---------------------------\r\n"  );

    irsense_power_on( &irsense );
    log_printf( &logger, "         Power On          \r\n"  );
    Delay_ms ( 1000 );
    log_printf( &logger, "---------------------------\r\n"  );

    irsense_soft_reset( &irsense );
    log_printf( &logger, "        Soft Reset         \r\n"  );
    Delay_ms ( 1000 );
    log_printf( &logger, "---------------------------\r\n"  );

    irsense_set_mode( &irsense, IRSENSE_ECNTL1_MODE_CONTINUOUS_0 );
    irsense_set_cutoff_frequency( &irsense, IRSENSE_ECNTL1_CUTOFF_FREQUENCY_0_6_Hz );
    log_printf( &logger, "  Set Continuous Mode 0    \r\n"  );
    log_printf( &logger, "Set cutoff frequency 0.6 Hz\r\n"  );
    Delay_ms ( 100 );
    log_printf( &logger, "---------------------------\r\n"  );

    irsense_set_interrupts_reg( &irsense, IRSENSE_EINTEN_IR13_HIGH_INT_DISABLE,
                                         IRSENSE_EINTEN_IR13_LOW_INT_DISABLE,
                                         IRSENSE_EINTEN_IR24_HIGH_INT_DISABLE,
                                         IRSENSE_EINTEN_IR24_LOW_INT_DISABLE,
                                         IRSENSE_EINTEN_DRI_INT_ENABLE );

    log_printf( &logger, " Interrupt Source Setting  \r\n"  );
    log_printf( &logger, "Enable Data Ready Interrupt\r\n"  );
    Delay_ms ( 100 );
    log_printf( &logger, "---------------------------\r\n"  );
    log_printf( &logger, "      IR Sense  Click      \r\n"  );
    log_printf( &logger, "---------------------------\r\n"  );
    log_printf( &logger, "      Observable Area      \r\n"  );
    deg_cel[ 0 ] = 32;
    deg_cel[ 1 ] = 176;
    deg_cel[ 2 ] = 67;
    deg_cel[ 3 ] = 0;
}
```

### Application Task

> This is an example which demonstrates the use of IR Sense Click board. Detects the temperature of objects and detects the motion in observable area of the AK9750 sensor. Results are being sent to the Usart Terminal where you can track their changes. All data logs write on usb uart changes for every 1 sec.

```c
void application_task ( void )
{
   if ( irsense_check_available( &irsense ) )
    {
        irsense_get_ir_sense( &irsense, &bottom_area, &left_area, &right_area, &top_area );

        log_printf( &logger, "- - - - - - - - -\r\n" );
        log_printf( &logger, " Bottom : %d \r\n", bottom_area );

        log_printf( &logger, " Left   : %d \r\n", left_area );

        log_printf( &logger, " Top    : %d \r\n", top_area );

        log_printf( &logger, " Right  : %d \r\n", right_area );
        log_printf( &logger, "- - - - - - - - -\r\n" );

        temperature = irsense_get_temperature( &irsense );
        log_printf( &logger, " Temperature: %f \r\n", temperature );
        log_printf( &logger, "---------------------------\r\n" );

        irsense_refresh( &irsense );
        Delay_ms ( 1000 );
    }
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
