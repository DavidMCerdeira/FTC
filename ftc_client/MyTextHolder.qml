//UserMessages.qml
import QtQuick 2.0
import QtQuick.Layouts 1.2

ColumnLayout {
    id: root

    property Text title : Text{ text: ''; font.pointSize: 18}
    property var content_model
    property int title_pointSize: 16

    property int content_pointSize: 14

    Text{
        id: _title
        font.pointSize: title.font.pointSize
        text: title.text
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

                model: content_model

                delegate: Text{
                    text: display
                    font.pointSize: content_pointSize
                }
            }
        }
    }
}

