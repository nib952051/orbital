/*
 * Copyright 2013-2014 Giulio Camuffo <giuliocamuffo@gmail.com>
 *
 * This file is part of Orbital
 *
 * Orbital is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Orbital is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Orbital.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ORBITAL_SEAT_H
#define ORBITAL_SEAT_H

#include <functional>
#include <unordered_set>

#include <compositor.h>

#include <QObject>
#include <QPointF>

struct wl_resource;
struct wl_client;
struct weston_seat;
struct weston_pointer;
struct weston_pointer_grab;
struct weston_keyboard;
struct weston_pointer_motion_event;
struct weston_pointer_axis_event;

namespace Orbital {

class Compositor;
class PointerGrab;
class Pointer;
class Keyboard;
class View;
class Surface;
class ShellSurface;
class Workspace;
class Output;
class FocusScope;
class Keymap;
enum class PointerButton : unsigned char;

class Seat : public QObject
{
    Q_OBJECT
public:
    struct Listener;

    explicit Seat(Compositor *c, weston_seat *seat);
    ~Seat();

    Compositor *compositor() const;
    Pointer *pointer() const;
    Keyboard *keyboard() const;

    void activate(FocusScope *scope);

    void sendSelection(wl_client *client);

    void setKeymap(const Keymap &keymap);

    wl_resource *resource(wl_client *client) const;
    weston_seat *westonSeat() const { return m_seat; }

    wl_client *selectionClient() const;

    static Seat *fromSeat(weston_seat *seat);
    static Seat *fromResource(wl_resource *res);

signals:
    void pointerFocus(Pointer *pointer);
    void pointerMotion(Pointer *pointer);
    void selection(Seat *seat);

private:
    void capsUpdated();

    Compositor *m_compositor;
    weston_seat *m_seat;
    Listener *m_listener;
    Pointer *m_pointer;
    Keyboard *m_keyboard;
    FocusScope *m_activeScope;

    friend FocusScope;
};

enum class PointerCursor: unsigned int {
    None = 0,
    ResizeTop = 1,
    ResizeBottom = 2,
    Arrow = 3,
    ResizeLeft = 4,
    ResizeTopLeft = ResizeTop | ResizeLeft,
    ResizeBottomLeft = ResizeBottom | ResizeLeft,
    Move = 7,
    ResizeRight = 8,
    ResizeTopRight = ResizeTop | ResizeRight,
    ResizeBottomRight = ResizeBottom | ResizeRight,
    Busy = 11,
    Kill = 12
};

enum class PointerHotSpot : unsigned char {
    TopLeftCorner,
    TopRightCorner,
    BottomLeftCorner,
    BottomRightCorner
};

class Pointer
{
public:
    enum class ButtonState {
        Released = 0,
        Pressed = 1
    };
    class MotionEvent {
    public:
        explicit MotionEvent(weston_pointer_motion_event *e) : m_evt(e) {}

    private:
        weston_pointer_motion_event *m_evt;
        friend Pointer;
    };
    class AxisEvent {
    public:
        explicit AxisEvent(weston_pointer_axis_event *e) : m_evt(e) {}

    private:
        weston_pointer_axis_event *m_evt;
        friend Pointer;
    };

    explicit Pointer(Seat *seat, weston_pointer *pointer);
    ~Pointer();

    inline Seat *seat() const { return m_seat; }
    View *pickView(double *x = nullptr, double *y = nullptr,
                   const std::function<bool (View *view)> &filter = nullptr) const;
    View *pickActivableView(double *x = nullptr, double *y = nullptr) const;

    void setFocus(View *view);
    void setFocus(View *view, double x, double y);
    inline void setFocus(View *view, const QPointF &p) { setFocus(view, p.x(), p.y()); }
    inline View *focus() const { return m_focus; }
    void move(MotionEvent evt);
    void sendMotion(uint32_t time);
    void sendButton(uint32_t time, PointerButton button, ButtonState state);
    int buttonCount() const;
    double x() const;
    double y() const;

    Output *currentOutput() const;

    bool isGrabActive() const;
    PointerGrab *activeGrab() const;
    uint32_t grabSerial() const;
    uint32_t grabTime() const;
    PointerButton grabButton() const;
    QPointF grabPos() const;

    QPointF motionToAbs(MotionEvent evt) const;

    void defaultGrabFocus();
    void defaultGrabMotion(uint32_t time, MotionEvent evt);
    void defaultGrabButton(uint32_t time, uint32_t btn, uint32_t state);
    void defaultGrabAxis(uint32_t time, AxisEvent evt);
    void defaultGrabAxisSource(uint32_t source);
    void defaultGrabFrame();

private:
    void setFocusFixed(View *view, wl_fixed_t x, wl_fixed_t y);
    void handleMotionBinding(uint32_t time, MotionEvent evt);
    void updateFocus();
    struct Listener;

    Seat *m_seat;
    weston_pointer *m_pointer;
    View *m_focus;
    Output *m_currentOutput;
    Listener *m_listener;
    struct {
        std::unordered_set<Output *> outputs;
    } m_defaultGrab;
    struct {
        uint32_t lastTime;
        uint32_t enterHotZone;
    } m_hotSpotState;

    friend PointerGrab;
    friend Seat;
};

class PointerGrab
{
public:
    PointerGrab();
    virtual ~PointerGrab();

    void start(Seat *seat);
    void start(Seat *seat, PointerCursor c);
    void end();

    Pointer *pointer() const;
    void setCursor(PointerCursor cursor);

protected:
    virtual void focus() {}
    virtual void motion(uint32_t time, Pointer::MotionEvent evt) {}
    virtual void button(uint32_t time, PointerButton button, Pointer::ButtonState state) {}
    virtual void cancel() {}
    virtual void ended() {}
//     void setCursor(Cursor cursor);
//     void unsetCursor();

private:
    static PointerGrab *fromGrab(weston_pointer_grab *grab);

    Seat *m_seat;
    struct Grab : public weston_pointer_grab {
        PointerGrab *parent;
    } m_grab;

    static const weston_pointer_grab_interface s_grabInterface;

    friend Pointer;
};

class Keyboard
{
public:
    uint32_t grabSerial() const;

private:
    explicit Keyboard(Seat *seat, weston_keyboard *k);

    Seat *m_seat;
    weston_keyboard *m_keyboard;

    friend Seat;
};

}

#endif
