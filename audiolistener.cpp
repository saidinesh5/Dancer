#include "audiolistener.h"
#include <QDebug>
#include <cmath>

AudioListener::AudioListener(QObject *parent) :
    QObject(parent),
    m_fft_machine(N_BUFFER_FRAMES),
    m_sampleRate(SAMPLE_RATE),
    m_nChannels(N_CHANNELS),
    m_nBufferFrames(N_BUFFER_FRAMES)
{
    if(m_adc.getDeviceCount() < 1)
        qDebug() << "Error! No Audio devices found.";

    startRecording();
}


AudioListener::~AudioListener()
{
    stopRecording();
}


int AudioListener::record(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *userData)
{
    Q_UNUSED(outputBuffer)
    Q_UNUSED(streamTime)

    AudioListener* self = (AudioListener*)userData;

    if(status)
        qDebug() << "Stream overflow detected";
    else
        self->processAudio((qint16*)inputBuffer, nBufferFrames);
    return 0;
}


bool AudioListener::startRecording()
{
    RtAudio::StreamParameters parameters;
    parameters.deviceId = m_adc.getDefaultInputDevice();
    parameters.nChannels = m_nChannels;
    parameters.firstChannel = 0;

    try {

        m_adc.openStream( NULL, &parameters, RTAUDIO_SINT16,
                          m_sampleRate, &m_nBufferFrames, &AudioListener::record, (void*)this );
        m_adc.startStream();
        return true;
    }
    catch (RtError &e){
        qDebug()<< "Error!!!" << e.getMessage().c_str();
        return false;
    }
}


bool AudioListener::stopRecording()
{
    try {
        m_adc.stopStream();
        return true;
    }
    catch (RtError &e){
        qDebug()<< "Error!!!" << e.getMessage().c_str();
        return false;
    }
}


void AudioListener::processAudio(qint16 *data, int nFrames)
{
    m_nBufferFrames = nFrames;

    //Copy the data into buffers
    for( int i = 0; i < nFrames; i++){
        m_audioData[LEFT][i] = ((float)*( data + i ))/32768.0;
        m_audioData[RIGHT][i] = ((float)*( data + i + 1 ))/32768.0;
        m_monoAudioData[i] = (m_audioData[LEFT][i] + m_audioData[RIGHT][i])/2.0;
    }

    //Take the fft
    m_fft_machine.do_fft(m_tmp_fft_samples[LEFT],m_audioData[LEFT]);
    m_fft_machine.do_fft(m_tmp_fft_samples[RIGHT],m_audioData[RIGHT]);

    //Calculate the VU values
    float real, imaginary, vu;
    const int n_fft_values = nFrames/2;

    for (int i = 0; i < N_CHANNELS; i++){
        vu = 0;
        for (int j = 0; j < n_fft_values; j++){
            real = m_tmp_fft_samples[i][j];
            imaginary = m_tmp_fft_samples[i][n_fft_values + j];
            m_tmp_fft_values[i][j] = (sqrt(real*real + imaginary*imaginary)/n_fft_values);
            vu += m_tmp_fft_values[i][j];
        }
        m_vu[i] = vu;
    }

    //Calculate the spectrum data
    for (int i = 0; i < N_CHANNELS; i++){
        for (int j = 0; j < n_fft_values; j++){
            m_spectrumData[i][j] = m_tmp_fft_values[i][j/2] * 3.0 * pow(log( 10.0f + ((float)SAMPLE_RATE) * (j /(float)N_BUFFER_FRAMES)) ,1.0f);
        }
    }

    //Now calculate the octave data
    float current_octave =0;
    int values_per_octave = N_BUFFER_FRAMES/N_OCTAVES;
    for (int i = 0; i < N_CHANNELS; i++)
        for ( int j = 0; j < N_OCTAVES; j++){
            current_octave = 0;
            for ( int k = 0; k < values_per_octave; k++)
                current_octave +=  m_spectrumData[i][j*values_per_octave + k];
            current_octave /= values_per_octave;
            m_octaves[i][j] = current_octave;
        }
    emit audioDataUpdated();
}


QVariantMap AudioListener::data()
{
    QVariantMap result;
    QVariantMap leftResult,rightResult;

    leftResult[QString("vu")] = m_vu[LEFT];
    rightResult[QString("vu")] = m_vu[RIGHT];

    for(int i = 0; i < 8; i++ ){
        leftResult[QString("octave%1").arg(i)] =  m_octaves[LEFT][i];
        rightResult[QString("octave%1").arg(i)] =  m_octaves[RIGHT][i];
    }

    result[QString("left")] = leftResult;
    result[QString("right")] = rightResult;

    return result;
}
