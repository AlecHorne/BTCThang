/***********************************************************************************************
 * Copyright (C) 2020 Alec J. Horne - All Rights Reserved
 *
 * You may use, distribute and modify, or otherwise do whatever the fuck you want with this
 * code under the terms of no license, which is good because licenses suck.
 *
 * You obviously never received a copy of the above mentioned license with this file because
 * it doesn't fucking exist. Duh.
 *
 * If you have any questions regarding the following code you can figure it out yourself.
 *
 *
 * File:   NordOVPNConnection.h
 * Author: Alec J. Horne
 * Date:   5/1/2020
 *
 * Description: Connects to a NordVPN server using OpenVPN utilizing OpenVPNs command line
 *              interface tool. Signals are emitted when the connection status changes and
 *              also when an error is detected.
 *
 ***********************************************************************************************/

#pragma once

#include <memory>

#include <QObject>
#include <QProcess>

#include <ovpncli.hpp>

class NordOVPNConnection : public QObject,
                           public openvpn::ClientAPI::OpenVPNClient
{
   public:
      enum class Status
      {
         Unknown,
         Disconnected,
         Connecting,
         Connected
      };

      struct LoginInfo
      {
         QString username;
         QString password;
      };

      explicit NordOVPNConnection( const LoginInfo& loginInfo );
      explicit NordOVPNConnection( const QString& username, const QString& password );
      NordOVPNConnection() = default;
      ~NordOVPNConnection() override = default;

      // Prevent copying, moving and assigning
      NordOVPNConnection( const NordOVPNConnection& ) = delete;
      NordOVPNConnection& operator=( const NordOVPNConnection& ) = delete;
      NordOVPNConnection& operator=( NordOVPNConnection&& ) = delete;
      NordOVPNConnection( NordOVPNConnection&& ) = delete;

      bool SetAndApplyConfigFile( const QString& configFileName );

      // openvpn::ClientAPI::OpenVPNClient contract
      void event( const openvpn::ClientAPI::Event& event ) override;
      void log( const openvpn::ClientAPI::LogInfo& logInfo ) override;
      void external_pki_sign_request( openvpn::ClientAPI::ExternalPKISignRequest& signRequest ) override;
      void external_pki_cert_request( openvpn::ClientAPI::ExternalPKICertRequest& certRequest ) override;
      bool pause_on_connection_timeout() override;

   signals:
      void connectionStatusChanged() const;

   private:
      Q_OBJECT
      Q_ENUM( Status )

      static constexpr const auto ovpnConfigDirectory = R"(C:\Workspace\openvpn3\configs\)";

      std::unique_ptr< QProcess > ovpnProcess;

      LoginInfo loginInfo;
      QString server;
      Status status;
};
