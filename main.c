#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include <AL/al.h>
#include <AL/alc.h>

#define SAMPLE_RATE 44100
#define FREQUENCY 440.0
#define DURATION 1.0  // 1 second
#define NUM_SAMPLES (int)(SAMPLE_RATE * DURATION)

#if defined(_WIN32) || defined(_WIN64)
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
    #define SLEEP(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define SLEEP(ms) usleep(ms * 1000) // usleep takes microseconds
#endif

int main() {
    ALCdevice *device;
    ALCcontext *context;
    ALuint buffer, source;
    short samples[NUM_SAMPLES];
    double phaseIncrement = 2.0 * M_PI * FREQUENCY / SAMPLE_RATE;
    double phase = 0;

    // Generate sine wave samples
    for (int i = 0; i < NUM_SAMPLES; i++) {
        samples[i] = (short)(32767.0 * sin(phase));
        phase += phaseIncrement;
        if (phase > 2.0 * M_PI) {
            phase -= 2.0 * M_PI;
        }
    }

    // Initialize OpenAL
    device = alcOpenDevice(NULL);
    context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);

    alGenBuffers(1, &buffer);
    alGenSources(1, &source);

    // Load buffer and set up source
    alBufferData(buffer, AL_FORMAT_MONO16, samples, NUM_SAMPLES * sizeof(short), SAMPLE_RATE);
    alSourcei(source, AL_BUFFER, buffer);

    // Play audio
    alSourcePlay(source);
    SLEEP(2000);  // Sleep for 2 seconds

    // Clean up
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
    alcDestroyContext(context);
    alcCloseDevice(device);

    return 0;
}
