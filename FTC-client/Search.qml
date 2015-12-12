import QtQuick 2.0
import QtQuick.Layouts 1.2

Item {
    anchors.fill: parent

    RowLayout{
        id: mainLayout
        anchors.fill: parent

        SearchEmployee{
            Layout.maximumWidth: parent.width * 1 / 3
        }

        SearchWorking{
            Layout.fillWidth: true
        }
    }
}

