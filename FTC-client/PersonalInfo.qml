import QtQuick 2.0
import QtQuick.Layouts 1.2

ColumnLayout{
    id: personalInfo
    Layout.margins: 30
    spacing: 5

    Text{
        id: title
        font.pointSize: 20
        text: 'FTC - Facial Time Clock'
    }

    DateTime{
    }

    UserMessages {
        Layout.fillHeight: true
        id: messages
        title: 'Messages'
        title_pointSize: 18
    }
}

