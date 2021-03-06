#ifndef CLIENTAPPLOGIC_H
#define CLIENTAPPLOGIC_H

#include <QScopedPointer>
#include <QString>
#include <QHash>
#include <QHostAddress>
#include <QMainWindow>

#include "ts3video.h"
#include "yuvframe.h"

#include "networkclient/networkclient.h"

class QWidget;
class QProgressDialog;
class ViewBase;
class ClientCameraVideoWidget;
class RemoteClientVideoWidget;

/*!
  Logic to control the GUI and connection on client-side.
 */
class ClientAppLogicPrivate;
class ClientAppLogic : public QMainWindow
{
  Q_OBJECT
  friend class ClientAppLogicPrivate;
  QScopedPointer<ClientAppLogicPrivate> d;

public:
  class Options
  {
  public:
    // The address and port of the remote server.
    // The address can either be a name like "myhost.com" or and IPv4/IPv6 address.
    QString serverAddress = IFVS_SERVER_ADDRESS;
    quint16 serverPort = IFVS_SERVER_CONNECTION_PORT;
    QString serverPassword;

    // The visible username of the client.
    QString username = QString();

    // Information about the channel to join.
    qint64 channelId = 0;                                              ///< The channel's ID.
    QString channelIdentifier;                                         ///< String based identifier. An ID will be calculated from this string.
    QString channelPassword;                                           ///< The channel's password.

    // The camera's device ID to stream video.
    QString cameraDeviceId = QString();
  };

  /*!
    This is very, very dirty.
    I'm currently using this approach, because i don't want to pass
    the object into every small object/dialog which might need it.

    This method does not actually create the object.
    As soon as the normal constructor gets called it will return the
    created instance. As i said... very dirty.

    \todo As long as we use this way, we can't not have multiple instances.
  */
  static ClientAppLogic* instance();
  static ClientAppLogic* I() { return instance(); }

public:
  ClientAppLogic(const Options &opts, QWidget *parent, Qt::WindowFlags flags);
  ~ClientAppLogic();
  NetworkClient* networkClient();

public slots:
  void init();

private slots:
  void onConnected();
  void onDisconnected();
  void onError(QAbstractSocket::SocketError socketError);
  void onServerError(int code, const QString &message);
  void onClientJoinedChannel(const ClientEntity &client, const ChannelEntity &channel);
  void onClientLeftChannel(const ClientEntity &client, const ChannelEntity &channel);
  void onClientDisconnected(const ClientEntity &client);
  void onNewVideoFrame(YuvFrameRefPtr frame, int senderId);
  void onNetworkUsageUpdated(const NetworkUsageEntity &networkUsage);

protected:
  virtual void showEvent(QShowEvent *e);
  virtual void closeEvent(QCloseEvent *e);
  void initGui();
  QWidget* createCameraWidget();
  void showProgress(const QString &text);
  void hideProgress();
  void showResponseError(int status, const QString &errorMessage, const QString &details = QString());
  void showError(const QString &shortText, const QString &longText = QString(), bool exitApp = false);
};

#endif