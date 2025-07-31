#ifndef JOINROOM_H
#define JOINROOM_H

#include <QDialog>
#include "information.pb.h"
namespace Ui {
class JoinRoom;
}

enum class DialogType:char{Manul, Search};
class JoinRoom : public QDialog
{
    Q_OBJECT

public:
    explicit JoinRoom(DialogType type, QWidget *parent = nullptr);
    ~JoinRoom();
    void searchRoom();
    void joinRoom();

private:
    Ui::JoinRoom *ui;
    void encodeMessage(RequestCode code);
};

#endif // JOINROOM_H
