#include "lightbulb.h"
#include "joylink_extern.h"

static void joylink_AmbientLight(void)
{
    lightbulb_set_hue(300);
}

void lightbulb_Control(user_dev_status_t user_dev)
{
    lightbulb_set_brightness(78);
    lightbulb_set_saturation(100);
    if (user_dev.Power == 1) {
        lightbulb_set_on(true);
        if (user_dev.AmbientLight == 1) {
            joylink_AmbientLight();
        } else if (user_dev.AmbientLight == 0) {
            lightbulb_set_saturation(0);
        }
    } else if (user_dev.Power == 0) {
        lightbulb_set_on(false);
        lightbulb_set_brightness(0);
    }
}
