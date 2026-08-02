#pragma once

#include "Mesh.h"


class LocationProvider {
protected:
    mesh::RTCClock* _clock;
    bool _time_sync_needed = true;
    unsigned long _last_time_sync = 0;
    long _time_valid = 0;

public:
    virtual void syncTime() { _time_sync_needed = true; }
    virtual bool waitingTimeSync() { return _time_sync_needed; }
    virtual long getLatitude() = 0;
    virtual long getLongitude() = 0;
    virtual long getAltitude() = 0;
    virtual long satellitesCount() = 0;
    virtual bool isValid() = 0;
    virtual long getTimestamp() = 0;
    virtual void sendSentence(const char * sentence);
    virtual void reset() = 0;
    virtual void configure() = 0;
    virtual void begin() = 0;
    virtual void stop() = 0;
    virtual void loop() {
        if (isValid()) {
            time_valid ++;
        } else {
            _time_valid = 0;
        }
        if (_time_sync_needed && time_valid > 3) {
            if (_clock != NULL) {
                _clock->setCurrentTime(getTimestamp());
                _time_sync_needed = false;
                _last_time_sync = millis();
            }
        }
    };
    virtual bool isEnabled() = 0;
};
