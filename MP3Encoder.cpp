
#include "include/MP3Encoder.h"

#include "include/logger.h"

#define LOG_TAG "MP3Encoder"

MP3Encoder::MP3Encoder(int sample_rate, int channels, int bit_rate, int quality) {
    mLame = lame_init();
    int ret = 0;
    if (mLame) {


        lame_set_in_samplerate(mLame, sample_rate);
        lame_set_num_channels(mLame, channels);
        lame_set_quality(mLame, quality);
        lame_set_brate(mLame, bit_rate);
        lame_set_bWriteVbrTag(mLame, 0);


        if (channels == 1) {
            lame_set_mode(mLame, MONO);
        } else {
            lame_set_mode(mLame, STEREO);
        }
        ret = lame_init_params(mLame);
        if (ret >= 0) {
            initialised = 1;
        } else {

            initialised = -1;
        }

    }
}

MP3Encoder::~MP3Encoder() {
    lame_close(mLame);

}

int MP3Encoder::flush(unsigned char *mp3_buffer) {

    int blockSize = 8 * 1024;
    int output_byte = 0;
    if (initialised != 1) {
        LOGE( " Cannot initialize decoder - %s ", __FUNCTION__ );
        return 0;
    }

    if (mp3_buffer != nullptr) {

        output_byte = lame_encode_flush(mLame, mp3_buffer, blockSize);
        initialised = 2;
    }

    return output_byte;
}

int MP3Encoder::encode(short int *pcm_buffer, int pcm_size, unsigned char *mp3_buffer) {
    int channels;
    int sample_count = 0;
    int output_size = 0;
    int output_byte = 0;
    if (pcm_size % 2 != 0) {
        LOGE(" :%s: Input pcm_size must be 16-bit PCM data ", __FUNCTION__);
        return 0;
    }
    if (initialised != 1) {
        LOGE(" :%s: Decoder not initialized ", __FUNCTION__);
        return 0;
    }
    pcm_size /= 2;
    channels = lame_get_num_channels(mLame);


    sample_count = pcm_size / channels;
    if (pcm_size % channels != 0) {
        LOGE(" :%s: The input data must be interleaved 16-bit PCM ", __FUNCTION__);
        return 0;
    }
    output_size = sample_count + (sample_count / 4) + 7200;

    if (mp3_buffer != nullptr) {

        if (channels > 1) {
            output_byte = lame_encode_buffer_interleaved(
                    mLame,
                    pcm_buffer, sample_count,
                    mp3_buffer, output_size
            );

        } else {
            output_byte = lame_encode_buffer(
                    mLame,
                    pcm_buffer, pcm_buffer, sample_count,
                    mp3_buffer, output_size
            );
        }

        if (output_byte <= 0) {
        }
    }
    return output_byte;
}

bool MP3Encoder::set_channels(int channels) {
    if (lame_set_num_channels(mLame, channels) < 0) {
        return false;
    }
    return true;
}


bool MP3Encoder::set_bitrate(int bitrate) {
    if (lame_set_brate(mLame, bitrate) < 0) {
        return false;
    }
    return true;
}

bool MP3Encoder::set_sample_rate(int sample_rate) {
    if (lame_set_in_samplerate(mLame, sample_rate) < 0) {
        return false;
    }
    return true;
}

bool MP3Encoder::set_quality(int quality) {
    if (lame_set_quality(mLame, quality) < 0) {
        return false;
    }
    return true;
}

