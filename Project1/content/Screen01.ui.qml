import QtQuick
import QtQuick.Controls
import Project1

Rectangle {
    width: Constants.width
    height: Constants.height

    color: Constants.backgroundColor

    Text {
        text: qsTr("Hello Project1")
        anchors.centerIn: parent
        font.family: Constants.font.family
    }
}
