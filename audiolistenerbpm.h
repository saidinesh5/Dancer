#ifndef AUDIOLISTENERBPM_H
#define AUDIOLISTENERBPM_H

#include <MiniBpm/MiniBpm.h>
#include <QTimer>

#include "audiolistener.h"

#define BPM_INTERVAL 1000

class AudioListenerBPM : public AudioListener
{
    // BPM is actually computed periodically - every 1 second
    // Save CPU to save kittens
    Q_OBJECT

    Q_PROPERTY(double bpm READ bpm NOTIFY bpmChanged)

    double m_bpm;
    breakfastquay::MiniBPM m_miniBPM;
    QTimer *m_timer;

private slots:
    void processSampleData();
    void updateBPM();

public:
    explicit AudioListenerBPM(QObject *parent = 0);
    double bpm() const;

signals:
    void bpmChanged();
    
public slots:

};

#endif // AUDIOLISTENERBPM_H
