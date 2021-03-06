#ifndef TILEVIEWWIDGETPRIVATE
#define TILEVIEWWIDGETPRIVATE

#include "tileviewwidget.h"

#include <QSize>
#include <QHash>
#include <QObject>
#include <QFrame>

class QPushButton;
class QLabel;
class ClientAppLogic;
class FlowLayout;
class RemoteClientVideoWidget;
class TileViewTileWidget;
class TileViewCameraWidget;
class TileViewUserListWidget;

///////////////////////////////////////////////////////////////////////

class TileViewWidgetPrivate : public QObject
{
  Q_OBJECT

public:
  TileViewWidgetPrivate(TileViewWidget *o) :
    owner(o),
    logic(nullptr),
    tilesAspectRatio(4, 3),
    tilesCurrentSize(tilesAspectRatio),
    leftPanelVisible(true),
    rightPanelVisible(false),
    tilesLayout(nullptr),
    cameraWidget(nullptr),
    zoomInButton(nullptr),
    zoomOutButton(nullptr)
  {}

public:
  TileViewWidget *owner;
  ClientAppLogic *logic;

  QSize tilesAspectRatio;
  QSize tilesCurrentSize;

  bool leftPanelVisible; ///< Used to store state in settings.
  bool rightPanelVisible; ///< Used to store state in settings.

  FlowLayout *tilesLayout;
  FlowLayout *noVideoTilesLayout;
  TileViewUserListWidget *userListWidget;
  TileViewCameraWidget *cameraWidget;
  QWidget *leftPanel;
  QWidget *rightPanel;
  QPushButton *zoomInButton;
  QPushButton *zoomOutButton;
  QPushButton *userListButton;
  QPushButton *hideLeftPanelButton;
  QPushButton *showLeftPanelButton;
  QLabel *userCountLabel;
  QLabel *bandwidthRead;
  QLabel *bandwidthWrite;

  QHash<int, TileViewTileWidget*> tilesMap; ///< Maps client's ID to it's widget.
};

///////////////////////////////////////////////////////////////////////

class TileViewCameraWidget : public QFrame
{
  Q_OBJECT
  friend class TileViewWidget;

public:
  TileViewCameraWidget(QWidget *parent = nullptr);
  ~TileViewCameraWidget();
  void setWidget(QWidget *w);

private:
  class QBoxLayout *_mainLayout;
};

///////////////////////////////////////////////////////////////////////

class TileViewTileWidget : public QFrame
{
  Q_OBJECT
  friend class TileViewWidget;

public:
  TileViewTileWidget(const ClientEntity &client, QWidget *parent = nullptr);

private:
  RemoteClientVideoWidget *_videoWidget;
};

///////////////////////////////////////////////////////////////////////

class TileViewUserListWidget : public QFrame
{
  Q_OBJECT
  friend class TileViewWidget;

public:
  TileViewUserListWidget(QWidget *parent = nullptr);

private:
  class QListView *_listView;
};

#endif