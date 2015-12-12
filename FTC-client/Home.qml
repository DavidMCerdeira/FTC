import QtQuick 2.0
import QtQuick.Layouts 1.2

RowLayout{
    id: mainLayout
    anchors.fill: parent
    Layout.margins: 30

    Login{
        id: login
        width: parent.width * 2 / 5
    }

    PersonalInfo{
        id: info
        Layout.fillWidth: true
    }
}

