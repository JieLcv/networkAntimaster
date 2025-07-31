#include "scorepannel.h"
#include "ui_scorepannel.h"
#include <QFont>
const QString MYCOLOR[] = {"black", "white", "red", "blue", "green"};
ScorePannel::ScorePannel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScorePannel)
{
    ui->setupUi(this);
    m_list << ui->myScore << ui->leftScore << ui->rightScore
           << ui->meTitle << ui->leftTitle << ui->rightTitle
           << ui->score1 << ui->score2 << ui->score3;
}

ScorePannel::~ScorePannel()
{
    delete ui;
}

void ScorePannel::setScores(int left, int right, int user)
{
    ui->leftScore->setText(QString::number(left));
    ui->rightScore->setText(QString::number(right));
    ui->myScore->setText(QString::number(user));
}

void ScorePannel::setMyFontSize(int point)
{
    QFont font("微软雅黑",point, QFont::Bold);
    for(int i = 0; i < m_list.size(); ++i)
    {
        m_list[i]->setFont(font);
    }
}

void ScorePannel::setMyFontColor(ScorePannel::FontColor color)
{
    QString style = QString("QLabel{color:%1}").arg(MYCOLOR[color]);
    for(int i = 0; i < m_list.size(); ++i)
    {
        m_list[i]->setStyleSheet(style);
    }
}

void ScorePannel::setPlayerName(QByteArray left, QByteArray mid, QByteArray right)
{
    ui->leftTitle->setText(left);
    ui->meTitle->setText(mid);
    ui->rightTitle->setText(right);
}
