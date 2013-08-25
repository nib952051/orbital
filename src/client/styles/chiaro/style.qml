/*
 * Copyright 2013 Giulio Camuffo <giuliocamuffo@gmail.com>
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

import QtQuick 2.1
import Orbital 1.0
import QtGraphicalEffects 1.0

Style {
    panelBackground: StyleComponent {
        topContentsMargin: 2
        leftContentsMargin: 2
        rightContentsMargin: 2
        Rectangle {
            anchors.fill: parent
            color: "#e6e6e6"
        }
    }

    panelBorder: StyleComponent {
        Rectangle {
            anchors.fill: parent
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#f0202020" }
                GradientStop { position: 1.0; color: "#00000000" }
            }
        }
    }

    taskBarBackground: StyleComponent {
        Rectangle {
            anchors.fill: parent
            color: "transparent"
        }
    }

    taskBarItem: StyleComponent {
        property alias title: text.text
        property int state: Window.Inactive
        Item {
            anchors.fill: parent
            clip: true

            Rectangle {
                id: rect
                color: "#D2E3F5"
                radius: 3
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                height: parent.height + 10

                Behavior on color { ColorAnimation { duration: 100 } }
            }

            Text {
                id: text
                anchors.fill: parent
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                maximumLineCount: 1
                elide: Text.ElideRight
                color: "black"
            }

            states: [
                State {
                    name: "active"
                    when: state == Window.Active
                    PropertyChanges { target: rect; color: "#57A2FD" }
                }
            ]
        }
    }

    pagerBackground: StyleComponent {
        bottomContentsMargin: 2
    }

    pagerWorkspace: StyleComponent {
        property bool active: false
        Rectangle {
            id: rect
            anchors.fill: parent
            anchors.margins: 1
            color: active ? "white" : "#B4B4B4"

            Behavior on border.color { ColorAnimation {} }
        }
    }

    toolTipBackground: StyleComponent {
        Rectangle {
            anchors.fill: parent
            radius: 4
            color: "#e6e6e6e6"
        }
    }

    button: StyleComponent {
        property alias text: text.text
        property bool pressed: false

        Rectangle {
            anchors.fill: parent
            radius: 3
            border.color: "#a2a2a2"
            color: pressed ? "white" : "#c4c4c4"

            Behavior on color { ColorAnimation {} }

            Text {
                anchors.fill: parent
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                id: text
                color: "black"
            }
        }
    }

    textColor: "black"
    backgroundColor: "#F4F4F4"
}