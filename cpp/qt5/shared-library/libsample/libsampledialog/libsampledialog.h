
#ifndef LIBSAMPLEDIALOG_H
#define LIBSAMPLEDIALOG_H

#include <QDialog>
#include "libsampleglobals.h"

namespace Ui {
class LibSampleDialog;
}

namespace Sample
{

class LIBSAMPLE_API LibSampleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LibSampleDialog(const QString& title, QWidget* parent = nullptr);

    ~LibSampleDialog() override;

Q_SIGNALS:
    /*!
     * This is emitted when the button is clicked.
     */
    void clicked();

private:
    Ui::LibSampleDialog *ui;

private Q_SLOTS:
    void onSendSignalButtonClicked();
};

} // namespace Sample
#endif // LIBSAMPLEDIALOG_H
