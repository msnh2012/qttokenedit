#pragma once

#include <token-edit/AbstractTokenDragDropHandler.h>

class QAbstractItemModel;

namespace mjendruk {

class TokenEdit;
class TokenEditView;

class TokenDragDropHandler : public AbstractTokenDragDropHandler {
 public:
  TokenDragDropHandler(TokenEdit* tokenEdit);

  bool canDrag(Token const* source) const override;

  QMimeData* mimeData(const Token* source) const override;

  bool dropAccepted(Token* token) override;

  bool canDropMimeData(const Token* target, const QMimeData* data,
                       QObject* source, TokenDropHint dropHint) const override;

  bool canDropMimeData(int row, QMimeData const* data,
                       QObject* source) const override;

  bool dropMimeData(const Token* target, const QMimeData* data, QObject* source,
                    TokenDropHint dropHint) override;

  bool dropMimeData(int row, QMimeData const* data, QObject* source) override;

 private:
  QAbstractItemModel* model() const;
  TokenEditView* view() const;

 private:
  TokenEdit* _tokenEdit;
};

}  // namespace mjendruk