import QtQuick 2.0
import QtQuick.Layouts 1.2

ColumnLayout {
    Rectangle {
        color: 'white'
        border.color: 'black'
        border.width: 2

        Timer{
            id: timer
            interval: 1; repeat: true
            running: true
            triggeredOnStart: true

            onTriggered: {
                text.text = new Date().toLocaleString(Qt.locale())
            }
        }

        Text{
            id: text
            width: parent.width
            font.pointSize: 18
            wrapMode: Text.WordWrap
        }

        Layout.fillWidth: true
        Layout.minimumHeight: text.height
    }
}

