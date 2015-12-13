//MyTextHolder.qml
import QtQuick 2.0
import QtQuick.Layouts 1.2

ColumnLayout {
    id: root

    property string title: ''
    property int title_pointSize: 16

    property string content : ''
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

        Flickable {
            anchors.fill: parent
            height: parent.height - 5
            contentWidth: parent.width
            contentHeight: text.height
            clip: true
            Text{
                id: text
                font.pointSize: content_pointSize
                width: notesfield.width
                wrapMode: Text.WordWrap
                text: content
            }
        }
    }


    //Layout.maximumHeight: text.height
}

