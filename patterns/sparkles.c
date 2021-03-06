
#include "sparkles.h"

inline void init_sparkle(sparkle_t *sparkle)
{
    // reset time
    sparkle->t = 0;

    // select a random LED
    sparkle->led = 0x0001;  //select_random_led();

    // set a random fade-in time
    sparkle->t_fade_in = 15; // random256();

    // set fade-out time after fade-in time
    sparkle->t_fade_out = sparkle->t_fade_in + 256;

    // set end time to when fade-out is complete
    sparkle->t_fade_out = sparkle->t_fade_out + 256;
}

inline uint8_t sparkle_color_function(sparkle_t *sparkle)
{
    if (sparkle->t > sparkle->t_fade_in)
    {
        // fade in
        return sparkle->t - sparkle->t_fade_in;
    }
    if (sparkle->t > sparkle->t_fade_out)
    {
        // fade out
        return 256 - (sparkle->t - sparkle->t_fade_out); 
    }
    return 0;
}

inline void sparkle_update(sparkle_t *sparkle)
{
    uint8_t color = sparkle_color_function(sparkle);

    set_led(sparkle->led, color, color, color);
}

inline bool is_sparkle_finished(sparkle_t *sparkle)
{
    return (sparkle->t >= sparkle->t_end);
}
