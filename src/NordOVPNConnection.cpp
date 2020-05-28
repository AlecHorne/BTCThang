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
#include "NordOVPNConnection.h"

NordOVPNConnection::NordOVPNConnection( const LoginInfo& loginInfo ) :
   loginInfo{ loginInfo }
{}

NordOVPNConnection::NordOVPNConnection( const QString& username, const QString& password ) :
   NordOVPNConnection{ LoginInfo{ username, password } }
{}

bool NordOVPNConnection::SetAndApplyConfigFile( const QString& configFileName )
{
   Q_UNUSED( configFileName )

   return true;
}

void NordOVPNConnection::event( const openvpn::ClientAPI::Event& event )
{
   Q_UNUSED( event )
}

void NordOVPNConnection::log( const openvpn::ClientAPI::LogInfo& logInfo )
{
   Q_UNUSED( logInfo )
}

void NordOVPNConnection::external_pki_sign_request( openvpn::ClientAPI::ExternalPKISignRequest& signRequest )
{
   Q_UNUSED( signRequest )
}

void NordOVPNConnection::external_pki_cert_request( openvpn::ClientAPI::ExternalPKICertRequest& certRequest )
{
   Q_UNUSED( certRequest )
}

bool NordOVPNConnection::pause_on_connection_timeout()
{
   return true;
}
