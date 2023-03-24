\mainpage Main Page

---
# RTK Base click

> RTK Base Click is a compact add-on board used to improve the positional accuracy of the compatible RTK Rover board. This board features Quectel’s LG69TASMD, a dual-band multi-constellation GNSS module featuring a high-performance and high-reliability positioning engine. This module carries an RTK base station function by calculating and transmitting differential correction data via radio to allow the roving GPS to correct its position. It features the fifth generation of STMicroelectronics® positioning receiver platform with 80 tracking and four fast acquisition channels, supports up to 4 concurrent global constellations (GPS, QZSS, Galileo, and BDS) alongside RTCM 3.x protocol and commonly used UART interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rtkbase_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/rtk-base-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2022.
- **Type**          : UART type


# Software Support

We provide a library for the RTK Base Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for RTK Base Click driver.

#### Standard key functions :

- `rtkbase_cfg_setup` Config Object Initialization function.
```c
void rtkbase_cfg_setup ( rtkbase_cfg_t *cfg );
```

- `rtkbase_init` Initialization function.
```c
err_t rtkbase_init ( rtkbase_t *ctx, rtkbase_cfg_t *cfg );
```

#### Example key functions :

- `rtkbase_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t rtkbase_generic_read ( rtkbase_t *ctx, char *data_out, uint16_t len );
```

- `rtkbase_rx_bytes_available` This function returns the number of bytes available in the RX ring buffer.
```c
err_t rtkbase_rx_bytes_available ( rtkbase_t *ctx );
```

- `rtkbase_calculate_crc24` This function calculates and returns the CRC 24-bit of RTCM3 packet input. The CRC across the whole packet should sum to zero (remainder).
```c
uint32_t rtkbase_calculate_crc24( uint8_t *data_buf, uint16_t data_len );
```

## Example Description

> This example demonstrates the use of RTK Base click by reading and displaying the RTCM3 messages.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtkbase_cfg_t rtkbase_cfg;  /**< Click config object. */

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
    rtkbase_cfg_setup( &rtkbase_cfg );
    RTKBASE_MAP_MIKROBUS( rtkbase_cfg, MIKROBUS_1 );
    if ( UART_ERROR == rtkbase_init( &rtkbase, &rtkbase_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads and parses the RTCM3 messages received from the module, and displays them on the USB UART.

```c
void application_task ( void )
{
    rtkbase_process_rtcm3 ( &rtkbase );
    rtkbase_clear_app_buf( );
}
```

## Note

> The click board comes with the default baud rate of 460800, but the baud rate is set to 115200
in the example due to code portability and speed limitations of some MCUs. So in order to run
the example you will need to adjust the baud rate using Quectel QGNSS evaluation software.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.RTKBase

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
