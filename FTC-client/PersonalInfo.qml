import QtQuick 2.0
import QtQuick.Layouts 1.2
import UserMessages 1.0

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

    MyTextHolder {
        Layout.fillHeight: true
        id: messages
        title{
            text:  "Messages"
        }
        content_model: UserMessages {

        }
        
    }
}

