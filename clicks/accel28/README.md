\mainpage Main Page

---
# Accel 28 Click

> Accel 28 Click is a compact add-on board that contains an acceleration sensor. This board features the LIS2HH12TR, an ultra-low-power high-performance three-axis accelerometer from STMicroelectronics. It allows selectable full-scale acceleration measurements in ranges of ±2g, ±4g, and ±8g in three axes with a configurable host interface that supports both SPI and I2C serial communication. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/accel28_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/accel-28-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : May 2023.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Accel 28 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Accel 28 Click driver.

#### Standard key functions :

- `accel28_cfg_setup` Config Object Initialization function.
```c
void accel28_cfg_setup ( accel28_cfg_t *cfg );
```

- `accel28_init` Initialization function.
```c
err_t accel28_init ( accel28_t *ctx, accel28_cfg_t *cfg );
```

- `accel28_default_cfg` Click Default Configuration function.
```c
err_t accel28_default_cfg ( accel28_t *ctx );
```

#### Example key functions :

- `accel28_get_data` Accel 28 data reading function.
```c
err_t accel28_get_data ( accel28_t *ctx, accel28_data_t *data_out );
```

- `accel28_write_reg` Accel 28 register data writing function.
```c
err_t accel28_write_reg ( accel28_t *ctx, uint8_t reg, uint8_t data_in );
```

- `accel28_sw_reset` Accel 28 SW reset function.
```c
err_t accel28_sw_reset ( accel28_t *ctx );
```

## Example Description

> This example demonstrates the use of Accel 28 Click board by reading and
  displaying the accelerometer data (X, Y, and Z axis).

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel28_cfg_t accel28_cfg;  /**< Click config object. */

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
    accel28_cfg_setup( &accel28_cfg );
    ACCEL28_MAP_MIKROBUS( accel28_cfg, MIKROBUS_1 );
    err_t init_flag = accel28_init( &accel28, &accel28_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    uint8_t id_data = 0;
    
    accel28_generic_read( &accel28, ACCEL28_REG_WHO_AM_I, &id_data, 1 );
    if ( ACCEL28_WHO_AM_I_VALUE != id_data )
    {
        log_error( &logger, " Communication error." );
        for ( ; ; );
    }
    
    if ( ACCEL28_ERROR == accel28_default_cfg ( &accel28 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
        
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads and displays on the USB UART the accelerometer data (X, Y, and Z axis)
  when it is available. 

```c
void application_task ( void )
{
    err_t error_flag = ACCEL28_OK;
    if ( ACCEL28_PIN_STATE_HIGH == accel28_get_int_state( &accel28 ) )
    {
        uint8_t tmp_data;
        error_flag = accel28_read_reg( &accel28, ACCEL28_REG_STATUS, &tmp_data );
         if ( ( tmp_data & ACCEL28_STATUS_ZYX_DATA_AVL ) && ( ACCEL28_OK == error_flag ) )
        {
            error_flag = accel28_get_data( &accel28, &accel_data );
            if ( ACCEL28_OK == error_flag )
            {
                log_printf( &logger, " X-axis %.2f mg\r\n", accel_data.x_data );
                log_printf( &logger, " Y-axis %.2f mg\r\n", accel_data.y_data );
                log_printf( &logger, " Z-axis %.2f mg\r\n", accel_data.z_data );
                log_printf( &logger, " = = = = = = = = = = = = = =\r\n" );
            }
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel28

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
