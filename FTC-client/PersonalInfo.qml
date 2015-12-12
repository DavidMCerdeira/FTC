import QtQuick 2.0
import QtQuick.Layouts 1.2


ColumnLayout{
    id: personalInfo
    Layout.margins: 30
    spacing: 5

//    MyTextHolder {
//        id: dataTime
//        title: 'FTC - Facial Time Clock'
//        title_pointSize: 20
//        content: "HH:MM x.m. DD/MM/YYYY"
//        content_pointSize: 26
//        Layout.fillHeight: false
//    }

    Text{
        id: title
        font.pointSize: 20
        text: 'FTC - Facial Time Clock'
    }

    Rectangle {
        color: 'white'
        border.color: 'black'
        border.width: 2

        Text{
            id: text
            font.pointSize: 26
            wrapMode: Text.WordWrap
            text: "HH:MM x.m. DD/MM/YYYY"
        }

        Layout.fillWidth: true
        Layout.minimumHeight: text.height
    }

        MyTextHolder {
            id: notes
            title: 'Notes'
            title_pointSize: 18
            content: 'Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! Notes will apear here! '
            content_pointSize: 14
            height: parent.height * 1 / 5
        }

    MyTextHolder {
        Layout.fillHeight: true
        id: messages
        title: 'Messages'
        title_pointSize: 18
        content: 'Messages will apear here! Messages will apear here! Messages will apear here! Messages will apear here! Messages will apear here! Messages will apear here! Messages will apear here! Messages will apear here! Messages will apear here! Messages will apear here! Messages will apear here! Messages will apear here! Messages will apear here! Messages will apear here! Messages will apear here! Messages will apear here! Messages will apear here! Messages will apear here! Messages will apear here! Messages will apear here! Messages will apear here! Messages will apear here! Messages will apear here! Messages will apear here! Messages will apear here! Messages will apear here! Messages will apear here! Messages will apear here! Messages will apear here! Messages will apear here! Messages will apear here! Messages will apear here! Messages will apear here! Messages will apear here! Messages will apear here! Messages will apear here! Messages will apear here! '
        content_pointSize: 14
    }
}

