/////////////////////////////////////////////////////////////////////////////
//
// RCServerEvents.cpp : Implementation of CRCServer events
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RCServer.h"
#include "RCServerSocket.h"

void CRCServer::OpenStateChange( long NewState )
{
    switch (NewState)
    {
    case wmposUndefined:
        break;
	case wmposPlaylistChanging:
        break;
	case wmposPlaylistLocating:
        break;
	case wmposPlaylistConnecting:
        break;
	case wmposPlaylistLoading:
        break;
	case wmposPlaylistOpening:
        break;
	case wmposPlaylistOpenNoMedia:
        break;
	case wmposPlaylistChanged:
        break;
	case wmposMediaChanging:
        break;
	case wmposMediaLocating:
        break;
	case wmposMediaConnecting:
        break;
	case wmposMediaLoading:
        break;
	case wmposMediaOpening:
        break;
	case wmposMediaOpen:
        break;
	case wmposBeginCodecAcquisition:
        break;
	case wmposEndCodecAcquisition:
        break;
	case wmposBeginLicenseAcquisition:
        break;
	case wmposEndLicenseAcquisition:
        break;
	case wmposBeginIndividualization:
        break;
	case wmposEndIndividualization:
        break;
	case wmposMediaWaiting:
        break;
	case wmposOpeningUnknownURL:
        break;
    default:
        break;
    }
}

void CRCServer::PlayStateChange( long NewState )
{
	char s[32];

    switch (NewState)
    {
    case wmppsUndefined:
        break;
	case wmppsStopped:
		strcpy(s, "Stopped");
		//m_pServerSocket->SendToClient(s, strlen(s), 0);
		//MessageBox(NULL, _T("Stopped"), _T("Dauer"), MB_OK);
        break;
	case wmppsPaused: {
		//MessageBox(NULL, _T("Paused"), _T("Dauer"), MB_OK);
		strcpy(s, "Paused");
		//m_pServerSocket->SendToClient(s, strlen(s), 0);
        break;
	}
	case wmppsPlaying: {
		strcpy(s, "Playing");
		//m_pServerSocket->SendToClient(s, strlen(s), 0);
		/*CComPtr<IWMPMedia>      spMedia;
		HRESULT                 dwError = S_OK;
		HRESULT                 hr = S_OK;
		
		if (m_spCore) {
			hr = m_spCore->get_currentMedia(&spMedia);
			CComBSTR sDuration, sName;

			if (SUCCEEDED(hr)) {
				hr = spMedia->get_durationString(&sDuration);
				spMedia->get_name(&sName);
				spMedia->getItemInfo(_T("Author"), &sName);
			}

			if (SUCCEEDED(hr)) {
				MessageBox(NULL, (LPCTSTR)OLE2T(sDuration), _T("Dauer"), MB_OK);
				MessageBox(NULL, (LPCTSTR)OLE2T(sName), _T("Name"), MB_OK);
			}
		}*/
		break;
					   }
	case wmppsScanForward:
        break;
	case wmppsScanReverse:
        break;
	case wmppsBuffering:
        break;
	case wmppsWaiting:
        break;
	case wmppsMediaEnded:
        break;
	case wmppsTransitioning:
        break;
	case wmppsReady:
        break;
	case wmppsReconnecting:
        break;
	case wmppsLast:
        break;
    default:
        break;
    }
}

void CRCServer::AudioLanguageChange( long LangID )
{
}

void CRCServer::StatusChange()
{
}

void CRCServer::ScriptCommand( BSTR scType, BSTR Param )
{
}

void CRCServer::NewStream()
{
}

void CRCServer::Disconnect( long Result )
{
}

void CRCServer::Buffering( VARIANT_BOOL Start )
{
}

void CRCServer::Error()
{
    CComPtr<IWMPError>      spError;
    CComPtr<IWMPErrorItem>  spErrorItem;
    HRESULT                 dwError = S_OK;
    HRESULT                 hr = S_OK;

    if (m_spCore)
    {
        hr = m_spCore->get_error(&spError);

        if (SUCCEEDED(hr))
        {
            hr = spError->get_item(0, &spErrorItem);
        }

        if (SUCCEEDED(hr))
        {
            hr = spErrorItem->get_errorCode( (long *) &dwError );
        }
    }
}

void CRCServer::Warning( long WarningType, long Param, BSTR Description )
{
}

void CRCServer::EndOfStream( long Result )
{
}

void CRCServer::PositionChange( double oldPosition, double newPosition)
{
}

void CRCServer::MarkerHit( long MarkerNum )
{
}

void CRCServer::DurationUnitChange( long NewDurationUnit )
{
}

void CRCServer::CdromMediaChange( long CdromNum )
{
}

void CRCServer::PlaylistChange( IDispatch * Playlist, WMPPlaylistChangeEventType change )
{
    switch (change)
    {
    case wmplcUnknown:
        break;
	case wmplcClear:
        break;
	case wmplcInfoChange:
        break;
	case wmplcMove:
        break;
	case wmplcDelete:
        break;
	case wmplcInsert:
        break;
	case wmplcAppend:
        break;
	case wmplcPrivate:
        break;
	case wmplcNameChange:
        break;
	case wmplcMorph:
        break;
	case wmplcSort:
        break;
	case wmplcLast:
        break;
    default:
        break;
    }
}

void CRCServer::CurrentPlaylistChange( WMPPlaylistChangeEventType change )
{
    switch (change)
    {
    case wmplcUnknown:
        break;
	case wmplcClear:
        break;
	case wmplcInfoChange:
        break;
	case wmplcMove:
        break;
	case wmplcDelete:
        break;
	case wmplcInsert:
        break;
	case wmplcAppend:
        break;
	case wmplcPrivate:
        break;
	case wmplcNameChange:
        break;
	case wmplcMorph:
        break;
	case wmplcSort:
        break;
	case wmplcLast:
        break;
    default:
        break;
    }
}

void CRCServer::CurrentPlaylistItemAvailable( BSTR bstrItemName )
{
}

void CRCServer::MediaChange( IDispatch * Item )
{
}

void CRCServer::CurrentMediaItemAvailable( BSTR bstrItemName )
{
}

void CRCServer::CurrentItemChange( IDispatch *pdispMedia)
{
	CComPtr <IWMPMedia> spMedia;
	HRESULT hr = pdispMedia->QueryInterface(&spMedia);
	
	if (SUCCEEDED(hr)) {
			/*CComBSTR sDuration, sName;

			if (SUCCEEDED(hr)) {
				hr = spMedia->get_durationString(&sDuration);
				spMedia->get_name(&sName);
				spMedia->getItemInfo(_T("Author"), &sName);
			}

			if (SUCCEEDED(hr)) {
				MessageBox(NULL, (LPCTSTR)OLE2T(sDuration), _T("Dauer Change"), MB_OK);
				MessageBox(NULL, (LPCTSTR)OLE2T(sName), _T("Name Change"), MB_OK);
			}*/
	}
}

void CRCServer::MediaCollectionChange()
{
}

void CRCServer::MediaCollectionAttributeStringAdded( BSTR bstrAttribName,  BSTR bstrAttribVal )
{
}

void CRCServer::MediaCollectionAttributeStringRemoved( BSTR bstrAttribName,  BSTR bstrAttribVal )
{
}

void CRCServer::MediaCollectionAttributeStringChanged( BSTR bstrAttribName, BSTR bstrOldAttribVal, BSTR bstrNewAttribVal)
{
}

void CRCServer::PlaylistCollectionChange()
{
}

void CRCServer::PlaylistCollectionPlaylistAdded( BSTR bstrPlaylistName)
{
}

void CRCServer::PlaylistCollectionPlaylistRemoved( BSTR bstrPlaylistName)
{
}

void CRCServer::PlaylistCollectionPlaylistSetAsDeleted( BSTR bstrPlaylistName, VARIANT_BOOL varfIsDeleted)
{
}

void CRCServer::ModeChange( BSTR ModeName, VARIANT_BOOL NewValue)
{
}

void CRCServer::MediaError( IDispatch * pMediaObject)
{
}

void CRCServer::OpenPlaylistSwitch( IDispatch *pItem )
{
}

void CRCServer::DomainChange( BSTR strDomain)
{
}

void CRCServer::SwitchedToPlayerApplication()
{
}

void CRCServer::SwitchedToControl()
{
}

void CRCServer::PlayerDockedStateChange()
{
}

void CRCServer::PlayerReconnect()
{
}

void CRCServer::Click( short nButton, short nShiftState, long fX, long fY )
{
}

void CRCServer::DoubleClick( short nButton, short nShiftState, long fX, long fY )
{
}

void CRCServer::KeyDown( short nKeyCode, short nShiftState )
{
}

void CRCServer::KeyPress( short nKeyAscii )
{
}

void CRCServer::KeyUp( short nKeyCode, short nShiftState )
{
}

void CRCServer::MouseDown( short nButton, short nShiftState, long fX, long fY )
{
}

void CRCServer::MouseMove( short nButton, short nShiftState, long fX, long fY )
{
}

void CRCServer::MouseUp( short nButton, short nShiftState, long fX, long fY )
{
}
