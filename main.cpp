#include <iostream>
#include <fstream>
#include "include/MP3Encoder.h"


int main() {

    int sample_size = 44100;
    std::fstream myfile;
    unsigned char mp3_buffer [sample_size];
    char  pcm_buffer[sample_size];




    myfile.read(pcm_buffer, sample_size);

    MP3Encoder mp3_encoder{};
    int encoded_size = mp3_encoder.encode((short *)pcm_buffer, sample_size, mp3_buffer);
    ///play mp3_buffer
    return 0;
}
