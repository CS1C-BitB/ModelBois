#ifndef DETAILVIEW_H
#define DETAILVIEW_H

#include <QDialog>

namespace Ui {
class DetailView;
}

/**
 * @brief DetailView class
 *
 * This class is used with objects which work with the detailed view of the shape objects
 */
class DetailView : public QDialog
{
	Q_OBJECT
	
public:
    /**
     * @brief Constructor
     * @param text, string to be used in the detailed view window
     * @param parent
     */
	explicit DetailView(const QString &text, QWidget *parent = nullptr);

    /**
     * @brief Destructor
     */
    ~DetailView();
	
private:
	Ui::DetailView *ui;
};

#endif // DETAILVIEW_H
