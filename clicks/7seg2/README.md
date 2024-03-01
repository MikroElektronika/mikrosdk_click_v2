\mainpage Main Page

---
# 7-SEG 2 click

> 7-SEG 2 Click is a compact add-on board that represents an easy solution for adding a numeric or hexadecimal display to your application. This board features the LDT-M2804RI, a three-digit seven-segment display from Lumex. The display has a 0.28” height, red LED segments, gray faces, and white diffused segments. All three digits come with a following dot point that can be used as a decimal point in displaying the number values.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/7seg2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/7-seg-2-click)

---


#### Click library

- **Author**        : MikroE Team
- **Date**          : Sep 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the 7-SEG 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for 7-SEG 2 Click driver.

#### Standard key functions :

- `c7seg2_cfg_setup` Config Object Initialization function.
```c
void c7seg2_cfg_setup ( c7seg2_cfg_t *cfg );
```

- `c7seg2_init` Initialization function.
```c
err_t c7seg2_init ( c7seg2_t *ctx, c7seg2_cfg_t *cfg );
```

- `c7seg2_default_cfg` Click Default Configuration function.
```c
err_t c7seg2_default_cfg ( c7seg2_t *ctx );
```

#### Example key functions :

- `c7seg2_set_segments_current` This function is used to set the current value of the segment's leds.
```c
err_t c7seg2_set_segments_current ( c7seg2_t *ctx, float current_val );
```

- `c7seg2_write_segment` This function is used to write a number [0..9] to a selected segment [0..2] with or w/o a decimal pointer.
```c
err_t c7seg2_write_segment ( c7seg2_t *ctx, uint8_t segment, uint8_t number, uint8_t dpt );
```

- `c7seg2_write_number` This function is used to write a number [0..999] to a selected segment [0..2] with or w/o a decimal pointer.
```c
err_t c7seg2_write_number ( c7seg2_t *ctx, uint16_t number, uint8_t dpt );
```

## Example Description

> The example demonstrates the use of the 7-SEG 2 click board by displaying a counter number [0.00-9.99] which is incremented by 0.01 at a desired rate.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs default configuration, sets the device in output enabled mode and checks communication by reading device ID.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c7seg2_cfg_t c7seg2_pnp_cfg;  /**< Click config object. */

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
    c7seg2_cfg_setup( &c7seg2_pnp_cfg );
    C7SEG2_MAP_MIKROBUS( c7seg2_pnp_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == c7seg2_init( &c7seg2, &c7seg2_pnp_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    uint8_t device_id = 0;
    c7seg2_read_reg( &c7seg2, C7SEG2_REG_DEVICE_ID, &device_id );
    if ( C7SEG2_DEVICE_ID != device_id )
    {
        log_error( &logger, " Communication error." );
        for ( ; ; );
    }
    
    if ( C7SEG2_ERROR == c7seg2_default_cfg ( &c7seg2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Writes a counter number [0.00-9.99] to the display as frequently as possible. The displayed counter value is incremented by 0.01 at a rate defined with the C7SEG2_NUM_COUNTER_RATE macro.

```c
void application_task ( void )
{
    static uint16_t counter = 0;
    static uint16_t time = 0;
    
    c7seg2_write_number( &c7seg2, counter, C7SEG2_DP_AT_SEGMENT_2 );
    
    if ( ++time >= C7SEG2_NUM_COUNTER_RATE ) 
    {
        if ( ++counter > C7SEG2_MAX_NUMBER )
        {
            counter = 0;
        }
        time = 0;
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.7SEG2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
