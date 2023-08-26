/*
  Created by Mathieu Lory <mathieu@internetcollaboratif.info>.
  - t6 website: https://www.internetcollaboratif.info
  - t6 iot: https://api.internetcollaboratif.info
  - Api doc: https://api.internetcollaboratif.info/docs/
*/
#include "t6iot_audio.h"
#define I2S_DOUT     25
#define I2S_LRC      26
#define I2S_BCLK     27
int _volume        = 5;

#if defined(ESP8266)
	t6iot_Audio::t6iot_Audio() {

	}
	void t6iot_Audio::audio_loop() {

	}
	bool t6iot_Audio::audioListenTo(const char* url) {
//		Serial.print("t6 > audioListenTo");
//		Serial.println(url);
		return 0;
	}
	bool t6iot_Audio::audioSetVol(int volume) {
//		Serial.print("t6 > audioSetVol");
//		Serial.println(url);
		_volume = volume;
		return 0;
	}
	int t6iot_Audio::audioGetVol() {
		return _volume;
	}
#elif ESP32
	#include "Audio.h"
	Audio audio;
	t6iot_Audio::t6iot_Audio() {
		Serial.println("t6 > t6iot_Audio Constructor");
	}
	void t6iot_Audio::audio_loop() {
		audio.loop();
	}
	bool t6iot_Audio::audioListenTo(const char* url) {
		audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
		audio.setVolume(_volume);
		audio.connecttohost(url);
		return 1;
	}
	bool t6iot_Audio::audioSetVol(int volume) {
		audio.setVolume(volume);
		_volume = volume;
		return 1;
	}
	int t6iot_Audio::audioGetVol() {
		return _volume;
	}
#endif
