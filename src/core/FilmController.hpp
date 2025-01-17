#pragma once

#include "FilmDetails.hpp"
#include <SFML/System/Clock.hpp>
#include <chrono>
#include <functional>
#include <list>

class FilmController
{
public:
    using Callback = std::function<void()>;

    explicit FilmController(const FilmDetails &details);

    enum class State { Playing, Paused, Loading };

    State state() const;
    FilmDetails filmDetails() const;
    std::chrono::milliseconds currentTime() const;

    bool playing() const;
    bool paused() const;
    bool loading() const;
    bool atEnd() const;

    void play();
    void pause();
    void restart();
    void jumpBackward();
    void jumpForward();
    void jumpTo(std::chrono::milliseconds time);
    void update();

    void onCurrentTimeChanged(Callback &&callback);
    void onStateChanged(Callback &&callback);

private:
    void jump(std::chrono::milliseconds interval);
    void notify(const std::list<Callback> &callbacks);

    FilmDetails m_filmDetails;
    State m_state{State::Loading};
    std::chrono::milliseconds m_currentTime{};
    std::list<Callback> m_currentTimeChangedCallbacks;
    std::list<Callback> m_stateChangedCallbacks;
    sf::Clock m_clock;
};
