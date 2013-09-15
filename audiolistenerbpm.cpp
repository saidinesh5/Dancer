#include "audiolistenerbpm.h"

#include <QDebug>

AudioListenerBPM::AudioListenerBPM(QObject *parent) :
    AudioListener(parent),
    m_bpm(0.0),
    m_miniBPM(SAMPLE_RATE)
{
    connect(this, SIGNAL(audioDataUpdated()), this, SLOT(processSampleData()));

    m_timer = new QTimer(this);
    connect(m_timer,SIGNAL(timeout()), this, SLOT(updateBPM()));
    m_timer->start(BPM_INTERVAL);
}


void AudioListenerBPM::processSampleData()
{
    m_miniBPM.process(m_monoAudioData, m_nBufferFrames);
}

void AudioListenerBPM::updateBPM()
{
    double bpm = m_miniBPM.estimateTempo();
    if(bpm != m_bpm){
        m_bpm = bpm;
        emit bpmChanged();
    }
}


double AudioListenerBPM::bpm() const
{
    return m_bpm;
}


