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

#ifndef ORBITAL_DESKTOP_SHELL_H
#define ORBITAL_DESKTOP_SHELL_H

#include "interface.h"

struct wl_resource;

namespace Orbital {

class Shell;
class ChildProcess;
class View;
class Pointer;
class DesktopShellSplash;
enum class PointerCursor: unsigned int;

class DesktopShell : public Interface, public Global
{
    Q_OBJECT
public:
    explicit DesktopShell(Shell *shell);
    ~DesktopShell();

protected:
    void bind(wl_client *client, uint32_t version, uint32_t id) override;

private:
    void setGrabCursor(Pointer *p, PointerCursor c);

    void setBackground(wl_resource *outputResource, wl_resource *surfaceResource);
    void setPanel(uint32_t id, wl_resource *outputResource, wl_resource *surfaceResource, uint32_t position);
    void setLockSurface(wl_resource *surfaceResource);
    void setPopup(uint32_t id, wl_resource *parentResource, wl_resource *surfaceResource, int x, int y);
    void unlock();
    void setGrabSurface(wl_resource *surfaceResource);
    void desktopReady();
    void addKeyBinding(uint32_t id, uint32_t key, uint32_t modifiers);
    void addOverlay(wl_resource *outputResource, wl_resource *surfaceResource);
    void minimizeWindows();
    void restoreWindows();
    void createGrab(uint32_t id);
    void addWorkspace();
    void selectWorkspace(wl_resource *outputResource, wl_resource *workspaceResource);
    void quit();
    void addTrustedClient(int32_t fd, const char *interface);
    void pong(uint32_t serial);

    Shell *m_shell;
    ChildProcess *m_client;
    wl_resource *m_resource;
    View *m_grabView;
    DesktopShellSplash *m_splash;
};

}

#endif