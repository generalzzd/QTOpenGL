import QtQuick 2.0
import QtQuick.Controls 2.0

ApplicationWindow {
    id:mAppWindow
    visible: true
    width: 640
    height: 480

    Text {
        id: mText
        text: qsTr("ZZD text")
    }

    Button {
        id: button
        x: 87
        y: 69
        text: qsTr("Button")

        onClicked: {

            ZDWindow.openWindow();
        }
    }



}
