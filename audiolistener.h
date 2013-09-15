#ifndef AUDIOLISTENER_H
#define AUDIOLISTENER_H

#include <QObject>
#include <QVariantMap>
#include <RtAudio/RtAudio.h>
#include <RtAudio/RtError.h>
#include <fftreal/fftreal.h>

#define SAMPLE_RATE 44100
#define N_CHANNELS 2
#define N_BUFFER_FRAMES 512
#define N_OCTAVES 8

#define LEFT 0
#define RIGHT 1

class AudioListener : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariantMap data READ data NOTIFY audioDataUpdated())

    //The Machinery
    FFTReal m_fft_machine;
    RtAudio m_adc;

    void processAudio(qint16* data, int nFrames);

protected:
    const unsigned int m_sampleRate;
    const unsigned int m_nChannels;
    unsigned int m_nBufferFrames;

    float m_audioData[N_CHANNELS][N_BUFFER_FRAMES];
    float m_spectrumData[N_CHANNELS][N_BUFFER_FRAMES];

    //These are needed for internal processing
    float m_monoAudioData[N_BUFFER_FRAMES];
    float m_tmp_fft_samples[N_CHANNELS][N_BUFFER_FRAMES];
    float m_tmp_fft_values[N_CHANNELS][N_BUFFER_FRAMES];

    double m_vu[N_CHANNELS];
    double m_octaves[N_CHANNELS][N_OCTAVES];

public:
    explicit AudioListener(QObject *parent = 0);
    ~AudioListener();

    static int record( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
                       double streamTime, RtAudioStreamStatus status, void *userData );

    bool startRecording();
    bool stopRecording();

signals:
    void audioDataUpdated();

public slots:
    QVariantMap data();
};

#endif // AUDIOLISTENER_H
