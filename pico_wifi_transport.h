// https://github.com/PICO-MAZING/micro_ros_raspberrypi_pico_sdk/
#ifndef MICRO_ROS_WIFI_PICOSDK
#define MICRO_ROS_WIFI_PICOSDK

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "lwip/pbuf.h"
#include "lwip/udp.h"

#include <uxr/client/profile/transport/custom/custom_transport.h>

bool pico_wifi_transport_open(struct uxrCustomTransport *transport);
bool pico_wifi_transport_close(struct uxrCustomTransport *transport);
size_t pico_wifi_transport_write(struct uxrCustomTransport *transport, const uint8_t *buf, size_t len, uint8_t *err);
size_t pico_wifi_transport_read(struct uxrCustomTransport *transport, uint8_t *buf, size_t len, int timeout, uint8_t *err);

struct micro_ros_agent_locator
{
    ip_addr_t address;
    int port;
};

static inline bool set_microros_wifi_transports(char *ssid, char *pass, char *agent_ip, uint agent_port)
{

    stdio_init_all();
    sleep_ms(2000);
    printf("\33[2K\r");
    if (cyw43_arch_init())
    {
        
        printf("cyw43_arch_init failed\n");
        return 1;
    } else {
        printf("cyw43_arch_init completed\n");
    }

    cyw43_arch_enable_sta_mode();

    sleep_ms(1000);
    printf("\33[2K\r");
    printf("Connecting to Wi-Fi...\n");
    printf("\33[2K\r");
    if (cyw43_arch_wifi_connect_timeout_ms(ssid, pass, CYW43_AUTH_WPA2_AES_PSK, 30000))
    {
        printf("failed to connect.\n");
        return 1;
    }
    else
    {
        printf("Connected.\n");
    }

    static struct micro_ros_agent_locator locator;
    ipaddr_aton(agent_ip, &locator.address);
    locator.port = agent_port;

    rmw_uros_set_custom_transport(
        false,
        (void *)&locator,
        pico_wifi_transport_open,
        pico_wifi_transport_close,
        pico_wifi_transport_write,
        pico_wifi_transport_read);

    return 0;
}

#ifdef __cplusplus
}
#endif


#endif // MICRO_ROS_WIFI_PICOSDK
