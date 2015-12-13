//UserMessages.qml
import QtQuick 2.0
import QtQuick.Layouts 1.2
import UserMessages 1.0

ColumnLayout {
    id: root

    property string title: ''
    property int title_pointSize: 16

    property int content_pointSize: 14

    Text{
        id: _title
        font.pointSize: {title: '' ? 0 : title_pointSize}
        text: title
    }


    Rectangle {
        id: notesfield
        color: 'white'
        border.color: 'black'
        border.width: 2
        Layout.fillWidth: true
        Layout.fillHeight: true

        Rectangle {
            id: inside
            width: parent.width - 10;
            height: parent.height - 10;
            anchors.centerIn: parent

            ListView{
                anchors.fill: parent
                clip: true
                model: UserMessages{
                    id: messages
                }
                delegate: Text{
                    text: index + ' ' + display
                    font.pointSize: content_pointSize
                }
            }
        }
    }
}

