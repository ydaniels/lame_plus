**A simple c++ library for your project encode pcm to mp3**


**Installation (nix & co.)**

1. apt install lame

**Usage in 2 lines**

`MP3Encoder mp3_encoder{};`

`mp3_encoder.encode((short *)pcm_buffer, sample_size, mp3_buffer);`