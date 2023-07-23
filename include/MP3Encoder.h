#ifndef LAME_MP3ENCODER_H
#define LAME_MP3ENCODER_H

#include "include/lame/lame.h"


class MP3Encoder {
private:
    lame_t mLame;
    int initialised = 0;

public:
    explicit MP3Encoder(int sample_rate = 44100, int channels = 2, int bit_rate = 128, int quality = 7);

    ~MP3Encoder();

    int flush(unsigned char *mp3_buffer);

    int encode(short int pcm_buffer[], int pcm_size, unsigned char *mp3_buffer);

    bool set_channels(int channels);

    bool set_bitrate(int bitrate);

    bool set_sample_rate(int sample_rate);

    bool set_quality(int quality);
};


#endif //LAME_MP3ENCODER_H
