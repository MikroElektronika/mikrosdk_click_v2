
---
# Temp Probe click

> Temp Probe Click is a compact add-on board used as thermocouple temperature monitoring system. This board features the LTC2986, a high accuracy digital temperature measurement system used to directly digitize thermocouples with 0.1°C accuracy and 0.001°C resolution from Analog Devices.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/temp_probe_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/temp-probe-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the TempProbe Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for TempProbe Click driver.

#### Standard key functions :

- `tempprobe_cfg_setup` Config Object Initialization function.
```c
void tempprobe_cfg_setup ( tempprobe_cfg_t *cfg );
```

- `tempprobe_init` Initialization function.
```c
err_t tempprobe_init ( tempprobe_t *ctx, tempprobe_cfg_t *cfg );
```

- `tempprobe_default_cfg` Click Default Configuration function.
```c
err_t tempprobe_default_cfg ( tempprobe_t *ctx );
```

#### Example key functions :

- `tempprobe_write_word` Word Write function.
```c
err_t tempprobe_write_word ( tempprobe_t *ctx, uint16_t reg_addr, uint32_t data_in );
```

- `tempprobe_read_bytes` Byte Read function.
```c
err_t tempprobe_read_bytes( tempprobe_t *ctx, uint16_t reg_addr, uint8_t *data_out, uint8_t n_bytes );
```

- `tempprobe_read_temp` Temperature Read function.
```c
uint8_t tempprobe_read_temp ( tempprobe_t *ctx, uint16_t sel_channel, float *data_out );
```

## Example Description

> This is an example that demonstrates the use of the Temp Probe Click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes SPI interface and performs a  device configuration for properly working and  configures the desired channels.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    tempprobe_cfg_t tempprobe_cfg;  /**< Click config object. */

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

    tempprobe_cfg_setup( &tempprobe_cfg );
    TEMPPROBE_MAP_MIKROBUS( tempprobe_cfg, MIKROBUS_1 );
    err_t init_flag  = tempprobe_init( &tempprobe, &tempprobe_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_printf( &logger, " Temp Probe initialization \r\n" );
    tempprobe_reset( &tempprobe );
    Delay_ms( 300 );
    err_t cfg_flag = tempprobe_default_cfg( &tempprobe );
    if ( TEMPPROBE_ERROR == cfg_flag ) {
        log_printf( &logger, " Config Error \r\n" );
        
        for ( ; ; );
    }
    Delay_ms( 300 );

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Measure temperatures from all sensors and display the measurements on the serial port.

```c

void application_task ( void ) {
    uint8_t check_state;

    tempprobe_write_byte( &tempprobe, TEMPPROBE_REG_COMM_STATUS, TEMPPROBE_START_CONV  );
    check_state = tempprobe_check_busy( &tempprobe );
    while ( check_state != TEMPPROBE_NO_BUSY_STATE ) {
        check_state = tempprobe_check_busy( &tempprobe );
    }

    tempprobe_read_temp( &tempprobe, TEMPPROBE_REG_PN_JUNCTION_CONV_RES , &temperature_k );
    log_printf( &logger, " PN-Junction: %.4f C\r\n", temperature_k );
    tempprobe_read_temp( &tempprobe, TEMPPROBE_REG_THERMO_K_CONV_RES, &temperature_pn );
    log_printf( &logger, " Thermo K:    %.4f C\r\n", temperature_pn );

    log_printf( &logger, "------------------------\r\n" );
    Delay_ms( 1500 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.TempProbe

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
