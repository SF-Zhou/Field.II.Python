#include "../func.hpp"
#include "../para.hpp"


void reversed_method(float* signals, float* image, const Para& para) {
    const int offset = (para.element_count - para.line_count) / 2;
    const int min_delay = (para.z_start * 2 * para.ratio);
    const float empty_j = para.z_start / para.pixel_height;
    const float A = 1 / para.ratio / para.pixel_height / 2;
    const float B = sqr(para.pixel_width) * para.ratio / para.pixel_height / 2;

    ff (i, para.line_count) {
#ifndef MEASURE
        printf("# Current Line: %d\n", i);
#endif
        float *signal_line = signals + i * para.element_count * para.data_length;
        float *image_line = image + i * para.row_count;

        ff (k, para.element_count) {
            float *current_signal = signal_line + k * para.data_length + min_delay;
            const int C = sqr(i + offset - k);

            fff(d, min_delay + 1, para.data_length - 1) {
                if (* ++current_signal == 0) continue;

                const int j = A * d - B * C / d - empty_j;

                if (0 <= j && j < para.row_count) {
                    image_line[j] += *current_signal;
                }
            }
        }
    }
}