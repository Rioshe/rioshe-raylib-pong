#include "sound.h"
#include "raylib.h"
#include "assets.h"

#include <stdlib.h>
#include <string.h>


static Sound s_hitSounds[HIT_SOUND_COUNT];
static Sound s_scoredSounds[SCORED_SOUND_COUNT];

void Sound_Init() {

    const char* hitSoundFormat = HIT_SOUNDS_PATH "hit%d.wav";
    for (size_t i = 0; i < HIT_SOUND_COUNT; i++)
    {
        const char* soundPath = TextFormat(hitSoundFormat, i);
        s_hitSounds[i] = LoadSound(soundPath);
    }
    
    const char* scoredSoundFormat = SCORED_SOUNDS_PATH "PowerUp%d.wav";
    for (size_t i = 0; i < SCORED_SOUND_COUNT; i++)
    {
        const char* soundPath = TextFormat(scoredSoundFormat, i);
        s_scoredSounds[i] = LoadSound(soundPath);
    }
}

void Sound_PlayHit() {
    int index = rand() % HIT_SOUND_COUNT;
    PlaySound(s_hitSounds[index]);
}

void Sound_PlayScored() {
    int index = rand() % SCORED_SOUND_COUNT;
    PlaySound(s_scoredSounds[index]);
}

void Sound_Cleanup() {
    for (int i = 0; i < HIT_SOUND_COUNT; i++) UnloadSound(s_hitSounds[i]);
    for (int i = 0; i < SCORED_SOUND_COUNT; i++) UnloadSound(s_scoredSounds[i]);
}
