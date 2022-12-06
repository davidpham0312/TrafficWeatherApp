#ifndef FORCASTCOMBINEDPAGE_H
#define FORCASTCOMBINEDPAGE_H

#include <QWidget>

namespace Ui {
class forcastCombinedPage;
}

class forcastCombinedPage : public QWidget
{
    Q_OBJECT

public:
    explicit forcastCombinedPage(QWidget *parent = nullptr);
    ~forcastCombinedPage();

private:
    Ui::forcastCombinedPage *ui;
};

#endif // FORCASTCOMBINEDPAGE_H
