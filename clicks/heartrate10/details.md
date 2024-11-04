
---
# Heart Rate 10 Click

Heart Rate 10 Click is a compact add-on board suitable for heart rate monitoring applications. This board features the MAX86916, an integrated optical sensor with applications in bio-sensing, proximity, and color from Maxim Integrated.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/heart_rate_10_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/heart-rate-10-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : May 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the HeartRate10 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for HeartRate10 Click driver.

#### Standard key functions :

- `heartrate10_cfg_setup` Config Object Initialization function.
```c
void heartrate10_cfg_setup ( heartrate10_cfg_t *cfg );
```

- `heartrate10_init` Initialization function.
```c
HEARTRATE10_RETVAL heartrate10_init ( heartrate10_t *ctx, heartrate10_cfg_t *cfg );
```

- `heartrate10_default_cfg` Click Default Configuration function.
```c
void heartrate10_default_cfg ( heartrate10_t *ctx );
```

#### Example key functions :

- `heartrate10_generic_write` Writing function.
```c
err_t heartrate10_generic_write ( heartrate10_t *ctx, uint8_t reg, uint8_t tx_data )
```

- `heartrate10_reset` Reset device.
```c
void heartrate10_reset ( heartrate10_t *ctx )
```

- `heartrate10_read_complete_fifo_data` Read all led samples.
```c
err_t heartrate10_read_complete_fifo_data ( heartrate10_t *ctx, uint32_t *led1, uint32_t *led2, uint32_t *led3, uint32_t *led4 );
```

## Example Description

> This example showcases ability for device to read Heart Rate with 4 different diodes.
There is IR, Red, Green and Blue. You can control every one of them individualy, and 
change theirs sequence in FIFO register. All leds data is read from FIFO register, 
it's 19bit data for every led.

**The demo application is composed of two sections :**

### Application Init

> Initialization of host communication periphrials and interrupt pin. Configures default
configuration to device where device is reset, checks Part ID and enables all 4 leds 
and sets sequence as IR-Red-Green-Blue. Sets their power to maximum, and enables 
interrupt on new data ready.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    heartrate10_cfg_t heartrate10_cfg;  /**< Click config object. */

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

    // Click initialization.
    heartrate10_cfg_setup( &heartrate10_cfg );
    HEARTRATE10_MAP_MIKROBUS( heartrate10_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == heartrate10_init( &heartrate10, &heartrate10_cfg ) ) 
    {
        log_error( &logger, " Initializtion." );
        log_info( &logger, " Please, run example again... " );

        for ( ; ; );
    }
    
    if ( HEARTRATE10_ERROR == heartrate10_default_cfg ( &heartrate10 ) ) 
    {
        log_error( &logger, " Configuration." );
        log_info( &logger, " Please, run example again... " );

        for ( ; ; );
    }


```

### Application Task

> Reads FIFO data for all 4 didoes and logs them with separation character ','.

```c

void application_task ( void ) 
{   
    uint8_t rd_dat = 0;
    heartrate10_generic_read( &heartrate10, HEARTRATE10_REG_INT_STATUS, &rd_dat );
    if ( ( rd_dat & 0x40 ) )
    {        
        uint32_t ir, red, green, blue = 0;
        heartrate10_read_complete_fifo_data( &heartrate10, &ir, &red, &green, &blue );
        log_printf( &logger, "%lu,%lu,%lu,%lu\r\n", ir, red, green, blue );
    }
    Delay_ms ( 3 );
}

```

## Note

> For testing this example application SerialPlot was used. 
There you can see heart rate graphicly shown.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HeartRate10

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
