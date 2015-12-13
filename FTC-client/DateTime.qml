import QtQuick 2.0
import QtQuick.Layouts 1.2

ColumnLayout {
    Rectangle {
        color: 'white'
        border.color: 'black'
        border.width: 2

        Text{
            id: text
            width: parent.width
            font.pointSize: 18
            wrapMode: Text.WordWrap
            text: new Date().toLocaleString(Qt.locale())
        }

        Layout.fillWidth: true
        Layout.minimumHeight: text.height
    }
}

