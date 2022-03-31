#include <Blinker.h>

Blinker::Blinker(int pin, bool idleState) {
    _blinkPin = pin;
    _highDelay = 500;
    _lowDelay = 500;
    _lastBlink = 0;
    _blinkState = false;
    _running = false;
    _idleState = idleState;
}

void Blinker::setDelay(uint32_t d) {
    _highDelay = d;
    _lowDelay = d;
}

void Blinker::setDelay(uint32_t h, uint32_t l) {
    _highDelay = h;
    _lowDelay = l;
}

void Blinker::blink() {
    if (running) {
        uint32_t diff = millis() - _lastBlink;
        uint32_t blinkDelay = _blinkState ? _highDelay : _lowDelay;
        _duration -= diff;
        if (_duration <= 0) {
            stop();
        } else if (diff >= blinkDelay) {
            _lastBlink = millis() - (diff - blinkDelay); // Account for any delay in calling blink
            _blinkState = !_blinkState;
            digitalWrite(_blinkPin, _blinkState ? HIGH : LOW);
        }
    }
}

void Blinker::start(double duration) {
    pinMode(_blinkPin, OUTPUT);
    _running = true;
    _duration = duration;
    _lastBlink = millis();
}

void Blinker::stop() {
    _running = false;
    digitalWrite(_blinkPin, _idleState);
}
