#include "sound.h"
#include "graphics/graphics.h"

void play_sound(const char *filepath, bool repeat) {
	do {
		waveOutSetVolume(0, 0xFFFFFF);
		PlaySound(TEXT(filepath), NULL, SND_FILENAME);
	} while (repeat);
}