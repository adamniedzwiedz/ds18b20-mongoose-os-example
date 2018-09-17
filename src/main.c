#include "mgos.h"
#include "ds18b20_lib.h"

#define ONEWIRE_PIN 14

static struct mgos_ds18b20* ds18b20;

static void ds18b20_ready(void *arg) {
  float *temperature = arg;

  if (temperature == NULL) {
    LOG(LL_ERROR, ("Reading temperature has failed.\r\n"));
    return;
  }

  LOG(LL_INFO, ("Temperature: %f \r\n", *temperature));
}

static void measure_cb(void *arg) {
  
  if (!ds18b20_start_conversion(ds18b20, ds18b20_ready)) {
    LOG(LL_ERROR, ("Starting conversion has failed\r\n"));
  }

  (void) arg;
}

enum mgos_app_init_result mgos_app_init(void) {
  struct ds18b20_scratchpad scratchpad;

  ds18b20 = ds18b20_create(ONEWIRE_PIN);

  if (ds18b20 == NULL) {
    LOG(LL_ERROR, ("DS18B20 object has not been created.\r\n"));
    return MGOS_INIT_APP_INIT_FAILED;
  }

  if (!ds18b20_read_scratchpad(ds18b20, &scratchpad)) {
    LOG(LL_ERROR, ("Reading scratchpad has failed\r\n"));
    return MGOS_INIT_APP_INIT_FAILED;
  }

  LOG(LL_INFO, ("Temperature: %f\r\n", scratchpad.temperature));
  LOG(LL_INFO, ("Alarm high: %d\r\n", scratchpad.alarm_high));
  LOG(LL_INFO, ("Alarm low: %d\r\n", scratchpad.alarm_low));
  LOG(LL_INFO, ("Resolution: %d\r\n", scratchpad.resolution));

  scratchpad.resolution = DS18B20_12_BIT;

  if (!ds18b20_write_scratchpad(ds18b20, scratchpad)) {
    LOG(LL_ERROR, ("Writing scratchpad has failed\r\n"));
    return MGOS_INIT_APP_INIT_FAILED;
  }

  mgos_set_timer(3000, MGOS_TIMER_REPEAT, measure_cb, NULL);

  return MGOS_APP_INIT_SUCCESS;
}
