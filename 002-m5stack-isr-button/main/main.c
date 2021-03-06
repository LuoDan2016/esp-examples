#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "stdio.h"

#include "sdkconfig.h"

#define ESP_INTR_FLAG_DEFAULT 0

static const char* TAG = "gpio_button";
static xQueueHandle gpio_evt_queue = NULL;

// The pin ISR handlers no longer need to be declared with IRAM_ATTR, unless
// you pass the ESP_INTR_FLAG_IRAM flag when allocating the ISR in
// gpio_install_isr_service().

static void IRAM_ATTR gpio_isr_handler(void *arg)
{
    uint32_t gpio_num = (uint32_t) arg;
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
}

static void gpio_task(void* arg)
{
    uint32_t pin;
    while(1) {
        if (xQueueReceive(gpio_evt_queue, &pin, portMAX_DELAY)) {
            switch (pin) {
                case GPIO_NUM_39:
                    ESP_LOGD(TAG, "Button A value: %d", gpio_get_level(pin));
                    break;
                case GPIO_NUM_38:
                    ESP_LOGD(TAG, "Button B value: %d", gpio_get_level(pin));
                    break;
                case GPIO_NUM_37:
                    ESP_LOGD(TAG, "Button C value: %d", gpio_get_level(pin));
                    break;
                default:
                    ESP_LOGD(TAG, "This should not happen...");
                    break;
                }
        }
    }
}

/* ESP32 application entry point */
void app_main()
{
    ESP_LOGD(TAG, "Starting...");

    gpio_config_t button_config;
    button_config.pin_bit_mask = GPIO_SEL_37 | GPIO_SEL_38 | GPIO_SEL_39;
    button_config.mode         = GPIO_MODE_INPUT;
    button_config.pull_up_en   = GPIO_PULLUP_DISABLE;
    button_config.pull_down_en = GPIO_PULLDOWN_ENABLE;
    button_config.intr_type    = GPIO_INTR_ANYEDGE;
    gpio_config(&button_config);

    /* Queue which receives events from ISR */
    gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));

    /* Task which receives events from queue */
    xTaskCreate(gpio_task, "GPIO task", 2048, NULL, 10, NULL);

    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
    gpio_isr_handler_add(GPIO_NUM_39, gpio_isr_handler, (void*) GPIO_NUM_39);
    gpio_isr_handler_add(GPIO_NUM_38, gpio_isr_handler, (void*) GPIO_NUM_38);
    gpio_isr_handler_add(GPIO_NUM_37, gpio_isr_handler, (void*) GPIO_NUM_37);
}
