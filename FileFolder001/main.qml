import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import Qt.labs.folderlistmodel 2.1
import FileFolder 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("File Box")

    StandardPaths{
        id: stdpath
    }

    FolderListModel {
        id: folderModel
        folder: "file://" + stdpath.documentPath()
        nameFilters: ["*.*"]
    }

    ListView{
        anchors.fill: parent
        model: folderModel
        delegate:
            Text { text: fileName + " : " + fileSize + " : " + fileModified  }
    }
}
