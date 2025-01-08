
---
# G2C 3G Click

> [G2C 3G Click](https://www.mikroe.com/?pid_product=MIKROE-3888) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3888&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : May 2023.
- **Type**          : UART type

# Software Support

## Example Description

> This example shows the device capability of connecting to the cloud and updating the sensor data on the cloud and receiving data from actuators.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.G2C3G

### Example Key Functions

- `g2c3g_cfg_setup` Config Object Initialization function.
```c
void g2c3g_cfg_setup ( g2c3g_cfg_t *cfg );
```

- `g2c3g_init` Initialization function.
```c
err_t g2c3g_init ( g2c3g_t *ctx, g2c3g_cfg_t *cfg );
```

- `g2c3g_reset_device` This function resets the device by toggling the RST pin.
```c
void g2c3g_reset_device ( g2c3g_t *ctx );
```

- `g2c3g_set_net_creds` This function sets the APN, username, and password for entered sim card.
```c
void g2c3g_set_net_creds ( g2c3g_t *ctx, uint8_t *sim_apn, uint8_t *username, uint8_t *password );
```

- `g2c3g_set_broker_creds` This function sets the broker credentials (device key and password).
```c
void g2c3g_set_broker_creds ( g2c3g_t *ctx, uint8_t *dev_key, uint8_t *password );
```

### Application Init

> Initializes the driver, restarts the device, and after that tests the communication by sending "AT" command.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    g2c3g_cfg_t g2c3g_cfg;  /**< Click config object. */

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
    g2c3g_cfg_setup( &g2c3g_cfg );
    G2C3G_MAP_MIKROBUS( g2c3g_cfg, MIKROBUS_2 );
    if ( UART_ERROR == g2c3g_init( &g2c3g, &g2c3g_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    // Clear RX buffer
    g2c3g_process( );   
    g2c3g_clear_app_buf( );
    Delay_ms ( 100 );
    
    // Reset device
    g2c3g_reset_device ( &g2c3g );
    error_flag = g2c3g_rsp_check( G2C3G_RSP_DEVICE_READY );
    g2c3g_error_check( error_flag );
    
    // Check communication
    g2c3g_send_cmd( &g2c3g, G2C3G_CMD_AT );
    error_flag = g2c3g_rsp_check( G2C3G_RSP_OK );
    g2c3g_error_check( error_flag );
    
    log_info( &logger, " Application Task " );
    example_state = G2C3G_CONNECT_TO_NETWORK;
}
```

### Application Task

> Application task is split in few stages:
 - G2C3G_CONNECT_TO_NETWORK: 
   > Sends commands to configure device to connect to the specified network.
 - G2C3G_CONNECT_TO_CLOUD: 
   > Sends commands to configure device to connect to the specified device on the cloud.
 - G2C3G_EXAMPLE:
   > This function executes example which updates sensor data on the cloud and displays
   > all data received from the module (ex. the actuator switch state change received from the cloud).

```c
void application_task ( void )
{
    switch ( example_state )
    {
        case G2C3G_CONNECT_TO_NETWORK:
        {
            if ( G2C3G_OK == g2c3g_connect_to_network( ) )
            {
                example_state = G2C3G_CONNECT_TO_CLOUD;
            }
            break;
        }
        case G2C3G_CONNECT_TO_CLOUD:
        {
            if ( G2C3G_OK == g2c3g_connect_to_cloud( ) )
            {
                example_state = G2C3G_EXAMPLE;
            }
            break;
        }
        case G2C3G_EXAMPLE:
        {
            g2c3g_example( );
            break;
        }
        default:
        {
            log_error( &logger, " Example state." );
            break;
        }
    }
}
```

### Note

> In order for the example to work, user needs to set the SIM card and the cloud device parameters.
Enter valid values for the following macros: 
SIM_APN, SIM_USERNAME, SIM_PASSWORD, DEVICE_KEY, DEVICE_PASSWORD, DEVICE_SENSOR_REF.
> > Example: 
> > - SIM_APN              "internet"
> > - SIM_USERNAME         "internet"
> > - SIM_PASSWORD         "internet"
> > - DEVICE_KEY           "xxxxxxxxxxxxxxxx"
> > - DEVICE_PASSWORD      "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"
> > - DEVICE_SENSOR_REF    "TEMP_SEN_R"
> DEVICE_KEY and DEVICE_PASSWORD strings should match the device credentials which were generated during the Click Cloud device creation step.
DEVICE_SENSOR_REF is expected to be a reference to a temperature sensor with a data range from -20 to +80 degrees Celsius.
For more information about the registration on the Click Cloud and creating the device refer to the following [user guide](https://download.mikroe.com/documents/click-cloud/guide-to-click-cloud.pdf).

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
