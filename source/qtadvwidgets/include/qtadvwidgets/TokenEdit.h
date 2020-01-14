#pragma once

#include <qtadvwidgets/TokenEditMode.h>
#include <qtadvwidgets/TokenEditViewport.h>
#include <qtadvwidgets/qtadvwidgets_api.h>

#include <QModelIndex>
#include <QScrollArea>
#include <QVariant>
#include <QVector>
#include <cstdint>

class QLineEdit;
class QAbstractItemModel;

class BaseToken;
class FlexLayout;
class TokenLineEdit;
class TokenChain;

class QTADVWIDGETS_API TokenEdit : public TokenEditViewport {
  Q_OBJECT

 public:
  using Mode = TokenEditMode;

  TokenEdit(TokenEditMode mode = TokenEditMode::AlwaysShowLineEdit,
            QWidget* parent = nullptr);
  ~TokenEdit();

  int maxLineCount() const;
  void setMaxLineCount(int count);

  bool dragEnabled() const;
  void setDragEnabled(bool enable);
  
  bool removable() const;
  void setRemovable(bool enable);

  int count() const;
  int isEmpty() const;

  QLineEdit* lineEdit();

  QAbstractItemModel* model() const;
  void setModel(QAbstractItemModel* model);

  int modelColumn() const;
  void setModelColumn(int column);

  QModelIndex rootIndex() const;
  void setRootIndex(QModelIndex const& index);
  
 signals:
  void dragStateChanged(bool enabled);
  void removableStateChanged(bool enabled);

 private:
  BaseToken const* at(int index) const;
  BaseToken* at(int index);
  void addItem(BaseToken* token);
  void insertItem(int index, BaseToken* token);
  void moveItem(int from, int to);
  void removeItem(int index);
  
  BaseToken* createToken(QString const& text);

  void updateHeight();
  void init();
  void clear();

  void onRowsInserted(QModelIndex const& parent, int first, int last);
  void onRowsRemoved(QModelIndex const& parent, int first, int last);
  void onRowsMoved(QModelIndex const& parent, int first, int last,
                   QModelIndex const& destination, int row);
  void onDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight,
                     const QVector<int>& roles);
  void onModelReset();

  void onItemDragged(Token* source, Token* target, Token::DropHint hint);

 private:
  QVector<BaseToken*> _items;
  TokenLineEdit* _lineEdit;
  TokenChain* _tokenChain;
  FlexLayout* _layout;
  int _maxLineCount;
  bool _dragEnabled;
  bool _removable;
  int _spacing;
  TokenEditMode _mode;
  QScrollArea* _scrollArea;

  // model members
  QAbstractItemModel* _model;
  QModelIndex _rootModelIndex;
  int _modelColumn;
};
