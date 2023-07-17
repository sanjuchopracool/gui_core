#ifndef COMPOSITIONVIEWMODEL_H
#define COMPOSITIONVIEWMODEL_H

#include <QAbstractListModel>
#include <QObject>

namespace inae {
class CompositionViewModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit CompositionViewModel(QObject *parent = nullptr);
};

} // namespace inae

#endif // COMPOSITIONVIEWMODEL_H
